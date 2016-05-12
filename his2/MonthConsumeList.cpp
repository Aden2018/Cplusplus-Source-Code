// MonthConsumeList.cpp: implementation of the CMonthConsumeList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "MonthConsumeList.h"
#include "progressIndicate.h"
#include "chartView.h"
#include "selectView.h"
#include "manMedused.h"
#include "DoctorMedused.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMonthConsumeList::CMonthConsumeList()
{

}

CMonthConsumeList::~CMonthConsumeList()
{

}

BOOL CMonthConsumeList::OnInitDialog()
{
	CDoctorWorkLoad::OnInitDialog();

	CComboBox * pc=(CComboBox*)GetDlgItem(IDC_COMBO1);
	//CenterWindow();
	GetDlgItem(IDC_STATIC1)->SetWindowText("编码");
	GetDlgItem(IDC_STATIC2)->SetWindowText("拼音");
	GetDlgItem(IDC_STATIC_2)->SetWindowText("月份");
	GetDlgItem(IDC_STATIC_1)->SetWindowText("库房");
	GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_DATETIMEPICKER1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATETIMEPICKER2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATETIMEPICKER3)->ShowWindow(SW_SHOW);

	CRect rt1;
	GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	c_edit1.MoveWindow(rt1);
	c_edit1.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DATETIMEPICKER2)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	c_edit3.MoveWindow(rt1);
	c_edit3.ShowWindow(SW_SHOW);
	
	pc->ShowWindow(SW_SHOW);
	pc->ResetContent();
	
	SetGridHead();
	return true;
}

void CMonthConsumeList::OnOK()
{
	UpdateData();
	CString strNoti;
	strNoti.Format("%d年%d月 药品消耗明细表",m_date3.GetYear(),m_date3.GetMonth() );
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strNoti);

	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryMonth;
	pg.DoModal();

}

void CMonthConsumeList::SetGridHead()
{
	UpdateData();
	CString HeadTitle[]={"序号","编码","名称","规格","单位"} ,strTmp;//共 
	
	long  headWidth[]={600,820,1100,1000,400,1300,1000,1000,1000,1100,1000,1000,1000,1000,1000,1600,1300,1300,1300,0,1300,1300,1300,00,00,1400};
	int days=CHis2App::GetMonthDays(m_date3.GetYear(),m_date3.GetMonth() )+1 ;//加上一个合计
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString)+days);
	m_grid.SetFixedCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<4){
			m_grid.SetMergeCol(i,true);// 前6列单元格进行合
			m_grid.SetColAlignment(i,4);
		}
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
	for( count=0 ; count<days; count++){
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		m_grid.SetColWidth(i,600);
		strTmp.Format("%ld",count+1 );
		if( count != days-1 )m_grid.SetTextArray(i++,strTmp);
		else m_grid.SetTextArray(i++,"合计");
		
	}

}

UINT CMonthConsumeList::QueryMonth(LPVOID ps)
{
	CMonthConsumeList * pd=(CMonthConsumeList * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);

	pd->UpdateData();
	int days=CHis2App::GetMonthDays(pd->m_date3.GetYear(),pd->m_date3.GetMonth());
	pd->SetGridHead();

	CString strSql,str1,strTmp,str2;
	long cols,row,i,col;
	double add[32];
	const int START_COMPUTE=4; //在SQL语句中
	
	for( i=0 ;i <32 ;i++) add[i]=0.;
	COleDateTime setDate;
	try{
//构造出 SELECT bm,mc,gg,dw,sum(d1),sum(d2)...monthADD from medcode a,(select *...)
//形式
		strSql.Format("SELECT bm,mc,gg,dw,");
		strTmp="";
		for(  i=0 ; i <days ;i++ ){
			strTmp.Format("d%d , ",i+1); //日期名
			strSql+=strTmp;
		}
		
		pd->c_edit3.GetWindowText(str1); //拼音
		pd->c_edit1.GetWindowText(str2) ;// 编码
		if( ! str1.IsEmpty() && ! str2.IsEmpty() ) 
			strTmp.Format(" (SELECT * from medcode where py like '%s%%' AND bm like '%s%%' ) ",str1,str2);
		else if ( !str1.IsEmpty() )
			strTmp.Format(" (SELECT * from medcode where py like '%s%%' ) ",str1);
		else if( ! str2.IsEmpty() )
			strTmp.Format(" (SELECT * from medcode where bm like '%s%%' ) ",str2);
		else strTmp=" medcode ";



		strSql+=" Monthadd FROM "+strTmp+" a, ( SELECT YPBM,";
		
		for( i=0 ; i <days ;i++ ){
			setDate.SetDate(pd->m_date3.GetYear(),pd->m_date3.GetMonth(),i+1);
			strTmp.Format(" SUM( DECODE( riqi,to_date(%s,'yyyymmdd'),SL,NULL) ) d%d , ",setDate.Format("%Y%m%d"),i+1); //日期名
			strSql+=strTmp;
		}
			
		strSql+=" SUM( NVL(sl,0) ) monthAdd FROM ITEMTI WHERE SUBSTR(danjuhao,1,1) in ('G','E','B') and \
			riqi ";
		strTmp.Format(" BETween Trunc(to_date(%s,'yyyymmdd'),'mm') and  to_date(%s,'yyyymmdd') ",setDate.Format("%Y%m%d"),setDate.Format("%Y%m%d") );

		strSql+=strTmp+" GROUP BY YPBM ) b WHERE a.bm=b.ypbm(+) ";

		
///////////////////////////////////////////////////////
		

		strSql+=" ORDER BY BM,MC ";
	 	
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		cols=recSet->GetFields()->Count;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			str1.Format("%ld",row);
			pd->m_grid.SetTextMatrix(row,col++,str1);
	/*		pd->m_grid.SetRow(row);
			pd->m_grid.SetCol(6);
			pd->m_grid.SetCellBackColor(BK1);
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

		pd->m_grid.SetMergeCells(true);
		pd->m_grid.SetMergeRow(row,1); 
		pd->m_grid.SetRow(row);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("共有 %ld 条记录",row-1);
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

		
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
	
		return false;
	}	
	pd->m_grid.SetRedraw(true);
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);	return true;

}



void CMonthConsumeList::OnDblClickMshflexgrid1()
{

	UpdateData();
	long rows=m_grid.GetRows(),row=m_grid.GetRow(),i;
	if( rows == 2 || row == 0 || row == rows-1 ) return ;
	CSelectView sv;
	CChartView vi;
	CManMedused mu;
	CDoctorMedUsed du;
	
	if( m_grid.GetCol() == m_grid.GetCols(0)-1 ){ //最后一列为当月消耗的药品总数,我们作为查询医生工作量来统计
		du.strBM=m_grid.GetTextMatrix(row,1); //药品编码
		du.date=m_date3;
		du.iday=atol(m_grid.GetTextMatrix(0,m_grid.GetCol() ) );
		du.last_day=atol(m_grid.GetTextMatrix(0,m_grid.GetCols(0)-2) ); //最后一天日期
		i=0;
		du.strTmp[i]=m_grid.GetTextMatrix(row,i+1);i++;
		du.strTmp[i]=m_grid.GetTextMatrix(row,i+1);i++;
		du.strTmp[i]=m_grid.GetTextMatrix(row,i+1);i++;
		du.strTmp[i]=m_grid.GetTextMatrix(row,i+1);i++;

		du.DoModal();
		return;


	}
	
	if(sv.DoModal() ==IDCANCEL) return;

	if( sv.flagSelect!= CB_ERR && sv.strSelect == "走势图" ){
		//显示药品消耗趋势图
		vi.dateConsume=m_date3;
		vi.strYpbm=m_grid.GetTextMatrix(row,1); //药品编码
		vi.effectCols=m_grid.GetCols(0)-6 ;
		vi.strName.Format("%s %s %s/%s",m_grid.GetTextMatrix(row,1),m_grid.GetTextMatrix(row,2),m_grid.GetTextMatrix(row,3),m_grid.GetTextMatrix(row,4) );
		
		for (i=0 ; i < vi.effectCols ; i++ )
		{
			vi.iData[i]=atof( m_grid.GetTextMatrix(row,i+5) );
		}
		vi.DoModal();
	
	}
	else if( sv.flagSelect!= CB_ERR && sv.strSelect == "消耗人"){
		//显示药品消耗人员
		mu.strBM=m_grid.GetTextMatrix(row,1); //药品编码
		mu.date=m_date3;
		mu.iday=atol(m_grid.GetTextMatrix(0,m_grid.GetCol() ) );
		if( mu.iday <1 || mu.iday >31  ) return;
		i=0;
		mu.strTmp[i]=m_grid.GetTextMatrix(row,i+1);i++;
		mu.strTmp[i]=m_grid.GetTextMatrix(row,i+1);i++;
		mu.strTmp[i]=m_grid.GetTextMatrix(row,i+1);i++;
		mu.strTmp[i]=m_grid.GetTextMatrix(row,i+1);i++;

		mu.DoModal();
	}


	
	
}
