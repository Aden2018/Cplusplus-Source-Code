#if !defined(AFX_EMPLOYEEDECHARGE_H__236BB78B_9C55_43F2_9F53_75452FB0A6CA__INCLUDED_)
#define AFX_EMPLOYEEDECHARGE_H__236BB78B_9C55_43F2_9F53_75452FB0A6CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmployeeDecharge.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEmployeeDecharge dialog

class CEmployeeDecharge : public CDialog
{
// Construction
public:
	CEmployeeDecharge(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEmployeeDecharge)
	enum { IDD = IDD_DIALOG_EMPLOYEE_DECHARGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmployeeDecharge)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEmployeeDecharge)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMPLOYEEDECHARGE_H__236BB78B_9C55_43F2_9F53_75452FB0A6CA__INCLUDED_)
