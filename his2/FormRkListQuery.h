#include "qiuXpButton.h"
#if !defined(AFX_FORMRKLISTQUERY_H__C2C72C6B_9C26_483C_AE7A_6A7E6205BC7E__INCLUDED_)
#define AFX_FORMRKLISTQUERY_H__C2C72C6B_9C26_483C_AE7A_6A7E6205BC7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormRkListQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormRkListQuery dialog

class CFormRkListQuery : public CDialog
{
// Construction
public:
	CString strCombo1Kfbm;
	CString strRkyID;
	CString strRkyName;
	CString strFactoryName,strFactoryID,strYwyID,strYwyName;
	CFormRkListQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFormRkListQuery)
	enum { IDD = ID_FORM_RKLIST_QUERY };
	CEditFlat	c_editYpbm;
	CEditFlat	c_editRky;
	CQiuXpButton	c_brk;
	CQiuXpButton	m_fa;
	CEditFlat	c_editFactory;
	CEditFlat	c_editYwy;
	CQiuXpButton	c_ywy;
	CQiuXpButton	m_3;
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CComboBox	c_combo2;
	CComboBox	c_combo1;
	CEditFlat	c_py;
	CEditFlat	c_gys;
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormRkListQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFormRkListQuery)
	virtual void OnOK();
	afx_msg void OnButtonGys();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonFactory();
	afx_msg void OnButtonYwy();
	afx_msg void OnButtonRky();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMRKLISTQUERY_H__C2C72C6B_9C26_483C_AE7A_6A7E6205BC7E__INCLUDED_)
