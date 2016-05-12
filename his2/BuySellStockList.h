//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_BUYSELLSTOCKLIST_H__9CFBF8B4_32BC_43B4_8603_20D49DFACB2B__INCLUDED_)
#define AFX_BUYSELLSTOCKLIST_H__9CFBF8B4_32BC_43B4_8603_20D49DFACB2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuySellStockList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuySellStockList form view
#include "qiuXpButton.h"

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CBuySellStockList : public CFormView
{
protected:
	CBuySellStockList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CBuySellStockList)

// Form Data
public:
	//{{AFX_DATA(CBuySellStockList)
	enum { IDD = ID_FORM_RKLIST };
	CQiuXpButton	m_xbt;
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
	//{{AFX_VIRTUAL(CBuySellStockList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBuySellStockList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CBuySellStockList)
	afx_msg void OnDblClickMshflexgrid1();
	afx_msg void OnButtonToExcel();
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUYSELLSTOCKLIST_H__9CFBF8B4_32BC_43B4_8603_20D49DFACB2B__INCLUDED_)
