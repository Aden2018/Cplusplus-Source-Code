// ResidePriceQuery.cpp: implementation of the CResidePriceQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "ResidePriceQuery.h"
#include "ProgressIndicate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResidePriceQuery::CResidePriceQuery()
{

}

CResidePriceQuery::~CResidePriceQuery()
{

}

BOOL CResidePriceQuery::OnInitDialog()
{
	CGenericStockMed::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	SetWindowText(strTitle);
	
	OnOK();
	CenterWindow();
	return true;

}

void CResidePriceQuery::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryAddPrice;
	pg.DoModal();

}

void CResidePriceQuery::SetGridHead()
{
	CString HeadTitle[]={"序号","日期","操作人","上次余额","交款金额"} ;//共 8 列
	
	long  headWidth[]={800,2000,1000,1200,1200};
	long iCols=sizeof(HeadTitle)/sizeof(CString);
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetRedraw(false);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(false); //设定单元格可以进行合并
	m_grid.SetCols(iCols);
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count< iCols;count++){
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
	m_grid.SetRedraw(false);
	m_grid.SetSelectionMode(1);//按行选择
	
}

UINT CResidePriceQuery::QueryAddPrice(LPVOID ps)
{
	CResidePriceQuery * pd=(CResidePriceQuery * )((CProgressIndicate *)ps)->pDialog;

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
		strSql.Format(" SELECT d1,n2,p1,p2 FROM lsq_reside_price_log WHERE c1='%s' ORDER BY d1 ",pd->strSerial);//,pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d") );
		
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
				if( i== cols-1 )add[0]+=atof(str1); 
			}
	
			row++;
			pd->m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();
		}
		recSet->Close();

		pd->m_grid.SetTextMatrix(row,0,"合计");	
		str1.Format("%.2f",add[0]);
		pd->m_grid.SetTextMatrix(row,cols,str1);
		

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
