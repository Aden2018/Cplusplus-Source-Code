#if !defined(AFX_SELECTVIEW_H__4BA4D202_95C3_4769_880C_CF2AEE8FEA74__INCLUDED_)
#define AFX_SELECTVIEW_H__4BA4D202_95C3_4769_880C_CF2AEE8FEA74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectView dialog

class CSelectView : public CDialog
{
// Construction
public:
	CString strSelect;
	CString strTitle;
	CFont fontTitle;
	UINT flagSelect;
	CSelectView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectView)
	enum { IDD = IDD_DIALOG_SELECTVIEW };
	CComboBox	combo2;
	CComboBox	combo1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectView)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTVIEW_H__4BA4D202_95C3_4769_880C_CF2AEE8FEA74__INCLUDED_)
