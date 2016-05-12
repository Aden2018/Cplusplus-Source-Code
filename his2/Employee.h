#if !defined(AFX_EMPLOYEE_H__5C5F1CC0_2929_4289_BCF3_1FE774652F60__INCLUDED_)
#define AFX_EMPLOYEE_H__5C5F1CC0_2929_4289_BCF3_1FE774652F60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Employee.h : header file
//
#include "qiuXpButton.h"
#include "editEx.h"
/////////////////////////////////////////////////////////////////////////////
// CEmployee dialog

class CEmployee : public CDialog
{
// Construction
public:
	CStringArray m_depart;
	CFont fontTitle;
	CString strTitle;
	CEmployee(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEmployee)
	enum { IDD = IDD_DIALOG_EMPLOYEE };
	CComboBox	c_depart;
	CEditEx	c_kahao;
	CEditEx	c_name;
	CComboBox	c_sort;
	CComboBox	c_sex;
	CComboBox	c_property;
	CQiuXpButton	m_b3;
	CQiuXpButton	m_b2;
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmployee)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEmployee)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMPLOYEE_H__5C5F1CC0_2929_4289_BCF3_1FE774652F60__INCLUDED_)
