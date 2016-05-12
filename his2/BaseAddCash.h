//baseAddCash.h
//
// 类描述:
//		作为其他类的基类,提供了一些通用按钮及对话框操作模板
//
//
/////////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_BASEADDCASH_H__8E5C91FB_7862_411B_94B7_FE2217DCA643__INCLUDED_)
#define AFX_BASEADDCASH_H__8E5C91FB_7862_411B_94B7_FE2217DCA643__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseAddCash.h : header file
//
#include "editex.h"
#include "qiuXpButton.h"
/////////////////////////////////////////////////////////////////////////////
// CBaseAddCash dialog

class CBaseAddCash : public CDialog
{
// Construction
public:
	CFont fontTitle;
	CString strTitle;
	CBaseAddCash(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBaseAddCash)
	enum { IDD = IDD_DIALOG_BASE_ADD_CASH };
	CQiuXpButton	m_b6;
	CQiuXpButton	m_b5;
	CQiuXpButton	m_b4;
	CQiuXpButton	m_b3;
	CQiuXpButton	m_b2;
	CQiuXpButton	m_b1;
	CStatic	m_xe1;
	CEditEx	e9;
	CEditEx	e8;
	CEditEx	e7;
	CEdit	e6;
	CEditEx	e5;
	CEditEx	e4;
	CEditEx	e3;
	CEditEx	e2;
	CEditEx	e1;
	CDateTimeCtrl	d2;
	CDateTimeCtrl	d1;
	CComboBox	c3;
	CComboBox	c2;
	CComboBox	c1;
	CStatic	m_xe4;
	CStatic	m_xe3;
	CStatic	m_xe2;
	CStatic	m_e4;
	CStatic	m_e3;
	CStatic	m_e2;
	CStatic	m_e1;
	CStatic	m_sx4;
	CStatic	m_sx3;
	CStatic	m_sx2;
	CStatic	m_sx1;
	CStatic	m_s4;
	CStatic	m_s3;
	CStatic	m_s2;
	CStatic	m_s1;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseAddCash)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBaseAddCash)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnExcel();
	virtual void OnB2();
	virtual void OnB1();
	virtual void OnB3();
	virtual void OnDblClickMshflexgrid1();
	virtual void OnClickMshflexgrid1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEADDCASH_H__8E5C91FB_7862_411B_94B7_FE2217DCA643__INCLUDED_)
