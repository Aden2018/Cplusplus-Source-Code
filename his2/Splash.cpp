// Splash.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "Splash.h"
#include "mmsystem.h"
#include "DMessageRead.h"
#include "progressIndicate.h"
#include "excel9.H"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplash dialog
_ConnectionPtr HospitalConnect;
_RecordsetPtr recSet;
const int ONESECOND=1000;

UINT CheckNotify(LPVOID ps) //检查系统中是否有通知
{
	_RecordsetPtr rec1;
	UINT Flag=0;
	CString strSql,strTitle("");
	if(FAILED(rec1.CreateInstance( __uuidof( Recordset ))))
	{
		AfxMessageBox("初始化 全局线程Recordset失败...");
		return false ;
	}
	CString strFileName;
	strFileName.Format("%s",LoginInformation.path);
	strFileName+="RingIN.wav";

	try{
		while(true){
/***********管理员可以杀死当前登录用户**********************/
			strSql.Format("SELECT count(*) FROM lsq_log_operator WHERE logid='%s' AND killflag='1' ",theApp.strLogID);
			rec1->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!rec1->adoEOF){
				strSql=(char*)_bstr_t(rec1->GetFields()->GetItem(0L)->Value);
				rec1->Close();
				if( atol(strSql) != 0 ){

					AfxMessageBox("您已被管理人员禁用当前系统!!!如有疑问,请联系管理人员",MB_OK|MB_ICONSTOP);
				//	AfxGetMainWnd()->MessageBox("您已被管理人员禁用当前系统!!!如有疑问,请联系管理人员","test",MB_OK|MB_ICONSTOP);
					::SendMessage(AfxGetMainWnd()->m_hWnd,WM_CLOSE,0,0);
					return false;
				}
			}else
				rec1->Close();
/***********************************************************************/		
			Flag=0;
			strSql.Format("select * from LSQ_NOTIFY_BODY a ,LSQ_NOTIFY_LIST b \
				WHERE a.ID=b.ID and B.RYBM='%s' and B.READTIME is NULL ",\
				LoginInformation.user_code);
			rec1->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!rec1->adoEOF){

				::sndPlaySound(strFileName,SND_ASYNC|SND_LOOP|SND_NODEFAULT);
				if( MessageBox(NULL,"是否阅读 ????","Hello! You have a Message from your messageBox",MB_OKCANCEL)==IDOK )
				{
					strSql=(char*)_bstr_t(rec1->GetCollect("BODY").vt == VT_NULL ? " ":rec1->GetCollect("BODY"));
					strTitle=(char*)_bstr_t(rec1->GetCollect("TITLE").vt == VT_NULL ? " " :rec1->GetCollect("TITLE"));
					
					
				}
				else strTitle="";
				Flag=1;
				
				::sndPlaySound(NULL,SND_ASYNC|SND_LOOP|SND_NODEFAULT);

			}
			rec1->Close();

			if(! strTitle.IsEmpty() ){
				CDMessageRead read;
				read.DoModal();
				strTitle="";
				
			}
			
			Sleep(30*ONESECOND); //延时20秒
		
			
			
		}
		
	}
	catch(_com_error e)
	{
		rec1->Close();
		AfxMessageBox(strSql);
		return false;
	}



}
/*DWORD WINAPI */ UINT  ConnectData(LPVOID ps)  //此函数作为线程来连接数据库...
{
	AfxOleInit(); //初始化COM库
//	::CoInitialize(NULL);
	if(FAILED(HospitalConnect.CreateInstance(__uuidof(Connection))))
	{
		((CSplash *)ps)->ConnectFlag=true;
		((CSplash *)ps)->timer_count=3; //连接COM失败标志
		((CSplash *)ps)->SendMessage(WM_CLOSE,0,0);
	
		return 0;
	}

	try{
		
		HospitalConnect->Open(_bstr_t(theApp.strConn),"","",adModeUnknown);
		((CSplash *)ps)->ConnectFlag=true;
		((CSplash *)ps)->timer_count=1; //连接成功标志
		((CSplash *)ps)->SendMessage(WM_CLOSE,0,0);
	
		return 1;
	}
	catch(_com_error e)
	{
		((CSplash *)ps)->ConnectFlag=true; //作为进度条线程停止标志
		((CSplash *)ps)->timer_count=2; //连接失败标志

		((CSplash *)ps)->SendMessage(WM_CLOSE,0,0);
	

		return 2;
	
	}

}

 /*DWORD WINAPI*/ UINT Schedule(LPVOID ps)
{
	int i=0;
	while(!((CSplash*)ps)->ConnectFlag ){
	
		((CSplash*)ps)->m_progress.SetPos(i++);
		if(i==100) i=0;
		Sleep(30);
	
	}

	return 1;

}
#define   IDC_PROGRESS_EXCEL WM_USER+1211
void ToExcel(CMSHFlexGrid * pg)
{
	_Application app2;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;
	 COleVariant vOpt2(DISP_E_PARAMNOTFOUND,VT_ERROR);

	CProgressEx pp;
	CRect r1(0,0,400,25);
	pp.Create(WS_CHILD |PBS_SMOOTH|WS_BORDER ,r1,AfxGetMainWnd()->GetForegroundWindow(),IDC_PROGRESS_EXCEL);
	pp.UpdateWindow();
	pp.ShowWindow(SW_SHOW);
	pp.CenterWindow();
	pp.Invalidate();
	pp.SetRange32(0,pg->GetRows() );
	pp.strView="正在准备导出...请稍等!!";

//	if( ! app2 ){
	app2.CreateDispatch("excel.application");
	if(!app2){
		AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
		return;
	}
	books2=app2.GetWorkbooks();
	//		book2=books2.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	book2=books2.Add(vOpt2);
	sheets2=book2.GetWorksheets();
	sheet2=sheets2.GetItem(COleVariant((short)1));
//	}

//


	Range vRange;
	Font font;
	long x,y;
	CString str1,str2;
	
	app2.SetVisible(false);
	pp.strView="";


	for (x=0; x<pg->GetRows(); x++)
	{
		for( y=0 ; y< pg->GetCols(0) ; y++ )
		{
			if( y<26)str1.Format("%c%ld",'A'+y , x+1 );
			else str1.Format("%c%c%ld",'A'+ ( y/26 -1) ,'A'+y % 26,x+1 );
			vRange=sheet2.GetRange(_variant_t(str1),_variant_t(str1)); // 医疗机构
		//	font=vRange.GetFont();
		//	font.SetName(_O(FONTNAME));
		//	font.SetSize(_O((short)STANDARDFONT));
			vRange.SetValue(COleVariant(pg->GetTextMatrix(x,y)));
		}
		
		pp.strView.Format("%2.0f%%",double(x)/pg->GetRows()*100);
		pp.SetPos(x);
	}
	app2.SetVisible(true);
		
	pp.DestroyWindow();
	sheet2.ReleaseDispatch();

	sheets2.ReleaseDispatch();
//	book.Close(_O((short)0),vOpt,vOpt); //关闭EXCEL,不保存文件

	book2.ReleaseDispatch();
//	books2.Close();
	books2.ReleaseDispatch();
	app2.ReleaseDispatch();	

}
CSplash::CSplash(CWnd* pParent /*=NULL*/)
	: CDialog(CSplash::IDD, pParent)
{
	timer_count=0;
	ConnectFlag=false;
	//{{AFX_DATA_INIT(CSplash)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSplash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplash)
	DDX_Control(pDX, IDC_PROGRESS_SPLASH, m_progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSplash, CDialog)
	//{{AFX_MSG_MAP(CSplash)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplash message handlers

BOOL CSplash::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString strFileName;
	strFileName.Format("%s",LoginInformation.path);
	strFileName+="splash.bmp";

	hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), \
		strFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);

    ////////////////////该断程序用来取得加载的BMP的信息////////////////////////

    m_bitmap.Attach( hbmp );

 //   DIBSECTION ds;

   // BITMAPINFOHEADER &bminfo = ds.dsBmih; 

    m_bitmap.GetObject( sizeof(BITMAP), &bmp );
	
	// TODO: Add extra initialization here
/*	m_bitmap.LoadBitmap(IDB_BITMAP_SPLASH);

	BITMAP bmp;

	m_bitmap.GetObject(sizeof(BITMAP),&bmp);
*/
	CRect rtOld,rtProgress;

	GetWindowRect(rtOld);

	CPoint point = rtOld.TopLeft();//pl(bmp.bmWidth-100,bmp.bmHeight-50),pr(bmp.bmWidth-10,bmp.bmHeight-20);

	CRect rtNew = CRect(point,CSize(bmp.bmWidth,bmp.bmHeight));   

	MoveWindow(rtNew);
//调整流动条控件位置	
	rtProgress.left=20;
	rtProgress.top=bmp.bmHeight-52;
	rtProgress.right=bmp.bmWidth-20;
	rtProgress.bottom=rtProgress.top+30;
	m_progress.MoveWindow(rtProgress);


	::SetWindowPos(GetSafeHwnd() , HWND_TOPMOST ,  rtNew.left ,rtNew.top , rtNew.Width() , rtNew.Height(), SWP_NOSIZE );

	
	CenterWindow();
	AnimateWindow(m_hWnd,300,AW_SLIDE|AW_CENTER);
	
	Invalidate(); 
//	DWORD pid;
//	::CreateThread(NULL,NULL,::ConnectData,(LPVOID)this,0,&pid);
//	::CreateThread(NULL,NULL,Schedule,(LPVOID)this,0,&pid);
//	UINT connectData(LPVOID);
	AfxBeginThread(ConnectData,(LPVOID)this);
	
	AfxBeginThread(Schedule,(LPVOID)this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CSplash::OnPaint() 
{
//	CPaintDC dc(this); // device context for painting
	
	CPaintDC pv(this); // device context for painting
	
	BITMAP bmp;
	m_bitmap.GetObject(sizeof(BITMAP),&bmp);
	
//	HBITMAP bit=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_SPLASH));
	HBITMAP bit=hbmp;
	HDC hdc=::CreateCompatibleDC(NULL);
	SelectObject(hdc,bit);

	::StretchBlt(pv.m_hDC,0,0,bmp.bmWidth,bmp.bmHeight,hdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	::DeleteDC(hdc);
	::DeleteObject(bit);	// TODO: Add your message handler code here


	// Do not call CDialog::OnPaint() for painting messages
}



BOOL CSplash::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN )return true;
		
	return CDialog::PreTranslateMessage(pMsg);
}

void WriteDebug(CString strOut)
{
	extern CFile fDebug;
	COleDateTime curDate=COleDateTime::GetCurrentTime();
	CString strFmt;
	CString strRet("\r\n");
	CString strSpan('-',40);
	strFmt.Format("%s\r\n",curDate.Format("%Y-%m-%d %H %M %S") );
	fDebug.Write(strFmt,strFmt.GetLength());
	strSpan+=strRet;
	fDebug.Write(strSpan,strSpan.GetLength());

	fDebug.Write(strOut,strOut.GetLength());
	fDebug.Write(strRet+strRet,strRet.GetLength()*2 );

}