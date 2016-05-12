// PeculiarInput.cpp: implementation of the CPeculiarInput class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "PeculiarInput.h"
#include "progressIndicate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPeculiarInput::CPeculiarInput()
{
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_upgrade WHERE ds2='PECULIAR' ");
	
}

CPeculiarInput::~CPeculiarInput()
{

}

BOOL CPeculiarInput::OnInitDialog()
{
	CWageInput::OnInitDialog();
	m_b4.ShowWindow(SW_HIDE); //工资文件
	m_s4.ShowWindow(SW_HIDE);
	c2.ShowWindow(SW_HIDE);	

	CString px[]={"部门名称","卡号","姓名","性别","年龄","补助性质","补助金额","帐号余额","充值总额"};
	long pl[]={1200,1100,1000,400,400,2200,1000,1000,1000};
	SetGridHead(px,pl,m_grid,sizeof(px)/sizeof(CString),5,5);
	return true;
}

void CPeculiarInput::OnB3() //实际充值
{
	UpdateData();
	COleDateTime dt1;
	d1.GetTime(dt1);
	CString strSql,strTmp;
	strSql.Format("请确认要对当前特殊人员进行%d年度充值吗？？",dt1.GetYear() );
	if( AfxMessageBox(strSql,MB_OKCANCEL) == IDCANCEL )return;

	try{
		strTmp.Format(" SELECT count(*) FROM LSQ_EMP_HeadSHip_charge WHERE n2=%d ",dt1.GetYear() );
		recSet->Open(_bstr_t(strTmp),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		strTmp=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value);
		recSet->Close();
		if( atol(strTmp) != 0 ){
			AfxMessageBox("本年特殊人员已经结算过...");
			return;
		}
		HospitalConnect->BeginTrans();
		//卡号,补助性质,代码,操作人信息,金额,年度,原帐号余额,操作时间
		strTmp.Format("INSERT INTO lsq_emp_headship_charge (ds1,ds2,ds3,ds4,n1,n2,n3,d1) \
			SELECT  t.ds1,a.ds1,t.ds2,(select sys_context( 'userenv','ip_address') \
			FRom dual)||'_%s' ,a.n3,%d,结存金额,sysdate FROM lsq_emp_headship t,lsq_upgrade a,\
			职工基本情况表 b WHERE t.ds2=a.ds3 and a.ds2='ESUB' AND b.卡号=t.ds1 and b.类别!='消户' ",LoginInformation.user,dt1.GetYear() );
		HospitalConnect->Execute(_bstr_t(strTmp),NULL,adCmdText);
	
		strTmp.Format("UPDATE 职工基本情况表 a SET 结存金额=结存金额+ \
		    (SELECT NVL(sum(a.n3),0) FROM lsq_emp_headship t,lsq_upgrade a \
				WHERE t.ds2=a.ds3 and a.ds2='ESUB' and a.卡号=t.ds1 group by t.ds1) \
			WHERE a.卡号 in (select distinct ds1 from lsq_emp_headship) ");
		HospitalConnect->Execute(_bstr_t(strTmp),NULL,adCmdText);
		
		HospitalConnect->CommitTrans();


	}
	catch(_com_error e)
	{
		AfxMessageBox("结算失败,请联系程序设计人员...");
		AfxMessageBox(strTmp);
		HospitalConnect->RollbackTrans();
		return;
	}
	strTmp.Format("%d年度特殊人员结算完成!!!",dt1.GetYear());
	AfxMessageBox(strTmp);



}

void CPeculiarInput::OnB1()//模拟
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryData;
	pg.DoModal();

}





void CPeculiarInput::SetGridHead(CString ps[], long pl[], CMSHFlexGrid &pg,
								 long len, long fixLen,long merge)
///////////////////////////////////////////////////////////////////////////
//		设定表格标题头
//
//		ps[] 标题数组
//		pl[] 标题列宽度数组
//		&pg  表格引用
//		len  标题长度(多少列)
//		fixlen 固定宽度
//		merge 需要合并的列数(从前开始向后数)
//////////////////////////////////////////////////////////////////////////
{

	pg.Clear();
	pg.SetRows(2);
	pg.SetCols(len);
	pg.SetFixedCols(fixLen);
	pg.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	

	pg.SetMergeCells(2); //设定单元格可以进行合并
	pg.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count< len;count++){
		if( count < merge ){
			pg.SetMergeCol(count,true);// 前 Merge 列单元格进行合
			pg.SetColAlignmentFixed(count,4);
		}
		else 
			pg.SetColAlignment(count,9); //用默认方式显示列内容,即数字靠右,字符串靠左

		pg.SetCol((long) count);
		pg.SetCellAlignment((short)4); //居中对齐
		pg.SetColWidth(i,pl[count]);
		pg.SetTextArray(i++,ps[count]);

		
	}

}

UINT CPeculiarInput::QueryData(LPVOID ps)
{
	CPeculiarInput * pd=(CPeculiarInput * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);

	CString px[]={"部门名称","卡号","姓名","性别","年龄","补助性质","补助金额","帐号余额","充值总额"};
	long pl[]={1200,1100,1000,400,400,2200,1000,1000,1000};
	CPeculiarInput::SetGridHead(px,pl,pd->m_grid,sizeof(px)/sizeof(CString),5,sizeof(px)/sizeof(CString));

	COleDateTime dt1;
	pd->d1.GetTime(dt1);

	CString strSql,str1;
	long cols,row,i,col;
	double add[20];
	const int START_COMPUTE=6; //在SQL语句中
	for( i=0 ; i< 20 ;i++)add[i]=0.0;

	try{
		strSql.Format("	select 部门名称,卡号,姓名,性别,%d-to_char(出生日期,'yyyy'),\
			B.DS1,B.N3,结存金额,(select sum(y.n3) FROm lsq_emp_headship x,lsq_upgrade y \
			where  x.ds2=y.ds3 and y.ds2='ESUB' and x.ds1=a.卡号 group by x.ds1 )+结存金额 from \
			lsq_emp_headship t,职工基本情况表 a ,Lsq_Upgrade B,厂部门表 c wHERE \
			T.DS1=A.卡号 AND T.DS2=B.DS3 and B.DS2='ESUB' and c.部门编码=a.部门编码 and a.类别 !='消户' order by 卡号 ",dt1.GetYear() );

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		row=1;
		double dX;
		while(!recSet->adoEOF){
			col=0;
		//	str1.Format("%ld",row);
		//	pd->m_grid.SetTextMatrix(row,col++,str1);
	/*		pd->m_grid.SetRow(row);
			pd->m_grid.SetCol(6);
			pd->m_grid.SetCellBackColor(BK1);
			pd->m_grid.SetCol(9);
			pd->m_grid.SetCellBackColor(BK2);
	*/		pd->m_grid.SetMergeRow(row,false);
			for(i=0;i<cols;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				pd->m_grid.SetTextMatrix(row,col++,str1);
				
				if( i==START_COMPUTE )add[i-START_COMPUTE]+=atof(str1); 
			}
			row++;
			pd->m_grid.AddItem("",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();

//		str1.Format("总计: 需采购 %ld 条药品",row-1 );
//		pd->GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(str1);
		pd->m_grid.SetMergeCells(2);
		pd->m_grid.SetMergeRow(row,1); 
		pd->m_grid.SetRow(row);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("共有%ld 条",row-1);
		pd->m_grid.SetTextMatrix(row,0,"合计");	
		
		
		for(int count=1;count<cols;count++){
			pd->m_grid.SetTextMatrix(row,count,strSql);	
			pd->m_grid.SetCol(count);
			pd->m_grid.SetCellBackColor(RGB(255,128,0));
			
		}
		
/*		for(i=START_COMPUTE;i<cols;i++){
			strSql.Format("%.2f",add[i-START_COMPUTE]);
			pd->m_grid.SetTextMatrix(row,i+1,strSql);
		}
*/
		strSql.Format("%.2f",add[0]);
		pd->m_grid.SetTextMatrix(row,START_COMPUTE,strSql);

		pd->m_grid.SetRedraw(true);
		
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
	
		return false;
	}	

	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
	return true;
}

void CPeculiarInput::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryData2;
	pg.DoModal();

}

UINT CPeculiarInput::QueryData2(LPVOID ps)
{
	CPeculiarInput * pd=(CPeculiarInput * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);

	CString px[]={"日期","操作员","部门名称","卡号","姓名","性别","年龄","补助性质","上期余额","补助金额","结算总额","帐户余额"};
	long pl[]={1100,1600,1200,1100,1000,400,400,2200,1000,1000,1000,1000};
	CPeculiarInput::SetGridHead(px,pl,pd->m_grid,sizeof(px)/sizeof(CString),5,sizeof(px)/sizeof(CString));

	COleDateTime dt1;
	pd->d1.GetTime(dt1);

	CString strSql,str1;
	long cols,row,i,col;
	double add[20];
	const int START_COMPUTE=9; //在SQL语句中
	for( i=0 ; i< 20 ;i++)add[i]=0.0;

	try{
		strSql.Format("select trunc(b.d1,'dd'),b.ds4,部门名称,b.ds1,a.姓名,性别,2005-to_char(出生日期,'yyyy') ag,\
			b.ds2,b.n3,b.n1,b.n3+(select NVL(sum(n1),0) from lsq_emp_headship_charge where ds1=a.卡号 AND n2=%d group by ds1 ),\
			结存金额 from 职工基本情况表 a, lsq_emp_headship_charge b,\
			厂部门表 c where a.卡号=b.ds1 and  a.部门编码=c.部门编码 and b.n2=%d order by ds1 ",dt1.GetYear(),dt1.GetYear() );

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		row=1;
		double dX;
		while(!recSet->adoEOF){
			col=0;
		//	str1.Format("%ld",row);
		//	pd->m_grid.SetTextMatrix(row,col++,str1);
	/*		pd->m_grid.SetRow(row);
			pd->m_grid.SetCol(6);
			pd->m_grid.SetCellBackColor(BK1);
			pd->m_grid.SetCol(9);
			pd->m_grid.SetCellBackColor(BK2);
	*/		pd->m_grid.SetMergeRow(row,false); 
			for(i=0;i<cols;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				pd->m_grid.SetTextMatrix(row,col++,str1);
				
				if( i==START_COMPUTE )add[i-START_COMPUTE]+=atof(str1); 
			}
			row++;
			pd->m_grid.AddItem("",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();

		pd->m_grid.SetMergeCells(2);
		pd->m_grid.SetMergeRow(row,1); 
		pd->m_grid.SetRow(row);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("共有%ld 条",row-1);
		pd->m_grid.SetTextMatrix(row,0,"合计");	
		
		
		for(int count=1;count<cols;count++){
			pd->m_grid.SetTextMatrix(row,count,strSql);	
			pd->m_grid.SetCol(count);
			pd->m_grid.SetCellBackColor(RGB(255,128,0));
			
		}
		
	/*	for(i=START_COMPUTE;i<cols;i++){
			strSql.Format("%.2f",add[i-START_COMPUTE]);
			pd->m_grid.SetTextMatrix(row,i+1,strSql);
		}
*/		strSql.Format("%.2f",add[0]);
		pd->m_grid.SetTextMatrix(row,START_COMPUTE,strSql);

		pd->m_grid.SetRedraw(true);
		
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
	
		return false;
	}	

	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
	return true;
}
