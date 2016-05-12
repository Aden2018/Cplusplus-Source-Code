// MoveKf.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "MoveKf.h"
#include "queryRybm.h"
#include "medStockList.h"
#include "DialogInStorage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMoveKf dialog


CMoveKf::CMoveKf(CWnd* pParent /*=NULL*/)
	: CDialog(CMoveKf::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMoveKf)
	m_date = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"宋体");
	c_getRymcID="";
	c_getRymcName="";
	flagPANDIAN=0;
}


void CMoveKf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMoveKf)
	DDX_Control(pDX, IDOK_EFFIECT, m_45);
	DDX_Control(pDX, IDC_COMBO_CONSUME, c_use);
	DDX_Control(pDX, IDOK_SEARCH, m_22);
	DDX_Control(pDX, IDC_EDIT_GET_RYMC, c_getRymc);
	DDX_Control(pDX, IDC_EDIT_DANJUHAO, c_danjuhao);
	DDX_Control(pDX, IDC_EDIT_CUR_KF, m_curKf);
	DDX_Control(pDX, IDC_COMBO_GET_KF, c_getKf);
	DDX_Control(pDX, IDC_BUTTON_RYBM, m_4);
	DDX_Control(pDX, IDCANCEL, m_3);
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, IDC_MSHFLEXGRID2, m_grid);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMoveKf, CDialog)
	//{{AFX_MSG_MAP(CMoveKf)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_RYBM, OnButtonRybm)
	ON_BN_CLICKED(IDOK_SEARCH, OnSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_GET_KF, OnSelchangeComboGetKf)
	ON_EN_KILLFOCUS(IDC_EDIT_GET_RYMC, OnKillfocusEditGetRymc)
	ON_EN_SETFOCUS(IDC_EDIT_GET_RYMC, OnSetfocusEditGetRymc)
	ON_BN_CLICKED(IDOK_EFFIECT, OnEffiect)
	//}}AFX_MSG_MAP
	ON_EN_KILLFOCUS(T_EDIT_YPZK,OnKillEditCtrl)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoveKf message handlers

BOOL CMoveKf::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	CString strSql;
	try{
		strSql.Format("select distinct(kfmc) from storeroom  ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetCollect("kfmc").vt==VT_NULL?" ":recSet->GetCollect("kfmc"));
			c_getKf.AddString(strSql);
			recSet->MoveNext();

		
		}
		recSet->Close();
		
		strSql.Format("select distinct to_char(sysdate,'yyyymmddhh24miss') da from dual" );
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		
		if(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t (recSet->GetCollect("da"));
			m_zktou='Z';
			m_zktou+=strSql;
			
		}
		recSet->Close();
		c_danjuhao.SetWindowText(m_zktou);
		m_curKf.SetWindowText(LoginInformation.kfmc);


	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		

	CRect r1(0,0,0,0);
	editCtrl.Create(WS_CHILD,r1,this,T_EDIT_YPZK);

	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","售价","进价","指导价","取药数"}; //共14列
	long  headWidth[]={0,00,2000,1600,600,0,1400,0,1600,1000,000,0,0,1200};


	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	

	


	SetWindowText("药品转库操作");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
HBRUSH CMoveKf::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	pDC->SetBkMode(TRANSPARENT);
	
	if(pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd){
		pDC->SetTextColor(RGB(255,255,255));
		return theApp.titleBrush;

	}
	if(pWnd->m_hWnd == c_getRymc.m_hWnd || pWnd->m_hWnd == c_danjuhao.m_hWnd 
		|| pWnd->m_hWnd == m_curKf.m_hWnd )
	{
		pDC->SetBkColor(RGB(255,255,255));
		pDC->SetTextColor(RGB(255,0,0));
	}
	
	return GetSysColorBrush(20);
	
	// TODO: Return a different brush if the default is not desired
//	return hbr;
}

void CMoveKf::OnButtonRybm() 
{
	CQueryRybm rybm;
	if(rybm.DoModal()==IDOK)// TODO: Add your control notification handler code here
	{
		c_getRymc.SetWindowText(rybm.strName);
		c_getRymcName=rybm.strName;
		c_getRymcID=rybm.strNum;

	}
}

BEGIN_EVENTSINK_MAP(CMoveKf, CDialog)
    //{{AFX_EVENTSINK_MAP(CMoveKf)
	ON_EVENT(CMoveKf, IDC_MSHFLEXGRID2, -601 /* DblClick */, OnDblClickMshflexgrid2, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CMoveKf::OnDblClickMshflexgrid2() 
{
	if(m_grid.GetRow()==m_grid.GetRows()-1 || m_grid.GetCol() != 13){
		OnSearch();	
		return; //列13为取药数
	}
	CDC *pCdcGrid=m_grid.GetDC();
	int nWidth=pCdcGrid->GetDeviceCaps(LOGPIXELSX);
	int nHigh=pCdcGrid->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pCdcGrid);

	long    row=m_grid.GetRow();
	editRow=row;
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
	rectGrid.right=right*nWidth/1440+rectGrid.left-1;
	rectGrid.bottom=bottom*nHigh/1440+rectGrid.top-1;

	editCtrl.MoveWindow(rectGrid);
	editCtrl.ShowWindow(SW_SHOW);
	editCtrl.SetFocus();
	editCtrl.SetWindowText(strOrigin);
	editCtrl.SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	editCtrl.SetSel(0,strOrigin.GetLength());
	
}

void CMoveKf::OnSearch() 
{
	CMedStockList medlist;
	theApp.pParentGrid.pGrid=&m_grid;
	GetDlgItem(IDC_EDIT_CUR_KF)->GetWindowRect(medlist.r1);
	medlist.flagMoveKF=111; //作为转移库房时用,不要输入药品
	medlist.DoModal();
	
}

void CMoveKf::OnOK()  //药品转库操作
{
	UpdateData();
	CString strSql,danjuhao,ywy,str[20];

	c_getRymc.GetWindowText(ywy);
	c_danjuhao.GetWindowText(danjuhao);


	if(c_getKf.GetCurSel() == CB_ERR || ywy.IsEmpty() ){
		AfxMessageBox("请将所有项目填写完整再进行转库操作...");
		return;
	}

	long rows=m_grid.GetRows()-2; //得到药品行数
	if( 0 == rows)return;
/*	CString HeadTitle[]={"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
																	5		  6
	  "产地BM","产地","库存量","售价","进价","指导价","取药数"}; //共14列
						9        10              12      13
*/
	try{
		HospitalConnect->BeginTrans();

		strSql.Format("insert into ItemZkTou (danjuhao,riqi,领料员,领料员名,DFKF,BFKF,\
			发料员,发料员名 ) values('%s',TRUNC(SYSDATE,'dd'),'%s','%s',\
			'%s','%s','%s','%s' ) ",danjuhao,c_getRymcID,ywy,m_getKfbm,\
			LoginInformation.kfbm,LoginInformation.user_code,LoginInformation.user);
	
	
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		for(long i=0;i<rows;i++){
			str[0]=m_grid.GetTextMatrix(i+1,1/*药品编码*/);
			str[1]=LoginInformation.kfbm;/*库房编码*/
			str[4]=m_grid.GetTextMatrix(i+1,0/*药品ID*/);
			str[3]=m_getKfbm; //目的库房编码


			for(int x=5;x<14;x++)
				str[x]=m_grid.GetTextMatrix(i+1,x);
	      //自动生成药品  ID	
			strSql.Format("select * from medlie where kfbm='%s' and sl=0 and ypbm='%s' ",str[3],str[0]);
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){
				str[2]/*药品ID*/=(char*)_bstr_t(recSet->GetCollect("ID"));

			}
			else {
				recSet->Close();
				strSql.Format("select max(ID)+1 newID from medlie ");
				recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
				str[2]=(char*)_bstr_t(recSet->GetCollect("newID"));
			}
			recSet->Close();
///////////////////////////////////////////////////////////////////////////////			
			strSql.Format("delete from  medlie where id=%s ",str[2]);
			
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		
			strSql.Format("insert into medlie (id,kfbm,ypbm,factorycode,rq1,rq2,sl,jinjia,sell_price,coach_price) \
				values(%s,'%s','%s','%s',to_date('%s','yyyy-mm-dd'),to_date('%s','yyyy-mm-dd'),%.2f,%.2f,\
				%.2f,%.2f  ) ",str[2],str[3],str[0],str[7],str[5],str[6],atof(str[13]),atof(str[11]),\
				atof(str[10]),atof(str[12]));

			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			strSql.Format("UPDATE MEDLIE set SL=SL-%.2f where ID=%s and KFBM='%s' ",atof(str[13]),str[4],str[1]);
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

			strSql.Format("insert into ITEMTI (id,sl,dj,selldj,riqi,danjuhao,rq1,rq2,ypbm,kfbm,factory,kfbm2 ) values(%s,\
				%.2f,%.2f,%.2f,TRUNC(SYSDATE,'dd'),'%s',to_date('%s','yyyy-mm-dd'),to_date('%s','yyyy-mm-dd'),\
				'%s','%s' ,'%s','%s') ",str[2],atof(str[13]),atof(str[10]),\
				atof(str[11]),danjuhao,	str[5],str[6],str[0],str[3],str[8],str[1]); //新增一列源库房编码
		
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		}


		HospitalConnect->CommitTrans();

		strSql.Format("select distinct to_char(sysdate,'yyyymmddhh24miss') da from dual" );
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		
		if(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t (recSet->GetCollect("da"));
			m_zktou='Z';
			m_zktou+=strSql;
			
		}
		recSet->Close();
		c_danjuhao.SetWindowText(m_zktou);

	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox(strSql);
		AfxMessageBox("转库失败,请重启应用程序然后重新操作一次...");
		return;


	}
	AfxMessageBox("药品转库成功...");

	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","售价","进价","指导价","取药数"}; //共14列
	long  headWidth[]={0,00,2000,1600,600,0,1400,0,1600,1000,000,0,0,1200};


	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	






}

void CMoveKf::OnKillEditCtrl()
{
	CString str1;
	double flSL;

	editCtrl.GetWindowText(str1);

	flSL=atof(str1);
	if ( flagPANDIAN != 888 && flagPANDIAN !=999 )
			if(flSL > atof(m_grid.GetTextMatrix(editRow,9))){ //库存数
				
				AfxMessageBox("提取的药品数量大于库存量...");
				editCtrl.SetWindowText("");
				editCtrl.SetFocus();
				return ;
			}
	else if( flagPANDIAN == 999 ) //报损药品时用
	{
			if( flSL > atof(m_grid.GetTextMatrix(editRow,9)) || flSL <=0 ){

				AfxMessageBox("输入的药品数量不正确...不能小于等于零 或者 大于药品库存量");
				editCtrl.SetWindowText("");
				editCtrl.SetFocus();
				return ;
			}



	}
	
	
	str1.Format("%.2f",flSL);

	m_grid.SetTextMatrix(editRow,13,str1); //提取数


	editCtrl.SetWindowText("");
	editCtrl.ShowWindow(SW_HIDE);
	m_3.SetFocus();
}

BOOL CMoveKf::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN ){
		if(	GetFocus()->m_hWnd == editCtrl.m_hWnd ) {
			CString str1;
			double flSL;
			
			editCtrl.GetWindowText(str1);
			
			flSL=atof(str1);
			if ( flagPANDIAN != 888 || flagPANDIAN != 999)
				
				if(flSL > atof(m_grid.GetTextMatrix(editRow,9))){ //库存数
					
					//	AfxMessageBox("提取的药品数量大于库存量...");
					//	editCtrl.SetFocus();
					editCtrl.SetWindowText("");
					return true ;
				}
				
				if( flagPANDIAN == 999 && (flSL > atof(m_grid.GetTextMatrix(editRow,9)) || flSL <=0  )){
					editCtrl.SetWindowText("");
					return true ;
				}

			
			str1.Format("%.2f",flSL);
			
			m_grid.SetTextMatrix(editRow,13,str1); //提取数
			
			
			editCtrl.ShowWindow(SW_HIDE);
			
			if(m_grid.GetRow() < m_grid.GetRows()-2){
				m_grid.SetRow(m_grid.GetRow()+1);
				OnDblClickMshflexgrid2();
				
			}	
			return true;
		}
		else if(GetFocus()->m_hWnd == GetDlgItem(IDC_MSHFLEXGRID2)->m_hWnd)
		{
				OnSearch();
				return true;
		}
		else pMsg->wParam=VK_TAB;
		return CDialog::PreTranslateMessage(pMsg);
	}
///////右键删除
	if(pMsg->message==WM_RBUTTONUP && GetFocus()->m_hWnd == m_grid.m_hWnd)
	{
		if( m_grid.GetRow() >= m_grid.GetRows()-1)return true;
		m_grid.RemoveItem(m_grid.GetRow());
		return true;

	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CMoveKf::OnSelchangeComboGetKf() 
{
	if(c_getKf.GetCurSel() == CB_ERR )return;

	CString strSql,str1;
	c_getKf.GetLBText(c_getKf.GetCurSel(),str1);

	try{
		strSql.Format("select NVL(KFBM,'FFF') as KFBM from STOREROOM where KFMC='%s' ",str1);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			
			m_getKfbm=(char*)_bstr_t(recSet->GetCollect("KFBM"));
					
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}	// TODO: Add extra initialization here
		
}

void CMoveKf::OnKillfocusEditGetRymc() 
{
	CString str1,str2,str3;
	c_getRymc.GetWindowText(str2); //编码
	if( str2 == c_getRymcID ){
		c_getRymc.SetWindowText(c_getRymcName);
		return;
	}
	if( !str2.IsEmpty() ){
		str1.Format(" SELECT NVL(name,' '),rybm FROM operator WHERE rybm='%s' ",str2);
		if( CDialogInStorage::GetName_ID(str1,str2,str3) ){ //分别为SQL,name,id
			c_getRymc.SetWindowText(str2);
			c_getRymcName=str2;
			c_getRymcID=str3;
			return;
		}

	}		// TODO: Add your control notification handler code here
	c_getRymcID="";
	c_getRymcName="";
	c_getRymc.SetWindowText("");
	
}

void CMoveKf::OnSetfocusEditGetRymc() 
{
	if( ! c_getRymcID.IsEmpty() ) c_getRymc.SetWindowText(c_getRymcID);
	
}

void CMoveKf::OnEffiect()  //列出过期药品
{
	
}
