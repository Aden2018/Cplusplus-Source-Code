// EmployeeRelateQueryForFee.cpp: implementation of the CEmployeeRelateQueryForFee class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "EmployeeRelateQueryForFee.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEmployeeRelateQueryForFee::CEmployeeRelateQueryForFee()
{

}

CEmployeeRelateQueryForFee::~CEmployeeRelateQueryForFee()
{

}

BOOL CEmployeeRelateQueryForFee::OnInitDialog()
{
	CEmployeeQuery::OnInitDialog();

	SetWindowText("供养亲属人员表");
	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"编码","姓名","性别","年龄","供养性质","余额","供养人","所属部",\
		"工作性质","工龄"};

	long j=0, i=0,x=0;

	long  headWidth[]={0,1400,1200,600,1400,1300,1300,2000,2000,2000};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		m_grid.SetColWidth(i,headWidth[count]);

//		p2->m_grid.SetRow(0);
//		p2->m_grid.SetCol(i);
//		p2->m_grid.SetColAlignment(i,4);//flexAlignCenterCenter 4 单元格的内容居中、居中对齐	

		m_grid.SetTextArray(i++,HeadTitle[count]);
	}


	GetDlgItem(IDC_STATIC_3)->SetWindowText("供养人部门");
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("供养亲属情况表");

	return true;
}

void CEmployeeRelateQueryForFee::OnOK()
{
	BeginWaitCursor();
	//卡号,姓名,性别,出生日期,工作日期,部门,结存金额,工作性质
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetRedraw(false);

	long j=0, i=0,x=0,z;

	CString HeadTitle2[]={"编码","姓名","性别","供养性质","余额","年龄","供养人","所属部",\
		"工作性质","工龄","hao"},str1;
	long  headWidth[]={1400,1000,600,1400,900,800,1000,1400,1200,800,0};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle2)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(long count=0;count<sizeof(HeadTitle2)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle2[count]);
	}
	CString strSql,strName,strID,strDepart;
	if(m_depart.GetCurSel()==CB_ERR)strDepart="所有部门";
	else m_depart.GetLBText(m_depart.GetCurSel(),strDepart); 

	m_name.GetWindowText(strName);
	m_kahao.GetWindowText(strID);
	j=1;
	try{
		if(strDepart=="所有部门")
			strSql.Format("select BM,XM,XB,XINGZHI,YUER,to_char(sysdate,'yyyy')-to_char(csRiQI,'yyyy') 年龄 ,\
			姓名,所属部,工作性质,to_char(sysdate,'yyyy')-to_char(工作日期,'yyyy')+1 工龄,kahao from 职工基本情况表 e1,厂部门表 e2,codeQingShu e3 where  \
			e1.部门编码=e2.部门编码 and e3.kahao=e1.卡号 and \
			卡号 like '%s%%' and 姓名 like '%s%%' AND ZXRIQI IS NULL",strID,strName);
		else
			strSql.Format("select BM,XM,XB,XINGZHI,YUER,to_char(sysdate,'yyyy')-to_char(csRiQI,'yyyy') 年龄 ,\
			姓名,所属部,工作性质,to_char(sysdate,'yyyy')-to_char(工作日期,'yyyy')+1 工龄,kahao from 职工基本情况表 e1,厂部门表 e2,codeQingShu e3 where \
				e1.部门编码=e2.部门编码 and e3.kahao=e1.卡号 and \
				卡号 like '%s%%' and 姓名 like '%s%%' and 所属部='%s' and ZXriqi is NULL ",strID,strName,strDepart);
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		z=recSet->GetFields()->Count ;
		while(!recSet->adoEOF){
			x=0;
			for(count=0;count< z ;count++){
				
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(count)->Value.vt==VT_NULL ? " ":recSet->GetFields()->GetItem(count)->Value ) ;
				m_grid.SetTextMatrix(j,x++,str1);
			}
				
			
			m_grid.AddItem(" ",_variant_t(++j));
			recSet->MoveNext();


		}
		m_grid.SetRedraw(true);
		recSet->Close();		
		
	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox("数据库可能破坏,请检查数据...");
		return;
	}
	m_grid.SetTextMatrix(j,0,"合计");
	strSql.Format("共查询到: %ld 条信息",j-1);
	GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(strSql);
	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow=1;
		for( i=1;i<8;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
	EndWaitCursor();
}
