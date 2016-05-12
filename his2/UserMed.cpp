// UserMed.cpp: implementation of the CUserMed class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "UserMed.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char EMPLOYEE[]="���䱣��";
const char GENERIC[]="������";
const char RELATE[]="��������";
const char NOWORK[]="������Ա";
const char IC[]="��������";

const char GAOQIAN[]="��ǰְ��";
const char GANGSHANG[]="������Ա";
const char TUIYANG[]="������Ա";

CUserMed::CUserMed()
{
	dbAccount=0;
	dbCash=0;

}

CUserMed::~CUserMed()
{

}

void CUserMed::OnOK()
{

	CDialog::OnOK();
}

BOOL CUserMed::OnInitDialog()
{
	CPayMed::OnInitDialog();
	CRect rt1;
	GetDlgItem(IDC_EDIT_GH_HUAJIA)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	GetDlgItem(IDC_EDIT_GH_HUAJIA)->MoveWindow(rt1.left,rt1.top,(rt1.right-rt1.left)*2,rt1.bottom-rt1.top);

	GetDlgItem(IDC_EDIT_GH_HUAJIA)->SetWindowText("�Һ�: "+str2[6]+" �����շ�: "+str2[7]+" ��ҩ: "+str2[8] );
	
	GetDlgItem(IDBUTTON_ROLLMED)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_X4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_X6)->ShowWindow(SW_SHOW); //* ��ʾ�ʻ�֧��
	GetDlgItem(IDC_EDIT_X1)->ShowWindow(SW_SHOW); //* ��ʾ�ֽ�֧��
	GetDlgItem(IDC_EDIT_X8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_X9)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_X1)->ShowWindow(SW_SHOW); //* ��ʾ�ֽ�֧��
	GetDlgItem(IDC_STATIC_X4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_X6)->ShowWindow(SW_SHOW); //* ��ʾ�ʻ�֧��
	GetDlgItem(IDC_EDIT_MED_NUM)->EnableWindow(false);

	GetDlgItem(IDC_STATIC_X1)->SetWindowText("�ʻ�֧��");
	GetDlgItem(IDC_STATIC_X6)->SetWindowText("�ֽ�֧��");

	CString strMessage,s2;
	strMessage.Format("%.2f",dbCash);
	GetDlgItem(IDC_EDIT_X6)->SetWindowText(strMessage);
//	strMessage.Format("�ʻ�:%.2f	�ֽ�:%.2f",dbAccount,dbCash);
//	GetDlgItem(IDC_STATIC_PRICE)->SetWindowText(strMessage);
//	GetDlgItem(IDC_STATIC_PRICE)->ShowWindow(SW_SHOW);
	if( str2[3] == TUIYANG ) s2.Format("%.2f",dbAccount*0.1); //������Ա90%�ۿ�
	else if( str2[3] == NOWORK ) s2.Format("%.2f",0);
	else if( str2[3] == GAOQIAN ) s2.Format("%.2f",0);
	else if( str2[3] == GANGSHANG ) s2.Format("%.2f",0);
	else s2.Format("%.2f",dbAccount) ;
	GetDlgItem(IDC_EDIT_X1)->SetWindowText(s2);


	GetDlgItem(IDC_STATIC_NAME1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NAME2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NAME3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_MEDNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_MEDGG)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_MED_NUM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NAME1)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	long top=rt1.top;
	GetDlgItem(IDC_MSHFLEXGRID1)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	rt1.top=top;
	GetDlgItem(IDC_MSHFLEXGRID1)->MoveWindow(rt1);
	return true;
}

HBRUSH CUserMed::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr=CHuaJia::OnCtlColor(pDC,  pWnd, nCtlColor);

	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_X1)->m_hWnd || pWnd->m_hWnd == GetDlgItem(IDC_STATIC_X6)->m_hWnd )
		pDC->SetTextColor(RGB(255,0,0));
	return hbr;
}
