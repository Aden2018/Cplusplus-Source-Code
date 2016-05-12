#if !defined(AFX_RESIDEBEDSETADD_H__C29B15A9_70C2_4141_98D4_B8D45FCFCB41__INCLUDED_)
#define AFX_RESIDEBEDSETADD_H__C29B15A9_70C2_4141_98D4_B8D45FCFCB41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResideBedSetAdd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResideBedSetAdd dialog

class CResideBedSetAdd : public CDialog
{
// Construction
public:
	CString strTitle;
	CString strSql;
	CStringArray localArray,roomArray;
	CResideBedSetAdd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResideBedSetAdd)
	enum { IDD = IDD_DIALOG_RESIDE_BED_ADD };
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CComboBox	m_combox_room;
	CComboBox	m_combox_local;
	CString	m_strName;
	CString	m_strRemark;
	double	m_price;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResideBedSetAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResideBedSetAdd)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboLocal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIDEBEDSETADD_H__C29B15A9_70C2_4141_98D4_B8D45FCFCB41__INCLUDED_)
