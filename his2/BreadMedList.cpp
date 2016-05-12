// BreadMedList.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "BreadMedList.h"
#include "breadMedQuery.h"
#include "qiuXpButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBreadMedList

IMPLEMENT_DYNCREATE(CBreadMedList, CFormView)

CBreadMedList::CBreadMedList()
	: CFormView(CBreadMedList::IDD)
{
	//{{AFX_DATA_INIT(CBreadMedList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"黑体");
}

CBreadMedList::~CBreadMedList()
{
}

void CBreadMedList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBreadMedList)
	DDX_Control(pDX, IDC_BUTTON_TO_EXCEL, m_f);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBreadMedList, CFormView)
	//{{AFX_MSG_MAP(CBreadMedList)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_TO_EXCEL, OnButtonToExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBreadMedList diagnostics

#ifdef _DEBUG
void CBreadMedList::AssertValid() const
{
	CFormView::AssertValid();
}

void CBreadMedList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBreadMedList message handlers

void CBreadMedList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	theApp.hBMList=GetParentFrame()->m_hWnd;
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("报损 过期等药品明细表");

	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle("报损药品情况一览表");
	SetGridHead();
	
}

void CBreadMedList::SetGridHead()
{
	CString HeadTitle[]={"DAN","报损日期","库房","操作员","编码","药品名称","规格","单位","生产期","有效期",\
		"产地","进价","报损量","损耗额","备注"}; 

	long  headWidth[]={0,1200,1000,1000,900,1400,1200,400,1200,1200,1200,1000,\
		1000,1000,1200,1000,1400,1400,1400,1400,1400};
	
	
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<5)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
	//	if(count<4)m_grid.SetColAlignment(i,1);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
}

void CBreadMedList::OnDestroy() 
{
	CFormView::OnDestroy();
	
	theApp.pBMList=NULL;	
}

void CBreadMedList::OnDraw(CDC* pDC) 
{
/*	CRect r1,r2;
	GetClientRect(&r2);


	GetDlgItem(IDC_MSHFLEXGRID1)->GetWindowRect(&r1);
	ScreenToClient(&r1);
	GetDlgItem(IDC_MSHFLEXGRID1)->MoveWindow(0,0,r2.right,r2.bottom);
*/
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

BEGIN_EVENTSINK_MAP(CBreadMedList, CFormView)
    //{{AFX_EVENTSINK_MAP(CBreadMedList)
	ON_EVENT(CBreadMedList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CBreadMedList::OnDblClickMshflexgrid1() 
{
	CBreadMedQuery query;
	theApp.pParentGrid.pWnd=this;
	query.DoModal();
	
}

void CBreadMedList::OnButtonToExcel() 
{
	extern void ToExcel(CMSHFlexGrid * pg);
	if( MessageBox("是否确定要导出到 Excel 表格 ??? ","提示",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	ToExcel(&m_grid);
	
}
