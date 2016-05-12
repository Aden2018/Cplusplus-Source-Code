// OtherDechargeQuery.cpp: implementation of the COtherDechargeQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "OtherDechargeQuery.h"
#include "otherDecharge.h"
#include "dialogQueryAAA.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
// flagQuery用于查询时的标志使用,作为是否使用原来的SQL标志
//////////////////////////////////////////////////////////////////////

COtherDechargeQuery::COtherDechargeQuery()
{
	strQuery="";
	strQuery2="";
	flagQuery=0; 
}

COtherDechargeQuery::~COtherDechargeQuery()
{

}

BOOL COtherDechargeQuery::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect r1;
	const CString strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_Title_list WHERE ds2='DIALOG' AND ds3='TITLE' and \
		ds4='AAE' ");;
	const int moveLeft=40;
	GetDlgItem(IDC_STATIC_HEAD)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_HEAD)->SetWindowText(strTitle);
	SetWindowText(strTitle);
//	GetDlgItem(IDC_BUTTON_ADD)->ShowWindow(SW_HIDE);
//-------------------------------------------------------
	m_23.GetWindowRect(r1);
	ScreenToClient(r1);
	m_33.MoveWindow(r1);
	m_33.ShowWindow(SW_SHOW);
//--------------------------------------------------------
	
	c_combo1.ResetContent();
	GetDlgItem(IDC_STATIC_1)->SetWindowText("姓 名");
	GetDlgItem(IDC_STATIC_2)->SetWindowText("内 容");

//	GetDlgItem(IDC_STATIC_3)->SetWindowText("类 别");
//---------------------------------------------------
	GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_HIDE);
//--------------------------------------------------
	GetDlgItem(IDC_EDIT_NAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_2)->GetWindowRect(r1);
	ScreenToClient(r1);
	r1.left-=moveLeft;
	r1.right-=moveLeft;
	GetDlgItem(IDC_STATIC_2)->MoveWindow(r1);

	c_name.GetWindowRect(r1);
	ScreenToClient(r1);
	c_combo2.MoveWindow(r1.left-moveLeft,r1.top,(r1.right-r1.left)*2-60,r1.bottom-r1.top+400 );
	c_combo2.ShowWindow(SW_SHOW);


	GetDlgItem(IDC_STATIC_3)->GetWindowRect(r1);
	ScreenToClient(r1);
	r1.left-=moveLeft;
	r1.right-=moveLeft;
	GetDlgItem(IDC_STATIC_3)->MoveWindow(r1);

	
	c_combo1.GetWindowRect(r1);
	ScreenToClient(r1);
//	c_combo1.MoveWindow(r1.left-moveLeft,r1.top,(r1.right-r1.left)*2,r1.bottom-r1.top+400 );
//-----------------------------------------------------------------------------------------
	c_combo1.ShowWindow(SW_HIDE);
	m_23.MoveWindow(r1.left-moveLeft,r1.top-3,(r1.right-r1.left)*2,r1.bottom-r1.top );
	m_23.ShowWindow(SW_SHOW);
	m_23.SetWindowText("特殊查询操作");
//-----------------------------------------------------------------------------------------
	
	CString strSql;
	try{
//经济内容		
		strSql.Format("select ds3 from LSQ_Economy_Rank ORDER BY n1  ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		c_combo2.AddString(" ");
		while(!recSet->adoEOF){
		
			strSql=(char*)_bstr_t(recSet->GetCollect("ds3").vt==VT_NULL?" ":recSet->GetCollect("ds3"));
			c_combo2.AddString(strSql);
			
			recSet->MoveNext();
		}
		recSet->Close();
//就诊类别
		strSql.Format("select ds1,ds2 from LSQ_gh_type WHERE DS3='B' ORDER BY n1  ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		c_combo1.AddString(" ");
		while(!recSet->adoEOF){
		
			strSql=(char*)_bstr_t(recSet->GetCollect("ds2").vt==VT_NULL?" ":recSet->GetCollect("ds2"));
			c_combo1.AddString(strSql);
			strSql=(char*)_bstr_t(recSet->GetCollect("ds1").vt==VT_NULL?" ":recSet->GetCollect("ds1"));
			typeArray.Add(strSql);
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
	m_date1.SetDate(COleDateTime::GetCurrentTime().GetYear(),1,1);
	UpdateData(false);

	SetGridHead();
	return TRUE;  // return TRUE unless you set the focus to a control

}

void COtherDechargeQuery::OnButtonDeleteRow()
{
	CString strSql;
	strSql.Format("DELETE FROM lsq_other_decharge WHERE ds1='%s' ",m_grid.GetTextMatrix(preRow,1) );
	if( !COtherDecharge::WriteSQL(strSql) ){
		AfxMessageBox("删除失败!!");
		return;
	}
	m_grid.RemoveItem(preRow);

}

void COtherDechargeQuery::OnButtonAdd()  //费用报销特殊查询
{
	CDialogQueryAAA aa;
	if( aa.DoModal()== IDOK){
		strQuery=aa.strSql; //经济内容
		strQuery2=aa.strSql2; //报销类别
	}
	else
	{
		strQuery="";
		strQuery2="";
	}

}

void COtherDechargeQuery::OnOK()
{
	UpdateData();

	CString strSql,strTemp,strT1,strT2;
	long cc,row,cols,i;
	double add[]={0.,.0,.0,0,0,0,0,0,0,0,0};
	CONST int COMPUTE_COLS=6;
	m_grid.SetRedraw( false);
//{"序号","报销日期","使用人","报销内容","发票数","附件","总金额","比例","实报金额","操作员","验收人","经手人","审批人","类别","备注"}; 
/*	if( c_combo1.GetCurSel()==0 || c_combo1.GetCurSel() == CB_ERR) strT1="";
	else {
		strT1=typeArray.GetAt(c_combo1.GetCurSel()-1 ); //报销类别
	}
*/
	if( c_combo2.GetCurSel()==0 || c_combo2.GetCurSel() == CB_ERR) strT2="";
	else c_combo2.GetLBText(c_combo2.GetCurSel(),strT2); //经济内容
	
	SetGridHead();
	try{

		strSql.Format("select t.ds1,t.d1,t.ds4,t.ds2,t.n1,t.n2,t.n3,to_char(t.n4*100)||'%%',round(t.n3*t.n4,2), \
			t.ds8,ds5,ds6,ds7,b.ds2,t.ds3 from lsq_other_decharge t,lsq_gh_type b where t.ds9=b.ds1 and b.ds3='B' ");
	//	if( !strT1.IsEmpty() ) strSql+=" AND b.ds1='"+strT1+"'";
	//	if( !strT2.IsEmpty() ) strSql+=" AND t.ds2='"+strT2+"'";
//----------------------------------------------------------------------
		if( !strQuery2.IsEmpty() )strSql+=" AND b.ds2 "+strQuery2; //报销类别
		if( ! strQuery.IsEmpty() )strSql+=" AND t.ds2 "+strQuery;  //经济内容
		else if( !strT2.IsEmpty() ) strSql+=" AND t.ds2='"+strT2+"'";
		strQuery2="";
		strQuery="";
//----------------------------------------------------------------------

		m_bm.GetWindowText(strTemp);
		if( !strTemp.IsEmpty() ) strSql+=" AND t.ds4 like '"+strTemp+"%'";
	
		strTemp.Format(" AND t.d1 BETWEEN to_date(%s,'yyyymmdd') AND to_date(%s,'yyyymmdd') ORDER BY t.d1,t.ds4 ",m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d") );
		strSql+=strTemp;

		if( flagQuery == 2){ //判断是否为 医院成本查询 
			strSql=flagQueryStr;
		}
		flagQuery=0;

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		cols=recSet->GetFields()->Count;
		row=1;

		while(!recSet->adoEOF){
			i=0;
			strSql.Format("%ld",row);
			m_grid.SetTextMatrix(row,0,strSql);
			m_grid.SetMergeRow(row,false);
			for(cc=0;cc<cols;cc++)
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(cc))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(cc))->Value);
				if( cc ==6 || cc == 8){
					strTemp=strSql;
					strSql.Format("%.2f",atof(strTemp) );
					add[cc]+=atof(strTemp);
				}
				m_grid.SetTextMatrix(row,cc+1,strSql);
				
			}
			row++;
			m_grid.AddItem("",_variant_t(row));
			recSet->MoveNext();

		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return;
	}
	
	

	m_grid.SetRow(row);
	m_grid.SetCol(0);
	m_grid.SetMergeCells(true);
	m_grid.SetMergeRow(row,1); 
	m_grid.SetCellBackColor(RGB(255,0,0));
	strSql.Format("   共有 %ld 条记录 ",row-1);
	m_grid.SetTextMatrix(row,0,"合计");	


	for(int count=1;count<cols;count++){
		m_grid.SetTextMatrix(row,count,strSql);	
		m_grid.SetCol(count);
		m_grid.SetCellBackColor(RGB(255,128,0));

	}
	strSql.Format("%.2f",add[6]);
	m_grid.SetTextMatrix(row,7,strSql);
	strSql.Format("%.2f",add[8]);
	m_grid.SetTextMatrix(row,8,"");
	m_grid.SetTextMatrix(row,9,strSql);
	
	m_grid.SetRedraw(true);
}

void COtherDechargeQuery::SetGridHead()
{
	CString HeadTitle[]={"序号","series","报销日期","使用人","报销内容","发票数","附件","总金额","比例","实报金额","操作员","验收人","经手人","审批人","类别","备注"}; 
	
	long  headWidth[]={600,0,1000,800,1800,600,600,1000,600,1000,700,700,700,700,3000,8000,500,600,1000,600,1000,\
		1000,1000,1000,11400,1400,1400,1400};
	long numCols[]={4,5,6,7,8},x;
	
	m_grid.SetRows(2);
	m_grid.Clear();

	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(4);
	long  i=0,col(0),row(0);
	m_grid.SetRow(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<4){
			m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		}
	//	for(x=0 ; x < sizeof(numCols)/sizeof(long) ; x++)
	//		if( count == numCols[x] )break;
		if( count >10 )
			m_grid.SetColAlignment((long)count,short(1));
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
	
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}

}

void COtherDechargeQuery::OnButtonCostQuery()
{
     UpdateData();
	 CString strTemp;
	 flagQuery=2;
	

	 flagQueryStr.Format("select t.ds1,t.d1,t.ds4,t.ds2,t.n1,t.n2,t.n3,to_char(t.n4*100)||'%%',round(t.n3*t.n4,2), \
			 t.ds8,t.ds5,t.ds6,t.ds7,b.ds2,t.ds3 from lsq_other_decharge t,lsq_gh_type b,lsq_title_list c where t.ds9=b.ds1 \
			 and b.ds3='B' AND c.ds1=t.ds9 AND c.ds2='QUERY' AND c.ds3='SORT' and c.ds4='AAA' ");
														 
	 m_bm.GetWindowText(strTemp);
	 if( !strTemp.IsEmpty() ) flagQueryStr+=" AND t.ds4 like '"+strTemp+"%'";
														 
	 strTemp.Format(" AND t.d1 BETWEEN to_date(%s,'yyyymmdd') AND to_date(%s,'yyyymmdd') ",m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d") );
	 flagQueryStr+=strTemp;
	 flagQueryStr+=" ORDER BY t.d1,t.ds2 ";
	 OnOK();
														 
}
