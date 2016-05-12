// StandardSubsidySet.cpp: implementation of the CStandardSubsidySet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "StandardSubsidySet.h"
#include "standardSubsidyAdd.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStandardSubsidySet::CStandardSubsidySet()
{

}

CStandardSubsidySet::~CStandardSubsidySet()
{

}

void CStandardSubsidySet::OnRclickListQuery(NMHDR *pNMHDR, LRESULT *pResult)
{
	UINT nIndex;
	nIndex=c_list.GetNextItem(-1,LVNI_SELECTED);
	if(nIndex== -1 ) {

		AfxMessageBox("����ѡ�񡣡���");
		return ;
	}

	strKH.Format("�Ƿ�Ҫɾ�� (%s / %s) ����",c_list.GetItemText(nIndex,1),c_list.GetItemText(nIndex,2) );
	if ( AfxMessageBox(strKH,MB_OKCANCEL)== IDCANCEL ) return;

	strKH.Format(" DELETE FROM lsq_upgrade WHERE ds3='%s' AND ds2='ESUB' ",c_list.GetItemText(nIndex,0) );
	if(!COtherDecharge::WriteSQL(strKH)){
		AfxMessageBox("ɾ��ʧ�ܣ���");
		return;
	}
	OnOK();

}

void CStandardSubsidySet::OnDblclkListQuery(NMHDR *pNMHDR, LRESULT *pResult)
{
	UINT nIndex;
	nIndex=c_list.GetNextItem(-1,LVNI_SELECTED);
	CStandardSubsidyAdd di;
	if(nIndex== -1 ) {
		di.strTitle="����������׼";
		di.flag=1;
//����		AfxMessageBox("����ѡ�񡣡���");
	}
	else {
		di.strTitle="�޸Ĳ�������";
		di.flag=2;
		di.str[0]=c_list.GetItemText(nIndex,0); //����
		di.str[2]=c_list.GetItemText(nIndex,1); // ����
		di.str[3]=c_list.GetItemText(nIndex,2); //���
	}

	if(di.DoModal()==IDOK) OnOK();

}
