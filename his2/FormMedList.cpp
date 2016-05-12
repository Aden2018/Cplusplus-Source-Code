// FormMedList.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "FormMedList.h"
#include "DialogMedModify.h"
#include "qiuXpButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormMedList
IMPLEMENT_DYNCREATE(CFormMedList, CFormView)

CFormMedList::CFormMedList()
	: CFormView(CFormMedList::IDD)
{
	//{{AFX_DATA_INIT(CFormMedList)
	//}}AFX_DATA_INIT
	theApp.pParentGrid.p2=this;
	curRow=0;
	fontTitle.CreatePointFont(220,"黑体");

}

CFormMedList::~CFormMedList()
{
	theApp.pParentGrid.pWnd=NULL;
}

void CFormMedList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormMedList)
	DDX_Control(pDX, IDC_BUTTON_TO_EXCEL, m_f);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormMedList, CFormView)
	//{{AFX_MSG_MAP(CFormMedList)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_COMMAND(ID_QM_BAOFEI, OnQmBaofei)
	ON_COMMAND(ID_QM_MODIFY_MED, OnQmModifyMed)
	ON_BN_CLICKED(IDC_BUTTON_TO_EXCEL, OnButtonToExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormMedList diagnostics

#ifdef _DEBUG
void CFormMedList::AssertValid() const
{
	CFormView::AssertValid();

}

void CFormMedList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormMedList message handlers

void CFormMedList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	theApp.hMedlist=GetParentFrame()->m_hWnd;
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("当前库存药品情况明细表");
	GetParentFrame()->ShowWindow(SW_SHOWMAXIMIZED);
	GetDocument()->SetTitle("医院药品列表");
	SetGridHead();
	// TODO: Add your specialized code here and/or call the base class
/*	CString HeadTitle[]={"大类","小类","库房名","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地","库存量","售价","进价","指导价"}; //共 13 列
	
	long  headWidth[]={1400,1400,1400,0,2000,1600,600,0,1400,1600,1000,1000,1000,1000,1000,1000};
	
	
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}	
*/
}

//DEL void CFormMedList::OnOK() 
//DEL {
//DEL 
//DEL 	UpdateData();
//DEL 
//DEL 	CString HeadTitle[]={"大类","小类","药品编码","药品名称","规格","单位","生产期","有效期",\
//DEL 		"产地","库存量","售价","进价","指导价"}; //共 13 列
//DEL 
//DEL 	long  headWidth[]={1400,1400,1400,2000,1600,600,0,1400,1600,1000,1000,1000,1000,1000,1000};
//DEL 
//DEL 	CString getTitle[]={"DLMC","XLMC","BM","MC","GG","DW","RQ1","RQ2","GONGMC","SL",\
//DEL 		"SELL_PRICE","JINJIA","COACH_PRICE"};
//DEL 
//DEL 	m_grid.SetRows(2);
//DEL 	m_grid.Clear();
//DEL 	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
//DEL 	m_grid.SetMergeCells(true); //设定单元格可以进行合并
//DEL 	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
//DEL 	m_grid.SetFixedCols(0);
//DEL 	long  i=0,col(0),row(0);
//DEL 	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
//DEL 		if(count<2)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
//DEL 		m_grid.SetColWidth(i,headWidth[count]);
//DEL 		m_grid.SetTextArray(i++,HeadTitle[count]);
//DEL 		
//DEL 	}		
//DEL 	m_grid.SetRedraw(false);
//DEL 	CString strSql,str1;
//DEL 	try{
//DEL 		//选出药品数量大于0,且不过期的药品
//DEL 		strSql.Format("select * from V_MED_QUERY_DETAIL  ");
//DEL 		
//DEL 		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
//DEL 	
//DEL 		row=1;
//DEL 		while(!recSet->adoEOF){
//DEL 			col=0;
//DEL 			for(i=0;i<sizeof(getTitle)/sizeof(CString);i++)
//DEL 			{
//DEL 				str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(getTitle[i])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(getTitle[i])));
//DEL 				m_grid.SetTextMatrix(row,col++,str1);
//DEL 			}
//DEL 			row++;
//DEL 			m_grid.AddItem(" ",_variant_t(row));
//DEL 			recSet->MoveNext();
//DEL 
//DEL 		}
//DEL 		recSet->Close();
//DEL 		m_grid.SetRedraw(true);
//DEL 	}
//DEL 	catch(_com_error e)
//DEL 	{
//DEL 		AfxMessageBox(strSql);
//DEL 		recSet->Close();
//DEL 		return;
//DEL 	}
//DEL 
//DEL 
//DEL 
//DEL 
//DEL 
//DEL 
//DEL 	
//DEL 
//DEL 
//DEL 
//DEL }

BOOL CFormMedList::PreCreateWindow(CREATESTRUCT& cs) 
{

	return CFormView::PreCreateWindow(cs);
}



void CFormMedList::OnDraw(CDC* pDC) 
{
/*
	CRect r1,r2;
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

HBRUSH CFormMedList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor == CTLCOLOR_STATIC){
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);	
		return (HBRUSH )theApp.titleBrush.GetSafeHandle();	
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}






void CFormMedList::OnDestroy() 
{
	CFormView::OnDestroy();
//	AfxMessageBox("test...");
	theApp.pMedlist= NULL;
	if(theApp.search!=NULL)theApp.search->DestroyWindow();
	delete theApp.search;
	theApp.search= NULL;
}

void CFormMedList::OnDblClickMshflexgrid1()
{
	if(theApp.search != NULL) {
		theApp.search->ShowWindow(SW_SHOW);
		return;
	}

	theApp.search =new CSearchMed;
	theApp.search->Create( IDD_QUERY_MED );
	theApp.search->ShowWindow(SW_SHOW);
	theApp.search->UpdateWindow();

}

BEGIN_EVENTSINK_MAP(CFormMedList, CFormView)
    //{{AFX_EVENTSINK_MAP(CFormMedList)
	ON_EVENT(CFormMedList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CFormMedList, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()
const long COLS=10;
void CFormMedList::OnClickMshflexgrid1() 
{
	// TODO: Add your control notification handler code here
	const int ENDLINES=2;
	if(m_grid.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
/*		long r1;
		r1=m_grid.GetRow();
		if(r1>=m_grid.GetRows()-1 || curRow== r1)return;

		m_grid.SetCol(0);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();
		m_grid.SetColSel(COLS);
		m_grid.SetRowSel(curRow);
		m_grid.SetBackColorSel(color);
/*		for(int i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
*//*		m_grid.SetRow(r1);
		m_grid.SetCol(0);
		m_grid.SetRowSel(r1);
		m_grid.SetColSel(COLS);
		m_grid.SetBackColorSel(RGB(255,0,0));
		curRow=r1;
/*		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
*/		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_MEDLIST);
	CMenu* pmenu=pm.GetSubMenu(0);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  

	
}
/* HeadTitle[]={"ID","KFBM","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地","库存量","售价","进价","指导价","大类","小类","库房名"}; //共 13 列
*/
void CFormMedList::OnQmBaofei()  //报废当前所列药品
{
//	AfxMessageBox("确定要报废当前的药品吗?");	// TODO: Add your command handler code here
/*	if(!theApp.AssertRole(ROLE_MED_BF))return; 

	if(AfxMessageBox("确定要对当前所列药品进行报废操作吗?? 报废后将不可挽回!!!",MB_OKCANCEL)==IDCANCEL)return;
	long rows=m_grid.GetRows()-1;
	UINT id=0;
	CString strDanjuhao,strSql;
	try{
		strSql.Format("select distinct to_char(sysdate,'yyyymmddhh24miss') da from dual" );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			strSql=(char*)_bstr_t (recSet->GetCollect("da"));
			strDanjuhao='B'+strSql+LoginInformation.user_code;
			
		}
		recSet->Close();
	
		HospitalConnect->BeginTrans();

		strSql.Format("Insert into 报废表 (danjuhao,kfbm,riqi,operator,beizhu ) \
			values('%s','%s',trunc(sysdate,'dd'),'%s','过期') ",strDanjuhao,\
			LoginInformation.kfbm,LoginInformation.user );
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		for(long i=1;i<rows;i++)
		{
			id=atol(m_grid.GetTextMatrix(i,0));// MED ID
			strSql.Format("Insert Into ItemTI (danjuhao,ID,sL,DJ,riqi,selldj,\
				kfbm,ypbm,rq1,rq2,factory ) (select '%s',id,sl,sell_price,\
				trunc(sysdate,'dd'),jinjia,kfbm,ypbm,rq1,rq2,gongmc from medlie,codegys \
				where medlie.factorycode=codegys.gongbm and id=%ld ) ",strDanjuhao,id);
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			strSql.Format("Update Medlie set SL=0 where id=%ld ",id);
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		}
		HospitalConnect->CommitTrans();
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		HospitalConnect->RollbackTrans();
		return ;
	}	
	SetGridHead();
*/
	AfxMessageBox("您无权进行药品报废操作...");
}

void CFormMedList::OnQmModifyMed() 
{
	if(!theApp.AssertRole(ROLE_MED_STATUS_MODIFY))return; 
	// TODO: Add your command handler code here
	//AfxMessageBox("修改药品情况");
	if(m_grid.GetRows()<3 || curRow == 0) return; //未选择药品情况
	CDialogMedModify med;
	med.row=curRow;
	theApp.pParentGrid.pGrid=&m_grid;
	med.DoModal();


}

void CFormMedList::SetGridHead()
{
	CString HeadTitle[]={"ID","FACTORYBM","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地","库存量","购进价","零售价","指导价","购进额","零售额","利润","大类","小类","库房名"}; //共 19 列
	
	long  headWidth[]={0,0,800,1400,1400,400,0,1200,1400,1200,1200,1200,0,1000,1000,1000,00,00,1400};
	
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
//	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetSelectionMode(1);
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count>15)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		if(count<4)m_grid.SetColAlignment(i,1);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
	m_grid.SetFillStyle(1); //

}

void CFormMedList::OnButtonToExcel() 
{
	// TODO: Add your control notification handler code here
	extern void ToExcel(CMSHFlexGrid * pg);
	if( MessageBox("是否确定要导出到 Excel 表格 ??? ","提示",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	ToExcel(&m_grid);
	
}
