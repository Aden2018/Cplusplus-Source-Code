// DechargeScale.cpp: implementation of the CDechargeScale class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "DechargeScale.h"
#include "otherDecharge.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDechargeScale::CDechargeScale()
{

}

CDechargeScale::~CDechargeScale()
{

}

BOOL CDechargeScale::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	strTitle.Format("报销比例维护");
	SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	
	CString strSql;
	for( long i=0; i< 3 ; i++ ){ //获取各利比例情况
		strSql.Format("SELECT n1 FROM LSQ_GH_TYPE WHERE ds3='D' and ds1='%d' ",i+1);
		dbScale[i]=atof(COtherDecharge::GetStringTitle(strSql));
	}
	i=0;
	strSql.Format("%.2f%%",dbScale[i++]*100);
	oc1.SetWindowText(strSql);
	c1.SetWindowText(strSql);

	strSql.Format("%.2f%%",dbScale[i++]*100);
	oc3.SetWindowText(strSql);
	c3.SetWindowText(strSql);

	strSql.Format("%.2f%%",dbScale[i++]*100);
	oc5.SetWindowText(strSql);
	c5.SetWindowText(strSql);

	oc2.ShowWindow(SW_HIDE);
	c2.ShowWindow(SW_HIDE);
	oc4.ShowWindow(SW_HIDE);
	c4.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC1)->SetWindowText("在职");
	GetDlgItem(IDC_STATIC3)->SetWindowText("建国后退休");
	GetDlgItem(IDC_STATIC5)->SetWindowText("建国前退休");

	return true;
}

void CDechargeScale::OnOK()
{
	long i(0);
	CString strTmp;
	c1.GetWindowText(strTmp);
	dbScale[i++]=atof(strTmp);

	c3.GetWindowText(strTmp);
	dbScale[i++]=atof(strTmp);

	c5.GetWindowText(strTmp);
	dbScale[i++]=atof(strTmp);
//分三种情况 1.在职 2.建国后退休 3.建国前退休
	for(i=0; i< 3; i++)
	{
		strTmp.Format(" UPDATE LSQ_GH_TYPE SET n1=%.4f WHERE DS3='D' AND ds1='%d' ",dbScale[i]/100,i+1);
		COtherDecharge::WriteSQL(strTmp);
	}
	AfxMessageBox("成功更改当前职工报销比例");

}
