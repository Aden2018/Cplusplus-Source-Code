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
	strTitle="�����޸�";
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
		AfxMessageBox("����������в��ܺ��õ����ż��ֺŵ������ַ�");

	CString strCurSel=localArray.GetAt(m_combox.GetCurSel());
	strSql.Format("Update lsq_reside_room Set rlocal='%s',rname='%s',Rremark='%s' where rcode='%s'  ",strCurSel,m_name,m_remark,strCode);
	if( COtherDecharge::WriteSQL(strSql) )AfxMessageBox("�޸ĳɹ�");
	else  AfxMessageBox("�޸�ʧ��...");
	CDialog::OnOK();

}
