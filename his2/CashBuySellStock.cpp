// CashBuySellStock.cpp: implementation of the CCashBuySellStock class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "CashBuySellStock.h"
#include "PeculiarInput.h"
#include "ProgressIndicate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCashBuySellStock::CCashBuySellStock()
{
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_Title_list WHERE ds2='DIALOG' AND ds3='TITLE' and ds4='AAI' ");

}

CCashBuySellStock::~CCashBuySellStock()
{

}

BOOL CCashBuySellStock::OnInitDialog()
{
	CAccrualAdd::OnInitDialog();

	GetDlgItem(IDC_STATIC1)->SetWindowText("编码/名称");
	GetDlgItem(IDC_STATIC2)->SetWindowText("拼音");
	GetDlgItem(IDC_STATIC_1)->SetWindowText("查询月度");
	GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_2)->SetWindowText("显示方式");
	GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_BUTTON_PRINT)->ShowWindow(SW_HIDE);

	CRect rt1;
	pc->GetWindowRect(rt1);
	ScreenToClient(rt1);
	GetDlgItem(IDC_DATETIMEPICKER1)->MoveWindow(rt1);
	GetDlgItem(IDC_DATETIMEPICKER1)->ShowWindow(SW_SHOW);
	pc->ShowWindow(SW_HIDE);

	((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();

	CDialogMedXL::ReadName("SELECT ds1　FROM lsq_upgrade WHERE ds2='SELECTVIEW' order by n1",*((CComboBox*)GetDlgItem(IDC_COMBO2)) );
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);

	CDialogMedXL::ReadName("SELECT ds3　FROM lsq_upgrade WHERE ds2='SELECTVIEW' ORDER BY n1 ",*((CComboBox*)GetDlgItem(IDC_COMBO1)));
	
	
	CString HeadTitle[]={"序号","药品编码","名称","规格","单位","购进","零售","购进","零售","购进","零售","购进","零售","购进","零售","购进","零售","购进","零售"} ;//共 7 列
	//															 ----------    ------------   ----------   -----------    -----------  ------------ --------------
	//															上期结存         购进           销售          盘点           其它用      报损         结存
	//										
	long  headWidth[]={800,1000,1100,1000,900,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,0,1300,1300,1300,00,00,1400};
	//                                        -------
	CPeculiarInput::SetGridHead(HeadTitle,headWidth,m_grid,sizeof(HeadTitle)/sizeof(CString),5,0);
	return true;
}

void CCashBuySellStock::OnSelchangeCombo2()
{
	CString selStr="";

	int i=0;
	long  headWidth[]={800,1000,1100,1000,500,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,0,1300,1300,1300,00,00,1400};
	//									3	4	5	
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel(),selStr);
	if( selStr == "ALL" )
	{
		for(i=0; i< 7; i++ )
		{
			m_grid.SetColWidth(i*2+5,headWidth[i*2+5]);
			m_grid.SetColWidth(i*2+6,headWidth[i*2+6]);
		}

	}
	else if( selStr== "BUY")
	{
		for(i=0; i< 7; i++ ){
			m_grid.SetColWidth(i*2+5,headWidth[i*2+5]);
			m_grid.SetColWidth(i*2+6,0);
		}
	}
	else if( selStr == "SELL" )
	{
		for(i=0; i< 7; i++ ){
			
			m_grid.SetColWidth(i*2+6,headWidth[i*2+6]);
			m_grid.SetColWidth(i*2+5,0);
		}
	}
	else
	{
	}



}

void CCashBuySellStock::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryDatax;
	pg.DoModal();

}

UINT CCashBuySellStock::QueryDatax(LPVOID ps)
{
	CCashBuySellStock * pd=(CCashBuySellStock *)((CProgressIndicate *)ps)->pDialog;
	pd->UpdateData();
	pd->m_grid.SetRedraw(false);

	CString HeadTitle[]={"序号","药品编码","名称","规格","单位","结存(进)","结存(零)","购进(进)","购进(零)","销售(进)","销售(零)","盘点(进)","盘点(零)","内部(进)","内部(零)","报损(进)","报损(零)","结存(进)","结存(零)"} ;//共 7 列
	//															 ----------              ------------   ----------       -----------    -----------  ------------ --------------
	//															上期结存                    购进               销售          盘点           其它用      报损         结存
	//										
	long  headWidth[]={800,1000,1100,1000,500,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,0,1300,1300,1300,00,00,1400};
	//                                        -------
	CPeculiarInput::SetGridHead(HeadTitle,headWidth,pd->m_grid,sizeof(HeadTitle)/sizeof(CString),5,0);
	pd->m_grid.SetMergeCol(0,false);
	pd->m_grid.SetMergeCol(1,false);

	CString strSql,str1,str2,str3,strPar,strx1,strx2;
	long cols,row,i,col;
	double add[14]={0,0,0,0,0,0,0,0,0};
	for(i=0; i<14; i++ ) add[i]=0.0;

	const int START_COMPUTE=4; //在SQL语句中
	CComboBox *pc=pd->pc,*pc2=(CComboBox*)pd->GetDlgItem(IDC_COMBO2);
	try{
		strSql.Format(" SELECT to_char(SYSDATE,'yyyymm') FROM DUAL ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
	
		strx1=(char*)_bstr_t(recSet->GetFields()->GetItem(0l)->Value);
		recSet->Close();
		strx2=pd->m_date1.Format("%Y%m");
		if ( atol(strx2) > atol(strx1) ) goto END;  //日期取值过大
	
		pd->c_edit1.GetWindowText(str1);  // 编码或者名称
		pd->c_edit3.GetWindowText(str2);  // 拼音
	//	select bm,mc,gg,dw,st,st1 from medcode a

		if( !str1.IsEmpty() ) {

			if( str1.Left(1) >= '0' && str1.Left(1)<='9' )strPar=" AND BM like '"+str1+"%'";
			else strPar=" AND MC like '"+str1+"%'";

		}
		if( !str2.IsEmpty() ) {

			strPar+=" AND py LIKE '"+str2+"%'";

		}


		str1.Format(" select bm,mc,gg,dw,st,st1,mo,mo1,mo2,mo3,mo4,mo5,mo6,mo7,mo8,mo9 from \
			(select bm,mc,gg,dw,st,st1 from medcode a, \
			(select ypbm,sum(jinjia*sl) st,sum(sl*dj) st1 from 期初库存 where nian=%d and yue=%d \
																             and sl!=0 group by ypbm ) b \
			      where a.bm=b.ypbm(+) %s ) a1,\
       (select ypbm,  sum(decode(substr(danjuhao,1,1),'A',dj*sl,0)) mo,\
                      sum(decode(substr(danjuhao,1,1),'A',selldj*sl,0)) mo1 ,\
                         \
                      sum(decode(substr(danjuhao,1,1),'G',pdj*sl,0)) mo2,\
                      sum(decode(substr(danjuhao,1,1),'G',dj*sl,0)) mo3,\
                       \
                      sum(decode(substr(danjuhao,1,1),'P',selldj*sl,0)) mo4,\
                      sum(decode(substr(danjuhao,1,1),'P',dj*sl,0)) mo5,\
                       \
                      sum(decode(substr(danjuhao,1,1),'E',selldj*sl,0)) mo6,\
                      sum(decode(substr(danjuhao,1,1),'E',dj*sl,0)) mo7,\
                         \
                      sum(decode(substr(danjuhao,1,1),'B',selldj*sl,0)) mo8,\
                      sum(decode(substr(danjuhao,1,1),'B',dj*sl,0)) mo9\
                               \
       from itemti a where  riqi between TRUNC(to_date(%s,'yyyymmdd'),'mm') \
       and  Last_day(to_date(%s,'yyyymmdd')) group by ypbm ) a2 \
	where a1.bm=a2.ypbm(+)	",pd->m_date1.GetYear(),pd->m_date1.GetMonth(),strPar,pd->m_date1.Format("%Y%m%d"),\
			pd->m_date1.Format("%Y%m%d"));


		if ( atol(strx2) == atol( strx1 ) ){
			
			str3.Format("select ypbm,sum(sl*jinjia) stock1,sum(sl*sell_price) stock2  \
				from medlie where sl!=0  group by ypbm	");



		}
		else //作为库存用
		{

			str3.Format("select ypbm, sum(jinjia*sl) stock1,sum(sl*dj) stock2 from 期初库存 where nian=%d and yue=%d \
				and sl!=0 group by ypbm " ,pd->m_date1.GetYear()+(pd->m_date1.GetMonth()%12==0?1:0),\
				pd->m_date1.GetMonth()%12==0?0:pd->m_date1.GetMonth()%12+1 );


		}
		strSql.Format(" SELECT  bm,mc,gg,dw,st,st1,mo,mo1,mo2,mo3,mo4,mo5,mo6,mo7,mo8,mo9,stock1,stock2 from \
			( %s ) z1,( %s ) z2 WHERE z1.bm=z2.ypbm(+) ",str1,str3 );

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		row=1;
		cols=recSet->GetFields()->Count;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			str1.Format("%ld",row);
			pd->m_grid.SetTextMatrix(row,col++,str1);

			pd->m_grid.SetMergeRow(row,false);
			for(i=0;i<cols;i++)
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
		strSql.Format("   共有 %ld 条记录 ",row-1);
		pd->m_grid.SetTextMatrix(row,0,"合计");	
		pd->GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(strSql);
		
		for(int count=1;count<cols+1;count++){
			pd->m_grid.SetTextMatrix(row,count,strSql);	
			pd->m_grid.SetCol(count);
			pd->m_grid.SetCellBackColor(RGB(255,128,0));
			
		}
	
		for(i=START_COMPUTE+1;i< cols+1;i++){
		
			strSql.Format("%.2f",add[i-START_COMPUTE-1]);
			pd->m_grid.SetTextMatrix(row,i,strSql);
		}

		pd->m_grid.SetRedraw(true);
		
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		((CProgressIndicate *)ps)->ConnectFlag =1;
		((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
		
		return false;
	}	
END:
	pd->m_grid.SetRedraw(true);
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
}
