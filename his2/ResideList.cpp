// ResideList.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "ResideList.h"
#include "residelistQuery.h"
#include "ResideUseMedquery.h"
#include "resideAddPrice.h"
#include "residePriceQuery.h"
#include "startDoctor.h"
#include "resideCheckOut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResideList

IMPLEMENT_DYNCREATE(CResideList, CFormView)

CResideList::CResideList()
	: CFormView(CResideList::IDD)
{
	//{{AFX_DATA_INIT(CResideList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	curRow=0;
	fontTitle.CreatePointFont(220,"姚体");
}

CResideList::~CResideList()
{
}

void CResideList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResideList)
	DDX_Control(pDX, IDC_BUTTON_TO_EXCEL, m_button);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResideList, CFormView)
	//{{AFX_MSG_MAP(CResideList)
	ON_WM_DESTROY()
	ON_COMMAND(ID_MENU_QUICK_RESIDE_MEDQUERY, OnMenuQuickResideMedquery)
	ON_COMMAND(ID_MENU_RESIDE_ADD_PRICE, OnMenuResideAddPrice)
	ON_COMMAND(ID_MENU_RESIDE_PRICEQUERY, OnMenuResidePricequery)
	ON_COMMAND(ID_MENU_RESIDE_HUAJIA, OnMenuResideHuajia)
	ON_COMMAND(ID_MENU_RESIDE_DELETE, OnMenuResideDelete)
	ON_COMMAND(ID_MENU_RESIDE_USEMED, OnMenuResideHuajia)
	ON_COMMAND(ID_MENU_RESIDE_CHECKOUT, OnMenuResideCheckout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResideList diagnostics

#ifdef _DEBUG
void CResideList::AssertValid() const
{
	CFormView::AssertValid();
}

void CResideList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResideList message handlers

void CResideList::OnDraw(CDC* pDC) 
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

void CResideList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	theApp.hResideList=GetParentFrame()->m_hWnd;
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	const CString strcon="住院人员列表";
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strcon);
	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle(strcon);

	SetGridHead();
		
}

void CResideList::OnDestroy() 
{
	CFormView::OnDestroy();
	
	theApp.pResideList=NULL;	
}

void CResideList::SetGridHead()
{
	CString HeadTitle[]={"序号","s1","姓名","性别","年龄","电话","工作单位","家庭住址","病情描述","医生",\
		"住院日期","床位","住院金余额","登记员","出院日期"}; //共 15 列

	long  headWidth[]={600,00,800,400,600,1600,2000,2000,2000,1200,1900,1600,1200,800,1800};
	
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0,col(0),row(0);
	m_grid.SetRow(0);
	m_grid.SetBackColor(RGB(255,255,255));
	m_grid.SetForeColor(RGB(0,0,0));
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
	//	if( count < 9 && count !=2) m_grid.SetColAlignment(long(count),short(4));
	//	if( count >3 && count < 9 ) m_grid.SetMergeCol(long(count),true);
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
	m_grid.SetMergeCol(1,true);
}

BEGIN_EVENTSINK_MAP(CResideList, CFormView)
    //{{AFX_EVENTSINK_MAP(CResideList)
	ON_EVENT(CResideList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CResideList, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CResideList::OnDblClickMshflexgrid1() 
{
	theApp.pParentGrid.pGrid=this;
	CResideListQuery rq;
	rq.DoModal();

}

void CResideList::OnClickMshflexgrid1() 
{
	const int ENDLINES=2;
	const int COLS=4;
	if(m_grid.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		
		long r1;
		r1=m_grid.GetRow();
		if(r1>=m_grid.GetRows()-1 || curRow== r1)return;
		
		m_grid.SetCol(8);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();
		
		for(int i=2;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
		m_grid.SetRow(r1);
		curRow=r1;
		for( i=2;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_MEDLIST);
	CMenu* pmenu=pm.GetSubMenu(7); // 住院人员菜单
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  
	
}

void CResideList::OnMenuQuickResideMedquery()  //药品查询
{
//	CString HeadTitle[]={"序号","s1","姓名","性别","年龄","电话","工作单位","家庭住址","病情描述","医生",\
		"日期","床位","住院金余额","登记员"}; //共 24 列
	long curRow=m_grid.GetRow();
	CResideUseMedQuery mq;
	mq.strTitle=m_grid.GetTextMatrix(curRow,2)+"/"+m_grid.GetTextMatrix(curRow,3)+"/"+m_grid.GetTextMatrix(\
		curRow,4)+"/"+m_grid.GetTextMatrix(curRow,8)+"----用药情况";
	mq.strSerial=m_grid.GetTextMatrix(curRow,1);
	mq.DoModal();
}

void CResideList::OnMenuResideAddPrice()  //补交住院款
{
	if( ! CheckStatus() ) return;

	CResideAddPrice ap;
	ap.pGrid=&m_grid;
	ap.DoModal();
}

void CResideList::OnMenuResidePricequery() //住院款查询
{
	long curRow=m_grid.GetRow();

	CResidePriceQuery pq;

	pq.strTitle=m_grid.GetTextMatrix(curRow,2)+"/"+m_grid.GetTextMatrix(curRow,3)+"/"+m_grid.GetTextMatrix(\
		curRow,4)+"/"+m_grid.GetTextMatrix(curRow,8)+"----交款情况";
	pq.strSerial=m_grid.GetTextMatrix(curRow,1);

	pq.DoModal();
}

void CResideList::OnMenuResideHuajia()  //住院划价
{

	CStartDoctor sd;
	sd.m_curTabSel=1; //设定划价单最上
	sd.m_startDate=m_grid.GetTextMatrix(m_grid.GetRow(),10);
	sd.DoModal();
}



void CResideList::OnMenuResideDelete() //住院人员删除
{
	if( ! CheckStatus() ) return;

	long curRow=m_grid.GetRow();
	if ( MessageBox("确定要删除吗","删除提示",MB_OKCANCEL|MB_ICONINFORMATION ) == IDCANCEL ) return;
	
	CString m_strSerial=m_grid.GetTextMatrix(curRow,1);  //待删除人员编码

	_CommandPtr cmd;
	_ParameterPtr par;
	cmd.CreateInstance(__uuidof( Command ));
	par.CreateInstance(__uuidof( Parameter));

	_variant_t vNULL;
	vNULL.vt = VT_ERROR;
	vNULL.scode = DISP_E_PARAMNOTFOUND;
	int succ=0;
	const int SUCCESS=0,FAIL=1;
	try{
		cmd->put_CommandType(adCmdStoredProc) ;
	
		par=cmd->CreateParameter(_bstr_t("succ"),adInteger,adParamOutput,0,vNULL);
		cmd->Parameters->Append( par ); //成功标志
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(m_strSerial),_bstr_t(m_strSerial));
		cmd->Parameters->Append(par ); //待删除人员编码
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(LoginInformation.user_code),_bstr_t(LoginInformation.user_code));
		cmd->Parameters->Append(par ); //操作编码
		par=cmd->CreateParameter(_bstr_t("strBm"),adBSTR,adParamInput,sizeof(LoginInformation.user),_bstr_t(LoginInformation.user)) ;
		cmd->Parameters->Append(par ); //操作名称


		cmd->put_CommandText(_bstr_t("prc_Reside_Delete "));
		cmd->ActiveConnection=HospitalConnect;
		cmd->Execute(NULL,NULL,adCmdStoredProc);
		
		succ=(long)cmd->Parameters->GetItem("succ")->Value;

		cmd.Detach();
		par.Detach();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description() );
		return;
	}	
	if( succ == SUCCESS ) AfxMessageBox("成功删除");
	else AfxMessageBox("删除失败");
}

void CResideList::OnMenuResideCheckout() //出院操作
{
	if( ! CheckStatus() ) return;
	CResideCheckOut co;
	co.pGrid=&m_grid;
	co.DoModal();

}

BOOL CResideList::CheckStatus() //检测当前人员是否已经出院
{
	if( ! m_grid.GetTextMatrix(m_grid.GetRow() ,14).IsEmpty() ) {
		AfxMessageBox("已经出院,请不要再操作");
		return false;
	}

	return true;
	
}
