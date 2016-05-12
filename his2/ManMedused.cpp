// ManMedused.cpp: implementation of the CManMedused class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "ManMedused.h"
#include "PeculiarInput.h"
#include "ProgressIndicate.h"
#include "userMed.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CManMedused::CManMedused()
{
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_mixed WHERE ds3='DIALOG2' AND ds4='TITLE' ");

}

CManMedused::~CManMedused()
{

}

BOOL CManMedused::OnInitDialog()
{
	CString str33;
	str33.Format(" ( %s / %s / %s / %s )",strTmp[0],strTmp[1],strTmp[2],strTmp[3] );
	strTitle+=str33;

	str33.Format("%s%02d",date.Format("%Y-%m-"),iday);
	m_date1.ParseDateTime(str33);
	m_date2.ParseDateTime(str33);
	UpdateData(false);
	GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(false);
	GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow(false);
	CDoctorWorkLoad::OnInitDialog();

	CString px[]={"序号","单据","人员类别","卡号","姓名","性质","医生","挂号员","划价收费员","发药员","总费用","药品费用","其它费用","药品数量"};
	long pl[]={1000,0,900,1400,900,1000,1000,1000,1000,1000,1200,1200,1200,1000};
	CPeculiarInput::SetGridHead(px,pl,m_grid,sizeof(px)/sizeof(CString),1,sizeof(px)/sizeof(CString)-4);

	OnOK();
	return true;

}

void CManMedused::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryData;
	pg.DoModal();

}

UINT CManMedused::QueryData(LPVOID ps)
{
	CManMedused * pd=(CManMedused * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);

	CString px[]={"序号","单据","挂号类别","卡号","姓名","性质","医生","挂号员","划价收费员","发药员","总费用","药品费用","其它费用","药品数量"};
	long pl[]={600,0,1000,1400,900,900,900,900,900,1000,1200,1200,1200,1000};
	CPeculiarInput::SetGridHead(px,pl,pd->m_grid,sizeof(px)/sizeof(CString),1,4);

	CString strSql,str1,str2,str3;
	long cols,row,i,col;
	double add[]={0,0,0,0,0,0,0,0,0};
	const int START_COMPUTE=9; //在SQL语句中
	str1.Format("%s%02d",pd->date.Format("%Y%m"),pd->iday );
//	AfxMessageBox(str1);
	try{
		strSql.Format("SELECT aa.danjuhao,ghtype,sickbm,sickname,' ',doctorname,挂号员名,收费员名,发药员名,medMoney+treateMoney,MedMoney,treateMoney,xx from \
			(select * from itemregistertou where  riqi=to_date(%s,'yyyymmdd') ) aa,\
			(select danjuhao,sum(sl) xx from itemti t where riqi=to_date(%s,'yyyymmdd') and substr(danjuhao,1,1)='G' and ypbm='%s' group by danjuhao ) bb \
			where aa.danjuhao=bb.danjuhao ",str1,str1,pd->strBM );
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
		//	if( i == START_COMPUTE+1 ) strSql="";
		//	else 
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

void CManMedused::OnDblClickMshflexgrid1()
{
	int curRow=m_grid.GetRow();
	if( curRow== 0 || curRow>= m_grid.GetRows()-1 ) return;
 	CUserMed userMed;
//"序号","单据","挂号类别","卡号","姓名","性质","医生","挂号员","划价收费员","发药员","总费用","药品费用","其它费用","药品数量"};

	userMed.str2[1]=m_grid.GetTextMatrix(curRow,4);//
	userMed.str2[2]=strBM;//
	userMed.str2[3]=m_grid.GetTextMatrix(curRow,2);
	userMed.str2[5]=m_grid.GetTextMatrix(curRow,1);

	userMed.str2[6]=m_grid.GetTextMatrix(curRow,7);
	userMed.str2[7]=m_grid.GetTextMatrix(curRow,8);
	userMed.str2[8]=m_grid.GetTextMatrix(curRow,9);

	userMed.DoModal();

}
