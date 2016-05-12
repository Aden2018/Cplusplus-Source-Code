#if !defined(AFX_RESIDEADDPRICE_H__E2A9DD0F_9624_4E12_925A_CE3FDDDE5CA1__INCLUDED_)
#define AFX_RESIDEADDPRICE_H__E2A9DD0F_9624_4E12_925A_CE3FDDDE5CA1__INCLUDED_

#include "mshflexgrid.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResideAddPrice.h : header file
//
#include "qiuXpbutton.h"
/////////////////////////////////////////////////////////////////////////////
// CResideAddPrice dialog

class CResideAddPrice : public CDialog
{
// Construction
public:
	CString strTitle;
	CMSHFlexGrid * pGrid;
	CResideAddPrice(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResideAddPrice)
	enum { IDD = IDD_DIALOG_RESIDE_PRICE };
	CQiuXpButton	m_3;
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	double	m_dbPrice;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResideAddPrice)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResideAddPrice)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CString m_strFmt;
	CString m_strSerial;
	long m_curRow;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIDEADDPRICE_H__E2A9DD0F_9624_4E12_925A_CE3FDDDE5CA1__INCLUDED_)
