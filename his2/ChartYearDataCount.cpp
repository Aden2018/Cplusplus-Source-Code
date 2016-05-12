// ChartYearDataCount.cpp: implementation of the CChartYearDataCount class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "ChartYearDataCount.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChartYearDataCount::CChartYearDataCount()
{
	yStr="消耗金额";
	strHead="年度消耗金额统计表";
	flagTitle=1; //标题有效
}

CChartYearDataCount::~CChartYearDataCount()
{

}

BOOL CChartYearDataCount::OnInitDialog()
{
	CChartView::OnInitDialog();
	//hide second view
	CRect r1,r2;
	pChartYear->GetWindowRect(r1);
	ScreenToClient(r1);
	pChart->GetWindowRect(r2);
	ScreenToClient(r2);
	r2.right=r1.right;
	r2.bottom=r1.bottom;
	pChartYear->ShowWindow(SW_HIDE);
	pChart->MoveWindow(r2);

	m_b2.ShowWindow(SW_HIDE);
	return true;
}
