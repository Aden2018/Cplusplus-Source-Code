// PandianList.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "PandianList.h"
#include "PandianQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPandianList

IMPLEMENT_DYNCREATE(CPandianList, CFormView)

CPandianList::CPandianList()
	: CFormView(CPandianList::IDD)
{
	//{{AFX_DATA_INIT(CPandianList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"����");
}

CPandianList::~CPandianList()
{
}

void CPandianList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPandianList)
	DDX_Control(pDX, IDC_BUTTON_TO_EXCEL, m_f);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPandianList, CFormView)
	//{{AFX_MSG_MAP(CPandianList)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_TO_EXCEL, OnButtonToExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPandianList diagnostics

#ifdef _DEBUG
void CPandianList::AssertValid() const
{
	CFormView::AssertValid();
}

void CPandianList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPandianList message handlers

void CPandianList::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
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

void CPandianList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	theApp.hPDList=GetParentFrame()->m_hWnd;
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("��ӯ �̿���ϸ��");
	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle("��ӯ���̿���");
	SetGridHead();
	// TODO: Add your specialized code here and/or call the base class
	
}

void CPandianList::SetGridHead()
{
	CString HeadTitle[]={"DAN","����","�ⷿ","����Ա","ҩƷ����","���","��λ","������","��Ч��",\
		"����","ӯ����","����","ӯ����"}; 

	long  headWidth[]={0,1200,1200,1200,1600,1400,600,1200,1200,1400,1200,\
		1000,1200,1000,1000,1400,1400,1400,1400,1400};
	
	
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<5)m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����кϲ�
	//	if(count<4)m_grid.SetColAlignment(i,1);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //���ж���
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
}

void CPandianList::OnDestroy() 
{
	CFormView::OnDestroy();
	
	theApp.pPDList=NULL;	
}

BEGIN_EVENTSINK_MAP(CPandianList, CFormView)
    //{{AFX_EVENTSINK_MAP(CPandianList)
	ON_EVENT(CPandianList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CPandianList::OnDblClickMshflexgrid1() 
{
	CPandianQuery query;
	theApp.pParentGrid.pWnd=this;
	query.DoModal();
	
}

HBRUSH CPandianList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd )
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH) theApp.titleBrush.GetSafeHandle();


	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CPandianList::OnButtonToExcel() 
{
	extern void ToExcel(CMSHFlexGrid * pg);
	if( MessageBox("�Ƿ�ȷ��Ҫ������ Excel ��� ??? ","��ʾ",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	ToExcel(&m_grid);
	// TODO: Add your control notification handler code here
	
}
