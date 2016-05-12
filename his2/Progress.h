#if !defined(AFX_PROGRESS_H__1F5264AD_942E_4E15_B7EB_7C036DD2ED92__INCLUDED_)
#define AFX_PROGRESS_H__1F5264AD_942E_4E15_B7EB_7C036DD2ED92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Progress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgress dialog

class CProgress : public CDialog
{
// Construction
public:
	UINT iYear;
	bool flagRun;
	static UINT createBalanceCount(LPVOID ps);
	static UINT EmpAutoAddCash(LPVOID ps);
	CString strNotify;
	CFont fontTitle;
	CString strView;
	UINT connectFlag;
	static UINT scheduleProgress(LPVOID ps);
	UINT (* pThreadFunction)(LPVOID);
	static UINT RelateAutoAddCash(LPVOID ps);
	CProgress(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgress)
	enum { IDD = IDD_DIALOG_PROGRESS };
	CProgressCtrl	m_p;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgress)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESS_H__1F5264AD_942E_4E15_B7EB_7C036DD2ED92__INCLUDED_)
