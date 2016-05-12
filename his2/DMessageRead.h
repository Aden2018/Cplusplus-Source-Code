#if !defined(AFX_DMESSAGEREAD_H__8FD140EF_933D_45ED_8AB5_95AE73B99297__INCLUDED_)
#define AFX_DMESSAGEREAD_H__8FD140EF_933D_45ED_8AB5_95AE73B99297__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DMessageRead.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDMessageRead dialog

class CDMessageRead : public CDialog //消息查看
{
// Construction
public:
	virtual void ListMessage();
	_RecordsetPtr rec2;
	CDMessageRead(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDMessageRead)
	enum { IDD = ID_FORM_SENDMESSAGE_READ };
	CListCtrl	c_message;
	CEditFlat	c_body;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMessageRead)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDMessageRead)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnClickListMessage(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListMessage(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	afx_msg void OnDeleteall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMESSAGEREAD_H__8FD140EF_933D_45ED_8AB5_95AE73B99297__INCLUDED_)
