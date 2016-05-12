// EmployeeNoworkQuery.cpp: implementation of the CEmployeeNoworkQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "EmployeeNoworkQuery.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEmployeeNoworkQuery::CEmployeeNoworkQuery()
{

}

CEmployeeNoworkQuery::~CEmployeeNoworkQuery()
{

}

BOOL CEmployeeNoworkQuery::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	CRect r1,r2;
	GetDlgItem(IDC_STATIC_3)->GetWindowRect(r1);
	ScreenToClient(r1);
	GetDlgItem(IDC_COMBO1)->GetWindowRect(r2);
	ScreenToClient(r2);
	GetDlgItem(IDC_STATIC_2)->MoveWindow(r1);
	GetDlgItem(IDC_EDIT2)->MoveWindow(r2);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("离休人员列表");
	OnOK();
	return true;
}

void CEmployeeNoworkQuery::OnOK()
{
	BeginWaitCursor();
	//卡号,姓名,性别,出生日期,工作日期,部门,结存金额,工作性质
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetRedraw(false);

	long j=0, i=0,x=0;
	CString HeadTitle[]={"所属部","卡号","姓名","性别","出生日期","工作日期",\
		"结存金额","工作性质"},str1;

	long  headWidth[]={1400,1200,1200,400,1300,1300,1200,2000};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		m_grid.SetColWidth(i,headWidth[count]);


		m_grid.SetTextArray(i++,HeadTitle[count]);
	}
	CString strSql,strName,strID,strDepart;

	m_name.GetWindowText(strName);
	m_kahao.GetWindowText(strID);
	j=1;
	try{
//		strSql.Format("select * from 职工基本情况表 e1,厂部门表 e2 where e1.部门编码=e2.部门编码 and \
				卡号 like '%s%%' and 姓名 like '%s%%' and 所属部='离休干部' and 类别 != '消户' ",strID,strName,strDepart);
		strSql.Format("select * from 职工基本情况表 e1,厂部门表 e2 where e1.部门编码=e2.部门编码 and \
				卡号 like '%s%%' and 姓名 like '%s%%'  and 类别 = '离休' ",strID,strName,strDepart);

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			x=0;
			for(count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
				
				str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(HeadTitle[count])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(HeadTitle[count])));
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

void CEmployeeNoworkQuery::OnSelchangeCombo1()
{

}


