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
	strTitle="住院人员出院操作";
}

CResideCheckOut::~CResideCheckOut()
{

}

BOOL CResideCheckOut::OnInitDialog()
{
	CResideAddPrice::OnInitDialog();
	GetDlgItem(IDC_STATIC_OUTDATE)->SetWindowText("出院日期");
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
		cmd->Parameters->Append( par ); //成功标志
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(m_strSerial),_bstr_t(m_strSerial));
		cmd->Parameters->Append(par ); //人员编码
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(LoginInformation.user_code),_bstr_t(LoginInformation.user_code));
		cmd->Parameters->Append(par ); //操作编码
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(LoginInformation.user),_bstr_t(LoginInformation.user)) ;
		cmd->Parameters->Append(par ); //操作名称


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
	if( SUCCESS == succ ) AfxMessageBox("成功进行出院操作");
	else AfxMessageBox("出院操作失败");
	
	CDialog::EndDialog(0);
}
