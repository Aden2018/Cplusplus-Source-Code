#if !defined(AFX_MAKEFEE_H__5D0BE0E9_C349_4671_80F6_ABFC27C74B41__INCLUDED_)
#define AFX_MAKEFEE_H__5D0BE0E9_C349_4671_80F6_ABFC27C74B41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MakeFee.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMakeFee dialog

class CMakeFee : public CDialog
{
// Construction
public:
	CMakeFee(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMakeFee)
	enum { IDD = IDD_DIALOG_MAKE_FEE };
	CComboBox	m_MakeFactory;
	CListBox	m_listBox;
	CComboBox	m_ReleaseNum;
	CComboBox	m_FeeType;
	CString	m_strCmt;
	COleDateTime	m_rq;
	COleDateTime	m_rq2;
	CString	m_strFee;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMakeFee)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	CStringArray m_arrType,m_arrISSN,m_arrList;
	CStringArray m_arrFactory,arrNewsType;
	CString strSql;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMakeFee)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboFeeType();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDel();
	virtual void OnOK();
	afx_msg void OnButtonClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ResetData();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAKEFEE_H__5D0BE0E9_C349_4671_80F6_ABFC27C74B41__INCLUDED_)
