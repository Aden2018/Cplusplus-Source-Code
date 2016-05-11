#include <vector>

#if !defined(AFX_FORMGHLIST_H__4A7A5128_03D2_4B28_84FB_7C63A6188EED__INCLUDED_)
#define AFX_FORMGHLIST_H__4A7A5128_03D2_4B28_84FB_7C63A6188EED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormGhList.h : header file
//Date:2014/09/22
//author:LingShaoQing
//summary:
//		稿费明细、汇总查询，提供输出到excel功能

/////////////////////////////////////////////////////////////////////////////
// CFormGhList form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CFormGhList : public CFormView
{
protected:
	CFormGhList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFormGhList)

// Form Data
public:
	//{{AFX_DATA(CFormGhList)
	enum { IDD = IDD_FORM_GHLIST };

	//}}AFX_DATA
	vector<int> vtAlign;
	CGridCtrl m_grid;
	enum { GRID_ID=4,SUM_COL=12 }; //合计列
	CFont fontTitle,font;
// Attributes
public:
	enum { DANJUHAO_COL = 0 };
// Operations
public:
	CString TITLE;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormGhList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFormGhList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFormGhList)
//	afx_msg void OnDblClickMshflexgrid1();
	afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickMshflexgrid1();
	afx_msg void OnMenuGhListtoexcel();
	afx_msg void OnMenuGhViewlist();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMGHLIST_H__4A7A5128_03D2_4B28_84FB_7C63A6188EED__INCLUDED_)
