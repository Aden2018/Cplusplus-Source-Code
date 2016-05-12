#include "editFlat.h"
#include "qiuXpButton.h"
#if !defined(AFX_MEDDETAIL_H__FD577BD1_B2D6_4120_B065_A32490093325__INCLUDED_)
#define AFX_MEDDETAIL_H__FD577BD1_B2D6_4120_B065_A32490093325__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MedDetail.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMedDetail dialog

class CMedDetail : public CDialog
{
// Construction
public:
	UINT FlagRollMED;
//	CBrush brush2;
	CString c_factoryID;
	CFont fontTitle;
	CMedDetail(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMedDetail)
	enum { IDD = IDD_MEDCODE_PRICE };
	CEditFlat	CcurrentPrice;
	CEditFlat	c_coach;
	CEditFlat	c_factory;
	CEditFlat	c_out_price;
	CEditFlat	c_in_price;
	CEditFlat	c_sl;
	CEditFlat	c_dw;
	CEditFlat	c_gg;
	CEditFlat	c_mc;
	CEditFlat	c_bm;
	CEditFlat	c_xl;
	CEditFlat	c_dl;
	CQiuXpButton	m_x3;
	CQiuXpButton	m_x2;
	CQiuXpButton	m_x1;
	COleDateTime	m_riqi1;
	COleDateTime	m_riqi2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedDetail)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMedDetail)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonGys();
	afx_msg void OnKillfocusEdit10();
	afx_msg void OnSetfocusEdit10();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDDETAIL_H__FD577BD1_B2D6_4120_B065_A32490093325__INCLUDED_)
