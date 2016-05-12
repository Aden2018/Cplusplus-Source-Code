#include "qiuXpButton.h"
#if !defined(AFX_QUERY_H__02233703_D66B_46A8_BB84_506ED95EB853__INCLUDED_)
#define AFX_QUERY_H__02233703_D66B_46A8_BB84_506ED95EB853__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Query.h : header file
//
#include "editEx.h"
/////////////////////////////////////////////////////////////////////////////
// CQuery dialog
#include "progress.h"

class CQuery : public CDialog
{
// Construction
public:
	CQuery(CWnd* pParent = NULL);   // standard constructor
	CString strFlag; //作为其它人员体检信息标志
// Dialog Data
	//{{AFX_DATA(CQuery)
	enum { IDD = IDD_DIALOG_QUERY };
	CQiuXpButton	m_x2;
	CQiuXpButton	m_x1;
	CEditEx	m_xm;
	CEditEx	m_kh;
	CComboBox	m_bz;
	CComboBox	m_bm;
	BOOL	m_bLastCheck;
	BOOL	m_bD3;
	BOOL	m_bX3;
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQuery)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboBm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	DoublePointer pParent;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERY_H__02233703_D66B_46A8_BB84_506ED95EB853__INCLUDED_)
