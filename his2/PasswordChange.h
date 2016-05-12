#if !defined(AFX_PASSWORDCHANGE_H__36AF362F_5DFE_4447_9733_7997E8DC683A__INCLUDED_)
#define AFX_PASSWORDCHANGE_H__36AF362F_5DFE_4447_9733_7997E8DC683A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PasswordChange.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPasswordChange dialog

class CPasswordChange : public CDialog
{
// Construction
public:
	CFont fontTitle;
	CPasswordChange(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPasswordChange)
	enum { IDD = IDD_DIALOG_CHANGE_PASSWORD };
	CQiuXpButton	m_33;
	CQiuXpButton	m_22;
	CEditFlat	m_3;
	CEditFlat	m_2;
	CEditFlat	m_1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPasswordChange)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPasswordChange)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSWORDCHANGE_H__36AF362F_5DFE_4447_9733_7997E8DC683A__INCLUDED_)
