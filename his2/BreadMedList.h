//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_BREADMEDLIST_H__D8EFA333_D2E8_4820_9954_C8D75138EFEC__INCLUDED_)
#define AFX_BREADMEDLIST_H__D8EFA333_D2E8_4820_9954_C8D75138EFEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BreadMedList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBreadMedList form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CBreadMedList : public CFormView
{
protected:
	CBreadMedList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CBreadMedList)

// Form Data
public:
	//{{AFX_DATA(CBreadMedList)
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
	//{{AFX_VIRTUAL(CBreadMedList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBreadMedList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CBreadMedList)
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

#endif // !defined(AFX_BREADMEDLIST_H__D8EFA333_D2E8_4820_9954_C8D75138EFEC__INCLUDED_)
