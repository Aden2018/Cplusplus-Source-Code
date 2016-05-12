// DoctorWorkOther.cpp: implementation of the CDoctorWorkOther class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "DoctorWorkOther.h"
#include "peculiarInput.h"
#include "ProgressIndicate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDoctorWorkOther::CDoctorWorkOther()
{
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_Title_list WHERE ds2='DIALOG' AND ds3='TITLE' AND ds4='AAK' ");

}

CDoctorWorkOther::~CDoctorWorkOther()
{

}

BOOL CDoctorWorkOther::OnInitDialog()
{
	CDoctorWorkLoad::OnInitDialog();
	GetDlgItem(IDC_STATIC_1)->SetWindowText("统计类别");
	GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_SHOW);
	

	pCombo1=(CComboBox*)GetDlgItem(IDC_COMBO1);
	pCombo1->ShowWindow(SW_SHOW);
	pCombo1->ResetContent();
	CDialogMedXL::ReadName("SELECT DISTINCT 费用大类 FROM 费用项目表 ",*pCombo1);
	pCombo1->AddString("");

	
	return true;

}

void CDoctorWorkOther::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryDoctorOther;
	pg.DoModal();
	
}

void CDoctorWorkOther::SetGridHead()
{
	CString px[]={"序号","费用名称","编码","姓名","费用金额","百分比"};
	long pl[]={1000,800,1000,1400,1400,1000,1000};
	CPeculiarInput::SetGridHead(px,pl,m_grid,sizeof(px)/sizeof(CString),1,2);

}

UINT CDoctorWorkOther::QueryDoctorOther(LPVOID ps)
{
	CDoctorWorkOther * pd=(CDoctorWorkOther * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);
	pd->SetGridHead();
	CString strSql,str1,strt1,strt2,strt3;
	long cols,row,i,col;
	double add[]={0,0,0,0,0,0,0,0,0};
	const int START_COMPUTE=3; //在SQL语句中
	pd->UpdateData();
	if( pd->pCombo1->GetCurSel() != CB_ERR ){
		pd->pCombo1->GetLBText(pd->pCombo1->GetCurSel(),str1);

	}
	else str1="";
	try{

		if( str1.IsEmpty() ){
			strt1="总治疗费用";
			strt2="";
			strt3="";
		}
		else {
			strt1=str1;
			strt2=str1+",";
			strt3=" and 费用大类='"+strt1+"' " ;

		}

		strSql.Format("select '%s',doctor,doctorname,sum(dj) xc from itemregistertizl a,itemregistertou c, 费用项目表 b\
				 where a.danjuhao=c.danjuhao and b.费用编码=a.zlmc %s \
				 and c.riqi between to_date(%s,'yyyymmdd') and to_date(%s,'yyyymmdd')  \
				 group by  doctor,doctorname order by  xc \
				   ",strt1,strt3,pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d") );

	 	
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		cols=recSet->GetFields()->Count;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			str1.Format("%ld",row);
			pd->m_grid.SetTextMatrix(row,col++,str1);
	/*		pd->m_grid.SetRow(row);
			pd->m_grid.SetCol(6);
			pd->m_grid.SetCellBackColor(BK1);
	*/
			for(i=0;i<cols;i++)
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
			
			str1=pd->m_grid.GetTextMatrix(i,4);
			strSql.Format("%.2f%%",atof( str1 )/add[0]*100);
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
