// RelateConsumeList.cpp: implementation of the CRelateConsumeList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "RelateConsumeList.h"
#include "progressIndicate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRelateConsumeList::CRelateConsumeList()
{

}

CRelateConsumeList::~CRelateConsumeList()
{

}

void CRelateConsumeList::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryConsume;
	pg.DoModal();

}

UINT CRelateConsumeList::QueryConsume(LPVOID ps)
{
	CRelateConsumeList * pd=(CRelateConsumeList * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);
	pd->SetGridHead();
	CString strSql,str1,str2,str3;
	long cols,row,i,col;
	double add[]={0,0,0,0,0,0,0,0,0};
	const int START_COMPUTE=5; //在SQL语句中
	pd->UpdateData();
	CComboBox *pc=(CComboBox*)pd->GetDlgItem(IDC_COMBO1);
	try{
		strSql.Format("SELECT * FROM V_RELATE_CONSUME ");
	
		pd->c_edit1.GetWindowText(str1); //卡号
		if( !str1.IsEmpty() ) strSql+=" WHERE  bm like '"+str1+"%'";
		pd->c_edit3.GetWindowText(str2); //姓名
		if ( !str2.IsEmpty() ){
			if( str1.IsEmpty() )
			strSql+=" WHERE xm like '"+str2+"%'";
			else			
			strSql+=" AND xm like '"+str2+"%'";
		
		}
		if(pc->GetCurSel() != 0 && pc->GetCurSel() != CB_ERR ) 
		{
			pc->GetLBText(pc->GetCurSel(),str3);
			if( str1.IsEmpty() && str2.IsEmpty() )strSql+=" WHERE xingzhi='"+str3+"'";
			else strSql+=" AND xingzhi='"+str3+"'";
		}
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		cols=recSet->GetFields()->Count;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			str1.Format("%ld",row);
			pd->m_grid.SetTextMatrix(row,col++,str1);
			pd->m_grid.SetRow(row);
			pd->m_grid.SetCol(6);
			pd->m_grid.SetCellBackColor(BK1);
	/*		pd->m_grid.SetCol(9);
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
	pd->m_grid.SetRedraw(true);
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
}

void CRelateConsumeList::SetGridHead()
{
	CString HeadTitle[]={"序号","编码","姓名","性别","年龄","供养性质","上年余额","本年充值","外诊报销","本院消耗","帐户剩余"} ;//共 7 列
	
	long  headWidth[]={800,1000,900,400,500,1300,1000,1000,1000,1100,1000,1000,1000,1000,1000,1600,1300,1300,1300,0,1300,1300,1300,00,00,1400};
	
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetFixedCols(0l);
	m_grid.SetRedraw(false);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<4){
			m_grid.SetMergeCol(i,true);// 前6列单元格进行合
			m_grid.SetColAlignment(i,4);
		}
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}

}

BOOL CRelateConsumeList::OnInitDialog()
{
	CComboBox * pc=(CComboBox*)GetDlgItem(IDC_COMBO1);
	CDoctorWorkLoad::OnInitDialog();
	CenterWindow();
	GetDlgItem(IDC_STATIC1)->SetWindowText("卡号");
	GetDlgItem(IDC_STATIC2)->SetWindowText("姓名");
	GetDlgItem(IDC_STATIC_1)->SetWindowText("供养性质");
	GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_DATETIMEPICKER1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATETIMEPICKER2)->ShowWindow(SW_HIDE);

	CRect rt1;
	GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	c_edit1.MoveWindow(rt1);
	c_edit1.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DATETIMEPICKER2)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	c_edit3.MoveWindow(rt1);
	c_edit3.ShowWindow(SW_SHOW);
	
	pc->ShowWindow(SW_SHOW);
	pc->ResetContent();
	pc->AddString("");
	pc->AddString("双职工子女");
	pc->AddString("单职工子女");
	pc->AddString("职工父母");
	pc->AddString("职工配偶");
	pc->SetCurSel(0);
	
	OnOK();

	return true;
}
