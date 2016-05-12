#if !defined(AFX_DSRECIVE_H__E306A604_6A4F_427C_A04C_7A4ADDB741E6__INCLUDED_)
#define AFX_DSRECIVE_H__E306A604_6A4F_427C_A04C_7A4ADDB741E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DSRecive.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDSRecive dialog

class CDSRecive : public CDialog //选择添加收件人信息
{
// Construction
public:
	CString strName;
	CListCtrl * pList;
	CDSRecive(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDSRecive)
	enum { IDD = ID_FORM_SEND_RECIVE };
	CComboBox	c_depart;
	CListCtrl	c_list2;
	CListCtrl	c_list1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSRecive)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDSRecive)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboDepart();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnButtonAll();
	afx_msg void OnButtonDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSRECIVE_H__E306A604_6A4F_427C_A04C_7A4ADDB741E6__INCLUDED_)
