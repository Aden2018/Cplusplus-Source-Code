//{{AFX_INCLUDES()
#include "richtext.h"
//}}AFX_INCLUDES
#if !defined(AFX_OTHERDECHARGE_H__68C438B1_1D8F_4546_9E64_0D01FA218987__INCLUDED_)
#define AFX_OTHERDECHARGE_H__68C438B1_1D8F_4546_9E64_0D01FA218987__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OtherDecharge.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COtherDecharge dialog
#include "qiuXpButton.h"
#include "editEx.h"
//大病医保外诊费用报销
class COtherDecharge : public CDialog 
{
// Construction
public:
	UINT PRINTflag;
	CString strTag;
	static CString GetStringTitle(CString strtag);
	void OnComputeScale();
	static BOOL WriteSQL(CString strSql);
	CString strTitle;
	CFont fontTitle;
	COtherDecharge(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COtherDecharge)
	enum { IDD = IDD_DIALOG_OTHER_DECHARGE };
	CQiuXpButton	m_ps;
	CEditEx	c_scale;
	CEditEx	c10;
	CEditEx	c9;
	CEditEx	c8;
	CEditEx	c7;
	CEditEx	c6;
	CEditEx	c5;
	CEditEx	c4;
	CEditEx	c3;
	CEditEx	c2;
	CEditEx	c1;
	CQiuXpButton	m_a;
	CComboBox	c_type;
	CQiuXpButton	m_c;
	CQiuXpButton	m_o;
	CQiuXpButton	m_p;
	CRichText	c11;
	COleDateTime	m_date1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COtherDecharge)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COtherDecharge)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnEditchangeCombo1();
	afx_msg void OnKillfocusCombo1();
	afx_msg void OnChangeEdit9();
	afx_msg void OnSetfocusEdit9();
	afx_msg void OnKillfocusEdit9();
	afx_msg void OnChangeEdit8();
	virtual void OnButtonA();
	afx_msg void OnPrint();
	afx_msg void OnSearch();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void ClearDialogInformation();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTHERDECHARGE_H__68C438B1_1D8F_4546_9E64_0D01FA218987__INCLUDED_)
