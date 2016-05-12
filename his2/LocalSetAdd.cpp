// LocalSetAdd.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "LocalSetAdd.h"
#include "qiuXpButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocalSetAdd dialog


CLocalSetAdd::CLocalSetAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CLocalSetAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLocalSetAdd)
	m_name = _T("");
	m_remark = _T("");
	//}}AFX_DATA_INIT
	strTitle="病区新增操作";

}


void CLocalSetAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocalSetAdd)
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, IDCANCEL, m_1);
	DDX_Text(pDX, IDC_EDIT_ADD_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_ADD_REMARK, m_remark);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLocalSetAdd, CDialog)
	//{{AFX_MSG_MAP(CLocalSetAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalSetAdd message handlers

void CLocalSetAdd::OnOK() 
{
	const int NOFIND=-1;
	UpdateData();
	if ( ! (m_name.Find("'") == NOFIND && m_name.Find(";") == NOFIND  && \
		m_remark.Find("'") == NOFIND && m_remark.Find(";") == NOFIND && ! m_name.IsEmpty())  )
		AfxMessageBox("输入的文字中不能含用单引号及分号等特殊字符");
	
	strSql.Format("Insert into lsq_reside_local ( llocal,lname,lremark) values( \
		(select Ltrim(to_char(NVL(max(llocal),0)+1,'009')) from lsq_reside_local),\
		'%s','%s' ) ",m_name,m_remark);
	if( COtherDecharge::WriteSQL(strSql) )AfxMessageBox("新增成功");
	else  AfxMessageBox("新增失败...");
	CDialog::OnOK();
}

BOOL CLocalSetAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_NAME)->SetFont(&CHis2App::fontTitle);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
