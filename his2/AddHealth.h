
#include "qiuxpButton.h"
#if !defined(AFX_ADDHEALTH_H__7E2D8B5E_5A6D_4FC5_9DCF_DCA975341091__INCLUDED_)
#define AFX_ADDHEALTH_H__7E2D8B5E_5A6D_4FC5_9DCF_DCA975341091__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddHealth.h : header file
//
#include "colorComboBox.h"
/////////////////////////////////////////////////////////////////////////////
// CAddHealth dialog

class CAddHealth : public CDialog
{
// Construction
public:
	COLORREF backColor;
	CString strKH;//,str[4];
	void GetEmployee(void);
	CPen penRect,pen2;
	CBrush brushDialog;
	CFont fontTitle,fontEdit,font2;
	CBrush brushEdit;
	CAddHealth(CWnd* pParent = NULL);   // standard constructor
	int ps[40];
// Dialog Data
	//{{AFX_DATA(CAddHealth)
	enum { IDD = IDD_DIALOG_HEALTH_ADD };
	CQiuXpButton	m_x4;
	CQiuXpButton	m_x3;
	CQiuXpButton	m_x2;
	CQiuXpButton	m_x1;
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
	CString	m_kahao;
	CString	m_strEdit0;
	CString	m_strEdit1;
	CString	m_strEdit2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddHealth)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddHealth)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnSearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDHEALTH_H__7E2D8B5E_5A6D_4FC5_9DCF_DCA975341091__INCLUDED_)
