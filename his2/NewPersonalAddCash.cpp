// NewPersonalAddCash.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "NewPersonalAddCash.h"
#include "employeeQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewPersonalAddCash dialog


CNewPersonalAddCash::CNewPersonalAddCash(CWnd* pParent /*=NULL*/)
	: CDialog(CNewPersonalAddCash::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewPersonalAddCash)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_upgrade WHERE ds2='NEWADDCASH' ");
	fontTitle.CreatePointFont(200,"宋体");
	strKH="";
	dbScale=0.;
}


void CNewPersonalAddCash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewPersonalAddCash)
	DDX_Control(pDX, IDC_EDIT_CASH, c_cash);
	DDX_Control(pDX, IDC_EDIT_NEWCASH, c_NewCash);
	DDX_Control(pDX, IDC_EDIT_KH, c_kh);
	DDX_Control(pDX, IDC_EDIT_INFORMATION, c_infor);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, cAccount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewPersonalAddCash, CDialog)
	//{{AFX_MSG_MAP(CNewPersonalAddCash)
	ON_BN_CLICKED(IDC_BUTTON_EMP, OnButtonEmp)
	ON_EN_CHANGE(IDC_EDIT_NEWCASH, OnChangeEditNewcash)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewPersonalAddCash message handlers

BOOL CNewPersonalAddCash::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	SetWindowText(strTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewPersonalAddCash::OnButtonEmp() 
{
//	CString HeadTitle[]={"所属部","卡号","姓名","性别","出生日期","工作日期",\
		"结存金额","工作性质","类别","pass"},str1;
	CEmployeeQuery rybm;
	rybm.p=NULL;
	if(rybm.DoModal()==IDOK){
		for(int i=0; i< 20; i++ )
			strInfor[i]=rybm.lineInfor[i] ;
		WriteInformation();
	}
	
}

BOOL CNewPersonalAddCash::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN )
	{
		if(pMsg->wParam == VK_RETURN ){
			CString strSql;
			c_kh.GetWindowText(strKH);
			strSql.Format("SELECT 所属部,卡号,姓名,性别,出生日期,工作日期,\
		结存金额,工作性质,类别 FROM 职工基本情况表 a,厂部门表 b WHERE a.部门编码=b.部门编码 \
		AND 卡号='%s' ",strKH);
	
			
			if( !GetEmpInformation(strInfor,strSql) ){
				AfxMessageBox("没有找到此人信息");
			}
			WriteInformation();
			
			return true;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CNewPersonalAddCash::GetEmpInformation(CString *a, CString strSql)
{
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		long cols=recSet->GetFields()->Count,i;
		for(i=0; i< cols ;i++)
			a[i]="";
		if(!recSet->adoEOF){
			for( i=0; i< cols ;i++)
				a[i]=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt== VT_NULL? "":recSet->GetFields()->GetItem(i)->Value );
			
			recSet->Close();
		}else
		{
			recSet->Close();
			return false;
		}
					
	}
	catch(_com_error e)
	{
		recSet->Close();
		return false;
	}
	return true;
}

void CNewPersonalAddCash::WriteInformation()
{
	CString strTmp1,strTmp2,strTmp3;
	strKH=strInfor[1];
	c_kh.SetWindowText(strKH);
	strTmp1.Format("\r\n部门: %s, 卡号: %s, 姓名: %s",strInfor[0],strInfor[1],strInfor[2] );
	strTmp2.Format("\r\n\r\n出生日期: %s, 工作日期: %s,结存金额: %s ",strInfor[4],strInfor[5],strInfor[6] );
	strTmp1+=strTmp2;
	strTmp2.Format("\r\n\r\n工作性质: %s, 类别: %s",strInfor[7],strInfor[8] );
	strTmp1+=strTmp2;
	cAccount.SetWindowText(strInfor[6]);
	long age=COleDateTime::GetCurrentTime().GetYear()-atol(strInfor[4].Left(4));

	strTmp2.Format(" SELECT n1 FROM lsq_gh_type WHERE ds3='C' AND ds2='%s' AND %d >=n2 \
			AND %d <= n3 ",strInfor[7],	age,age);
	
	dbScale=atof( COtherDecharge::GetStringTitle(strTmp2) );
	strTmp2.Format("%.2f%%,年龄: %d ",dbScale*100,age);
		
	strTmp1+="\r\n\r\n充值比例: "+strTmp2;
	c_infor.SetWindowText(strTmp1);

	c_NewCash.SetFocus();

}

void CNewPersonalAddCash::OnOK() //手工人员充值
{
	if( strInfor[1].IsEmpty() ) {
		AfxMessageBox("请先选择要充值的人员!!!");
		return;
	}
	CString strSql,strTmp1,strTmp2;
	
	c_cash.GetWindowText(strTmp1);
	double dbCash=atof(strTmp1);
	c_NewCash.GetWindowText(strTmp1);
	double dbWage=atof(strTmp1);

	try{
		HospitalConnect->BeginTrans();
		//卡号,操作人,性质,充入,工资,比例,年度,日期,结存
		strSql.Format("INSERT INTO lsq_emp_charge (ds1,ds2,ds3,n1,n2,n3,n4,d1,n5) \
			Values('%s','%s','%s',%.2f,%.2f,%.4f,to_char(sysdate,'yyyy'),sysdate,%.2f ) ",\
			strInfor[1],LoginInformation.user,strInfor[7],dbCash,dbWage,dbScale,atof(strInfor[6]) );
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText );

		strSql.Format("UPDATE 职工基本情况表 SET 结存金额=结存金额+(%.2f) WHERE 卡号='%s' ",dbCash,strInfor[1] );
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		HospitalConnect->CommitTrans();

		for(int i=0; i< 20; i++)
			strInfor[i]="";
		WriteInformation();
		c_kh.SetFocus();
		c_cash.SetWindowText("");
		c_NewCash.SetWindowText("");
		AfxMessageBox("新增人员充值成功");


	}
	catch(_com_error e)
	{
		AfxMessageBox("充值失败!!请重新充值!!");
		HospitalConnect->RollbackTrans();

		return;
	}
}

void CNewPersonalAddCash::OnChangeEditNewcash() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if( strInfor[1].IsEmpty() ) return;
	CString strTemp;
	double dbWage;
	c_NewCash.GetWindowText(strTemp);
	dbWage=atof(strTemp);
	strTemp.Format("%.2f",dbWage*dbScale);
	c_cash.SetWindowText(strTemp);
}

HBRUSH CNewPersonalAddCash::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if( c_infor.m_hWnd == pWnd->m_hWnd || c_cash.m_hWnd == pWnd->m_hWnd )
		pDC->SetTextColor(RGB(255,0,0));
		
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
