// EverydayConsumeList.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "EverydayConsumeList.h"
//#include "FormZkListQuery.h"
#include "EverydayConsumeQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEverydayConsumeList

IMPLEMENT_DYNCREATE(CEverydayConsumeList, CFormView)

CEverydayConsumeList::CEverydayConsumeList()
	: CFormView(CEverydayConsumeList::IDD)
{
	//{{AFX_DATA_INIT(CEverydayConsumeList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"黑体");
}

CEverydayConsumeList::~CEverydayConsumeList()
{
}

void CEverydayConsumeList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEverydayConsumeList)
	DDX_Control(pDX, IDC_BUTTON_TO_EXCEL, m_234);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEverydayConsumeList, CFormView)
	//{{AFX_MSG_MAP(CEverydayConsumeList)
	ON_BN_CLICKED(IDC_BUTTON_TO_EXCEL, OnButtonToExcel)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_EN_KILLFOCUS(T_EDIT1,OnKillEditCtrl)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEverydayConsumeList diagnostics

#ifdef _DEBUG
void CEverydayConsumeList::AssertValid() const
{
	CFormView::AssertValid();
}

void CEverydayConsumeList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEverydayConsumeList message handlers

void CEverydayConsumeList::OnDraw(CDC* pDC) 
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

void CEverydayConsumeList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	theApp.hConsume=GetParentFrame()->m_hWnd;
	const CString title="药品日消耗明细表";
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(title);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle(title);

	CString strSql;
	try{
		strSql.Format("select kfbm,kfmc from storeroom where med='1' ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
		
			strSql=(char*)_bstr_t(recSet->GetCollect("kfbm").vt==VT_NULL?" ":recSet->GetCollect("kfbm"));
		//	if( strSql == LoginInformation.kfbm ) goto CONTINUE;
			strBm.Add(strSql);
			
			strSql=(char*)_bstr_t(recSet->GetCollect("kfmc").vt==VT_NULL?" ":recSet->GetCollect("kfmc"));
			strMc.Add(strSql);

//		CONTINUE:
			recSet->MoveNext();
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return ;
	}

	SetGridHead();

	fontMoveEdit.CreatePointFont(90,"宋体");
	CRect r1(0,0,0,0);
	editCtrl.Create(WS_CHILD,r1,this,T_EDIT1);
	editCtrl.SetFont(&fontMoveEdit);
	
}

void CEverydayConsumeList::OnButtonToExcel() 
{
	extern void ToExcel(CMSHFlexGrid * pg);
	if( MessageBox("是否确定要导出到 Excel 表格 ??? ","提示",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;

	ToExcel(&m_grid);
	
}

BEGIN_EVENTSINK_MAP(CEverydayConsumeList, CFormView)
    //{{AFX_EVENTSINK_MAP(CEverydayConsumeList)
	ON_EVENT(CEverydayConsumeList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CEverydayConsumeList::OnDblClickMshflexgrid1() 
{
	long lastCol=m_grid.GetCols(0) -1 ;

	if( lastCol != m_grid.GetCol() ){
	
		CEverydayConsumeQuery query;
		theApp.pParentGrid.pWnd=this;
		query.DoModal();
		return;
	}

	if(m_grid.GetRow()==m_grid.GetRows()-1 )return;

	CDC *pCdcGrid=m_grid.GetDC();
	int nWidth=pCdcGrid->GetDeviceCaps(LOGPIXELSX);
	int nHigh=pCdcGrid->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pCdcGrid);

	long	row=m_grid.GetRow();
	long 	col=m_grid.GetCol();
	CString str2;
	CString	strOrigin=m_grid.GetTextMatrix(row,col);

	long left=m_grid.GetCellLeft();
	long top=m_grid.GetCellTop();
	long right=m_grid.GetCellWidth();
	long bottom=m_grid.GetCellHeight();

	CRect rectGrid,r2;
	m_grid.GetWindowRect(rectGrid);
	ScreenToClient(rectGrid);
	rectGrid.left+=left*nWidth/1440-1;
	rectGrid.top+=top*nHigh/1440-1;
	rectGrid.right=right*nWidth/1440+rectGrid.left;
	rectGrid.bottom=bottom*nHigh/1440+rectGrid.top;


	editCtrl.MoveWindow(rectGrid);
	editCtrl.ShowWindow(SW_SHOW);
	editCtrl.SetFocus();
	editCtrl.SetWindowText(strOrigin);
	editCtrl.SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	editCtrl.SetSel(0,strOrigin.GetLength());
	
}

void CEverydayConsumeList::SetGridHead()
{
	CString HeadTitle[]={"编号","药品编码","药品名称","规格","单位","消耗量",\
		"库存量"}; 
	//共 18 列
	
	long  headWidth[]={1200,1400,1600,1400,700,1200,1200,0,00,00,00,\
		000,00,00,00,00,00,00,00,00};
	
	
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString) + strBm.GetSize()+1 );
	m_grid.SetFixedCols(0);
	long  i=0,col(0),row(0);
	m_grid.SetRow(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString) +strBm.GetSize() ;count++){
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		
		if ( count >= sizeof(HeadTitle)/sizeof(CString) ){
			m_grid.SetColWidth(i,1200);
				
			m_grid.SetTextArray(i++,strMc.GetAt( count -sizeof(HeadTitle)/sizeof(CString) ));
		}
		else {
	
			
			m_grid.SetColWidth(i,headWidth[count]);
			
			
			m_grid.SetTextArray(i++,HeadTitle[count]);
		}
		
	}
	m_grid.SetCol((long) i);
	m_grid.SetCellAlignment((short)4); //居中对齐
	m_grid.SetColWidth(i,1400);
	m_grid.SetTextArray(i,"计划取药量");
	m_grid.SetColAlignment(0,4);

}

HBRUSH CEverydayConsumeList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd ) 
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,70,140));
		pDC->SetBkColor(RGB(255,255,255));
	}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}



void CEverydayConsumeList::OnDestroy() 
{
	CFormView::OnDestroy();
	
	theApp.pConsume=NULL;	
}

void CEverydayConsumeList::OnKillEditCtrl()
{
	CString str1;
	long dt;
	editCtrl.GetWindowText(str1);
	dt=atol(str1);
	str1.Format("%ld",dt);
	m_grid.SetTextMatrix(m_grid.GetRow(),m_grid.GetCol(),str1);
	editCtrl.ShowWindow(SW_HIDE);

}

BOOL CEverydayConsumeList::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		if(GetFocus()->m_hWnd == GetDlgItem(T_EDIT1)->m_hWnd){
			OnKillEditCtrl();
			if( m_grid.GetRows()-1 > m_grid.GetRow() ){
				m_grid.SetRow(m_grid.GetRow()+1);
				OnDblClickMshflexgrid1();
			}
			return true;

		}
	
	return CFormView::PreTranslateMessage(pMsg);


}