#include "resource.h"
#include "editFlat.h"
#include "codeGysQuery.h"
#include "qiuXpButton.h"

#if !defined(AFX_SEARCHMED_H__B4A80674_B038_4397_9F71_4B9C9DC4EE48__INCLUDED_)
#define AFX_SEARCHMED_H__B4A80674_B038_4397_9F71_4B9C9DC4EE48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchMed.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchMed dialog

class CSearchMed : public CDialog
{
// Construction
public:
	CString strGysBm;
	CString strGysName;
	CFont fontTitle;
	CSearchMed(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchMed)
	enum { IDD = IDD_QUERY_MED };
	CQiuXpButton	m_3;
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CComboBox	c_kf;
	CEditFlat	m_sl;
	CEditFlat	m_factory;
	CEditFlat	m_bm;
	CComboBox	c_order;
	CComboBox	c_compare;
	CComboBox	c_comXL;
	CComboBox	c_comDL;
	CEditFlat	m_py;
	CEditFlat	m_mc;
	COleDateTime	m_date2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchMed)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchMed)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeComboDl();
	afx_msg void OnButtonFactory();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHMED_H__B4A80674_B038_4397_9F71_4B9C9DC4EE48__INCLUDED_)
