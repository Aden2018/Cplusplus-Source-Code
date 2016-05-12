// EmpGetAccount.cpp: implementation of the CEmpGetAccount class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "EmpGetAccount.h"
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

CEmpGetAccount::CEmpGetAccount()
{
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_mixed WHERE ds3='TITLE' AND ds4='AAA' ");

}

CEmpGetAccount::~CEmpGetAccount()
{

}

BOOL CEmpGetAccount::OnInitDialog()
{
	CDoctorWorkLoad::OnInitDialog();

	m_grid.SetRedraw(true);

	pc=(CComboBox*)GetDlgItem(IDC_COMBO1);
	CenterWindow();
	GetDlgItem(IDC_STATIC2)->SetWindowText("查询年度");
	CRect rt1;

	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATETIMEPICKER1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATETIMEPICKER2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATETIMEPICKER2)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	rt1.bottom+=200;
	pc->MoveWindow(rt1);
	pc->ShowWindow(SW_SHOW);

/*	;
	GetDlgItem(IDC_STATIC_2)->SetWindowText("部门名称");
	GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_BUTTON_PRINT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_PRINT)->SetWindowText("利息结算");


	GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	c_edit1.MoveWindow(rt1);
	c_edit1.ShowWindow(SW_SHOW);

	GetDlgItem(IDC_DATETIMEPICKER3)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	rt1.bottom+=200;
	((CComboBox *)GetDlgItem(IDC_COMBO2))->MoveWindow(rt1);
	((CComboBox *)GetDlgItem(IDC_COMBO2))->ShowWindow(SW_SHOW);
	
	pc->ShowWindow(SW_SHOW);
*/
	pc->ResetContent();
	CString strTmp;
	int year=COleDateTime::GetCurrentTime().GetYear();
	for(long i=0; i<5; i++ ){
		strTmp.Format("%d",year-i );
		pc->AddString(strTmp);
	}
	pc->SetCurSel(0);

	CString px[]={"类别","人数","工资总额和养老金总额","单位提取","统筹","个人帐户","个人","特殊"};
	long pl[]={1600,1200,1500,1500,1500,1500,1500,1500,1000,1000,1000,1000};
	CPeculiarInput::SetGridHead(px,pl,m_grid,sizeof(px)/sizeof(CString),1,sizeof(px)/sizeof(CString));
	
	return true;
}

void CEmpGetAccount::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryData;
	pg.DoModal();


}

UINT CEmpGetAccount::QueryData(LPVOID ps)
{
	CEmpGetAccount * pd=(CEmpGetAccount * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);


	CString px[]={"类别","人数","工资总额和养老金总额","单位提取","统筹","个人帐户","个人","特殊"};
	long pl[]={1800,1200,2200,1500,1500,1500,1500,1500,1000,1000,1000,1000};
	CPeculiarInput::SetGridHead(px,pl,pd->m_grid,sizeof(px)/sizeof(CString),1,1);
	
	CString strSql,str1;

	pd->pc->GetLBText(pd->pc->GetCurSel(),strSql);

	int year=atol(strSql);

	long cols,row,i,col;
	double add[20];
	const int START_COMPUTE=1; //在SQL语句中
	for( i=0 ; i< 20 ;i++)add[i]=0.0;

	try{
		strSql.Format("SELECT bb.ds3,cc,round(a1,2),round(a2,2),round(a3-NVL(x1,0),2),round(a4+NVL(x1,0),2),a4,x1 from  \
						(select ds3, count(*) cc,sum(n2) a1,sum(n2)*0.04 a2,sum(n2)*0.04-sum(n1) a3,sum(n1) a4 from lsq_emp_charge where n4=%d group by ds3 ) bb,\
						(select ds5,sum(NVL(n1,0)) x1  from lsq_emp_headship_charge t where n2=%d  group by ds5) bb2,\
						lsq_mixed \
						where bb.ds3=bb2.ds5(+) and bb.ds3=lsq_mixed.ds3 order by lsq_mixed.n1 ",year,year );

	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		row=1;
		double dX;
		while(!recSet->adoEOF){
			col=0;
		//	str1.Format("%ld",row);
		//	pd->m_grid.SetTextMatrix(row,col++,str1);
	/*		pd->m_grid.SetRow(row);
			pd->m_grid.SetCol(6);
			pd->m_grid.SetCellBackColor(BK1);
			pd->m_grid.SetCol(9);
			pd->m_grid.SetCellBackColor(BK2);
	*/	
			pd->m_grid.SetMergeRow(row,false); 
			for(i=0;i<cols;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				pd->m_grid.SetTextMatrix(row,col++,str1);
				
				if( i>=START_COMPUTE )add[i-START_COMPUTE]+=atof(str1); 
			}
			row++;
			pd->m_grid.AddItem("",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();

/*		pd->m_grid.SetMergeCells(2);
		pd->m_grid.SetMergeRow(row,1); 
		pd->m_grid.SetRow(row);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("共有%ld 条",row-1);

	*/
		pd->m_grid.SetTextMatrix(row,0,"合计");	
		pd->m_grid.SetRow(row);
		for(int count=1;count<cols;count++){
		//	pd->m_grid.SetTextMatrix(row,count,strSql);	
			pd->m_grid.SetCol(count);
			pd->m_grid.SetCellBackColor(RGB(255,128,0));
			
		}
		
		for(i=START_COMPUTE;i<cols;i++){
			strSql.Format("%.2f",add[i-START_COMPUTE]);
			pd->m_grid.SetTextMatrix(row,i,strSql);
		}
	
		pd->m_grid.SetRedraw(true);
		
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
	
		return false;
	}	

	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
	return true;
}
