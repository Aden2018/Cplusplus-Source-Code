#if !defined(AFX_NEWPERSONALADDCASH_H__2842A8A2_F945_461C_9A70_B0E55B207B12__INCLUDED_)
#define AFX_NEWPERSONALADDCASH_H__2842A8A2_F945_461C_9A70_B0E55B207B12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewPersonalAddCash.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewPersonalAddCash dialog

class CNewPersonalAddCash : public CDialog
{
// Construction
public:
	double dbScale;
	CString strInfor[20];
	static BOOL GetEmpInformation(CString *a ,CString strSql );
	CString strKH;
	CFont fontTitle;
	CString strTitle;
	CNewPersonalAddCash(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewPersonalAddCash)
	enum { IDD = IDD_DIALOG_NEWPERSONAL_ADDCASH };
	CEditEx	c_cash;
	CEditEx	c_NewCash;
	CEditEx	c_kh;
	CEditEx	c_infor;
	CEditEx	cAccount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewPersonalAddCash)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewPersonalAddCash)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonEmp();
	virtual void OnOK();
	afx_msg void OnChangeEditNewcash();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void WriteInformation();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPERSONALADDCASH_H__2842A8A2_F945_461C_9A70_B0E55B207B12__INCLUDED_)
