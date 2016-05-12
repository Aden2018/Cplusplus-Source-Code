//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#include "qiuXpButton.h"
#include "editEx.h"
#if !defined(AFX_EMPLOYEEQUERY_H__721B7F50_5DCD_4D2F_9F85_757D0C6A2A7A__INCLUDED_)
#define AFX_EMPLOYEEQUERY_H__721B7F50_5DCD_4D2F_9F85_757D0C6A2A7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmployeeQuery.h : header file
// 补充保险人员基础编码

/////////////////////////////////////////////////////////////////////////////
// CEmployeeQuery dialog

class CEmployeeQuery : public CDialog  //用于职工基本信息查询
{
// Construction
public:
	UINT iMenuSel;
	UINT flag_EXIT;
	UINT flagRELATE;
	CString strDate[2],lineInfor[20];
	LPVOID p;
	long curRow;
	CString strSex;
	CString strName;
	CString strKH;
	CFont fontTitle;
	CEmployeeQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEmployeeQuery)
	enum { IDD = IDD_DIALOG_EMPLOYEE_QUERY };
	CQiuXpButton	m_aaa;
	CQiuXpButton	m_excel;
	CQiuXpButton	m_x2;
	CQiuXpButton	m_x1;
	CEditEx	m_kahao;
	CEditEx	m_name;
	CComboBox	m_depart;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmployeeQuery)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetSel();

	// Generated message map functions
	//{{AFX_MSG(CEmployeeQuery)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnDblClickMshflexgrid2();
	virtual void OnSelchangeCombo1();
	virtual void OnKeyDownMshflexgrid2(short FAR* KeyCode, short Shift);
	virtual void OnClickMshflexgrid2();
	afx_msg void OnToExcel();
	afx_msg void OnMenuQEmpAdd();
	afx_msg void OnMenuQEmpDel();
	afx_msg void OnMenuQEmpModify();
	afx_msg void OnMenuQEmpSubsidy();
	afx_msg void OnSearch();
	afx_msg void OnMenuQPassView();
	afx_msg void OnChangeEdit1();
	virtual void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnMenuQuickBaseryDel();
	virtual void OnMenuQuickBaseryModify();
	virtual void OnMenuQuickBaseryViewpassword();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMPLOYEEQUERY_H__721B7F50_5DCD_4D2F_9F85_757D0C6A2A7A__INCLUDED_)
