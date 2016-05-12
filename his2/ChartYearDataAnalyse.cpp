// ChartYearDataAnalyse.cpp: implementation of the CChartYearDataAnalyse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "ChartYearDataAnalyse.h"
#include "vcBackdrop.h"
#include "vcPlot.h"
#include "vcDataGrid.h"
#include "vcFill.h"
#include "vcAxis.h"
#include "vcValueScale.h"
#include "vcAxisTitle.h"
#include "vcBrush.h"
#include "vcSeriesCollection.H"
#include "vcColor.h"
#include "vcSeries.h"
#include "vcPen.h"
#include "vcDataPoint.h"
#include "vcDatapoints.h"
#include "vcCategoryScale.h"
#include "vcDatapointLabel.h"
#include "progressIndicate.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChartYearDataAnalyse::CChartYearDataAnalyse()
{
	strHead="年度金额消耗分析表";
	for(int i=0; i< 12*5 ;i++) dbData[i]=0.0;

}

CChartYearDataAnalyse::~CChartYearDataAnalyse()
{

}

BOOL CChartYearDataAnalyse::OnInitDialog()
{
	CChartYearDataCount::OnInitDialog();
	return true;
}

void CChartYearDataAnalyse::DisplayChart1()
{
	long i=1,x;

	pChart->SetRedraw(false);
//	pChart->GetBackdrop().GetFill().SetStyle(1);
//	pChart->GetBackdrop().GetFill().GetBrush().GetFillColor().Set(0, 255, 255);

	// 3条曲线
	pChart->SetColumnCount(5); 

	i=1;
	pChart->SetShowLegend(true);
	pChart->SetColumn(i++);
	pChart->SetColumnLabel("总金额");
	pChart->SetColumn(i++);
	pChart->SetColumnLabel("其它费用");
	pChart->SetColumn(i++);
	pChart->SetColumnLabel("药品成本");
	pChart->SetColumn(i++);
	pChart->SetColumnLabel("利 润");
	pChart->SetColumn(i++);
	pChart->SetColumnLabel("现 金");
	// 线色
	i=1;
	pChart->GetPlot().GetSeriesCollection().GetItem(i++).GetPen().GetVtColor().Set(255, 0, 0);
	pChart->GetPlot().GetSeriesCollection().GetItem(i++).GetPen().GetVtColor().Set(0, 0, 255);
	pChart->GetPlot().GetSeriesCollection().GetItem(i++).GetPen().GetVtColor().Set(0, 255, 0);
	pChart->GetPlot().GetSeriesCollection().GetItem(i++).GetPen().GetVtColor().Set(0, 128,0);
	pChart->GetPlot().GetSeriesCollection().GetItem(i++).GetPen().GetVtColor().Set(128,0, 64);
	// 栈模式
	pChart->SetStacking(FALSE);

	// Y轴设置
	COleVariant var(DISP_E_PARAMNOTFOUND,VT_ERROR);
	int maxFoot=0;
	for(long row=0 ; row < 12*5-1 ; row ++ ){
		if( dbData[maxFoot] < dbData[row+1] ) maxFoot=row+1;

	}
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetAuto(FALSE);	// 不自动标注Y轴刻度
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetMaximum( dbData[maxFoot] );	// Y轴最大刻度
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetMinimum(0);		// Y轴最小刻度
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetMajorDivision(0);	// Y轴刻度5等分
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetMinorDivision(0);	// 每刻度一个刻度线
	pChart->GetPlot().GetAxis(1,var).GetAxisTitle().SetText(yStr);	// Y轴名称



 
	// 线宽(对点线图有效)
//	pChart->GetPlot().GetSeriesCollection().GetItem(1).GetPen().SetWidth(40);
//	pChart->GetPlot().GetSeriesCollection().GetItem(2).GetPen().SetWidth(100);
//	pChart->GetPlot().GetSeriesCollection().GetItem(3).GetPen().SetWidth(1);

	// 数据点类型显示数据值的模式(对柱柱状图和点线图有效)
	// 0: 不显示	1: 显示在柱状图外
	// 2: 显示在柱状图内上方	3: 显示在柱状图内中间	4: 显示在柱状图内下方
//	pChart->GetPlot().GetSeriesCollection().GetItem(1).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);

	pChart->SetRowCount( 12);
	pChart->GetPlot().GetAxis(0,var).GetCategoryScale().SetAuto(false);			// 不自动标注X轴刻度
	pChart->GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerLabel(1);// 每刻度一个标注
	pChart->GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerTick(1); // 每刻度一个刻度线

	pChart->GetPlot().GetAxis(0,var).GetAxisTitle().SetText(strTitleAnalyse);			// X轴名称

	char buf[32];
	
	for( row = 1; row <= 12; ++row)
	{
	//	dbData[row-1]=row*10;
		pChart->SetRow(row);
		sprintf(buf, "%d", row);
	
		pChart->SetRowLabel((LPCTSTR)buf);
		i=1;x=0;
		pChart->GetDataGrid().SetData(row, i++, dbData[ (row-1)*5+(x++) ], 0); //总金额
		pChart->GetDataGrid().SetData(row, i++, dbData[ (row-1)*5+(x++) ], 0); //其它费用
		pChart->GetDataGrid().SetData(row, i++, dbData[ (row-1)*5+(x++) ], 0); //成本
		pChart->GetDataGrid().SetData(row, i++, dbData[ (row-1)*5+(x++) ], 0); //利润
		pChart->GetDataGrid().SetData(row, i++, dbData[ (row-1)*5+(x++) ], 0); //现金
	
    }

	pChart->SetRedraw(true);
	pChart->Refresh();	
}




