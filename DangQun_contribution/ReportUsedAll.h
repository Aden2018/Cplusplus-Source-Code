//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_REPORTUSEDALL1_H__EE883D62_BE8C_4486_8E89_C784606309B4__INCLUDED_12)
#define AFX_REPORTUSEDALL1_H__EE883D62_BE8C_4486_8E89_C784606309B4__INCLUDED_12

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportUsedAll1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportUsedAll form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
/*
2012/2/21
���ҩƷ��ѯ



*/

class CReportMedQuery : public CFormView
{
protected:
	CReportMedQuery();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CReportMedQuery)

// Form Data
public:
	//{{AFX_DATA(CReportMedQuery)
	enum { IDD = IDD_FORM_USED_ALL };
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA
	enum { SUM_COL=12,COL_ID=23 }; //�ϼ���
	CFont fontTitle;
	CString TITLE;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportUsedAll)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CReportMedQuery();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CReportUsedAll)
	afx_msg void OnDestroy();
	afx_msg void OnDblClickMshflexgrid1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTUSEDALL1_H__EE883D62_BE8C_4486_8E89_C784606309B4__INCLUDED_)
