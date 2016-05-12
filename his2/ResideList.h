//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_RESIDELIST_H__369A3822_F51E_4D25_84DB_BF04C7760421__INCLUDED_)
#define AFX_RESIDELIST_H__369A3822_F51E_4D25_84DB_BF04C7760421__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResideList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResideList form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CResideList : public CFormView
{
protected:
	CResideList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CResideList)

// Form Data
public:
	//{{AFX_DATA(CResideList)
	enum { IDD = ID_FORM_RKLIST };
	CQiuXpButton	m_button;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA

// Attributes
public:
	CFont fontTitle;
	long curRow;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResideList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CResideList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CResideList)
	afx_msg void OnDestroy();
	afx_msg void OnDblClickMshflexgrid1();
	afx_msg void OnClickMshflexgrid1();
	afx_msg void OnMenuQuickResideMedquery();
	afx_msg void OnMenuResideAddPrice();
	afx_msg void OnMenuResidePricequery();
	afx_msg void OnMenuResideHuajia();
	afx_msg void OnMenuResideDelete();
	afx_msg void OnMenuResideCheckout();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void SetGridHead();
private:
	BOOL CheckStatus();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIDELIST_H__369A3822_F51E_4D25_84DB_BF04C7760421__INCLUDED_)
