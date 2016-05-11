#if !defined(AFX_GHQUERY_H__6536CB7F_C36A_4BC8_BD17_79045C46D99E__INCLUDED_)
#define AFX_GHQUERY_H__6536CB7F_C36A_4BC8_BD17_79045C46D99E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GhQuery.h : header file
//DATE:2014/09/22
//author:LingShaoQing
//summary:
//		为查询提供参数，可以进行明细、人员、期号等查询，并可输出到Excel

#include "userQuery.h"
#include <vector>
/////////////////////////////////////////////////////////////////////////////
// CGhQuery dialog
//稿费列表人查询
class CGhQuery : public CDialog
{
// Construction
public:
	static UINT  QueryGhList(LPVOID ps);
	CGhQuery(CWnd* pParent = NULL);   // standard constructor
	CStringArray arrType,arrFactory,arrArticleType;
// Dialog Data
	//{{AFX_DATA(CGhQuery)
	enum { IDD = IDD_DIALOG_GH_QUERY };
	CComboBox	m_Type;
	CComboBox	m_Factory;
	CComboBox	m_articleType;
	COleDateTime	m_date;
	COleDateTime	m_date2;
	CString	m_strEditor;
	CString	m_strEnd;
	CString	m_strStart;
	CString	m_strTitle;
	CString	m_strLayoutNum;
	//}}AFX_DATA
	vector<int> vtAlign;
	enum{ GRID_ID=5 };
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGhQuery)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGhQuery)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClassify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedClassifyExcel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GHQUERY_H__6536CB7F_C36A_4BC8_BD17_79045C46D99E__INCLUDED_)
