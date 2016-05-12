// CureList.cpp: implementation of the CCureList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "CureList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCureList::CCureList()
{

}

CCureList::~CCureList()
{

}

BOOL CCureList::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString strSql,strRec;
	const CString STRNAME="治疗项目费用标准";
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(STRNAME);
	SetWindowText(STRNAME);
	GetDlgItem(IDC_STATIC_3)->SetWindowText("收费项目");
	GetDlgItem(IDC_STATIC_2)->SetWindowText("编码");
//********************************************************************************
//* purpose:原来是用项目名称输入查询,现改用拼音查询
//* date:	2005/11/6 凌绍清
//********************************************************************************
    GetDlgItem(ID_SEARCH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_1)->SetWindowText("拼音");
	long z=0;
	try{
		strSql.Format("select distinct(费用大类) from 费用项目表 order by 费用大类 ");
		m_depart.AddString("   ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetCollect("费用大类").vt==VT_NULL?" ":recSet->GetCollect("费用大类"));
			if(z!=0){
				if(strSql==strRec){
					recSet->MoveNext();
					continue;
				}

			}
			m_depart.AddString(strSql);
			recSet->MoveNext();
			strRec=strSql;
			z++;
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		recSet->Close();
		return false;
	}

/*	m_grid.SetRows(2);
	m_grid.Clear();

	long j=0, i=0,x=0;
	CString HeadTitle[]={"费用大类","费用编码","费用名称","标准金额","拼音"};

	long  headWidth[]={1400,1200,1600,1400,1300,1300,1200,2000};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		m_grid.SetColWidth(i,headWidth[count]);


		m_grid.SetTextArray(i++,HeadTitle[count]);
	}

*/
	SetGridHead();

	return true;
}

void CCureList::OnOK()
{
	BeginWaitCursor();
	//卡号,姓名,性别,出生日期,工作日期,部门,结存金额,工作性质
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetRedraw(false);

	long j=0, i=0,x=0,count;
	CString HeadTitle[]={"费用大类","费用编码","费用名称","标准金额","NAME_PY"};
/*
	long  headWidth[]={1400,1200,1600,1400,1300,1300,1200,2000};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		m_grid.SetColWidth(i,headWidth[count]);


		m_grid.SetTextArray(i++,HeadTitle[count]);
	}
*/
	
	SetGridHead();
	
	CString strSql,strName,strID,strDepart,str1;

	m_name.GetWindowText(strName);
	m_kahao.GetWindowText(strID);
	j=1;
	try{
		if(m_depart.GetCurSel()== CB_ERR || m_depart.GetCurSel() == 0 )
			strSql.Format("select * from 费用项目表 where  费用编码 like '%s%%' ",strID );
		else{
			m_depart.GetLBText(m_depart.GetCurSel(),strDepart);
			strSql.Format("select * from 费用项目表 where 费用大类 = '%s' and 费用编码 like '%s%%' ",strDepart,strID);

		}
		if ( ! strName.IsEmpty() ) strSql+=" and name_py like '"+strName+"%%'";


		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		double dX;
		while(!recSet->adoEOF){
			x=0;
			for(count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
				
				str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(HeadTitle[count])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(HeadTitle[count])));
				if( 3== count){
					dX=atof(str1);
					str1.Format("%.2f",dX);

				}
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
		curRow = 1;
		for( i=1;i<4;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
	m_name.Clear();
	m_name.SetFocus();
	EndWaitCursor();
}
void CCureList::OnDblClickMshflexgrid2()
{
	long row=m_grid.GetRow(),i;
	CString strFeeName;
	CMSHFlexGrid * pgrid=(CMSHFlexGrid*)theApp.pParentGrid.pGrid;
	i=pgrid->GetRows()-1;

	if(row<m_grid.GetRows()-1 && row !=0){
		strKH=m_grid.GetTextMatrix(row,1); //编码
		pgrid->SetTextMatrix(i,0,strKH);
		
		pgrid->SetTextMatrix(i,1,m_grid.GetTextMatrix(row,2)); //费用名称
		pgrid->SetTextMatrix(i,2,m_grid.GetTextMatrix(row,3));
		pgrid->AddItem("",_variant_t(++i));
	//	AfxMessageBox("成功加入:"+m_grid.GetTextMatrix(row,2)+" / "+m_grid.GetTextMatrix(row,3));
	}
	m_name.Clear();
	m_name.SetFocus();

}

void CCureList::OnClickMshflexgrid2()
{
	long r1;
	r1=m_grid.GetRow();
	if(r1 >= m_grid.GetRows()-1 || curRow == r1)return;

	m_grid.SetCol(0);
	m_grid.SetRow(curRow);
	UINT color=m_grid.GetCellBackColor();

	for(int i=1;i<4;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(color);
	}
	m_grid.SetRow(r1);
	curRow=r1;
	for( i=1;i<4;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(RGB(255,0,0));
	}

}

void CCureList::OnSelchangeCombo1()
{
	OnOK();
	m_name.SetFocus();

}

void CCureList::SetGridHead()
{
	m_grid.SetRows(2);
	m_grid.Clear();	long j=0, i=0,x=0;
	CString HeadTitle[]={"费用大类","费用编码","费用名称","标准金额","拼音"};

	long  headWidth[]={1400,1200,1600,1400,1300,1300,1200,2000};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		m_grid.SetColWidth(i,headWidth[count]);


		m_grid.SetTextArray(i++,HeadTitle[count]);
	}

	
}

void CCureList::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	m_name.SetFocus();
}
