// BuySellStockQuery.cpp: implementation of the CBuySellStockQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "BuySellStockQuery.h"
#include "ProgressIndicate.h"
#include "buySellStocklist.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBuySellStockQuery::CBuySellStockQuery()
{

}

CBuySellStockQuery::~CBuySellStockQuery()
{

}

BOOL CBuySellStockQuery::OnInitDialog()
{
	CEverydayConsumeQuery::OnInitDialog();
	const CString strTitle="药品数量进销存 (以开始日期为准,主要精确到月查询)";
	SetWindowText(strTitle);

	return true;
}

void CBuySellStockQuery::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryDatabase;
	pg.DoModal();

}

UINT CBuySellStockQuery::QueryDatabase(LPVOID ps) //药品进销存明细表查询函数
{
	CBuySellStockList * pf=(CBuySellStockList *)theApp.pParentGrid.pWnd;
	CBuySellStockQuery * pd=(CBuySellStockQuery * )((CProgressIndicate *)ps)->pDialog;

	pf->m_grid.SetRedraw( false);
	pf->SetGridHead();
	pd->UpdateData();
	CString strSql,strTemp;
	long cc,row,cols,i;
	double add[8]={0.,.0,.0,0,0,0,0,0};
	COleDateTime NOWDATE=COleDateTime::GetCurrentTime();
	strSql.Format("药品( 进销存[%d月份] ) 明细表",pd->m_date1.GetMonth() );
	pf->GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strSql);

	int year,month,days;
	year=pd->m_date1.GetYear();
	month=pd->m_date1.GetMonth();
	days=CHis2App::GetMonthDays(year,month);
	

	try{
		if( !(pd->c_combo1.GetCurSel() == CB_ERR || pd->c_combo1.GetCurSel()== 0) ){

			if ( month < NOWDATE.GetMonth() )strTemp.Format("SELECT ypbm,sum(sl) stock FROM 期初库存 where nian=%d and yue=%d and kfbm='%s' group by ypbm",year+ (month%12 == 0 ? 1: 0),month%12 == 0 ? 1: month+1,pd->strCombo1Kfbm );
			else strTemp.Format("select ypbm,sum(sl) stock from medlie where kfbm='%s' group by ypbm ",pd->strCombo1Kfbm );

			strSql.Format("SELECT bm,mc,gg,dw,beg,rk,xh,stock 库存,er 盘点,NVL(beg,0)+NVL(rk,0)-NVL(xh,0)-NVL(stock,0) from \
								(select bm,mc,gg,dw,beg,rk,xh,stock,py from \
									( select bm,mc,gg,dw,rk,xh,stock,py from \
									    (select bm,mc,gg,dw,rk,xh,py from \
										      (select bm,mc,gg,dw,py from  medcode)   sa,   \
											  (select sum(decode(substr(danjuhao,1,1),'A',sl,0)) rk,\
												      sum(decode(substr(danjuhao,1,1),'G',sl,'E',sl,'B',sl,0)) xh,ypbm \
													  FROM itemti  where riqi between trunc(to_date(%s,'yyyymmdd'),'mm') and \
													  Last_day(to_date(%s,'yyyymmdd')) AND KFBM='%s' group by ypbm ) sb \
											   where sa.bm=sb.ypbm(+) ) aa,\
										(%s ) ab \
									where aa.bm=ab.ypbm(+) ) ac,\
								(select ypbm,sum(sl) beg from 期初库存 where nian=%d and yue=%d AND KFBM='%s' group by ypbm ) ad\
							where ac.bm=ad.ypbm(+)) t1,\
							 (select ypbm,sum(sl) er from itemti where riqi between Trunc(to_date(%s,'yyyymmdd'),'mm') and last_day(to_date(%s,'yyyymmdd') ) and \
								substr(danjuhao,1,1)='P' AND kfbm='%s' group by ypbm) t2 \
						 where t1.bm=t2.ypbm(+) ",pd->m_date1.Format("%Y%m%d"),pd->m_date1.Format("%Y%m%d"),\
						 pd->strCombo1Kfbm,strTemp,year,month,pd->strCombo1Kfbm,\
							pd->m_date1.Format("%Y%m%d"),pd->m_date1.Format("%Y%m%d"),pd->strCombo1Kfbm );
		}
		else { //未选择时列举全部库房
			if ( month < NOWDATE.GetMonth() && year <= NOWDATE.GetYear() )strTemp.Format("SELECT ypbm,sum(sl) stock FROM 期初库存 where nian=%d and yue=%d group by ypbm",year+ (month%12 == 0 ? 1: 0),month%12 == 0 ? 1: month+1);
			else strTemp.Format("select ypbm,sum(sl) stock from medlie  group by ypbm ");

			strSql.Format("SELECT bm,mc,gg,dw,beg,rk,xh,stock 库存,er 盘点,NVL(beg,0)+NVL(rk,0)-NVL(xh,0)-NVL(stock,0) from \
								(select bm,mc,gg,dw,beg,rk,xh,stock,py from \
									( select bm,mc,gg,dw,rk,xh,stock,py from \
									    (select bm,mc,gg,dw,rk,xh,py from \
										      (select bm,mc,gg,dw,py from  medcode)   sa,   \
											  (select sum(decode(substr(danjuhao,1,1),'A',sl,0)) rk,\
												      sum(decode(substr(danjuhao,1,1),'G',sl,'E',sl,'B',sl,0)) xh,ypbm \
													  FROM itemti  where riqi between trunc(to_date(%s,'yyyymmdd'),'mm') and \
													  Last_day(to_date(%s,'yyyymmdd')) group by ypbm ) sb \
											   where sa.bm=sb.ypbm(+) ) aa,\
										(%s ) ab \
									where aa.bm=ab.ypbm(+) ) ac,\
								(select ypbm,sum(sl) beg from 期初库存 where nian=%d and yue=%d group by ypbm ) ad\
							where ac.bm=ad.ypbm(+)) t1,\
							 (select ypbm,sum(sl) er from itemti where riqi between Trunc(to_date(%s,'yyyymmdd'),'mm') and last_day(to_date(%s,'yyyymmdd') ) and \
								substr(danjuhao,1,1)='P' group by ypbm) t2 \
						 where t1.bm=t2.ypbm(+) ",pd->m_date1.Format("%Y%m%d"),pd->m_date1.Format("%Y%m%d"),strTemp,year,month,\
							pd->m_date1.Format("%Y%m%d"),pd->m_date1.Format("%Y%m%d") );
	}

		pd->c_py.GetWindowText(strTemp);
		if(! strTemp.IsEmpty() ) strSql+=" AND PY like '"+strTemp+"%'";

		pd->c_editYpbm.GetWindowText(strTemp);
		if(! strTemp.IsEmpty() ) strSql+=" AND bm like '"+strTemp+"%'";
		strSql+=" ORDER BY bm,MC"	;

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		cols=recSet->GetFields()->Count;
	
		while(!recSet->adoEOF){
			i=0;
			strSql.Format("%ld",row);
			pf->m_grid.SetTextMatrix(row,0,strSql);
			for(cc=0;cc<cols;cc++)
			{
				
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(cc))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(cc))->Value);
				if( cc +1 == cols ) {
					pf->m_grid.SetRow(row);
					pf->m_grid.SetCol(cc+1);
					if( atof(strSql) != 0 ) pf->m_grid.SetCellBackColor(RGB(255,128,128));
				}
				pf->m_grid.SetTextMatrix(row,cc+1,strSql);
				if(cc>=cols-6)add[i++]+=atof(strSql);
			}
			row++;
			pf->m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();

		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}
	pf->m_grid.SetMergeCells(true);
	pf->m_grid.SetMergeRow(row,1);

	pf->m_grid.SetRow(row);
	pf->m_grid.SetCol(0);
	pf->m_grid.SetCellBackColor(RGB(255,0,0));
	strSql.Format("   共有 %ld 条药品记录 ",row-1);
	pf->m_grid.SetTextMatrix(row,0,"合计");	

	pf->GetDlgItem(IDC_BUTTON_TO_EXCEL)->SetWindowText(strSql+"         [ 导入 Excel ]");

	for(int count=1;count<cols;count++){
		pf->m_grid.SetTextMatrix(row,count,strSql);	
		pf->m_grid.SetCol(count);
		pf->m_grid.SetCellBackColor(RGB(255,128,0));

	}

	for(i=0;i<6;i++){
		strSql.Format("%.2f",add[i]);
		pf->m_grid.SetTextMatrix(row,cols-5+i,strSql);
	}

	pf->m_grid.SetRedraw(true);

	
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

	pd->SendMessage(WM_CLOSE,NULL,NULL);
	return true;
}
