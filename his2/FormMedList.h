#include "qiuXpButton.h"
//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_FORMMEDLIST_H__B6F917D1_301F_49C9_8C1B_A97DD45AD1F3__INCLUDED_)
#define AFX_FORMMEDLIST_H__B6F917D1_301F_49C9_8C1B_A97DD45AD1F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormMedList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormMedList form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CFormMedList : public CFormView
{
protected:
	CFormMedList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFormMedList)

// Form Data
public:
	//{{AFX_DATA(CFormMedList)
	enum { IDD = ID_FORM_RKLIST };
	CQiuXpButton	m_f;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	CFont fontTitle;
	long curRow;
	void SetGridHead();
	void OnDblClickMshflexgrid1();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormMedList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFormMedList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFormMedList)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnClickMshflexgrid1();
	afx_msg void OnQmBaofei();
	afx_msg void OnQmModifyMed();
	afx_msg void OnButtonToExcel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMMEDLIST_H__B6F917D1_301F_49C9_8C1B_A97DD45AD1F3__INCLUDED_)
