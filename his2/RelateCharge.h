//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_RELATECHARGE_H__E569085D_B805_4029_933C_43A2DDC67687__INCLUDED_)
#define AFX_RELATECHARGE_H__E569085D_B805_4029_933C_43A2DDC67687__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RelateCharge.h : header file
//
#include "qiuXpButton.h"
#include "editEx.h"
/////////////////////////////////////////////////////////////////////////////
// CRelateCharge dialog

class CRelateCharge : public CDialog
{
// Construction
public:
	long preRow;
	void SetGridHead();
	CFont fontTitle;
	CRelateCharge(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRelateCharge)
	enum { IDD = IDD_DIALOG_RELATE_CHARGE };
	CQiuXpButton	m_33;
	CComboBox	c_combo2;
	CQiuXpButton	m_267;
	CEditEx	c_name;
	CEditEx	m_bm;
	CQiuXpButton	m_26;
	CQiuXpButton	m_25;
	CQiuXpButton	m_24;
	CQiuXpButton	m_23;
	CComboBox	c_combo1;
	CMSHFlexGrid	m_grid;
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRelateCharge)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRelateCharge)
	virtual void OnButtonAdd();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonToexcel();
	virtual void OnClickMshflexgrid1();
	virtual void OnButtonDeleteRow();
	virtual void OnButtonCostQuery();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RELATECHARGE_H__E569085D_B805_4029_933C_43A2DDC67687__INCLUDED_)
