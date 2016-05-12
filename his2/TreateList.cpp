// TreateList.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "TreateList.h"
#include "treateQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreateList

IMPLEMENT_DYNCREATE(CTreateList, CFormView)

CTreateList::CTreateList()
	: CFormView(CTreateList::IDD)
{
	//{{AFX_DATA_INIT(CTreateList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"黑体");

}

CTreateList::~CTreateList()
{
}

void CTreateList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreateList)
	DDX_Control(pDX, IDC_BUTTON_TO_EXCEL, m_x3);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTreateList, CFormView)
	//{{AFX_MSG_MAP(CTreateList)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_TO_EXCEL, OnButtonToExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreateList diagnostics

#ifdef _DEBUG
void CTreateList::AssertValid() const
{
	CFormView::AssertValid();
}

void CTreateList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreateList message handlers

void CTreateList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	

	theApp.hTreateList=GetParentFrame()->m_hWnd;

	const CString strTitle="医院其它收费项目费用明细表";
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDocument()->SetTitle(strTitle);

	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	
	SetGridHead();
	
}

void CTreateList::SetGridHead()
{
//	CString HeadTitle[]={"DAN","日期","姓名","医生","挂号","划价","收费","类型",\
		"治疗费","手术费","化验费","B 超费","心电费","理疗费","推拿费",\
		"口腔费","妇检费","总计"};
	CString HeadTitle[]={"DAN","日期","姓名","医生","挂号","划价","收费","类型",\
		"治疗费","手术费","化验费","B 超费","心电费","理疗费","推拿费",\
		"口腔费","妇检费","眼  科","总计"};

	long  headWidth[]={0,1000,900,900,000,000,000,900,1000,1000,1000,1000,\
		1000,1000,1000,1000,1000,1000,1000,1200,1200,1200};
	
	
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<8){
			m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
			m_grid.SetColAlignment(long(count),(short)4);
		}
	//	if(count<4)m_grid.SetColAlignment(i,1);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}

}

void CTreateList::OnDestroy() 
{
	CFormView::OnDestroy();

	theApp.pTreateList=NULL;	
	
	
}

BEGIN_EVENTSINK_MAP(CTreateList, CFormView)
    //{{AFX_EVENTSINK_MAP(CTreateList)
	ON_EVENT(CTreateList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CTreateList::OnDblClickMshflexgrid1() 
{
	CTreateQuery query;

	theApp.pParentGrid.pWnd=this;
	query.DoModal();
	// TODO: Add your control notification handler code here
	
}

void CTreateList::OnButtonToExcel() 
{
	extern void ToExcel(CMSHFlexGrid * pg);
	if( MessageBox("是否确定要导出到 Excel 表格 ??? ","提示",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	ToExcel(&m_grid);
	// TODO: Add your control notification handler code here
	
}

void CTreateList::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
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
