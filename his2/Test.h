#if !defined(AFX_TEST_H__A17D508F_9934_4594_9076_4B9F6E1EB265__INCLUDED_)
#define AFX_TEST_H__A17D508F_9934_4594_9076_4B9F6E1EB265__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Test.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTest dialog

class CTest : public CDialog
{
// Construction
public:
	CFont font1;
	CTest(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTest)
	enum { IDD = IDD_DIALOG1 };
	CString	m_str1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTest)
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_H__A17D508F_9934_4594_9076_4B9F6E1EB265__INCLUDED_)
