// AdoTest.cpp : 实现文件
//

#include "stdafx.h"
#include "his3.h"
#include "AdoTest.h"
#include "afxdialogex.h"
#include "ComFunc.h"



// CAdoTest 对话框

IMPLEMENT_DYNAMIC(CAdoTest, CDialogEx)

CAdoTest::CAdoTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdoTest::IDD, pParent)
{

	m_str1 = _T("");
	m_str2 = _T("");
	m_str3 = _T("");
}

CAdoTest::~CAdoTest()
{
}

void CAdoTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_str1);
	DDX_Text(pDX, IDC_EDIT2, m_str2);
	DDX_Text(pDX, IDC_EDIT3, m_str3);
}


BEGIN_MESSAGE_MAP(CAdoTest, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAdoTest::OnBnClickedOk)
END_MESSAGE_MAP()


// CAdoTest 消息处理程序


void CAdoTest::OnBnClickedOk()
{
	UpdateData();

	vector<string> vtSz;
	string szRet("");
	vtSz.push_back((LPCSTR)m_str1); //存储过程名
	vtSz.push_back("1");			//操作命令
	vtSz.push_back("1");		//第一游标
	

	CComFunc::callSqlPro(vtSz,szRet);
	if ( szRet.size() ==0 ) AfxMessageBox("No Data return;");
	else	AfxMessageBox(szRet.c_str());
}
