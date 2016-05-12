#if !defined(AFX_BASEOTHERSICKADD_H__E60F0120_0961_400E_9B69_BB8A90C57D36__INCLUDED_)
#define AFX_BASEOTHERSICKADD_H__E60F0120_0961_400E_9B69_BB8A90C57D36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseOtherSickAdd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBaseOtherSickAdd dialog
#include "editEx.h"
class CBaseOtherSickAdd : public CDialog
{
// Construction
public:
	CString str[10];
	UINT flag;
	CString strSql;
	CString strTitle;
	CFont fontTitle;
	CBaseOtherSickAdd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBaseOtherSickAdd)
	enum { IDD = IDD_DIALOG_BASE_OTHERSICK };
	CEditEx	edit2;
	CEditEx	edit1;
	CComboBox	attr;
	CComboBox	sex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseOtherSickAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBaseOtherSickAdd)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEOTHERSICKADD_H__E60F0120_0961_400E_9B69_BB8A90C57D36__INCLUDED_)
