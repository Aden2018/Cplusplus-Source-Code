//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_FORMRKLIST_H__D4D81B97_B141_4891_8526_1C28976E7923__INCLUDED_)
#define AFX_FORMRKLIST_H__D4D81B97_B141_4891_8526_1C28976E7923__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormRkList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormRkList form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CFormRkList : public CFormView
{
protected:
	CFormRkList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFormRkList)

// Form Data
public:
	//{{AFX_DATA(CFormRkList)
	enum { IDD = ID_FORM_RKLIST };
	CQiuXpButton	c_button_to_excel;
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
	//{{AFX_VIRTUAL(CFormRkList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFormRkList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFormRkList)
	virtual void OnDblClickMshflexgrid1();
	virtual void OnDestroy();
	afx_msg void OnButtonToExcel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMRKLIST_H__D4D81B97_B141_4891_8526_1C28976E7923__INCLUDED_)
