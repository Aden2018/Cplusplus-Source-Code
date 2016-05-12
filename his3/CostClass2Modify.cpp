// CostClass2Modify.cpp: implementation of the CCostClass2Modify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "CostClass2Modify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCostClass2Modify::CCostClass2Modify()
{
	m_id=0;
	m_aid=0;
}

CCostClass2Modify::~CCostClass2Modify()
{

}

BOOL CCostClass2Modify::OnInitDialog()
{
	int x(0);
	CCostClass2Add::OnInitDialog();

	for( ; x< arrayDepart.GetSize() ; x++ )
		if( atol(arrayDepart[x]) == m_aid ) break;
	if( x== arrayDepart.GetSize())
	{
		AfxMessageBox("����б���ѡ�񲻵���Ӧ����𣡣�");
		return false;
	}
	m_depart.SetCurSel(x);

	m_name=strName;
	m_rem=strRem;
	m_seq=iSeq;
	UpdateData(false);
	return true;
}

void CCostClass2Modify::OnOK()
{
	UpdateData();
	if( m_name.IsEmpty() ){
		AfxMessageBox("��Ŀ�������Ʋ���Ϊ��");
		return;
	
	}
	CString strSql;
	m_aid=atol(arrayDepart[m_depart.GetCurSel()] );
	strSql.Format(" UPDATE lsq_cost_class_b SET name='%s',seq=%ld,rem='%s',id2=%ld WHERE \
		id=%ld ",m_name,m_seq,m_rem,m_aid,m_id);
	if( !CComFunc::WriteSql(strSql) )
	{	
		AfxMessageBox("�޸���Ŀ����2����,������!");
		return;
	}
	AfxMessageBox("��Ŀ����2�޸ĳɹ�!");
	
	CDialog::OnOK();

}
