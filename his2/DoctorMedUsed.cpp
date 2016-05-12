// DoctorMedUsed.cpp: implementation of the CDoctorMedUsed class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "DoctorMedUsed.h"
#include "PeculiarInput.h"
#include "ProgressIndicate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDoctorMedUsed::CDoctorMedUsed()
{
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_Title_list WHERE ds2='DIALOG' AND ds3='TITLE' AND ds4='AAJ' ");

}

CDoctorMedUsed::~CDoctorMedUsed()
{

}

BOOL CDoctorMedUsed::OnInitDialog()
{
	CString str33;
	str33.Format(" ( %s / %s / %s / %s )",strTmp[0],strTmp[1],strTmp[2],strTmp[3] );
	strTitle+=str33;

	str33.Format("%s%02d",date.Format("%Y-%m-"),1);
	m_date1.ParseDateTime(str33);
	str33.Format("%s%02d",date.Format("%Y-%m-"),last_day);
	m_date2.ParseDateTime(str33);
	UpdateData(false);
	GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(false);
	GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow(false);
	CDoctorWorkLoad::OnInitDialog();


	CString px[]={"序号","编码","姓名","数量","购进额","零售额","利润"};
	long pl[]={1000,800,1000,1000,1000,1000,1000};
	CPeculiarInput::SetGridHead(px,pl,m_grid,sizeof(px)/sizeof(CString),1,0);
	OnOK();

	return true;
}

UINT CDoctorMedUsed::QueryDataX(LPVOID ps)
{
	CDoctorMedUsed * pd=(CDoctorMedUsed * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);
	CString px[]={"序号","编码","姓名","数量","购进额","零售额","利润"};
	long pl[]={1000,800,1000,1000,1000,1000,1000};
	CPeculiarInput::SetGridHead(px,pl,pd->m_grid,sizeof(px)/sizeof(CString),1,0);


	CString strSql,str1,str2,str3;
	long cols,row,i,col;
	double add[]={0,0,0,0,0,0,0,0,0};
	const int START_COMPUTE=2; //在SQL语句中
	str2.Format("%s%02d",pd->date.Format("%Y%m"),pd->last_day );
	str1.Format("%s%02d",pd->date.Format("%Y%m"),1 );
//	AfxMessageBox(str1);
	try{
		strSql.Format("select doctor,doctorname,sum(zzx) slx,sum(x1) ,sum(x2),sum(x2)-sum(x1) pt from itemregistertou a,\
			(select danjuhao,sum(SL) zzx,sum(sl*pdj) x1,sum(sl*dj) x2 from itemti t where riqi between \
			to_date(%s,'yyyymmdd') and to_date(%s,'yyyymmdd') and substr(danjuhao,1,1)='G' \
			and ypbm='%s' group by danjuhao ) b \
			where a.danjuhao=b.danjuhao and a.riqi  between to_date(%s,'yyyymmdd') and \
			to_date(%s,'yyyymmdd') group by doctor,doctorname ",str1,str2,pd->strBM,str1,str2); 
		strSql+=" ORDER BY pt,slx " ;
	
	/*	
		CFile of("c:\\his.log",CFile::modeRead|CFile::modeWrite);
		str1.Format("\r\n--------------------------------------------------\r\n");
		of.SeekToEnd();
		of.Write(str1,str1.GetLength());
		of.Write(strSql,strSql.GetLength());
		of.Flush();
		of.Close();
	
	*/	
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
			pd->m_grid.SetCol(9);
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

		pd->m_grid.SetMergeCells(true);
		pd->m_grid.SetMergeRow(row,1); 
		pd->m_grid.SetRow(row);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("   共有 %ld 条记录 ",row-1);
		pd->m_grid.SetTextMatrix(row,0,"合计");	
		pd->GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(strSql);
		
		for(int count=1;count<cols+1;count++){
			pd->m_grid.SetTextMatrix(row,count,strSql);	
			pd->m_grid.SetCol(count);
			pd->m_grid.SetCellBackColor(RGB(255,128,0));
			
		}
	
		for(i=START_COMPUTE;i<cols;i++){
			strSql.Format("%.2f",add[i-START_COMPUTE]);
			pd->m_grid.SetTextMatrix(row,i+1,strSql);
		}

		pd->m_grid.SetRedraw(true);
		
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		((CProgressIndicate *)ps)->ConnectFlag =1;
		((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
		
		return false;
	}	
END:
	pd->m_grid.SetRedraw(true);
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
}

void CDoctorMedUsed::OnDblClickMshflexgrid1()
{

}

void CDoctorMedUsed::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryDataX;
	pg.DoModal();


}
