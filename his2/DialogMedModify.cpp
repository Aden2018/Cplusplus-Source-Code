// DialogMedModify.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "DialogMedModify.h"
#include "CodeGysQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogMedModify dialog


CDialogMedModify::CDialogMedModify(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogMedModify::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogMedModify)
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	row=0;
}


void CDialogMedModify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogMedModify)
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, IDCANCEL, m_1);
	DDX_Control(pDX, IDC_EDIT_COACH_PRICE, c_coach);
	DDX_Control(pDX, IDC_EDIT_FACTORY, c_factory);
	DDX_Control(pDX, IDC_EDIT_IN_PRICE, c_InPrice);
	DDX_Control(pDX, IDC_EDIT_PRICE, c_Price);
	DDX_Control(pDX, IDC_EDIT_SL, c_SL);
	DDX_Control(pDX, IDC_EDIT_KF, m_kf);
	DDX_Control(pDX, IDC_EDIT_6, m6);
	DDX_Control(pDX, IDC_EDIT_5, m5);
	DDX_Control(pDX, IDC_EDIT_4, m4);
	DDX_Control(pDX, IDC_EDIT_3, m3);
	DDX_Control(pDX, IDC_EDIT_2, m2);
	DDX_Control(pDX, IDC_EDIT_1, m1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogMedModify, CDialog)
	//{{AFX_MSG_MAP(CDialogMedModify)
	ON_EN_KILLFOCUS(IDC_EDIT_FACTORY, OnKillfocusEditFactory)
	ON_EN_SETFOCUS(IDC_EDIT_FACTORY, OnSetfocusEditFactory)
	ON_BN_CLICKED(IDC_BUTTON_CODEGYS, OnButtonCodegys)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogMedModify message handlers
/* HeadTitle[]={"ID","KFBM","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地","库存量","售价","进价","指导价","大类","小类","库房名"}; //共 16 列
		8		9		10		11		12		13       14
  */
//	CString HeadTitle[]={"ID","FACTORYBM","药品编码","药品名称","规格","单位","生产期","有效期",\
//		"产地","库存量","购进价","零售价","指导价","购进额","零售额","利润","大类","小类","库房名"}; //共 19 列
//         8      9        10         11     12        13         14     15  16     17     18
BOOL CDialogMedModify::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString strTemp;
	pg=(CMSHFlexGrid *)theApp.pParentGrid.pGrid;
	m1.SetWindowText(pg->GetTextMatrix(row,16));
	m2.SetWindowText(pg->GetTextMatrix(row,17));
	m3.SetWindowText(pg->GetTextMatrix(row,2));
	m4.SetWindowText(pg->GetTextMatrix(row,3));
	m5.SetWindowText(pg->GetTextMatrix(row,4));
	m6.SetWindowText(pg->GetTextMatrix(row,5));
	m_kf.SetWindowText(pg->GetTextMatrix(row,18));
//以上为基本信息填写
	c_SL.SetWindowText(pg->GetTextMatrix(row,9));
	c_factory.SetWindowText(factoryMC=pg->GetTextMatrix(row,8));
	c_Price.SetWindowText(pg->GetTextMatrix(row,11));
	c_InPrice.SetWindowText(pg->GetTextMatrix(row,10));
	CString strCoach;
	strCoach.Format("%.2f",atof(pg->GetTextMatrix(row,12))*1.15);
	c_coach.SetWindowText(strCoach);
	strTemp=pg->GetTextMatrix(row,6);
	m_date1.SetDate(atoi(strTemp.Left(4)),atoi(strTemp.Mid(5,2)),atoi(strTemp.Right(2)));
	strTemp=pg->GetTextMatrix(row,7);
	m_date2.SetDate(atoi(strTemp.Left(4)),atoi(strTemp.Mid(5,2)),atoi(strTemp.Right(2)));
	
	MedID=atol(pg->GetTextMatrix(row,0)); //ID
	factoryBM=pg->GetTextMatrix(row,1);//KFBM
	
	UpdateData(false);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogMedModify::OnOK() 
{

	CString strSql,strTemp;
	UpdateData();
	if(factoryBM.IsEmpty()){
		AfxMessageBox("请将产地填写清楚...");
		return;
	}
	double sl,price,inprice,coach;
	c_SL.GetWindowText(strTemp);
	sl=atof(strTemp);
	c_Price.GetWindowText(strTemp);
	price=atof(strTemp);
	c_InPrice.GetWindowText(strTemp);
	inprice=atof(strTemp);
	c_coach.GetWindowText(strTemp);
	coach=atof(strTemp);
	try{
		HospitalConnect->BeginTrans();

		strSql.Format("Insert into LSQ_MED_MODIFY_REC ( ID,KFBM , YPBM , FACTORYCODE,\
		  RQ1 , RQ2 , SL,JINJIA, SELL, COACH , MOD_DATE, N_FACTORYCODE,\
		   N_RQ1 , N_RQ2 , N_SL, N_JINJIA, N_SELL, N_COACH , N_NAME ) (select ID,KFBM,YPBM,\
		   FACTORYCODE,RQ1,RQ2,SL,JINJIA,SELL_PRICE,COACH_PRICE,sysdate,'%s',\
		   to_date('%s','yyyymmdd'),to_date('%s','yyyymmdd'),%.2f,%.2f,%.2f,%.2f/1.15,'%s' FROM \
		   MEDLIE WHERE ID=%ld  ) ",factoryBM,m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d"),\
		   sl,inprice,price,coach,LoginInformation.user,MedID);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
	
		strSql.Format("UPDATE MEDLIE Set factoryCODE='%s',RQ1=to_date('%s','yyyymmdd'),rq2=\
			to_date('%s','yyyymmdd'),sl=%.2f,jinjia=%.2f,sell_price=%.2f,coach_Price=%.2f/1.15 WHERE ID = %ld ",\
			factoryBM,m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d"),sl,inprice,price,coach,MedID);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);


		HospitalConnect->CommitTrans();
/* HeadTitle[]={"ID","KFBM","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地","库存量","售价","进价","指导价","大类","小类","库房名"}; //共 16 列
		8		9		10		11		12		13       14
  */
//	CString HeadTitle[]={"ID","FACTORYBM","药品编码","药品名称","规格","单位","生产期","有效期",\
//		"产地","库存量","购进价","零售价","指导价","购进额","零售额","利润","大类","小类","库房名"}; //共 19 列
//         8      9        10         11     12        13         14     15  16     17     18
		
		pg->SetTextMatrix(row,8,factoryMC);
		strSql.Format("%.2f",sl);
		pg->SetTextMatrix(row,9,strSql);
		strSql.Format("%.2f",price);
		pg->SetTextMatrix(row,11,strSql);
		strSql.Format("%.2f",inprice);
		pg->SetTextMatrix(row,10,strSql);
		strSql.Format("%.2f",coach/1.15);
		pg->SetTextMatrix(row,12,strSql);
		pg->SetTextMatrix(row,6,m_date1.Format("%Y-%m-%d"));
		pg->SetTextMatrix(row,7,m_date2.Format("%Y-%m-%d"));



	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		HospitalConnect->RollbackTrans();
		return;
	}
	AfxMessageBox("修改成功...");
	CDialog::OnOK();

}

void CDialogMedModify::OnKillfocusEditFactory() 
{
//	c_factory.SetWindowText(factoryMC);
	CString strSql,str1;
	c_factory.GetWindowText(str1);
	if(str1 == factoryBM){
		c_factory.SetWindowText(factoryMC);	
		return;
	}

	try{
		strSql.Format("select GONGMC from CODEGYS where GONGBM = '%s' ",str1);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			factoryBM=str1;
			factoryMC=(char*)_bstr_t(recSet->GetCollect("GONGMC").vt==VT_NULL?" ":recSet->GetCollect("GONGMC"));
//			AfxMessageBox(factoryMC);
			c_factory.SetWindowText(factoryMC);
		}
		else {
			factoryBM="";
			factoryMC="";
			c_factory.SetWindowText(factoryMC);
			c_factory.SetFocus();

		}
		recSet->Close();


	}
	catch(_com_error e)
	{
		AfxMessageBox("输入有误,请重新进行正确输入...");
		recSet->Close();
		return;
	}	
}

void CDialogMedModify::OnSetfocusEditFactory() 
{
	c_factory.SetWindowText(factoryBM);
	
}

BOOL CDialogMedModify::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){
		if(GetDlgItem(IDOK)->m_hWnd != GetFocus()->m_hWnd )pMsg->wParam=VK_TAB;

	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDialogMedModify::OnButtonCodegys() 
{
	CCodeGysQuery gys;
	if(gys.DoModal()==IDOK){
		c_factory.SetWindowText(factoryMC=gys.strName);
		factoryBM=gys.strNum;
	
	}
	// TODO: Add your control notification handler code here
	
}
