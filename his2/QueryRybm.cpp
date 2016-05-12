// QueryRybm.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "QueryRybm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueryRybm dialog


CQueryRybm::CQueryRybm(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryRybm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQueryRybm)
	//}}AFX_DATA_INIT
	curRow=0;
}


void CQueryRybm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryRybm)
	DDX_Control(pDX, IDCANCEL, m_x2);
	DDX_Control(pDX, IDOK, m_x1);
	DDX_Control(pDX, IDC_COMBO1, c_com1);
	DDX_Control(pDX, IDC_EDIT3, c_bm);
	DDX_Control(pDX, IDC_EDIT1, c_name);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQueryRybm, CDialog)
	//{{AFX_MSG_MAP(CQueryRybm)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryRybm message handlers

BOOL CQueryRybm::OnInitDialog() 
{
	CDialog::OnInitDialog();

	fontTitle.CreatePointFont(200,"宋体");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	m_grid.SetRows(2);
	m_grid.Clear();
//	m_grid.SetRedraw(false);

	CString HeadTitle[]={"工作性质","编号","姓名"},getTitle[]={"attribute","rybm","name"};
	long  headWidth[]={1800,1200,1200,400,1300,1300,1200,2000};

	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		m_grid.SetColWidth(i,headWidth[count]);

//		p2->m_grid.SetRow(0);
//		p2->m_grid.SetCol(i);
//		p2->m_grid.SetColAlignment(i,4);//flexAlignCenterCenter 4 单元格的内容居中、居中对齐	

		m_grid.SetTextArray(i++,HeadTitle[count]);
	}
	c_com1.AddString("  ");
//	long z=0;
	CString strSql,strRec;
	try{
	//	strSql.Format("select distinct attribute  from operator  order by attribute");
	
		strSql.Format("SELECT kfmc FROM storeroom order by KFMC ");
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
	
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetCollect("KFMC").vt==VT_NULL?" ":recSet->GetCollect("KFMC"));
		/*	if(z!=0){
				if(strSql==strRec){
					recSet->MoveNext();
					continue;
				}
			}
		*/	c_com1.AddString(strSql);
		//	z++;
			recSet->MoveNext();
		//	strRec=strSql;
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		
	OnOK();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CQueryRybm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(GetDlgItem(IDC_STATIC_NOTI)->m_hWnd == pWnd->m_hWnd)pDC->SetTextColor(RGB(255,0,0));
		// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CQueryRybm::OnOK() 
{
	UpdateData();

	m_grid.SetRows(2);
	m_grid.Clear();
//	m_grid.SetRedraw(false);

	CString HeadTitle[]={"工作性质","编号","姓名"},getTitle[]={"attribute","rybm","name"};
	long  headWidth[]={1800,1200,1200,400,1300,1300,1200,2000};

	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long j=0, i=0,x=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		m_grid.SetColWidth(i,headWidth[count]);

//		p2->m_grid.SetRow(0);
//		p2->m_grid.SetCol(i);
//		p2->m_grid.SetColAlignment(i,4);//flexAlignCenterCenter 4 单元格的内容居中、居中对齐	

		m_grid.SetTextArray(i++,HeadTitle[count]);
	}

	CString strSql,str1,str2,str3;
	c_name.GetWindowText(str1);
	c_bm.GetWindowText(str2);
	try{
		if(c_com1.GetCurSel() == CB_ERR || c_com1.GetCurSel() == 0)
			strSql.Format("select b.kfmc as attribute,a.rybm as rybm ,a.name as name from operator a,storeroom b \
				where a.kfbm=b.kfbm and sfdel !='y' and name like '%s%%' and rybm like '%s%%' order by attribute ",\
				str1,str2);
		else {
			c_com1.GetLBText(c_com1.GetCurSel(),str3);
			strSql.Format("select b.kfmc as attribute,a.rybm as rybm ,a.name as name from operator a,storeroom b \
					where a.kfbm=b.kfbm and  sfdel !='y' and b.kfmc='%s' and name like '%s%%' and rybm like '%s%%' order by attribute ",\
				str3,str1,str2);

		}
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		j=1;
		while(!recSet->adoEOF){
			x=0;
			for(count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
				
				str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(getTitle[count])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(getTitle[count])));
				m_grid.SetTextMatrix(j,x++,str1);
			}
				
			
			m_grid.AddItem(" ",_variant_t(++j));
			
			recSet->MoveNext();
		
		}
		recSet->Close();
		m_grid.SetTextMatrix(j,0,"合计");
		m_grid.SetRedraw(true);
		strSql.Format("共查询到: %ld 人次",j-1);
		GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(strSql);

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		AfxMessageBox(strSql);
		return ;
	}		
	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow = 1;
		for( i=1;i<3;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CQueryRybm::OnSelchangeCombo1() 
{

	OnOK();
}

void CQueryRybm::OnChangeEdit1() 
{
	OnOK();
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CQueryRybm::OnChangeEdit3() 
{
	OnOK();
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

BEGIN_EVENTSINK_MAP(CQueryRybm, CDialog)
    //{{AFX_EVENTSINK_MAP(CQueryRybm)
	ON_EVENT(CQueryRybm, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CQueryRybm, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CQueryRybm::OnDblClickMshflexgrid1() //选择要操作的人员
{
	long rows=m_grid.GetRows();
	long row=m_grid.GetRow();
	if(rows<3 || row>=rows-1)return;

	strNum=m_grid.GetTextMatrix(row,1);//bm;
	strName=m_grid.GetTextMatrix(row,2);//mc;
	CDialog::OnOK();
	
	
}

void CQueryRybm::OnClickMshflexgrid1() 
{
	// TODO: Add your control notification handler code here
	long r1;
	r1=m_grid.GetRow();
	if(r1 >= m_grid.GetRows()-1 || curRow == r1)return;

	m_grid.SetCol(0);
	m_grid.SetRow(curRow);
	UINT color=m_grid.GetCellBackColor();

	for(int i=1;i<3;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(color);
	}
	m_grid.SetRow(r1);
	curRow=r1;
	for( i=1;i<3;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(RGB(255,0,0));
	}
	
}
