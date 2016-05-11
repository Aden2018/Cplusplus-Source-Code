#pragma once

#include <vector>
#include <string>
#include "QiuXpButton.h"
/* Date:	2014/09/23
	Author:LingShaoQing
	abstract:
		调用存储过程prc_compute_reporter对指定年度的特约通讯员进行某一区间
		的稿酬翻番操作
*/
using namespace std;
class CSpecReporter : public CDialogEx
{
	DECLARE_DYNAMIC(CSpecReporter)

public:
	CSpecReporter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSpecReporter();

// 对话框数据
	enum { IDD = IDD_DIALOG_SPEC_REPORTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
