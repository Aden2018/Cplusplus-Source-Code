#if !defined(AFX_OPERATORADD_H__E223CEC2_BDD3_4432_8431_C99586D7F3CE__INCLUDED_)
#define AFX_OPERATORADD_H__E223CEC2_BDD3_4432_8431_C99586D7F3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OperatorAdd.h : header file
//
#include "editEx.h"

/////////////////////////////////////////////////////////////////////////////
// COperatorAdd dialog

class COperatorAdd : public CDialog
{
// Construction
public:
	CString str[10];
	UINT flag;
	CFont fontTitle;
	CString strTitle;
	COperatorAdd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COperatorAdd)
	enum { IDD = IDD_DIALOG_OPERATOR_ADD };
	CEditEx	pass2;
	CEditEx	pass1;
	CEditEx	name;
	CEditEx	attr;
	CComboBox	combo1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperatorAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COperatorAdd)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERATORADD_H__E223CEC2_BDD3_4432_8431_C99586D7F3CE__INCLUDED_)
