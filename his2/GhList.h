//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_GHLIST_H__6E92C078_4184_4DE3_8A7A_1DC43C4BADCD__INCLUDED_)
#define AFX_GHLIST_H__6E92C078_4184_4DE3_8A7A_1DC43C4BADCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GhList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGhList form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CGhList : public CFormView
{
protected:
	CGhList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGhList)

// Form Data
public:
	//{{AFX_DATA(CGhList)
	enum { IDD = ID_FORM_RKLIST };
	CQiuXpButton	m_t;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	static UINT CureDetailProcess(LPVOID ps);
	CFont fontTitle;
	long curRow;
	void OnDblClickMshflexgrid1();
	void OnClickMshflexgrid1();
	void SetGridHead();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGhList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGhList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CGhList)
	afx_msg void OnDestroy();
	afx_msg void OnQmUserRollmed();
	afx_msg void OnQmUserMed();
	afx_msg void OnMenuCureDetail();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonToExcel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GHLIST_H__6E92C078_4184_4DE3_8A7A_1DC43C4BADCD__INCLUDED_)
