// RoomSetModify.cpp: implementation of the CRoomSetModify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "RoomSetModify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRoomSetModify::CRoomSetModify()
{
	strTitle="房间修改";
}

CRoomSetModify::~CRoomSetModify()
{

}

BOOL CRoomSetModify::OnInitDialog()
{
	CRoomSetAdd::OnInitDialog();
	UpdateData(false);
	m_combox.SelectString(-1,strLocalName);
	return true;

}

void CRoomSetModify::OnOK()
{
	const int NOFIND=-1;
	UpdateData();
	if ( ! (m_name.Find("'") == NOFIND && m_name.Find(";") == NOFIND  && \
		m_remark.Find("'") == NOFIND && m_remark.Find(";") == NOFIND && ! m_name.IsEmpty())  )
		AfxMessageBox("输入的文字中不能含用单引号及分号等特殊字符");

	CString strCurSel=localArray.GetAt(m_combox.GetCurSel());
	strSql.Format("Update lsq_reside_room Set rlocal='%s',rname='%s',Rremark='%s' where rcode='%s'  ",strCurSel,m_name,m_remark,strCode);
	if( COtherDecharge::WriteSQL(strSql) )AfxMessageBox("修改成功");
	else  AfxMessageBox("修改失败...");
	CDialog::OnOK();

}
