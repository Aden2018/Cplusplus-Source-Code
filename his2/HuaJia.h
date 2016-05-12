#include "editFlat.h"
#include "qiuXpButton.h"
//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#define T_EDIT_HUAJIA (WM_USER)+102
#define T_EDIT_CURE   (WM_USER)+103

#if !defined(AFX_HUAJIA_H__D1C76738_ECBA_494D_9302_7E0B81D935E9__INCLUDED_)
#define AFX_HUAJIA_H__D1C76738_ECBA_494D_9302_7E0B81D935E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HuaJia.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CHuaJia dialog
#include "excel9.h"

class CHuaJia : public CDialog
{
// Construction
public:
	static CString  GetBigMoney(double dMoney);
	CString strGhHuajia[2];
	CString GetChinesePrice(CString strNum);
	float inPrice;
	void SetGridHead();
	void ComputerFee();
	float balance;
	float scale; //用于报销比例
	long editRow;
	void OnKillEdit2();
	CEdit edit2;
	void OnKillEditCtrl(void);
	CFont fontMoveEdit;
	CEdit editCtrl;
	CString m_strDoctorBm,str2[20]; //str2用于以前传过来的信息,
	CFont fontTitle;
	CHuaJia(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHuaJia)
	enum { IDD = IDD_MED_HUAJIAN };
	CQiuXpButton	m_223;
	CQiuXpButton	c_rollmedbutton;
	CEditFlat	x7;
	CEditFlat	x6;
	CEditFlat	x5;
	CEditFlat	x4;
	CEditFlat	x3;
	CEditFlat	x2;
	CEditFlat	x1;
	CEditFlat	c_medname;
	CEditFlat	c_medgg;
	CEditFlat	c_mednum;
	CQiuXpButton	m_xx;
	CEditFlat	c_type;
	CEditFlat	c_sick;
	CEditFlat	c_doctor;
	CEditFlat	c_danjuhao;
	CQiuXpButton	m_34;
	CQiuXpButton	m_3;
	CQiuXpButton	m_2;
	CMSHFlexGrid	m_grid;
	CMSHFlexGrid	m_grid2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHuaJia)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont fontSmall;
	void SetExcelCell(_Worksheet &sheet,int iRow,int iCol,CString &strData);
	void ComputeRows();

	// Generated message map functions
	//{{AFX_MSG(CHuaJia)
	virtual BOOL OnInitDialog();
	virtual void OnButtonDoctor();
	virtual void OnKillfocusEditDoctor();
	virtual void OnSetfocusEditDoctor();
	virtual void OnOK();
	virtual void OnDblClickMshflexgrid1();
	virtual void OnClickMshflexgrid1();
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnDblClickMshflexgrid2();
	virtual void OnClickMshflexgrid2();
	virtual void OnChargePrice();
	virtual void OnKillfocusEditMedNum();
	virtual void OnSetfocusEditMedNum();
	virtual void OnChangeEditX1();
	virtual void OnRollmed();
	afx_msg void OnPrint();
	afx_msg void OnChangeEditX8();
	afx_msg void OnDestroy();
	afx_msg void OnChangeEditX9();
	afx_msg void OnChangeEditX5();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HUAJIA_H__D1C76738_ECBA_494D_9302_7E0B81D935E9__INCLUDED_)
