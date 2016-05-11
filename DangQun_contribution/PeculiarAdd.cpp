// PeculiarAdd.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "PeculiarAdd.h"
#include "progressEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPeculiarAdd dialog


CPeculiarAdd::CPeculiarAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CPeculiarAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPeculiarAdd)
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	m_strNum = _T("");
	//}}AFX_DATA_INIT
}


void CPeculiarAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPeculiarAdd)
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comType);
	DDX_Control(pDX, IDOK_QUERY, m_22);
	DDX_Control(pDX, IDOK_EXECUTE_ADD, m_1);
	DDX_Control(pDX, IDOK_EXCEL_IN, m_B_EXCEL_IN);
	DDX_Control(pDX, IDCANCEL, m_b1);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	DDX_Text(pDX, IDC_EDIT_RELEASE_NUM, m_strNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPeculiarAdd, CDialog)
	//{{AFX_MSG_MAP(CPeculiarAdd)
	ON_BN_CLICKED(IDOK_EXCEL_IN, OnExcelIn)
	ON_BN_CLICKED(IDOK_EXECUTE_ADD, OnExecuteAdd)
	ON_BN_CLICKED(IDOK_QUERY, OnQuery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPeculiarAdd message handlers

BOOL CPeculiarAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	arrType.Add(BLANKSTR);
	m_comType.AddString(BLANKSTR);

	CString strSql;
	long i;

	try{
		
		strSql.Format(" SELECT id,des From Ems_Type Where effect=1 Order by rank ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			arrType.Add(CComFunc::GetSqlItem(i++));
			m_comType.AddString(CComFunc::GetSqlItem(i++));
			
			recSet->MoveNext();
	
		}
		recSet->Close();


			
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		
	
	CComFunc::comSetGridHeader(m_grid,HEADER_ID);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
#define   IDC_PROGRESS_EXCEL WM_USER+1211

void CPeculiarAdd::OnExcelIn() //数据导出
{
	CComFunc::ToExcel(&m_grid);	

	
}

void CPeculiarAdd::OnExecuteAdd() //充值
{

}



void CPeculiarAdd::OnQuery() 
{
	UpdateData();

	CString strSql,strConnect(BLANKSTR);
	const char *strORDER=" ORDER BY c.rq,a.num ";
	const int ZERO=0;

	strSql.Format("select 1,a.`Num`,b.`news_name`,E.des,c.`cmt`,c.`rq`,c.`price`,D.`name`  from \
		make_fee c,fee_release_num a ,news_type b,business D ,Ems_type E where c.`ID`=a.`ID`  And \
		a.`news_type`=b.`news_ID` AND c.`MAKE_ID`=D.`ID` AND D.sort_type=E.ID ");

	if( ! m_strNum.IsEmpty() ){
		strConnect.Format(" AND a.num=%ld ",atol(m_strNum) );
	}
	strSql+=strConnect;

	int i=m_comType.GetCurSel();
	if( CB_ERR == i || ZERO== i)
	{
		strConnect=BLANKSTR;
	}else
		strConnect.Format(" AND D.sort_type =%ld ",atol( arrType[i] ) );
	strSql+=strConnect;


	


	strSql+=strORDER;

	CComFunc::comSetGridHeader(m_grid,HEADER_ID);
		
	m_grid.SetMergeCells(3); //1,自由合并,2,限制行,3,限制列

	for( i=2; i< m_grid.GetCols(0) ; ++i)
		m_grid.SetMergeCol(i,true);
	

	CComFunc::ReadDataForGrid(strSql,m_grid);

}
