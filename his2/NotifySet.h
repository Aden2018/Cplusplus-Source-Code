#if !defined(AFX_NOTIFYSET_H__CA90F861_AE55_4C3B_8276_8AFA6F6251B6__INCLUDED_)
#define AFX_NOTIFYSET_H__CA90F861_AE55_4C3B_8276_8AFA6F6251B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NotifySet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNotifySet dialog

class CNotifySet : public CDialog
{
// Construction
public:
	CNotifySet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNotifySet)
	enum { IDD = IDD_DIALOG_NOTIFY_SET };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotifySet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNotifySet)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTIFYSET_H__CA90F861_AE55_4C3B_8276_8AFA6F6251B6__INCLUDED_)
