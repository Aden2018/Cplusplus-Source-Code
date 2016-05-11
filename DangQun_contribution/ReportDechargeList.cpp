// ReportDechargeList.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "ReportDechargeList.h"
#include "dechargeQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportDechargeList

IMPLEMENT_DYNCREATE(CReportDechargeList, CFormView)

CReportDechargeList::CReportDechargeList()
	: CFormView(CReportDechargeList::IDD)
{
	//{{AFX_DATA_INIT(CReportDechargeList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"姚体");

	font.CreatePointFont(110,"微软雅黑");
	TITLE="费用报销明细查询";
}

CReportDechargeList::~CReportDechargeList()
{
}

void CReportDechargeList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportDechargeList)
	DDX_GridControl(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportDechargeList, CFormView)
	//{{AFX_MSG_MAP(CReportDechargeList)
	ON_WM_DESTROY()
	ON_COMMAND(ID_MENUITEM_REPORT_EXCEL, OnMenuitemReportExcel)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_DBLCLK, IDC_MSHFLEXGRID1, OnDblClickMshflexgrid1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportDechargeList diagnostics

#ifdef _DEBUG
void CReportDechargeList::AssertValid() const
{
	CFormView::AssertValid();
}

void CReportDechargeList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportDechargeList message handlers

void CReportDechargeList::OnDestroy() 
{
	CFormView::OnDestroy();
	
	theApp.pDechargeList=NULL;
	theApp.hDechargeList=NULL;
}

void CReportDechargeList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	TITLE.LoadString(IDS_STR_JOURNAL_RELEASE);

	theApp.hDechargeList=GetParentFrame()->m_hWnd;
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(TITLE);
	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle(TITLE);

//	CComFunc::comSetGridHeader(m_grid,GRID_ID);	
	CComFunc::SetGridHeader(m_grid,GRID_ID,vtAlign);
	m_grid.SetEditable(false);
	m_grid.SetListMode();
	m_grid.SetSingleRowSelection(true);
	m_grid.SetFont(&font);
	
}

void CReportDechargeList::OnDraw(CDC* pDC) 
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


void CReportDechargeList::OnDblClickMshflexgrid1(NMHDR *pNotifyStruct, LRESULT *pResult) 
{
	CDechargeQuery dq(m_grid);
	theApp.pParentGrid.pGrid=this;
	dq.DoModal();
}

void CReportDechargeList::OnClickMshflexgrid1() 
{
	const int ENDLINES=2;
	if(m_grid.GetRowCount() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_QUICK);
	CMenu* pmenu=pm.GetSubMenu(6);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  	
	
}

void CReportDechargeList::OnMenuitemReportExcel() 
{
	CComFunc::ToExcel(m_grid);	
	
}


