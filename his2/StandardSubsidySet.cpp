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

		AfxMessageBox("请先选择。。。");
		return ;
	}

	strKH.Format("是否要删除 (%s / %s) ？？",c_list.GetItemText(nIndex,1),c_list.GetItemText(nIndex,2) );
	if ( AfxMessageBox(strKH,MB_OKCANCEL)== IDCANCEL ) return;

	strKH.Format(" DELETE FROM lsq_upgrade WHERE ds3='%s' AND ds2='ESUB' ",c_list.GetItemText(nIndex,0) );
	if(!COtherDecharge::WriteSQL(strKH)){
		AfxMessageBox("删除失败！！");
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
		di.strTitle="新增补助标准";
		di.flag=1;
//新增		AfxMessageBox("请先选择。。。");
	}
	else {
		di.strTitle="修改补助性质";
		di.flag=2;
		di.str[0]=c_list.GetItemText(nIndex,0); //编码
		di.str[2]=c_list.GetItemText(nIndex,1); // 内容
		di.str[3]=c_list.GetItemText(nIndex,2); //金额
	}

	if(di.DoModal()==IDOK) OnOK();

}
