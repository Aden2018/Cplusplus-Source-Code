//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_OPERATORSET_H__560DC413_9745_4CF5_BB94_85EDA896D4FA__INCLUDED_)
#define AFX_OPERATORSET_H__560DC413_9745_4CF5_BB94_85EDA896D4FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OperatorSet.h : header file
// 类描述:
//		操作人员新增及修改

/////////////////////////////////////////////////////////////////////////////
// COperatorSet dialog

class COperatorSet : public CDialog
{
// Construction
public:
	CString gstrSql;
	CString strTitle;
	CFont fontTitle;
	COperatorSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COperatorSet)
	enum { IDD = IDD_DIALOG_OPERATOR_SET };
	CComboBox	combo1;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperatorSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COperatorSet)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnClickMshflexgrid1();
	virtual void OnDblClickMshflexgrid1();
	virtual void OnSelchangeCombo1();
	virtual void OnAdd();
	virtual void OnExcel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERATORSET_H__560DC413_9745_4CF5_BB94_85EDA896D4FA__INCLUDED_)
