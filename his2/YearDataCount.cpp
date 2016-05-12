

#include "stdafx.h"
#include "his2.h"
#include "YearDataCount.h"
#include "progressIndicate.h"
#include "ChartYearDataCount.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CYearDataCount::CYearDataCount()
{
	strConstName=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_Title_list WHERE ds2='DIALOG' AND ds3='TITLE' \
		AND ds4='AAB' ");

	strTitle=strConstName;
}

CYearDataCount::~CYearDataCount()
{

}

BOOL CYearDataCount::OnInitDialog()
{
	CDoctorWorkLoad::OnInitDialog();
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATETIMEPICKER1)->ShowWindow(SW_HIDE);
	
	GetDlgItem(IDC_DATETIMEPICKER2)->ShowWindow(SW_HIDE);
	pbox2=(CComboBox*)GetDlgItem(IDC_COMBO2);
	CRect r1;
	GetDlgItem(IDC_DATETIMEPICKER2)->GetWindowRect(r1);
	ScreenToClient(r1);
	pbox2->MoveWindow(r1);
	pbox2->ShowWindow(SW_SHOW);
	CString strTmp;
	for( int i=m_date2.GetYear() ; i > m_date2.GetYear() -5 ; i-- )
	{
		strTmp.Format("%d",i);
		pbox2->AddString(strTmp);
	}
	pbox2->SetCurSel(0);



	GetDlgItem(IDC_STATIC2)->SetWindowText("��ѯ���");
	
	SetGridHead();
	return true;
}

void CYearDataCount::SetGridHead()
{
	CString HeadTitle[]={"���","�������","һ��","����","����","����","����","����","����","����","����","ʮ��","ʮһ��","ʮ����","�� ��"} ;//�� 8 ��
	
//	long  headWidth[]={800,1000,1000,1000,1000,1000,1100,1000,1000,1000,1000,1000,1600,1300,1300,1300,0,1300,1300,1300,00,00,1400};
	
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetRedraw(false);
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(2);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //���ж���
		m_grid.SetColWidth(i,1000);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
	m_grid.SetColWidth(0,600); //��һ��

	m_grid.SetRedraw(true);
}

void CYearDataCount::OnOK()
{
	UpdateData();
	
	strTitle.Format("%d���%s",m_date2.GetYear(),strConstName);
	
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryYearData;
	pg.DoModal();

}

UINT CYearDataCount::QueryYearData(LPVOID ps)
{
	CYearDataCount * pd=(CYearDataCount * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);
	pd->SetGridHead();
	CString strSql,str1;
	long cols,row,i,col;
	double add[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	const int START_COMPUTE=1; //��SQL�����
	pd->UpdateData();
	try{
		strSql="SELECT ghtype,";
		for( i=0 ;i<12 ;i++)
		{
			str1.Format(" SUM( DECODE(to_number(to_char(riqi,'mm'),'99'),%d,MedMoney+treateMoney,0) ), ",i+1 );
			strSql+=str1;
		}
		strSql+=" SUM(treateMoney+MedMoney) FROM ItemRegisterTou ";
		str1.Format(" WHERE riqi between to_date('%s'||'0101','yyyymmdd') and to_date('%s'||'1231','yyyymmdd') \
			group by ghtype ",pd->m_date2.Format("%Y"),pd->m_date2.Format("%Y"));
		strSql+=str1;
		
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

//		str1.Format("�ܼ�: ��ɹ� %ld ��ҩƷ",row-1 );
//		pd->GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(str1);
		pd->m_grid.SetMergeCells(true);
		pd->m_grid.SetMergeRow(row,1); 
		pd->m_grid.SetRow(row);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("%ld����¼ ",row-1);
		pd->m_grid.SetTextMatrix(row,0,"�ϼ�");	
		
		
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
	
		return false;
	}	
	pd->m_grid.SetRedraw(true);
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
}

void CYearDataCount::OnDblClickMshflexgrid1()
{
	UpdateData();
	long rows=m_grid.GetRows(),row=m_grid.GetRow();
	if( rows == 2 || row == 0 ) return ;
	
	CChartYearDataCount vi;

	vi.dateConsume=m_date3;
	vi.strYpbm=m_grid.GetTextMatrix(row,1); //ҩƷ����
	vi.effectCols=m_grid.GetCols(0)-3 ;
	vi.strName.Format("%d��� (%s) �����Ľ������ͼ ��λ:Ԫ",m_date2.GetYear(),m_grid.GetTextMatrix(row,1));

	for ( int i=0 ; i < vi.effectCols ; i++ )
	{
		vi.iData[i]=atof( m_grid.GetTextMatrix(row,i+2) );
	}
	vi.DoModal();
}
void CYearDataCount::OnSelchangeCombo2()
{
	CString strTmp;
	pbox2->GetLBText(pbox2->GetCurSel(),strTmp);
	m_date2.SetDate(atoi(strTmp),1,1);
	UpdateData(false);



}