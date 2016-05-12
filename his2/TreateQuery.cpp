// TreateQuery.cpp: implementation of the CTreateQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "TreateQuery.h"
#include "progressIndicate.h"
#include "treateList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTreateQuery::CTreateQuery()
{

}

CTreateQuery::~CTreateQuery()
{

}

void CTreateQuery::OnOK()
{
	CProgressIndicate pq;
	pq.pDialog= this;
	pq.pThreadFunction = TreateQuery;

	pq.DoModal();

}

UINT CTreateQuery::TreateQuery(LPVOID ps)
{

	CTreateList *pf=(CTreateList*)theApp.pParentGrid.pWnd;
	CTreateQuery * pd =(CTreateQuery *) ((CProgressIndicate *) ps )->pDialog ;

	pd->UpdateData();

	pf->m_grid.SetRedraw(false);
	pf->SetGridHead();
	CString strSql,str1,strGhtype,strname;
	
	const int COMPUTE_COLS= 11 ;
	long row,col,i,cols;
	double price(0),add[]={0,0,0,0,0,0,0,0,0,0,0,0,0};
	//后面共要统计七列
	if( pd->c_type.GetCurSel()==CB_ERR || pd->c_type.GetCurSel() == 0 )strGhtype = "";
	else {
		pd->c_type.GetLBText(pd->c_type.GetCurSel(),strGhtype);
		if( strGhtype == "国前职工" ) strGhtype="建国前老工人";

	}
	pd->c_name.GetWindowText(strname);
	strname.Remove(' ');

	try{
		//共14列查询
		strSql.Format("SELECT b.danjuhao,to_char(min(riqi),'yyyy-mm-dd') xx ,min(sickname),min(doctorname),\
			min(挂号员名) ,min(划价员名) ,min(收费员名) ,min( ghtype ) ,\
			sum(decode(费用大类,'治疗费',b.dj,NULL )) c1,\
			sum(decode(费用大类,'手术费',b.dj,NULL )) c2,\
			sum(decode(费用大类,'化验费',b.dj,NULL )) c3,\
			sum(decode(费用大类,'B 超费',b.dj,NULL )) c4,\
			sum(decode(费用大类,'心电费',b.dj,NULL )) c5,\
			sum(decode(费用大类,'理疗费',b.dj,NULL )) c6,\
			sum(decode(费用大类,'推拿费',b.dj,NULL )) c7,\
			sum(decode(费用大类,'口腔费',b.dj,NULL )) c8,\
			sum(decode(费用大类,'妇检费',b.dj,NULL )) c9,\
			sum(decode(费用大类,'眼  科',b.dj,NULL )) c10,\
			max(nvl(treatemoney,NULL)) \
		FROM itemregistertizl b,费用项目表 c,itemregistertou x  where \
			b.zlmc=c.费用编码 and b.danjuhao=x.danjuhao \
			and x.riqi between to_date(%s,'yyyymmdd') AND to_date(%s,'yyyymmdd') \
			AND x.treatemoney != 0 ",pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d"));

		if(! pd->strdoctorbm.IsEmpty())strSql+=" AND doctor='"+pd->strdoctorbm+"'";
		if(! strGhtype.IsEmpty())strSql+=" AND GHTYPE='"+strGhtype+"'";
		if(!strname.IsEmpty())strSql+=" AND SICKNAME like '"+strname+"%'";
		if( pd->strSFY != "" ) strSql+=" AND 收费员='"+pd->strSFY+"'";
	
		if( pd->c_status.GetCurSel() == 0 /*已取药人员*/)
			strSql+=" AND 发药员>0 ";
		else if( pd->c_status.GetCurSel() == 1 /*未取药人员*/)
			strSql+=" AND 收费员>0 AND 发药员 is NULL ";

		
		strSql+=" GROUP BY b.danjuhao ORDER BY xx ";
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		
		row=1;
//		double dd;
//		unsigned int tx,bk;
		cols=recSet->GetFields()->Count;

		while(!recSet->adoEOF){
			col=0;
			price=0;
			for(i=0;i<cols;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);

				if( i >= cols-COMPUTE_COLS ){
					add[i - (cols-COMPUTE_COLS) ]+=atof(str1);
					strSql=str1;
					if( atof(strSql) != 0. )
						str1.Format("%.2f",atof(strSql));

				}

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

	pf->m_grid.SetMergeRow(row,1);
	pf->m_grid.SetRow(row);
	pf->m_grid.SetCol(1);
	pf->m_grid.SetCellBackColor(RGB(255,0,0));
	strSql.Format("   共有 %ld 条就诊记录 ",row-1);


	pf->m_grid.SetTextMatrix(row,1,"合计");	
	pf->GetDlgItem(IDC_BUTTON_TO_EXCEL)->SetWindowText(strSql+"         [ 导入 Excel ]");

	for(long count=2;count< cols;count++){
		pf->m_grid.SetCol(count);
		pf->m_grid.SetCellBackColor(RGB(255,128,0));
		if( count >= cols-COMPUTE_COLS ){
			str1.Format("%.2f",add[count-(cols-COMPUTE_COLS)]);
			pf->m_grid.SetTextMatrix(row,count,str1);	

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

BOOL CTreateQuery::OnInitDialog()
{
	CDialogGhQuery::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE2)->SetWindowText("治疗明细表查询");
	return true;
}
