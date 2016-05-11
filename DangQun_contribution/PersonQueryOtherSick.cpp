// PersonQueryOtherSick.cpp: implementation of the CPersonQueryOtherSick class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "PersonQueryOtherSick.h"
#include "comFunc.H"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPersonQueryOtherSick::CPersonQueryOtherSick()
{

}

CPersonQueryOtherSick::~CPersonQueryOtherSick()
{

}

BOOL CPersonQueryOtherSick::OnInitDialog()
{
	CDialog::OnInitDialog();
	CComFunc::comSetGridHeader(m_grid,10 ); //���ͷ����
	OnOK();
	return true;

}

void CPersonQueryOtherSick::OnOK()
{
	CString strSql,strID,strMc;
	int iSel=m_depart.GetCurSel();
	m_id.GetWindowText(strID);
	m_mc.GetWindowText(strMc);
	
	CComFunc::comSetGridHeader(m_grid,10);
	CComFunc::GetSql(strSql,9);
	if( ! strID.IsEmpty() ) strSql+=" AND BM like '"+strID+"%'" ;
	if( ! strMc.IsEmpty() ) strSql+=" AND XM like '"+strMc+"%' " ;
	strSql+=" AND lb='"+strTYPE+"'";
	
	CComFunc::ReadDataForGrid(strSql,m_grid);

}

void CPersonQueryOtherSick::OnDblClickMshflexgrid1()
{
	CRegisterGh *pGH=(CRegisterGh*)lp;
	long iSel=m_grid.GetRowSel();
	if( iSel == 0 || iSel == m_grid.GetRows()-1 ) return;
	
	pGH->strOHTERcode=m_grid.GetTextMatrix(iSel,1);
	pGH->m_kh.SetWindowText(pGH->strOHTERcode ); //����
	pGH->m_name.SetWindowText(m_grid.GetTextMatrix(iSel,2) ); //����
	pGH->m_se.SetCurSel( m_grid.GetTextMatrix(iSel,3).Compare("��")== 0 ? 0:1 ); // �Ա�
	pGH->m_name.SetReadOnly();
	pGH->m_se.EnableWindow(false);

	CDialog::OnOK();

}
