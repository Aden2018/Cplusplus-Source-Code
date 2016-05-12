// QueryICList.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "QueryICList.h"
#include "queryIc.h"
#include "userMed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueryICList

IMPLEMENT_DYNCREATE(CQueryICList, CFormView)

CQueryICList::CQueryICList()
	: CFormView(CQueryICList::IDD)
{
	//{{AFX_DATA_INIT(CQueryICList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"����");
	curRow=0; 
}

CQueryICList::~CQueryICList()
{
}

void CQueryICList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryICList)
	DDX_Control(pDX, IDC_BUTTON_TO_EXCEL, m_232);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQueryICList, CFormView)
	//{{AFX_MSG_MAP(CQueryICList)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_TO_EXCEL, OnButtonToExcel)
	ON_COMMAND(ID_QM_USER_MED, OnQmUserMed)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryICList diagnostics

#ifdef _DEBUG
void CQueryICList::AssertValid() const
{
	CFormView::AssertValid();
}

void CQueryICList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQueryICList message handlers

void CQueryICList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	const CString str="����ҽ�Ʊ������ﵥ��";

	theApp.hICList=GetParentFrame()->m_hWnd;

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(str);
	GetDocument()->SetTitle(str);

	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
//	ResizeParentToFit();
	
	SetGridHead();
	
}

void CQueryICList::SetGridHead()
{
	CString HeadTitle[]={"���","DAN","����","IC����","����","ҽ��","�Һ�","����","��ҩ","��������",\
		"����","ҩƷ��","��������","�����ܶ�","�ʻ�֧��","�ֽ�֧��","ͳ��֧��","IC֧��","����ǰ�Ϲ���֧��","����Ա����","ҩƷ������"}; 

	long  headWidth[]={1000,0,1200,1400,1000,1000,1000,00,00,900,900,900,900,900,900,\
		900,900,900,900,900,1000,1000,1200,1200,1200,1200,1200};
	
	
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if( count!=3 && count< 10  ){
			m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����кϲ�
			m_grid.SetColAlignment(long(count),short(4));
		}
	//	if(count<4)m_grid.SetColAlignment(i,1);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //���ж���
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
}

void CQueryICList::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	theApp.pICList=NULL;	
	
}

void CQueryICList::OnDraw(CDC* pDC) 
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

void CQueryICList::OnButtonToExcel() 
{
	// TODO: Add your control notification handler code here
	extern void ToExcel(CMSHFlexGrid * pg);
	if( MessageBox("�Ƿ�ȷ��Ҫ������ Excel ��� ??? ","��ʾ",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	ToExcel(&m_grid);
	
}

BEGIN_EVENTSINK_MAP(CQueryICList, CFormView)
    //{{AFX_EVENTSINK_MAP(CQueryICList)
	ON_EVENT(CQueryICList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CQueryICList, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CQueryICList::OnDblClickMshflexgrid1() 
{
	// TODO: Add your control notification handler code here
	CQueryIC query;
	theApp.pParentGrid.pWnd=this;
	query.DoModal();
	
}

void CQueryICList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFormView::OnLButtonDown(nFlags, point);
}

void CQueryICList::OnClickMshflexgrid1()  //��굥����ѡ��
{
	const int ENDLINES=2;
	const int MOUSE_LEFT_KEYDOWN=0x205;
	const int MOUSE_RIGHT_KEYDOWN=0x202;//0x202Ϊ������,0x205Ϊ����Ҽ���Ϣ
	const int START_COL=3; 
	const int END_COL= START_COL+1 ; 
	const COLORREF COLOR_SELECT=RGB(255,0,0);
	if(m_grid.GetRows() == ENDLINES )return;//�ж��Ƿ���Ҫ��ʾ��ݲ˵�

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != MOUSE_LEFT_KEYDOWN ) {
		
		long r1;
		r1=m_grid.GetRow();
		if(r1>=m_grid.GetRows()-1 || curRow== r1)return;
		
		m_grid.SetRow(r1);
		for(int i=START_COL ;i< END_COL;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(COLOR_SELECT );
		}

		m_grid.SetCol(8);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor(); //��ȡԭ��Ԫ����ɫ
		
		for( i= START_COL ;i< END_COL;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
		curRow=r1;
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_MEDLIST);
	CMenu* pmenu=pm.GetSubMenu(1);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  	

}

void CQueryICList::OnQmUserMed()
{
 	CUserMed userMed;
//		CString HeadTitle[]={"���","DAN","����","IC����","����","ҽ��","�Һ�","����","��ҩ","��������",\
	                           0            2               4             6             8               \
		"����","ҩƷ��","��������","�����ܶ�","�ʻ�֧��","�ֽ�֧��","ͳ��֧��","ҩƷ������"}; \
	       10                              


	userMed.str2[1]=m_grid.GetTextMatrix(curRow,4);//��������
	userMed.str2[2]=m_grid.GetTextMatrix(curRow,3);//����
	userMed.str2[3]="IC��"; //�Һ����
	userMed.str2[4]=m_grid.GetTextMatrix(curRow,2);//����
	userMed.str2[5]=m_grid.GetTextMatrix(curRow,1);//���ݺ�

	userMed.str2[6]=m_grid.GetTextMatrix(curRow,6);//�Һ�Ա
	userMed.str2[7]=m_grid.GetTextMatrix(curRow,7);//����Ա
	userMed.str2[8]=m_grid.GetTextMatrix(curRow,8);//��ҩԱ
	userMed.dbAccount=atof(m_grid.GetTextMatrix(curRow,14)); // �ʻ�֧��
	userMed.dbCash=atof(m_grid.GetTextMatrix(curRow,15)); //�ֽ�֧��
	userMed.DoModal();


}
