#include "editEx.h"
#include "qiuXpButton.H"
#if !defined(AFX_DIALOGGHQUERY_H__3BEFB3D7_4589_4D23_95E0_C4B1BDD2E5F4__INCLUDED_)
#define AFX_DIALOGGHQUERY_H__3BEFB3D7_4589_4D23_95E0_C4B1BDD2E5F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogGhQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogGhQuery dialog

class CDialogGhQuery : public CDialog
{
// Construction
public:
	static UINT  QueryGhList(LPVOID ps);
	CString strSFY;
	CString strdoctorbm;
	CStringArray arrGHType;
	CFont fontTitle;
	CDialogGhQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogGhQuery)
	enum { IDD = IDD_DIALOG_GHLIST_QUERY };
	CComboBox	c_empType;
	CComboBox	c_status;
	CEdit	c_sfy;
	CQiuXpButton	m_342;
	CQiuXpButton	m_3;
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CEditEx	c_name;
	CEditEx	c_doctorname;
	CComboBox	c_type;
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	BOOL	m_sf;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogGhQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogGhQuery)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonDoctor();
	afx_msg void OnPaint();
	afx_msg void OnButtonSfy();
	afx_msg void OnSelchangeComboGhtype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGGHQUERY_H__3BEFB3D7_4589_4D23_95E0_C4B1BDD2E5F4__INCLUDED_)
