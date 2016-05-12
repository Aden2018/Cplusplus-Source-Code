#if !defined(AFX_OTHERSICKQUERY_H__7173F63C_B64A_4316_9A80_DDE7D8BE5A2C__INCLUDED_)
#define AFX_OTHERSICKQUERY_H__7173F63C_B64A_4316_9A80_DDE7D8BE5A2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OtherSickQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COtherSickQuery dialog

class COtherSickQuery : public CDialog
{
// Construction
public:
	UINT flagWhatDo;
	CString strTitle;
	CFont fontTitle;
	LPVOID p;
	CString strSex;
	CString strKH;
	CString strName;
	CString strSql;
	COtherSickQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COtherSickQuery)
	enum { IDD = IDD_DIALOG_OTHERSICK_QUERY };
	CListCtrl	c_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COtherSickQuery)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COtherSickQuery)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnDblclkListQuery(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnRclickListQuery(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTHERSICKQUERY_H__7173F63C_B64A_4316_9A80_DDE7D8BE5A2C__INCLUDED_)
