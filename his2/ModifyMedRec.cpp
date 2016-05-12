// ModifyMedRec.cpp: implementation of the CModifyMedRec class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "ModifyMedRec.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModifyMedRec::CModifyMedRec()
{

}

CModifyMedRec::~CModifyMedRec()
{

}

BOOL CModifyMedRec::OnInitDialog()
{
	CDialog::OnInitDialog();
	const CString strTitle="药品修改情况明细表";
	
	GetDlgItem(IDC_STATIC_HEAD)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_HEAD)->SetWindowText(strTitle);
	SetWindowText(strTitle);

	GetDlgItem(IDC_STATIC_1)->SetWindowText("拼 音");
	GetDlgItem(IDC_STATIC_2)->SetWindowText("名 称");
	GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_DELETE_ROW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_ADD)->ShowWindow(SW_HIDE);

	SetGridHead();
	return TRUE;  // return TRUE unless you set the focus to a control

}

void CModifyMedRec::SetGridHead()
{
	CString HeadTitle[]={"序号","修改日期","操作员","库房","编码","名称","规格","单位","数量(旧)","数量(新)","相关数",\
		"价格(旧)","价格(新)","指导价(旧)","指导价(新)","进价(旧)","进价(新)","有效期(旧)","有效期(新)","产地(旧)",\
		"产地(新)"}; 
																														//*
	long  headWidth[]={600,1000,800,800,900,1200,1000,500,900,900,900,\
		800,800,1000,1000,1000,1000,1000,1000,1400,\
		1400,1000,1000,11400,1400,1400,1400};							//*
	
	
	m_grid.SetRows(2);
	m_grid.Clear();

	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(8);
	long  i=0,col(0),row(0);
	m_grid.SetRow(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<6){
			m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		}
	/*	if( count < 14 )
			m_grid.SetColAlignment((long)count,short(4));
	*/	m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
	
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
	m_grid.SetBackColorFixed(RGB(170,170,85));
}

void CModifyMedRec::OnOK()
{
	UpdateData();
//	{"序号","修改日期","操作员","库房","编码","名称","规格","单位","数量(旧)","数量(新)","相关数",\
		"价格(旧)","价格(新)","指导价(旧)","指导价(新)","进价(旧)","进价(新)","有效期(旧)","有效期(新)","产地(旧)",\
		"产地(新)"}; 

	CString strSql,strTemp;
	long cc,row,cols,i;
	double add[8]={0.,.0,.0,0,0,0,0,0};
	CONST int COMPUTE_COLS=7;
	m_grid.SetRedraw( false);

	SetGridHead();
	try{
		strSql.Format("select trunc(mod_date,'dd'),n_name,kfmc,bm,mc,gg,dw,sl,n_sl,n_sl-sl,\
			sell,n_sell,coach,n_coach,jinjia,n_jinjia,rq2,n_rq2,c.gongmc,e.gongmc \
			from lsq_med_modify_rec a ,medcode b,codegys c,storeroom d ,codegys e \
			where a.ypbm=b.bm and a.factorycode=c.gongbm and a.kfbm=d.kfbm and a.n_factorycode=e.gongbm \
			and mod_date between to_date(%s,'yyyymmdd') and to_date(%s,'yyyymmdd') \
			 ",m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d") );
		m_bm.GetWindowText(strTemp); //作为药品拼音
		if( ! strTemp.IsEmpty() ) strSql+=" AND b.py like '"+strTemp+"%'";
		c_name.GetWindowText(strTemp); //作为药品名称
		if( ! strTemp.IsEmpty() ) strSql+=" AND mc like '"+strTemp+"%'";
		strSql+=" ORDER BY trunc(mod_date,'dd'),kfmc ";
				
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		cols=recSet->GetFields()->Count;
		row=1;

		while(!recSet->adoEOF){
			strSql.Format("%ld",row);
			m_grid.SetTextMatrix(row,0,strSql);
			m_grid.SetRow(row);
			m_grid.SetCol(10);
			m_grid.SetCellForeColor(RGB(255,0,0));
			i=0;
			for(cc=0;cc<cols;cc++)
			{
				
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(cc))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(cc))->Value);
				m_grid.SetTextMatrix(row,cc+1,strSql);
				if( cc >=COMPUTE_COLS && cc < COMPUTE_COLS+3 ){
					strTemp=strSql;
					strSql.Format("%.2f",atof(strTemp) );
					add[i++]+=atof(strSql);
				}
			
			}
			row++;
			m_grid.AddItem(" ",_variant_t(row));
			m_grid.SetMergeRow(row-1,false);
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

	for(i=COMPUTE_COLS; i< COMPUTE_COLS+3; i++){
		strSql.Format("%.2f",add[i-COMPUTE_COLS]);
		m_grid.SetTextMatrix(row,i+1,strSql);
	}

	m_grid.SetRedraw(true);

}

void CModifyMedRec::OnButtonAdd()
{

}

void CModifyMedRec::OnButtonDeleteRow()
{

}

void CModifyMedRec::OnClickMshflexgrid1()
{

}
