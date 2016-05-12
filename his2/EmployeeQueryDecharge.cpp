// EmployeeQueryDecharge.cpp: implementation of the CEmployeeQueryDecharge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "EmployeeQueryDecharge.h"
#include "employeeBmp.H"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEmployeeQueryDecharge::CEmployeeQueryDecharge()
{

}

CEmployeeQueryDecharge::~CEmployeeQueryDecharge()
{

}

BOOL CEmployeeQueryDecharge::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString strSql;
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	try{
		strSql.Format("select distinct(所属部) from 厂部门表 ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetCollect("所属部").vt==VT_NULL?" ":recSet->GetCollect("所属部"));
			m_depart.AddString(strSql);
			recSet->MoveNext();
		}
		recSet->Close();
		m_depart.AddString("所有部门");

	}
	catch(_com_error e)
	{
		recSet->Close();
		return false;
	}
	SetGridHead();
	return true;
}

void CEmployeeQueryDecharge::SetGridHead()
{
	m_grid.SetRows(2);
	m_grid.Clear();

	long j=0, i=0,x=0;
	CString HeadTitle[]={"所属部","部门名称","卡号","姓名","性别","年龄","结存金额",\
		"性质","上年结存","使用累计","凭证号"};

	long  headWidth[]={1200,1200,1200,1000,600,600,1200,1000,1000,1000,1000};
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
}

void CEmployeeQueryDecharge::OnOK()
{
	BeginWaitCursor();
	//卡号,姓名,性别,出生日期,工作日期,部门,结存金额,工作性质
	SetGridHead();
	m_grid.SetRedraw(false);

	CString strSql,strName,strID,strDepart,str1;
	if(m_depart.GetCurSel()==CB_ERR)strDepart="所有部门";
	else m_depart.GetLBText(m_depart.GetCurSel(),strDepart); 

	m_name.GetWindowText(strName);
	m_kahao.GetWindowText(strID);
	long count,cols,j,x;
	j=1;
	try{
		if(strDepart=="所有部门")

			strSql.Format(" SELECT * FROM V_EMP_DECHARGE_COUNT WHERE  卡号 like '%s%%' AND 姓名 like '%s%%' ",strID,strName);


		else
			strSql.Format(" SELECT * FROM V_EMP_DECHARGE_COUNT WHERE  卡号 like '%s%%' AND 姓名 like '%s%%' AND 所属部='%s' ",strID,strName,strDepart );

		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->GetCount();
		while(!recSet->adoEOF){
			x=0;
			for(count=0;count< cols ;count++){
				
			//	str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(HeadTitle[count])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(HeadTitle[count])));
				str1=(char*)_bstr_t( recSet->GetFields()->GetItem(count)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(count)->Value);

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
	m_grid.SetRedraw(true);
	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow = 1;
		for( int i=2;i<8;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
	EndWaitCursor();
}

void CEmployeeQueryDecharge::OnDblClickMshflexgrid2()
{
	long row=m_grid.GetRow();
	if(row<m_grid.GetRows()-1 && row !=0){
		
		if(p!=NULL){
			for(int i=0; i< m_grid.GetCols(0) ;i++)((CString*)p)[i]=m_grid.GetTextMatrix(row,i);
			((CString*)p)[i]="FFFFFFFF";
			CDialog::OnOK();
		}
	}

}

void CEmployeeQueryDecharge::OnClickMshflexgrid2()
{
	long r1;
	r1=m_grid.GetRow();
	if(r1 >= m_grid.GetRows()-1 || curRow == r1)return;
	
	m_grid.SetCol(0);
	m_grid.SetRow(curRow);
	UINT color=m_grid.GetCellBackColor();
	
	for(int i=2;i<8;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(color);
	}
	m_grid.SetRow(r1);
	curRow=r1;
	for( i=2;i<8;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(RGB(255,0,0));
	}
}
