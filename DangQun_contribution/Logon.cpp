// Logon.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "Logon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogon dialog


CLogon::CLogon(CWnd* pParent /*=NULL*/)
	: CDialog(CLogon::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogon)
	//}}AFX_DATA_INIT
	backBrush.CreateSolidBrush(RGB(255,255,255)); //������ɫˢ��
	bk2.CreateSolidBrush(RGB(0,74,152));
}


void CLogon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogon)
	DDX_Control(pDX, IDCANCEL, m_re);
	DDX_Control(pDX, IDOK, m_we);
	DDX_Control(pDX, IDC_COMBO1, m_depart);
	DDX_Control(pDX, IDC_EDIT1, m_password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogon, CDialog)
	//{{AFX_MSG_MAP(CLogon)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogon message handlers
extern CHis3App theApp;
BOOL CLogon::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	if( theApp.exitCode == 2){ //Ӧ�ó������������,Ҫ��������
//		OnCancel();
//		return false;
//	}
	

	m_depart.SetEditNewFont(120, _T("΢���ź�"));
	m_depart.SetListNewFont(120, _T("΢���ź�"));
	m_depart.SetEdtTextColor(RGB(255, 0, 0));
	m_depart.SetListTextColor(RGB(255, 0, 0));
	


	CString strSql;
	try{
		strSql.Format("SELECT user_name ,id from grant_login Where effect=1 order by rank");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
		
			m_depart.AddString( CComFunc::GetSqlItem(0) );
			vtID.push_back( atoi( (LPCSTR)CComFunc::GetSqlItem(1) ) );
			recSet->MoveNext();

		
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return false;
	}		
//	SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOSIZE);
	SetWindowText(theApp.strProject);
	CenterWindow();
	//AnimateWindow(m_hWnd,300,AW_SLIDE|AW_HOR_POSITIVE);
	//Invalidate();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLogon::OnSelchangeCombo1() 
{
	m_password.SetFocus();

}

void CLogon::OnOK() 
{
	CString strSql,str1,str2,str3,str4,str5,str6,strTemp;
	if(m_depart.GetCurSel() == CB_ERR  ) return;
//	m_depart.GetLBText(m_depart.GetCurSel(),str1);
	int iSel=m_depart.GetCurSel();

	m_password.GetWindowText(str3);
	COleDateTime dt=COleDateTime::GetCurrentTime();	

	try{
		strSql.Format("select user_pass from grant_login where  ID=%d  ",vtID[ iSel]  );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetCollect("user_pass").vt==VT_NULL?"":recSet->GetCollect("user_pass"));
		
		}
		recSet->Close();

		if(strSql.Compare(str3) == 0){ //������ͬ
			LoginInformation.kfmc=str1;// ����
			LoginInformation.user_code.Format("%d", vtID[iSel] );
			CDialog::OnOK();
		}
		else {
			AfxMessageBox("������������벻��ȷ!!����ϸ�˶���������...");
			m_password.SetWindowText("");
			m_password.SetFocus();
		}


	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return ;
	}	

}

void CLogon::OnSelchangeCombo2() 
{
	m_password.SetFocus();
	// TODO: Add your control notification handler code here
	
}

HBRUSH CLogon::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor ==CTLCOLOR_STATIC)pDC->SetBkMode(TRANSPARENT);
	// TODO: Change any attributes of the DC here
	if(pWnd->m_hWnd == m_password.m_hWnd )pDC->SetTextColor(RGB(255,0,0));
	if( pWnd->m_hWnd== GetDlgItem(IDC_STATIC_BMP)->m_hWnd){
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH )bk2.GetSafeHandle();
		

	}
	return (HBRUSH )backBrush.GetSafeHandle();
	// TODO: Return a different brush if the default is not desired
//	return hbr;
}

void CLogon::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

}

void CLogon::OnCancel() 
{
	if( theApp.strLogID.IsEmpty() )
		HospitalConnect->Close();
		
	CDialog::OnCancel();
}

void CLogon::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonDown(nFlags, point);
	
	PostMessage(WM_NCLBUTTONDOWN, 2, 0);
}
