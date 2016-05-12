// YearDataCountAnalyse.cpp: implementation of the CYearDataCountAnalyse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "YearDataCountAnalyse.h"
#include "progressIndicate.h"
#include "chartYeardataAnalyse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CYearDataCountAnalyse::CYearDataCountAnalyse()
{
	strConstName=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_Title_list WHERE ds2='DIALOG' AND ds3='TITLE' \
		AND ds4='AAC' ");

	strTitle=strConstName;

}

CYearDataCountAnalyse::~CYearDataCountAnalyse()
{

}

BOOL CYearDataCountAnalyse::OnInitDialog()
{
	CYearDataCount::OnInitDialog();
	SetGridHead();
	return true;

}

void CYearDataCountAnalyse::OnOK()
{
	UpdateData();
	
	strTitle.Format("%d年度%s",m_date2.GetYear(),strConstName);
	
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryAnalyse;
	pg.DoModal();

/*	SetGridHead();*/
}

void CYearDataCountAnalyse::SetGridHead()
{
	CString HeadTitle[]={"一月","二月","三月","四月","五月","六月","七月","八月","九月","十月","十一月","十二月","合 计"} ;//共 8 列
	CString subTitle[]={"总金额","其它费用","成本","利润","现金"};
//	long  headWidth[]={800,1000,1000,1000,1000,1000,1100,1000,1000,1000,1000,1000,1600,1300,1300,1300,0,1300,1300,1300,00,00,1400};
	
	m_grid.Clear();
	m_grid.SetRows(3);
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString)*5+2);
	m_grid.SetFixedCols(2);
	m_grid.SetRedraw(false);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetFixedRows(2);

	m_grid.SetRow(0);
	long  i=0,col(0),row(0),x;
	m_grid.SetMergeCol(0,true); //0 和 1 列合并
	m_grid.SetMergeCol(1,true); 
	m_grid.SetMergeRow(0,true);
	m_grid.SetTextArray(i++,"序号");
	m_grid.SetTextArray(i++,"就诊类别");
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		for(x=0; x< 5; x++){
			m_grid.SetCol((long) i);
			m_grid.SetCellAlignment((short)4); //居中对齐
		
			m_grid.SetColWidth(i,1000);
			m_grid.SetTextArray(i++,HeadTitle[count]);
		}
		
	}

	i=0;
	m_grid.SetRow(1);
	m_grid.SetTextMatrix(1,i++,"序号");
	m_grid.SetTextMatrix(1,i++,"就诊类别");
	for( count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		for(x=0; x< 5; x++){
			m_grid.SetCol((long) i);
			m_grid.SetCellAlignment((short)4); //居中对齐
			m_grid.SetColWidth(i,1000);
			m_grid.SetTextMatrix(1,i++,subTitle[x]);
		}
		
	}
	m_grid.SetCol(0);
	m_grid.SetCellAlignment((short)4); //居中对齐
	m_grid.SetCol(1);
	m_grid.SetCellAlignment((short)4); //居中对齐
	m_grid.SetRedraw(true);
}

UINT CYearDataCountAnalyse::QueryAnalyse(LPVOID ps)
{
	CYearDataCountAnalyse * pd=(CYearDataCountAnalyse * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);
	pd->SetGridHead();
	CString strSql,str1;
	long cols,row,i,col;
	double add[13*5];
	const int START_COMPUTE=1; //在SQL语句中
	for( i= 0 ; i < 13*5 ;i++ )add[i]=0.0;
	pd->UpdateData();
	try{
		strSql="SELECT ghtype,";
		for( i=0 ;i<12 ;i++)
		{
			str1.Format(" SUM( DECODE(to_number(to_char(riqi,'mm'),'99'),%d,MedMoney+treateMoney,0) ),\
				SUM( DECODE(to_number(to_char(riqi,'mm'),'99'),%d,treateMoney,0) ),\
				SUM( DECODE(to_number(to_char(riqi,'mm'),'99'),%d,MedMoney-Profit,0) ) ,\
				SUM( DECODE(to_number(to_char(riqi,'mm'),'99'),%d,proFit,0) ), \
				SUM( DECODE(to_number(to_char(riqi,'mm'),'99'),%d,Cash,0) ),",i+1,i+1,i+1,i+1,i+1 );
			strSql+=str1;
		}
		strSql+=" SUM(treateMoney+MedMoney),SUM( treateMoney),SUM(medMoney-Profit),SUM(Profit),SUM( cash ) FROM ItemRegisterTou ";
		str1.Format(" WHERE riqi between to_date('%s'||'0101','yyyymmdd') and to_date('%s'||'1231','yyyymmdd') \
			group by ghtype ",pd->m_date2.Format("%Y"),pd->m_date2.Format("%Y"));
		strSql+=str1;
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=2;
		cols=recSet->GetFields()->Count;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			str1.Format("%ld",row-1); //从第二列计起
			pd->m_grid.SetTextMatrix(row,col++,str1);
	/*		pd->m_grid.SetRow(row);
			pd->m_grid.SetCol(6);
			pd->m_grid.SetCellBackColor(BK1);
			pd->m_grid.SetCol(9);
			pd->m_grid.SetCellBackColor(BK2);
	*/		for(i=0;i<cols;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				pd->m_grid.SetTextMatrix(row,col++,str1);
				
				if( i>=START_COMPUTE )add[i-START_COMPUTE]+=atof(str1); 
			}
			row++;
			pd->m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();

//		str1.Format("总计: 需采购 %ld 条药品",row-1 );
//		pd->GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(str1);
		pd->m_grid.SetMergeCells(true);
		pd->m_grid.SetMergeRow(row,1); 
		pd->m_grid.SetRow(row);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("%ld条记录 ",row-1);
		pd->m_grid.SetTextMatrix(row,0,"合计");	
		
		
		for(int count=1;count<cols+1;count++){
			pd->m_grid.SetTextMatrix(row,count,strSql);	
			pd->m_grid.SetCol(count);
			pd->m_grid.SetCellBackColor(RGB(255,128,0));
			
		}
		
		for(i=START_COMPUTE;i<cols;i++){
			strSql.Format("%.2f",add[i-START_COMPUTE]);
			pd->m_grid.SetTextMatrix(row,i+1,strSql);
		}

		pd->m_grid.SetRedraw(true);
		
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
	
		return false;
	}	
	pd->m_grid.SetRedraw(true);
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
}

void CYearDataCountAnalyse::OnDblClickMshflexgrid1()
{
	UpdateData();
	long rows=m_grid.GetRows(),row=m_grid.GetRow();
	if( rows == 3 || row == 0 || row == 1 ) return ;
	
	CChartYearDataAnalyse ana;
	for(int i=0 ; i< 12*5 ; i++ )
		ana.dbData[i]=atof( m_grid.GetTextMatrix(row,i+2) );

	ana.strTitleAnalyse.Format("%d年度 (%s) 消耗金额统计表 单位:元",m_date2.GetYear(),m_grid.GetTextMatrix(row,1) );

	ana.DoModal();

}
