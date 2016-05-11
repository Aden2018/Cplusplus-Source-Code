// ReportUsedAll1.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "ReportUsedAll1.h"
#include "reportUsedAllquery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportUsedAll

IMPLEMENT_DYNCREATE(CReportUsedAll, CFormView)

CReportUsedAll::CReportUsedAll()
	: CFormView(CReportUsedAll::IDD)
{
	//{{AFX_DATA_INIT(CReportUsedAll)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"姚体");
}

CReportUsedAll::~CReportUsedAll()
{
}

void CReportUsedAll::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportUsedAll)
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportUsedAll, CFormView)
	//{{AFX_MSG_MAP(CReportUsedAll)
	ON_WM_DESTROY()
	ON_COMMAND(ID_MENU_USEALL_EXCEL, OnMenuUseallExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportUsedAll diagnostics

#ifdef _DEBUG
void CReportUsedAll::AssertValid() const
{
	CFormView::AssertValid();
}

void CReportUsedAll::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportUsedAll message handlers

void CReportUsedAll::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
extern CHis3App theApp;
	theApp.hUsedAll=GetParentFrame()->m_hWnd;
	TITLE.LoadString(IDS_STR_TITLE_MAKE_FEE);

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(TITLE);
	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle(TITLE);

	CComFunc::comSetGridHeader(m_grid,COL_ID);	
	
}

void CReportUsedAll::OnDraw(CDC* pDC) 
{
	CRect r1,r2,rectTitle,rectButton;
	long titleHigh;

	GetClientRect(&r2);
	GetDlgItem(IDC_STATIC_TITLE)->GetWindowRect(rectTitle);
	ScreenToClient(rectTitle);
	rectTitle.right=r2.right;
	rectTitle.left= r2.left;
	titleHigh=rectTitle.bottom-rectTitle.top;
	rectTitle.top=  r2.top;
	rectTitle.bottom = r2.top+ titleHigh;
	GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(0,0,r2.right-r2.left,titleHigh);

	GetDlgItem(IDC_MSHFLEXGRID1)->GetWindowRect(&r1);
	ScreenToClient(&r1);
	GetDlgItem(IDC_MSHFLEXGRID1)->MoveWindow(0,r2.top+titleHigh,r2.right,r2.bottom-titleHigh);	
	
	
}

void CReportUsedAll::OnDestroy() 
{
	CFormView::OnDestroy();
	
	theApp.pUsedAll=NULL;
		theApp.hUsedAll=NULL;

	
	
}

BEGIN_EVENTSINK_MAP(CReportUsedAll, CFormView)
    //{{AFX_EVENTSINK_MAP(CReportUsedAll)
	ON_EVENT(CReportUsedAll, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CReportUsedAll, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CReportUsedAll::OnDblClickMshflexgrid1() 
{
	CReportUsedAllQuery aq;
	theApp.pParentGrid.pGrid=this;
	aq.DoModal();


}




void CReportUsedAll::OnClickMshflexgrid1() 
{
	const int ENDLINES=2;
	if(m_grid.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_QUICK);
	CMenu* pmenu=pm.GetSubMenu(7);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  	
	
}

void CReportUsedAll::OnMenuUseallExcel() 
{
	CComFunc::ToExcel(&m_grid);	
	
}
