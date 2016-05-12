#if !defined(AFX_BASEPROJECTSET_H__CC3FA2FB_47FA_4B53_BDF4_8147CF8E61D2__INCLUDED_)
#define AFX_BASEPROJECTSET_H__CC3FA2FB_47FA_4B53_BDF4_8147CF8E61D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseProjectSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBaseProjectSet dialog

#include "editEx.h"

class CBaseProjectSet : public CDialog
{
// Construction
public:
	UINT flag;
	CString strTitle,strSql,str[10];
	CFont fontTitle;
	CBaseProjectSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBaseProjectSet)
	enum { IDD = IDD_DIALOG_BASE_PROJECT_SET };
	CEditEx	editStandardCash;
	CEditEx	editCode;
	CEditEx	editPY;
	CEditEx	edit2;
	CEditEx	edit1;
	CComboBox	combo1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseProjectSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBaseProjectSet)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEPROJECTSET_H__CC3FA2FB_47FA_4B53_BDF4_8147CF8E61D2__INCLUDED_)
