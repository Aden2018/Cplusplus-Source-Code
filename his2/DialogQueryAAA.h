#if !defined(AFX_DIALOGQUERYAAA_H__40F9DBCB_F9DF_4174_A21D_5466B3C01A61__INCLUDED_)
#define AFX_DIALOGQUERYAAA_H__40F9DBCB_F9DF_4174_A21D_5466B3C01A61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogQueryAAA.h : header file
//-----------------------------------------------------------------------
// 类描述:
//	此类用于各种费用报销情况查询,由 COtherDechargeQuery类调用本类
//	日期: 2005/3/5
//-----------------------------------------------------------------------
//	修改记录

/////////////////////////////////////////////////////////////////////////////
// CDialogQueryAAA dialog
#include "qiuXpbutton.h"

class CDialogQueryAAA : public CDialog
{
// Construction
public:
	CString strSql2;
	CString strSql;
	CDialogQueryAAA(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogQueryAAA)
	enum { IDD = IDD_DIALOG_RELATE_CHARGE_ADDQUERY };
	CQiuXpButton	m_3;
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CListBox	listC;
	CListBox	listB;
	CListBox	listA;
	CComboBox	combo1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogQueryAAA)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogQueryAAA)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnDblclkList1();
	afx_msg void OnDblclkList2();
	afx_msg void OnDblclkList3();
	afx_msg void OnButtonClear();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CStringArray typeArray;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGQUERYAAA_H__40F9DBCB_F9DF_4174_A21D_5466B3C01A61__INCLUDED_)
