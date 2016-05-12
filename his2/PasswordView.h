#if !defined(AFX_PASSWORDVIEW_H__464C7958_C480_4DE6_9242_D779E58E07C4__INCLUDED_)
#define AFX_PASSWORDVIEW_H__464C7958_C480_4DE6_9242_D779E58E07C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PasswordView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPasswordView dialog
#include "editEx.h"

class CPasswordView : public CDialog
{
// Construction
public:
	CString str[10];
	CString strTitle;
	CFont fontTitle;
	CPasswordView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPasswordView)
	enum { IDD = IDD_DIALOG_VIEW_PASS };
	CEditEx	edit3;
	CEditEx	edit2;
	CEditEx	edit1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPasswordView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPasswordView)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSWORDVIEW_H__464C7958_C480_4DE6_9242_D779E58E07C4__INCLUDED_)
