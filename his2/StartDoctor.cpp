// StartDoctor.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "StartDoctor.h"
#include "ProgressIndicate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartDoctor dialog


CStartDoctor::CStartDoctor(CWnd* pParent /*=NULL*/)
	: CDialog(CStartDoctor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStartDoctor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_curTabSel=0;
}


void CStartDoctor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartDoctor)
	DDX_Control(pDX, IDC_TAB_DOCTOR_START, ctab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartDoctor, CDialog)
	//{{AFX_MSG_MAP(CStartDoctor)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_DOCTOR_START, OnSelchangeTabDoctorStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartDoctor message handlers

BOOL CStartDoctor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ctab.InsertItem(0,"      挂 号      ");
	ctab.InsertItem(1,"     划价收费    ");
	ctab.InsertItem(2,"      取 药       ");
	ctab.InsertItem(3,"   退出系统   ");
	gh.Create(IDD_GH,GetDlgItem(IDC_TAB_DOCTOR_START));
	
	hj.Create(IDD_MED_HUAJIA_LIST,GetDlgItem(IDC_TAB_DOCTOR_START));
	
	pm.Create(IDD_MED_HUAJIA_LIST,GetDlgItem(IDC_TAB_DOCTOR_START));
	
	SetWindowText("门诊划价收费系统...");
	CRect r1;
	GetDlgItem(IDC_TAB_DOCTOR_START)->GetClientRect(r1);
	r1.top+=25;
	r1.right-=2;
	gh.MoveWindow(r1);
	hj.MoveWindow(r1);
	pm.MoveWindow(r1);

	gh.ShowWindow(SW_SHOW);
	
	ctab.SetCurSel(m_curTabSel);
	if( m_curTabSel == 1){
		hj.m_comboxSort.SetCurSel(1);
	}
	OnSelchangeTabDoctorStart(NULL, NULL) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStartDoctor::OnSelchangeTabDoctorStart(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int sel=ctab.GetCurSel();

	switch(sel)
	{
	case 0:
		gh.ShowWindow(SW_SHOW);
		hj.ShowWindow(SW_HIDE);
		pm.ShowWindow(SW_HIDE);
		break;
	case 1:
		gh.ShowWindow(SW_HIDE);
		pm.ShowWindow(SW_HIDE);
		hj.ShowWindow(SW_SHOW);
		hj.OnOK();
		break;
	case 2:
		gh.ShowWindow(SW_HIDE);
		hj.ShowWindow(SW_HIDE);
		pm.ShowWindow(SW_SHOW);
		pm.OnOK();
		break;
	default:  // 撤消对话框
		gh.DestroyWindow();
		hj.DestroyWindow();
		pm.DestroyWindow();
		OnCancel();
		break;
	}
		
//	*pResult = 0;
}

//DEL BOOL CStartDoctor::PreTranslateMessage(MSG* pMsg) 
//DEL {
//DEL 	// TODO: Add your specialized code here and/or call the base class
//DEL 	
//DEL 	return CDialog::PreTranslateMessage(pMsg);
//DEL }



//DEL void CStartDoctor::OnDestroy() 
//DEL {
//DEL 	CDialog::OnDestroy();
//DEL 
//DEL 	gh.DestroyWindow();
//DEL 	hj.DestroyWindow();
//DEL 	pm.DestroyWindow();
//DEL 
//DEL 	
//DEL }
