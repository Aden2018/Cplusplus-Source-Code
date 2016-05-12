#if !defined(AFX_DIALOGMEDDL_H__CD0760F0_1AA5_4FA4_8903_55000E200DC1__INCLUDED_)
#define AFX_DIALOGMEDDL_H__CD0760F0_1AA5_4FA4_8903_55000E200DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogMedDL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogMedDL dialog

#include "Editex.h"
class CDialogMedDL : public CDialog
{
// Construction
public:
	CFont fontTitle;
	CDialogMedDL(CWnd* pParent = NULL);   // standard constructor
	virtual BOOL ReadName();
// Dialog Data
	//{{AFX_DATA(CDialogMedDL)
	enum { IDD = IDD_DIALOG_DL };
	CQiuXpButton	m_4;
	CQiuXpButton	m_3;
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CEditEx	m_xx;
	CComboBox	m_xcCombo;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogMedDL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogMedDL)
	virtual void OnAdd();
	virtual void OnDelete();
	virtual void OnModify();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGMEDDL_H__CD0760F0_1AA5_4FA4_8903_55000E200DC1__INCLUDED_)
