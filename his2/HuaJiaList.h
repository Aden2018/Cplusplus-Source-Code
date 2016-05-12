//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#include "qiuXpButton.h"
#include "ProgressIndicate.h"	// Added by ClassView
#if !defined(AFX_HUAJIALIST_H__1C2E951F_5945_4B9F_B252_27D38C6399E0__INCLUDED_)
#define AFX_HUAJIALIST_H__1C2E951F_5945_4B9F_B252_27D38C6399E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HuaJiaList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHuaJiaList dialog
// 列出待划价人员
class CHuaJiaList : public CDialog
{
// Construction
public:
	long curRow;
	CFont fontTitle;
	CHuaJiaList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHuaJiaList)
	enum { IDD = IDD_MED_HUAJIA_LIST };
	CComboBox	m_comboxSort;
	CQiuXpButton	m_3;
	CMSHFlexGrid	m_grid;
	COleDateTime	m_date1;
	COleDateTime	m_dateStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHuaJiaList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CHuaJiaList)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnDblClickMshflexgrid1();
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnSize(UINT nType, int cx, int cy);
	virtual void OnClickMshflexgrid1();
	virtual void OnCancel();
	virtual void OnKeyDownMshflexgrid1(short FAR* KeyCode, short Shift);
	afx_msg void OnSelchangeComboSort();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowReside();
	void ShowPublic();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HUAJIALIST_H__1C2E951F_5945_4B9F_B252_27D38C6399E0__INCLUDED_)
