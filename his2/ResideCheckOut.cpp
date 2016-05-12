// ResideCheckOut.cpp: implementation of the CResideCheckOut class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "ResideCheckOut.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResideCheckOut::CResideCheckOut()
{
	strTitle="סԺ��Ա��Ժ����";
}

CResideCheckOut::~CResideCheckOut()
{

}

BOOL CResideCheckOut::OnInitDialog()
{
	CResideAddPrice::OnInitDialog();
	GetDlgItem(IDC_STATIC_OUTDATE)->SetWindowText("��Ժ����");
	CString strDate;
	strDate=COleDateTime::GetCurrentTime().Format("%Y-%m-%d");
	((CEdit*)GetDlgItem(IDC_EDIT_PRICE))->SetReadOnly();
	GetDlgItem(IDC_EDIT_PRICE)->SetWindowText(strDate);

	return true;
}

void CResideCheckOut::OnOK()
{

	_CommandPtr cmd;
	_ParameterPtr par;
	cmd.CreateInstance(__uuidof( Command ));
	par.CreateInstance(__uuidof( Parameter));

	_variant_t vNULL;
	vNULL.vt = VT_ERROR;
	vNULL.scode = DISP_E_PARAMNOTFOUND;
	int succ=0;
	const int SUCCESS=0,FAIL=1;
	try{
		cmd->put_CommandType(adCmdStoredProc) ;
	
		par=cmd->CreateParameter(_bstr_t("succ"),adInteger,adParamOutput,0,vNULL);
		cmd->Parameters->Append( par ); //�ɹ���־
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(m_strSerial),_bstr_t(m_strSerial));
		cmd->Parameters->Append(par ); //��Ա����
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(LoginInformation.user_code),_bstr_t(LoginInformation.user_code));
		cmd->Parameters->Append(par ); //��������
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(LoginInformation.user),_bstr_t(LoginInformation.user)) ;
		cmd->Parameters->Append(par ); //��������


		cmd->put_CommandText(_bstr_t("prc_Reside_Checkout "));
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
	if( SUCCESS == succ ) AfxMessageBox("�ɹ����г�Ժ����");
	else AfxMessageBox("��Ժ����ʧ��");
	
	CDialog::EndDialog(0);
}
