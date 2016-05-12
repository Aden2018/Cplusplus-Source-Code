#if !defined(AFX_DIALOGMEDXL_H__61F199BA_CFA9_42F5_829D_D653C2393715__INCLUDED_)
#define AFX_DIALOGMEDXL_H__61F199BA_CFA9_42F5_829D_D653C2393715__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogMedXL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogMedXL dialog
#include "qiuXpbutton.h"
#include "editEx.h"
class CDialogMedXL : public CDialog
{
// Construction
public:
	BOOL GetBm(CString strSql,CString &bm);
	static BOOL ReadName( CString strSql, CComboBox &combo);
	CFont fontTitle;
	CDialogMedXL(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogMedXL)
	enum { IDD = IDD_DIALOG_XL };
	CQiuXpButton	m_15;
	CQiuXpButton	m_14;
	CQiuXpButton	m_13;
	CQiuXpButton	m_12;
	CEditEx	m_1;
	CComboBox	m_xComboXL;
	CComboBox	m_xComboDL;
	CString	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogMedXL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogMedXL)
	virtual void OnDelete();
	virtual BOOL OnInitDialog();
	virtual void OnAdd();
	virtual void OnModify();
	virtual void OnSelchangeComboDl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGMEDXL_H__61F199BA_CFA9_42F5_829D_D653C2393715__INCLUDED_)
