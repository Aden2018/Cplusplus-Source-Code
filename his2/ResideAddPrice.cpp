// ResideAddPrice.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "ResideAddPrice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResideAddPrice dialog


CResideAddPrice::CResideAddPrice(CWnd* pParent /*=NULL*/)
	: CDialog(CResideAddPrice::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResideAddPrice)
	m_dbPrice = 0.0;
	//}}AFX_DATA_INIT
	strTitle="住院人员补交住院款";
}


void CResideAddPrice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResideAddPrice)
	DDX_Control(pDX, IDCANCEL, m_3);
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, IDOK2, m_1);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_dbPrice);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResideAddPrice, CDialog)
	//{{AFX_MSG_MAP(CResideAddPrice)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResideAddPrice message handlers

BOOL CResideAddPrice::OnInitDialog() 
{
//	CString HeadTitle[]={"序号","s1","姓名","性别","年龄","电话","工作单位","家庭住址","病情描述","医生",\
		"日期","床位","住院金余额","登记员"}; //共 24 列
	CDialog::OnInitDialog();

	SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&CHis2App::fontTitle);

	m_curRow=pGrid->GetRow(); //所中的行
	m_strSerial=pGrid->GetTextMatrix(m_curRow,1); //病人序列号
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(pGrid->GetTextMatrix(m_curRow,2) ); //姓名
	GetDlgItem(IDC_STATIC_DATE)->SetWindowText(pGrid->GetTextMatrix(m_curRow,10) ); //住院日期
	GetDlgItem(IDC_STATIC_ADDR)->SetWindowText(pGrid->GetTextMatrix(m_curRow,7) ); //地址
	GetDlgItem(IDC_STATIC_WORK)->SetWindowText(pGrid->GetTextMatrix(m_curRow,6) ); //工作单位
	GetDlgItem(IDC_STATIC_DESC)->SetWindowText(pGrid->GetTextMatrix(m_curRow,8) ); //病情描述
	
	m_strFmt.Format("SELECT NVL(SUM(p1+p2),0) FROM lsq_reside_hos_huajia_complete  WHERE  s1='%s'  ",m_strSerial);
	CString strUsedPrice=COtherDecharge::GetStringTitle( m_strFmt);
    strUsedPrice+=  "/" +pGrid->GetTextMatrix(m_curRow,12) ;
	GetDlgItem(IDC_STATIC_BALANCE)->SetWindowText(strUsedPrice);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CResideAddPrice::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if( nCtlColor == CTLCOLOR_STATIC  )
		pDC->SetTextColor(RGB(255,0,0));	
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CResideAddPrice::OnOK()  // 交款
{
	UpdateData();

	_CommandPtr cmd;
	_ParameterPtr par;
	cmd.CreateInstance(__uuidof( Command ));
	par.CreateInstance(__uuidof( Parameter));

	_variant_t vNULL;
	vNULL.vt = VT_ERROR;
	vNULL.scode = DISP_E_PARAMNOTFOUND;
	int succ=0;
	try{
		cmd->put_CommandType(adCmdStoredProc) ;
	
		par=cmd->CreateParameter(_bstr_t("succ"),adInteger,adParamOutput,0,vNULL);
		cmd->Parameters->Append( par ); //成功标志
		par=cmd->CreateParameter(_bstr_t("price"),adDouble,adParamInput,sizeof(double),_bstr_t(m_dbPrice));
		cmd->Parameters->Append(par ); //充值金额
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(m_strSerial),_bstr_t(m_strSerial));
		cmd->Parameters->Append(par ); //人员编码
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(LoginInformation.user_code),_bstr_t(LoginInformation.user_code));
		cmd->Parameters->Append(par ); //操作编码
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(LoginInformation.user),_bstr_t(LoginInformation.user)) ;
		cmd->Parameters->Append(par ); //操作名称


		cmd->put_CommandText(_bstr_t("prc_Reside_add_price "));
		cmd->ActiveConnection=HospitalConnect;
		cmd->Execute(NULL,NULL,adCmdStoredProc);
		
		succ=(long)cmd->Parameters->GetItem("succ")->Value;

		cmd.Detach();
		par.Detach();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return;
	}
	if( ! succ ) AfxMessageBox("成功充值");
	else AfxMessageBox("充值失败");
	
	CDialog::OnOK();
}
