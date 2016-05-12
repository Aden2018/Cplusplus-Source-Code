#if !defined(AFX_ROLLMED_H__6AEBE57F_F381_4184_A78C_1416432DD634__INCLUDED_)
#define AFX_ROLLMED_H__6AEBE57F_F381_4184_A78C_1416432DD634__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RollMed.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRollMed dialog

class CRollMed : public CDialog
{
// Construction
public:
//	double oldSL;
	CString str2[10];
	CRollMed(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRollMed)
	enum { IDD = IDD_ROLL_MED };
	CListCtrl	c_listroll;
	CListCtrl	c_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRollMed)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRollMed)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROLLMED_H__6AEBE57F_F381_4184_A78C_1416432DD634__INCLUDED_)
