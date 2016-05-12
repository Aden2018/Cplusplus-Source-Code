// ResideLocalSet.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "ResideLocalSet.h"
#include "localSetAdd.h"
#include "localsetModify.h"
#include "qiuXpButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResideLocalSet dialog


CResideLocalSet::CResideLocalSet(CWnd* pParent /*=NULL*/)
	: CDialog(CResideLocalSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResideLocalSet)
	m_strBm = _T("");
	m_strMc = _T("");
	//}}AFX_DATA_INIT
	strTitle="病区设置";
}


void CResideLocalSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResideLocalSet)
	DDX_Control(pDX, IDC_COMBO1, m_combox);
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, IDCANCEL, m_1);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	DDX_Text(pDX, IDC_EDIT_BM, m_strBm);
	DDX_Text(pDX, IDC_EDIT_MC, m_strMc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResideLocalSet, CDialog)
	//{{AFX_MSG_MAP(CResideLocalSet)
	ON_COMMAND(ID_MENU_RESIDE_LOCAL_ADD, OnMenuResideLocalAdd)
	ON_COMMAND(ID_MENU_RESIDE_LOCAL_REFRESH, OnMenuResideLocalRefresh)
	ON_COMMAND(ID_MENU_RESIDE_LOCAL_DEL, OnMenuResideLocalDel)
	ON_COMMAND(ID_MENU_RESIDE_LOCAL_MODIFY, OnMenuResideLocalModify)
	ON_EN_CHANGE(IDC_EDIT_MC, OnChangeEditMc)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT_BM,OnChangeEditMc)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResideLocalSet message handlers

BOOL CResideLocalSet::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(strTitle );
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&CHis2App::fontTitle);

	OnMenuResideLocalRefresh();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CResideLocalSet::SetGridHead()
{
	CString HeadTitle[]={"编码","名称","备注"};
	long  headWidth[]={1600,2000,2400};
		
	m_grid.SetRows(2);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0,col(0),row(0);
	m_grid.SetRow(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
	
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
	m_grid.SetColAlignment(0,4);
	m_grid.SetColAlignment(2,1);  //中间左对齐
	m_grid.SetColAlignment(1,1);
	m_grid.SetSelectionMode(1); //按行选择
}

BEGIN_EVENTSINK_MAP(CResideLocalSet, CDialog)
    //{{AFX_EVENTSINK_MAP(CResideLocalSet)
	ON_EVENT(CResideLocalSet, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CResideLocalSet, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CResideLocalSet::OnClickMshflexgrid1() 
{
	const int ENDLINES=2;
	const int MOUSE_RIGHT_KEYDOWN=0x205;
	const int MOUSE_LEFT_KEYDOWN=0x202;//0x202为鼠标左键,0x205为鼠标右键消息
	const int START_COL=3; 
	const int END_COL= START_COL+1 ; 
	const COLORREF COLOR_SELECT=RGB(255,0,0);
//	if(m_grid.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message == MOUSE_LEFT_KEYDOWN ) {
		
/*		long r1;
		r1=m_grid.GetRow();
		if(r1>=m_grid.GetRows()-1 || curRow== r1)return;
		
		m_grid.SetRow(r1);
		for(int i=START_COL ;i< END_COL;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(COLOR_SELECT );
		}
		m_grid.SetCol(1);
		m_grid.SetCellBackColor(COLOR_SELECT);

		m_grid.SetCol(0);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor(); //获取原单元格颜色
		
		for( i= START_COL ;i< END_COL;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
		m_grid.SetCol(1);
		m_grid.SetCellBackColor(color);

		curRow=r1;
*/	
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_RESIDE_LOCAL);
	CMenu* pmenu=pm.GetSubMenu(0);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  	
	
}

void CResideLocalSet::OnMenuResideLocalAdd() 
{
	CLocalSetAdd ls;
	if(ls.DoModal()==IDOK) OnMenuResideLocalRefresh();
}

void CResideLocalSet::OnMenuResideLocalRefresh() //刷新
{
	UpdateData();
	SetGridHead();
	CString strSql,str1,strGhtype,strname;
	m_grid.SetRedraw(false);
	long row,i;

	try{
	strSql.Format("SELECT llocal,lname,lremark From lsq_reside_local where \
		leffect='1' AND llocal like '%s%%' AND lname like '%s%%' ",	m_strBm,m_strMc);
	recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
	row=1;
	while(!recSet->adoEOF){
		for(i=0;i< 3;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				m_grid.SetTextMatrix(row,i,str1);
			}
			row++;
			m_grid.AddItem("",_variant_t(row));
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


  m_grid.SetRedraw(true);;
	
}

void CResideLocalSet::OnMenuResideLocalDel() //删除
{
	if( CheckSelectRow() == FAIL) return;

	CString strBm=m_grid.GetTextMatrix(curRow,0);//获取编码
	CString strSql;
	strSql.Format("确认要删除: %s / %s ",m_grid.GetTextMatrix(curRow,1),m_grid.GetTextMatrix(curRow,2) );
	if( MessageBox(strSql,"提示",MB_OKCANCEL|MB_ICONINFORMATION  ) == IDCANCEL) return;

	strSql.Format("update lsq_reside_local set leffect='0' Where llocal='%s' ",strBm);
	if( COtherDecharge::WriteSQL(strSql) ){
		AfxMessageBox("删除成功");
		m_grid.RemoveItem(curRow);
	}
	else AfxMessageBox("删除失败");

	
}

void CResideLocalSet::OnMenuResideLocalModify()  //修改
{
	if( CheckSelectRow() == FAIL) return;
	CLocalSetModify sm;
	sm.m_name=m_grid.GetTextMatrix(curRow,1);
	sm.m_remark=m_grid.GetTextMatrix(curRow,2);
	sm.strBM=m_grid.GetTextMatrix(curRow,0);
	if( sm.DoModal()== IDOK) {
		m_grid.SetTextMatrix(curRow,1,sm.m_name);
		m_grid.SetTextMatrix(curRow,2,sm.m_remark);
	}

	
}

void CResideLocalSet::OnDblClickMshflexgrid1() 
{
	
}

int CResideLocalSet::CheckSelectRow()
{

	curRow=m_grid.GetRow();
	if( curRow == 0 || curRow == m_grid.GetRows()-1 ) {
		AfxMessageBox("请先选择需要操作的行");
		return FAIL;
	}
	return SUCCESS;


}

void CResideLocalSet::OnChangeEditMc() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnMenuResideLocalRefresh();
}

void CResideLocalSet::OnSelchangeCombo1() 
{
	OnMenuResideLocalRefresh();	
}
