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
	strTitle="סԺ��Ա����סԺ��";
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
//	CString HeadTitle[]={"���","s1","����","�Ա�","����","�绰","������λ","��ͥסַ","��������","ҽ��",\
		"����","��λ","סԺ�����","�Ǽ�Ա"}; //�� 24 ��
	CDialog::OnInitDialog();

	SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&CHis2App::fontTitle);

	m_curRow=pGrid->GetRow(); //���е���
	m_strSerial=pGrid->GetTextMatrix(m_curRow,1); //�������к�
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(pGrid->GetTextMatrix(m_curRow,2) ); //����
	GetDlgItem(IDC_STATIC_DATE)->SetWindowText(pGrid->GetTextMatrix(m_curRow,10) ); //סԺ����
	GetDlgItem(IDC_STATIC_ADDR)->SetWindowText(pGrid->GetTextMatrix(m_curRow,7) ); //��ַ
	GetDlgItem(IDC_STATIC_WORK)->SetWindowText(pGrid->GetTextMatrix(m_curRow,6) ); //������λ
	GetDlgItem(IDC_STATIC_DESC)->SetWindowText(pGrid->GetTextMatrix(m_curRow,8) ); //��������
	
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

void CResideAddPrice::OnOK()  // ����
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
		cmd->Parameters->Append( par ); //�ɹ���־
		par=cmd->CreateParameter(_bstr_t("price"),adDouble,adParamInput,sizeof(double),_bstr_t(m_dbPrice));
		cmd->Parameters->Append(par ); //��ֵ���
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(m_strSerial),_bstr_t(m_strSerial));
		cmd->Parameters->Append(par ); //��Ա����
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(LoginInformation.user_code),_bstr_t(LoginInformation.user_code));
		cmd->Parameters->Append(par ); //��������
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(LoginInformation.user),_bstr_t(LoginInformation.user)) ;
		cmd->Parameters->Append(par ); //��������


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
	if( ! succ ) AfxMessageBox("�ɹ���ֵ");
	else AfxMessageBox("��ֵʧ��");
	
	CDialog::OnOK();
}
