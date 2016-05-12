#if !defined(AFX_LOCALSETADD_H__65FED91B_52B1_40BB_B987_E855AF23F3D4__INCLUDED_)
#define AFX_LOCALSETADD_H__65FED91B_52B1_40BB_B987_E855AF23F3D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LocalSetAdd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLocalSetAdd dialog

class CLocalSetAdd : public CDialog
{
// Construction
public:
	CLocalSetAdd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLocalSetAdd)
	enum { IDD = IDD_DIALOG_RESIDE_LOCAL_ADD };
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CString	m_name;
	CString	m_remark;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalSetAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString strTitle;

	// Generated message map functions
	//{{AFX_MSG(CLocalSetAdd)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CString strSql;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCALSETADD_H__65FED91B_52B1_40BB_B987_E855AF23F3D4__INCLUDED_)
