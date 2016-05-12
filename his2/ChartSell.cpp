// ChartSell.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "ChartSell.h"
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
// CChartSell dialog


CChartSell::CChartSell(CWnd* pParent /*=NULL*/)
	: CDialog(CChartSell::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartSell)
	m_date = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(160,"黑体");
	flagYearDataEffect=0;
	for ( int i=0; i< 12 ;i++ ){
		fData1[i]=0;
		fData2[i]=0;
		fData3[i]=0;
		fData4[i]=0;
		fData5[i]=0;
	}
}


void CChartSell::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartSell)
	DDX_Control(pDX, IDC_COMBO1, combo1);
	DDX_Control(pDX, IDCANCEL, m_2);
	DDX_Control(pDX, IDOK, m_1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid1);
	DDX_Control(pDX, IDC_MSHFLEXGRID3, m_grid3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartSell, CDialog)
	//{{AFX_MSG_MAP(CChartSell)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, OnDatetimechangeDatetimepicker1)
	ON_WM_LBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartSell message handlers

BOOL CChartSell::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString strTmp;
	strTmp=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_Title_list WHERE ds2='DIALOG' AND ds3='TITLE' and \
		ds4='AAA' ");


	GetDlgItem(IDC_STATIC_HEAD)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_HEAD)->SetWindowText(strTmp);
	backBrush.CreateSolidBrush(RGB(0,0,132));
	
	plotNum1= 0;
	plotNum2= 0;
	plotStyle[0]=3;
	plotStyle[1]=1;
	plotStyle[2]=14;

	p1=(CMSChart *) GetDlgItem(IDC_MSCHART1);
	p2=(CMSChart *) GetDlgItem(IDC_MSCHART2);

	p1->SetChartType( plotStyle[plotNum1] );
	p2->SetChartType( plotStyle[plotNum2] );
	p1->SetAllowSelections(false);
	p2->SetAllowSelections(false);
	CString strMonth[12]={"一月","二月","三月","四月","五月","六月","七月","八月","九月","十月","十一月","十二月"};
	for(int i=1 ;i<=12 ;i++){
		m_grid1.SetRow(0);
		m_grid1.SetCol(i);
		m_grid1.SetCellAlignment(4);
		m_grid1.SetTextMatrix(0,i,strMonth[i-1]);
		m_grid1.SetColWidth(i,0,1000);
	
		m_grid3.SetRow(0);
		m_grid3.SetCol(i);
		m_grid3.SetCellAlignment(4);
		m_grid3.SetColWidth(i,0,1000);
		m_grid3.SetTextMatrix(0,i,strMonth[i-1]);
	}
	m_grid1.SetRow(0);
	m_grid1.SetCol(0);
	m_grid1.SetCellAlignment(4);
	m_grid1.SetTextMatrix(0,0,"类  别");
	m_grid1.SetTextMatrix(1,0,"销售总额");
	m_grid1.SetTextMatrix(2,0,"成  本");
	m_grid1.SetColAlignment(0,4);
	m_grid3.SetRow(0);
	m_grid3.SetCol(0);
	m_grid3.SetCellAlignment(4);
	m_grid3.SetTextMatrix(0,0,"类  别");
	m_grid3.SetTextMatrix(1,0,"其它费用");
	m_grid3.SetTextMatrix(2,0,"药品利润");
	m_grid3.SetColAlignment(0,4);
	m_grid1.SetColWidth(0,0,1200);
	m_grid3.SetColWidth(0,0,1200);
	for(int year=m_date.GetYear() ;year > m_date.GetYear()-5; year-- )
	{
		strTmp.Format("%d",year);
		combo1.AddString(strTmp);
	}
	combo1.SetCurSel(0);//默认为当年

	DisplayChart1();
	DisplayChart2();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CChartSell::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetBkMode(TRANSPARENT);
	if( GetDlgItem(IDC_STATIC_HEAD)->m_hWnd == pWnd->m_hWnd )
	{
		pDC->SetBkColor(RGB(0,70,140));
		pDC->SetTextColor(RGB(255,255,255));
		return backBrush;
	}
	
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
#define MAX_MONTH 12
void CChartSell::DisplayChart1()
{
	// TODO: Add extra validation here
//	pChart->SetTitleText(strTitle);
	// 下面两句改变背景色
	p1->SetRedraw(false);
//	p1->GetBackdrop().GetFill().SetStyle(1);
//	p1->GetBackdrop().GetFill().GetBrush().GetFillColor().Set(0, 255, 255);



	// 栈模式
	p1->SetStacking(FALSE);

	// Y轴设置
	COleVariant var(DISP_E_PARAMNOTFOUND,VT_ERROR);
	int maxFoot=0;
	for(long row=0 ; row < MAX_MONTH -1 ; row ++ ){
		if( fData4[maxFoot] < fData4[row+1] ) maxFoot=row+1;

	}
	p1->GetPlot().GetAxis(1,var).GetValueScale().SetAuto(FALSE);	// 不自动标注Y轴刻度
	p1->GetPlot().GetAxis(1,var).GetValueScale().SetMaximum( fData4[maxFoot] );	// Y轴最大刻度
	p1->GetPlot().GetAxis(1,var).GetValueScale().SetMinimum(0);		// Y轴最小刻度
	p1->GetPlot().GetAxis(1,var).GetValueScale().SetMajorDivision(0);	// Y轴刻度5等分
	p1->GetPlot().GetAxis(1,var).GetValueScale().SetMinorDivision(0);	// 每刻度一个刻度线
	p1->GetPlot().GetAxis(1,var).GetAxisTitle().SetText(yStr);	// Y轴名称

	// 3条曲线
//	p1->SetColumnCount(3); 
	p1->SetColumnCount(2); 

	p1->SetShowLegend(TRUE);
	p1->SetColumn(1);
	p1->SetColumnLabel(yStr);
	p1->SetColumn(2);
	p1->SetColumnLabel((LPCTSTR)"成本");
	// 线色
	p1->GetPlot().GetSeriesCollection().GetItem(1).GetPen().GetVtColor().Set(255, 0, 0);
	p1->GetPlot().GetSeriesCollection().GetItem(2).GetPen().GetVtColor().Set(0,255, 0);
//	p1->GetPlot().GetSeriesCollection().GetItem(3).GetPen().GetVtColor().Set(0, 255, 0);

	// 线宽(对点线图有效)
	p1->GetPlot().GetSeriesCollection().GetItem(1).GetPen().SetWidth(40);
//	p1->GetPlot().GetSeriesCollection().GetItem(2).GetPen().SetWidth(100);
//	p1->GetPlot().GetSeriesCollection().GetItem(3).GetPen().SetWidth(1);

	// 数据点类型显示数据值的模式(对柱柱状图和点线图有效)
	// 0: 不显示	1: 显示在柱状图外
	// 2: 显示在柱状图内上方	3: 显示在柱状图内中间	4: 显示在柱状图内下方
//	p1->GetPlot().GetSeriesCollection().GetItem(1).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);
//	p1->GetPlot().GetSeriesCollection().GetItem(2).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);

	p1->SetRowCount(MAX_MONTH);
	p1->GetPlot().GetAxis(0,var).GetCategoryScale().SetAuto(false);			// 不自动标注X轴刻度
	p1->GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerLabel(1);// 每刻度一个标注
	p1->GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerTick(1); // 每刻度一个刻度线
	
	p1->GetPlot().GetAxis(0,var).GetAxisTitle().SetText(strTitle);			// X轴名称

	char buf[32];
	
	for( row = 1; row <= MAX_MONTH ; ++row)
	{
	//	dbData[row-1]=row*10;
		p1->SetRow(row);
		sprintf(buf, "%d月", row);

		p1->SetRowLabel((LPCTSTR)buf);
		p1->GetDataGrid().SetData(row, 1, fData4[row-1], 0);
		p1->GetDataGrid().SetData(row, 2, fData5[row-1], 0);
	
	//	p1->GetDataGrid().SetData(row, 2, rand() * 100 / RAND_MAX, 0);
	//	p1->GetDataGrid().SetData(row, 3, rand() * 100 / RAND_MAX, 0);
    }

	p1->SetRedraw(true);
	p1->Refresh();	
}

void CChartSell::DisplayChart2()
{
	p2->SetRedraw(false);
	// 栈模式
	p2->SetStacking(FALSE);

	// Y轴设置
	COleVariant var(DISP_E_PARAMNOTFOUND,VT_ERROR);
	int maxFoot=0,max2Foot=0;
	for(long row=0 ; row < MAX_MONTH -1 ; row ++ ){
		if( fData2[maxFoot] < fData2[row+1] ) maxFoot=row+1;

	}
	for( row=0 ; row < MAX_MONTH -1 ; row ++ ){
		if( fData3[max2Foot] < fData3[row+1] ) max2Foot=row+1;

	}

	p2->GetPlot().GetAxis(1,var).GetValueScale().SetAuto(FALSE);	// 不自动标注Y轴刻度
	p2->GetPlot().GetAxis(1,var).GetValueScale().SetMaximum( fData2[maxFoot]>fData3[max2Foot] ? fData2[maxFoot]:fData3[max2Foot] );	// Y轴最大刻度
	p2->GetPlot().GetAxis(1,var).GetValueScale().SetMinimum(0);		// Y轴最小刻度
	p2->GetPlot().GetAxis(1,var).GetValueScale().SetMajorDivision(0);	// Y轴刻度5等分
	p2->GetPlot().GetAxis(1,var).GetValueScale().SetMinorDivision(0);	// 每刻度一个刻度线
	p2->GetPlot().GetAxis(1,var).GetAxisTitle().SetText(yStr);	// Y轴名称

	// 3条曲线
//	p2->SetColumnCount(3); 
	p2->SetColumnCount(2); 

	p2->SetShowLegend(TRUE);
	p2->SetColumn(1);
	p2->SetColumnLabel(yStr);
	p2->SetColumn(2);
	p2->SetColumnLabel((LPCTSTR)"药品利润");
	// 线色
	p2->GetPlot().GetSeriesCollection().GetItem(1).GetPen().GetVtColor().Set(255, 0, 0);
	p2->GetPlot().GetSeriesCollection().GetItem(2).GetPen().GetVtColor().Set(255,255, 0);
//	p2->GetPlot().GetSeriesCollection().GetItem(3).GetPen().GetVtColor().Set(0, 255, 0);

	// 线宽(对点线图有效)
	p2->GetPlot().GetSeriesCollection().GetItem(1).GetPen().SetWidth(40);
	p2->GetPlot().GetSeriesCollection().GetItem(2).GetPen().SetWidth(40);
//	p2->GetPlot().GetSeriesCollection().GetItem(3).GetPen().SetWidth(1);

	// 数据点类型显示数据值的模式(对柱柱状图和点线图有效)
	// 0: 不显示	1: 显示在柱状图外
	// 2: 显示在柱状图内上方	3: 显示在柱状图内中间	4: 显示在柱状图内下方
//	p2->GetPlot().GetSeriesCollection().GetItem(1).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);
//	p2->GetPlot().GetSeriesCollection().GetItem(2).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);

	p2->SetRowCount(MAX_MONTH);
	p2->GetPlot().GetAxis(0,var).GetCategoryScale().SetAuto(false);			// 不自动标注X轴刻度
	p2->GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerLabel(1);// 每刻度一个标注
	p2->GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerTick(1); // 每刻度一个刻度线
	
	p2->GetPlot().GetAxis(0,var).GetAxisTitle().SetText(strTitle);			// X轴名称

	char buf[32];
	
	for( row = 1; row <= MAX_MONTH ; ++row)
	{
	//	dbData[row-1]=row*10;
		p2->SetRow(row);
		sprintf(buf, "%d月", row);

		p2->SetRowLabel((LPCTSTR)buf);
		p2->GetDataGrid().SetData(row, 1, fData2[row-1], 0); //其它费用
		p2->GetDataGrid().SetData(row, 2, fData3[row-1], 0); //药品利润
	
    }

	p2->SetRedraw(true);
	p2->Refresh();	
}

void CChartSell::GetYearData()
{
	if(flagYearDataEffect == 1 ) return ; //年度数据有效

	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryYearData;
	pg.DoModal();

}

UINT CChartSell::QueryYearData(LPVOID ps)
{
	CChartSell * pd=(CChartSell * )((CProgressIndicate *)ps)->pDialog;
	pd->UpdateData();

	CString strSql,strTmp;
	long col,i;		
	CString str1,str2;

	try{

		strSql.Format("SELECT to_char(trunc(riqi,'mm'),'mm'),sum(medMoney),sum(treateMoney),sum(profit),\
			sum(MedMoney+treateMoney),sum(Medmoney-profit) from itemregistertou\
			where riqi between to_date(%s,'yyyymmdd') and to_date(%s,'yyyymmdd') group by \
			trunc(riqi,'mm') order BY trunc(riqi,'mm') ",pd->m_date.Format("%Y")+"0101",pd->m_date.Format("%Y")+"1231" );

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		while(!recSet->adoEOF){
			col=0;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(col))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(col))->Value);
			col++;
			strTmp=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(col))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(col))->Value);
			pd->fData1[atol(strSql)-1]=atof(strTmp); col++; //药品费
		
			strTmp=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(col))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(col))->Value);
			pd->fData2[atol(strSql)-1]=atof(strTmp); col++; //其它费
		
			strTmp=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(col))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(col))->Value);
			pd->fData3[atol(strSql)-1]=atof(strTmp); col++; //药品利润
		
			strTmp=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(col))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(col))->Value);
			pd->fData4[atol(strSql)-1]=atof(strTmp); col++; //总费
		
			strTmp=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(col))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(col))->Value);
			pd->fData5[atol(strSql)-1]=atof(strTmp);  //成本=药品费-药品利润
		

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
	for( i=1; i<=12 ; i++ ){
		strSql.Format("%.2f",pd->fData4[i-1]);
		pd->m_grid1.SetTextMatrix(1,i,strSql);
		
		strSql.Format("%.2f",pd->fData5[i-1]);
		pd->m_grid1.SetTextMatrix(2,i,strSql);

		strSql.Format("%.2f",pd->fData2[i-1]);
		pd->m_grid3.SetTextMatrix(1,i,strSql);
		strSql.Format("%.2f",pd->fData3[i-1]);
		pd->m_grid3.SetTextMatrix(2,i,strSql);

	}
END:
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);	
	return true;
}

void CChartSell::OnOK() 
{
	GetYearData();
	
	yStr="总金额";
	strTitle.Format("%d年销售 总金额/成本走势图 (单位:元)",m_date.GetYear());
	DisplayChart1();
	
	yStr="其它费用";
	strTitle.Format("%d年其它治疗.利润走势图 (单位:元)",m_date.GetYear());
	DisplayChart2();
}

void CChartSell::OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
		flagYearDataEffect=0;
		for ( int i=0; i< 12 ;i++ ){
			fData1[i]=0;
			fData2[i]=0;
			fData3[i]=0;
			fData4[i]=0;
			fData5[i]=0;
		}//	*pResult = 0;
}

BEGIN_EVENTSINK_MAP(CChartSell, CDialog)
    //{{AFX_EVENTSINK_MAP(CChartSell)
	ON_EVENT(CChartSell, IDC_MSCHART1, -601 /* DblClick */, OnDblClickMschart1, VTS_NONE)
	ON_EVENT(CChartSell, IDC_MSCHART2, -601 /* DblClick */, OnDblClickMschart2, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CChartSell::OnDblClickMschart1() 
{
	// TODO: Add your control notification handler code here
	plotNum1++;
	if( plotNum1 == 3 ) plotNum1= 0;
	
	p1->SetChartType( plotStyle[plotNum1] );
	yStr="总金额";
	strTitle.Format("%d年销售 总金额/成本走势图 (单位:元)",m_date.GetYear());
	DisplayChart1();
	
}

void CChartSell::OnDblClickMschart2() 
{
	plotNum2++;
	if( plotNum2 == 3 ) plotNum2 = 0;
	
	p2->SetChartType( plotStyle[plotNum2] );
	yStr="其它费用";
	strTitle.Format("%d年其它治疗.利润走势图 (单位:元)",m_date.GetYear());
	DisplayChart2();
	// TODO: Add your control notification handler code here
	
}

void CChartSell::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
	CDialog::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN, 2, 0);
}

void CChartSell::OnSelchangeCombo1() 
{
	CString strTmp;
	combo1.GetLBText(combo1.GetCurSel(),strTmp);
	m_date.SetDate(	atoi(strTmp),1,1);
	OnDatetimechangeDatetimepicker1(NULL, NULL); 
	UpdateData(false);
}
