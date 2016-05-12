//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_SUBSIDYSET_H__528C1FDE_DE68_4229_97DF_E09BB48BECEA__INCLUDED_)
#define AFX_SUBSIDYSET_H__528C1FDE_DE68_4229_97DF_E09BB48BECEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubsidySet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubsidySet dialog
// Describe:
//		此类用来设置厂类特殊补助人员性质
/////////////////////////////////////////////////////////////////////////////
class CSubsidySet : public CDialog
{
// Construction
public:
	CString strName,strKh;
	void SetGridHead();
	CSubsidySet(CWnd* pParent = NULL);   // standard constructor
	CFont fontTitle;
	CString strTitle;
// Dialog Data
	//{{AFX_DATA(CSubsidySet)
	enum { IDD = IDD_DIALOG_SUBSIDY };
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubsidySet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubsidySet)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblClickMshflexgrid1();
	virtual void OnOK();
	afx_msg void OnClickMshflexgrid1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBSIDYSET_H__528C1FDE_DE68_4229_97DF_E09BB48BECEA__INCLUDED_)
