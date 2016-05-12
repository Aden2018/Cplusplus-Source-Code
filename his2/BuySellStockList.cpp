// BuySellStockList.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "BuySellStockList.h"
#include "buySellStockQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuySellStockList

IMPLEMENT_DYNCREATE(CBuySellStockList, CFormView)

CBuySellStockList::CBuySellStockList()
	: CFormView(CBuySellStockList::IDD)
{
	//{{AFX_DATA_INIT(CBuySellStockList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"姚体");

}

CBuySellStockList::~CBuySellStockList()
{
}

void CBuySellStockList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuySellStockList)
	DDX_Control(pDX, IDC_BUTTON_TO_EXCEL, m_xbt);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBuySellStockList, CFormView)
	//{{AFX_MSG_MAP(CBuySellStockList)
	ON_BN_CLICKED(IDC_BUTTON_TO_EXCEL, OnButtonToExcel)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuySellStockList diagnostics

#ifdef _DEBUG
void CBuySellStockList::AssertValid() const
{
	CFormView::AssertValid();
}

void CBuySellStockList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBuySellStockList message handlers

void CBuySellStockList::OnDraw(CDC* pDC) 
{
	CRect r1,r2,rectTitle,rectButton;
	long titleHigh,buttonHigh;

	GetClientRect(&r2);
	GetDlgItem(IDC_STATIC_TITLE)->GetWindowRect(rectTitle);
	ScreenToClient(rectTitle);
	rectTitle.right=r2.right;
	rectTitle.left= r2.left;
	titleHigh=rectTitle.bottom-rectTitle.top;
	rectTitle.top=  r2.top;
	rectTitle.bottom = r2.top+ titleHigh;
	GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(0,0,r2.right-r2.left,titleHigh);

	GetDlgItem(IDC_BUTTON_TO_EXCEL)->GetWindowRect(rectButton);
	ScreenToClient(rectButton);
	buttonHigh=rectButton.bottom-rectButton.top;
	rectButton.top = r2.bottom - buttonHigh;
	rectButton.right =r2.right;
	rectButton.left =0 ;
	rectButton.bottom = r2.bottom ;
	GetDlgItem(IDC_BUTTON_TO_EXCEL)->MoveWindow(0,r2.bottom-buttonHigh,r2.right,buttonHigh);


	GetDlgItem(IDC_MSHFLEXGRID1)->GetWindowRect(&r1);
	ScreenToClient(&r1);
	GetDlgItem(IDC_MSHFLEXGRID1)->MoveWindow(0,r2.top+titleHigh,r2.right,r2.bottom-titleHigh-buttonHigh);
		
	
}

BEGIN_EVENTSINK_MAP(CBuySellStockList, CFormView)
    //{{AFX_EVENTSINK_MAP(CBuySellStockList)
	ON_EVENT(CBuySellStockList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CBuySellStockList::OnDblClickMshflexgrid1() 
{
	// TODO: Add your control notification handler code here
	CBuySellStockQuery query;
	theApp.pParentGrid.pWnd=this;
	query.DoModal();
	
}

void CBuySellStockList::OnButtonToExcel() 
{
	// TODO: Add your control notification handler code here
	extern void ToExcel(CMSHFlexGrid * pg);
	if( MessageBox("是否确定要导出到 Excel 表格 ??? ","提示",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;

	ToExcel(&m_grid);
	
}

void CBuySellStockList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	CString strTitle="药品( 进销存 )明细表";

	theApp.hBuySellStock=GetParentFrame()->m_hWnd;
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle(strTitle);

	SetGridHead();
	// TODO: Add your specialized code here and/or call the base class
	
}

void CBuySellStockList::SetGridHead()
{
	CString HeadTitle[]={"编号","药品编码","药品名称","规格","单位",\
		"上期库存","当前购进","当前消耗","当前库存","盘点数量","盈亏数量","修改数量"}; 
	//共 18 列
	
	long  headWidth[]={800,900,1200,1000,500,1000,1000,1000,1000,1000,1000,\
		1000,1200,1200,1000,1400,1400,1400,1400,1400};
	
	
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0,col(0),row(0);
	m_grid.SetRow(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
	
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐

		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
	m_grid.SetColAlignment(0,4);
}

void CBuySellStockList::OnDestroy() 
{
	CFormView::OnDestroy();
	
	theApp.pBuySellStock=NULL;	
}
