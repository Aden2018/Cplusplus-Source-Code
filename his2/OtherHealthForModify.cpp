// OtherHealthForModify.cpp: implementation of the COtherHealthForModify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "OtherHealthForModify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//* ���������Ա��Ϣ�޸���
//* ����̳��� COtherHealth ,COtherHealth���������������Ա��Ϣ����
//* �̳�֮���½� COtherHealthForModify ,���������ڲ�ѯ����Ա��Ϣ�޸�
//* ����:������			����:2005/12/08
//////////////////////////////////////////////////////////////////////

COtherHealthForModify::COtherHealthForModify()
{

}

COtherHealthForModify::~COtherHealthForModify()
{

}

BOOL COtherHealthForModify::OnInitDialog()
{
	COtherHealth::OnInitDialog();
	
	m_strName=str[0];
	m_strAge=str[2];
	m_strAddress=str[3];
	m_strPhone=str[4];
	
	int year,month,day;
	year=atoi(riqi.Left(4));
	month=atoi(riqi.Mid(5,2));
	day=atoi(riqi.Right(2));
	m_date.SetDate(year,month,day);

	if(gan[0].Left(2)=="��")m_sag.SetCurSel(1);
	else m_sag.SetCurSel(0);
	if(gan[1].Left(2)=="��")m_eag.SetCurSel(1);
	else m_eag.SetCurSel(0);
	if(gan[2].Left(2)=="��")m_cag.SetCurSel(1);
	else m_cag.SetCurSel(0);
	if(gan[3].Left(2)=="��")m_sab.SetCurSel(1);
	else m_sab.SetCurSel(0);
	if(gan[4].Left(2)=="��")m_eab.SetCurSel(1);
	else m_eab.SetCurSel(0);
	if(gan[5].Left(2)=="��")m_cab.SetCurSel(1);
	else m_cab.SetCurSel(0);

	UpdateData(false);
	
	if(xuexin.Left(1)=="O")c_xuexin.SetCurSel(0);
	else if(xuexin.Left(1)=="A" && xuexin.Left(2)=="AB")c_xuexin.SetCurSel(3);
	else if("A"== xuexin.Left(1))c_xuexin.SetCurSel(1);
	else if("B"== xuexin.Left(1) && "BR" != xuexin.Left(2))c_xuexin.SetCurSel(2);
	else if("BRho(-)"==xuexin.Left(7))c_xuexin.SetCurSel(4);
	else c_xuexin.SetCurSel(CB_ERR);

	if( str[1] == "��" )c_sex.SetCurSel(0);
	else c_sex.SetCurSel(1);

	return true;
}

void COtherHealthForModify::OnOK()
{
	CString strSql;
	UpdateData();

	strSql.Format("delete from other_tijian where rec_xm='%s' and riqi=to_date('%s','yyyy-mm-dd') ",m_strName,riqi);
	try{

		HospitalConnect->BeginTrans();
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();
		COtherHealth::OnOK();
	}
	catch(_com_error e)
	{
		AfxMessageBox("����ʧ��,������Ӧ�ó��������...");
		HospitalConnect->RollbackTrans();
		return;
	}
	
	CDialog::OnOK();
}
