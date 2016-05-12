// StandardSubsidyAdd.cpp: implementation of the CStandardSubsidyAdd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "StandardSubsidyAdd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStandardSubsidyAdd::CStandardSubsidyAdd()
{
	strTitle="特殊补助标准设定";
	strSql="select 1 FROM dual ";

}

CStandardSubsidyAdd::~CStandardSubsidyAdd()
{

}

BOOL CStandardSubsidyAdd::OnInitDialog()
{
	CBaseProjectSet::OnInitDialog();

	CRect rt;
	combo1.ShowWindow(SW_HIDE);
	combo1.GetWindowRect(rt);
	ScreenToClient(rt);
	edit1.MoveWindow(rt);

	

	GetDlgItem(IDC_STATIC1)->SetWindowText("补助性质");
	GetDlgItem(IDC_STATIC3)->SetWindowText("补助金额");
	GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_PY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_PY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_EDIT_CODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_CASH_STANDARD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CASH_STANDARD)->ShowWindow(SW_HIDE);

	CRect rt2;
	edit1.GetWindowRect(rt);
	edit2.GetWindowRect(rt2);
	rt2.right=rt.right;
	ScreenToClient(rt2);
	edit2.MoveWindow(rt2);

	return true;
}

void CStandardSubsidyAdd::OnOK()
{
	UpdateData();
	CString strT2,strSql,strT3,strT4;
	edit1.GetWindowText(strT2);
	edit2.GetWindowText(strT3);
	if( strT2.IsEmpty() || strT3.IsEmpty() ){
		AfxMessageBox("请将所有内容填写正确再进行操作!!!");
		return;
	}

	if( flag == 1 ){ //新增
		strSql.Format(" INSERT INTO lsq_upgrade(ds3,ds2,ds1,n2,n3) \
			VALUES( (select Ltrim(to_char(NVL(max(ds3),0)+1,'099')) FROM \
			lsq_upgrade WHERE ds2='ESUB'),'ESUB','%s',( select NVL(max(n2),0)+1 FROM \
			lsq_upgrade WHERE ds2='ESUB'),%.2f ) ",strT2,atof(strT3) );
		if(!COtherDecharge::WriteSQL(strSql)){
			AfxMessageBox("添加失败");
			return;
		}
	

	}
	else if(flag == 2){
		strSql.Format(" UPDATE lsq_upgrade SET ds1='%s',n3=%.2f WHERE ds3='%s' ",strT2,\
			atof(strT3),str[0] );
		if(!COtherDecharge::WriteSQL(strSql)){
			AfxMessageBox("修改失败");
			return;
		}

	}
	CDialog::OnOK();	
}

void CStandardSubsidyAdd::OnCancel()
{

	CDialog::OnCancel();
}
