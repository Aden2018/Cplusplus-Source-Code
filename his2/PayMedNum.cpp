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
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("��ҩ�û�һ����");
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
 //	CString HeadTitle[]={"���","����","BM","�Һ�����","����","���к�","�Һ�","����","ҽ��"}; //��6��
//	CString HeadTitle[]={"���","serial","s2","����","�Ա�","��ͥסַ","����","��λ","docotr"}; //9

	CPayMed huajia;
	long row=m_grid.GetRow();
	if(row == 0 || row >=m_grid.GetRows()-1){
		AfxMessageBox("��˫����Ҫ���۵���Ŀ...");
		return;
	}
	if( m_comboxSort.GetCurSel() == 1) { //סԺ��Ա
		huajia.str2[1]=m_grid.GetTextMatrix(row,3);//����
		huajia.str2[2]=m_grid.GetTextMatrix(row,2);//���к�
		huajia.str2[3]="סԺ��Ա";
		huajia.str2[4]=m_grid.GetTextMatrix(row,6);//����
		huajia.str2[5]=m_grid.GetTextMatrix(row,2); //���к�
		huajia.strGhHuajia[1]=m_grid.GetTextMatrix(row,8);//ҽ��
	}
	else {
		
		for(int i=1;i<6;i++)
			huajia.str2[i]=m_grid.GetTextMatrix(row,i);
		huajia.strGhHuajia[0]= m_grid.GetTextMatrix(row,i++); //������Ա
		huajia.strGhHuajia[1]= m_grid.GetTextMatrix(row,i++);//ҽ��
	}
	if(huajia.DoModal() == IDOK) OnOK();
}

void CPayMedNum::ShowPublic()
{
	CString getTitle[]={"sickName","SickBm","GhType","riqi","danjuhao","�Һ�Ա��","����Ա��","doctorName"};
	UpdateData();
	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"���","����","BM","�Һ�����","����","���к�","�Һ�","����","ҽ��"}; //��6��

	long  headWidth[]={600,2000,00,2000,0,00,1200,1200,1000};

	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
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

		strSql.Format("select SICKNAME,SICKBM,GHTYPE,RIQI,DANJUHAO,�Һ�Ա��,����Ա��,doctorname \
			from itemregistertou t where to_char(riqi,'YYYYMMDD')='%s' \
			and �շ�Ա is not null and ��ҩԱ is NULL ",m_date1.Format("%Y%m%d"));
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
	CString HeadTitle[]={"���","serial","s2","����","�Ա�","��ͥסַ","����","��λ","ҽ��"}; //��6��+2

	long  headWidth[]={600,0,0,1200,400,1600,1300,4000,1200};

	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
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
