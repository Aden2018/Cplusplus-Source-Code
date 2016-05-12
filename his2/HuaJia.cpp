// HuaJia.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "HuaJia.h"
#include "queryRybm.h"
#include "medStockList.h" 
#include "cureList.h"
#include "paymedFee.h"
#include "MedCodeQuery.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHuaJia dialog


CHuaJia::CHuaJia(CWnd* pParent /*=NULL*/)
	: CDialog(CHuaJia::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHuaJia)
	//}}AFX_DATA_INIT
	fontSmall.CreatePointFont(100,"宋体");
}


void CHuaJia::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHuaJia)
	DDX_Control(pDX, IDBUTTON_PRINT, m_223);
	DDX_Control(pDX, IDBUTTON_ROLLMED, c_rollmedbutton);
	DDX_Control(pDX, IDC_EDIT_X7, x7);
	DDX_Control(pDX, IDC_EDIT_X6, x6);
	DDX_Control(pDX, IDC_EDIT_X5, x5);
	DDX_Control(pDX, IDC_EDIT_X4, x4);
	DDX_Control(pDX, IDC_EDIT_X3, x3);
	DDX_Control(pDX, IDC_EDIT_X2, x2);
	DDX_Control(pDX, IDC_EDIT_X1, x1);
	DDX_Control(pDX, IDC_EDIT_MEDNAME, c_medname);
	DDX_Control(pDX, IDC_EDIT_MEDGG, c_medgg);
	DDX_Control(pDX, IDC_EDIT_MED_NUM, c_mednum);
	DDX_Control(pDX, IDBUTTON_CHARGE_PRICE, m_xx);
	DDX_Control(pDX, IDC_EDIT_TYPE, c_type);
	DDX_Control(pDX, IDC_EDIT_SICK, c_sick);
	DDX_Control(pDX, IDC_EDIT_DOCTOR, c_doctor);
	DDX_Control(pDX, IDC_EDIT_DANJUHAO, c_danjuhao);
	DDX_Control(pDX, IDC_BUTTON_DOCTOR, m_34);
	DDX_Control(pDX, IDOK, m_3);
	DDX_Control(pDX, IDCANCEL, m_2);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	DDX_Control(pDX, IDC_MSHFLEXGRID2, m_grid2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHuaJia, CDialog)
	//{{AFX_MSG_MAP(CHuaJia)
	ON_BN_CLICKED(IDC_BUTTON_DOCTOR, OnButtonDoctor)
	ON_EN_KILLFOCUS(IDC_EDIT_DOCTOR, OnKillfocusEditDoctor)
	ON_EN_SETFOCUS(IDC_EDIT_DOCTOR, OnSetfocusEditDoctor)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDBUTTON_CHARGE_PRICE, OnChargePrice)
	ON_EN_KILLFOCUS(IDC_EDIT_MED_NUM, OnKillfocusEditMedNum)
	ON_EN_SETFOCUS(IDC_EDIT_MED_NUM, OnSetfocusEditMedNum)
	ON_EN_CHANGE(IDC_EDIT_X1, OnChangeEditX1)
	ON_BN_CLICKED(IDBUTTON_ROLLMED, OnRollmed)
	ON_BN_CLICKED(IDBUTTON_PRINT, OnPrint)
	ON_EN_CHANGE(IDC_EDIT_X8, OnChangeEditX8)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT_X9, OnChangeEditX9)
	ON_EN_CHANGE(IDC_EDIT_X5, OnChangeEditX5)
	//}}AFX_MSG_MAP
	ON_EN_KILLFOCUS(T_EDIT_HUAJIA,OnKillEditCtrl)
	ON_EN_KILLFOCUS(T_EDIT_CURE,OnKillEdit2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHuaJia message handlers

BOOL CHuaJia::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	CString HeadTitle[]={"序号","姓名","BM","挂号类型","日期","序列号"};
// 							0     1	     2       3        4       5
const int SCALE1= 55 ; //直系亲属为 55%,独生子女为单职工的也为 55%
const int SCALE2= 20 ; //独生子女为双职工的 20%

	c_sick.SetWindowText(str2[1]);
	c_type.SetWindowText(str2[3]);
	c_danjuhao.SetWindowText(str2[5]);
	GetDlgItem(IDC_EDIT_COUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_COUNT)->SetWindowText("");
	GetDlgItem(IDC_EDIT_GH_HUAJIA)->SetWindowText("挂号: "+strGhHuajia[0] );
	CString strSql,s1,s2;
	x4.SetWindowText("100%");
	scale=1; //费用自付,默认
	balance=0;
	GetDlgItem(IDOK)->EnableWindow(false); //禁用OK按钮

	try{
		if(str2[3] == "补充保险"){
			
		//	GetDlgItem(IDC_STATIC_PRICE)->ShowWindow(SW_SHOW);
		//	GetDlgItem(IDC_STATIC_PRICE2)->ShowWindow(SW_SHOW);

			strSql.Format("select * from 职工基本情况表 where 卡号 = '%s' ",str2[2]);
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){
				s1=(char*)_bstr_t(recSet->GetCollect("结存金额").vt == VT_NULL? "0":recSet->GetCollect("结存金额"));
				balance=atof(s1);
				s2.Format(" %s : %s ","帐户余额为",s1);
				x1.SetWindowText(s1);
			}
			recSet->Close();
		}
		else if(str2[3] == "供养亲属"){
			strSql.Format("select NVL(xm,' ') as xm,NVL(xb,' ') as xb,NVL(xingzhi,' ') as xz,\
				NVL(姓名,' ') as name ,NVL(yuer,'0') as yuer from codeQingShu a,职工基本情况表 b  where 卡号=KAHAO and BM = '%s' ",str2[2]);
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){

				GetDlgItem(IDC_STATIC_PRICE)->ShowWindow(SW_SHOW);

				s1=(char*)_bstr_t(recSet->GetCollect("name"));
				s2.Format("供养人:%s",s1);

				s1=(char*)_bstr_t(recSet->GetCollect("yuer"));
				x1.SetWindowText(s1);
				balance=atof(s1);

				s1=(char*)_bstr_t(recSet->GetCollect("xz"));
				s2+="     "+s1;
				GetDlgItem(IDC_STATIC_PRICE)->SetWindowText(s2);
			

			}

			recSet->Close();

		}
		else if(str2[3]=="特定门诊" || str2[3]=="基本保险" || str2[3] == "居民统筹" || str2[3]=="家庭病床" )
		{
			if(str2[3]=="特定门诊" ){
			
				GetDlgItem(IDC_STATIC_X1)->SetWindowText("统筹支付");
	
				GetDlgItem(IDC_STATIC_X8)->SetWindowText("国前工人");
				GetDlgItem(IDC_STATIC_X9)->SetWindowText("公务员补");
				GetDlgItem(IDC_STATIC_X5)->SetWindowText("IC卡支付");
			
				GetDlgItem(IDC_EDIT_X8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_EDIT_X9)->ShowWindow(SW_SHOW);
				((CEdit*)GetDlgItem(IDC_EDIT_X9))->SetReadOnly(false);
				((CEdit*)GetDlgItem(IDC_EDIT_X5))->SetReadOnly(false);
				GetDlgItem(IDC_STATIC_X8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_X9)->ShowWindow(SW_SHOW);
			
				GetDlgItem(IDC_STATIC_X8)->SetFont(&fontSmall);
				GetDlgItem(IDC_STATIC_X9)->SetFont(&fontSmall);
				GetDlgItem(IDC_STATIC_X5)->SetFont(&fontSmall);
			
			}
			else
			{
				GetDlgItem(IDC_STATIC_X1)->SetWindowText("IC卡支付");
				GetDlgItem(IDC_STATIC_X5)->SetWindowText("基本合计");
			}
			GetDlgItem(IDC_STATIC_X6)->SetWindowText("现金支付");
			x1.SetReadOnly(false);
			CRect rt1,rt2;
			GetDlgItem(IDC_STATIC_X5)->GetWindowRect(rt1);
			ScreenToClient(rt1);
			GetDlgItem(IDC_STATIC_X6)->GetWindowRect(rt2);
			ScreenToClient(rt2);
			GetDlgItem(IDC_STATIC_X5)->MoveWindow(rt2);
			GetDlgItem(IDC_STATIC_X6)->MoveWindow(rt1);
		
			GetDlgItem(IDC_EDIT_X5)->GetWindowRect(rt1);
			ScreenToClient(rt1);
			GetDlgItem(IDC_EDIT_X6)->GetWindowRect(rt2);
			ScreenToClient(rt2);
			GetDlgItem(IDC_EDIT_X5)->MoveWindow(rt2);
			GetDlgItem(IDC_EDIT_X6)->MoveWindow(rt1);

		}
		else if( str2[3] == "住院人员" ){
			strSql.Format("SELECT price FROM lsq_reside_hos WHERE serial  = '%s' ",str2[5]);
			balance=atof(COtherDecharge::GetStringTitle(strSql) );
			s2.Format("%.2f",balance);
			x1.SetWindowText(s2);
		}
		else
		{
			GetDlgItem(IDC_STATIC_X1)->SetWindowText("现  金");
			x1.SetReadOnly(false);
		}
		
	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox(strSql);
		return false;
	}

//	fontTitle.CreatePointFont(220,"宋体");
//	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	fontMoveEdit.CreatePointFont(120,"宋体");

	CRect r1(0,0,0,0);
	editCtrl.Create(WS_CHILD,r1,this,T_EDIT_HUAJIA);
	editCtrl.SetFont(&fontMoveEdit);
	edit2.Create(WS_CHILD,r1,this,T_EDIT_CURE);
	edit2.SetFont(&fontMoveEdit);

	SetGridHead();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHuaJia::OnButtonDoctor() 
{
	CQueryRybm rybm;
	if(rybm.DoModal()==IDOK){
		m_strDoctorBm=rybm.strNum;
		c_doctor.SetWindowText(rybm.strName);

	}
}

void CHuaJia::OnKillfocusEditDoctor() 
{
	CString str1,strSql;
	c_doctor.GetWindowText(str1);
	if(str1.IsEmpty()){
	//	c_doctor.SetFocus();
		return;
	}
	try{
		strSql.Format("select NVL(name,' ') NAME from operator where rybm='%s' ",str1);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			m_strDoctorBm=str1;
			c_doctor.SetWindowText((char*)_bstr_t(recSet->GetCollect("NAME")));
		}
		else {
			m_strDoctorBm="";
			c_doctor.SetWindowText("");
			c_doctor.SetFocus();
		}
		recSet->Close();


	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox(strSql);
		return;
	}
}

void CHuaJia::OnSetfocusEditDoctor() 
{
	c_doctor.SetWindowText(m_strDoctorBm);	
}

void CHuaJia::OnOK()  //药品保存
{
	CString str1,strSql,str_onok[20];
	long row=0,x(0),y(0);
	double medMoney(0.0),zlMoney(0.0),profit(0.0);
	UpdateData();
	if(m_strDoctorBm.IsEmpty() ){
		AfxMessageBox("请选择治疗医生...");
		c_doctor.SetFocus();
		return;
	}
	c_type.GetWindowText(str1);
	c_doctor.GetWindowText(str_onok[0]); //医生名
	c_danjuhao.GetWindowText(str_onok[1]);//单据号
	try{
		HospitalConnect->BeginTrans();
	/*	离休人员是10/21日晚上刚刚注释掉的,因为现在收费,划价放在一起,所以全部以一种方式来

		if(str1 == "离休人员"){ //直接从帐户中扣除,注意费用

			for(row=1;row<m_grid.GetRows()-1; row++)
			{
				str[2]=m_grid.GetTextMatrix(row,0);//ID
				str[3]=m_grid.GetTextMatrix(row,10);//售价
				str[4]=m_grid.GetTextMatrix(row,13);//取药数
				str[5]=m_grid.GetTextMatrix(row,1);//ypbm
				str[6]=m_grid.GetTextMatrix(row,5);//product date
				str[7]=m_grid.GetTextMatrix(row,6);//effiect date
				str[8]=m_grid.GetTextMatrix(row,8);//产地
				str[9]=m_grid.GetTextMatrix(row,11);//进价
		
				strSql.Format("insert into ITEMTI (ID,SL,DJ,RIQI,DANJUHAO,KFBM,YPBM,\
					RQ1,RQ2,factory) values(%s,%.2f,%.2f,to_date('%s','yyyy-mm-dd'),'%s','%s',\
					'%s',to_date('%s','yyyy-mm-dd'),to_date('%s','yyyy-mm-dd'),'%s' )",\
					str[2],atof(str[4]),atof(str[3]),str2[4] ,str[1],LoginInformation.kfbm,str[5],\
					str[6],str[7] ,str[8]);
				medMoney+=atof(str[4])*atof(str[3]);//销售价格
				
				profit+=atof(str[9])*atof(str[4]);//进货价
			
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			}
		
			for(row=1;row<m_grid2.GetRows()-1;row++)
			{
				str[2]=m_grid2.GetTextMatrix(row,0);//iD
				str[3]=m_grid2.GetTextMatrix(row,2);//dj
				
				strSql.Format("insert into ItemRegisterTiZL (ZLMC,dj,danjuhao ) values(\
					'%s',%.2f,'%s' )",str[2],atof(str[3]),str[1]);
				zlMoney+=atof(str[3]);
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);


			}

			strSql.Format("update ITEMREGISTERTOU set DOCTOR='%s' ,DOCTORNAME='%s',\
				划价员='%s',划价员名='%s',KFBM='%s',收费员='%s',收费员名='%s', \
				profit=%.2f,MedMoney=%.2f,treateMoney=%.2f where DANJUHAO='%s' ",m_strDoctorBm,\
				str[0],LoginInformation.user_code,LoginInformation.user,LoginInformation.kfbm,\
				LoginInformation.user_code,LoginInformation.user,\
				medMoney-profit,medMoney,zlMoney,str[1]);
			
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
	
			
			
			
			
			
		}
		else {
	*/	
	
	
	//ITEMTI 中的 DJ 在划价中 是药品零售价,PDJ 是进货价, SELLDJ 是国家标准批发价
		strSql.Format("update ITEMREGISTERTOU set DOCTOR='%s' ,DOCTORNAME='%s',\
				划价员='%s',划价员名='%s',KFBM='%s' where DANJUHAO='%s' ",m_strDoctorBm,\
				str_onok[0],LoginInformation.user_code,LoginInformation.user,LoginInformation.kfbm,\
				str_onok[1]);
			
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
/*			{"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","售价","进价","指导价","取药数"}; //共14列
*/
		for(row=1;row<m_grid.GetRows()-1; row++)
		{
				str_onok[2]=m_grid.GetTextMatrix(row,0);//ID
				str_onok[3]=m_grid.GetTextMatrix(row,10);//售价
				str_onok[4]=m_grid.GetTextMatrix(row,13);//取药数
				str_onok[5]=m_grid.GetTextMatrix(row,1);//ypbm
				str_onok[6]=m_grid.GetTextMatrix(row,5);//product date
				str_onok[7]=m_grid.GetTextMatrix(row,6);//effiect date
				str_onok[8]=m_grid.GetTextMatrix(row,8);//产地
		
				strSql.Format("insert into ITEMTI (ID,SL,DJ,RIQI,DANJUHAO,KFBM,YPBM,\
					RQ1,RQ2,factory,PDJ,SELLDJ) values(%s,%.2f,%.2f,to_date('%s','yyyy-mm-dd'),'%s','%s',\
					'%s',to_date('%s','yyyy-mm-dd'),to_date('%s','yyyy-mm-dd'),'%s' ,%.2f,%.2f)",\
					str_onok[2],atof(str_onok[4]),atof(str_onok[3]),str2[4] ,str_onok[1],LoginInformation.kfbm,str_onok[5],\
					str_onok[6],str_onok[7] ,str_onok[8],atof(m_grid.GetTextMatrix(row,11)),atof(m_grid.GetTextMatrix(row,12)));
			 //在挂号划价中 PDJ 为购进价 SELLDJ 为指导价
			//在其它转为时 SELLDJ 为进价,PDJ 为指导价
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			}
		
			for(row=1;row<m_grid2.GetRows()-1;row++)
			{
				str_onok[2]=m_grid2.GetTextMatrix(row,0);//iD
				str_onok[3]=m_grid2.GetTextMatrix(row,2);//dj
				
				strSql.Format("insert into ItemRegisterTiZL (ZLMC,dj,danjuhao ) values(\
					'%s',%.2f,'%s' )",str_onok[2],atof(str_onok[3]),str_onok[1]);
				
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);


			}


//		}
		
		HospitalConnect->CommitTrans();
	
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		AfxMessageBox("保存药品出错...");
		HospitalConnect->RollbackTrans();
		return;
	}
	GetDlgItem(IDOK)->EnableWindow(false);

}

BOOL CHuaJia::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){
		if(GetFocus()->m_hWnd==GetDlgItem(IDC_MSHFLEXGRID1)->m_hWnd){
			OnDblClickMshflexgrid1() ;
			return true;
		}
		else if(GetFocus()->m_hWnd == GetDlgItem(IDC_EDIT_MEDNAME)->m_hWnd){
			CRect r1;
			GetDlgItem(IDC_EDIT_MEDNAME)->GetWindowRect(r1);
		//	ScreenToClient(r1);

			CMedStockList medlist;
			medlist.r1=r1;

			theApp.pParentGrid.pGrid=&m_grid;
			if(medlist.DoModal() == IDOK){
				c_medname.SetWindowText(m_grid.GetTextMatrix(m_grid.GetRows()-2,2));//药品名
				c_medgg.SetWindowText(m_grid.GetTextMatrix(m_grid.GetRows()-2,3));//药品规格

				ComputerFee();
				GetDlgItem(IDC_EDIT_MED_NUM)->SetFocus();
			}

			return true;


		}else if(GetFocus()->m_hWnd == GetDlgItem(IDC_EDIT_MED_NUM)->m_hWnd){
			GetDlgItem(IDC_EDIT_MEDNAME)->SetFocus();			
			return true;

		}

		else if(GetFocus()->m_hWnd == GetDlgItem(IDC_MSHFLEXGRID2)->m_hWnd) {
			OnDblClickMshflexgrid2();
			return true;
		
		}
		else if(GetFocus()->m_hWnd == edit2.m_hWnd ){
		
			CString str1;
			edit2.GetWindowText(str1);
			double	dX=atof(str1);
			str1.Format("%.2f",dX);
			m_grid2.SetTextMatrix(m_grid2.GetRow(),2,str1);
			
			if(m_grid2.GetRow() < m_grid2.GetRows()-2){
				m_grid2.SetRow(m_grid2.GetRow()+1);
				OnClickMshflexgrid2();
					
			}else edit2.ShowWindow(SW_HIDE);
		
			return true;

		


		}
		else if(GetFocus()->m_hWnd == editCtrl.m_hWnd ) {
			CString str1;
			double flSL;
			
			editCtrl.GetWindowText(str1);
			
			flSL=atof(str1);
			
			if(flSL > atof(m_grid.GetTextMatrix(editRow,9))){ //库存数
				
			//	AfxMessageBox("提取的药品数量大于库存量...");
				//	editCtrl.SetFocus();
				editCtrl.SetWindowText("");
				return true ;
			}
			
			str1.Format("%.2f",flSL);
			
			m_grid.SetTextMatrix(editRow,13,str1); //提取数
			
			
			//	editCtrl.SetWindowText("");
			editCtrl.ShowWindow(SW_HIDE);
			
			if(m_grid.GetRow() < m_grid.GetRows()-2){
				m_grid.SetRow(m_grid.GetRow()+1);
				OnClickMshflexgrid1();
					
			}
			return true;
		
			//return CDialog::PreTranslateMessage(pMsg);
		}
		else
		{
			pMsg->wParam=VK_TAB;
			CDialog::PreTranslateMessage(pMsg);
		}
		
		
	}
	if(pMsg->message==WM_RBUTTONUP && GetFocus()->m_hWnd == GetDlgItem(IDC_MSHFLEXGRID1)->m_hWnd )
	{
		if( m_grid.GetRow() >= m_grid.GetRows()-1)return true;
		m_grid.RemoveItem(m_grid.GetRow());
		ComputerFee();
		return true;

	}
	if(pMsg->message==WM_RBUTTONUP && GetFocus()->m_hWnd == GetDlgItem(IDC_MSHFLEXGRID2)->m_hWnd )
	{
		if( m_grid2.GetRow() >= m_grid2.GetRows()-1)return true;
		m_grid2.RemoveItem(m_grid2.GetRow());
		ComputerFee();
		return true;

	}
	/*
	GetNextDlgTabItem(GetFocus())->SetFocus();
	((CEdit*)GetFocus())->SetSel(0,((CEdit*)GetFocus())->LineLength(-1));
	*/
// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}

BEGIN_EVENTSINK_MAP(CHuaJia, CDialog)
    //{{AFX_EVENTSINK_MAP(CHuaJia)
	ON_EVENT(CHuaJia, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CHuaJia, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CHuaJia, IDC_MSHFLEXGRID2, -601 /* DblClick */, OnDblClickMshflexgrid2, VTS_NONE)
	ON_EVENT(CHuaJia, IDC_MSHFLEXGRID2, -600 /* Click */, OnClickMshflexgrid2, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()
void CHuaJia::OnDblClickMshflexgrid1() 
{
/*	CMedStockList medlist;
	theApp.pParentGrid.pGrid=&m_grid;
	medlist.DoModal();
*/
}

void CHuaJia::OnClickMshflexgrid1() 
{
	if(m_grid.GetRow()==m_grid.GetRows()-1 || m_grid.GetCol() != 13)return; //列13为取药数

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

void CHuaJia::OnKillEditCtrl()
{
	CString str1;
	double flSL,price;

	editCtrl.GetWindowText(str1);

	flSL=atof(str1);
	
	if(flSL > atof(m_grid.GetTextMatrix(editRow,9))){ //库存数
	
		AfxMessageBox("提取的药品数量大于库存量...");
		editCtrl.SetWindowText("");
		editCtrl.SetFocus();
		return ;
	}
	price=atof(m_grid.GetTextMatrix(editRow,10) ) ;//零售价

	str1.Format("%.2f",flSL);
	m_grid.SetTextMatrix(editRow,13,str1); //提取数
	str1.Format("%.2f",flSL*price);
	m_grid.SetTextMatrix(editRow,14,str1); //零售额

	editCtrl.SetWindowText("");
	editCtrl.ShowWindow(SW_HIDE);
	m_3.SetFocus();
	ComputerFee();
}

HBRUSH CHuaJia::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor==CTLCOLOR_EDIT)pDC->SetTextColor(RGB(255,0,0));	
	if(pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd){
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return theApp.titleBrush;


	}
	if(pWnd->m_hWnd == GetDlgItem(IDC_STATIC_PRICE)->m_hWnd)pDC->SetTextColor(RGB(255,0,0));
	if( pWnd->m_hWnd == GetDlgItem(IDC_EDIT_GH_HUAJIA)->m_hWnd )
		pDC->SetTextColor(RGB(255,0,0));
	if( pWnd->m_hWnd == GetDlgItem(IDC_EDIT_COUNT)->m_hWnd )
		pDC->SetTextColor(RGB(255,0,0));
	return hbr;
}

void CHuaJia::OnDblClickMshflexgrid2() 
{
	CCureList curelist;
	theApp.pParentGrid.pGrid=&m_grid2;
	curelist.DoModal();
	ComputerFee();
}

void CHuaJia::OnClickMshflexgrid2() 
{
	if(m_grid2.GetRow()==m_grid2.GetRows()-1 || m_grid2.GetCol() != 2)return; //列2为价格
	CDC *pCdcGrid=m_grid2.GetDC();
	int nWidth=pCdcGrid->GetDeviceCaps(LOGPIXELSX);
	int nHigh=pCdcGrid->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pCdcGrid);

	long	row=m_grid2.GetRow();
	long 	col=m_grid2.GetCol();
	CString str2;
	CString	strOrigin=m_grid2.GetTextMatrix(row,col);

	long left=m_grid2.GetCellLeft();
	long top=m_grid2.GetCellTop();
	long right=m_grid2.GetCellWidth();
	long bottom=m_grid2.GetCellHeight();

	CRect rectGrid,r2;
	m_grid2.GetWindowRect(rectGrid);
	ScreenToClient(rectGrid);
	rectGrid.left+=left*nWidth/1440;
	rectGrid.top+=top*nHigh/1440;
	rectGrid.right=right*nWidth/1440+rectGrid.left-1;
	rectGrid.bottom=bottom*nHigh/1440+rectGrid.top-1;


	edit2.MoveWindow(rectGrid);
	edit2.ShowWindow(SW_SHOW);
	edit2.SetFocus();
	edit2.SetWindowText(strOrigin);
	edit2.SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	edit2.SetSel(0,strOrigin.GetLength());	// TODO: Add your control notification handler code here
	
}

void CHuaJia::OnKillEdit2()
{
	CString str1;
	double dX;
	edit2.GetWindowText(str1);
	dX=atof(str1);
	str1.Format("%.2f",dX);
	m_grid2.SetTextMatrix(m_grid2.GetRow(),2,str1);
	m_grid2.SetWindowText("");

	edit2.ShowWindow(SW_HIDE);
	ComputerFee();
}
const char R1[]="供养亲属";
const char RR[]="补充保险";
const char IC[]="基本保险";
const char TUIYANG[]="退养人员";

void CHuaJia::OnChargePrice()  //收费
{
	const int SELL_PRICE_COL=10,GET_PRICE_COL=11,GET_MED_COL=13;
	const int ZL_PRICE_COL=2;

	if(m_strDoctorBm.IsEmpty() ){
		AfxMessageBox("请选择治疗医生!!!!");
		c_doctor.SetFocus();
		return;
	}
	CString str[10];
	for(long row=1;row<m_grid.GetRows()-1; row++)
	{
		str[4]=m_grid.GetTextMatrix(row,13);//取药数
		if ( atof(str[4]) == 0 ){
			str[0].Format("发现第 %ld 行药品取药数量为 零",row );
			AfxMessageBox(str[0]);
			return;
		}
	}

/////////////////////////取代原来的ONOK()调用//////////////////////
//	OnOK();
	
	CString str1,str_onok[20];
	long x(0),y(0);
	double medMoney(0.0),zlMoney(0.0),profit(0.0);
	UpdateData();
	c_type.GetWindowText(str1);
	c_doctor.GetWindowText(str_onok[0]); //医生名
	c_danjuhao.GetWindowText(str_onok[1]);//单据号

/////////////////////取代原来的ONOK()调用/////////////////////////
//	c_type.GetWindowText(str1);

	CString strSql,s1;
	float fMed(0),fZl(0),fPro(0),fMZ,fgetPrice(0);//药品费,治疗费,利润,总费用
	
	x2.GetWindowText(s1);
	fMed=atof(s1);

	
	fgetPrice=fMed-inPrice; //药品利润 

	x3.GetWindowText(s1);
	fZl=atof(s1);

	x5.GetWindowText(s1);
	fMZ=atof(s1);
	CString strx6;
	x6.GetWindowText(strx6); //结余是负还是正
	CString strResideSerial="AB"+COtherDecharge::GetStringTitle("SELECT RPAD(sys_context('USERENV','ip_address'),15,'.')||'.'||to_char(sysdate,'yyyymmddhh24miss')  from dual");
	try{ 
		HospitalConnect->BeginTrans();
//////////////////////////////////insert into onok//////////////////////////////	
	//ITEMTI 中的 DJ 在划价中 是药品零售价,PDJ 是进货价, SELLDJ 是国家标准批发价
		if( str2[3] == "住院人员" ){
			strSql.Format("INSERT INTO lsq_reside_hos_huajia (s1,s2,h1,n1,y1,y2,p1,p2,pr1,r1 ) values \
				('%s','%s','%s','%s','%s','%s',%.2f,%.2f,%.2f,sysdate ) ",str_onok[1],strResideSerial,\
				LoginInformation.user_code,LoginInformation.user,\
				m_strDoctorBm,str_onok[0],fMed,fZl,fgetPrice);
				str_onok[1]=strResideSerial;

		}
		else
			strSql.Format("update ITEMREGISTERTOU set DOCTOR='%s' ,DOCTORNAME='%s',\
				划价员='%s',划价员名='%s',KFBM='%s' where DANJUHAO='%s' ",m_strDoctorBm,\
				str_onok[0],LoginInformation.user_code,LoginInformation.user,LoginInformation.kfbm,\
				str_onok[1]);
			
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
/*			{"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","售价","进价","指导价","取药数"}; //共14列
*/
		for(row=1;row<m_grid.GetRows()-1; row++)
		{
				str_onok[2]=m_grid.GetTextMatrix(row,0);//ID
				str_onok[3]=m_grid.GetTextMatrix(row,10);//售价
				str_onok[4]=m_grid.GetTextMatrix(row,13);//取药数
				str_onok[5]=m_grid.GetTextMatrix(row,1);//ypbm
				str_onok[6]=m_grid.GetTextMatrix(row,5);//product date
				str_onok[7]=m_grid.GetTextMatrix(row,6);//effiect date
				str_onok[8]=m_grid.GetTextMatrix(row,8);//产地
		
				strSql.Format("insert into ITEMTI (ID,SL,DJ,RIQI,DANJUHAO,KFBM,YPBM,\
					RQ1,RQ2,factory,PDJ,SELLDJ) values(%s,%.2f,%.2f,to_date('%s','yyyy-mm-dd'),'%s','%s',\
					'%s',to_date('%s','yyyy-mm-dd'),to_date('%s','yyyy-mm-dd'),'%s' ,%.2f,%.2f)",\
					str_onok[2],atof(str_onok[4]),atof(str_onok[3]),str2[4] ,str_onok[1],LoginInformation.kfbm,str_onok[5],\
					str_onok[6],str_onok[7] ,str_onok[8],atof(m_grid.GetTextMatrix(row,11)),atof(m_grid.GetTextMatrix(row,12)));
			 //在挂号划价中 PDJ 为购进价 SELLDJ 为指导价
			//在其它转为时 SELLDJ 为进价,PDJ 为指导价
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			}
		
			for(row=1;row<m_grid2.GetRows()-1;row++)
			{
				str_onok[2]=m_grid2.GetTextMatrix(row,0);//iD
				str_onok[3]=m_grid2.GetTextMatrix(row,2);//dj
				
				strSql.Format("insert into ItemRegisterTiZL (ZLMC,dj,danjuhao ) values(\
					'%s',%.2f,'%s' )",str_onok[2],atof(str_onok[3]),str_onok[1]);
				
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);


			}

		
//////////////////////////////////insert into onok//////////////////////////////	
		
		
		
		
		if(str2[3] == R1 || str2[3] == RR ){
		
			if(str2[3] == R1 ){ //供养亲属
				if( atof(strx6) <= 0 )strSql.Format("UPDATE codeqingshu SET YUER= 0.0 ,ds1=( SELECT sys_context('USERENV','ip_address')||'.'|| to_char(sysdate,'hh24yyyymimmssdd')||'RELMED' from dual ),d1=sysdate  WHERE BM='%s' ",str2[2] );
				else strSql.Format("UPDATE codeqingshu SET YUER= YUER-(%.2f) ,ds1=( SELECT sys_context('USERENV','ip_address')||'.'|| to_char(sysdate,'hh24yyyymimmssdd')||'RELMED' from dual ),d1=sysdate WHERE BM='%s' ",fMZ,str2[2] );
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			}
			else if( str2[3] == RR ){ //职工补充
				if( atof(strx6) <= 0 )strSql.Format("UPDATE 职工基本情况表 SET 结存金额=0.00,ds1=( SELECT sys_context('USERENV','ip_address')||'.'|| to_char(sysdate,'hh24yyyymimmssdd') ||'EMPMED' from dual ),d1=sysdate WHERE 卡号='%s' ",str2[2] );
				else strSql.Format("UPDATE 职工基本情况表 SET 结存金额=结存金额-(%.2f),ds1=( SELECT sys_context('USERENV','ip_address')||'.'|| to_char(sysdate,'hh24yyyymimmssdd') ||'EMPMED' from dual ),d1=sysdate WHERE 卡号='%s' ",fMZ,str2[2] );
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			}
			
			strSql.Format("UPDATE ItemRegisterTou SET MEDMONEY=%.2f,TREATEMONEY=%.2f,收费员='%s',\
				收费员名='%s',PROFIT=%.2f,cash=%.2f WHERE DANJUHAO='%s' ",fMed,fZl,LoginInformation.user_code,\
				LoginInformation.user ,fgetPrice,atof(strx6)< 0 ? -atof(strx6):0,str2[5] );
		
		}
		else if ( str2[3] == "特定门诊" || str2[3] == IC )
		{
			if( str2[3]== "特定门诊" ) {
				CString s01,s02,s03;
				GetDlgItem(IDC_EDIT_X8)->GetWindowText(s01); // 建国前老工人
				GetDlgItem(IDC_EDIT_X9)->GetWindowText(s02); //公务员补助
				GetDlgItem(IDC_EDIT_X5)->GetWindowText(s03); //IC 卡

		    	strSql.Format("UPDATE ItemRegisterTou SET MEDMONEY=%.2f,TREATEMONEY=%.2f,收费员='%s',\
				收费员名='%s',PROFIT=%.2f,cash=%.2f,p1=%.2f,p2=%.2f,p3=%.2f WHERE DANJUHAO='%s' ",fMed,fZl,LoginInformation.user_code,\
				LoginInformation.user ,fgetPrice,atof(strx6),atof(s01),atof(s02),atof(s03),str2[5] );
				

			}
			else
		    	strSql.Format("UPDATE ItemRegisterTou SET MEDMONEY=%.2f,TREATEMONEY=%.2f,收费员='%s',\
				收费员名='%s',PROFIT=%.2f,cash=%.2f WHERE DANJUHAO='%s' ",fMed,fZl,LoginInformation.user_code,\
				LoginInformation.user ,fgetPrice,atof(strx6),str2[5] );

		}
		else if ( str2[3]== "住院人员" )
		{
			strSql.Format("UPDATE lsq_reside_hos SET price=price-(%.2f) WHERE serial='%s' ",fMZ,str2[5] );


		}
		else
		{

			strSql.Format("UPDATE ItemRegisterTou SET MEDMONEY=%.2f,TREATEMONEY=%.2f,收费员='%s',\
				收费员名='%s',PROFIT=%.2f,CASH=%.2f WHERE DANJUHAO='%s' ",fMed,fZl,LoginInformation.user_code,\
				LoginInformation.user ,fgetPrice,fMZ,str2[5] );


		}
	
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		HospitalConnect->CommitTrans();
		

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		AfxMessageBox("划价收费出错,请重新划价收费!!!");
		HospitalConnect->RollbackTrans();
		return;
	}


	CDialog::OnOK();
}

void CHuaJia::OnKillfocusEditMedNum() //计算是否超出库存量
{
	CString str1,strtemp;
	c_mednum.GetWindowText(str1);
	str1.Format("%.2f",atof(str1));
	long r=0;
	r=m_grid.GetRows();
	double price;
	if(r>2){
		strtemp=m_grid.GetTextMatrix(r-2,9);//库存列
		if( atof(str1) > atof(strtemp) ) {
			AfxMessageBox("输入的药品数量大于库存量!!!请重新输入");
			c_mednum.SetSel(0,c_mednum.LineLength(-1));
			c_mednum.SetFocus();
			return;
		}
		m_grid.SetTextMatrix(r-2,13,str1);

		price=atof(m_grid.GetTextMatrix(r-2,10) );//零售价
		strtemp.Format("%.2f",price*atof(str1) );
		m_grid.SetTextMatrix(r-2,14,strtemp); //零售额

	}
	ComputerFee();

	c_medname.SetWindowText("");
	c_medgg.SetWindowText("");

}

void CHuaJia::OnSetfocusEditMedNum() 
{
		// TODO: Add your control notification handler code here
	c_mednum.SetWindowText("1.00");
	c_mednum.SetSel(0,c_mednum.LineLength(-1));
	
}

const char NOWORK[]="离休人员";
const char GAOQIAN[]="建国前老工人";
const char GANGSHANG[]="工伤人员";
//		if( strGhtype == "国前职工" ) strGhtype="建国前老工人";

void CHuaJia::ComputerFee()
{
	const int SELL_PRICE_COL=10,GET_PRICE_COL=11,GET_MED_COL=13;
	const int ZL_PRICE_COL=2;
	double db1,db2;
	CString str11,str222;
	
	
	float medPrice(0),zlPrice(0);
	theApp.pParentGrid.p3=this; //p2已经由药品列表使用,请不要再使用
	inPrice=0;
	for(int i=1;i<m_grid.GetRows()-1;i++){
		medPrice+=atof(m_grid.GetTextMatrix(i,SELL_PRICE_COL))*atof(m_grid.GetTextMatrix(i,GET_MED_COL));
		inPrice+=atof(m_grid.GetTextMatrix(i,GET_PRICE_COL))*atof(m_grid.GetTextMatrix(i,GET_MED_COL));


	}
	for(i=1;i<m_grid2.GetRows()-1;i++){
		zlPrice+=atof(m_grid2.GetTextMatrix(i,ZL_PRICE_COL));

	}
	
	CString str1,str22,str3,str0;
	str0.Format("%.2f",medPrice);
	str1.Format("%.2f",zlPrice);
	str22.Format("%.2f",medPrice+zlPrice);
			 //药品进价合计,用于计算利润
	
	x2.SetWindowText(str0); //药品费
	x3.SetWindowText(str1); //治疗费
	x7.SetWindowText(str22); //总费用
	if( str2[3]== "特定门诊" ) {
		CString  sx1,sx2,sx3,sx4;
		GetDlgItem(IDC_EDIT_X1)->GetWindowText(sx1); //统筹
		GetDlgItem(IDC_EDIT_X5)->GetWindowText(sx2); //IC
		GetDlgItem(IDC_EDIT_X8)->GetWindowText(sx3); //建国前老工人
		GetDlgItem(IDC_EDIT_X9)->GetWindowText(sx4); //公务员补助
		double dx1;
		dx1=atof(str22) -( atof(sx1)+atof(sx2)+atof(sx3)+atof(sx4) );
		sx1.Format("%.2f",dx1);
		x6.SetWindowText(sx1 ); //现金支付



	goto END;
	}

	if( str2[3] == TUIYANG ) str0.Format("%.2f",(medPrice+zlPrice)*0.1); //退养人员90%折扣
	else if( str2[3] == NOWORK ) str0.Format("%.2f",0);
	else if( str2[3] == GAOQIAN ) str0.Format("%.2f",0);
	else if( str2[3] == GANGSHANG ) str0.Format("%.2f",0);
	else if( str2[3] == IC ) str0.Format("%.2f",medPrice+zlPrice);
	else	str0.Format("%.2f",(medPrice+zlPrice)*scale);

	x5.SetWindowText(str0);//实收费


	if( str2[3] == TUIYANG ) str0.Format("%.2f",balance-(medPrice+zlPrice)*0.1); //退养人员90%折扣
	else if( str2[3] == NOWORK ) str0.Format("%.2f",0);
	else if( str2[3] == GAOQIAN ) str0.Format("%.2f",0);
	else if( str2[3] == GANGSHANG ) str0.Format("%.2f",0);
	else if( str2[3] == IC || str2[3] == "特定门诊" ){

		x5.GetWindowText(str11);//实收费
		x1.GetWindowText(str222);//统支付
		db1=atof(str11);
		db2=atof(str222);
		str0.Format("%.2f",db1-db2 );
		
	}
	else str0.Format("%.2f",balance-(medPrice+zlPrice)*scale);

	x6.SetWindowText(str0);

	if( ( ( balance-(medPrice+zlPrice) ) < 0 && ( str2[3].Compare("补充保险")==0 || str2[3].Compare("供养亲属")==0 ) ) || str2[3]=="特定门诊"   ){
		GetDlgItem(IDC_STATIC_X8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_X9)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_X8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_X9)->ShowWindow(SW_SHOW);

	}
	else{
		GetDlgItem(IDC_STATIC_X8)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_X9)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_X8)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_X9)->ShowWindow(SW_HIDE);

	}
END:
	ComputeRows();
}

void CHuaJia::OnChangeEditX1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString str1;
	x1.GetWindowText(str1);
	balance=atof(str1);
	
	ComputerFee();
}

void CHuaJia::SetGridHead()
{
	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","零售价","进价","指导价","取药数","费用额"}; //共14列+1
	long  headWidth[]={0,00,2000,1600,600,0,1400,0,1600,1000,1000,0,0,1200,1200};


	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	

	m_grid2.SetRows(2);
	m_grid2.Clear();
	CString HeadTitle2[]={"ID","治疗名称","治疗费用"};
	long  headWidth2[]={0,2000,1200,600,0,1400,0,1600,1000,1000,0,0};


	m_grid2.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid2.SetMergeCells(true); //设定单元格可以进行合并
	m_grid2.SetCols(sizeof(HeadTitle2)/sizeof(CString));
	m_grid2.SetFixedCols(0);
	i=0;
	for(count=0;count<sizeof(HeadTitle2)/sizeof(CString);count++){
		m_grid2.SetColWidth(i,headWidth2[count]);
		m_grid2.SetTextArray(i++,HeadTitle2[count]);
	}	
	
}

void CHuaJia::OnRollmed() 
{
	theApp.pParentGrid.pGrid=&m_grid;
	CMedCodeQuery med;
	med.FlagRollMED=8888; //作为退药标志
	med.DoModal();
	
}
//	CString HeadTitle[]={"序号","姓名","BM","挂号类型","日期","序列号"};
extern _Application app;
extern Workbooks books;
extern _Workbook book;
extern Worksheets sheets;
extern _Worksheet sheet;
extern COleVariant vOpt;
void CHuaJia::OnPrint() 
{
#define _O(x) COleVariant(x)

	BeginWaitCursor();

	CString strFileName;
	strFileName.Format("%s",LoginInformation.path);
	strFileName+=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_upgrade WHERE ds2='HUAJIA_PRINT_FILE' ");

	if( str2[3] == "基本保险" || str2[3] == "特定门诊" || str2[3] == "居民统筹" || str2[3]=="家庭病床" ){
		AfxMessageBox("基本保险人员禁止打印");	
		return; //基本保险禁止用户打印
	}

	app.CreateDispatch("excel.application");
	if(!app){
		AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
		return;
	}
	books=app.GetWorkbooks();
	book=books.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	sheets=book.GetWorksheets();

	sheet=sheets.GetItem(_O("MED_Origin_DATA")); //可以指定sheet索引号或sheet名

	
	Range vRange;
	app.SetVisible(false); //显示

//* EXCEL 第一行输入顺序为 药品行数 治疗项目行数 收费员 
	const int START_RECORD=2;
	int iUseCol[]={2,3,4,13,10 };  //*药品要输出的列
	int iUseCol2[]={1,2 };          //* 治疗项目要输出的列
	int y,x;
	int iMedRows=m_grid.GetRows()-2; //药品行数
	int iZlRows=m_grid2.GetRows()-2; //治疗项目行数
	CString strMedtmp;
	CString strInsert[20]; //* 分别按列填入必要的信息
	
	for ( x=0; x< iMedRows  ; x++)    //* 药品原始信息输出
	{
		for(  y=0; y < sizeof(iUseCol) /sizeof(int) ; y++)
		{
			SetExcelCell(sheet,x+START_RECORD,y,m_grid.GetTextMatrix(x+1,iUseCol[y]));
		}
	}

	for ( x=0 ; x < iZlRows; x++ )  //* 治疗费信息输出
	{
		for( y=0 ; y < sizeof(iUseCol2)/ sizeof(int) ; y ++)
		{
			SetExcelCell(sheet,x+START_RECORD+iMedRows,y,m_grid2.GetTextMatrix(x+1,iUseCol2[y]));
	
		}
	}

	x=0;
	strMedtmp.Format("%ld",iMedRows); 
	strInsert[x++]=strMedtmp;				//* 药品行数 0
	strMedtmp.Format("%ld",iZlRows);
	strInsert[x++]=strMedtmp;				//* 治疗行数 1
	strInsert[x++]=str2[1];					//* 病人姓名 2
	strInsert[x++]=LoginInformation.user;	//* 收费员名 3
	strInsert[x++]=str2[3];					//* 人员类别 4   如 社会就诊\补充保险
	c_danjuhao.GetWindowText(strMedtmp);
	strInsert[x++]=strMedtmp;				//* 挂号单据 5
	x7.GetWindowText(strMedtmp);
	strInsert[x++]=strMedtmp;				//* 总金额   6
	strInsert[x++]=GetChinesePrice(strMedtmp); //* 总金额大写 7
	x2.GetWindowText(strMedtmp);
	strInsert[x++]=strMedtmp;				//* 药品费  8
	x3.GetWindowText(strMedtmp);		
	strInsert[x++]=strMedtmp;				//*　治疗费  9
	
//* 基本保险 补充保险 供养亲属 由于帐户金额不足,可能使用现金
//* 社会就诊 完全是现金
//* 离休人员 建国前老工人 工伤人员 无需现金
//* 退养人员 现金为金额的10%
//* 居民统筹　与基本保险应是一样
//* X2 药品费 x1 余额
//* x3 治疗费 x5 实收
//* x7 总费用 x6 找零
//* x8 付款	　x9 找零　　用于帐户余额不够时
	CString strType;
    if(str2[3] == R1 || str2[3] == RR   ){  
		x1.GetWindowText(strMedtmp); // 帐户余额
		if( atof(strMedtmp) <= 0.00) strMedtmp="0.00";
	}
	else if( str2[3] == "社会就诊" ){
		strMedtmp="0.00" ; //总费用即用户现金
	}
	else if( str2[3] == "退养人员" ){
		x1.GetWindowText(strMedtmp); //退养人员
	}
	else 
		strMedtmp="0.00";

	strInsert[x++]=strMedtmp;  //帐户余额 10

    if(str2[3] == R1 || str2[3] == RR   ){  
		x6.GetWindowText(strMedtmp); // 现金,应为负数,即帐户不够支付
		if( atof( strMedtmp) >= 0.00 ) strMedtmp="0.00";
		else {
			strFileName.Format("%.2f",fabs(atof(strMedtmp)) ); //取正数
			strMedtmp=strFileName;
		}
	
	}
	else if( str2[3] == "社会就诊" || str2[3]== "退养人员" ){
		x5.GetWindowText(strMedtmp) ; //总费用即用户现金
	} 
	else strMedtmp="0.00";
	
	strInsert[x++]=strMedtmp;  //现金  11


    if(str2[3] == R1 || str2[3] == RR || str2[3] == "退养人员"  ){  
		x6.GetWindowText(strMedtmp);
		if( atof( strMedtmp ) <=0.00 ) strMedtmp="0.00";
	}else
		strMedtmp="0.00";

	strInsert[x++]=strMedtmp;				//* 本次户余  12

	for ( y=0 ; y < x ; y++)
		SetExcelCell(sheet,1,y,strInsert[y]);  //从EXCEL的第二行第一行开始输出,


/*	
//H54 输入现金收讫
	CString b1;

	/*
	const char R1[]="供养亲属";
const char RR[]="补充保险";
const char IC[]="基本保险";
const char TUIYANG[]="退养人员";

	x6.GetWindowText(b1); //结余是负还是正
	CString strCash;
	vRange=sheet.GetRange(_O("H54"),_O("H54")); //本次户余
	font=vRange.GetFont();
	font.SetName(_O(FONTNAME));
	font.SetSize(_O((short)STANDARDFONT));
	
	if(str2[3] == R1 || str2[3] == RR || str2[3] == IC ){
		if( atof(b1) < 0 ) {
			strCash.Format("现金收讫: %.2f",-atof(b1));
		}
		else{
			strCash.Format("现金收讫: 0.00");
		}
		vRange.SetValue(COleVariant(strCash));

	}
	else {
		x5.GetWindowText(b1);
		strCash.Format("现金收讫: %.2f",atof(b1));
		vRange.SetValue(COleVariant(strCash));

	}

*/	
	app.Run(COleVariant("thisWorkBook.Print_Invoice"),vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
		vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
		vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt );  //调用excel中thisworkbook.print_invoice宏
	
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	app.DetachDispatch();

	EndWaitCursor();
	
}

CString CHuaJia::GetChinesePrice(CString strPrice) //strPrice为标准的二位小数格式,最大到万位  
{
	return GetBigMoney(atof(strPrice) );
/*	CString strPRC[]={"零","壹","贰","叁","肆","伍","陆","柒","捌","玖"};
	CString strBIT[]={"元","拾","佰","仟","万","整"};
	CString str[30];
	char charPre='1';
	int m=0;
	if(strPrice=="0.00")return "零元整";
	CString strInteger,strFloat,strINT="",strFLOAT="",strOut="",str1,str2;

	strInteger=strPrice.Left(strPrice.GetLength()-3); //取整数部分
	strFloat=strPrice.Right(2);//小数部分
	
	if(strInteger[0] == '-'){
		strOut="负";
		strInteger=strInteger.Right(strInteger.GetLength()-1);
	}
//作出整数大写部分
	BOOL flag=0;
	for(int i=0;i<strInteger.GetLength();i++){
		if(strInteger[i]=='0'&&flag==0){
			if(i==strInteger.GetLength()-1){
				strINT+="元";continue;
			}
			flag=1;
			continue;
		}
		if(strInteger[i]=='0'&&strInteger[i-1]=='0')continue;
		if(flag==1)strINT+="零";
		strINT+=strPRC[strInteger[i]-0x30];//取得大写数字
		strINT+=strBIT[strInteger.GetLength()-i-1];//得到大写整称
		flag=0;
	}
	if(flag)strINT+="元";
		
//处理小数部分
	if(strInteger[0]=='0')
	{
		strINT=""; //防止整数为零
		str1="";
	}
	else str1="零";

	if(strFloat=="00"){
		strFLOAT="";
		return strOut+strINT+"整";
	}//小数为零
	if(strFloat[0]=='0'){
		strFLOAT=strPRC[strFloat[1]-0x30]+"分";
		return strOut+strINT+str1+strFLOAT;

	}
	if(strFloat[1]=='0'){
		strFLOAT=strPRC[strFloat[0]-0x30]+"角"+"整";
		if(strInteger[strInteger.GetLength()-1]=='0')
			return strOut+strINT+str1+strFLOAT;
		return strOut+strINT+strFLOAT;
	}
	strFLOAT=strPRC[strFloat[0]-0x30]+"角"+strPRC[strFloat[1]-0x30]+"分";
	if(strInteger[strInteger.GetLength()-1]=='0')
		return strOut+strINT+str1+strFLOAT;
	return strOut+strINT+strFLOAT;
*/

}

void CHuaJia::OnChangeEditX8()  //帐户余额不足时自动计算职工应付款的余额
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if( str2[3]== "特定门诊" ) {
		ComputerFee();
		return;
	}
	CString strx8,strx6;
	double dx8,dx6;
	GetDlgItem(IDC_EDIT_X8)->GetWindowText(strx8);
	GetDlgItem(IDC_EDIT_X6)->GetWindowText(strx6);
	
	dx8=atof(strx8);
	dx6=atof(strx6);
	strx8.Format("%.2f",dx8+dx6); //计算出用户输入的数额减去用户不够付的的(负数)
	GetDlgItem(IDC_EDIT_X9)->SetWindowText(strx8);
}



void CHuaJia::OnDestroy() 
{
	CDialog::OnDestroy();
	CString strSql;
	try{
		HospitalConnect->BeginTrans();
		strSql.Format("DELETE FROM lsq_share WHERE serial='%s' ",str2[5] );
	
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		
		HospitalConnect->CommitTrans();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现系统性错误,请联系系统管理人员...");
		HospitalConnect->RollbackTrans();
		return;
	}
	
}

void CHuaJia::ComputeRows()
{
	CString str1;
	str1.Format("%ld条",m_grid.GetRows()-2 );
	GetDlgItem(IDC_EDIT_COUNT)->SetWindowText(str1);
}

CString CHuaJia::GetBigMoney(double dMoney)
{
     CString strMoney;

     strMoney.Format ("%.2f" , dMoney);

	 if( strMoney.GetLength() >15 ){
		 
		 return "￥"+strMoney; //数值太大
	 }

     CString strUnit = "元拾佰仟万拾佰仟亿拾佰仟";

     CString strNumber = "零壹贰叁肆伍陆柒捌玖";

     CString strOtherUnit = "整角分";

 

     //将数字分整数部份与小数部份处理

     int nPos = strMoney.Find (".");

     int nLength = strMoney.GetLength ();

     if(nPos < 0)

         nPos = nLength;

     CString strReturnValue;

     int nCount = 0;

     bool bZero = false;

     bool bNeedLevel = false;    //对段的识别，用于是否需要出现段名，如亿，万等

     //对整数部份进行反相识别处理

     for(int i = nPos - 1;i >= 0;i --)

     {

         TCHAR ch = strMoney.GetAt (i);

         if(nCount % 4 == 0 && nCount > 0)

         {

               //如果处理的数字为第四位（万），或第八位（亿）等，则要求置段

              bNeedLevel = true;

         }

         if(ch == '0')

         {

               //只对拾佰仟位的０进行识别，主要考虑到拾的特殊性，即如１０读壹拾，不会读壹拾零

              if(nCount % 4 != 0)

                   bZero = true;

         }

         else

         {

              CString strTemp(strReturnValue);

              strReturnValue = strNumber.Mid ((ch - 0x30) * 2 , 2);

              if(nCount > 0)

              {

                  strReturnValue += strUnit.Mid (nCount * 2 , 2);

                   if(nCount % 4 != 0 && bNeedLevel)

                   {

                         //这里判断是否需要读段名，如万，亿等

                       strReturnValue += strUnit.Mid (int(nCount / 4) * 8 , 2);

                   }

                   bNeedLevel = false;

              }

              if(bZero)

              {

                   //只有比当前处理的位要低中有数字才补零

                   if(!strTemp.IsEmpty ())

                       strReturnValue += strNumber.Left (2);

                   bZero = false;

              }

              strReturnValue += strTemp;

         }

         nCount ++;

     }

     strReturnValue += strUnit.Left (2);
	 if(strReturnValue.GetLength()<=2) strReturnValue="";
	 //防止整数部分为零

     bool bAllZero = true;

     //下面实现对小数点后面的处理

     //先判断是否为全零，则不需要继续读

     if(nPos < nLength)

     {

         if(nLength > 2)

              nLength = 2;

         for(int i = 0;i < nLength;i ++)

              if(strMoney.GetAt (nPos + i + 1) != '0')

                   bAllZero = false;

     }

     if(bAllZero)

     {

         strReturnValue += strOtherUnit.Left (2);

     }

     else

     {

          //对分角的处理

         for(int i = 0;i < nLength;i ++)

         {

              TCHAR ch = strMoney.GetAt (nPos + 1 + i);

              if(ch == '0' && i > 0)

              {

              }

              else

              {

                   strReturnValue += strNumber.Mid ((ch - 0x30) * 2 , 2);

                   if(ch != '0')

                       strReturnValue += strOtherUnit.Mid ((i + 1) * 2 , 2);

              }

         }

     }

     return strReturnValue;
}

void CHuaJia::SetExcelCell(_Worksheet &sheetx,int iRow, int iCol, CString &strData)
{
	/* 设置EXCEL单元格字符串 
		sheetx  要操作的工作表
		iRow	要操作工作表所在的行
		iCol	要操作的工作表所在列
		strData 要写入的字符串
	*/
	
	CString strCell;
	Range vRange;
	strCell.Format("%c%d",iCol+'A',iRow+1);
	vRange=sheetx.GetRange(_O(strCell),_O(strCell));
	vRange.SetValue(_O(strData));

}

void CHuaJia::OnChangeEditX9() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if( str2[3]== "特定门诊" ) {
		ComputerFee();
		return;
	}
	
}

void CHuaJia::OnChangeEditX5() 
{
	if( str2[3]== "特定门诊" ) {
		ComputerFee();
		return;
	}
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
