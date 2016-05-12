// BreadMedQuery.cpp: implementation of the CBreadMedQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "BreadMedQuery.h"
#include "breadMedList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBreadMedQuery::CBreadMedQuery()
{

}

CBreadMedQuery::~CBreadMedQuery()
{

}

void CBreadMedQuery::OnOK()
{
	CBreadMedList * pf=(CBreadMedList *)theApp.pParentGrid.pWnd;
	pf->SetGridHead();
	UpdateData();
	CString strSql,strTemp;
	long cc,row,i,cols;
	double add[9]={0.,.0,.0,0,0,0,0,0,0};
	try{

//		CString HeadTitle[]={"DAN","日期","库房","操作员","药品名称","规格","单位","生产期","有效期",\
//		"产地","进价","报损量","损耗额' beizhu}; 

		strSql.Format("SELECT a.danjuhao,a.riqi,d.kfmc,a.operator,c.bm,c.mc,c.gg,c.dw,b.rq1,\
			b.rq2,b.factory,b.selldj,b.sl,b.selldj*b.sl,a.beizhu	FROM 报废表 a,itemti b,medcode c,\
			storeroom d  WHERE a.riqi BETWEEN \
			to_date('%s','yyyymmdd') AND to_date('%s','yyyymmdd') AND a.danjuhao=b.danjuhao \
			AND b.ypbm= c.bm AND b.kfbm= d.kfbm",m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d") );
		c_py.GetWindowText(strTemp);
		strTemp.Remove(' ');
		if(!strTemp.IsEmpty())strSql+=" and C.Py like '"+strTemp+"%'";
	//	c_gys.GetWindowText(strTemp);
	//	if(!strTemp.IsEmpty())strSql+=" and d.GONGMC='"+strTemp+"'";
		c_editFactory.GetWindowText(strTemp);
		strTemp.Remove(' ');
		if(! strTemp.IsEmpty() ) strSql+=" AND b.factory ='"+strTemp+"'";
		
		c_editRky.GetWindowText(strTemp);
		if( ! strTemp.IsEmpty() ) strSql+=" AND a.operator='"+strTemp+"'";
	
		c_editYpbm.GetWindowText(strTemp);
		strTemp.Remove(' ');
		if(! strTemp.IsEmpty() )strSql+=" AND c.bm like '"+strTemp+"%'";
		
		strSql+=" ORDER BY a.RIQI,c.dlbm,c.xlbm,c.mc ";

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
				if(cc == cols-3 )add[0]+=atof(strSql); 
				if(cc == cols-2 )add[1]+=atof(strSql);
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
	pf->m_grid.SetTextMatrix(row,1,"合计");	
	pf->GetDlgItem(IDC_BUTTON_TO_EXCEL)->SetWindowText(strSql+"         [ 导入 Excel ]");

	for(int count=2;count<cols-2; count++){
		pf->m_grid.SetTextMatrix(row,count,strSql);	
		pf->m_grid.SetCol(count);
		pf->m_grid.SetCellBackColor(RGB(255,128,0));

	}
	strSql.Format("%.2f",add[0]);
	pf->m_grid.SetTextMatrix(row,cols-3,strSql);
	strSql.Format("%.2f",add[1]);
	pf->m_grid.SetTextMatrix(row,cols-2,strSql);
	

	CDialog::OnOK();
}

BOOL CBreadMedQuery::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowText("损耗药品查询");
	CRect rt1,rtGys;
	GetDlgItem(IDC_EDIT_GYS)->GetWindowRect(rtGys);
	ScreenToClient(rtGys);

	GetDlgItem(IDC_COMBO1)->GetWindowRect(rt1);
	ScreenToClient(rt1);
//	rt1.right =rt1.left+ rtGys.right-rtGys.left ;
	GetDlgItem(IDC_EDIT_YPBM)->MoveWindow(rt1);

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


	GetDlgItem(IDC_STATIC_2)->SetWindowText("操作员");
	GetDlgItem(IDC_STATIC_3)->SetWindowText("药品编码");
	GetDlgItem(IDC_STATIC_4)->SetWindowText("产地");

	GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_EDIT_FACTORY)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_BUTTON_FACTORY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_RKY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_RKY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_YPBM)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_EDIT_GYS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_GYS)->ShowWindow(SW_HIDE);

	return true;
}
