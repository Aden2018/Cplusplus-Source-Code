// EmpBalanceCount.cpp: implementation of the CEmpBalanceCount class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "EmpBalanceCount.h"
#include "PeculiarInput.h"
#include "progress.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/********************************************************************
	desc:
		���䱣�ջ�������,�����ʽ��ϵ���ҽԺ��Ա
	author:
	date:2005/2/24

*********************************************************************/
CEmpBalanceCount::CEmpBalanceCount()
{
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_mixed WHERE ds3='TITLE' AND ds4='AAB' ");

}

CEmpBalanceCount::~CEmpBalanceCount()
{

}

BOOL CEmpBalanceCount::OnInitDialog()
{
	CDoctorWorkLoad::OnInitDialog();

	m_grid.SetRedraw(true);

	pc=(CComboBox*)GetDlgItem(IDC_COMBO1);
	CenterWindow();
	GetDlgItem(IDC_STATIC2)->SetWindowText("ͳ�����");
	CRect rt1;

	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATETIMEPICKER1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATETIMEPICKER2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATETIMEPICKER2)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	rt1.bottom+=200;
	pc->MoveWindow(rt1);
	pc->ShowWindow(SW_SHOW);


	pc->ResetContent();
	CString strTmp;
	int year=COleDateTime::GetCurrentTime().GetYear();
	for(long i=0; i<5; i++ ){
		strTmp.Format("%d",year-i );
		pc->AddString(strTmp);
	}
	pc->SetCurSel(0);

	CString px[]={"������Ŀ","��ְ","����������","����ǰ����","�ϼ�"};
	long pl[]={2400,1600,1600,1600,1600,2000,1500,2200,1000,1000,1000,1000};
	CPeculiarInput::SetGridHead(px,pl,m_grid,sizeof(px)/sizeof(CString),1,0);
	
	return true;
}

void CEmpBalanceCount::OnOK() //��ѯѡ��
{

	CString strSql,str1;
	long year;
	pc->GetLBText(pc->GetCurSel(),str1);
	year=atol(str1);

	CProgress pd;
	pd.flagRun=false; //ָʾ����ǰ�Ƿ񵯳��Ի���
//	pd.strNotify="�Ƿ�ȷ��Ҫ������Ƚ�ת��ֵ,ÿ���ֻ�������һ�γ�ֵ!!!";
	pd.pThreadFunction=CProgress::createBalanceCount;
	pd.strView="���ڽ��в�ѯ,���Ժ�...";
	pd.iYear = year;
	pd.DoModal();

	
	if( pd.flagRun ){
		AfxMessageBox("���ɽ����ʱ����!!!");
		return;
	}

	
	long row,cols,i,col;
	
	m_grid.Clear();
	m_grid.SetRows(2);
	CString px[]={"������Ŀ","��ְ","����������","����ǰ����","�ϼ�"};

	long pl[]={2800,1600,1600,1600,1600,2000,1500,2200,1000,1000,1000,1000};
	CPeculiarInput::SetGridHead(px,pl,m_grid,sizeof(px)/sizeof(CString),1,0);
	
	m_grid.SetColAlignmentFixed(0,1); //���о������
	
	try{
		strSql.Format("SELECT * FROM v_balance_count");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		row=1;
		double dX;
		while(!recSet->adoEOF){
			col=0;

			m_grid.SetMergeRow(row,false); 
			for(i=0;i<cols;i++)
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				if( row != 1 && i != 0 ) str1.Format("%.2f",atof(strSql)); //��һ������������С����,����ȫ������λС����
				else str1=strSql;
				m_grid.SetTextMatrix(row,col++,str1);
				
			}
			row++;
			m_grid.AddItem("",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();

		m_grid.SetRedraw(true);
		m_grid.RemoveItem(row);
		
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
	
		return ;
	}	
}
