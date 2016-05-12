//{{AFX_INCLUDES()
#include "mshflexgrid.h"
#include "Query.h"	// Added by ClassView
//}}AFX_INCLUDES
#include "qiuXpButton.h"
#if !defined(AFX_HEALTHSEARCH_H__40894CF3_BF4D_473D_8BA2_454005FC40C1__INCLUDED_)
#define AFX_HEALTHSEARCH_H__40894CF3_BF4D_473D_8BA2_454005FC40C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HealthSearch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHealthSearch dialog


class CHealthSearch : public CDialog
{
// Construction
public:
	COLORREF backColor;
	virtual void OnFastMenuSelect(void);
	void OnFastMenuPrint(void);
	COLORREF selBackColor;
	UINT lRow;
	UINT uint_AllRecords;
	UINT uint_records;
	int flagConti;
	bool flagQuery;  //作为查询对话框是否已建立标志
	CQuery condiQuery;
	CBrush staticBrush;
	CHealthSearch(CWnd* pParent = NULL);   // standard constructor
	CFont fontTitle,font2;
	
// Dialog Data
	//{{AFX_DATA(CHealthSearch)
	enum { IDD = IDD_DIALOG_HEALTH_CHECK };
	CQiuXpButton	m_3333;
	CQiuXpButton	m_54;
	CQiuXpButton	m_5;
	CQiuXpButton	m_3;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHealthSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnModify(void);
	virtual void OnDelete(void);
	virtual void OnPrintSelect(void);
	// Generated message map functions
	//{{AFX_MSG(CHealthSearch)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	virtual void OnCancel();
	virtual void OnAdd();
	afx_msg void OnClickMshflexgrid1();
	afx_msg void OnPrint();
	afx_msg void OnDblClickMshflexgrid1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEALTHSEARCH_H__40894CF3_BF4D_473D_8BA2_454005FC40C1__INCLUDED_)
