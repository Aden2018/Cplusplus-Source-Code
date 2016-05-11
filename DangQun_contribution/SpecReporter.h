#pragma once

#include <vector>
#include <string>
#include "QiuXpButton.h"
/* Date:	2014/09/23
	Author:LingShaoQing
	abstract:
		���ô洢����prc_compute_reporter��ָ����ȵ���ԼͨѶԱ����ĳһ����
		�ĸ�귭������
*/
using namespace std;
class CSpecReporter : public CDialogEx
{
	DECLARE_DYNAMIC(CSpecReporter)

public:
	CSpecReporter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSpecReporter();

// �Ի�������
	enum { IDD = IDD_DIALOG_SPEC_REPORTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	vector<int> vtType;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CComboBox m_cbType;
	CComboBox m_cbYear;
	CString m_szStart;
	CString m_szEnd;
	virtual BOOL OnInitDialog();
	string szProName;
	string SZERROR;
	CQiuXpButton m_btnOK;
	CQiuXpButton m_btnCancel;
};
