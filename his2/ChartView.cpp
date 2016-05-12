// ChartView.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "ChartView.h"
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
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartView dialog


CChartView::CChartView(CWnd* pParent /*=NULL*/)
	:CDialog(CChartView::IDD, pParent)
{
	flagYearDataEffect=0; //年度数据无效
	flagTitle=0; //strTitle标题有效
	for(int row=0 ; row <12 ;row++)iYearData[row]=0;
	//{{AFX_DATA_INIT(CChartView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	backBrush.CreateSolidBrush(RGB(0,0,132));
	fontTitle.CreatePointFont(160,"黑体");
	strHead="药品销售情况走势图";
	yStr="数量";
}


void CChartView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartView)
	DDX_Control(pDX, IDOK, m_b2);
	DDX_Control(pDX, IDCANCEL, m_b1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartView, CDialog)
	//{{AFX_MSG_MAP(CChartView)
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartView message handlers

BOOL CChartView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strHead);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	plotStyleNum1= 0;
	plotStyleNum2= 0;
	plotStyle[0]=3;
	plotStyle[1]=1;
	plotStyle[2]=14;

	pChart=(CMSChart *) GetDlgItem(IDC_MSCHART1);
	pChartYear=(CMSChart *) GetDlgItem(IDC_MSCHART2);

	pChart->SetChartType( plotStyle[plotStyleNum1] );
	pChartYear->SetChartType( plotStyle[plotStyleNum2] );
	pChart->SetAllowSelections(false);
	pChartYear->SetAllowSelections(false);

	DisplayChart1();
	DisplayChart2();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChartView::OnOK()  //年度图
{
	GetYearData();
	DisplayChart2();
	
}

BEGIN_EVENTSINK_MAP(CChartView, CDialog)
    //{{AFX_EVENTSINK_MAP(CChartView)
	ON_EVENT(CChartView, IDC_MSCHART1, -601 /* DblClick */, OnDblClickMschart1, VTS_NONE)
	ON_EVENT(CChartView, IDC_MSCHART2, -601 /* DblClick */, OnDblClickMschart2, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CChartView::OnDblClickMschart1() 
{
	plotStyleNum1++;
	if( plotStyleNum1 == 3 ) plotStyleNum1= 0;
	
	pChart->SetChartType( plotStyle[plotStyleNum1] );
	DisplayChart1();
		
}

void CChartView::DisplayChart1()
{
	// TODO: Add extra validation here
	if( flagTitle == 0 )
		strTitle.Format("%d年%d月( %s )销售走势图",dateConsume.GetYear(),dateConsume.GetMonth(),strName);
	else
		strTitle=strName;
	//	pChart->SetTitleText(strTitle);
	// 下面两句改变背景色
	pChart->SetRedraw(false);
	pChart->GetBackdrop().GetFill().SetStyle(1);
	pChart->GetBackdrop().GetFill().GetBrush().GetFillColor().Set(0, 255, 255);


	// 栈模式
	pChart->SetStacking(FALSE);

	// Y轴设置
	COleVariant var(DISP_E_PARAMNOTFOUND,VT_ERROR);
	int maxFoot=0;
	for(long row=0 ; row < effectCols-1 ; row ++ ){
		if( iData[maxFoot] < iData[row+1] ) maxFoot=row+1;

	}
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetAuto(FALSE);	// 不自动标注Y轴刻度
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetMaximum( iData[maxFoot] );	// Y轴最大刻度
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetMinimum(0);		// Y轴最小刻度
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetMajorDivision(0);	// Y轴刻度5等分
	pChart->GetPlot().GetAxis(1,var).GetValueScale().SetMinorDivision(0);	// 每刻度一个刻度线
	pChart->GetPlot().GetAxis(1,var).GetAxisTitle().SetText(yStr);	// Y轴名称

	// 3条曲线
//	pChart->SetColumnCount(3); 
	pChart->SetColumnCount(1); 

	// 线色
	pChart->GetPlot().GetSeriesCollection().GetItem(1).GetPen().GetVtColor().Set(255, 0, 0);
//	pChart->GetPlot().GetSeriesCollection().GetItem(2).GetPen().GetVtColor().Set(255, 0, 0);
//	pChart->GetPlot().GetSeriesCollection().GetItem(3).GetPen().GetVtColor().Set(0, 255, 0);

	// 线宽(对点线图有效)
	pChart->GetPlot().GetSeriesCollection().GetItem(1).GetPen().SetWidth(40);
//	pChart->GetPlot().GetSeriesCollection().GetItem(2).GetPen().SetWidth(100);
//	pChart->GetPlot().GetSeriesCollection().GetItem(3).GetPen().SetWidth(1);

	// 数据点类型显示数据值的模式(对柱柱状图和点线图有效)
	// 0: 不显示	1: 显示在柱状图外
	// 2: 显示在柱状图内上方	3: 显示在柱状图内中间	4: 显示在柱状图内下方
	pChart->GetPlot().GetSeriesCollection().GetItem(1).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);

	pChart->SetRowCount(effectCols);
	pChart->GetPlot().GetAxis(0,var).GetCategoryScale().SetAuto(false);			// 不自动标注X轴刻度
	pChart->GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerLabel(1);// 每刻度一个标注
	pChart->GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerTick(1); // 每刻度一个刻度线
	
	pChart->GetPlot().GetAxis(0,var).GetAxisTitle().SetText(strTitle);			// X轴名称

	char buf[32];
	
	for( row = 1; row <= effectCols; ++row)
	{
	//	dbData[row-1]=row*10;
		pChart->SetRow(row);
		sprintf(buf, "%d", row);

		pChart->SetRowLabel((LPCTSTR)buf);
		pChart->GetDataGrid().SetData(row, 1, iData[row-1], 0);
	
	//	pChart->GetDataGrid().SetData(row, 2, rand() * 100 / RAND_MAX, 0);
	//	pChart->GetDataGrid().SetData(row, 3, rand() * 100 / RAND_MAX, 0);
    }

	pChart->SetRedraw(true);
	pChart->Refresh();	
	
}

void CChartView::DisplayChart2() //年度图
{
	// TODO: Add extra validation here
	strTitle.Format("%d年( %s )销售走势图",dateConsume.GetYear(),strName);
	pChartYear->SetRedraw(false);
	//	pChartYear->GetBackdrop().GetFill().SetStyle(1);
//	pChartYear->GetBackdrop().GetFill().GetBrush().GetFillColor().Set(255, 0, 255);


	// 栈模式
	pChartYear->SetStacking(FALSE);

	// Y轴设置
    COleVariant var(DISP_E_PARAMNOTFOUND,VT_ERROR);
	int maxFoot=0;
	for(long row=0 ; row < 11 ; row ++ ){
		if( iYearData[maxFoot] < iYearData[row+1] ) maxFoot=row+1;

	}

	pChartYear->GetPlot().GetAxis(1,var).GetValueScale().SetAuto(FALSE);	// 不自动标注Y轴刻度
	pChartYear->GetPlot().GetAxis(1,var).GetValueScale().SetMaximum(iYearData[maxFoot] );	// Y轴最大刻度
	pChartYear->GetPlot().GetAxis(1,var).GetValueScale().SetMinimum(0);		// Y轴最小刻度
	pChartYear->GetPlot().GetAxis(1,var).GetValueScale().SetMajorDivision(0);	// Y轴刻度5等分
	pChartYear->GetPlot().GetAxis(1,var).GetValueScale().SetMinorDivision(0);	// 每刻度一个刻度线
	pChartYear->GetPlot().GetAxis(1,var).GetAxisTitle().SetText("数量");	// Y轴名称
	
	pChartYear->SetColumnCount(1); 

	// 线色
	pChartYear->GetPlot().GetSeriesCollection().GetItem(1).GetPen().GetVtColor().Set(0, 255, 0);

	// 线宽(对点线图有效)
	pChartYear->GetPlot().GetSeriesCollection().GetItem(1).GetPen().SetWidth(40);

	// 数据点类型显示数据值的模式(对柱柱状图和点线图有效)
	// 0: 不显示	1: 显示在柱状图外
	// 2: 显示在柱状图内上方	3: 显示在柱状图内中间	4: 显示在柱状图内下方
	pChartYear->GetPlot().GetSeriesCollection().GetItem(1).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);

	pChartYear->SetRowCount(12);
	pChartYear->GetPlot().GetAxis(0,var).GetCategoryScale().SetAuto(false);			// 不自动标注X轴刻度
	pChartYear->GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerLabel(1);// 每刻度一个标注
	pChartYear->GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerTick(1); // 每刻度一个刻度线
	
	pChartYear->GetPlot().GetAxis(0,var).GetAxisTitle().SetText(strTitle);			// X轴名称

	char buf[32];
	
	for( row = 1; row <= 12; ++row)
	{
		pChartYear->SetRow(row);
		sprintf(buf, "%d月", row);

		pChartYear->SetRowLabel((LPCTSTR)buf);
		pChartYear->GetDataGrid().SetData(row, 1,iYearData[row-1], 0);
	
    }
	pChartYear->SetRedraw(true);
	pChartYear->Refresh();	
}

void CChartView::GetYearData()
{
	if(flagYearDataEffect == 1 ) return ; //年度数据有效

	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryYear;
	pg.DoModal();
}

void CChartView::OnDblClickMschart2() 
{
	// TODO: Add your control notification handler code here
	plotStyleNum2++;
	if( plotStyleNum2 == 3 ) plotStyleNum2 = 0;
	
	pChartYear->SetChartType( plotStyle[plotStyleNum2] );
	DisplayChart2();
	
}

void CChartView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN, 2, 0);
}

UINT CChartView::QueryYear(LPVOID ps)
{
	CChartView * pd=(CChartView * )((CProgressIndicate *)ps)->pDialog;

	CString strSql,strTmp;
	int row;
		
//	for( row=0 ; row <12 ;row++)pd->iYearData[row]=0;

	try{

		strSql.Format("SELECT to_char( trunc(riqi,'mm'),'mm'),NVL(sum(SL),0) FROM itemti WHERE ypbm='%s' and \
			riqi between to_date(%s,'yyyymmdd') and to_date(%s,'yyyymmdd') and substr(danjuhao,1,1) \
			in ('G','B','E') GROUP by trunc(riqi,'mm') order BY trunc(riqi,'mm') ",\
			pd->strYpbm,pd->dateConsume.Format("%Y")+"0101",pd->dateConsume.Format("%Y")+"1231" );

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
	
		while(!recSet->adoEOF){
			strTmp=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(0l))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(0l))->Value);
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(1l))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(1l))->Value);
	
			pd->iYearData[atol(strTmp)-1]=atof(strSql);
			recSet->MoveNext();

		}
		recSet->Close();
		pd->flagYearDataEffect=1; //年度数据有效

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		goto END;
	}
END:
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);	
	return true;
}

HBRUSH CChartView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetBkMode(TRANSPARENT);
	if( GetDlgItem(IDC_STATIC_TITLE)->m_hWnd == pWnd->m_hWnd )
	{
		pDC->SetBkColor(RGB(0,70,140));
		pDC->SetTextColor(RGB(255,255,255));
		return backBrush;
	}
	
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
