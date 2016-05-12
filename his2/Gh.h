#if !defined(AFX_GH_H__F2DF0614_CD19_427E_8AEA_49BFDB35CCD1__INCLUDED_)
#define AFX_GH_H__F2DF0614_CD19_427E_8AEA_49BFDB35CCD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Gh.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGh dialog

class CGh : public CDialog
{
// Construction
public:
	CString strWorkType;
	CStringArray arrWorkType;
	CString strIC;
	void OnGetEmployeeInformation();
	BOOL GetBaseRy();
	CString infor[20];
	CString strSql;
	CString strDanjuhao;
	CString strKH,strName;
	CFont fontTitle;
	CGh(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGh)
	enum { IDD = IDD_GH };
	CComboBox	c_sex;
	CStatic	c_message;
	CComboBox	c_type;
	CEditFlat	c_ghf;
	CEditFlat	c_name;
	CQiuXpButton	m_4;
	CQiuXpButton	m_2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGh)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString strDate[2];

	// Generated message map functions
	//{{AFX_MSG(CGh)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGetinformation();
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeComboType();
	afx_msg void OnKillfocusEditName();
	afx_msg void OnSetfocusEditName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GH_H__F2DF0614_CD19_427E_8AEA_49BFDB35CCD1__INCLUDED_)
