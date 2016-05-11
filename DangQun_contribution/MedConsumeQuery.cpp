// MedConsumeQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "MedConsumeQuery.h"
#include "ProgressIndicate.h"
#include "ReportMedConsume.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedConsumeQuery dialog


CMedConsumeQuery::CMedConsumeQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CMedConsumeQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMedConsumeQuery)
	m_date = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	m_strStart = _T("");
	m_strEnd = _T("");
	//}}AFX_DATA_INIT
}


void CMedConsumeQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedConsumeQuery)
	DDX_Control(pDX, IDC_COMBO1, m_Type);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	DDX_Text(pDX, IDC_EDIT_START, m_strStart);
	DDX_Text(pDX, IDC_EDIT_END, m_strEnd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedConsumeQuery, CDialog)
	//{{AFX_MSG_MAP(CMedConsumeQuery)
	ON_BN_CLICKED(IDOK2, OnOk2)
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(IDOK, &CMedConsumeQuery::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedConsumeQuery message handlers

void CMedConsumeQuery::OnOK() 
{
	UpdateData();

	if( CB_ERR == m_Type.GetCurSel() ){

		AfxMessageBox("请先选择要生成稿费的类别..");
		return;
	}

	CProgressIndicate pq;
	pq.pDialog= this;

	pq.pThreadFunction = QueryData;
	pq.DoModal();

	
	
	CDialog::OnOK();
}

UINT CMedConsumeQuery::QueryData(LPVOID ps)
{
	
	CReportMedConsume *pf=(CReportMedConsume *)theApp.pParentGrid.pGrid; //FormView窗口
	CMedConsumeQuery * pd =(CMedConsumeQuery *) ((CProgressIndicate *) ps )->pDialog ; //条件窗口

	//CString strSql,strConstruct(BLANKSTR),str[2] ;
	//const char *ARGU=" group by factory order by rank";
	//pf->m_grid.SetRedraw(false);

	//strSql.Format("select 1,factory,post_code, factory_addr,contacts,sum(price) from v_remit WHERE Release_TYPE=%d  ", atoi(pd->arrType[pd->m_Type.GetCurSel()]) );

	//if(  pd->m_date.Format("%Y%m%d") !=  pd->m_date2.Format("%Y%m%d") ) //日期范围
	//{
	//	strConstruct.Format(" AND Release_Date Between '%s' AND '%s' ", pd->m_date.Format("%Y-%m-%d"), pd->m_date2.Format("%Y-%m-%d") );
	
	//}else strConstruct=BLANKSTR;

	//strSql+=strConstruct;
	//long iStart,iEnd;
	//if( !  pd->m_strStart.IsEmpty() ){ //期号范围
	//	iStart=atol( pd->m_strStart);
	//	iEnd=atol( pd->m_strEnd);
	//	strConstruct.Format(" AND ISSN BETWEEN %ld AND %ld ",iStart,iEnd);
	//}else
	//	strConstruct=BLANKSTR;
	//		
	//strSql+=strConstruct;

	//strSql+=ARGU;



	//CComFunc::comSetGridHeader(pf->m_grid,CReportMedConsume::COL_ID);	
	//int iSumCol[]={5};

	//CComFunc::ReadDataForGrid(strSql,pf->m_grid,iSumCol,sizeof(iSumCol)/sizeof(int) );

	//pf->m_grid.SetRedraw(true);
	//
	CComFunc::SetGridHeader(pf->m_grid,CReportMedConsume::COL_ID/* 表格头部ID*/,pf->vtAlign); 


	pd->UpdateData();

	pf->m_grid.SetRowCount(2);

	int iSel(0);


	vector<string> vtSz;
	vtSz.push_back(MYSQL_PRC_RPT); //存储过程名
	vtSz.push_back("1");			//查询
	vtSz.push_back("F");			//分类汇总
	CString str("");

	//起止期号 
	vtSz.push_back((LPCSTR)pd->m_strStart);
	vtSz.push_back((LPCSTR)pd->m_strEnd);
	//日期
	vtSz.push_back((LPCSTR)pd->m_date.Format("%Y-%m-%d"));
	vtSz.push_back((LPCSTR)pd->m_date2.Format("%Y-%m-%d"));

	//报刊类型
	 
	iSel=pd->m_Type.GetCurSel() ;
	if( !(iSel == CB_ERR ))
		str=pd->arrType[iSel] ;
	vtSz.push_back((LPCSTR)str);
	

	
	
	_RecordsetPtr rec;
	CComFunc::callSqlPro(vtSz,rec);
	vector<int> vtCol;
	vtCol.push_back(5);
	vector<double> vtCount(1,0);

	CComFunc::ReadDataForGrid(pf->m_grid,rec,vtCol,vtCount,pf->vtAlign);

	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

	pd->SendMessage(WM_CLOSE,NULL,NULL);

	return true;
}

BOOL CMedConsumeQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	strSql.LoadString(IDS_STR_JOURNAL_COUNT);
	SetWindowText(strSql);	

	long i;

	try{

		strSql.LoadString(IDS_SQL_NEWS_TYPE);
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			arrType.Add(CComFunc::GetSqlItem(i++));
			m_Type.AddString(CComFunc::GetSqlItem(i++));
		
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



void CMedConsumeQuery::OnOk2() //输出到excel
{
	CReportMedConsume *pf=(CReportMedConsume *)theApp.pParentGrid.pGrid; //FormView窗口

	CComFunc::ToExcel(pf->m_grid);	
	
}





BOOL CMedConsumeQuery::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){
		if( pMsg->hwnd == GetDlgItem(IDOK)->m_hWnd )
		{
			OnOK();
			return false;
		}
		pMsg->wParam = VK_TAB;

	}
	

	return CDialog::PreTranslateMessage(pMsg);
}
