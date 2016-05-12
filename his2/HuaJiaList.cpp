// HuaJiaList.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "HuaJiaList.h"
#include "huaJia.h"
#include "progressIndicate.h"
#include "otherDecharge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHuaJiaList dialog
#define COLS  6
#define DOWN_ARROR 0x28
#define UP_ARROR 0x26
void WriteDebug(CString);
CHuaJiaList::CHuaJiaList(CWnd* pParent /*=NULL*/)
	: CDialog(CHuaJiaList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHuaJiaList)
	m_date1 = COleDateTime::GetCurrentTime();
	m_dateStart = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"宋体");
	curRow=0;
}


void CHuaJiaList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHuaJiaList)
	DDX_Control(pDX, IDC_COMBO_SORT, m_comboxSort);
	DDX_Control(pDX, IDOK, m_3);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START, m_dateStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHuaJiaList, CDialog)
	//{{AFX_MSG_MAP(CHuaJiaList)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_SORT, OnSelchangeComboSort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHuaJiaList message handlers

BOOL CHuaJiaList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);	

	CRect r1,r2;
	GetClientRect(r1);
	GetDlgItem(IDC_STATIC_TITLE)->GetClientRect(r2);
	GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(0,0,r1.right,r2.bottom);

	GetDlgItem(IDC_MSHFLEXGRID1)->GetWindowRect(r2);
	ScreenToClient(r2);
	r2.right=r1.right-5;
	GetDlgItem(IDC_MSHFLEXGRID1)->MoveWindow(r2);
	m_comboxSort.SetCurSel(0); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHuaJiaList::OnOK() 
{
//	CString HeadTitle[]={"序号","姓名","bm","挂号类型","日期","序列号"}; 
	if( m_comboxSort.GetCurSel() == CB_ERR || m_comboxSort.GetCurSel() == 0 ){
		m_comboxSort.SetCurSel(0);
		ShowPublic();

	}
	else if (m_comboxSort.GetCurSel() == 1) {
		ShowReside();
	}


}

BEGIN_EVENTSINK_MAP(CHuaJiaList, CDialog)
    //{{AFX_EVENTSINK_MAP(CHuaJiaList)
	ON_EVENT(CHuaJiaList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CHuaJiaList, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CHuaJiaList, IDC_MSHFLEXGRID1, -602 /* KeyDown */, OnKeyDownMshflexgrid1, VTS_PI2 VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CHuaJiaList::OnDblClickMshflexgrid1()  //划价操作
{
//	CString HeadTitle[]={"序号","姓名","BM","挂号类型","日期","序列号"};
// 							0     1	     2       3        4       5
//	住院人员           ={"序号","serial","姓名","性别","家庭住址","日期","床位"}; //共6列+2

	if(!theApp.AssertRole(ROLE_STARTDOCTOR_HJ))return ;	
 	CHuaJia huajia;
	long row=m_grid.GetRow();
	if(row == 0 || row >=m_grid.GetRows()-1){
		AfxMessageBox("请双击需要划价的条目...");
		return;
	}
	CString strSql;
	long count=0;

	if( m_comboxSort.GetCurSel() == 0 ){  //普通人员正常操作
		/* 加上一个检测 是否有另一人在划价  */
		strSql.Format(" SELECT NVL(划价员,0) FROM ItemRegisterTou WHERE danjuhao='%s' ",m_grid.GetTextMatrix(row,5) );
		count=atol( COtherDecharge::GetStringTitle(strSql) );
		if( count != 0 ) { //已经划过价,禁止划价
			OnOK();
			return;
		}
		
		strSql.Format(" SELECT count(*) FROM lsq_share WHERE serial='%s' ",m_grid.GetTextMatrix(row,5) );
		count=atol( COtherDecharge::GetStringTitle(strSql) );
		
		if( count != 0 ) {
			MessageBox("已有划价人员对此记录正进行划价,请选择其它人员划价!!!","警告",MB_OK|MB_ICONINFORMATION );
			return;
		}
		else {
			strSql.Format("INSERT INTO lsq_SHARE (serial) values('%s') ",m_grid.GetTextMatrix(row,5) );
			COtherDecharge::WriteSQL(strSql);
		}
		/******************************************/
		for(int i=1;i<6;i++)
			huajia.str2[i]=m_grid.GetTextMatrix(row,i);
		huajia.strGhHuajia[0]= m_grid.GetTextMatrix(row,i++);
		huajia.strGhHuajia[1]= m_grid.GetTextMatrix(row,i);
		if(huajia.DoModal() == IDOK) OnOK();
	}
	else if( m_comboxSort.GetCurSel() ==1 ) { //住院人员划价
		
		strSql.Format(" SELECT count(*) FROM lsq_share WHERE serial='%s' ",m_grid.GetTextMatrix(row,1) );
		count=atol( COtherDecharge::GetStringTitle(strSql) );
		
		if( count != 0 ) {
			MessageBox("已有划价人员对此记录正进行划价,请选择其它人员划价!!!","警告",MB_OK|MB_ICONINFORMATION );
			return;
		}
		else {
			strSql.Format("INSERT INTO lsq_SHARE (serial) values('%s') ",m_grid.GetTextMatrix(row,1) );
			COtherDecharge::WriteSQL(strSql);
		}

		huajia.str2[3]="住院人员";     // str2[3] 作为住院类型
		huajia.str2[5]=m_grid.GetTextMatrix(row,1); //str2[5]在划价初始化时作为单据号使用
		huajia.str2[1]=m_grid.GetTextMatrix(row,2); //住院人姓名
		huajia.str2[4]=COleDateTime::GetCurrentTime().Format("%Y-%m-%d");
//		huajia.strGhHuajia[0]= m_grid.GetTextMatrix(row,i++);
//		huajia.strGhHuajia[1]= m_grid.GetTextMatrix(row,i);
		if(huajia.DoModal() == IDOK) OnOK();

	}
	
}
HBRUSH CHuaJiaList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd){
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return theApp.titleBrush;


	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CHuaJiaList::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
}

void CHuaJiaList::OnClickMshflexgrid1() 
{
	// TODO: Add your control notification handler code here
	long r1;
	r1=m_grid.GetRow();
	if(r1>=m_grid.GetRows()-1 || curRow== r1)return;

	m_grid.SetCol(0);
	m_grid.SetRow(curRow);
	UINT color=m_grid.GetCellBackColor();

	for(int i=1;i<COLS;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(color);
	}
	m_grid.SetRow(r1);
	curRow=r1;
	for( i=1;i<COLS;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(RGB(255,0,0));
	}
	
}

void CHuaJiaList::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}

void CHuaJiaList::OnKeyDownMshflexgrid1(short FAR* KeyCode, short Shift) 
{

	long rows=m_grid.GetRows()-2;
	if(rows == 0)return; //没有项目则反返回

	if( DOWN_ARROR == * KeyCode){  //下箭头按下动作
	
		m_grid.SetCol(0);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();

		for(int i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
	
		if(curRow < rows && curRow != 0 ) m_grid.SetRow(++curRow);
		else {
				curRow=1;
				m_grid.SetRow(curRow);

		}
		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
		

	}
	else if(UP_ARROR == * KeyCode){ //上箭头按下动作


		m_grid.SetCol(0);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();

		for(int i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
	
		if(curRow <= rows && curRow!= 1) m_grid.SetRow(--curRow);
		else {
				curRow=rows;
				m_grid.SetRow(curRow);

		}
		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}



	}	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	
}

BOOL CHuaJiaList::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN )

		if(pMsg->wParam == VK_RETURN && GetFocus()->m_hWnd == GetDlgItem(IDC_DATETIMEPICKER1)->m_hWnd ){
			OnOK();
			return true;
		}
		else if ( pMsg->wParam == VK_RETURN && GetFocus()->m_hWnd == GetDlgItem(IDC_MSHFLEXGRID1)->m_hWnd )	OnDblClickMshflexgrid1();
		else if( pMsg->wParam==VK_DOWN)
			m_grid.SetFocus();
	
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CHuaJiaList::OnSelchangeComboSort()  //分类人员选择,
{

	OnOK();
}

void CHuaJiaList::ShowPublic()
{
	m_comboxSort.SetCurSel(0); //选择普通人员
	CString getTitle[]={"sickName","SickBm","GhType","riqi","danjuhao","挂号员名","划价员名"};
	UpdateData();
	CString HeadTitle[]={"序号","姓名","BM","挂号类型","日期","序列号","挂号员","hj"}; //共6列+2
	
	long  headWidth[]={600,2000,00,2000,0,0,1200,0,0,0};
	int iCols=sizeof(HeadTitle)/sizeof(CString);

	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(iCols);
	m_grid.SetFixedCols(0);
	m_grid.SetRow(0);
	for(int count=0;count<iCols;count++){
		m_grid.SetColAlignment(long(count),short(4));
		m_grid.SetColWidth(count,headWidth[count]);
		m_grid.SetCol(long(count));
		m_grid.SetCellAlignment(short(4));
		m_grid.SetTextArray(count,HeadTitle[count]);
	}	
	m_grid.SetMergeCol(6,1);//划价员合并
	long row=1,col;
	CString strSql,str1;
	try{

		strSql.Format("select * from itemregistertou t where riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd')  \
			and 划价员 is null ORDER BY 挂号员",m_dateStart.Format("%Y%m%d"),m_date1.Format("%Y%m%d"));
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			str1.Format("%ld",row);
			col=0;
			m_grid.SetTextMatrix(row,col++,str1);
			for(int i=0;i<sizeof(getTitle)/sizeof(CString);i++)
			{
				str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(getTitle[i])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(getTitle[i])));
				m_grid.SetTextMatrix(row,col++,str1);
			}
			row++;
			m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();

		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return;
	}
	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow=1;
		for( row=1;row <COLS;row++){
			m_grid.SetCol(row);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
}

void CHuaJiaList::ShowReside()
{
	UpdateData();
	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"序号","serial","姓名","性别","家庭住址","日期","床位"}; //共6列+2

	long  headWidth[]={600,0,1200,400,1400,2600,2400};

	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	m_grid.SetRow(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetColAlignment(long(count),short(4));
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetCol(long(count));
		m_grid.SetCellAlignment(short(4));
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	
	long row=1,col;
	CString strSql,str1;
	try{

		strSql.Format("select serial,xm,xb,home_addr,rq,rname || '/'|| bname from lsq_reside_hos a,lsq_reside_bed b,lsq_reside_room c \
			where a.bed_id=b.bcode and b.broom=c.rcode and \
			rq between to_date('%s000000','yyyymmddhh24miss') and to_date('%s235959','yyyymmddhh24miss') 	",\
			m_dateStart.Format("%Y%m%d"),m_date1.Format("%Y%m%d"));
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			str1.Format("%ld",row);
			col=0;
			m_grid.SetTextMatrix(row,col++,str1);
			for(int i=0;i< recSet->GetFields()->Count;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(long(i))->Value);
				m_grid.SetTextMatrix(row,col++,str1);
			}
			row++;
			m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();

		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return;
	}
	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow=1;
		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
}
