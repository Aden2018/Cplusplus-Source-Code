#include "gh.h"
#include "ProgressIndicate.h"	// Added by ClassView

#include "PayMedNum.h"	// Added by ClassView
#include "huajiaList.h"

#if !defined(AFX_STARTDOCTOR_H__A1F7386C_0861_49E7_8DED_64CCE751C16B__INCLUDED_)
#define AFX_STARTDOCTOR_H__A1F7386C_0861_49E7_8DED_64CCE751C16B__INCLUDED_

#include "Gh.h"	// Added by ClassView
#include "HuaJiaList.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartDoctor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStartDoctor dialog

class CStartDoctor : public CDialog
{
// Construction
public:
	CString m_startDate;
	int m_curTabSel;
	CPayMedNum pm;
//	CGetMed gm;
	CHuaJiaList hj;
	CGh gh;
	CStartDoctor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStartDoctor)
	enum { IDD = IDD_DIALOG_DOCTOR_START };
	CTabCtrl	ctab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartDoctor)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStartDoctor)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabDoctorStart(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTDOCTOR_H__A1F7386C_0861_49E7_8DED_64CCE751C16B__INCLUDED_)
