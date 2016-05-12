// PayMedNum.cpp: implementation of the CPayMedNum class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "PayMedNum.h"
#include "payMed.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define COLS  6
#define DOWN_ARROR 0x28
#define UP_ARROR 0x26

CPayMedNum::CPayMedNum()
{

}

CPayMedNum::~CPayMedNum()
{

}

BOOL CPayMedNum::OnInitDialog()
{
	CHuaJiaList::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("付药用户一览表");
	return true;
}

void CPayMedNum::OnOK()
{

	if( m_comboxSort.GetCurSel() == CB_ERR || m_comboxSort.GetCurSel() == 0 ){
		m_comboxSort.SetCurSel(0);
		ShowPublic();

	}
	else if (m_comboxSort.GetCurSel() == 1) {
		ShowReside();
	}


}

void CPayMedNum::OnDblClickMshflexgrid1()
{
 //	CString HeadTitle[]={"序号","姓名","BM","挂号类型","日期","序列号","挂号","划价","医生"}; //共6列
//	CString HeadTitle[]={"序号","serial","s2","姓名","性别","家庭住址","日期","床位","docotr"}; //9

	CPayMed huajia;
	long row=m_grid.GetRow();
	if(row == 0 || row >=m_grid.GetRows()-1){
		AfxMessageBox("请双击需要划价的条目...");
		return;
	}
	if( m_comboxSort.GetCurSel() == 1) { //住院人员
		huajia.str2[1]=m_grid.GetTextMatrix(row,3);//姓名
		huajia.str2[2]=m_grid.GetTextMatrix(row,2);//序列号
		huajia.str2[3]="住院人员";
		huajia.str2[4]=m_grid.GetTextMatrix(row,6);//日期
		huajia.str2[5]=m_grid.GetTextMatrix(row,2); //序列号
		huajia.strGhHuajia[1]=m_grid.GetTextMatrix(row,8);//医生
	}
	else {
		
		for(int i=1;i<6;i++)
			huajia.str2[i]=m_grid.GetTextMatrix(row,i);
		huajia.strGhHuajia[0]= m_grid.GetTextMatrix(row,i++); //划价人员
		huajia.strGhHuajia[1]= m_grid.GetTextMatrix(row,i++);//医生
	}
	if(huajia.DoModal() == IDOK) OnOK();
}

void CPayMedNum::ShowPublic()
{
	CString getTitle[]={"sickName","SickBm","GhType","riqi","danjuhao","挂号员名","划价员名","doctorName"};
	UpdateData();
	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"序号","姓名","BM","挂号类型","日期","序列号","挂号","划价","医生"}; //共6列

	long  headWidth[]={600,2000,00,2000,0,00,1200,1200,1000};

	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	m_grid.SetRow(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetColAlignment(long(count),short(4));
		m_grid.SetColWidth(i,headWidth[count]);
	
		m_grid.SetCol(long(count));
		m_grid.SetCellAlignment(short(4));
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	
	long row=1,col;
	CString strSql,str1;
	try{

		strSql.Format("select SICKNAME,SICKBM,GHTYPE,RIQI,DANJUHAO,挂号员名,划价员名,doctorname \
			from itemregistertou t where to_char(riqi,'YYYYMMDD')='%s' \
			and 收费员 is not null and 发药员 is NULL ",m_date1.Format("%Y%m%d"));
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			str1.Format("%ld",row);
			col=0;
			m_grid.SetTextMatrix(row,col++,str1);
			for(int i=0;i<sizeof(getTitle)/sizeof(CString);i++)
			{
				str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(getTitle[i])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(getTitle[i])));
				m_grid.SetTextMatrix(row,col++,str1);
			}
			row++;
			m_grid.AddItem(" ",_variant_t(row));
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
	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow=1;
		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}

}

void CPayMedNum::ShowReside()
{
	UpdateData();
	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"序号","serial","s2","姓名","性别","家庭住址","日期","床位","医生"}; //共6列+2

	long  headWidth[]={600,0,0,1200,400,1600,1300,4000,1200};

	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	m_grid.SetRow(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetColAlignment(long(count),short(4));
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetCol(long(count));
		m_grid.SetCellAlignment(short(4));
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	
	long row=1,col;
	CString strSql,str1;
	try{

		strSql.Format("select serial,s2,xm,xb,home_addr,rq,rname || '/'|| bname,y2 from lsq_reside_hos a,lsq_reside_bed b,lsq_reside_room c \
			,lsq_reside_hos_huajia d where a.bed_id=b.bcode and b.broom=c.rcode and d.s1=a.serial and \
			r1 between to_date('%s000000','yyyymmddhh24miss') and to_date('%s235959','yyyymmddhh24miss') 	",\
			m_dateStart.Format("%Y%m%d"),m_date1.Format("%Y%m%d"));

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			str1.Format("%ld",row);
			col=0;
			m_grid.SetTextMatrix(row,col++,str1);
			for(int i=0;i< recSet->GetFields()->Count;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(long(i))->Value);
				m_grid.SetTextMatrix(row,col++,str1);
			}
			row++;
			m_grid.AddItem(" ",_variant_t(row));
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
	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow=1;
		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}

}
