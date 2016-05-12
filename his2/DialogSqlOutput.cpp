// DialogSqlOutput.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "DialogSqlOutput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogSqlOutput dialog


CDialogSqlOutput::CDialogSqlOutput(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSqlOutput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogSqlOutput)
	m_sql = _T("");
	//}}AFX_DATA_INIT
}


void CDialogSqlOutput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSqlOutput)
	DDX_Text(pDX, IDC_OUT_SQL, m_sql);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogSqlOutput, CDialog)
	//{{AFX_MSG_MAP(CDialogSqlOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogSqlOutput message handlers

void CDialogSqlOutput::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CDialogSqlOutput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(false);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
