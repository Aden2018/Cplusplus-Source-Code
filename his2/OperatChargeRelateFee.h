#if !defined(AFX_OPERATCHARGERELATEFEE_H__8AD9A260_AC0A_48B4_95DA_3F652755E14F__INCLUDED_)
#define AFX_OPERATCHARGERELATEFEE_H__8AD9A260_AC0A_48B4_95DA_3F652755E14F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OperatChargeRelateFee.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COperatChargeRelateFee dialog
#include "qiuXpButton.h"
class COperatChargeRelateFee : public CDialog
{
// Construction
public:
	static void WriteExcelCell(CString strCell,CString strData);
	double dbQuota;
	void GetAlreadyUsed();
	void GetInformationFromBM(CString strx);
	CString c_mRymc;
	CString c_mRybm;
	CFont fontTitle;
	void GenericScale(void);
	CString infor[20];
	COperatChargeRelateFee(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COperatChargeRelateFee)
	enum { IDD = IDD_DIALOG_CHARGE_REAL_RELATE };
	CQiuXpButton	m_3;
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CEditFlat	c_scaleConsume;
	CEditFlat	c_spare;
	CEditFlat	c_accountConsume;
	CEditFlat	c_grzf;
	CEditFlat	c_realbao;
	CEditFlat	c_rymc;
	CEditFlat	c_sex;
	CEditFlat	c_scale;
	CEditFlat	c_property;
	CEditFlat	c_name;
	CEditFlat	c_invoice;
	CEditFlat	c_age;
	CEditFlat	c_account;
	CComboBox	c_combo1;
	COleDateTime	m_date1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperatChargeRelateFee)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COperatChargeRelateFee)
	afx_msg void OnButtonRelate();
	afx_msg void OnSelchangeCombo1();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnSetfocusEdit1();
	afx_msg void OnChangeEditAll();
	virtual void OnOK();
	afx_msg void OnPrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERATCHARGERELATEFEE_H__8AD9A260_AC0A_48B4_95DA_3F652755E14F__INCLUDED_)
