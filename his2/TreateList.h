//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_TREATELIST_H__C276D3F2_5FFC_4A38_BBD9_BC08D36FC07D__INCLUDED_)
#define AFX_TREATELIST_H__C276D3F2_5FFC_4A38_BBD9_BC08D36FC07D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreateList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreateList form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CTreateList : public CFormView
{
protected:
	CTreateList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTreateList)

// Form Data
public:
	//{{AFX_DATA(CTreateList)
	enum { IDD = ID_FORM_RKLIST };
	CQiuXpButton	m_x3;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void SetGridHead();
	CFont fontTitle;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreateList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTreateList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTreateList)
	afx_msg void OnDestroy();
	afx_msg void OnDblClickMshflexgrid1();
	afx_msg void OnButtonToExcel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREATELIST_H__C276D3F2_5FFC_4A38_BBD9_BC08D36FC07D__INCLUDED_)
