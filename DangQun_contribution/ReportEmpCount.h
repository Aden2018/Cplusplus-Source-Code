//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_REPORTEMPCOUNT_H__19AF6CF5_0FE6_4BCF_AFE3_41FDC0D37C4F__INCLUDED_)
#define AFX_REPORTEMPCOUNT_H__19AF6CF5_0FE6_4BCF_AFE3_41FDC0D37C4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportEmpCount.h : header file
//
//*****************************************
//*DATE:2012/06/16
//*DESC:
//*     ��ԭ���ϰ汾�еĲ���ҽ����Ա����������ת�Ƶ��µĳ����У����µļ��㷽ʽ
//*	��ԭ�������ı䣬������㷽ʽ���£�
//*	�����ܶ�*4%---->���ᱨ���
//*	����ȡ���-������Ա��ֵ���---->ͳ����
//*	�����ֵ�������κμ���
/////////////////////////////////////////////////////////////////////////////
// CReportEmpCount dialog

class CReportEmpCount : public CDialog
{
// Construction
public:
	CReportEmpCount(CWnd* pParent = NULL);   // standard constructor
	enum { GRID_ID=26 ,SQL_ID=43 };
// Dialog Data
	//{{AFX_DATA(CReportEmpCount)
	enum { IDD = IDD_DIALOG_BCBX_ZJB };
	CComboBox	m_comYear;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA
	CFont fontTitle;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportEmpCount)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportEmpCount)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExcel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTEMPCOUNT_H__19AF6CF5_0FE6_4BCF_AFE3_41FDC0D37C4F__INCLUDED_)
