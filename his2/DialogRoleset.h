#include "editFlat.h"
#include "qiuXpbutton.h"
#if !defined(AFX_DIALOGROLESET_H__F3B26A36_5A50_4406_9B53_E91A4D801772__INCLUDED_)
#define AFX_DIALOGROLESET_H__F3B26A36_5A50_4406_9B53_E91A4D801772__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogRoleset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogRoleset dialog

class CDialogRoleset : public CDialog
{
// Construction
public:
	CString strRybm;
	CString strParent;
	CString strSel;
	bool flagRy;
	long RoleLines;
	void InsertOperator();
	CDialogRoleset(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogRoleset)
	enum { IDD = IDD_DIALOG_ROLE_SET };
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CEditFlat	c_name;
	CTreeCtrl	c_tree;
	CListCtrl	c_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogRoleset)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogRoleset)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickTreeRy(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkTreeRy(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListRole(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGROLESET_H__F3B26A36_5A50_4406_9B53_E91A4D801772__INCLUDED_)
