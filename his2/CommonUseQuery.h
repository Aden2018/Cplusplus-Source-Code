//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_COMMONUSEQUERY_H__94BA6584_A18F_4A34_8B80_DED9D8FF2A6C__INCLUDED_)
#define AFX_COMMONUSEQUERY_H__94BA6584_A18F_4A34_8B80_DED9D8FF2A6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommonUseQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommonUseQuery form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CCommonUseQuery : public CFormView
{
protected:
	CCommonUseQuery();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCommonUseQuery)

// Form Data
public:
	//{{AFX_DATA(CCommonUseQuery)
	enum { IDD = ID_FORM_RKLIST };
	CQiuXpButton	m_5;
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
	//{{AFX_VIRTUAL(CCommonUseQuery)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCommonUseQuery();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CCommonUseQuery)
	afx_msg void OnDblClickMshflexgrid1();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonToExcel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMONUSEQUERY_H__94BA6584_A18F_4A34_8B80_DED9D8FF2A6C__INCLUDED_)
