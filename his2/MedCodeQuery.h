
#include "editFlat.h"
#include "comboxEx.h"
#include "qiuXpButton.h"
//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_MEDCODEQUERY_H__2CB4F495_ED87_4152_9CC1_E999D0BA90AD__INCLUDED_)
#define AFX_MEDCODEQUERY_H__2CB4F495_ED87_4152_9CC1_E999D0BA90AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MedCodeQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMedCodeQuery dialog

class CMedCodeQuery : public CDialog
{
// Construction
public:
	long curRow;
	UINT FlagRollMED;
	CFont fontTitle;
	CMedCodeQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMedCodeQuery)
	enum { IDD = IDD_MEDCODE };
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CComBoxEx	c_comDL;
	CComBoxEx	c_comXL;
	CEditFlat	c_py;
	CEditFlat	c_mc;
	CEditFlat	c_bm;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedCodeQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMedCodeQuery)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboDl();
	virtual void OnOK();
	afx_msg void OnSelchangeComboXl();
	virtual void OnChangeEditPy();
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnDblClickMshflexgrid1();
	virtual void OnClickMshflexgrid1();
	afx_msg void OnMenuMedcodeModify();
	afx_msg void OnMenuMedcodeAdd();
	afx_msg void OnMenuMedcodeDelete();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDCODEQUERY_H__2CB4F495_ED87_4152_9CC1_E999D0BA90AD__INCLUDED_)
