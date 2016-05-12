//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES

#include "editFlat.h"
#include "qiuXpbutton.h"

#define T_EDIT1 (WM_USER)+100
#define T_COMBO1 (WM_USER)+101
#if !defined(AFX_DIALOGINSTORAGE_H__1EDB8A3D_DE5C_405E_9B32_546BDE650AAD__INCLUDED_)
#define AFX_DIALOGINSTORAGE_H__1EDB8A3D_DE5C_405E_9B32_546BDE650AAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogInStorage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogInStorage dialog

class CDialogInStorage : public CDialog //采购药品入库操作
{
// Construction
public:

	CString c_ywyName;
	CString c_gysName;
	static BOOL GetName_ID(CString strSql,CString &strName,CString &strID);
	void Startup(void);
	CFont fontMoveEdit;
	CString c_ywyID;
	void OnKillEditCtrl();
	CComboBox comCtrl;
	CEdit editCtrl;
	CString c_gysID;
	CFont fontTitle;
	CDialogInStorage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogInStorage)
	enum { IDD = IDD_DIALOG_IN_STORAGE };
	CQiuXpButton	m_excel_button;
	CEditFlat	c_serial;
	CQiuXpButton	m_334;
	CQiuXpButton	m_33;
	CQiuXpButton	m_22;
	CQiuXpButton	m_4;
	CQiuXpButton	m_1;
	CEditFlat	m_2;
	CEditFlat	c_ywy;
	CEditFlat	c_paoju;
	CEditFlat	c_gys;
	CMSHFlexGrid	m_grid;
	COleDateTime	riqi;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogInStorage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogInStorage)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGys();
	afx_msg void OnButtonYwy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	afx_msg void OnSearch();
	afx_msg void OnDblClickMshflexgrid1();
	afx_msg void OnKillfocusEditGys();
	afx_msg void OnSetfocusEditGys();
	afx_msg void OnKillfocusEditYwy();
	afx_msg void OnSetfocusEditYwy();
	afx_msg void OnExcelPrint();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CalculatePrice();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGINSTORAGE_H__1EDB8A3D_DE5C_405E_9B32_546BDE650AAD__INCLUDED_)
