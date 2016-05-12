#if !defined(AFX_RESIDELISTQUERY_H__6A237F42_555B_4843_99E5_25EC725100B1__INCLUDED_)
#define AFX_RESIDELISTQUERY_H__6A237F42_555B_4843_99E5_25EC725100B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResideListQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResideListQuery dialog

class CResideListQuery : public CDialog
{
// Construction
public:
	static UINT QueryResideList(LPVOID ps);
	CResideListQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResideListQuery)
	enum { IDD = IDD_DIALOG_RESIDE_QUERY };
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	COleDateTime	m_date1;
	COleDateTime	m_date2;
	int		m_radio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResideListQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResideListQuery)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIDELISTQUERY_H__6A237F42_555B_4843_99E5_25EC725100B1__INCLUDED_)
