// DechargeQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "DechargeQuery.h"
#include "OperatorSel.h"
#include "CostClassAb.h"
#include "ReportDechargeList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDechargeQuery dialog


CDechargeQuery::CDechargeQuery(CGridCtrl &p,CWnd* pParent /*=NULL*/)
	: CDialog(CDechargeQuery::IDD, pParent),m_grid(p)
{
	//{{AFX_DATA_INIT(CDechargeQuery)
	m_date = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	m_strNum1 = _T("");
	m_strNum2 = _T("");
	//}}AFX_DATA_INIT
}


void CDechargeQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDechargeQuery)
	DDX_Control(pDX, IDC_COMBO_NEWS_TYPE, m_newsType);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	DDX_Text(pDX, IDC_EDIT_NUM1, m_strNum1);
	DDX_Text(pDX, IDC_EDIT_NUM2, m_strNum2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDechargeQuery, CDialog)
	//{{AFX_MSG_MAP(CDechargeQuery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDechargeQuery message handlers

void CDechargeQuery::OnOK() 
{
	UpdateData();
	
	CReportDechargeList *pf=(CReportDechargeList *)theApp.pParentGrid.pGrid;
	CComFunc::SetGridHeader(m_grid,CReportDechargeList::GRID_ID,pf->vtAlign);


	int iSel(0);


	vector<string> vtSz;
	vtSz.push_back(MYSQL_PRC_RPT); //存储过程名
	vtSz.push_back("1");			//查询
	vtSz.push_back("G");			//报刊发行期号查询
	CString str("");

	//起止期号 
	vtSz.push_back((LPCSTR)m_strNum1);
	vtSz.push_back((LPCSTR)m_strNum2);
	//日期
	vtSz.push_back((LPCSTR)m_date.Format("%Y-%m-%d"));
	vtSz.push_back((LPCSTR)m_date2.Format("%Y-%m-%d"));

	//报刊类型
	iSel=m_newsType.GetCurSel();
	 if( !(iSel == CB_ERR || iSel == 0 ))
		 str=arrType[iSel];

	vtSz.push_back((LPCSTR)str);
	

	
	
	_RecordsetPtr rec;
	CComFunc::callSqlPro(vtSz,rec);
	vector<int> vtCol;

	vtCol.push_back(6);vtCol.push_back(7);vtCol.push_back(8);
	vector<double> vtCount(3,0);

	CComFunc::ReadDataForGrid(m_grid,rec,vtCol,vtCount,pf->vtAlign);

	CDialog::OnOK();
	
}


BOOL CDechargeQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString strSql;
	arrType.Add(BLANKSTR);
	m_newsType.AddString(BLANKSTR);

	long i;

	try{

		strSql.LoadString(IDS_SQL_NEWS_TYPE);
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			arrType.Add(CComFunc::GetSqlItem(i++));
			m_newsType.AddString(CComFunc::GetSqlItem(i++));
		
			recSet->MoveNext();
	
		}
		recSet->Close();
	
	
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查");
		return false;
	}		
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




