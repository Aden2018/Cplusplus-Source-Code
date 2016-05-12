// QueryIC.cpp: implementation of the CQueryIC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "QueryIC.h"
#include "queryIClist.h"
#include "ProgressIndicate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQueryIC::CQueryIC()
{

}

CQueryIC::~CQueryIC()
{

}

void CQueryIC::OnOK()
{
	CProgressIndicate pq;
	pq.pDialog= this;
	pq.pThreadFunction = QueryICList;

	pq.DoModal();

}

UINT CQueryIC::QueryICList(LPVOID ps)
{
//	CString HeadTitle[]={"DAN","日期","IC","姓名","医生","挂号","划价","发药",ghtype,\
		"药品费","其它费用","利润","费用总额","帐户支出","现金支出","统筹支出"}; 

	CQueryICList *pf=(CQueryICList*)theApp.pParentGrid.pWnd;
	CQueryIC * pd =(CQueryIC *) ((CProgressIndicate *) ps )->pDialog ;
	pd->UpdateData();

	pf->m_grid.SetRedraw(false);

	pf->SetGridHead();
	CString strSql,str1,strGhtype,strname;
	
	const int COMPUTE_COLS=11; //共需计算列数
	long row,col,i,cols;
	double price(0),add[11]={0,0,0,0,0,0,0,0,0,0,0};
	//后面共要统计七列
	if( pd->c_type.GetCurSel()==CB_ERR || pd->c_type.GetCurSel() == 0 )strGhtype = "";
	else {
		pd->c_type.GetLBText(pd->c_type.GetCurSel(),strGhtype);
		if( strGhtype == "国前职工" ) strGhtype="建国前老工人";

	}
	pd->c_name.GetWindowText(strname);
//	strname.Remove(' ');

	try{
		//共14列查询
		strSql.Format("SELECT 'a',DANJUHAO,RIQI,SICKBM,SICKNAME,DOCTORNAME,挂号员名,收费员名,发药员名,ghtype,\
			PROFIT,MEDMONEY,TreateMONEY,MEDMONEY+TREATEMoney,decode(ghtype,'基本保险',\
			medmoney+treatemoney-cash,NULL) 帐户支出,cash,decode(ghtype,'特定门诊',\
			medmoney+treatemoney-cash-NVL(p3,0)-NVL(p2,0)-NVL(p1,0),NULL) 统筹支出,NVL(p3,0),NVL(p1,0),NVL(p2,0) ,medMoney-Profit 药品购进额 FROM ITEMREGISTERTOU WHERE riqi BETWEEN to_date('%s','yyyymmdd') \
			and to_date('%s','yyyymmdd')   ",pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d"));
//AND 发药员 IS NOT NULL
	
		if(! pd->strdoctorbm.IsEmpty())strSql+=" AND doctor='"+pd->strdoctorbm+"'";
		if(!strname.IsEmpty())strSql+=" AND SICKNAME like '"+strname+"%'";
		if( pd->strSFY != "" ) strSql+=" AND 收费员='"+pd->strSFY+"'";
		if( !strGhtype.IsEmpty() ) strSql+=" AND ghtype='"+strGhtype+"'";
	
		if( pd->c_status.GetCurSel() == 0 /*已取药人员*/)
			strSql+=" AND 发药员>0 ";
		else if( pd->c_status.GetCurSel() == 1 /*未取药人员*/)
			strSql+=" AND 收费员>0 AND 发药员 is NULL ";
		


		strSql+=" AND GHTYPE in ('基本保险','特定门诊') ORDER BY riqi,ghtype";
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		
		row=1;
		double dd;
		unsigned int tx,bk;
		cols=recSet->GetFields()->Count;
	
		while(!recSet->adoEOF){
			col=0;
			price=0;
			for(i=0;i<cols;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				if( i >= cols-COMPUTE_COLS ){
					strSql=str1;
					add[i - (cols-COMPUTE_COLS) ]+=atof(str1);
					if( atof(strSql) != 0 )
						str1.Format("%.2f",atof(strSql));
					else str1.Format(" ");
				}
				if( i == 10 ){
					pf->m_grid.SetCol(i);
					pf->m_grid.SetRow(row);
					pf->m_grid.SetCellBackColor(RGB(248,135,244));
				}
				if( i == 13 ){
					pf->m_grid.SetCol(i);
					pf->m_grid.SetRow(row);
					pf->m_grid.SetCellBackColor(RGB(0,128,64));
				}
				if( i == 0 )
					str1.Format("%ld",row);
				
				pf->m_grid.SetMergeRow(row,false);
				pf->m_grid.SetTextMatrix(row,col++,str1);
			}
			row++;
			pf->m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
	
		return false;
	}	

	pf->m_grid.SetMergeCells(true);
	pf->m_grid.SetMergeRow(row,1);
	pf->m_grid.SetRow(row);
	pf->m_grid.SetCol(0);
	pf->m_grid.SetCellBackColor(RGB(255,0,0));
	strSql.Format("   共有 %ld 条就诊记录 ",row-1);


	pf->m_grid.SetTextMatrix(row,0,"合计");	
	pf->GetDlgItem(IDC_BUTTON_TO_EXCEL)->SetWindowText(strSql+"         [ 导入 Excel ]");

	for(long count=2;count< cols;count++){
		pf->m_grid.SetCol(count);
		pf->m_grid.SetCellBackColor(RGB(255,128,0));
		if( count >= cols-COMPUTE_COLS ){
			str1.Format("%.2f",add[count-(cols-COMPUTE_COLS)]);
			pf->m_grid.SetTextMatrix(row,count,str1);	

		//	add[i-CALC_START]+=atof(str1); //从药品数量开始到利润共七列
		}
		else {
			pf->m_grid.SetTextMatrix(row,count,strSql);	
		}
	}
	pf->m_grid.SetRedraw(true);
	
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

	pd->SendMessage(WM_CLOSE,NULL,NULL);
}

BOOL CQueryIC::OnInitDialog()
{
	CDialogGhQuery::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE2)->SetWindowText("基本保险就诊查询");
	return true;


}
