#if !defined(AFX_EMPLOYEEBMP_H__3570B9C1_01A4_4C3B_8797_99BC930057AF__INCLUDED_)
#define AFX_EMPLOYEEBMP_H__3570B9C1_01A4_4C3B_8797_99BC930057AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmployeeBmp.h : header file
//补充保险外诊报销

/////////////////////////////////////////////////////////////////////////////
// CEmployeeBmp dialog
#include "editEx.h"
#include "staticDecharge.h"

class CEmployeeBmp : public CDialog
{
// Construction
public:
	UINT PRINTflag;
	void clearEdit(void);
	void EnDiControl(BOOL flag);
	CStringArray strScale,strName;
	void Compute(void);
	CFont fontTitle;
	CString strTitle;
	CBrush backBrush;
	CString strInfor[15];
	CEmployeeBmp(CWnd* pParent = NULL);   // standard constructor
	

// Dialog Data
	//{{AFX_DATA(CEmployeeBmp)
	enum { IDD = IDD_DIALOG_EMP_BMP };
	CEditEx	c_kh;
	CStaticDecharge	m_sb;
	CDateTimeCtrl	c_date;
	CEditEx	c_invoice;
	CEditEx	c_personCash;
	CEditEx	c_whole;
	CEditEx	c_cash;
	CEditEx	c_account;
	CComboBox	c_type;
	CQiuXpButton	b4;
	CQiuXpButton	b3;
	CQiuXpButton	b2;
	CQiuXpButton	b1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmployeeBmp)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEmployeeBmp)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonEmp();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnKillfocusEditKh();
	afx_msg void OnSetfocusEditKh();
	afx_msg void OnPrint();
	virtual void OnCancel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void OnChangeEdit1(UINT nID);
	void OnSetFocusEdit1(UINT nID);
private:
	void EmpInforWrite();
	BOOL GetEmpInformation(void);
	void ClearInformation(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMPLOYEEBMP_H__3570B9C1_01A4_4C3B_8797_99BC930057AF__INCLUDED_)
