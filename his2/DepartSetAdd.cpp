// DepartSetAdd.cpp: implementation of the CDepartSetAdd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "DepartSetAdd.h"
#include "otherDecharge.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDepartSetAdd::CDepartSetAdd()
{

}

CDepartSetAdd::~CDepartSetAdd()
{

}

BOOL CDepartSetAdd::OnInitDialog()
{
	CBaseProjectSet::OnInitDialog();
	edit1.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_PY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_PY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_EDIT_CODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CODE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC1)->SetWindowText("������");
	GetDlgItem(IDC_STATIC3)->SetWindowText("��������");
	GetDlgItem(IDC_EDIT_CASH_STANDARD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CASH_STANDARD)->ShowWindow(SW_HIDE);

	edit2.SetWindowText(str[2]);//��������
	CRect rt,rt2;
	edit1.GetWindowRect(rt);
	edit2.GetWindowRect(rt2);
	rt2.right=rt.right;
	ScreenToClient(rt2);
	edit2.MoveWindow(rt2);
	return true;
}

void CDepartSetAdd::OnOK()
{
	UpdateData();
	CString strT1,strT2,strSql,strT3,strT4;

	combo1.GetWindowText(strT1);
	edit2.GetWindowText(strT3);
	if( strT1.IsEmpty() ||  strT3.IsEmpty() ){
		AfxMessageBox("�뽫����������д��ȷ�ٽ��в���!!!");
		return;
	}

	if( flag == 1 ){ //����
		strSql.Format(" INSERT INTO �����ű�(���ű���,������,��������) \
			VALUES( (select NVL(max(���ű���),0)+1 FROM �����ű�),'%s','%s') ",\
			strT1,strT3 );
		if(!COtherDecharge::WriteSQL(strSql)){
			AfxMessageBox("���ʧ��");
			return;
		}
	

	}
	else if(flag == 2){
		strSql.Format(" UPDATE �����ű� SET ������='%s',��������='%s' \
			WHERE ���ű���='%s' ",strT1,strT3,str[1] );
		if(!COtherDecharge::WriteSQL(strSql)){
			AfxMessageBox("�޸�ʧ��");
			return;
		}

	}
	CDialog::OnOK();	
}

void CDepartSetAdd::OnCancel()
{
	CDialog::OnCancel();
}
