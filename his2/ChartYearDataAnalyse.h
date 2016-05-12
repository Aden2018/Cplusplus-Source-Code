// ChartYearDataAnalyse.h: interface for the CChartYearDataAnalyse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARTYEARDATAANALYSE_H__1CC7D072_29A5_4B71_BC2F_97923CEC3DD1__INCLUDED_)
#define AFX_CHARTYEARDATAANALYSE_H__1CC7D072_29A5_4B71_BC2F_97923CEC3DD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChartYearDataCount.h"

class CChartYearDataAnalyse : public CChartYearDataCount  
{
public:
	CString strTitleAnalyse;
	double dbData[12*5];
	void DisplayChart1();
	BOOL OnInitDialog();
	CChartYearDataAnalyse();
	virtual ~CChartYearDataAnalyse();

};

#endif // !defined(AFX_CHARTYEARDATAANALYSE_H__1CC7D072_29A5_4B71_BC2F_97923CEC3DD1__INCLUDED_)
