//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_EVERYDAYCONSUMELIST_H__5CB6B2FD_2975_439A_AD71_F7AE35EAE996__INCLUDED_)
#define AFX_EVERYDAYCONSUMELIST_H__5CB6B2FD_2975_439A_AD71_F7AE35EAE996__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EverydayConsumeList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEverydayConsumeList form view
#define T_EDIT1 (WM_USER)+102

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "qiuXpButton.h"

class CEverydayConsumeList : public CFormView
{
protected:
	CEverydayConsumeList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEverydayConsumeList)

// Form Data
public:
	//{{AFX_DATA(CEverydayConsumeList)
	enum { IDD = ID_FORM_RKLIST };
	CQiuXpButton	m_234;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void OnKillEditCtrl();
	CFont fontMoveEdit;
	void SetGridHead();
	CFont fontTitle;
	CStringArray strMc,strBm;
	CEdit editCtrl;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEverydayConsumeList)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEverydayConsumeList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CEverydayConsumeList)
	afx_msg void OnButtonToExcel();
	afx_msg void OnDblClickMshflexgrid1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVERYDAYCONSUMELIST_H__5CB6B2FD_2975_439A_AD71_F7AE35EAE996__INCLUDED_)
