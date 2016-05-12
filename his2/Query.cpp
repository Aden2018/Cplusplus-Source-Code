// Query.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "Query.h"
#include "editEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuery dialog


CQuery::CQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQuery)
	m_bLastCheck = false;
	m_bD3 = FALSE;
	m_bX3 = FALSE;
//	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	m_date1.SetDate(m_date2.GetYear()-1,m_date2.GetMonth(),m_date2.GetDay());
}


void CQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQuery)
	DDX_Control(pDX, IDCANCEL, m_x2);
	DDX_Control(pDX, IDOK, m_x1);
	DDX_Control(pDX, IDC_EDIT_XM, m_xm);
	DDX_Control(pDX, IDC_EDIT_KH, m_kh);
	DDX_Control(pDX, IDC_COMBO_BZ, m_bz);
	DDX_Control(pDX, IDC_COMBO_BM, m_bm);
	DDX_Check(pDX, IDC_CHECK_LASTCHECK, m_bLastCheck);
	DDX_Check(pDX, IDC_CHECK_D3, m_bD3);
	DDX_Check(pDX, IDC_CHECK_X3, m_bX3);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQuery, CDialog)
	//{{AFX_MSG_MAP(CQuery)
	ON_CBN_SELCHANGE(IDC_COMBO_BM, OnSelchangeComboBm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuery message handlers
extern UINT Tsearch(LPVOID p); 
extern UINT Tsearch2(LPVOID p); 
void CQuery::OnOK() 
{
	UpdateData();

	ShowWindow(SW_HIDE);

	pParent.pQuery=(LPVOID)this;
	
	if( strFlag == "������Ա" ) AfxBeginThread(Tsearch2,&pParent);
	else AfxBeginThread(Tsearch,&pParent);
	
 
	GetDlgItem(IDOK)->EnableWindow(false);
}

void CQuery::OnCancel() 
{
	// TODO: Add extra cleanup here
	ShowWindow(SW_HIDE);
//	CDialog::OnCancel();
}

BOOL CQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
//m_bm Ϊ CComBox�ؼ�
	CString strSql;
	try{
		strSql.Format("select distinct(������) from �����ű� ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetCollect("������").vt==VT_NULL?" ":recSet->GetCollect("������"));
			m_bm.AddString(strSql);
			recSet->MoveNext();

		
		}
		recSet->Close();
		m_bm.AddString("���в���");

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return false;
	}	// TODO: Add extra initialization here
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CQuery::OnSelchangeComboBm() 
{
	CString strSql,str1;
	m_bm.GetLBText(m_bm.GetCurSel(),str1);

	while(m_bz.DeleteString(0)!=CB_ERR); //�����ԭ���İ�����Ϣ
	try{
		strSql.Format("select �������� from �����ű� where ������='%s' ",str1);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetCollect("��������").vt==VT_NULL?" ":recSet->GetCollect("��������"));
			m_bz.AddString(strSql);
			recSet->MoveNext();

		
		}
		recSet->Close();
		
		m_bz.AddString("���а���");

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		recSet->Close();
		return ;
	}	// TODO: Add extra initialization here
	// TODO: Add your control notification handler code here
	
}
