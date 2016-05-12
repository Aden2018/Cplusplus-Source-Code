// ResideUseMedQuery.cpp: implementation of the CResideUseMedQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "ResideUseMedQuery.h"
#include "ProgressIndicate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResideUseMedQuery::CResideUseMedQuery()
{

}

CResideUseMedQuery::~CResideUseMedQuery()
{

}

BOOL CResideUseMedQuery::OnInitDialog()
{
	CGenericStockMed::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	SetWindowText(strTitle);
	
	OnOK();
	CenterWindow();
	return true;

}

void CResideUseMedQuery::SetGridHead()
{
	CString HeadTitle[]={"序号","单据","医生","划价","发药","日期","药品编码","药品名称","规格","单位","产地","有效期","单价","数量","金额",} ;//共 8 列
	
	long  headWidth[]={800,0,800,800,800,1800,900,1400,1200,300,1200,1200,700,700,1400,1300,1300,0,1300,1300,1300,00,00,1400};
	
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetRedraw(false);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<6){
			m_grid.SetMergeCol(i,true);// 前6列单元格进行合
			m_grid.SetColAlignment(i,4); 
		}
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
	m_grid.SetRedraw(false);
	m_grid.SetSelectionMode(1);


}

void CResideUseMedQuery::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryUseMed;
	pg.DoModal();

}

UINT CResideUseMedQuery::QueryUseMed(LPVOID ps)
{
	CResideUseMedQuery * pd=(CResideUseMedQuery * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);
	pd->SetGridHead();
	CString strSql,str1;
	long cols,row,i,col;
	double add[]={0,0,0,0,0,0,0,0,0};
	const int START_COMPUTE=2; //在SQL语句中
	COLORREF bc[2]={RGB(255,255,255),RGB(69,135,224)};
	COLORREF fc[2]={RGB(0,0,0),RGB(255,255,255)};
	unsigned long color,fcolor;
	pd->UpdateData();
	try{
		strSql.Format(" select a.s2,a.y2,a.n1,a.n2 ,a.r1,c.bm,c.mc,c.gg,c.dw,b.factory,to_char(b.rq2 ,'yyyy-mm-dd'),b.dj,b.sl,b.Sl*b.DJ from \
			lsq_reside_hos_huajia_complete  a,itemti b,medcode c \
			 where a.s2=b.danjuhao and b.ypbm=c.bm and a.s1='%s' \
			   union \
			 select d.s2,d.y2,d.n1,d.n2,d.r1,e.zlmc,f.费用大类,f.费用名称,'','','',e.dj,1,e.dj  from \
			 lsq_reside_hos_huajia_complete d,itemregistertizl e,费用项目表 f  where \
			  d.s2=e.danjuhao and e.zlmc=f.费用编码 and d.s1='%s'  order by r1,s2 ",pd->strSerial,pd->strSerial);//,pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d") );
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		cols=recSet->GetFields()->Count;
		CString oldStr="",strNew;
		while(!recSet->adoEOF){
			col=0;
			str1.Format("%ld",row);
			pd->m_grid.SetTextMatrix(row,col++,str1);
	
			for(i=0;i<cols;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				pd->m_grid.SetTextMatrix(row,col++,str1);
				if( i == 1 ) strNew= str1 ;
				if( i== cols-1 )add[0]+=atof(str1); 
			}
			if( oldStr != strNew ) {
				oldStr=strNew ;
				if( color == bc[0] ){
					color=bc[1];
					fcolor=fc[1];
				}
				else {
					color=bc[0];
					fcolor=fc[0];
				}
			}
			pd->m_grid.SetRow(row);
			for( i=5; i < cols+1 ; i++ ){
					pd->m_grid.SetCol(i);	
					pd->m_grid.SetCellBackColor(color);
					pd->m_grid.SetCellForeColor(fcolor);
			}
				
	
			row++;
			pd->m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();
		}
		recSet->Close();

		pd->m_grid.SetTextMatrix(row,0,"合计");	
		str1.Format("%.2f",add[0]);
		pd->m_grid.SetTextMatrix(row,cols,str1);
		
/*		
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
*/
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
}
