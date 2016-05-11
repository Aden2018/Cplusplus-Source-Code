//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_REPORTDECHARGELIST_H__DA5E1437_8131_456B_9350_60FE7BEC2BA4__INCLUDED_)
#define AFX_REPORTDECHARGELIST_H__DA5E1437_8131_456B_9350_60FE7BEC2BA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportDechargeList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportDechargeList form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CReportDechargeList : public CFormView
{
protected:
	CReportDechargeList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CReportDechargeList)

// Form Data
public:
	//{{AFX_DATA(CReportDechargeList)
	enum { IDD = IDD_FORM_DECHARGELIST };

	//}}AFX_DATA
	enum{GRID_ID= 7 };
// Attributes
public:
private:
	CFont fontTitle,font;
	CString TITLE;
// Operations
public:
	CGridCtrl m_grid;
	vector<int> vtAlign;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDechargeList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CReportDechargeList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CReportDechargeList)
	afx_msg void OnDestroy();
	afx_msg void OnDblClickMshflexgrid1(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnClickMshflexgrid1();
	afx_msg void OnMenuitemReportExcel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDECHARGELIST_H__DA5E1437_8131_456B_9350_60FE7BEC2BA4__INCLUDED_)
