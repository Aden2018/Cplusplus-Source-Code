#if !defined(AFX_JOURNAL_H__B780A6A3_8EEA_4DDD_A256_9FA48F08E807__INCLUDED_)
#define AFX_JOURNAL_H__B780A6A3_8EEA_4DDD_A256_9FA48F08E807__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Journal.h : header file
//
#include "QiuXpButton.h"

/////////////////////////////////////////////////////////////////////////////
// Journal dialog

class Journal : public CDialog
{
// Construction
public:
	Journal(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Journal)
	enum { IDD = IDD_DIALOG_JOURNAL };
	CComboBox	m_comboType;
	CString	m_strExpressFee;
	CString	m_strGetFee;
	CString	m_ISSN;
	CString	m_strMakeFee;
	CString	m_strPostFee;
	CString	m_strNums;
	COleDateTime	m_date;
	//}}AFX_DATA
	CFont ft;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Journal)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Journal)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ResetCtrl();
	CString strTitle,strSql;
	CStringArray arrType;
public:
	CQiuXpButton m_btnOK;
	CQiuXpButton m_btnCancel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JOURNAL_H__B780A6A3_8EEA_4DDD_A256_9FA48F08E807__INCLUDED_)
