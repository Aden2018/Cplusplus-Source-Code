#if !defined(AFX_RESIDECHECKIN_H__72BE3C0E_31CF_4799_995F_CE340E5541D3__INCLUDED_)
#define AFX_RESIDECHECKIN_H__72BE3C0E_31CF_4799_995F_CE340E5541D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResideCheckIn.h : header file
//

#include "excel9.h"

/////////////////////////////////////////////////////////////////////////////
// CResideCheckIn dialog

class CResideCheckIn : public CDialog
{
// Construction
public:
	static void SetValue(_Worksheet & sheet,int count,CString * pStr);
	CResideCheckIn(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResideCheckIn)
	enum { IDD = IDD_DIALOG_RESIDE_CHECKIN };
	CQiuXpButton	m_okprint;
	CComboBox	m_cSex;
	CEdit	c_doctor;
	CQiuXpButton	m_doctor;
	CQiuXpButton	m_bed;
	CQiuXpButton	m_cancel;
	CQiuXpButton	m_ok;
	COleDateTime	m_date;
	int		m_age;
	CString	m_strHome;
	CString	m_strill;
	CString	m_strPhone;
	double	m_dbPrice;
	double	m_dbRebate;
	CString	m_strRemark;
	CString	m_strWork;
	CString	m_strXm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResideCheckIn)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString strSerial;

	// Generated message map functions
	//{{AFX_MSG(CResideCheckIn)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReDoctor();
	afx_msg void OnButtonReBed();
	afx_msg void OnKillfocusEditReDoctor();
	afx_msg void OnSetfocusEditReDoctor();
	virtual void OnOK();
	afx_msg void OnPrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL CheckAvail();
	void InitControl();
	CString m_strDoctorName;
	CString m_strDoctorBm;
	CString m_strBedName;
	CString m_strBedCode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIDECHECKIN_H__72BE3C0E_31CF_4799_995F_CE340E5541D3__INCLUDED_)
