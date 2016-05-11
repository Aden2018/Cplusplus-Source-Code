// ReportUsedAllQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "ReportUsedAllQuery.h"
#include "ProgressIndicate.h"
#include "ReportUsedAll1.h"
#include "comFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportUsedAllQuery dialog


CReportUsedAllQuery::CReportUsedAllQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CReportUsedAllQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportUsedAllQuery)
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CReportUsedAllQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportUsedAllQuery)
	DDX_Control(pDX, IDC_COMBO_SORT_TYPE, m_comSortType);
	DDX_Control(pDX, IDC_COMBO_BUSINESS_COMPANY, m_comBusiness);
	DDX_Control(pDX, IDEXCEL, m_b3);
	DDX_Control(pDX, IDCANCEL, m_b2);
	DDX_Control(pDX, IDOK, m_b1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportUsedAllQuery, CDialog)
	//{{AFX_MSG_MAP(CReportUsedAllQuery)
	ON_BN_CLICKED(IDEXCEL, OnExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportUsedAllQuery message handlers

BOOL CReportUsedAllQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_comBusiness.AddString(BLANKSTR);
	m_arrBusiness.Add(BLANKSTR);

	m_arrSortType.Add(BLANKSTR);
	m_comSortType.AddString(BLANKSTR);

	long i(0);

	try{
		
		strSql.Format(" Select ID,name FROM business Where effect=1 Order by rank ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			m_arrBusiness.Add(CComFunc::GetSqlItem(i++));
			m_comBusiness.AddString(CComFunc::GetSqlItem(i++));
			
			recSet->MoveNext();
	
		}
		recSet->Close();

		strSql.Format(" SELECT id,des From Ems_Type Where effect=1 Order by rank ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			m_arrSortType.Add(CComFunc::GetSqlItem(i++));
			m_comSortType.AddString(CComFunc::GetSqlItem(i++));
			
			recSet->MoveNext();
	
		}
		recSet->Close();


			
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		
	
	
	
	return TRUE;  
	              
}

void CReportUsedAllQuery::OnOK() 
{
	CReportUsedAll *pf=(CReportUsedAll *)theApp.pParentGrid.pGrid; //FormView窗口

	UpdateData();
	CString strTmp;
	const char * ORDER=" ORDER BY  A.RQ ";
	int i;

	CComFunc::comSetGridHeader(pf->m_grid, CReportUsedAll::COL_ID);	
	/*
	pf->m_grid.SetMergeCells(3); //1,自由合并,2,限制行,3,限制列
	for(i=2; i< pf->m_grid.GetCols(0) ; ++i)
		pf->m_grid.SetMergeCol(i,true);
	*/
	try{
		/*
		strSql.Format("select 1,ISSN,news_name,a.cmt,price,b.name,bank,account,rq,rq2 from newspaper c,make_fee a,\
			business b,news_type d where a.make_id=b.id AND a.release_type=d.news_id and c.make_fee=a.id ");
			*/
		strSql.Format("select 1,a.id,a.cmt,b.bank_id,a.price,b.name,b.bank,b.account,a.rq,a.rq2 from make_fee a,\
			business b where a.make_id=b.id ");

		if(m_date1.Format("%Y%m%d") == m_date2.Format("%Y%m%d") )
			strTmp=BLANKSTR;
		else 
			strTmp.Format(" AND rq Between '%s' AND '%s' ",m_date1.Format("%Y-%m-%d"),m_date2.Format("%Y-%m-%d") );
		strSql+=strTmp;
	
		i=m_comBusiness.GetCurSel() ;
		int const ZERO=0;
		if( CB_ERR == i || ZERO == i )
			strTmp=BLANKSTR;
		else
			strTmp.Format(" AND b.id=%ld ",atol(m_arrBusiness[ i ]) );
		strSql+=strTmp;

		i=m_comSortType.GetCurSel();
		if( CB_ERR == i || ZERO == i )
			strTmp=BLANKSTR;
		else
			strTmp.Format(" AND b.sort_type = %ld ",atol(m_arrSortType[i]) );
		strSql+=strTmp;

		
		strSql+=ORDER;

		CComFunc::ReadDataForGrid(strSql,pf->m_grid);






	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return;
	}

	

	CDialog::OnOK();
}

UINT CReportUsedAllQuery::QueryList(LPVOID ps)
{

	return true;
}

void CReportUsedAllQuery::OnExcel() 
{
	CComFunc::ToExcel( &((CReportUsedAll*)theApp.pParentGrid.pGrid)->m_grid);	
	
}
