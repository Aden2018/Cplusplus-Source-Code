#include "editFlat.h"
#include "HuaJia.h"	// Added by ClassView
#include "qiuXpButton.h"
#if !defined(AFX_PAYMEDFEE_H__590FD51D_59A8_483A_BF58_1CB007681CBC__INCLUDED_)
#define AFX_PAYMEDFEE_H__590FD51D_59A8_483A_BF58_1CB007681CBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PayMedFee.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPayMedFee dialog

class CPayMedFee : public CDialog
{
// Construction
public:
	CHuaJia * p;
	CString str[20];
	CFont fontTitle;
	CPayMedFee(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPayMedFee)
	enum { IDD = IDD_DIALOG_CHARGE_PRICE };
	CQiuXpButton	m_34;
	CEditFlat	m_pay2;
	CEditFlat	m_med;
	CEditFlat	m_zl;
	CQiuXpButton	m_3;
	CQiuXpButton	m_2;
	CEditFlat	m_should_pay;
	CEditFlat	m_scale;
	CEditFlat	m_real_pay;
	CEditFlat	m_pay;
	CEditFlat	m_more_pay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPayMedFee)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPayMedFee)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditPay();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAYMEDFEE_H__590FD51D_59A8_483A_BF58_1CB007681CBC__INCLUDED_)
