// EmpUsedAccountCollect.cpp: implementation of the CEmpUsedAccountCollect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "EmpUsedAccountCollect.h"
#include "ProgressIndicate.h"
#include "DialogMedXl.h"
#include "dialogSqloutput.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEmpUsedAccountCollect::CEmpUsedAccountCollect()
{
	strTitle=COtherDecharge::GetStringTitle("SELECT ds2 FROM lsq_gh_type WHERE ds3='B' AND ds1='BAO' ");

}

CEmpUsedAccountCollect::~CEmpUsedAccountCollect()
{

}

BOOL CEmpUsedAccountCollect::OnInitDialog()
{
	CPeculiarInput::OnInitDialog();

	CString px[]={"��������","����","����","�Ա�","����","������","�������","�������","����","����","�����Ϣ","Ŀǰ�ʻ�"};
	long pl[]={1200,1100,1000,500,500,1200,1200,1200,1200,1200,1200,1200,1200};
	SetGridHead(px,pl,m_grid,sizeof(px)/sizeof(CString),5,5);

	m_b3.ShowWindow(SW_HIDE);
	m_b4.ShowWindow(SW_HIDE);
	m_b6.ShowWindow(SW_HIDE);
	m_b2.SetWindowText("��ѯ");
	
	m_s4.SetWindowText("����");
	m_s4.ShowWindow(SW_SHOW);
	
	CRect rt;
	m_e4.GetWindowRect(rt);
	ScreenToClient(rt);
	rt.bottom+=200;
	rt.right+=40;
	c2.MoveWindow(rt);
	c2.ShowWindow(SW_SHOW);

	CDialogMedXL::ReadName("SELECT distinct(��������)��FROM ְ����������� WHERE ���='�α�' order by �������� ",c2);
	c2.AddString("");

	return true;
}

UINT CEmpUsedAccountCollect::QueryData2(LPVOID ps)
{
	CEmpUsedAccountCollect * pd=(CEmpUsedAccountCollect * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);

	CString px[]={"����","��������","����","����","�Ա�","����","����","������","�������","�������","����","����","�����Ϣ","�ʻ�����"};
	long pl[]={1100,1200,1100,1000,500,500,1400,1200,1200,1200,1200,1200,1200,1200,1200};
	CPeculiarInput::SetGridHead(px,pl,pd->m_grid,sizeof(px)/sizeof(CString),5,6);

	COleDateTime dt1;
	pd->d1.GetTime(dt1);

	CString strSql,str1,str2;
	long cols,row,i,col,year=dt1.GetYear();
	double add[20];
	const int START_COMPUTE=7; //��SQL�����
	for( i=0 ; i< 20 ;i++)add[i]=0.0;
	if( pd->c1.GetCurSel()== CB_ERR ) str2="";
	else pd->c1.GetLBText(pd->c1.GetCurSel(),str2);

	try{


		str1.Format("select ��������,����,����,�Ա�,%d-to_char(��������,'yyyy') ��������,��������,����� from ְ����������� x,�����ű� y  where  x.���ű���=y.���ű���    ",year );
	
		if( !str2.IsEmpty() ) str1+=" AND ��������='"+str2+"'";
		pd->e2.GetWindowText(str2);
		if( !str2.IsEmpty() ) str1+=" AND ���� like '"+str2+"%'";
		pd->e3.GetWindowText(str2);
		if( !str2.IsEmpty() ) str1+=" AND ���� like '"+str2+"%'";
		if( pd->c2.GetCurSel() == CB_ERR ) str2="";
		else pd->c2.GetLBText(pd->c2.GetCurSel(),str2);
		if( !str2.IsEmpty() ) str1+=" AND ��������='"+str2+"'";
		
		CString strT01;

		if (year == COleDateTime::GetCurrentTime().GetYear() )   //����ǵ�ǰ���,�����һ��ΪĿǰ���
		  {
				strSql.Format("select Trunc(����,'dd') ddate, ��������,����,����,�Ա�,��������,��������,��Ϣ�����,������,���ⲹ��,�������,�������,��ǰ��Ϣ,����� from  \
							    (select ����, ��������,����,����,�Ա�,��������,��������,��Ϣ�����,������,���ⲹ��,�����,�������,��ǰ��Ϣ from \
									(select ����, ��������,����,����,�Ա�,��������,��������,��Ϣ�����,������,���ⲹ��,�����,��ǰ��Ϣ from	\
										(select ds1,sum(n1) ���ⲹ�� from lsq_emp_headship_charge t where n2 =%d group by  ds1 ) a11,\
										( select ����,��������,����,����,�Ա�,��������,��������,��Ϣ�����,������,�����,��ǰ��Ϣ from \
											(  select I01.ds1 ds1,��Ϣ�����,��ǰ��Ϣ from  \
												( select ds1,n3 ��Ϣ�����  from lsq_remain_employee t where n2=%d-1) I01,\
												( select ds1,nvl(n3,0)-nvl(n1,0) ��ǰ��Ϣ from lsq_remain_employee where n2=%d ) I02 where I01.ds1=I02.ds1(+) \
												) a1,\
											(select ��������,����,����,�Ա�,��������,��������,������,����� ,���� from \
												(select ds1,n1 ������,d1 ���� from lsq_emp_charge t where n4=%d ) a, \
												(%s)  b \
												where a.ds1 = b.���� ) b1 \
										where a1.ds1(+) =b1.����  ) b11 \
										where a11.ds1(+)=b11.���� ) a111 ,\
			(select ds3,sum(n7) ������� from lsq_emp_decharge t  where d1 between to_date('%d'||'0101','yyyymmdd') and to_date('%d'||'1231','yyyymmdd') group by ds3 ) b111 \
			  where b111.ds3(+)=a111.���� ) a14 , \
			 (select sickbm,sum(medmoney+treatemoney-cash) ������� from itemregistertou t where \
		   riqi between to_date('%d'||'0101','yyyymmdd') and to_date('%d'||'1231','yyyymmdd')  and ghtype='���䱣��' \
		   group by sickbm  )  b14 \
			where  b14.sickbm(+)=a14.����  order by ��������,���� ",year,year,year,year,str1,year,year,year,year);
			strT01=strSql;
		}
		else						//���ǵ�ǰ���,�����һ����ʾ��Ӧ��ݵĽ���
		{	
			strSql.Format("select Trunc(����,'dd') ddate, ��������,����,����,�Ա�,��������,��������,��Ϣ�����,������,���ⲹ��,�������,������� from  \
							    (select ����, ��������,����,����,�Ա�,��������,��������,��Ϣ�����,������,���ⲹ��,������� from \
									(select ����, ��������,����,����,�Ա�,��������,��������,��Ϣ�����,������,���ⲹ�� from	\
										(select ds1,sum(n1) ���ⲹ�� from lsq_emp_headship_charge t where n2 =%d group by  ds1 ) a11,\
										( select ����,��������,����,����,�Ա�,��������,��������,��Ϣ�����,������ from \
											( select ds1,n3 ��Ϣ�����  from lsq_remain_employee t where n2=%d-1 ) a1,\
											(select ��������,����,����,�Ա�,��������,��������,������ ,���� from \
												(select ds1,n1 ������,d1 ���� from lsq_emp_charge t where n4=%d ) a, \
												(%s)  b \
												where a.ds1 = b.���� ) b1 \
										where a1.ds1(+) =b1.����  ) b11 \
										where a11.ds1(+)=b11.���� ) a111 ,\
			(select ds3,sum(n7) ������� from lsq_emp_decharge t  where d1 between to_date('%d'||'0101','yyyymmdd') and to_date('%d'||'1231','yyyymmdd') group by ds3 ) b111 \
			  where b111.ds3(+)=a111.���� ) a14 , \
			 (select sickbm,sum(medmoney+treatemoney-cash) ������� from itemregistertou t where \
		   riqi between to_date('%d'||'0101','yyyymmdd') and to_date('%d'||'1231','yyyymmdd')  and ghtype='���䱣��' \
		   group by sickbm  )  b14 \
			where  b14.sickbm(+)=a14.����  order by ��������,���� ",year,year,year,str1,year,year,year,year);

	
	
		strT01.Format("select  ddate, ��������,����,����,�Ա�,��������,��������,��Ϣ�����,������,���ⲹ��,�������,�������,a.n3-a.n1 ������Ϣ,a.n3 ����� from lsq_remain_employee A,\
			(%s) B Where a.ds1(+)=B.���� and a.n2 = %d ",strSql,year);
		}
		/*
		CDialogSqlOutput sqlput;
		sqlput.m_sql=strT01;
		sqlput.DoModal();
		*/
		recSet->Open(_bstr_t(strT01),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		row=1;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			for(i=0;i<cols;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				pd->m_grid.SetTextMatrix(row,col++,str1);
				
				if( i>=START_COMPUTE )add[i-START_COMPUTE]+=atof(str1); 
			}
			row++;
			pd->m_grid.AddItem("",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();

		pd->m_grid.SetMergeCells(true);
		pd->m_grid.SetMergeRow(row,1); 
		pd->m_grid.SetRow(row);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("����%ld ��",row-1);
		pd->m_grid.SetTextMatrix(row,0,"�ϼ�");	
		
		
		for(int count=1;count<cols;count++){
			pd->m_grid.SetTextMatrix(row,count,strSql);	
			pd->m_grid.SetCol(count);
			pd->m_grid.SetCellBackColor(RGB(255,128,0));
			
		}
		
		for(i=START_COMPUTE;i<cols;i++){
			strSql.Format("%.2f",add[i-START_COMPUTE]);
			pd->m_grid.SetTextMatrix(row,i,strSql);
		}

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
	return true;
}

void CEmpUsedAccountCollect::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryData2;
	pg.DoModal();

}
