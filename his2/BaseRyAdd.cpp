// BaseRyAdd.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "BaseRyAdd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseRyAdd dialog


CBaseRyAdd::CBaseRyAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseRyAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBaseRyAdd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBaseRyAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBaseRyAdd)
	DDX_Control(pDX, IDC_EDIT_NAME, c_name);
	DDX_Control(pDX, IDC_EDIT_KAHAO, c_kh);
	DDX_Control(pDX, IDC_COMBO_SEX, c_sex);
	DDX_Control(pDX, IDCANCEL, m_3);
	DDX_Control(pDX, IDOK, m_2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBaseRyAdd, CDialog)
	//{{AFX_MSG_MAP(CBaseRyAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseRyAdd message handlers

BOOL CBaseRyAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();

	c_kh.SetWindowText(str[0]);
	
	c_sex.SetCurSel(0);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBaseRyAdd::OnOK() 
{
	CString strSql;
	c_sex.GetLBText(c_sex.GetCurSel(),str[2]);
	c_name.GetWindowText(str[1]);

	try{
		strSql.Format(" SELECT * FROM 医保人员列表 WHERE 卡号='%s' ",str[0] );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if( ! recSet->adoEOF ) {
			recSet->Close();
			AfxMessageBox("此人员信息数据库在已经存在");
			return;
		}
		else recSet->Close();


		HospitalConnect->BeginTrans();
		strSql.Format(" INSERT INTO 医保人员列表 (卡号,姓名,性别) values('%s','%s',\
			'%s') ",str[0],str[1],str[2]);

		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);


		HospitalConnect->CommitTrans();


	}
	catch(_com_error e)
	{
		AfxMessageBox("INSERT ERROR...");
		HospitalConnect->RollbackTrans();
		return;
	}

	CDialog::OnOK();
}
