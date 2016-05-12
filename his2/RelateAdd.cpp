// RelateAdd.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "RelateAdd.h"
#include "employeeQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRelateAdd dialog


CRelateAdd::CRelateAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CRelateAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRelateAdd)
	m_date = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"黑体");
}


void CRelateAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRelateAdd)
	DDX_Control(pDX, IDC_EDIT_MONEY, c_money);
	DDX_Control(pDX, IDC_COMBO_TYPE, c_type);
	DDX_Control(pDX, IDC_COMBO_SEX, c_sex);
	DDX_Control(pDX, IDC_EDIT_BM, c_bm);
	DDX_Control(pDX, IDC_EDIT_EMP, c_emp);
	DDX_Control(pDX, IDCANCEL, m_3);
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, IDC_BUTTON1, m_1);
	DDX_Control(pDX, IDC_EDIT_NAME, c_name);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRelateAdd, CDialog)
	//{{AFX_MSG_MAP(CRelateAdd)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, OnDatetimechangeDatetimepicker1)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRelateAdd message handlers

void CRelateAdd::OnButton1() //查找职工姓名
{
	CEmployeeQuery rybm;

	if(rybm.DoModal()==IDOK){
		strEmp=rybm.strKH;
		c_emp.SetWindowText(rybm.strName);
//////////////////////////////////////	生成供养人编码	
		CString str1;
		
		_CommandPtr cmd;
		_ParameterPtr par;
		cmd.CreateInstance(__uuidof( Command ));
		par.CreateInstance(__uuidof( Parameter));
		
		_variant_t vNULL;
		vNULL.vt = VT_ERROR;
		vNULL.scode = DISP_E_PARAMNOTFOUND;
		try{
			cmd->put_CommandType(adCmdStoredProc) ;
			par=cmd->CreateParameter(_bstr_t("bmin"),adVarChar,adParamInput,20,_bstr_t(strEmp));
			cmd->Parameters->Append( par );
			par=cmd->CreateParameter(_bstr_t("bmout"),adVarChar,adParamOutput,20,vNULL);
			cmd->Parameters->Append( par );
			
			cmd->put_CommandText(_bstr_t("PRC_Generic_BM"));
			cmd->ActiveConnection=HospitalConnect;
			cmd->Execute(NULL,NULL,adCmdStoredProc);
			
			str1=(char*)_bstr_t(cmd->Parameters->GetItem("bmout")->Value);
			if ( str1 == "ERROR") {
				c_bm.SetWindowText("");
				AfxMessageBox("生成编码错误,请检查数据库...");
			}
			else {
				c_bm.SetWindowText(str1);
			}
			cmd.Detach();
			par.Detach();
		}
		catch(_com_error e)
		{
			AfxMessageBox(e.ErrorMessage());
			return;
		}
////////////////////////////////////////////
	}
	else {
		strEmp="";
		c_bm.SetWindowText("");
		c_emp.SetWindowText("");
	}
	
}

void CRelateAdd::OnOK() 
{
	UpdateData();
	CString strSql,strTmp1,strTmp2,s1,s2,s3;
	c_bm.GetWindowText(strTmp1);
	c_name.GetWindowText(strTmp2);

	if( strTmp1.IsEmpty() || strEmp.IsEmpty() || strTmp2.IsEmpty() || c_sex.GetCurSel() == CB_ERR || c_type.GetCurSel() == CB_ERR )
	{
		AfxMessageBox("请将所有信息填写完整再点击确定!!!");
		return;
	}
	c_sex.GetLBText(c_sex.GetCurSel(),s1);
	c_type.GetLBText(c_type.GetCurSel(),s2);
	c_money.GetWindowText(s3); //余额
	try{
		strSql.Format("INSERT INTO codeQingShu (bm,xm,xb,csriqi,xingzhi,kahao,yuer) values('%s',\
			'%s','%s',to_date(%s,'yyyymmdd'),'%s','%s',%.2f ) ",strTmp1,strTmp2,s1,m_date.Format("%Y%m%d"),s2,strEmp,atof(s3) );
		HospitalConnect->BeginTrans();
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
	
		strSql.Format("INSERT INTO LSQ_REMAIN_RELATE ( ds1,d1,n1,n2) VALUES('%s',TRUNC(sysdate,'yy'),0,%.2f ) ",\
			strTmp1,atof(s3) );
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();

	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		AfxMessageBox(strSql);
		HospitalConnect->RollbackTrans();
		return;
	}

	AfxMessageBox("当前供养亲属成功加入!!!");
	c_name.SetWindowText("");
	c_type.SetCurSel(CB_ERR);
	c_sex.SetCurSel(CB_ERR);
	c_bm.SetWindowText("");
	c_emp.SetWindowText("");
	c_money.SetWindowText("");
	m_date=COleDateTime::GetCurrentTime();
	UpdateData(false);

	
}

void CRelateAdd::ComputeCash() //计算当前新增用户的生成金额
{
	const int DOUBLE_FAMILY=0;
	const int DOUBLE_AGE=14;
	const float DB_CASH=300.00;
	const float SG_CASH=150.00;
	CString strTmp;
	UpdateData();
	int age=COleDateTime::GetCurrentTime().GetYear() - m_date.GetYear() ;

	if( c_type.GetCurSel() == DOUBLE_FAMILY && age <= DOUBLE_AGE )
	{
		strTmp.Format("%.2f",DB_CASH);
	}
	else{

		strTmp.Format("%.2f",SG_CASH);
	}
	c_money.SetWindowText(strTmp);


}

void CRelateAdd::OnSelchangeComboType() 
{
	ComputeCash();	
}

void CRelateAdd::OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	ComputeCash();	
//	*pResult = 0;
}

BOOL CRelateAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_HEAD)->SetFont(&fontTitle);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CRelateAdd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if( pWnd->m_hWnd == c_bm.m_hWnd || pWnd->m_hWnd == c_money.m_hWnd 
		|| pWnd->m_hWnd == GetDlgItem(IDC_STATIC_HEAD)->m_hWnd )
		pDC->SetTextColor(RGB(255,0,0));
		
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
