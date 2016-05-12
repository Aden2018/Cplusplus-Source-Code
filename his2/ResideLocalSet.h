//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_RESIDELOCALSET_H__31AB6BCB_588E_41CF_83BA_7DFA93F58E47__INCLUDED_)
#define AFX_RESIDELOCALSET_H__31AB6BCB_588E_41CF_83BA_7DFA93F58E47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResideLocalSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResideLocalSet dialog

class CResideLocalSet : public CDialog
{
// Construction
public:
	CResideLocalSet(CWnd* pParent = NULL);   // standard constructor
	enum { SUCCESS=0,FAIL};
// Dialog Data
	//{{AFX_DATA(CResideLocalSet)
	enum { IDD = IDD_DIALOG_RESIDE_LOCAL };
	CComboBox	m_combox;
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CMSHFlexGrid	m_grid;
	CString	m_strBm;
	CString	m_strMc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResideLocalSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString strTitle;
	int CheckSelectRow();

	// Generated message map functions
	//{{AFX_MSG(CResideLocalSet)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickMshflexgrid1();
	virtual void OnMenuResideLocalAdd();
	virtual void OnMenuResideLocalRefresh();
	virtual void OnMenuResideLocalDel();
	virtual void OnMenuResideLocalModify();
	virtual void OnDblClickMshflexgrid1();
	afx_msg void OnChangeEditMc();
	afx_msg void OnSelchangeCombo1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	long curRow;
	void SetGridHead();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIDELOCALSET_H__31AB6BCB_588E_41CF_83BA_7DFA93F58E47__INCLUDED_)
