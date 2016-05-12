// DialogInStorage.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "DialogInStorage.h"
#include "QueryRybm.h"
#include "codegysQuery.h"
#include "medCodeQuery.h"
#include "excel9.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogInStorage dialog
extern _Application app;
extern Workbooks books;
extern _Workbook book;
extern Worksheets sheets;
extern _Worksheet sheet;
extern COleVariant vOpt;

CDialogInStorage::CDialogInStorage(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogInStorage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogInStorage)
	riqi = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	c_ywyID="";
	c_gysID="";

}


void CDialogInStorage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogInStorage)
	DDX_Control(pDX, IDB_EXCEL_PRINT, m_excel_button);
	DDX_Control(pDX, IDC_EDIT_SERIAL, c_serial);
	DDX_Control(pDX, IDB_SEARCH, m_334);
	DDX_Control(pDX, IDC_BUTTON_YWY, m_33);
	DDX_Control(pDX, IDC_BUTTON_GYS, m_22);
	DDX_Control(pDX, IDCANCEL, m_4);
	DDX_Control(pDX, IDOK, m_1);
	DDX_Control(pDX, IDC_EDIT_OPERATOR, m_2);
	DDX_Control(pDX, IDC_EDIT_YWY, c_ywy);
	DDX_Control(pDX, IDC_EDIT_PAOJU, c_paoju);
	DDX_Control(pDX, IDC_EDIT_GYS, c_gys);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, riqi);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogInStorage, CDialog)
	//{{AFX_MSG_MAP(CDialogInStorage)
	ON_BN_CLICKED(IDC_BUTTON_GYS, OnButtonGys)
	ON_BN_CLICKED(IDC_BUTTON_YWY, OnButtonYwy)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDB_SEARCH, OnSearch)
	ON_EN_KILLFOCUS(IDC_EDIT_GYS, OnKillfocusEditGys)
	ON_EN_SETFOCUS(IDC_EDIT_GYS, OnSetfocusEditGys)
	ON_EN_KILLFOCUS(IDC_EDIT_YWY, OnKillfocusEditYwy)
	ON_EN_SETFOCUS(IDC_EDIT_YWY, OnSetfocusEditYwy)
	ON_BN_CLICKED(IDB_EXCEL_PRINT, OnExcelPrint)
	//}}AFX_MSG_MAP
	ON_EN_KILLFOCUS(T_EDIT1,OnKillEditCtrl)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogInStorage message handlers

BOOL CDialogInStorage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	fontTitle.CreatePointFont(220,"����");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	
	GetDlgItem(IDC_EDIT_OPERATOR)->SetWindowText(LoginInformation.user);

	Startup();

	fontMoveEdit.CreatePointFont(120,"����");
	CRect r1(0,0,0,0);
	editCtrl.Create(WS_CHILD,r1,this,T_EDIT1);
	comCtrl.Create(WS_CHILD,r1,this,T_COMBO1);
	editCtrl.SetFont(&fontMoveEdit);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogInStorage::OnButtonGys() 
{
	CCodeGysQuery gys;
	gys.strFlag=" AND Flag='A' "; //��ѯ��Ӧ��

	if(gys.DoModal()==IDOK){
		c_gys.SetWindowText(gys.strName);
		c_gysID=gys.strNum;
		c_gysName=gys.strName;
	
	}
		// TODO: Add your control notification handler code here
	
}

void CDialogInStorage::OnButtonYwy() 
{
	CQueryRybm rybm;
	if(rybm.DoModal()==IDOK)// TODO: Add your control notification handler code here
	{
		c_ywy.SetWindowText(rybm.strName);
		c_ywyID=rybm.strNum;
		c_ywyName=rybm.strName;

	}
}
HBRUSH CDialogInStorage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->m_hWnd == GetDlgItem(IDC_EDIT_YWY)->m_hWnd || pWnd->m_hWnd == \
		GetDlgItem(IDC_EDIT_GYS)->m_hWnd || pWnd->m_hWnd == GetDlgItem(IDC_EDIT_OPERATOR)->m_hWnd \
		|| pWnd->m_hWnd==GetDlgItem(IDC_EDIT_SERIAL)->m_hWnd)pDC->SetTextColor(RGB(255,0,0));
	// TODO: Return a different brush if the default is not desired
	if(pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd ){
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));
		return theApp.titleBrush;


	}
	return hbr;
}
//*********************************************************************************
//* ҩƷ��Ϣ��⣬��Ϊ���������ֱ�������������ظ����ݺ����������ݿ���ԭ�е���
//* �ţ�ע�ⵥ�ݺ�������ݿ���ѡ��
//********************************************************************************
void CDialogInStorage::OnOK() 
{
	UpdateData();
	CString strSql,danjuhao,danjuhao2,paoju,ywy,str[20];
	c_serial.GetWindowText(danjuhao2);
	c_paoju.GetWindowText(paoju);
	c_ywy.GetWindowText(ywy);
	if(c_gysID.IsEmpty() || c_ywyID.IsEmpty() || paoju.IsEmpty() ){
		AfxMessageBox("�뽫������Ŀ��д�����ٽ���������...");
		return;
	}
	long rows=m_grid.GetRows()-2; //�õ�ҩƷ����
	if( 0 == rows)return;
	/*"S","����","С��","����","����","���","��λ","����","����ID","����","����","�ۼ�","��Ч��","������","ָ����"
       0     1       2      3    4        5     6      7      8       9      10      11    12        13        14   */

	try{
	//* ����һ����ѯϵͳ���Ƿ��������Ʊ�ݺţ����򲻽���ͷ��������ֱ�ӽ������
		HospitalConnect->BeginTrans();
	
	
		for(long i=0;i<rows;i++){
			paoju=m_grid.GetTextMatrix(i+1,15);
			strSql.Format(" Select danjuhao from itemrkTou Where piaojuhao='%s' ",paoju ); //Ʊ�ݺ�
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			danjuhao.Empty();
			if( ! recSet->adoEOF )	danjuhao=(char*)_bstr_t (recSet->GetFields()->GetItem(0L)->Value);
			recSet->Close();
			if( danjuhao.IsEmpty() ){
			//* ҵ��Ա����Ϊ��ǰ��
				c_ywyID=m_grid.GetTextMatrix(i+1,19); //ҵ��ԱID
				ywy=m_grid.GetTextMatrix(i+1,18); //ҵ��Ա
				c_gysID=m_grid.GetTextMatrix(i+1,17);//��Ӧ�̱���

				
				strSql.Format("_%d",i);
				danjuhao=danjuhao2+strSql;
				strSql.Format("insert into ItemRkTou (danjuhao,piaojuhao,riqi,gongbm,kfbm,ҵ��Ա,\
					ҵ��Ա��,���Ա,���Ա��) values('%s','%s',to_date('%s','yyyymmdd'),'%s','%s',\
					'%s','%s','%s','%s' ) ",danjuhao,paoju,riqi.Format("%Y%m%d"),c_gysID,\
					LoginInformation.kfbm,c_ywyID,ywy,LoginInformation.user_code,LoginInformation.user);
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			}
		
		
			str[0]=m_grid.GetTextMatrix(i+1,3/*ҩƷ����*/);
			str[1]=LoginInformation.kfbm;/*�ⷿ����*/
			for(int x=8;x<15;x++)
				str[x]=m_grid.GetTextMatrix(i+1,x);
		
			strSql.Format("select * from medlie where kfbm='%s' and sl=0 ",str[1]);
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){
				str[2]/*ҩƷID*/=(char*)_bstr_t(recSet->GetCollect("ID"));

			}
			else {
				recSet->Close();
				strSql.Format("select max(ID)+1 newID from medlie ");
				recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
				str[2]=(char*)_bstr_t(recSet->GetCollect("newID"));
			}
			recSet->Close();
			
			strSql.Format("delete from  medlie where id=%s ",str[2]);
			
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		
			strSql.Format("insert into medlie (id,kfbm,ypbm,factorycode,rq1,rq2,sl,jinjia,sell_price,coach_price) \
				values(%s,'%s','%s','%s',to_date('%s','yyyy-mm-dd'),to_date('%s','yyyy-mm-dd'),%.2f,%.2f,\
				%.2f,%.2f  ) ",str[2],str[1],str[0],str[8],str[13],str[12],atof(str[9]),atof(str[10]),\
				atof(str[11]),atof(str[14]));

			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

			strSql.Format("insert into ITEMTI (id,sl,dj,selldj,pdj,jssl,riqi,danjuhao,rq1,rq2,ypbm,kfbm,factory ) values(%s,\
				%.2f,%.2f,%.2f,%.2f,%.2f,to_date('%s','yyyymmdd'),'%s',to_date('%s','yyyy-mm-dd'),to_date('%s','yyyy-mm-dd'),\
				'%s','%s','%s' ) ",str[2],atof(str[9]),atof(str[10]),\
				atof(str[11]),atof(str[14]),atof(str[9]),riqi.Format("%Y%m%d"),danjuhao,\
				str[13],str[12],str[0],str[1],m_grid.GetTextMatrix(i+1,7)/*����*/);
		
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		}


		HospitalConnect->CommitTrans();

	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox(strSql);
		AfxMessageBox("���ʧ��,������Ӧ�ó���Ȼ�����²���һ��...");
		return;


	}
	AfxMessageBox("ҩƷ���ɹ�...");
	Startup();
	c_paoju.SetWindowText("");
}

void CDialogInStorage::OnSearch() //ҩƷ��������
{
	UpdateData();
	theApp.pParentGrid.pGrid=&m_grid;
	theApp.pDialog=this;
	CMedCodeQuery med;
	med.DoModal();
	CalculatePrice();
	
}

BEGIN_EVENTSINK_MAP(CDialogInStorage, CDialog)
    //{{AFX_EVENTSINK_MAP(CDialogInStorage)
	ON_EVENT(CDialogInStorage, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDialogInStorage::OnDblClickMshflexgrid1() 
{
	if(m_grid.GetRow()==m_grid.GetRows()-1 || m_grid.GetCol()<7)return;
	CDC *pCdcGrid=m_grid.GetDC();
	int nWidth=pCdcGrid->GetDeviceCaps(LOGPIXELSX);
	int nHigh=pCdcGrid->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pCdcGrid);

	long	row=m_grid.GetRow();
	long 	col=m_grid.GetCol();
	CString str2;
	CString	strOrigin=m_grid.GetTextMatrix(row,col);

	long left=m_grid.GetCellLeft();
	long top=m_grid.GetCellTop();
	long right=m_grid.GetCellWidth();
	long bottom=m_grid.GetCellHeight();

	CRect rectGrid,r2;
	m_grid.GetWindowRect(rectGrid);
	ScreenToClient(rectGrid);
	rectGrid.left+=left*nWidth/1440;
	rectGrid.top+=top*nHigh/1440;
	rectGrid.right=right*nWidth/1440+rectGrid.left;
	rectGrid.bottom=bottom*nHigh/1440+rectGrid.top;

/*  r2=rectGrid;
	rectGrid.right-=20;

	r2.left=rectGrid.right;
	bt.MoveWindow(r2);
	bt.ShowWindow(SW_SHOW);
	bt.SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
*/

	editCtrl.MoveWindow(rectGrid);
	editCtrl.ShowWindow(SW_SHOW);
	editCtrl.SetFocus();
	editCtrl.SetWindowText(strOrigin);
	editCtrl.SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	editCtrl.SetSel(0,strOrigin.GetLength());		
}

void CDialogInStorage::OnKillEditCtrl()
{
	CString str1;
	editCtrl.GetWindowText(str1);
	m_grid.SetTextMatrix(m_grid.GetRow(),m_grid.GetCol(),str1);
	editCtrl.ShowWindow(SW_HIDE);
	CalculatePrice();
}

BOOL CDialogInStorage::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		if(GetFocus()->m_hWnd == GetDlgItem(T_EDIT1)->m_hWnd){
			OnKillEditCtrl();
			return true;

		}
		else if(GetFocus()->m_hWnd == GetDlgItem(IDC_MSHFLEXGRID1)->m_hWnd)
		{
				OnSearch();
				return true;
		}
		else pMsg->wParam=VK_TAB;
		return CDialog::PreTranslateMessage(pMsg);

	}
/////////////////////////////ɾ������
	if(pMsg->message==WM_RBUTTONUP && GetFocus()->m_hWnd == m_grid.m_hWnd )
	{
		if( m_grid.GetRow() >= m_grid.GetRows()-1)return true;
		m_grid.RemoveItem(m_grid.GetRow());
		CalculatePrice();
		return true;

	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDialogInStorage::Startup()
{
	CString strSql,m_rktou;
	try{
		strSql.Format("select distinct to_char(sysdate,'yyyymmddhh24miss') da from dual" );
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		
		if(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t (recSet->GetCollect("da"));
			m_rktou='A';
			m_rktou+=strSql;
			
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox("ϵͳ���ֹ��ϣ��������ݿ�ϵͳ��������");
		//HospitalConnect->Close();
		return ;
	}
	GetDlgItem(IDC_EDIT_SERIAL)->SetWindowText(m_rktou);
	
	m_grid.SetRows(2);
	m_grid.Clear();

	CString HeadTitle[]={"S","����","С��","����","����","���","��λ","����","ID","����",\
		"����","�ۼ�","��Ч��","������","ָ����","��Ʊ��","��Ӧ��","bm1","ҵ��Ա","bm2" }; //��������

	long  headWidth[]={400,00,00,1200,2000,1600,800,1400,0,1200,1200,1200,1600,1600,1200,1200,1200,0,1200,0};

	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����кϲ�
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	
}

BOOL CDialogInStorage::GetName_ID(CString strSql, CString &strName, CString &strID)
{

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			strName=(char*) _bstr_t(recSet->GetFields()->GetItem((short)0)->Value);
			strID=(char*)_bstr_t(recSet->GetFields()->GetItem((short)1)->Value);
			recSet->Close();
			return true;
		}
		else {
			recSet->Close();
			return false;
		}

	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox("��ѯSQL����...");
		return false;
	}
	return true;

}

void CDialogInStorage::OnKillfocusEditGys() 
{
	CString str1,str2,str3;
	c_gys.GetWindowText(str2); //����
	if( str2 == c_gysID ) {
		c_gys.SetWindowText(c_gysName);
		return;
	}
	if( !str2.IsEmpty() ){
		str1.Format(" SELECT NVL(gongmc,' '),gongbm FROM codegys WHERE gongbm='%s' ",str2);
		if( GetName_ID(str1,str2,str3) ){ //�ֱ�ΪSQL,name,id
			c_gys.SetWindowText(str2);
			c_gysName=str2;
			c_gysID=str3;
			return;
		}
		c_gysID="";
		c_gysName="";
		c_gys.SetWindowText("");

	}
}

void CDialogInStorage::OnSetfocusEditGys() 
{
	c_gys.SetWindowText(c_gysID);
}

void CDialogInStorage::OnKillfocusEditYwy() 
{
	// TODO: Add your control notification handler code here
	CString str1,str2,str3;
	c_ywy.GetWindowText(str2); //����
	if( str2 == c_ywyID ){
		c_ywy.SetWindowText(c_ywyName);
		return;
	}
	if( !str2.IsEmpty() ){
		str1.Format(" SELECT NVL(name,' '),rybm FROM operator WHERE rybm='%s' ",str2);
		if( GetName_ID(str1,str2,str3) ){ //�ֱ�ΪSQL,name,id
			c_ywy.SetWindowText(str2);
			c_ywyName=str2;
			c_ywyID=str3;
			return;
		}
		c_ywyID="";
		c_ywyName="";
		c_ywy.SetWindowText("");

	}	
}

void CDialogInStorage::OnSetfocusEditYwy() 
{
	// TODO: Add your control notification handler code here
	c_ywy.SetWindowText(c_ywyID);
}




void CDialogInStorage::OnExcelPrint() //�����excel���д�ӡ
{
#define _O(x) COleVariant(x)
#define STANDARDFONT  9
#define FONTNAME	"����"

	CString str[10];
	
	c_serial.GetWindowText(str[1]); //����
	c_paoju.GetWindowText(str[2]); //Ʊ��
	c_ywy.GetWindowText(str[3]); //ҵ��Ա
	c_gys.GetWindowText(str[4]); //��Ӧ��
	str[5]=riqi.Format("%Y-%m-%d"); //����
	str[6]=LoginInformation.user; //�����û�

	if(str[1].IsEmpty() || str[2].IsEmpty() || str[3].IsEmpty() ){
		AfxMessageBox("�뽫������Ŀ��д�����ٽ���������...");
		return;
	}

	
	COleDateTime curDate=COleDateTime::GetCurrentTime();
	CString strCurDate,strMedica,s1,s2,s3,str2;
	int x ,y,intLastRow=m_grid.GetRows()-1;
	int intCols=m_grid.GetCols(0);
	str[0].Format("%d",intLastRow-1);

	strCurDate=curDate.Format("%Y-%m-%d");
//	BeginWaitCursor();
	CString strFileName,strLoc;
	strFileName.Format("%s",LoginInformation.path);
	strFileName+=COtherDecharge::GetStringTitle("Select ds3 From lsq_upgrade Where ds2='PRINT_RK' ");

	app.CreateDispatch("excel.application");
	if(!app){
		AfxMessageBox("��ע��ϵͳ�б���װ��EXCEL97 ���� EXCEL2000 ,����˹��ܲ���ʹ��...");
		return;
	}
	books=app.GetWorkbooks();
	book=books.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	sheets=book.GetWorksheets();

	sheet=sheets.GetItem(COleVariant((short)2));

//	{"ID","ҩƷ����","ҩƷ����","���","��λ","������","��Ч��",\
		"����BM","����","�����","���ۼ�","����","ָ����","ȡҩ��","���ö�"}; //��14��+1
	Range vRange;
	Font font;
	app.SetVisible(true); //��ʾ

	for ( x=1; x< intLastRow ; x++)
	{
		for(y=0; y< intCols ; y++){

			strLoc.Format("%c%d",'A'+y,x+1);
			vRange=sheet.GetRange(_O(strLoc),_O(strLoc)); // ҽ�ƻ���
			
			vRange.SetValue(COleVariant(m_grid.GetTextMatrix(x,y)));
		}
	}
	for( x=0; x < 7 ; x++ )
	{
		strLoc.Format("%c%d",'A'+x,1);
		vRange=sheet.GetRange(_O(strLoc),_O(strLoc)); // ҽ�ƻ���
		
		vRange.SetValue(COleVariant(str[x]));
		

	}



	
//Print cell data
	app.Run(COleVariant("thisWorkBook.PrintSheet"),vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
		vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
		vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt );

	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();	
/*
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
//	book.Close(_O((short)0),vOpt,vOpt); //�ر�EXCEL,�������ļ�

	book.ReleaseDispatch();
//	books.Close();
	books.ReleaseDispatch();

	app.ReleaseDispatch();
	app.Quit();
*/
	EndWaitCursor();

}


void CDialogInStorage::CalculatePrice()  //* ͳ�Ƴ�������ҩƷ���ۺ�
{
	long iRows=m_grid.GetRows();
	double dbPrice=0.;
	CString str;
	if ( iRows == 2 ) {
		m_grid.SetTextMatrix(1,9,"");
		m_grid.SetTextMatrix(1,10,"");
		return;
	}

	for(long i=1; i < iRows-1 ; i++ )
	{
		dbPrice+=atof(m_grid.GetTextMatrix(i,10))*atof(m_grid.GetTextMatrix(i,9)); //ҩƷ����,ҩƷ����
		
	}
	str.Format("%.2f",dbPrice);
	m_grid.SetTextMatrix(i,9,"������");
	m_grid.SetTextMatrix(i,10,str);
	
}
