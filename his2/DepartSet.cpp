// DepartSet.cpp: implementation of the CDepartSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "DepartSet.h"
#include "departSetAdd.h"
#include "otherDecharge.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDepartSet::CDepartSet()
{

}

CDepartSet::~CDepartSet()
{

}

BOOL CDepartSet::OnInitDialog()
{
	COperatorSet::OnInitDialog();
	return true;
}

void CDepartSet::OnOK()
{
	UpdateData();
	CString HeadTitle[]={"序号","所属部","编码","部门名称"} ,strTmp;//共 
	
	long  headWidth[]={600,2000,0,2000,00,0,00,1400};
	
	m_grid.SetRedraw(false);
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(2);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(long count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2){
			m_grid.SetMergeCol(i,true);// 前6列单元格进行合
			m_grid.SetColAlignment(i,4);
		}
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}	
	CString kfmc;
	CString strSql;
	long cols,x(1);
	try{
		
		strSql.Format("select 所属部,部门编码,部门名称 from 厂部门表 ");
		if( combo1.GetCurSel() == CB_ERR )strSql+=" ORDER BY 所属部,部门编码";
		else {
			combo1.GetLBText(combo1.GetCurSel(),kfmc);
			strSql+=" WHERE 所属部='"+kfmc+"' ORDER BY 所属部,部门编码 ";
		}
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		while(!recSet->adoEOF){
			strSql.Format("%ld",x);
			m_grid.SetTextMatrix(x,0,strSql);
			for(count=0;count< cols;count++){
				
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(count)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(count)->Value);
				m_grid.SetTextMatrix(x,count+1,strSql);
			}
			
			x++;
			m_grid.AddItem(" ",_variant_t(x));
			recSet->MoveNext();
		
		}
		recSet->Close();

		m_grid.SetTextMatrix(x,0,"合计");
		m_grid.SetRedraw(true);

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		AfxMessageBox(strSql);
		return ;
	}		
		
}

void CDepartSet::OnDblClickMshflexgrid1()
{
	CDepartSetAdd di;
	di.strSql.Format(" SELECT distinct 所属部 FROM 厂部门表 order by 所属部 ");

	long i=0;

	if( m_grid.GetRows()-1 == m_grid.GetRow() ){
		di.flag= 1; //新增
		di.strTitle="新增部门名称";
		if(di.DoModal()==IDOK) OnOK();
		return;
 
	}else
	{
		di.flag=2; //修改
		di.strTitle="部门名称修改";
	
		//大类,编码,名称
		for( i=0; i< 3; i++ )
			di.str[i]=m_grid.GetTextMatrix(m_grid.GetRow(),i+1);
		
		if( di.DoModal()==IDOK) OnOK();
		return;

	}
}

void CDepartSet::OnClickMshflexgrid1()
{
	const int ENDLINES=2;
	if(m_grid.GetRows() == ENDLINES || m_grid.GetRow() == m_grid.GetRows()-1 )return;//判断是否需要显示快捷菜单

	MSG *pms;
	CString strT1,strT2;
	pms=(MSG*)GetCurrentMessage();

	
	if(pms->message == 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		strT1.Format("是否要删除 (%s / %s) ？？",m_grid.GetTextMatrix(m_grid.GetRow(),1),m_grid.GetTextMatrix(m_grid.GetRow(),3) );
		if ( AfxMessageBox(strT1,MB_OKCANCEL)== IDCANCEL ) return;
	
		strT1.Format(" DELETE FROM 厂部门表 WHERE　部门编码='%s' ",m_grid.GetTextMatrix(m_grid.GetRow(),2) );
		if(!COtherDecharge::WriteSQL(strT1)){
			AfxMessageBox("删除失败!!");
			return;
		}
		OnOK();

	}
}

void CDepartSet::OnAdd()
{
	CDepartSetAdd di;
	di.strSql.Format(" SELECT distinct 所属部 FROM 厂部门表 order by 所属部 ");
		di.flag= 1; //新增
		di.strTitle="新增部门名称";
		if(di.DoModal()==IDOK) OnOK();

}
