// EverydayConsumeQuery.cpp: implementation of the CEverydayConsumeQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "EverydayConsumeQuery.h"
#include "EverydayConsumeList.h"
#include "ProgressIndicate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEverydayConsumeQuery::CEverydayConsumeQuery()
{

}

CEverydayConsumeQuery::~CEverydayConsumeQuery()
{

}

BOOL CEverydayConsumeQuery::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText("药品消耗查询");
	c_gys.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_GYS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_3)->SetWindowText("库  房");
	c_combo1.ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATIC_2)->SetWindowText("药品编码");
	CRect rt1,rt2;
	GetDlgItem(IDC_EDIT_GYS)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	GetDlgItem(IDC_COMBO2)->GetWindowRect(rt2);
	ScreenToClient(rt2);
	GetDlgItem(IDC_EDIT_YPBM)->MoveWindow(rt1.left,rt1.top,rt2.right-rt2.left,rt2.bottom-rt2.top);
	GetDlgItem(IDC_EDIT_YPBM)->ShowWindow(SW_SHOW);

	CString strSql;
	try{
		strSql.Format("select kfmc from storeroom where med='1' "); //有药品的库房
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		c_combo1.AddString("");
//		c_combo2.AddString("");
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetCollect("kfmc").vt==VT_NULL?" ":recSet->GetCollect("kfmc"));
			c_combo1.AddString(strSql);
//			c_combo2.AddString(strSql);
			recSet->MoveNext();

		
		}
		recSet->Close();
		


	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}
	return true;
}

void CEverydayConsumeQuery::OnOK()
{

//	ShowWindow(SW_HIDE);

	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryConsume;
	pg.DoModal();

}
/***日消耗药品查询***/
UINT CEverydayConsumeQuery::QueryConsume(LPVOID ps)
{
	CEverydayConsumeList * pf=(CEverydayConsumeList *)theApp.pParentGrid.pWnd;
	CEverydayConsumeQuery * pd=(CEverydayConsumeQuery * )((CProgressIndicate *)ps)->pDialog;

	pf->m_grid.SetRedraw( false);
	pf->SetGridHead();
	pd->UpdateData();
	CString strSql,strTemp;
	long cc,row,cols,i;
	double add[8]={0.,.0,.0,0,0,0,0,0};
	
	try{
//	HeadTitle[]={"编号","药品编码","药品名称","规格","单位","消耗量","库存量"}; 
		if(!(pd->c_combo1.GetCurSel() == CB_ERR || pd->c_combo1.GetCurSel()== 0) ){
	
		strSql.Format("SELECT bm,mc,gg,dw,s1,s2 from (select a.ypbm ypbm,s1,s2 FROM (SELECT ypbm,sum(sl) s1 FROM \
				itemti where riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd') \
				AND substr(danjuhao,1,1) in( 'G','E','B')  GROUP BY ypbm ) a ,(SELECT ypbm,sum(sl) s2 FROM \
				medlie GROUP BY YPBM ) b  WHERE a.ypbm=b.ypbm(+) ) x ,medcode c WHERE x.ypbm=c.bm ", \
				pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d")/*,pd->strCombo1Kfbm,pd->strCombo1Kfbm*/ );

		
		}
		else {


			CString st1,st2,st3,st4,stx;
			st1.Format(" ( SELECT a.ypbm ypbm,s1,s2 FROM \
							(SELECT ypbm,sum(sl) s1 FROM itemti WHERE riqi BETWEEN to_date('%s','yyyymmdd') AND \
								to_date('%s','yyyymmdd') AND substr(danjuhao,1,1) in ('G','E','B') GROUP BY ypbm ) a,\
							(SELECT ypbm,sum(sl) s2 FROM medlie GROUP BY ypbm ) b \
					WHERE a.ypbm=b.ypbm(+) ) x ",pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d") ); //消耗与库存表
			
			st2.Format(" ( SELECT ypbm,");
			for( i=0 ; i < pf->strBm.GetSize() ; i++ ){
				if( pf->strBm.GetSize() == i+1 )stx.Format(" SUM( DECODE(kfbm,'%s',sl,0) ) S%d ",pf->strBm.GetAt(i),i+3);
				else	stx.Format(" SUM( DECODE(kfbm,'%s',sl,0) ) S%d,",pf->strBm.GetAt(i),i+3);
				st2+=stx;
			}
			st2+=" FROM medlie GROUP BY ypbm ) y "; //各库房库存明细

			st3="(SELECT x.ypbm ypbm,s1,s2," ;
			for( i=0 ;i <pf->strBm.GetSize() ; i++ ){
				st4.Format("S%d",i+3);
				if( i+1 == pf->strBm.GetSize() )st3+=st4;
				else st3+=st4+",";

			}
			st3+=" FROM "+st1+","+st2+" WHERE x.ypbm=y.ypbm(+) ) Z" ;

			st4.Format(" SELECT bm,mc,gg,dw,s1,s2,");
			for( i=0 ;i <pf->strBm.GetSize() ; i++ ){
				st1.Format("S%d",i+3);
				if( i+1 == pf->strBm.GetSize() )st4+=st1;
				else st4+=st1+",";

			}
			st4+=" FROM "+st3+","+"medcode c WHERE Z.ypbm=c.bm ";
			
			strSql=st4;
		
		}
		
//		AfxMessageBox(strSql);
		pd->c_py.GetWindowText(strTemp);
//		strTemp.Remove(' ');
		if(! strTemp.IsEmpty() ) strSql+=" AND C.PY like '"+strTemp+"%'";

		pd->c_editYpbm.GetWindowText(strTemp);
//		strTemp.Remove(' ');
		if(! strTemp.IsEmpty() ) strSql+=" AND C.bm like '"+strTemp+"%'";
		strSql+=" ORDER BY dlbm,xlbm,MC ";		

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		cols=recSet->GetFields()->Count;
	
		while(!recSet->adoEOF){
			i=0;
			strSql.Format("%ld",row);
			pf->m_grid.SetTextMatrix(row,0,strSql);
			pf->m_grid.SetRow(row);
			pf->m_grid.SetCol(7);
			pf->m_grid.SetCellBackColor(RGB(0,128,0));
			for(cc=0;cc<cols;cc++)
			{
				
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(cc))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(cc))->Value);
				pf->m_grid.SetTextMatrix(row,cc+1,strSql);
				if(cc>=cols-5)add[i++]+=atof(strSql);
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

	for(i=0;i<5;i++){
		strSql.Format("%.2f",add[i]);
		pf->m_grid.SetTextMatrix(row,cols-4+i,strSql);
	}

	pf->m_grid.SetRedraw(true);

	
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

	pd->SendMessage(WM_CLOSE,NULL,NULL);

}
