// PasswordView.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "PasswordView.h"
#include "otherDecharge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPasswordView dialog


CPasswordView::CPasswordView(CWnd* pParent /*=NULL*/)
	: CDialog(CPasswordView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPasswordView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"宋体");
}


void CPasswordView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPasswordView)
	DDX_Control(pDX, IDC_EDIT3, edit3);
	DDX_Control(pDX, IDC_EDIT2, edit2);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPasswordView, CDialog)
	//{{AFX_MSG_MAP(CPasswordView)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPasswordView message handlers

BOOL CPasswordView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	SetWindowText(strTitle);

	edit1.SetReadOnly();
	edit1.SetWindowText(str[0]+" /"+str[1]+" /"+str[2]);
	edit2.SetWindowText(str[5]);
	edit3.SetWindowText("");

	CenterWindow();
	AnimateWindow(m_hWnd,300,AW_SLIDE|AW_VER_POSITIVE);
	Invalidate();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPasswordView::OnOK() 
{
	CString strSql;
	edit3.GetWindowText(str[9]);
	strSql.Format("UPDATE 职工基本情况表 SET pass='%s' WHERE 卡号='%s' ",str[9],str[1]);
	if( !COtherDecharge::WriteSQL(strSql) ){
		AfxMessageBox("操作失败!!");
		return;
	}
	CDialog::OnOK();
}

HBRUSH CPasswordView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd )
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));
		return theApp.titleBrush;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
