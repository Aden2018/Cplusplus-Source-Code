//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_FORMZKLIST_H__70F112DD_4B45_42CD_A2E2_C9D814122E21__INCLUDED_)
#define AFX_FORMZKLIST_H__70F112DD_4B45_42CD_A2E2_C9D814122E21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormZkList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormZkList form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CFormZkList : public CFormView
{
protected:
	CFormZkList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFormZkList)

// Form Data
public:
	//{{AFX_DATA(CFormZkList)
	enum { IDD = ID_FORM_RKLIST };
	CQiuXpButton	m_d;
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
	//{{AFX_VIRTUAL(CFormZkList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFormZkList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFormZkList)
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

#endif // !defined(AFX_FORMZKLIST_H__70F112DD_4B45_42CD_A2E2_C9D814122E21__INCLUDED_)
