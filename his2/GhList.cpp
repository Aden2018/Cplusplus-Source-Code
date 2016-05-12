// GhList.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "GhList.h"
#include "dialogGhQuery.h"
#include "userMed.h"
#include "rollMed.h"
#include "qiuXpbutton.h"
#include "progressIndicate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGhList

IMPLEMENT_DYNCREATE(CGhList, CFormView)

CGhList::CGhList()
	: CFormView(CGhList::IDD)
{
	//{{AFX_DATA_INIT(CGhList)
	//}}AFX_DATA_INIT
	curRow=0;
	fontTitle.CreatePointFont(220,"姚体");
}

CGhList::~CGhList()
{
}

void CGhList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGhList)
	DDX_Control(pDX, IDC_BUTTON_TO_EXCEL, m_t);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGhList, CFormView)
	//{{AFX_MSG_MAP(CGhList)
	ON_WM_DESTROY()
	ON_COMMAND(ID_QM_USER_ROLLMED, OnQmUserRollmed)
	ON_COMMAND(ID_QM_USER_MED, OnQmUserMed)
	ON_COMMAND(ID_MENU_CURE_DETAIL, OnMenuCureDetail)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_TO_EXCEL, OnButtonToExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGhList diagnostics

#ifdef _DEBUG
void CGhList::AssertValid() const
{
	CFormView::AssertValid();
}

void CGhList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGhList message handlers

void CGhList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	theApp.hGhList=GetParentFrame()->m_hWnd;
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	const CString strcon="医院门诊就诊单明细表";
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strcon);
	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle(strcon);
	// TODO: Add your specialized code here and/or call the base class
	SetGridHead();
	
}

void CGhList::OnDestroy() 
{
	CFormView::OnDestroy();

	theApp.pGhList= NULL;
	
	
}

void CGhList::OnDraw(CDC* pDC) 
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

void CGhList::SetGridHead()
{
	CString HeadTitle[]={"DAN","就诊日期","个人编码","病人姓名","医生","划价员","收费员",\
		"发药员","挂号类别","挂号费","现金","药品零售额","其它费用","合计","药品利润",\
		"药品购进额","手术费","化验费","B 超费","心电费","理疗费","推拿费",\
		"口腔费","妇检费"}; //共 24 列

	long  headWidth[]={0,1200,1400,800,800,800,800,800,1000,00,1200,\
		1200,1200,1200,1200,1200,00,00,00,00,00,00,00,00};
	
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
		if( count < 9 && count !=2) m_grid.SetColAlignment(long(count),short(4));
		if( count >3 && count < 9 ) m_grid.SetMergeCol(long(count),true);
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
	m_grid.SetMergeCol(1,true);
}


BEGIN_EVENTSINK_MAP(CGhList, CFormView)
    //{{AFX_EVENTSINK_MAP(CHuaJiaList)
	ON_EVENT(CGhList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CGhList, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CGhList::OnDblClickMshflexgrid1()
{
//	AfxMessageBox("OK...");
	theApp.pParentGrid.pGrid=this;
	CDialogGhQuery gh;
	gh.DoModal();


}

const long COLS=4;
void CGhList::OnClickMshflexgrid1() 
{
	const int ENDLINES=2;
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
	CMenu* pmenu=pm.GetSubMenu(1);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  
	// TODO: Add your control notification handler code here
	
}

void CGhList::OnQmUserRollmed() //用户退药
{
//	"DAN","日期","BM","病人姓名","挂号员","划价员","收费员","发药员","挂号类别","挂号费","现金","药品费","治疗费","利润","合计"}; //共 13 列
//    0      1     2      3          4        5         6      7         8          9        10     11         12     13  

	CRollMed roll;
	roll.str2[1]=m_grid.GetTextMatrix(curRow,3);//姓名
	roll.str2[2]=m_grid.GetTextMatrix(curRow,2); //编码
	roll.str2[3]=m_grid.GetTextMatrix(curRow,8);//挂号类型
	roll.str2[4]=m_grid.GetTextMatrix(curRow,1);//日期
	roll.str2[5]=m_grid.GetTextMatrix(curRow,0);//单据号

	
	roll.DoModal();

}

void CGhList::OnQmUserMed()  //用户用药列表
{
 	CUserMed userMed;

	userMed.str2[1]=m_grid.GetTextMatrix(curRow,3);//病人姓名
	userMed.str2[2]=m_grid.GetTextMatrix(curRow,2);//编码
	userMed.str2[3]=m_grid.GetTextMatrix(curRow,8);//挂号类别
	userMed.str2[4]=m_grid.GetTextMatrix(curRow,1);//日期
	userMed.str2[5]=m_grid.GetTextMatrix(curRow,0);//单据号

	userMed.str2[6]=m_grid.GetTextMatrix(curRow,4);//挂号员
	userMed.str2[7]=m_grid.GetTextMatrix(curRow,5);//划价员
	userMed.str2[8]=m_grid.GetTextMatrix(curRow,7);//发药员
	
	userMed.dbCash= atof(m_grid.GetTextMatrix(curRow,10))  ; //现金支付
	userMed.dbAccount=atof(m_grid.GetTextMatrix(curRow,13))-userMed.dbCash;
	userMed.DoModal();

	

}

void CGhList::OnMenuCureDetail()  //查询治疗单详情
{
	CProgressIndicate pq;

	pq.m_progress.strView="请稍候,系统正在处理治疗明细...";
	pq.pDialog=& m_grid;
	pq.pThreadFunction = CureDetailProcess;

	pq.DoModal();

}



HBRUSH CGhList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd )
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH) theApp.titleBrush.GetSafeHandle();


	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CGhList::OnButtonToExcel() 
{
	extern void ToExcel(CMSHFlexGrid * pg);
	if( MessageBox("是否确定要导出到 Excel 表格 ??? ","提示",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	ToExcel(&m_grid);
	
}

UINT CGhList::CureDetailProcess(LPVOID ps)
{
// OLD	"化验检查","辅助检查","口腔科","门诊手术","理疗","护理","妇科"}; //共 22 列
//	NEW	"治疗费","手术费","化验费","B 超费","心电费","理疗费","推拿费",
//		"口腔费","妇检费"}; //共 24 列
	CMSHFlexGrid * pg=(CMSHFlexGrid *)((CProgressIndicate *) ps )->pDialog;

	const int  BASE_CURE_COLS=15;
	CString strSql,strDanjuhao,str1,str2;
	long rows=pg->GetRows(),CureCol=0;
	double add[9]={0,0,0,0,0,0,0,0,0},dd;

	try{
		for(long i=1;i<rows-1 ;i++)
		{
			strDanjuhao=pg->GetTextMatrix(i,0); 
			strSql.Format("SELECT b.费用大类,sum(NVL(a.dj,0)) \
					FROM ITEMREGISTERTIZL a,费用项目表 b WHERE a.ZLMC=b.费用编码 AND \
					a.DANJUHAO='%s' GROUP BY b.费用大类 ",strDanjuhao );
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			while(!recSet->adoEOF){
					str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(0L))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(0L))->Value);
					str2=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(1L))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(1L))->Value);
		
		/*			if(str1 == "化验检查" )CureCol=0;
					else if(str1== "辅助检查")CureCol=1;
					else if(str1== "口腔科")CureCol=2;
					else if(str1== "门诊手术")CureCol=3;
					else if(str1=="理疗")CureCol=4;
					else if(str1=="护理")CureCol=5;
					else if(str1=="妇科")CureCol=6;
*/			
					
					if(str1 == "治疗费" )CureCol=0;
					else if(str1== "手术费")CureCol=1;
					else if(str1=="化验费")CureCol=2;
					else if(str1=="B 超费")CureCol=3;
					else if(str1=="心电费")CureCol=4;

					else if(str1== "理疗费")CureCol=5;
					else if(str1== "推拿费")CureCol=6;
					else if(str1=="口腔费")CureCol=7;
					else if(str1=="妇检费")CureCol=8;
				
					dd=atof(str2);
					str2.Format("%.2f",dd);
					pg->SetTextMatrix(i,CureCol+BASE_CURE_COLS,str2);
					add[CureCol]+=atof(str2);
					recSet->MoveNext();

				
				}
			
				recSet->Close();
		}
		for(i=BASE_CURE_COLS;i<24;i++){
			strSql.Format("%.2f",add[i-BASE_CURE_COLS]);
			pg->SetTextMatrix(rows-1,i,strSql);

		}
	}catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}

	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);


}
