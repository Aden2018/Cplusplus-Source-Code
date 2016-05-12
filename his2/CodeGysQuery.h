#include "editFlat.h"
#include "qiuXpButton.h"
//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_CODEGYSQUERY_H__398D3544_59CF_484A_A574_C5EC1742256A__INCLUDED_)
#define AFX_CODEGYSQUERY_H__398D3544_59CF_484A_A574_C5EC1742256A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeGysQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeGysQuery dialog


class CCodeGysQuery : public CDialog
{
// Construction
public:
	CString strFlag;
	long curRow;
	CString strName,strNum;
	CFont fontTitle;
	CCodeGysQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCodeGysQuery)
	enum { IDD = IDD_DIALOG_CODEGYS };
	CQiuXpButton	m_x2;
	CQiuXpButton	m_x1;
	CEditFlat	c_name;
	CEditFlat	c_bm;
	CEditFlat	c_py;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeGysQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCodeGysQuery)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit4();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDblClickMshflexgrid1();
	afx_msg void OnClickMshflexgrid1();
	afx_msg void OnQmCodegysAdd();
	afx_msg void OnQmCodegysDel();
	afx_msg void OnQmCodegysModify();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODEGYSQUERY_H__398D3544_59CF_484A_A574_C5EC1742256A__INCLUDED_)
