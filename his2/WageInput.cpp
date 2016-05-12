// WageInput.cpp: implementation of the CWageInput class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "WageInput.h"
#include "excel9.h"
#include "progressEx.h"
#include "ProgressIndicate.h"
#include "progress.h"
#include "peculiarInput.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWageInput::CWageInput() //充值汇总
{
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_upgrade WHERE ds2='SALARY' ");

}

CWageInput::~CWageInput()
{

}

BOOL CWageInput::OnInitDialog()
{
	CBaseAddCash::OnInitDialog();

	CRect rt;
	m_sx1.ShowWindow(SW_SHOW);
	m_sx1.SetWindowText("部门");
	m_sx2.ShowWindow(SW_SHOW);
	m_sx2.SetWindowText("工号");
	m_sx3.ShowWindow(SW_SHOW);
	m_sx3.SetWindowText("姓名");
	m_sx4.ShowWindow(SW_SHOW);
	m_sx4.SetWindowText("查询/导入年度");

	m_xe1.GetWindowRect(rt);
	ScreenToClient(rt);
	rt.bottom+=200;
	rt.right+=40;
	c1.MoveWindow(rt);
	c1.ShowWindow(SW_SHOW);
	

	m_xe2.GetWindowRect(rt);
	ScreenToClient(rt);
	e2.MoveWindow(rt);
	e2.ShowWindow(SW_SHOW);

	m_xe3.GetWindowRect(rt);
	ScreenToClient(rt);
	e3.MoveWindow(rt);
	e3.ShowWindow(SW_SHOW);

	m_xe4.GetWindowRect(rt);
	ScreenToClient(rt);
	d1.MoveWindow(rt);
	d1.ShowWindow(SW_SHOW);
	
	CDialogMedXL::ReadName("SELECT NVL(部门名称,' ')　FROM 厂部门表 ORDER BY 部门名称 ",c1);
	c1.AddString("");

	m_s4.SetWindowText("性质");
	m_s4.ShowWindow(SW_SHOW);
	
	m_e4.GetWindowRect(rt);
	ScreenToClient(rt);
	rt.bottom+=200;
	rt.right+=40;
	c2.MoveWindow(rt);
	c2.ShowWindow(SW_SHOW);

	CDialogMedXL::ReadName("SELECT distinct(工作性质)　FROM 职工基本情况表 WHERE 类别='参保' order by 工作性质 ",c2);
	c2.AddString("");

	SetGridHead();
	return true;
}

extern COleVariant vOpt;
#define _O(x) COleVariant(x)
#define   IDC_PROGRESS_EXCEL WM_USER+1211

void CWageInput::OnB2() //查找导入的文件
{
	CString strFile,filter;
	filter="Excel文件 (*.xls)|*.xls||";
	CFileDialog fixls(true,"xls","",0,filter);
	if(fixls.DoModal()==IDCANCEL)return;
	
	strFile=fixls.GetPathName();
	GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(strFile);
	GetDlgItem(IDC_STATIC_NOTIFY)->ShowWindow(SW_SHOW);

	CString strSql;
	COleDateTime dt1;
	d1.GetTime(dt1);
	strSql.Format("请确认下面所列文件及年度正确！！(%s,%d年) ",strFile,dt1.GetYear() );
	if( AfxMessageBox(strSql,MB_OKCANCEL) == IDCANCEL ) {
		GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText("");
		GetDlgItem(IDC_STATIC_NOTIFY)->ShowWindow(SW_HIDE);
		
		return;
	}
//检查年度是否已经导入,没有则导入,有则退出
	Range vr;
	long y(1);
	CString strTemp;
	double dbWage(0),db1;
	try{
		strSql.Format("SELECT count(*) FROM lsq_emp_wage WHERE to_char(d1,'yyyy')='%d' ",dt1.GetYear() );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(0l)->Value);
		recSet->Close();
		if( atol(strSql) > 0 ){
			strSql.Format("%d年度补助数据已经存在！！！禁止导入！！！",iYear );
			AfxMessageBox(strSql);
//			GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText("");
//			GetDlgItem(IDC_STATIC_NOTIFY)->ShowWindow(SW_HIDE);
			return;
		}
//////////////////////////////////////////////////////////////
	BeginWaitCursor();
	CProgressEx pp;
	CRect r1(0,0,400,25);
	pp.Create(WS_CHILD |PBS_SMOOTH|WS_BORDER ,r1,this,IDC_PROGRESS_EXCEL);
	pp.UpdateWindow();
	pp.ShowWindow(SW_SHOW);
	pp.CenterWindow();
	pp.Invalidate();
	pp.strView="正在准备导入...请稍等！！";

	_Application app2 ;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;

	app2.CreateDispatch("excel.application");
	if(!app2){
		AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
		return;
	}
	books2=app2.GetWorkbooks();
	book2=books2.Open(strFile,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	sheets2=book2.GetWorksheets();
	
	sheet2=sheets2.GetItem(COleVariant((short)1)); //sheet1 作为工资表
	app2.SetVisible(false);


	HospitalConnect->BeginTrans();
	while(true){
	
		filter.Format("A%d",y);
		vr=sheet2.GetRange(_O(filter),_O(filter));
		strTemp=(char*)_bstr_t( vr.GetValue() );
		if( strTemp.IsEmpty() ) {
			break;
		}
	
		filter.Format("B%d",y);
		vr=sheet2.GetRange(_O(filter),_O(filter));
		db1=atof((char*)_bstr_t(vr.GetValue()) );

	
		strSql.Format(" INSERT INTO lsq_emp_other_price(ds1,n1,n2) VALUES('%s',%.2f,%d )  ",strTemp,db1,iYear );
	
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		dbWage+=db1;
		++y;
		pp.strView.Format("已经导入%ld名职工工资",y-1);
		pp.SetPos( (y-1)%100 );
		
	}


	HospitalConnect->CommitTrans();
	EndWaitCursor();	


//////////////////////////////////////////////


	pp.DestroyWindow();
	sheet2.ReleaseDispatch();
	sheets2.ReleaseDispatch();
	book2.Close(_O((short)0),vOpt,vOpt); //关闭EXCEL,不保存文件
	book2.ReleaseDispatch();
	books2.Close();
	books2.ReleaseDispatch();
	app2.ReleaseDispatch();	
	app2.Quit();
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return;
	}
	
	
	strSql.Format("共导入 %ld 名职工工资,总额为：%.2f",y-1 ,dbWage);
	
	AfxMessageBox(strSql);
	GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText("");
	GetDlgItem(IDC_STATIC_NOTIFY)->ShowWindow(SW_HIDE);


}

void CWageInput::OnB1() //模拟查询
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryData;
	pg.DoModal();

	
}

void CWageInput::SetGridHead()
{
	CString HeadTitle[]={"序号","部门","卡号","姓名","性别","出生日期","年龄",\
		"性质","年度工资","比例","应充金额","帐户结存","合计"} ,strTmp;//共 
	
	long  headWidth[]={800,1000,1000,900,400,1100,400,\
		1200,1400,800,1400,1400,1400};
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));

	m_grid.SetFixedCols(1);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2){
			m_grid.SetMergeCol(i,true);// 前6列单元格进行合
			m_grid.SetColAlignment(i,4);
		}
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
}

UINT CWageInput::QueryData(LPVOID ps)
{
	CWageInput * pd=(CWageInput * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);
//	pd->SetGridHead();
	CString HeadTitle[]={"序号","部门","卡号","姓名","性别","出生日期","年龄",\
		"性质","年度工资","比例","应充金额","帐户结存","合计"} ,strTmp;//共 
	
	long  headWidth[]={800,1000,1000,900,400,1100,400,\
		1200,1400,800,1000,1400,1400};
	CPeculiarInput::SetGridHead(HeadTitle,headWidth,pd->m_grid,sizeof(HeadTitle)/sizeof(CString),5,2);

	COleDateTime dt1;
	pd->d1.GetTime(dt1);

	CString strSql,str1;
	long cols,row,i,col;
	double add[20];
	const int START_COMPUTE=7; //在SQL语句中
	const double GUOQING =700.00,GUOHOU= 500.00 ;
	for( i=0 ; i< 20 ;i++)add[i]=0.0;

	try{
 	
		strSql.Format("SELECT 部门名称,卡号,姓名,性别,出生日期,%d-to_char(出生日期,'yyyy') age,工作性质, \
			 x.n1,to_char(y.n1*100)||'%%',decode(工作性质,'建国后退休',decode(sign(round(y.n1*x.n1,2)-%.2f),1,round(y.n1*x.n1,2),%.2f),\
			 '建国前退休',decode(sign(round(y.n1*x.n1,2)-%.2f),1,round(y.n1*x.n1,2),%.2f),round(y.n1*x.n1,2) ), \
			 结存金额,round(结存金额+y.n1*x.n1,2) \
			 from lsq_emp_wage x,\
			 \
			 (select 卡号,姓名,性别,出生日期,工作性质,结存金额,ds2,n1,n2,n3,部门编码 from 职工基本情况表 a,\
			       (select n1,ds2,n2,n3 from lsq_gh_type t Where ds3='C' ) b \
			 where a.工作性质=b.ds2  and %d-to_char(出生日期,'yyyy') >=n2 and %d-to_char(出生日期,'yyyy')<=n3 ) y, \
			 \
			 厂部门表 z \
			 \
			 where x.ds1=y.卡号 and to_char(x.d1,'yyyy')=%d-1 and y.部门编码=z.部门编码 ",dt1.GetYear(),\
			 GUOHOU,GUOHOU,GUOQING,GUOQING,dt1.GetYear(),dt1.GetYear(),dt1.GetYear() );
	
		if( pd->c1.GetCurSel() != CB_ERR && pd->c1.GetCurSel() != pd->c1.GetCount()-1 ){
			pd->c1.GetLBText(pd->c1.GetCurSel(),str1);
			strSql+=" AND 部门名称='"+str1+"'";

		}
		if( pd->c2.GetCurSel() != CB_ERR  && pd->c2.GetCurSel() != pd->c2.GetCount()-1 ){
			pd->c2.GetLBText(pd->c2.GetCurSel(),str1);
			strSql+=" AND 工作性质='"+str1+"'";

		}

		strSql+=" ORDER by 部门名称,姓名";
		
	
		
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		row=1;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			str1.Format("%ld",row);
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
			pd->m_grid.AddItem("",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();

//		str1.Format("总计: 需采购 %ld 条药品",row-1 );
//		pd->GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(str1);
		pd->m_grid.SetMergeCells(true);
		pd->m_grid.SetMergeRow(row,1); 
		pd->m_grid.SetRow(row);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("共有%ld 条",row-1);
		pd->m_grid.SetTextMatrix(row,0,"合计");	
		
		
		for(int count=1;count<cols+1;count++){
			pd->m_grid.SetTextMatrix(row,count,strSql);	
			pd->m_grid.SetCol(count);
			pd->m_grid.SetCellBackColor(RGB(255,128,0));
			
		}
		
		for(i=START_COMPUTE;i<cols;i++){
			if( i== START_COMPUTE+1) strSql="";
			else 
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

	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
	return true;
}

void CWageInput::OnExcel()
{
	extern void ToExcel(CMSHFlexGrid * pg);
	if( MessageBox("是否确定要导出到 Excel 表格 ??? ","提示",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	ToExcel(&m_grid);

}

void CWageInput::OnB3() //实际充值操作
{
	CProgress pd;
	pd.strNotify="是否确定要进行年度结转充值,每年度只允许进行一次充值,且请确认工资已经导入!!!";
	pd.pThreadFunction=CProgress::EmpAutoAddCash;
	pd.strView="正在进行自动充值,请稍候...";
	pd.DoModal();
}

void CWageInput::OnOK() // 充值情况查询
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryDataReal;
	pg.DoModal();

}

UINT CWageInput::QueryDataReal(LPVOID ps) //实际情况查询
{
	CWageInput * pd=(CWageInput * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);
//	pd->SetGridHead();
	CString HeadTitle[]={"序号","部门","卡号","姓名","性别","出生日期","年龄",\
		"性质","年度工资","比例","应充金额","上年结存","合计","帐户余额"} ,strTmp;//共 
	
	long  headWidth[]={800,1000,1000,900,400,1100,400,\
		1200,1400,800,1000,1400,1400,1400};
	CPeculiarInput::SetGridHead(HeadTitle,headWidth,pd->m_grid,sizeof(HeadTitle)/sizeof(CString),5,2);
	
	COleDateTime dt1;
	pd->d1.GetTime(dt1);


	CString strSql,str1,str2;
	pd->e2.GetWindowText(str1);//卡号
	pd->e3.GetWindowText(str2);//姓名

	long cols,row,i,col;
	double add[20];
	const int START_COMPUTE=7; //在SQL语句中
	for( i=0 ; i< 20 ;i++)add[i]=0.0;
//	CString HeadTitle[]={"序号","部门","卡号","姓名","性别","出生日期","年龄",\
		"性质","年度工资","比例","应充金额","帐户结存","合计"} ,strTmp;//共 
	try{
 	
		strSql.Format("SELECT 部门名称,卡号,姓名,性别,出生日期,to_char(sysdate,'yyyy')-to_char(出生日期,'yyyy') age,工作性质, \
			 x.n2,decode(to_char(x.n3*100)||'%%','%%',' ',to_char(x.n3*100)||'%%'),n1,n5,n5+n1,结存金额 from lsq_emp_charge x,职工基本情况表　a,	 厂部门表 z	\
			 where x.ds1(+)=a.卡号 and a.部门编码=z.部门编码 AND 卡号 like '%s%%' AND 姓名　like '%s%%' and 类别='参保' and x.n4 =%d   ",str1,str2,dt1.GetYear() );
	
		if( pd->c1.GetCurSel() != CB_ERR && pd->c1.GetCurSel() != pd->c1.GetCount()-1 ){
			pd->c1.GetLBText(pd->c1.GetCurSel(),str1);
			strSql+=" AND 部门名称='"+str1+"'";

		}
		if( pd->c2.GetCurSel() != CB_ERR  && pd->c2.GetCurSel() != pd->c2.GetCount()-1 ){
			pd->c2.GetLBText(pd->c2.GetCurSel(),str1);
			strSql+=" AND 工作性质='"+str1+"'";

		}

		strSql+=" ORDER by 部门名称,姓名";

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		row=1;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			str1.Format("%ld",row);
			pd->m_grid.SetTextMatrix(row,col++,str1);
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
				
				if( i>=START_COMPUTE )add[i-START_COMPUTE]+=atof(str1); 
			}
			row++;
			pd->m_grid.AddItem("",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();

//		str1.Format("总计: 需采购 %ld 条药品",row-1 );
//		pd->GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(str1);
		pd->m_grid.SetMergeCells(true);
		pd->m_grid.SetMergeRow(row,1); 
		pd->m_grid.SetRow(row);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("共有%ld 条",row-1);
		pd->m_grid.SetTextMatrix(row,0,"合计");	
		
		
		for(int count=1;count<cols+1;count++){
			pd->m_grid.SetTextMatrix(row,count,strSql);	
			pd->m_grid.SetCol(count);
			pd->m_grid.SetCellBackColor(RGB(255,128,0));
			
		}
		
		for(i=START_COMPUTE;i<cols;i++){
			if( i== START_COMPUTE+1 ) strSql="";
			else
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

	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
	return true;
}
