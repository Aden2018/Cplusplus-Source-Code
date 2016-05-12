// FormRkList.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "FormRkList.h"
#include "FormRkListQuery.h"
#include "qiuxpbutton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormRkList

IMPLEMENT_DYNCREATE(CFormRkList, CFormView)

CFormRkList::CFormRkList()
	: CFormView(CFormRkList::IDD)
{
	//{{AFX_DATA_INIT(CFormRkList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"����");
}

CFormRkList::~CFormRkList()
{
}

void CFormRkList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormRkList)
	DDX_Control(pDX, IDC_BUTTON_TO_EXCEL, c_button_to_excel);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormRkList, CFormView)
	//{{AFX_MSG_MAP(CFormRkList)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_TO_EXCEL, OnButtonToExcel)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormRkList diagnostics

#ifdef _DEBUG
void CFormRkList::AssertValid() const
{
	CFormView::AssertValid();
}

void CFormRkList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormRkList message handlers

void CFormRkList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	theApp.hRkList=GetParentFrame()->m_hWnd;

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("ҽԺҩƷ�ɹ������ϸ��");
	GetDocument()->SetTitle("ҽԺҩƷ�ɹ�����б�");

	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
//	ResizeParentToFit();
	
	SetGridHead();
	
	
}

void CFormRkList::SetGridHead()
{
/*	CString HeadTitle[]={"DAN","����","��Ʊ��","��Ӧ��","ҵ��Ա","���Ա","ҩƷ����","���","��λ","������","��Ч��",\
		"����","������","����","�ۼ�","ָ����","������","���ܶ�","���ܶ�"}; 
	//�� 18 ��
*/
	
	CString HeadTitle[]={"DAN","�������","��Ʊ��","��Ӧ��","ҵ��Ա","���Ա","ҩƷ����","���","��λ","������","��Ч��",\
		"����","������","������","������","���ۼ�","���ܶ�","���ܶ�","���۶�","������"}; 

	long  headWidth[]={0,1200,1000,1400,800,800,1600,1400,400,0,1200,\
		1000,1000,1000,1000,1200,1200,1200,1200,1200};
	
	
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
//	m_grid.SetMergeCol(15,true);
}

void CFormRkList::OnDraw(CDC* pDC) 
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

BEGIN_EVENTSINK_MAP(CFormRkList, CFormView)
    //{{AFX_EVENTSINK_MAP(CFormRkList)
	ON_EVENT(CFormRkList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CFormRkList::OnDblClickMshflexgrid1() 
{
	// TODO: Add your control notification handler code here
	CFormRkListQuery query;
	theApp.pParentGrid.pWnd=this;
	query.DoModal();
}

void CFormRkList::OnDestroy() 
{
	CFormView::OnDestroy();
	
	theApp.pRkList=NULL;	
}

void CFormRkList::OnButtonToExcel() 
{
	extern void ToExcel(CMSHFlexGrid * pg);
	if( MessageBox("�Ƿ�ȷ��Ҫ������ Excel ��� ??? ","��ʾ",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	ToExcel(&m_grid);
}

HBRUSH CFormRkList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd)
		pDC->SetTextColor(RGB(0,70,140));
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
