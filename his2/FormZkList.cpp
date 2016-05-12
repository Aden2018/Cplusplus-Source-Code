// FormZkList.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "FormZkList.h"
#include "formZkListQuery.h"
#include "qiuXpButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormZkList

IMPLEMENT_DYNCREATE(CFormZkList, CFormView)

CFormZkList::CFormZkList()
	: CFormView(CFormZkList::IDD)
{
	//{{AFX_DATA_INIT(CFormZkList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"宋体");
}

CFormZkList::~CFormZkList()
{
}

void CFormZkList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormZkList)
	DDX_Control(pDX, IDC_BUTTON_TO_EXCEL, m_d);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormZkList, CFormView)
	//{{AFX_MSG_MAP(CFormZkList)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_TO_EXCEL, OnButtonToExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormZkList diagnostics

#ifdef _DEBUG
void CFormZkList::AssertValid() const
{
	CFormView::AssertValid();
}

void CFormZkList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormZkList message handlers

void CFormZkList::OnDestroy() 
{
	CFormView::OnDestroy();
	
	theApp.pZkList=NULL;	
	// TODO: Add your message handler code here
	
}

void CFormZkList::OnDraw(CDC* pDC) 
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

void CFormZkList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	theApp.hZkList=GetParentFrame()->m_hWnd;
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("医院药品转库明细表");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle("药品转库列表");
	SetGridHead();
	// TODO: Add your specialized code here and/or call the base class
	
}

void CFormZkList::SetGridHead()
{
	CString HeadTitle[]={"DAN","转库日期","始库房","发药员","终库房","领用员","编 码","药品名称","规格","单位","生产期","有效期",\
		"产地","转库量","购进价","转库金额"}; 
	//共 18 列
	
	long  headWidth[]={0,1200,800,800,800,800,900,1400,1200,400,1200,1200,\
		1200,1000,1000,1000,1400,1400,1400,1400,1400};
	
	
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0,col(0),row(0);
	m_grid.SetRow(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<6)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
	//	if(count<4)m_grid.SetColAlignment(i,1);
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐

		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
}

BEGIN_EVENTSINK_MAP(CFormZkList, CFormView)
    //{{AFX_EVENTSINK_MAP(CFormZkList)
	ON_EVENT(CFormZkList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CFormZkList::OnDblClickMshflexgrid1() 
{
	CFormZkListQuery query;
	theApp.pParentGrid.pWnd=this;
	query.DoModal();
	
}

HBRUSH CFormZkList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd)
		pDC->SetTextColor(RGB(0,70,140));
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CFormZkList::OnButtonToExcel() 
{
	extern void ToExcel(CMSHFlexGrid * pg);
	if( MessageBox("是否确定要导出到 Excel 表格 ??? ","提示",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	ToExcel(&m_grid);
	
}
