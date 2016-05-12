//{{AFX_INCLUDES()
#include "richtext.h"
//}}AFX_INCLUDES
#include "editEx.h"
#if !defined(AFX_DSENDNOTIFY_H__21424467_2159_4784_B56C_808E45DDE8A5__INCLUDED_)
#define AFX_DSENDNOTIFY_H__21424467_2159_4784_B56C_808E45DDE8A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DSendNotify.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDSendNotify dialog

class CDSendNotify : public CDialog //发送通知用
{
// Construction
public:
	CDSendNotify(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDSendNotify)
	enum { IDD = ID_FORM_SEND_NOTIFY };
	CListCtrl	c_recive;
	CEditFlat	c_richbody;
	CEditFlat	c_title;
	CEditFlat	c_send_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSendNotify)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDSendNotify)
	virtual void OnOK();
	afx_msg void OnButtonRecevie();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSENDNOTIFY_H__21424467_2159_4784_B56C_808E45DDE8A5__INCLUDED_)
