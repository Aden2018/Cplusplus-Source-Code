#if !defined(AFX_RELATEADD_H__42D9C9B7_AAC2_47D2_A709_0B74920202CA__INCLUDED_)
#define AFX_RELATEADD_H__42D9C9B7_AAC2_47D2_A709_0B74920202CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RelateAdd.h : header file
//
#include "editex.h"
#include "qiuXpbutton.h"

/////////////////////////////////////////////////////////////////////////////
// CRelateAdd dialog

class CRelateAdd : public CDialog
{
// Construction
public:
	CFont fontTitle;
	CString strEmp;
	CRelateAdd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRelateAdd)
	enum { IDD = IDD_DIALOG_RELATE_ADD };
	CEditEx	c_money;
	CComboBox	c_type;
	CComboBox	c_sex;
	CEditEx	c_bm;
	CEditEx	c_emp;
	CQiuXpButton	m_3;
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CEditEx	c_name;
	COleDateTime	m_date;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRelateAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ComputeCash();

	// Generated message map functions
	//{{AFX_MSG(CRelateAdd)
	virtual void OnButton1();
	virtual void OnOK();
	virtual void OnSelchangeComboType();
	virtual void OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RELATEADD_H__42D9C9B7_AAC2_47D2_A709_0B74920202CA__INCLUDED_)
