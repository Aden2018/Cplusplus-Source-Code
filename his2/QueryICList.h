//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_QUERYICLIST_H__A20C429C_1B38_40FC_A9EE_34D35E13AEDD__INCLUDED_)
#define AFX_QUERYICLIST_H__A20C429C_1B38_40FC_A9EE_34D35E13AEDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QueryICList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQueryICList form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CQueryICList : public CFormView
{
protected:
	CQueryICList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CQueryICList)
private:
	long curRow; //用户选择的当前行

// Form Data
public:
	//{{AFX_DATA(CQueryICList)
	enum { IDD = ID_FORM_RKLIST };
	CQiuXpButton	m_232;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	CFont fontTitle;
	void SetGridHead();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryICList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CQueryICList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CQueryICList)
	afx_msg void OnDestroy();
	afx_msg void OnButtonToExcel();
	afx_msg void OnDblClickMshflexgrid1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClickMshflexgrid1();
	DECLARE_EVENTSINK_MAP()
	afx_msg void OnQmUserMed();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYICLIST_H__A20C429C_1B38_40FC_A9EE_34D35E13AEDD__INCLUDED_)
