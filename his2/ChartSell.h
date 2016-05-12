//{{AFX_INCLUDES()
#include "mschart.h"
#include "mshflexgrid.h"
//}}AFX_INCLUDES
//---------------------------------------------------------------------------
//	类描述
//		此类生成 [年度销售走势图]
//	日期:2004/12/26	星期X			作者 凌绍清
//---------------------------------------------------------------------------
//	修改记录:
//	日期:2005/03/07 星期一			作者 凌绍清
//		将原来的年度选择(为日期型控件)更改为下拉框选择
//---------------------------------------------------------------------------
#if !defined(AFX_CHARTSELL_H__DED7AF92_812B_48C6_88A3_E9A9B601C98C__INCLUDED_)
#define AFX_CHARTSELL_H__DED7AF92_812B_48C6_88A3_E9A9B601C98C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChartSell.h : header file
//
#include "qiuXpButton.h"

/////////////////////////////////////////////////////////////////////////////
// CChartSell dialog

class CChartSell : public CDialog
{
// Construction
public:
	CString xStr,yStr;
	double fData1[12],fData2[12],fData3[12],fData4[12],fData5[12];
	UINT flagYearDataEffect;
	static UINT QueryYearData(LPVOID);
	void GetYearData();
	CString strTitle;
	void DisplayChart2();
	void DisplayChart1();
	long plotStyle[5],plotNum1,plotNum2;
	CBrush backBrush;
	CFont fontTitle;
	CChartSell(CWnd* pParent = NULL);   // standard constructor
	CMSChart *p1,*p2;
// Dialog Data
	//{{AFX_DATA(CChartSell)
	enum { IDD = IDD_DIALOG_CHART_GENE };
	CComboBox	combo1;
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	COleDateTime	m_date;
	CMSHFlexGrid	m_grid1;
	CMSHFlexGrid	m_grid3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartSell)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChartSell)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	afx_msg void OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblClickMschart1();
	afx_msg void OnDblClickMschart2();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeCombo1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTSELL_H__DED7AF92_812B_48C6_88A3_E9A9B601C98C__INCLUDED_)
