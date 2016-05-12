#include "qiuXpButton.h"
#include "editFlat.h"

#if !defined(AFX_BASERYADD_H__481CB2BF_3725_4E0B_B41C_AE0015514122__INCLUDED_)
#define AFX_BASERYADD_H__481CB2BF_3725_4E0B_B41C_AE0015514122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseRyAdd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBaseRyAdd dialog

class CBaseRyAdd : public CDialog
{
// Construction
public:
	CString str[3];
	CBaseRyAdd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBaseRyAdd)
	enum { IDD = IDD_DIALOG_BASERY };
	CEditFlat	c_name;
	CEditFlat	c_kh;
	CComboBox	c_sex;
	CQiuXpButton	m_3;
	CQiuXpButton	m_2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseRyAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBaseRyAdd)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASERYADD_H__481CB2BF_3725_4E0B_B41C_AE0015514122__INCLUDED_)
