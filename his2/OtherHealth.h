#if !defined(AFX_OTHERHEALTH_H__976B2FFF_8953_4F50_913E_8161BB88CEA3__INCLUDED_)
#define AFX_OTHERHEALTH_H__976B2FFF_8953_4F50_913E_8161BB88CEA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OtherHealth.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COtherHealth dialog

#include "qiuXpButton.h"
#include "colorComboBox.h"

class COtherHealth : public CDialog
{
// Construction
public:
	COLORREF backColor;
	CString strKH;
	CPen penRect,pen2;
	CBrush brushDialog;
	CFont fontTitle,fontEdit,font2;
	CBrush brushEdit;
	int ps[40];

	COtherHealth(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(COtherHealth)
	enum { IDD = IDD_DIALOG_OTHER_HEALTH };
	CColorComboBox	c_sex;
	CQiuXpButton	m_x4;
	CQiuXpButton	m_x3;
	CQiuXpButton	m_x2;
	CColorComboBox	m_cab;
	CColorComboBox	m_eab;
	CColorComboBox	m_sab;
	CColorComboBox	m_cag;
	CColorComboBox	m_eag;
	CColorComboBox	m_sag;
	CComboBox	c_xuexin;
	COleDateTime	m_date;
	CString	m_xueYa;
	CString	m_tiZong;
	CString	m_high;
	CString	m_story;
	CString	m_leiKe;
	CString	m_weKe;
	CString	m_eye;
	CString	m_women;
	CString	m_1;
	CString	m_2;
	CString	m_3;
	CString	m_4;
	CString	m_5;
	CString	m_6;
	CString	m_7;
	CString	m_8;
	CString	m_9;
	CString	m_10;
	CString	m_11;
	CString	m_12;
	CString	m_xinDian;
	CString	m_B;
	CString	m_X;
	CString	m_result;
	CString	m_suggest;
	CString	m_comment;
	CString	m_strEdit0;
	CString	m_strEdit1;
	CString	m_strEdit2;
	CString	m_strName;
	CString	m_strAge;
	CString	m_strAddress;
	CString	m_strPhone;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COtherHealth)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COtherHealth)
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSearch();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTHERHEALTH_H__976B2FFF_8953_4F50_913E_8161BB88CEA3__INCLUDED_)
