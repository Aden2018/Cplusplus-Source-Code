// FormGhList.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "FormGhList.h"
#include "comFunc.H"
#include "ghQuery.h"
#include "viewUserComuse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormGhList

IMPLEMENT_DYNCREATE(CFormGhList, CFormView)

CFormGhList::CFormGhList()
	: CFormView(CFormGhList::IDD)
{
	//{{AFX_DATA_INIT(CFormGhList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"姚体");
	font.CreatePointFont(110,"微软雅黑");

}

CFormGhList::~CFormGhList()
{
}

void CFormGhList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormGhList)
	DDX_GridControl(pDX,IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormGhList, CFormView)
	//{{AFX_MSG_MAP(CFormGhList)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_MENU_GH_LISTTOEXCEL, OnMenuGhListtoexcel)
	ON_COMMAND(ID_MENU_GH_VIEWLIST, OnMenuGhViewlist)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_DBLCLK, IDC_MSHFLEXGRID1, OnGridDblClick)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormGhList diagnostics

#ifdef _DEBUG
void CFormGhList::AssertValid() const
{
	CFormView::AssertValid();
}

void CFormGhList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormGhList message handlers

void CFormGhList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
extern CHis3App theApp;
	theApp.hGhList=GetParentFrame()->m_hWnd;
	TITLE.LoadString(IDS_STR_JOURNAL_QUERY);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(TITLE);
	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle(TITLE);

	
//	CComFunc::comSetGridHeader(m_grid,GRID_ID);	
	CComFunc::SetGridHeader(m_grid,GRID_ID/* 表格头部ID*/,vtAlign); 
	m_grid.SetEditable(false);
	m_grid.SetListMode();
	m_grid.SetSingleRowSelection(true);
	m_grid.SetFont(&font);

}

void CFormGhList::OnDraw(CDC* pDC) 
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

void CFormGhList::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)  //弹出查询对话框
{
	CGhQuery gq;
	theApp.pParentGrid.pGrid=this;
	gq.DoModal();
}

HBRUSH CFormGhList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd)
		pDC->SetTextColor(LSQ_RED);
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CFormGhList::OnClickMshflexgrid1()  //右键菜单
{ /*
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
	CMenu* pmenu=pm.GetSubMenu(3);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  	
	*/
}

void CFormGhList::OnMenuGhListtoexcel() // 输出 EXCEL
{
//	CComFunc::ToExcel(&m_grid);	
}

void CFormGhList::OnMenuGhViewlist()  // 查看消费详情
{

			
}

void CFormGhList::OnClose() 
{
	CFormView::OnClose();
}

void CFormGhList::OnDestroy() 
{
	CFormView::OnDestroy();
	theApp.hGhList=NULL;
	theApp.pGhList=NULL;
	
	
}

