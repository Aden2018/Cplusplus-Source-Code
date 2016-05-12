// AddHealthForModify.cpp: implementation of the CAddHealthForModify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "AddHealthForModify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAddHealthForModify::CAddHealthForModify()
{

}

CAddHealthForModify::~CAddHealthForModify()
{

}

BOOL CAddHealthForModify::OnInitDialog()
{
	CAddHealth::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_XM)->SetWindowText(str[0]);
	GetDlgItem(IDC_STATIC_XB)->SetWindowText(str[1]);
	GetDlgItem(IDC_STATIC_BM)->SetWindowText(str[2]);
	GetDlgItem(IDC_STATIC_BZ)->SetWindowText(str[3]);
	GetDlgItem(IDC_STATIC_AGE)->SetWindowText(str[4]+"/"+str[5]);
	
	
	int year,month,day;
	year=atoi(riqi.Left(4));
	month=atoi(riqi.Mid(5,2));
	day=atoi(riqi.Right(2));
	m_date.SetDate(year,month,day);

	if(gan[0].Left(2)=="阳")m_sag.SetCurSel(1);
	else m_sag.SetCurSel(0);
	if(gan[1].Left(2)=="阳")m_eag.SetCurSel(1);
	else m_eag.SetCurSel(0);
	if(gan[2].Left(2)=="阳")m_cag.SetCurSel(1);
	else m_cag.SetCurSel(0);
	if(gan[3].Left(2)=="阳")m_sab.SetCurSel(1);
	else m_sab.SetCurSel(0);
	if(gan[4].Left(2)=="阳")m_eab.SetCurSel(1);
	else m_eab.SetCurSel(0);
	if(gan[5].Left(2)=="阳")m_cab.SetCurSel(1);
	else m_cab.SetCurSel(0);

	UpdateData(false);
	
	if(xuexin.Left(1)=="O")c_xuexin.SetCurSel(0);
	else if(xuexin.Left(1)=="A" && xuexin.Left(2)=="AB")c_xuexin.SetCurSel(3);
	else if("A"== xuexin.Left(1))c_xuexin.SetCurSel(1);
	else if("B"== xuexin.Left(1) && "BR" != xuexin.Left(2))c_xuexin.SetCurSel(2);
	else if("BRho(-)"==xuexin.Left(7))c_xuexin.SetCurSel(4);
	else c_xuexin.SetCurSel(CB_ERR);

	return true;
}

void CAddHealthForModify::OnOK()
{
	CString strSql;
	UpdateData();
	strKH=m_kahao;
	strSql.Format("delete from tijian where kahao='%s' and riqi=to_date('%s','yyyy-mm-dd') ",m_kahao,riqi);
	try{

		HospitalConnect->BeginTrans();
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();
		CAddHealth::OnOK();
	}
	catch(_com_error e)
	{
		AfxMessageBox("更改失败,请重启应用程序后重试...");
		HospitalConnect->RollbackTrans();
		return;
	}
	
	CDialog::OnOK();

}
