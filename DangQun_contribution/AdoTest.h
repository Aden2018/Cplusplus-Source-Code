#pragma once


// CAdoTest �Ի���

class CAdoTest : public CDialogEx
{
	DECLARE_DYNAMIC(CAdoTest)

public:
	CAdoTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdoTest();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_str1;
	CString m_str2;
	CString m_str3;
};
