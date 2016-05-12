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
	strHead="��Ƚ�����ķ�����";
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

	// 3������
	pChart->SetColumnCount(5); 

	i=1;
	pChart->SetShowLegend(true);
	pChart->SetColumn(i++);
	pChart->SetColumnLabel("�ܽ��");
	pChart->SetColumn(i++);
	pChart->SetColumnLabel("��������");
	pChart->SetColumn(i++);
	pChart->SetColumnLabel("ҩƷ�ɱ�");
	pChart->SetColumn(i++);
	pChart->SetColumnLabel("�� ��");
	pChart->SetColumn(i++);
	pChart->SetColumnLabel("�� ��");
	// ��ɫ
	i=1;
	pChart->GetPlot().GetSeriesCollection().GetItem(i++).GetPen().GetVtColor().Set(255, 0, 0);
	pChart->GetPlot().GetSeriesCollection().GetItem(i++).GetPen().GetVtColor().Set(0, 0, 255);
	pChart->GetPlot().GetSeriesCollection().GetItem(i++).GetPen().GetVtColor().Set(0, 255, 0);
	pChart->GetPlot().GetSeriesCollection().GetItem(i++).GetPen().GetVtColor().Set(0, 128,0);
	pChart->GetPlot().GetSeriesCollection().GetItem(i++).GetPen().GetVtColor().Set(128,0, 64);
	// ջģʽ
	pChart->SetStacking(FALSE);

	// Y������
	COleVariant var(DISP_E_PARAMNOTFOUND,VT_ERROR);
	int maxFoot=0;
	for(long row=0 ; row < 12*5-1 ; row ++ ){
		if( dbData[maxFoot] < dbData[row+1] ) maxFoot=row+1;

	}
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetAuto(FALSE);	// ���Զ���עY��̶�
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetMaximum( dbData[maxFoot] );	// Y�����̶�
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetMinimum(0);		// Y����С�̶�
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetMajorDivision(0);	// Y��̶�5�ȷ�
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetMinorDivision(0);	// ÿ�̶�һ���̶���
	pChart->GetPlot().GetAxis(1,var).GetAxisTitle().SetText(yStr);	// Y������



 
	// �߿�(�Ե���ͼ��Ч)
//	pChart->GetPlot().GetSeriesCollection().GetItem(1).GetPen().SetWidth(40);
//	pChart->GetPlot().GetSeriesCollection().GetItem(2).GetPen().SetWidth(100);
//	pChart->GetPlot().GetSeriesCollection().GetItem(3).GetPen().SetWidth(1);

	// ���ݵ�������ʾ����ֵ��ģʽ(������״ͼ�͵���ͼ��Ч)
	// 0: ����ʾ	1: ��ʾ����״ͼ��
	// 2: ��ʾ����״ͼ���Ϸ�	3: ��ʾ����״ͼ���м�	4: ��ʾ����״ͼ���·�
//	pChart->GetPlot().GetSeriesCollection().GetItem(1).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);

	pChart->SetRowCount( 12);
	pChart->GetPlot().GetAxis(0,var).GetCategoryScale().SetAuto(false);			// ���Զ���עX��̶�
	pChart->GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerLabel(1);// ÿ�̶�һ����ע
	pChart->GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerTick(1); // ÿ�̶�һ���̶���

	pChart->GetPlot().GetAxis(0,var).GetAxisTitle().SetText(strTitleAnalyse);			// X������

	char buf[32];
	
	for( row = 1; row <= 12; ++row)
	{
	//	dbData[row-1]=row*10;
		pChart->SetRow(row);
		sprintf(buf, "%d", row);
	
		pChart->SetRowLabel((LPCTSTR)buf);
		i=1;x=0;
		pChart->GetDataGrid().SetData(row, i++, dbData[ (row-1)*5+(x++) ], 0); //�ܽ��
		pChart->GetDataGrid().SetData(row, i++, dbData[ (row-1)*5+(x++) ], 0); //��������
		pChart->GetDataGrid().SetData(row, i++, dbData[ (row-1)*5+(x++) ], 0); //�ɱ�
		pChart->GetDataGrid().SetData(row, i++, dbData[ (row-1)*5+(x++) ], 0); //����
		pChart->GetDataGrid().SetData(row, i++, dbData[ (row-1)*5+(x++) ], 0); //�ֽ�
	
    }

	pChart->SetRedraw(true);
	pChart->Refresh();	
}




