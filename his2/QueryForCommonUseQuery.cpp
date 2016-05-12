// QueryForCommonUseQuery.cpp: implementation of the CQueryForCommonUseQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "QueryForCommonUseQuery.h"
#include "CommonUseQuery.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQueryForCommonUseQuery::CQueryForCommonUseQuery()
{

}

CQueryForCommonUseQuery::~CQueryForCommonUseQuery()
{

}

void CQueryForCommonUseQuery::OnOK()
{
	CCommonUseQuery * pf=(CCommonUseQuery *)theApp.pParentGrid.pWnd;
	pf->SetGridHead();
	UpdateData();
	CString strSql,strTemp;
	long cc,row,i,cols;
	double add[9]={0.,.0,.0,0,0,0,0,0,0};
	try{
/*		strSql.Format("select b.danjuhao ,b.riqi,b.piaojuhao ,D.GONGMC,\
			b.业务员名 ,b.入库员名 ,c.mc,c.gg,c.dw,a.rq1,a.rq2,a.factory ,\
			a.sl , a.dj as jinjia,a.pdj as coach, a.selldj as sellDj ,\
			round(a.dj*a.sl,2) as allJInjia,round(a.pdj*a.sl,2) as AllCoach,\
			round(a.selldj*a.sl,2) as allselldj , round((a.pdj-a.dj)*a.sl,2) as preferential\
			from ITEMTI a,ITEMRKTOU b,MEDCODE c,CODEGYS d,STOREROOM e,\
			MEDDL f,MEDXL g  WHERE   a.danjuhao=b.danjuhao and a.ypbm=c.bm and b.kfbm=e.kfbm and \
			b.gongbm=d.gongbm and c.dlbm=g.dlbm and  c.xlbm=g.xlbm and g.dlbm=f.dlbm\
			and  b.riqi between to_date('%s','yyyymmdd') and \
			to_date('%s','yyyymmdd') ",m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d") );
*/
 //"DAN","日期","发放员","领用员","药品名称","规格","单位","生产期","有效期",\
//		"产地","领用量"}; 
		strSql.Format("SELECT a.danjuhao,a.riqi,a.发料员名,a.领料员名,c.mc,c.gg,c.dw,b.rq1,b.rq2,\
			b.factory,b.sl,b.selldj,b.sl*b.selldj,a.用途 FROM itemck1tou a,itemti b,medcode c WHERE a.riqi BETWEEN \
			to_date('%s','yyyymmdd') AND to_date('%s','yyyymmdd') AND a.danjuhao=b.danjuhao \
			AND b.ypbm= c.bm ",m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d") );
		c_py.GetWindowText(strTemp);
		strTemp.Remove(' ');
		if(!strTemp.IsEmpty())strSql+=" and C.Py like '"+strTemp+"%'";
	//	c_gys.GetWindowText(strTemp);
		c_editFactory.GetWindowText(strTemp);
		strTemp.Remove(' ');
		if(! strTemp.IsEmpty() ) strSql+=" AND b.factory ='"+strTemp+"'";
		c_editYwy.GetWindowText(strTemp);
		strTemp.Remove(' ');
		if(! strTemp.IsEmpty() ) strSql+= " AND a.领料员名='"+strTemp+"'";
		
		c_editRky.GetWindowText(strTemp);
		if( ! strTemp.IsEmpty() ) strSql+=" AND a.发料员名='"+strRkyID+"'";
	
		c_editYpbm.GetWindowText(strTemp);
		strTemp.Remove(' ');
		if(! strTemp.IsEmpty() )strSql+=" AND c.bm like '"+strTemp+"%'";
		
		strSql+=" ORDER BY a.RIQI ";
	//	if(!strTemp.IsEmpty())strSql+=" and d.GONGMC='"+strTemp+"'";
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		cols=recSet->GetFields()->Count;
		double dX;
		while(!recSet->adoEOF){
			i=0;
			for(cc=0;cc<cols;cc++)
			{
				
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(cc))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(cc))->Value);
				pf->m_grid.SetTextMatrix(row,cc,strSql);
				if(cc == cols-2 )add[0]+=atof(strSql);
				if(cc == cols-3 )add[1]+=atof(strSql);
				if(cc == cols-4 )add[2]+=atof(strSql);
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
		return;
	}

	pf->m_grid.SetMergeRow(row,1);
	pf->m_grid.SetRow(row);
	pf->m_grid.SetCol(1);
	pf->m_grid.SetCellBackColor(RGB(255,0,0));
	strSql.Format("   共有 %ld 条药品记录 ",row-1);
	pf->GetDlgItem(IDC_BUTTON_TO_EXCEL)->SetWindowText(strSql+"     [ 导出 Excel ]");

	pf->m_grid.SetTextMatrix(row,1,"合计");	

	for(int count=2;count<cols-2;count++){
		pf->m_grid.SetTextMatrix(row,count,strSql);	
		pf->m_grid.SetCol(count);
		pf->m_grid.SetCellBackColor(RGB(255,128,0));

	}
	strSql.Format("%.2f",add[0]);
	pf->m_grid.SetTextMatrix(row,cols-2,strSql);
	strSql.Format("%.2f",add[1]);
	pf->m_grid.SetTextMatrix(row,cols-3,strSql);
	strSql.Format("%.2f",add[2]);
	pf->m_grid.SetTextMatrix(row,cols-4,strSql);
	

	CDialog::OnOK();
}

BOOL CQueryForCommonUseQuery::OnInitDialog()
{
	CDialog::OnInitDialog();
	CRect rt1,rtGys;
	GetDlgItem(IDC_EDIT_GYS)->GetWindowRect(rtGys);
	ScreenToClient(rtGys);

	GetDlgItem(IDC_COMBO1)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	rt1.right =rt1.left+ rtGys.right-rtGys.left ;
	GetDlgItem(IDC_EDIT_YWY)->MoveWindow(rt1);
/*
	GetDlgItem(IDC_COMBO2)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	rt1.right =rt1.left+ rtGys.right-rtGys.left;
	GetDlgItem(IDC_EDIT_FACTORY)->MoveWindow(rt1);
*/
	GetDlgItem(IDC_COMBO2)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	rt1.right =rt1.left+ rtGys.right-rtGys.left;
	GetDlgItem(IDC_EDIT_FACTORY)->MoveWindow(rt1);

	GetDlgItem(IDC_EDIT_GYS)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	GetDlgItem(IDC_EDIT_RKY)->MoveWindow(rt1);

	GetDlgItem(IDC_BUTTON_GYS)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	GetDlgItem(IDC_BUTTON_RKY)->MoveWindow(rt1);

	GetDlgItem(IDC_STATIC_3)->SetWindowText("领用员");
	GetDlgItem(IDC_STATIC_4)->SetWindowText("产  地");
	GetDlgItem(IDC_STATIC_2)->SetWindowText("发放员");
	// TODO: Add extra initialization here
	GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_YWY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_FACTORY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_YWY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_FACTORY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_RKY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_RKY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_YPBM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_5)->ShowWindow(SW_SHOW);
//	GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_EDIT_GYS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_GYS)->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control

}
