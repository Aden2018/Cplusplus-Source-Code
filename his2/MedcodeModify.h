#if !defined(AFX_MEDCODEMODIFY_H__E7525E70_5408_40B8_8623_B2E928AAAE5E__INCLUDED_)
#define AFX_MEDCODEMODIFY_H__E7525E70_5408_40B8_8623_B2E928AAAE5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MedcodeModify.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMedcodeModify dialog

class CMedcodeModify : public CDialog
{
// Construction
public:
	CString xlmc;
	CString dlmc;
	CString strOldBm;
	UINT flagMode;
	CFont fontTitle;
	CMedcodeModify(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CMedcodeModify)
	enum { IDD = IDD_DIALOG_MEDCODE_ADD ,ADD=0,MODIFY=1};
	CEditFlat	c_bm;
	CComboBox	c_comXL;
	CComboBox	c_comDL;
	CString	m_comment;
	CString	m_dw;
	CString	m_gg;
	CString	m_max;
	CString	m_mc;
	CString	m_min;
	CString	m_py;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedcodeModify)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMedcodeModify)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeCombo2();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDCODEMODIFY_H__E7525E70_5408_40B8_8623_B2E928AAAE5E__INCLUDED_)
