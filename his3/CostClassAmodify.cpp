// CostClassAmodify.cpp: implementation of the CCostClassAmodify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "CostClassAmodify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCostClassAmodify::CCostClassAmodify()
{

}

CCostClassAmodify::~CCostClassAmodify()
{

}

BOOL CCostClassAmodify::OnInitDialog()
{
	CCostClassAadd::OnInitDialog();
	UpdateData(false);
	return true;
}



void CCostClassAmodify::OnOK()
{
	UpdateData();
	if( m_name.IsEmpty() ){
		AfxMessageBox("��Ŀ�������Ʋ���Ϊ��");
		return;
	
	}
	CString strSql;
	//strSql.Format(" INSERT INTO lsq_cost_class_a(id,name,seq,rem) values(\
		(select NVL(max(ID),0)+1 FROM lsq_cost_class_a ),'%s',%ld,'%s')",\
		m_name,m_order,m_cmt);
	strSql.Format(" UPDATE lsq_cost_class_a SET name='%s',seq=%ld,rem='%s' WHERE \
		id=%ld ",m_name,m_order,m_cmt,m_id);
	if( !CComFunc::WriteSql(strSql) )
	{	
		AfxMessageBox("�޸���Ŀ�������,������!");
		return;
	}
	AfxMessageBox("��Ŀ�����޸ĳɹ�!");
	
	CDialog::OnOK();
}
