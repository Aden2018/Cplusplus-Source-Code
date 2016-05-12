// FinanceReport.cpp: implementation of the CFinanceReport class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "FinanceReport.h"
#include "progressIndicate.h"
#include "excel9.h"
#include "OperatChargeRelateFee.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFinanceReport::CFinanceReport()
{
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_Title_list WHERE ds2='DIALOG' AND ds3='TITLE' and \
		ds4='AAD' ");
}

CFinanceReport::~CFinanceReport()
{

}

void CFinanceReport::SetGridHead()
{
	CString HeadTitle[]={"序号","科目名称","门诊人次"},strTmp;
//	CString subHead[]={"总额","其它费用","现金","帐户/统筹","药品成本","药品利润","总利润"} ;//共 8 列

	CString subHead[]={"帐户/统筹","现金","总额","其它费用","药品利润","总利润","药品成本"} ;//共 8 列
	
	long  headWidth[]={800,1200,900,1000,1000,1000,1100,1000,1000,1000,1000,1000,1600,1300,1300,1300,0,1300,1300,1300,00,00,1400};
	
	m_grid.Clear();
	m_grid.SetRows(4);
	m_grid.SetFixedRows(3);
	m_grid.SetRedraw(false);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	long cols=sizeof(HeadTitle)/sizeof(CString)+sizeof(subHead)/sizeof(CString) ;
	long subCols=sizeof(HeadTitle)/sizeof(CString);

	m_grid.SetCols(cols );
	m_grid.SetRow(0);
	m_grid.SetFixedCols(2);
	long  i=0,col(0),row(0);
	for(int count=0;count<subCols;count++){
		m_grid.SetColAlignmentFixed(count,4);
		m_grid.SetMergeCol(count,true);
	
		for ( i=0; i<3 ; i++){
			m_grid.SetTextMatrix(i,count,HeadTitle[count] );
		}

		m_grid.SetColWidth(count,0,headWidth[count]);
		
	}

	m_grid.SetMergeCells(true);
	
	for( count=0;count< cols-subCols;count++){
		m_grid.SetColAlignmentFixed(count+subCols,4);
		m_grid.SetMergeRow(0,true);
		m_grid.SetTextMatrix(0,count+subCols,"各项医疗经费分类汇总");
		strTmp.Format("%ld",count+1);
		m_grid.SetTextMatrix(1,count+subCols,strTmp);
		m_grid.SetTextMatrix(2,count+subCols,subHead[count]);

		m_grid.SetColWidth(count+subCols,0,1400 );
	}

	m_grid.SetRedraw(true);

}

BOOL CFinanceReport::OnInitDialog()
{
	CDoctorWorkLoad::OnInitDialog();
	c_print.ShowWindow(SW_SHOW);

	return true;

}

void CFinanceReport::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryReport;
	pg.DoModal();

}

UINT CFinanceReport::QueryReport(LPVOID ps)
{
	CFinanceReport * pd=(CFinanceReport * )((CProgressIndicate *)ps)->pDialog;

	pd->SetGridHead();

	pd->m_grid.SetRedraw(false);
	CString strSql,str1;
	long cols,row,i,col;
	double add[20];
	const int START_COMPUTE=1; //在SQL语句中
	for( i=0 ; i< 20 ;i++)add[i]=0.0;
	pd->UpdateData();
//	CString subHead[]={"总额","其它费用","现金","帐户/统筹","药品成本","药品利润","总利润"} ;//共 8 列
//new	CString subHead[]={"帐户/统筹","现金","总额","其它费用","药品利润","总利润","药品成本"} ;//共 8 列
	try{
//		strSql.Format("select ds1,sum(c1),sum(x1+x2),sum(x2),sum(x3),sum(x1+x2-x3),sum(x1-x4),sum(x4),sum(x4+x2) 
//      LSQ_GH_TYPE DS3='A' 作为统计时使用,其它作为另外方式使用
		strSql.Format("select ds1,sum(c1),sum(x1+x2-x3),sum(x3),sum(x1+x2),sum(x2),sum(x4),sum(x4+x2),sum(x1-x4) \
			from (select ds1,ds2,n1 from lsq_gh_type WHERE ds3='A') a,\
			(select ghtype,count(*) c1,sum(medMoney) x1,sum(treateMoney) x2,sum(cash) x3,sum(profit) x4 from itemregistertou \
				where riqi between to_date(%s,'yyyymmdd') and to_date(%s,'yyyymmdd') group by ghtype ) b \
			where a.ds2=b.ghtype(+) group by a.ds1,a.n1 order by a.n1 ",pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d") );

	 	
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=3;
		cols=recSet->GetFields()->Count;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			str1.Format("%ld",row-2);
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
		strSql.Format("共有%ld 条",row-3);
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
	return true;
}

void CFinanceReport::OnButtonPrint() //打印
{
extern _Application app;
extern Workbooks books;
extern _Workbook book;
extern Worksheets sheets;
extern _Worksheet sheet;
extern COleVariant vOpt;
#define _O(x) COleVariant(x)

	UpdateData();

	BeginWaitCursor();

	CString strFileName,strCell,strData;
	strFileName.Format("%s",LoginInformation.path);
	strFileName+="chargeprice.xls";


	if( ! app ){
		app.CreateDispatch("excel.application");
		if(!app){
			AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
			return;
		}
		books=app.GetWorkbooks();
		book=books.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
		sheets=book.GetWorksheets();

	}
	sheet=sheets.GetItem(COleVariant((short) 3 )); //sheet3 作为医院财务报表
	long cols=m_grid.GetCols(0)-2,i,rows=m_grid.GetRows()-3,j;

	strData.Format("%d年%d月%d日 ---------- %d年%d月%d日",m_date1.GetYear(),m_date1.GetMonth(),m_date1.GetDay(),\
		m_date2.GetYear(),m_date2.GetMonth(),m_date2.GetDay() );
	Range vRange;
	vRange=sheet.GetRange(_O("A4"),_O("A4")); // 医疗机构
	vRange.SetValue(COleVariant(strData));
	
	app.SetVisible(true);
	for( i=0 ;i < rows ; i++ )
		for( j=0 ;j < cols ; j++ ){
			strCell.Format("%c%d",'C'+j,i+9 );
			COperatChargeRelateFee::WriteExcelCell(strCell,m_grid.GetTextMatrix(i+3,j+2) );
		}

	PageSetup pageinfo=sheet.GetPageSetup();
/*	pageinfo.SetLeftMargin(0);
	pageinfo.SetRightMargin(0);
	pageinfo.SetTopMargin(0);
	pageinfo.SetBottomMargin(0);
*/
//	sheet.PrintPreview(_O((short)1));
//	sheet.PrintOut(vOpt,vOpt,_O((short)1),vOpt,vOpt,vOpt,vOpt,vOpt);


	sheet=sheets.GetItem(COleVariant((short)1)); //sheet1 打印收费单情况
	EndWaitCursor();
}


