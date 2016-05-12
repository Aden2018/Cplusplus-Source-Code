#if !defined(AFX_CODEGYSEDIT_H__3954F7D3_5F96_4791_9DB4_F2FB729E19D2__INCLUDED_)
#define AFX_CODEGYSEDIT_H__3954F7D3_5F96_4791_9DB4_F2FB729E19D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeGysEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeGysEdit dialog
#include "QiuXpButton.h"
class CCodeGysEdit : public CDialog
{
// Construction
public:
	UINT flag;
	CCodeGysEdit(CWnd* pParent = NULL);   // standard constructor
	CString m_str[5];
// Dialog Data
	//{{AFX_DATA(CCodeGysEdit)
	enum { IDD = IDD_DIALOG_GYS_ADD };
	CComboBox	combo1;
	CEditFlat	c_py;
	CEditFlat	c_mc;
	CEditFlat	c_bm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeGysEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCodeGysEdit)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODEGYSEDIT_H__3954F7D3_5F96_4791_9DB4_F2FB729E19D2__INCLUDED_)
