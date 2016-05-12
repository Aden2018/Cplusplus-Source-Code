// BaseAddCash.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "BaseAddCash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseAddCash dialog


CBaseAddCash::CBaseAddCash(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseAddCash::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBaseAddCash)
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"宋体");
	strTitle.Format("请设置标题");
}


void CBaseAddCash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBaseAddCash)
	DDX_Control(pDX, IDOK_B3, m_b6);
	DDX_Control(pDX, IDOK_EXCEL, m_b5);
	DDX_Control(pDX, IDOK_B2, m_b4);
	DDX_Control(pDX, IDOK_B1, m_b3);
	DDX_Control(pDX, IDOK, m_b2);
	DDX_Control(pDX, IDCANCEL, m_b1);
	DDX_Control(pDX, IDC_STATIC_XE1, m_xe1);
	DDX_Control(pDX, IDC_EDIT9, e9);
	DDX_Control(pDX, IDC_EDIT8, e8);
	DDX_Control(pDX, IDC_EDIT7, e7);
	DDX_Control(pDX, IDC_EDIT6, e6);
	DDX_Control(pDX, IDC_EDIT5, e5);
	DDX_Control(pDX, IDC_EDIT4, e4);
	DDX_Control(pDX, IDC_EDIT3, e3);
	DDX_Control(pDX, IDC_EDIT10, e2);
	DDX_Control(pDX, IDC_EDIT1, e1);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, d2);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, d1);
	DDX_Control(pDX, IDC_COMBO3, c3);
	DDX_Control(pDX, IDC_COMBO2, c2);
	DDX_Control(pDX, IDC_COMBO1, c1);
	DDX_Control(pDX, IDC_STATIC_XE4, m_xe4);
	DDX_Control(pDX, IDC_STATIC_XE3, m_xe3);
	DDX_Control(pDX, IDC_STATIC_XE2, m_xe2);
	DDX_Control(pDX, IDC_STATIC_E4, m_e4);
	DDX_Control(pDX, IDC_STATIC_E3, m_e3);
	DDX_Control(pDX, IDC_STATIC_E2, m_e2);
	DDX_Control(pDX, IDC_STATIC_E1, m_e1);
	DDX_Control(pDX, IDC_STATICX4, m_sx4);
	DDX_Control(pDX, IDC_STATICX3, m_sx3);
	DDX_Control(pDX, IDC_STATICX2, m_sx2);
	DDX_Control(pDX, IDC_STATICX1, m_sx1);
	DDX_Control(pDX, IDC_STATIC4, m_s4);
	DDX_Control(pDX, IDC_STATIC3, m_s3);
	DDX_Control(pDX, IDC_STATIC2, m_s2);
	DDX_Control(pDX, IDC_STATIC1, m_s1);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBaseAddCash, CDialog)
	//{{AFX_MSG_MAP(CBaseAddCash)
	ON_BN_CLICKED(IDOK_EXCEL, OnExcel)
	ON_BN_CLICKED(IDOK_B2, OnB2)
	ON_BN_CLICKED(IDOK_B1, OnB1)
	ON_BN_CLICKED(IDOK_B3, OnB3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseAddCash message handlers

BOOL CBaseAddCash::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	SetWindowText(strTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBaseAddCash::OnOK() 
{
	
}

void CBaseAddCash::OnExcel() 
{
	
}

void CBaseAddCash::OnB2() 
{
	
}

void CBaseAddCash::OnB1() 
{
	
}

void CBaseAddCash::OnB3() 
{
	// TODO: Add your control notification handler code here
	
}

BEGIN_EVENTSINK_MAP(CBaseAddCash, CDialog)
    //{{AFX_EVENTSINK_MAP(CBaseAddCash)
	ON_EVENT(CBaseAddCash, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CBaseAddCash, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CBaseAddCash::OnDblClickMshflexgrid1() 
{
	// TODO: Add your control notification handler code here
	
}

void CBaseAddCash::OnClickMshflexgrid1() 
{
	// TODO: Add your control notification handler code here
	
}
