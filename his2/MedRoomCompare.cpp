// MedRoomCompare.cpp: implementation of the CMedRoomCompare class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "MedRoomCompare.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMedRoomCompare::CMedRoomCompare()
{

}

CMedRoomCompare::~CMedRoomCompare()
{

}

BOOL CMedRoomCompare::OnInitDialog()
{
	CDialog::OnInitDialog();
	const CString strTitle="各药房药品对比表";
	fontTitle.CreatePointFont(200,"宋体");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);	
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	SetWindowText(strTitle);

	GetDlgItem(IDC_DATETIMEPICKER1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATETIMEPICKER2)->ShowWindow(SW_HIDE);
	
	CRect rt1;
	GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	GetDlgItem(IDC_COMBO1)->MoveWindow(rt1);
	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_DATETIMEPICKER2)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	GetDlgItem(IDC_EDIT1)->MoveWindow(rt1);
	GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC1)->SetWindowText("条  件");
	GetDlgItem(IDC_STATIC2)->SetWindowText("数  量");

	CString strSql;
	try{
		strSql.Format("select kfbm,kfmc from storeroom where med='1' ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
		
			strSql=(char*)_bstr_t(recSet->GetCollect("kfbm").vt==VT_NULL?" ":recSet->GetCollect("kfbm"));
			if( strSql == LoginInformation.kfbm ) goto CONTINUE;
			strBm.Add(strSql);
			
			strSql=(char*)_bstr_t(recSet->GetCollect("kfmc").vt==VT_NULL?" ":recSet->GetCollect("kfmc"));
			strMc.Add(strSql);

		CONTINUE:
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
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control

}
#define BK1 RGB(23,169,232)
#define BK2 RGB(244,196,251)
#define BK3 RGB(22,154,68)

void CMedRoomCompare::OnOK()
{
	SetGridHead();
	CString strSql,str1,strtemp;
	long cols,row,i,col;
	double d1;
	long flag;

	GetDlgItem(IDC_EDIT1)->GetWindowText(strtemp);
	d1=atof(strtemp);
	flag=((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();

	for(i=0 ; i < strMc.GetSize() ; i ++ ){
		m_grid.SetTextMatrix(0,6+i,strMc.GetAt(i) ); //第六列起为各库房药品
		m_grid.SetColWidth(6+i,1300);
	}

	try{

		strSql.Format(" ( SELECT ypbm,SUM( DECODE(kfbm,'%s',sl,0) ) SCURRENT ,",LoginInformation.kfbm );
	
		for( i=0 ;i < strBm.GetSize() ; i++ ){

			str1.Format(" SUM( DECODE(kfbm,'%s',sl,0) ) S%d ",strBm.GetAt(i),i );
			if( i+1 != strBm.GetSize() ) strSql+=str1+",";
			else strSql+=str1;
		}
		strSql+=" FROM medlie GROUP BY YPBM ) TA,MEDCODE TB WHERE TA.ypbm=TB.bm " ;

		str1.Format("SELECT  BM,mc,gg,dw,SCURRENT,");

		for(i =0 ;i <strBm.GetSize() ; i++ )
		{
			strtemp.Format("S%d",i);
			if ( i +1 == strBm.GetSize() )str1+=strtemp; 
			else	str1+=strtemp+",";

		}

		str1+=" FROM ";
		str1+=strSql;
	
		strtemp.Format("%.2f",d1);
		if( flag == 0 )	str1+=" AND SCURRENT < "+strtemp;
		else if( flag == 1) str1+=" AND SCURRENT > "+strtemp;
		else if ( flag == 2) str1+=" AND SCURRENT = "+strtemp;		

		str1+=" ORDER BY dlbm,xlbm,mc ";
//	AfxMessageBox(str1);
		
		recSet->Open(_bstr_t(str1),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		cols=recSet->GetFields()->Count;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			str1.Format("%ld",row);
			m_grid.SetTextMatrix(row,col++,str1);
			m_grid.SetRow(row);
			m_grid.SetCol(6);
			m_grid.SetCellBackColor(BK1);
			m_grid.SetCol(7);
			m_grid.SetCellBackColor(BK2);
		//	m_grid.SetCol(8);
		//	m_grid.SetCellBackColor(BK3);
			for(i=0;i<cols;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				m_grid.SetTextMatrix(row,col++,str1);
				
			//	if( i>=CALC_START && i<CALC_END )add[i-CALC_START]+=atof(str1); //从药品数量开始到利润共七列
			}
			row++;
			m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();
		m_grid.SetRedraw(true);

		str1.Format("总计:  %ld 条药品",row-1 );
		GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(str1);

	//	m_grid.RemoveItem(row);
	}
	catch(_com_error e)
	{
		AfxMessageBox(str1);
		recSet->Close();
	
		return;
	}

}

void CMedRoomCompare::SetGridHead()
{
	CString HeadTitle[]={"编号","药品编码","药品名称","规格","单位",LoginInformation.kfmc,"药房1","药房2","药房3","药房4","药房5","6","7"} ;//共 8 列
	//						1		2			3				5			7				9				11
	long  headWidth[]={1000,1200,2200,1600,800,1200,00,00,00,00,00,00,0,0,00,00,00,00,00,1400};
	
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetRedraw(false);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
//		if(count>15)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
//		if(count<4)m_grid.SetColAlignment(i,1);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
}

void CMedRoomCompare::OnDblClickMshflexgrid1()
{

}
