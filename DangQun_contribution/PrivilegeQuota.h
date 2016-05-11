//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_PRIVILEGEQUOTA_H__F3F76916_18E0_4327_978A_CED7FE3139B9__INCLUDED_)
#define AFX_PRIVILEGEQUOTA_H__F3F76916_18E0_4327_978A_CED7FE3139B9__INCLUDED_
#include "comFunc.H"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrivilegeQuota.h : header file
//* ���: 2008/11/3   ������
//* ʵ��Ӧ�ó������û���Ȩ�޷���,����Ҫ�Ķ�ϵͳ������Ӱ����пɿ��Է���
//*

/////////////////////////////////////////////////////////////////////////////
// CPrivilegeQuota dialog

class CPrivilegeQuota : public CDialog
{
// Construction
public:
	CPrivilegeQuota(CWnd* pParent = NULL);   // standard constructor
	CStringArray comArray1,comArray2;
	enum{ GRID_HEADER_ID=12};
	int MODIFY_FLAG;
// Dialog Data
	//{{AFX_DATA(CPrivilegeQuota)
	enum { IDD = IDD_DIALOG_PRIVILEGE };
	CComboBox	m_combo2;
	CComboBox	m_combo1;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrivilegeQuota)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrivilegeQuota)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnDblClickMshflexgrid1();
	virtual void OnOK();
	virtual void OnAdd();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRIVILEGEQUOTA_H__F3F76916_18E0_4327_978A_CED7FE3139B9__INCLUDED_)
