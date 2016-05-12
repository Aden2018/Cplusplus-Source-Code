//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#include "editFlat.h"
#include "comboxEx.h"
#include "qiuXpButton.h"
#if !defined(AFX_QUERYRYBM_H__4CFBCA6B_648E_42B8_B3B9_DCA1390B4437__INCLUDED_)
#define AFX_QUERYRYBM_H__4CFBCA6B_648E_42B8_B3B9_DCA1390B4437__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QueryRybm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQueryRybm dialog

class CQueryRybm : public CDialog
{
// Construction
public:
	long curRow;
	CString strName,strNum;
	CFont fontTitle;
	CQueryRybm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQueryRybm)
	enum { IDD = IDD_DIALOG_RYBM };
	CQiuXpButton	m_x2;
	CQiuXpButton	m_x1;
	CComBoxEx	c_com1;
	CEditFlat	c_bm;
	CEditFlat	c_name;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryRybm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQueryRybm)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit3();
	afx_msg void OnDblClickMshflexgrid1();
	afx_msg void OnClickMshflexgrid1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYRYBM_H__4CFBCA6B_648E_42B8_B3B9_DCA1390B4437__INCLUDED_)
