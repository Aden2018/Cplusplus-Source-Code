#include "qiuXpButton.h"
#if !defined(AFX_DIALOGMEDMODIFY_H__B5685788_C35C_46EF_80A2_233D06BC3F30__INCLUDED_)
#define AFX_DIALOGMEDMODIFY_H__B5685788_C35C_46EF_80A2_233D06BC3F30__INCLUDED_

#include "mshflexgrid.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogMedModify.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogMedModify dialog

class CDialogMedModify : public CDialog
{
// Construction
public:
	CString factoryMC;
	CString factoryBM;
	UINT MedID;
	long row;
	CMSHFlexGrid *pg;
	CDialogMedModify(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogMedModify)
	enum { IDD = IDD_DIALOG_MED_MODIFY };
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CEdit	c_coach;
	CEdit	c_factory;
	CEdit	c_InPrice;
	CEdit	c_Price;
	CEdit	c_SL;
	CEdit	m_kf;
	CEdit	m6;
	CEdit	m5;
	CEdit	m4;
	CEdit	m3;
	CEdit	m2;
	CEdit	m1;
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogMedModify)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogMedModify)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnKillfocusEditFactory();
	afx_msg void OnSetfocusEditFactory();
	afx_msg void OnButtonCodegys();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGMEDMODIFY_H__B5685788_C35C_46EF_80A2_233D06BC3F30__INCLUDED_)
