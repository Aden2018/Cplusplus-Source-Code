//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_GENERICSTOCKMED_H__E100CA6A_CFB4_4CBE_A2CD_3B102ACA252E__INCLUDED_)
#define AFX_GENERICSTOCKMED_H__E100CA6A_CFB4_4CBE_A2CD_3B102ACA252E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GenericStockMed.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGenericStockMed dialog
#include "qiuXpButton.h"
#include "editEx.h"
class CGenericStockMed : public CDialog
{
// Construction
public:
	static UINT QueryData(LPVOID ps);
	virtual void SetGridHead();
	CFont fontTitle;
	CGenericStockMed(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGenericStockMed)
	enum { IDD = IDD_DIALOG_GENERIC_STOCKMED };
	CQiuXpButton	c_print;
	CEditEx	c_edit3;
	CEditEx	c_edit1;
	CQiuXpButton	m_3;
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CMSHFlexGrid	m_grid;
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	COleDateTime	m_date3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenericStockMed)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGenericStockMed)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnButtonExcel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnDblClickMshflexgrid1();
	virtual void OnButtonPrint();
	virtual void OnSelchangeCombo2();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERICSTOCKMED_H__E100CA6A_CFB4_4CBE_A2CD_3B102ACA252E__INCLUDED_)
