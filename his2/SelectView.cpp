// SelectView.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "SelectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectView dialog


CSelectView::CSelectView(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_mixed WHERE ds3='DIALOG1' AND ds4='TITLE' ");
	fontTitle.CreatePointFont(180,"黑体");
	flagSelect=-1;
}


void CSelectView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectView)
	DDX_Control(pDX, IDC_COMBO2, combo2);
	DDX_Control(pDX, IDC_COMBO1, combo1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectView, CDialog)
	//{{AFX_MSG_MAP(CSelectView)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectView message handlers

BOOL CSelectView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	SetWindowText(strTitle);

	CDialogMedXL::ReadName("SELECT ds1　FROM lsq_mixed WHERE ds4='VIEWA' AND ds3='DIALOG1' ORDER BY n1 ",combo1);
	combo1.SetCurSel(0); //选择第一列

	CDialogMedXL::ReadName("SELECT ds2　FROM lsq_mixed WHERE ds4='VIEWA' AND ds3='DIALOG1' ORDER BY n1 ",combo2);
//选择第2列
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectView::OnOK() 
{
	flagSelect=combo1.GetCurSel();	
	combo2.GetLBText( flagSelect ,strSelect ) ;

	CDialog::OnOK();
}

HBRUSH CSelectView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd )
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,0,0));
		return theApp.titleBrush;
	}

	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
