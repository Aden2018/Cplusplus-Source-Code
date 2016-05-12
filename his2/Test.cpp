// Test.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "Test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest dialog


CTest::CTest(CWnd* pParent /*=NULL*/)
	: CDialog(CTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTest)
	m_str1 = _T("");
	//}}AFX_DATA_INIT
	font1.CreatePointFont(130,"宋体");

}


void CTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTest)
	DDX_Text(pDX, IDC_EDIT1, m_str1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTest, CDialog)
	//{{AFX_MSG_MAP(CTest)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest message handlers

void CTest::OnOK() 
{
	// TODO: Add extra validation here

	UpdateData();
	CString str1,strSql;
	union  {

		char pv[2];
		short   vl;
	}pa;
	pa.pv[0]=m_str1[1];
	pa.pv[1]=m_str1[0];
	if(m_str1.GetLength()<2){
		AfxMessageBox("you enter is a character...");
		return;
	}

	_RecordsetPtr recSet;

	if(FAILED(recSet.CreateInstance( __uuidof( Recordset ))))
	{
		AfxMessageBox("初始化Recordset失败...");
		return ;
	}
	
	try{
		strSql.Format("select * from py where py_v<=%ld order by py_V DESC ",pa.vl);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			str1=(char*)_bstr_t(recSet->GetCollect("py_c"));



		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("请程序设计人员检查数据库是否有异常...");
		return;
	}	
	AfxMessageBox(str1);
//	CDialog::OnOK();
}

HBRUSH CTest::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_EDIT){
		pDC->SelectObject(&font1);
	}
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
