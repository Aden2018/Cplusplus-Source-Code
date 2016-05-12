// ResideBedModify.cpp: implementation of the CResideBedModify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "ResideBedModify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResideBedModify::CResideBedModify()
{
	m_strBedCode="";
}

CResideBedModify::~CResideBedModify()
{

}

void CResideBedModify::OnOK()
{
	UpdateData();
	if( m_combox_local.GetCurSel() == CB_ERR || m_combox_room.GetCurSel() == CB_ERR ) {
		AfxMessageBox("����ѡ�������Ĳ����򷿼�");
		return;
	}
	strSql.Format("Update lsq_reside_bed Set blocal='%s',broom='%s',bname='%s',bprice=%.2f,bremark='%s' \
		where bcode='%s' ",localArray.GetAt(m_combox_local.GetCurSel()),roomArray.GetAt(m_combox_room.GetCurSel()),\
		m_strName,m_price,m_strRemark,m_strBedCode);

	if( COtherDecharge::WriteSQL(strSql) ) {
		AfxMessageBox("�޸ĳɹ�");
		CDialog::OnOK();

	}
	else AfxMessageBox("�޸�ʧ��");




}

BOOL CResideBedModify::OnInitDialog()
{
	CResideBedSetAdd::OnInitDialog();
	UpdateData(false);
	m_combox_local.SelectString(-1,strLocal);
	CResideBedSetAdd::OnSelchangeComboLocal();
	m_combox_room.SelectString(-1,strRoom);
	return true;

}
