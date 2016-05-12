// PasswordChange.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "PasswordChange.h"
#include "qiuXpbutton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPasswordChange dialog


CPasswordChange::CPasswordChange(CWnd* pParent /*=NULL*/)
	: CDialog(CPasswordChange::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPasswordChange)
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"黑体");
}


void CPasswordChange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPasswordChange)
	DDX_Control(pDX, IDOK, m_33);
	DDX_Control(pDX, IDCANCEL, m_22);
	DDX_Control(pDX, IDC_EDIT3, m_3);
	DDX_Control(pDX, IDC_EDIT2, m_2);
	DDX_Control(pDX, IDC_EDIT1, m_1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPasswordChange, CDialog)
	//{{AFX_MSG_MAP(CPasswordChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPasswordChange message handlers

BOOL CPasswordChange::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);	
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText("用户: "+LoginInformation.user+"   库房: "+LoginInformation.kfmc);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPasswordChange::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam == VK_RETURN && GetFocus()->m_hWnd !=GetDlgItem(IDOK)->m_hWnd)
		pMsg->wParam=VK_TAB;
		
	return CDialog::PreTranslateMessage(pMsg);
}

void CPasswordChange::OnOK() 
{
	CString strSql,pass;
	CString str1,str2;
	m_2.GetWindowText(str1);
	m_3.GetWindowText(str2);
	if( str1 != str2 ){
		MessageBox("两次输入的密码不相同,请重新输入...","警告",MB_OK|MB_ICONSTOP);
		m_2.SetFocus();
		return;
	}


	try{
		strSql.Format("SELECT pass FROM operator WHERE RYBM='%s' ",LoginInformation.user_code );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF)
		{
			pass=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value);
		}
		else pass="";
		recSet->Close();
		m_1.GetWindowText(str2);
		if( pass != str2 ){
			MessageBox("原密码不正确...","警告",MB_OK|MB_ICONSTOP);
			m_1.SetFocus();
			return;
		}			
		HospitalConnect->BeginTrans();
		strSql.Format("UPDATE operator SET pass='%s' WHERE RYBM='%s' ",str1,LoginInformation.user_code );
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();
	
		
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
	
		recSet->Close();
		HospitalConnect->RollbackTrans();

		return;
	}
	MessageBox("密码更改成功","警告",MB_OK|MB_ICONINFORMATION);
	m_1.SetFocus();
}
