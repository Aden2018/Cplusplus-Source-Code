#if !defined(AFX_ACCOUNTSCALE_H__5F846B72_5446_4241_AD65_09DC514EAE93__INCLUDED_)
#define AFX_ACCOUNTSCALE_H__5F846B72_5446_4241_AD65_09DC514EAE93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AccountScale.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAccountScale dialog
#include "qiuXpButton.h"
#include "editEx.h"

class CAccountScale : public CDialog
{
// Construction
public:
	double dbScale[10];
	CFont fontTitle;
	CAccountScale(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAccountScale)
	enum { IDD = IDD_DIALOG_ACCOUNT_SCALE };
	CEditEx	c5;
	CEditEx	c4;
	CEditEx	c3;
	CEditEx	c2;
	CEditEx	c1;
	CEditEx	oc5;
	CEditEx	oc4;
	CEditEx	oc3;
	CEditEx	oc2;
	CEditEx	oc1;
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountScale)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void changeEdit(CEdit *pe1,CEdit *pe2);
	void selEdit(CEdit * pe);
	CString strTitle;

	// Generated message map functions
	//{{AFX_MSG(CAccountScale)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocusEdit21();
	afx_msg void OnSetfocusEdit22();
	afx_msg void OnSetfocusEdit23();
	afx_msg void OnSetfocusEdit24();
	afx_msg void OnSetfocusEdit25();
	afx_msg void OnChangeEdit21();
	afx_msg void OnChangeEdit22();
	afx_msg void OnChangeEdit23();
	afx_msg void OnChangeEdit24();
	afx_msg void OnChangeEdit25();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCOUNTSCALE_H__5F846B72_5446_4241_AD65_09DC514EAE93__INCLUDED_)
