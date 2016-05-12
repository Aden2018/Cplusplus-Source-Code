#if !defined(AFX_CHARTVIEW_H__8BB31B39_D9D3_4BB1_9D9D_40DC2E0610A1__INCLUDED_)
#define AFX_CHARTVIEW_H__8BB31B39_D9D3_4BB1_9D9D_40DC2E0610A1__INCLUDED_

#include "mschart.h"	// Added by ClassView
#include "qiuXpbutton.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChartView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChartView dialog

class CChartView : public CDialog
{
// Construction
public:
	UINT flagTitle;
	CString yStr;
	CString strHead;
	CFont fontTitle;
	static UINT QueryYear(LPVOID ps);
	CBrush backBrush;
	CString strName;
	CString strYpbm;
	COleDateTime dateConsume;
	UINT flagYearDataEffect;
	void DisplayChart2();
	long plotStyle[10],plotStyleNum1,plotStyleNum2;
	CString strTitle;
	long effectCols;
	float iYearData[15],iData[31];
	CMSChart *pChart,*pChartYear;
	CChartView(CWnd* pParent = NULL);   // standard constructor
	virtual void DisplayChart1();

// Dialog Data
	//{{AFX_DATA(CChartView)
	enum { IDD = IDD_DIALOG_CHART };
	CQiuXpButton	m_b2;
	CQiuXpButton	m_b1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void GetYearData();

	// Generated message map functions
	//{{AFX_MSG(CChartView)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnDblClickMschart1();
	virtual void OnDblClickMschart2();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTVIEW_H__8BB31B39_D9D3_4BB1_9D9D_40DC2E0610A1__INCLUDED_)
