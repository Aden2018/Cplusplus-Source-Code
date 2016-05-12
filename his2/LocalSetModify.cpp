// LocalSetModify.cpp: implementation of the CLocalSetModify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "LocalSetModify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLocalSetModify::CLocalSetModify()
{
	 strTitle="病区修改操作";

}

CLocalSetModify::~CLocalSetModify()
{

}

BOOL CLocalSetModify::OnInitDialog()
{
	CLocalSetAdd::OnInitDialog();
	UpdateData(false);
	GetDlgItem(IDOK)->SetWindowText("修改");
	return true;
}

void CLocalSetModify::OnOK()
{
	const int NOFIND=-1;
	UpdateData();
	if ( ! (m_name.Find("'") == NOFIND && m_name.Find(";") == NOFIND  && \
		m_remark.Find("'") == NOFIND && m_remark.Find(";") == NOFIND && ! m_name.IsEmpty())  )
		AfxMessageBox("输入的文字中不能含用单引号及分号等特殊字符");
	
	strSql.Format("Update lsq_reside_local Set lname='%s',lremark='%s' Where lLocal='%s' ",m_name,m_remark,strBM);
	if( COtherDecharge::WriteSQL(strSql) )AfxMessageBox("修改成功");
	else  AfxMessageBox("修改失败...");
	CDialog::OnOK();

}
