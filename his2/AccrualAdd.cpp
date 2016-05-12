// AccrualAdd.cpp: implementation of the CAccrualAdd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "AccrualAdd.h"
#include "ProgressIndicate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAccrualAdd::CAccrualAdd()
{
//	strTitle.Format("���䱣�������Ϣ��ת");
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_Title_list WHERE ds2='DIALOG' AND ds3='TITLE' and ds4='AAH' ");

}

CAccrualAdd::~CAccrualAdd()
{

}

BOOL CAccrualAdd::OnInitDialog()
{
	CDoctorWorkLoad::OnInitDialog();

	m_grid.SetRedraw(true);

	pc=(CComboBox*)GetDlgItem(IDC_COMBO1);
	CenterWindow();
	GetDlgItem(IDC_STATIC1)->SetWindowText("����/����");
	GetDlgItem(IDC_STATIC2)->SetWindowText("��Ϣ(%)");
	GetDlgItem(IDC_STATIC_1)->SetWindowText("�������");
	GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_2)->SetWindowText("��������");
	GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_BUTTON_PRINT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_PRINT)->SetWindowText("��Ϣ����");

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

	GetDlgItem(IDC_DATETIMEPICKER3)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	rt1.bottom+=200;
	((CComboBox *)GetDlgItem(IDC_COMBO2))->MoveWindow(rt1);
	((CComboBox *)GetDlgItem(IDC_COMBO2))->ShowWindow(SW_SHOW);
	
	pc->ShowWindow(SW_SHOW);
	pc->ResetContent();
	CString strTmp;
	int year=COleDateTime::GetCurrentTime().GetYear();
	for(long i=0; i<5; i++ ){
		strTmp.Format("%d",year-i );
		pc->AddString(strTmp);
	}
	pc->SetCurSel(0);

	CDialogMedXL::ReadName("SELECT NVL(��������,' ')��FROM �����ű� ORDER BY �������� ",*((CComboBox*)GetDlgItem(IDC_COMBO2)) );
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString("");
	
	
	return true;
}

void CAccrualAdd::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryData;
	pg.DoModal();


}

UINT CAccrualAdd::QueryData(LPVOID ps)
{
	CAccrualAdd * pd=(CAccrualAdd * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);
	pd->SetGridHead();

	CString strSql,str1,str2,str3;
	long cols,row,i,col;
	double add[]={0,0,0,0,0,0,0,0,0};
	const int START_COMPUTE=7; //��SQL�����
	pd->UpdateData();
	CComboBox *pc=pd->pc,*pc2=(CComboBox*)pd->GetDlgItem(IDC_COMBO2);
	try{
		pc->GetLBText(pc->GetCurSel(),str1);
//{"���","������","��������","����","����","�Ա�","����","��������","��Ƚ��","����","������Ϣ","�����ܶ�","�ʻ����"} ;//�� 7 ��
		strSql.Format("SELECT ������,��������,����,����,�Ա�,to_char(sysdate,'yyyy')-to_char(��������,'yyyy'),��������,\
			pre,LL,acc,pre2,����� from ְ����������� x,\
			(select a.ds1 kh,a.n1 pre,b.n1*100||'%%' LL,round(a.n1*b.n1,2) acc,round(a.n1*(b.n1+1),2) \
			pre2 from lsq_remain_employee a,lsq_upgrade b where a.n2=b.n2 and \
			b.ds2='SCALE' and a.n2=%d ) y,�����ű� z where x.����=kh  and z.���ű���=\
			x.���ű���  ",atol(str1) );

		pd->c_edit1.GetWindowText(str1); //����
		if( !str1.IsEmpty() ) {

			if( str1.Left(1) >= '0' && str1.Left(1)<='9' )strSql+=" AND ���� like '"+str1+"%'";
			else strSql+=" AND ���� like '"+str1+"%'";

		}
		if( pc2->GetCurSel() != CB_ERR && pc2->GetCurSel() != pc2->GetCount()-1 )
		{
			pc2->GetLBText(pc2->GetCurSel(),str1);
			strSql+=" AND ��������='"+str1+"'";

		}
		strSql+=" ORDER BY ������,��������,����";	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		
		row=1;
		cols=recSet->GetFields()->Count;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			str1.Format("%ld",row);
			pd->m_grid.SetTextMatrix(row,col++,str1);
			pd->m_grid.SetMergeRow(row,false); //��ͬ��Ԫ��֮�䲻���кϲ�
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

		pd->m_grid.SetMergeCells(true);
		pd->m_grid.SetMergeRow(row,1); 
		pd->m_grid.SetRow(row);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("   ���� %ld ����¼ ",row-1);
		pd->m_grid.SetTextMatrix(row,0,"�ϼ�");	
		pd->GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(strSql);
		
		for(int count=1;count<cols+1;count++){
			pd->m_grid.SetTextMatrix(row,count,strSql);	
			pd->m_grid.SetCol(count);
			pd->m_grid.SetCellBackColor(RGB(255,128,0));
			
		}
		
		CString preStr("");
		for(i=START_COMPUTE;i<cols;i++){
			if( i == START_COMPUTE+1 ) strSql="";
			else {									//* ��ֹǰ������Ԫ��֮����ֵ��ͬ�����кϲ�,Ӱ��ۿ�Ч��

				strSql.Format("%.2f",add[i-START_COMPUTE]);
				if (strSql == preStr ){
					strSql.Format(" %.2f",add[i-START_COMPUTE]);
					pd->m_grid.SetRow(row);
					pd->m_grid.SetCol(i+1);
					pd->m_grid.SetCellAlignment((short)7); //���ҿ��ж���
				}

				preStr = strSql;

			}
		
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
END:
	pd->m_grid.SetRedraw(true);
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
}

void CAccrualAdd::SetGridHead()
{
	CString HeadTitle[]={"���","������","��������","����","����","�Ա�","����","��������","��Ƚ��","����","������Ϣ","�����ܶ�","�ʻ����"} ;//�� 7 ��
	
	long  headWidth[]={800,1000,1100,1000,900,400,500,1000,1400,1000,1200,1400,1400,1400,1200,1200,1000,1600,1300,1300,1300,0,1300,1300,1300,00,00,1400};
	
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetFixedCols(0l);
	m_grid.SetRedraw(false);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<4){
			m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����к�
			m_grid.SetColAlignment(i,4);
		}
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //���ж���
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}

}

void CAccrualAdd::OnButtonPrint() //��Ϣ����
{
	CString strTmp;
	double dbAcc;
	int year;
	c_edit3.GetWindowText(strTmp);
	dbAcc=atof(strTmp); 
	pc->GetLBText(pc->GetCurSel(),strTmp);
	year=atol(strTmp);
	if( dbAcc == 0. ){
		AfxMessageBox("���ʲ�����Ϊ(��),�����ú����ʺ���Ⱥ��ٽ��н���!!!");
		return;
	}
	strTmp.Format("��Ϣ�������: %d ��,����: %.2f%%",year,dbAcc);
	if(AfxMessageBox(strTmp,MB_OKCANCEL)==IDCANCEL)return;
	try{
		strTmp.Format(" SELECT count(*) FROM LSQ_REMAIN_EMPLOYEE WHERE n2=%d ",year );
		recSet->Open(_bstr_t(strTmp),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		strTmp=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value);
		recSet->Close();
		if( atol(strTmp) != 0 ){
			AfxMessageBox("�������Ϣ�Ѿ������...");
			return;
		}
		HospitalConnect->BeginTrans();
		
		strTmp.Format("DELETE FROM LSQ_UPGRADE WHERE DS2='SCALE' and n2=%d ",year);
		HospitalConnect->Execute(_bstr_t(strTmp),NULL,adCmdText);
	
		strTmp.Format("INSERT INTO lsq_upgrade (ds2,n1,n2) VALUES('SCALE',%.4f,%d) ",dbAcc/100,year);
		HospitalConnect->Execute(_bstr_t(strTmp),NULL,adCmdText);
		//����,����ʱ��,������,���
		strTmp.Format("INSERT INTO lsq_remain_employee (ds1,d1,n1,n2,n3) \
			SELECT ����,sysdate,�����,%d,�����*(1+%.4f) FROM ְ����������� WHERE ���='�α�' ",year,dbAcc/100 );
	
		
		
		HospitalConnect->Execute(_bstr_t(strTmp),NULL,adCmdText);
	
		strTmp.Format("UPDATE ְ����������� SET �����=(�����)*(1+%.4f) WHERE ���='�α�' ",dbAcc/100 );
		HospitalConnect->Execute(_bstr_t(strTmp),NULL,adCmdText);
		
		HospitalConnect->CommitTrans();


	}
	catch(_com_error e)
	{
		AfxMessageBox("����ʧ��,����ϵ���������Ա...");
		AfxMessageBox(strTmp);
		HospitalConnect->RollbackTrans();
		return;
	}
	strTmp.Format("%d�����Ϣ�������!!!",year);
	AfxMessageBox(strTmp);
}
