//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_PANDIANLIST_H__537E03E1_A571_41D9_A4AE_E9B2D1D4A0A2__INCLUDED_)
#define AFX_PANDIANLIST_H__537E03E1_A571_41D9_A4AE_E9B2D1D4A0A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PandianList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPandianList form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CPandianList : public CFormView
{
protected:
	CPandianList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPandianList)

// Form Data
public:
	//{{AFX_DATA(CPandianList)
	enum { IDD = ID_FORM_RKLIST };
	CQiuXpButton	m_f;
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
	//{{AFX_VIRTUAL(CPandianList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPandianList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPandianList)
	afx_msg void OnDestroy();
	afx_msg void OnDblClickMshflexgrid1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonToExcel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANDIANLIST_H__537E03E1_A571_41D9_A4AE_E9B2D1D4A0A2__INCLUDED_)
