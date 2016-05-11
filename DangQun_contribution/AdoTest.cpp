// AdoTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "his3.h"
#include "AdoTest.h"
#include "afxdialogex.h"
#include "ComFunc.h"



// CAdoTest �Ի���

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


// CAdoTest ��Ϣ�������


void CAdoTest::OnBnClickedOk()
{
	UpdateData();

	vector<string> vtSz;
	string szRet("");
	vtSz.push_back((LPCSTR)m_str1); //�洢������
	vtSz.push_back("1");			//��������
	vtSz.push_back("1");		//��һ�α�
	

	CComFunc::callSqlPro(vtSz,szRet);
	if ( szRet.size() ==0 ) AfxMessageBox("No Data return;");
	else	AfxMessageBox(szRet.c_str());
}
