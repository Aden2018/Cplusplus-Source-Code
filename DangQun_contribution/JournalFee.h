#if !defined(AFX_JOURNALFEE_H__14D993BE_3A1F_479A_9645_F08E2EEE8F52__INCLUDED_)
#define AFX_JOURNALFEE_H__14D993BE_3A1F_479A_9645_F08E2EEE8F52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JournalFee.h : header file
//DATE:2014/09/22
//author:LingShaoQing
//summary:
//		稿费录入模块

/////////////////////////////////////////////////////////////////////////////
// CJournalFee dialog
#include "QiuXpButton.h"
#include <string>
class CJournalFee : public CDialog
{
// Construction
public:
	CJournalFee(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CJournalFee)
	enum { IDD = IDD_DIALOG_JOURNAL_CONTRIBUTION_FEE };
	CComboBox	m_releaseNum;
	CComboBox	m_Factory;
	CComboBox	m_releaseType;
	CComboBox	m_newsType;
	CString	m_strEditor;
	CString	m_Fee;
	CString	m_layout;
	CString	m_strTitle;
	//}}AFX_DATA
	string szProName; //存储过程名
	
	CQiuXpButton xpButton[2];
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJournalFee)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	CString strSql;
	CStringArray arrNewsType,arrReleaseType,arrFactory;
	CStringArray arrReleaseNum,arrNewType;

// Implementation
protected:
	int iSel;
	// Generated message map functions
	//{{AFX_MSG(CJournalFee)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnKillfocusEditEditor();
	afx_msg void OnKillfocusComboBaokanType();
	afx_msg void OnSelchangeComboFactory();
	afx_msg void OnCbnSelchangeComboRelType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ResetCtrl();
public:
	CComboBox m_NewType;	//新增文章类型，代替之前的文章类型分类
	CString m_words;
	afx_msg void OnEnChangeEditWords();
	CFont ftTitle;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CFont cFont;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JOURNALFEE_H__14D993BE_3A1F_479A_9645_F08E2EEE8F52__INCLUDED_)
