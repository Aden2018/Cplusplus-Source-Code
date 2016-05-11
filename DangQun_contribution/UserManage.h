#pragma once

#include <vector>
#include "QiuXpButton.h"
// CUserManage 对话框

class CUserManage : public CDialogEx
{
	DECLARE_DYNAMIC(CUserManage)

public:
	CUserManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserManage();
	vector<int> vtAlign;
	CGridCtrl m_grid;
	CFont ft,font;
	CComboBox cb; 
	int iRow,iCol;
// 对话框数据
	enum { IDD = IDD_DIALOG_USER_MANAGE };
	enum {IDC_COMBO_STATUS = WM_USER+11 };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedOk();
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
protected:
//	afx_msg LRESULT OnGvnEndlabeledit(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedRightManage();
	CQiuXpButton m_btnCancel;
	CQiuXpButton m_btnOK;
	CQiuXpButton m_ts;
	CQiuXpButton m_btsd;
protected:

public:
	afx_msg void OnCbnSelchangeComboStatus(void);
	afx_msg void OnCbnKillFocus(void);
	void StoreDatabase(void);
};
