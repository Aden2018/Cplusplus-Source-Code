#pragma once


// CAdoTest 对话框

class CAdoTest : public CDialogEx
{
	DECLARE_DYNAMIC(CAdoTest)

public:
	CAdoTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAdoTest();

// 对话框数据
	enum { IDD = IDD_DIALOG_ADO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_str1;
	CString m_str2;
	CString m_str3;
};
