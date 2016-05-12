// DoctorWorkLoad.cpp: implementation of the CDoctorWorkLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "DoctorWorkLoad.h"
#include "ProgressIndicate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDoctorWorkLoad::CDoctorWorkLoad()
{

}

CDoctorWorkLoad::~CDoctorWorkLoad()
{

}

BOOL CDoctorWorkLoad::OnInitDialog()
{
	CGenericStockMed::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	SetWindowText(strTitle);
	
	SetGridHead();
	return true;
}

void CDoctorWorkLoad::OnDblClickMshflexgrid1()
{

}

void CDoctorWorkLoad::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryDoctor;
	pg.DoModal();
	

}


void CDoctorWorkLoad::SetGridHead()
{
	CString HeadTitle[]={"序号","编码","医生","接诊次数","药品费","其它费用","总费用","现金","药品利润","百分比"} ;//共 8 列
	
	long  headWidth[]={800,800,900,1400,1400,1400,1400,1400,1400,1400,1400,1400,1600,1300,1300,1300,0,1300,1300,1300,00,00,1400};
	
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetRedraw(false);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<3){
			m_grid.SetMergeCol(i,true);// 前6列单元格进行合
			m_grid.SetColAlignment(i,4);
		}
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
	m_grid.SetRedraw(true);

}

UINT CDoctorWorkLoad::QueryDoctor(LPVOID ps)
{
	CDoctorWorkLoad * pd=(CDoctorWorkLoad * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);
	pd->SetGridHead();
	CString strSql,str1;
	long cols,row,i,col;
	double add[]={0,0,0,0,0,0,0,0,0};
	const int START_COMPUTE=2; //在SQL语句中
	pd->UpdateData();
	try{
		strSql.Format("select doctor,doctorname,count(*),sum(medmoney),sum(treatemoney),\
			sum(medmoney)+sum(treatemoney) xc,sum(cash),sum(profit) from itemregistertou a \
			where riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd')\
			group by doctor,doctorname order by xc ",pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d") );

	 	
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		cols=recSet->GetFields()->Count;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			str1.Format("%ld",row);
			pd->m_grid.SetTextMatrix(row,col++,str1);
			pd->m_grid.SetRow(row);
			pd->m_grid.SetCol(6);
			pd->m_grid.SetCellBackColor(BK1);
	/*		pd->m_grid.SetCol(9);
			pd->m_grid.SetCellBackColor(BK2);
	*/		for(i=0;i<cols;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				pd->m_grid.SetTextMatrix(row,col++,str1);
				
				if( i>=START_COMPUTE )add[i-START_COMPUTE]+=atof(str1); 
			}
			row++;
			pd->m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();

//		str1.Format("总计: 需采购 %ld 条药品",row-1 );
//		pd->GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(str1);
		pd->m_grid.SetMergeCells(true);
		pd->m_grid.SetMergeRow(row,1); 
		pd->m_grid.SetRow(row);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("   共有 %ld 条记录 ",row-1);
		pd->m_grid.SetTextMatrix(row,0,"合计");	
		
		
		for(int count=1;count<cols+2;count++){
			pd->m_grid.SetTextMatrix(row,count,strSql);	
			pd->m_grid.SetCol(count);
			pd->m_grid.SetCellBackColor(RGB(255,128,0));
			
		}
		
		for(i=START_COMPUTE;i<cols;i++){
			strSql.Format("%.2f",add[i-START_COMPUTE]);
			pd->m_grid.SetTextMatrix(row,i+1,strSql);
		}

		count=pd->m_grid.GetCols(0)-1;
		for( i=1 ; i< pd->m_grid.GetRows()-1 ; i++ )
		{	
			
			str1=pd->m_grid.GetTextMatrix(i,6);
			strSql.Format("%.2f%%",atof( str1 )/add[3]*100);
			pd->m_grid.SetTextMatrix(i,count,strSql);
			pd->m_grid.SetCol(count);
			pd->m_grid.SetRow(i);
		//	pd->m_grid.SetCellBackColor(RGB(255,0,0));
			pd->m_grid.SetCellForeColor(RGB(255,0,0));

		}

		pd->m_grid.SetRedraw(true);
		
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
	
		return false;
	}	
	pd->m_grid.SetRedraw(true);
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
}
