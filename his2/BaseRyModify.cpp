// BaseRyModify.cpp: implementation of the CBaseRyModify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "BaseRyModify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseRyModify::CBaseRyModify()
{

}

CBaseRyModify::~CBaseRyModify()
{

}

void CBaseRyModify::OnOK()
{
	CString strSql;
	c_sex.GetLBText(c_sex.GetCurSel(),str[2]);
	c_name.GetWindowText(str[1]);
	c_kh.GetWindowText(str[0]);

	try{

		HospitalConnect->BeginTrans();
		strSql.Format(" UPDATE  医保人员列表 SET 姓名='%s',性别='%s' Where 卡号='%s' ",str[1],str[2],str[0]);

		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);


		HospitalConnect->CommitTrans();


	}
	catch(_com_error e)
	{
		AfxMessageBox("UPDATE ERROR...");
		HospitalConnect->RollbackTrans();
		return;
	}
	pGrid->SetTextMatrix(selRow,2,str[1]);
	pGrid->SetTextMatrix(selRow,3,str[2]);
	CDialog::OnOK();
}

BOOL CBaseRyModify::OnInitDialog()
{
	CDialog::OnInitDialog();
	c_name.SetWindowText( pGrid->GetTextMatrix(selRow,2) );
	c_kh.SetWindowText( pGrid->GetTextMatrix(selRow,1) );
	CString strTemp;
	strTemp=pGrid->GetTextMatrix(selRow,3);
	if( strTemp == "男" ) c_sex.SetCurSel(0);
	else if (strTemp == "女") c_sex.SetCurSel(1);
	else c_sex.SetCurSel(2);

	c_kh.SetReadOnly();

	return true;

}
