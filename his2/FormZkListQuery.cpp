// FormZkListQuery.cpp: implementation of the CFormZkListQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "FormZkListQuery.h"
#include "formZkList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFormZkListQuery::CFormZkListQuery()
{

}

CFormZkListQuery::~CFormZkListQuery()
{

}

void CFormZkListQuery::OnOK()
{
//	CString HeadTitle[]={"DAN","日期","始库房","终库房","领用员","发药员","药品名称","规格","单位","生产期","有效期",\
//		"产地","转库量","售价"}; 
	CFormZkList * pf=(CFormZkList *)theApp.pParentGrid.pWnd;
	pf->SetGridHead();
	UpdateData();
	CString strSql,strTemp;
	long cc,row,cols,i;
	double add[8]={0.,.0,.0,0,0,0,0,0};
	pf->m_grid.SetRedraw( false);
	
	try{
/*		strSql.Format("SELECT b.DANJUHAO,b.RIQI,T1.KFMC,B.发料员名,T2.KFMC,B.领料员名,\
				c.MC,C.GG,c.DW,a.RQ1,a.RQ2,a.FACTORY,A.SL,a.DJ \
				FROM ITEMTI a,ITEMZKTOU b,MEDCODE c,\
				STOREROOM T1,STOREROOM T2,MEDDL d,MEDXL e \
				WHERE a.DANJUHAO=b.DANJUHAO and a.YPBM=c.BM AND C.DLBM=D.DLBM \
				AND T1.KFBM=b.BFKF and T2.KFBM=B.DFKF and C.XLBM=\
				E.XLBM and D.DLBM=E.DLBM and b.riqi between to_date('%s','yyyymmdd') and \
				to_date('%s','yyyymmdd')  ",m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d") );
*/
		strSql.Format("SELECT b.DANJUHAO,b.RIQI,T1.KFMC,B.发料员名,T2.KFMC,B.领料员名,\
				c.BM,c.MC,C.GG,c.DW,a.RQ1,a.RQ2,a.FACTORY,A.SL,a.SellDJ,a.sl*a.selldj \
				FROM ITEMTI a,ITEMZKTOU b,MEDCODE c,\
				STOREROOM T1,STOREROOM T2 \
				WHERE a.DANJUHAO=b.DANJUHAO and a.YPBM=c.BM  \
				AND T1.KFBM=b.BFKF and T2.KFBM=B.DFKF  and b.riqi between to_date('%s','yyyymmdd') and \
				to_date('%s','yyyymmdd')  ",m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d") );		

		if(!(c_combo1.GetCurSel() == CB_ERR || c_combo1.GetCurSel()== 0) ){
			c_combo1.GetLBText(c_combo1.GetCurSel(),strTemp);
			strSql+=" AND T1.KFMC='"+strTemp+"'";
		}
		if(!(c_combo2.GetCurSel() == CB_ERR || c_combo2.GetCurSel()== 0) ){
			c_combo2.GetLBText(c_combo2.GetCurSel(),strTemp);
			strSql+=" AND T2.KFMC='"+strTemp+"'";
		}
		c_py.GetWindowText(strTemp);
		strTemp.Remove(' ');
		if(! strTemp.IsEmpty() ) strSql+=" AND C.PY like '"+strTemp+"%'";
		strSql+=" ORDER BY B.RIQI";
				
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		cols=recSet->GetFields()->Count;
	
		while(!recSet->adoEOF){
			i=0;
			for(cc=0;cc<cols;cc++)
			{
				
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(cc))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(cc))->Value);
				pf->m_grid.SetTextMatrix(row,cc,strSql);
				if(cc>=cols-3)add[i++]+=atof(strSql);
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

	for(int count=2;count<cols;count++){
		pf->m_grid.SetTextMatrix(row,count,strSql);	
		pf->m_grid.SetCol(count);
		pf->m_grid.SetCellBackColor(RGB(255,128,0));

	}

	for(i=0;i<3;i++){
		strSql.Format("%.2f",add[i]);
		pf->m_grid.SetTextMatrix(row,cols-3+i,strSql);
	}

	pf->m_grid.SetRedraw(true);

	
	CDialog::OnOK();
}

BOOL CFormZkListQuery::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowText("转库药品查询条件");
	GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_HIDE);
	c_gys.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_GYS)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
	c_combo1.ShowWindow(SW_SHOW);
	c_combo2.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_3)->SetWindowText("起始库房");
	GetDlgItem(IDC_STATIC_4)->SetWindowText("目的库房");
	CString strSql;
	try{
		strSql.Format("select distinct(kfmc) from storeroom  ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		c_combo1.AddString("");
		c_combo2.AddString("");
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetCollect("kfmc").vt==VT_NULL?" ":recSet->GetCollect("kfmc"));
			c_combo1.AddString(strSql);
			c_combo2.AddString(strSql);
			recSet->MoveNext();

		
		}
		recSet->Close();
		


	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}
	return true;
}
