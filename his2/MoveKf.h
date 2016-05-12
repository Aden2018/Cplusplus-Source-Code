#include "QiuXpButton.h"
#include "editFlat.h"
#define T_EDIT_YPZK WM_USER+115
//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_MOVEKF_H__F6C133C4_A7BA_420C_B410_727DC244CC7E__INCLUDED_)
#define AFX_MOVEKF_H__F6C133C4_A7BA_420C_B410_727DC244CC7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoveKf.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMoveKf dialog

class CMoveKf : public CDialog
{
// Construction
public:
	UINT flagPANDIAN;
	CString c_getRymcName;
	CString m_getKfbm;
	long editRow;
	virtual void OnKillEditCtrl();
	CEdit editCtrl;
	CString m_zktou;
	CFont fontTitle;
	CMoveKf(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMoveKf)
	enum { IDD = IDD_DIALOG_MOVE_KF };
	CQiuXpButton	m_45;
	CComboBox	c_use;
	CQiuXpButton	m_22;
	CEditFlat	c_getRymc;
	CEditFlat	c_danjuhao;
	CEditFlat	m_curKf;
	CComboBox	c_getKf;
	CQiuXpButton	m_4;
	CQiuXpButton	m_3;
	CQiuXpButton	m_2;
	CMSHFlexGrid	m_grid;
	COleDateTime	m_date;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoveKf)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString c_getRymcID;

	// Generated message map functions
	//{{AFX_MSG(CMoveKf)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnButtonRybm();
	afx_msg void OnDblClickMshflexgrid2();
	virtual void OnSearch();
	virtual void OnOK();
	virtual void OnSelchangeComboGetKf();
	virtual void OnKillfocusEditGetRymc();
	virtual void OnSetfocusEditGetRymc();
	virtual void OnEffiect();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVEKF_H__F6C133C4_A7BA_420C_B410_727DC244CC7E__INCLUDED_)
