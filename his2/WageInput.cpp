// WageInput.cpp: implementation of the CWageInput class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "WageInput.h"
#include "excel9.h"
#include "progressEx.h"
#include "ProgressIndicate.h"
#include "progress.h"
#include "peculiarInput.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWageInput::CWageInput() //��ֵ����
{
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_upgrade WHERE ds2='SALARY' ");

}

CWageInput::~CWageInput()
{

}

BOOL CWageInput::OnInitDialog()
{
	CBaseAddCash::OnInitDialog();

	CRect rt;
	m_sx1.ShowWindow(SW_SHOW);
	m_sx1.SetWindowText("����");
	m_sx2.ShowWindow(SW_SHOW);
	m_sx2.SetWindowText("����");
	m_sx3.ShowWindow(SW_SHOW);
	m_sx3.SetWindowText("����");
	m_sx4.ShowWindow(SW_SHOW);
	m_sx4.SetWindowText("��ѯ/�������");

	m_xe1.GetWindowRect(rt);
	ScreenToClient(rt);
	rt.bottom+=200;
	rt.right+=40;
	c1.MoveWindow(rt);
	c1.ShowWindow(SW_SHOW);
	

	m_xe2.GetWindowRect(rt);
	ScreenToClient(rt);
	e2.MoveWindow(rt);
	e2.ShowWindow(SW_SHOW);

	m_xe3.GetWindowRect(rt);
	ScreenToClient(rt);
	e3.MoveWindow(rt);
	e3.ShowWindow(SW_SHOW);

	m_xe4.GetWindowRect(rt);
	ScreenToClient(rt);
	d1.MoveWindow(rt);
	d1.ShowWindow(SW_SHOW);
	
	CDialogMedXL::ReadName("SELECT NVL(��������,' ')��FROM �����ű� ORDER BY �������� ",c1);
	c1.AddString("");

	m_s4.SetWindowText("����");
	m_s4.ShowWindow(SW_SHOW);
	
	m_e4.GetWindowRect(rt);
	ScreenToClient(rt);
	rt.bottom+=200;
	rt.right+=40;
	c2.MoveWindow(rt);
	c2.ShowWindow(SW_SHOW);

	CDialogMedXL::ReadName("SELECT distinct(��������)��FROM ְ����������� WHERE ���='�α�' order by �������� ",c2);
	c2.AddString("");

	SetGridHead();
	return true;
}

extern COleVariant vOpt;
#define _O(x) COleVariant(x)
#define   IDC_PROGRESS_EXCEL WM_USER+1211

void CWageInput::OnB2() //���ҵ�����ļ�
{
	CString strFile,filter;
	filter="Excel�ļ� (*.xls)|*.xls||";
	CFileDialog fixls(true,"xls","",0,filter);
	if(fixls.DoModal()==IDCANCEL)return;
	
	strFile=fixls.GetPathName();
	GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(strFile);
	GetDlgItem(IDC_STATIC_NOTIFY)->ShowWindow(SW_SHOW);

	CString strSql;
	COleDateTime dt1;
	d1.GetTime(dt1);
	strSql.Format("��ȷ�����������ļ��������ȷ����(%s,%d��) ",strFile,dt1.GetYear() );
	if( AfxMessageBox(strSql,MB_OKCANCEL) == IDCANCEL ) {
		GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText("");
		GetDlgItem(IDC_STATIC_NOTIFY)->ShowWindow(SW_HIDE);
		
		return;
	}
//�������Ƿ��Ѿ�����,û������,�����˳�
	Range vr;
	long y(1);
	CString strTemp;
	double dbWage(0),db1;
	try{
		strSql.Format("SELECT count(*) FROM lsq_emp_wage WHERE to_char(d1,'yyyy')='%d' ",dt1.GetYear() );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(0l)->Value);
		recSet->Close();
		if( atol(strSql) > 0 ){
			strSql.Format("%d��Ȳ��������Ѿ����ڣ�������ֹ���룡����",iYear );
			AfxMessageBox(strSql);
//			GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText("");
//			GetDlgItem(IDC_STATIC_NOTIFY)->ShowWindow(SW_HIDE);
			return;
		}
//////////////////////////////////////////////////////////////
	BeginWaitCursor();
	CProgressEx pp;
	CRect r1(0,0,400,25);
	pp.Create(WS_CHILD |PBS_SMOOTH|WS_BORDER ,r1,this,IDC_PROGRESS_EXCEL);
	pp.UpdateWindow();
	pp.ShowWindow(SW_SHOW);
	pp.CenterWindow();
	pp.Invalidate();
	pp.strView="����׼������...���Եȣ���";

	_Application app2 ;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;

	app2.CreateDispatch("excel.application");
	if(!app2){
		AfxMessageBox("��ע��ϵͳ�б���װ��EXCEL97 ���� EXCEL2000 ,����˹��ܲ���ʹ��...");
		return;
	}
	books2=app2.GetWorkbooks();
	book2=books2.Open(strFile,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	sheets2=book2.GetWorksheets();
	
	sheet2=sheets2.GetItem(COleVariant((short)1)); //sheet1 ��Ϊ���ʱ�
	app2.SetVisible(false);


	HospitalConnect->BeginTrans();
	while(true){
	
		filter.Format("A%d",y);
		vr=sheet2.GetRange(_O(filter),_O(filter));
		strTemp=(char*)_bstr_t( vr.GetValue() );
		if( strTemp.IsEmpty() ) {
			break;
		}
	
		filter.Format("B%d",y);
		vr=sheet2.GetRange(_O(filter),_O(filter));
		db1=atof((char*)_bstr_t(vr.GetValue()) );

	
		strSql.Format(" INSERT INTO lsq_emp_other_price(ds1,n1,n2) VALUES('%s',%.2f,%d )  ",strTemp,db1,iYear );
	
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		dbWage+=db1;
		++y;
		pp.strView.Format("�Ѿ�����%ld��ְ������",y-1);
		pp.SetPos( (y-1)%100 );
		
	}


	HospitalConnect->CommitTrans();
	EndWaitCursor();	


//////////////////////////////////////////////


	pp.DestroyWindow();
	sheet2.ReleaseDispatch();
	sheets2.ReleaseDispatch();
	book2.Close(_O((short)0),vOpt,vOpt); //�ر�EXCEL,�������ļ�
	book2.ReleaseDispatch();
	books2.Close();
	books2.ReleaseDispatch();
	app2.ReleaseDispatch();	
	app2.Quit();
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return;
	}
	
	
	strSql.Format("������ %ld ��ְ������,�ܶ�Ϊ��%.2f",y-1 ,dbWage);
	
	AfxMessageBox(strSql);
	GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText("");
	GetDlgItem(IDC_STATIC_NOTIFY)->ShowWindow(SW_HIDE);


}

void CWageInput::OnB1() //ģ���ѯ
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryData;
	pg.DoModal();

	
}

void CWageInput::SetGridHead()
{
	CString HeadTitle[]={"���","����","����","����","�Ա�","��������","����",\
		"����","��ȹ���","����","Ӧ����","�ʻ����","�ϼ�"} ,strTmp;//�� 
	
	long  headWidth[]={800,1000,1000,900,400,1100,400,\
		1200,1400,800,1400,1400,1400};
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));

	m_grid.SetFixedCols(1);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2){
			m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����к�
			m_grid.SetColAlignment(i,4);
		}
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //���ж���
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
}

UINT CWageInput::QueryData(LPVOID ps)
{
	CWageInput * pd=(CWageInput * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);
//	pd->SetGridHead();
	CString HeadTitle[]={"���","����","����","����","�Ա�","��������","����",\
		"����","��ȹ���","����","Ӧ����","�ʻ����","�ϼ�"} ,strTmp;//�� 
	
	long  headWidth[]={800,1000,1000,900,400,1100,400,\
		1200,1400,800,1000,1400,1400};
	CPeculiarInput::SetGridHead(HeadTitle,headWidth,pd->m_grid,sizeof(HeadTitle)/sizeof(CString),5,2);

	COleDateTime dt1;
	pd->d1.GetTime(dt1);

	CString strSql,str1;
	long cols,row,i,col;
	double add[20];
	const int START_COMPUTE=7; //��SQL�����
	const double GUOQING =700.00,GUOHOU= 500.00 ;
	for( i=0 ; i< 20 ;i++)add[i]=0.0;

	try{
 	
		strSql.Format("SELECT ��������,����,����,�Ա�,��������,%d-to_char(��������,'yyyy') age,��������, \
			 x.n1,to_char(y.n1*100)||'%%',decode(��������,'����������',decode(sign(round(y.n1*x.n1,2)-%.2f),1,round(y.n1*x.n1,2),%.2f),\
			 '����ǰ����',decode(sign(round(y.n1*x.n1,2)-%.2f),1,round(y.n1*x.n1,2),%.2f),round(y.n1*x.n1,2) ), \
			 �����,round(�����+y.n1*x.n1,2) \
			 from lsq_emp_wage x,\
			 \
			 (select ����,����,�Ա�,��������,��������,�����,ds2,n1,n2,n3,���ű��� from ְ����������� a,\
			       (select n1,ds2,n2,n3 from lsq_gh_type t Where ds3='C' ) b \
			 where a.��������=b.ds2  and %d-to_char(��������,'yyyy') >=n2 and %d-to_char(��������,'yyyy')<=n3 ) y, \
			 \
			 �����ű� z \
			 \
			 where x.ds1=y.���� and to_char(x.d1,'yyyy')=%d-1 and y.���ű���=z.���ű��� ",dt1.GetYear(),\
			 GUOHOU,GUOHOU,GUOQING,GUOQING,dt1.GetYear(),dt1.GetYear(),dt1.GetYear() );
	
		if( pd->c1.GetCurSel() != CB_ERR && pd->c1.GetCurSel() != pd->c1.GetCount()-1 ){
			pd->c1.GetLBText(pd->c1.GetCurSel(),str1);
			strSql+=" AND ��������='"+str1+"'";

		}
		if( pd->c2.GetCurSel() != CB_ERR  && pd->c2.GetCurSel() != pd->c2.GetCount()-1 ){
			pd->c2.GetLBText(pd->c2.GetCurSel(),str1);
			strSql+=" AND ��������='"+str1+"'";

		}

		strSql+=" ORDER by ��������,����";
		
	
		
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		row=1;
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
			pd->m_grid.AddItem("",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();

//		str1.Format("�ܼ�: ��ɹ� %ld ��ҩƷ",row-1 );
//		pd->GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(str1);
		pd->m_grid.SetMergeCells(true);
		pd->m_grid.SetMergeRow(row,1); 
		pd->m_grid.SetRow(row);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("����%ld ��",row-1);
		pd->m_grid.SetTextMatrix(row,0,"�ϼ�");	
		
		
		for(int count=1;count<cols+1;count++){
			pd->m_grid.SetTextMatrix(row,count,strSql);	
			pd->m_grid.SetCol(count);
			pd->m_grid.SetCellBackColor(RGB(255,128,0));
			
		}
		
		for(i=START_COMPUTE;i<cols;i++){
			if( i== START_COMPUTE+1) strSql="";
			else 
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

	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
	return true;
}

void CWageInput::OnExcel()
{
	extern void ToExcel(CMSHFlexGrid * pg);
	if( MessageBox("�Ƿ�ȷ��Ҫ������ Excel ��� ??? ","��ʾ",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	ToExcel(&m_grid);

}

void CWageInput::OnB3() //ʵ�ʳ�ֵ����
{
	CProgress pd;
	pd.strNotify="�Ƿ�ȷ��Ҫ������Ƚ�ת��ֵ,ÿ���ֻ�������һ�γ�ֵ,����ȷ�Ϲ����Ѿ�����!!!";
	pd.pThreadFunction=CProgress::EmpAutoAddCash;
	pd.strView="���ڽ����Զ���ֵ,���Ժ�...";
	pd.DoModal();
}

void CWageInput::OnOK() // ��ֵ�����ѯ
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryDataReal;
	pg.DoModal();

}

UINT CWageInput::QueryDataReal(LPVOID ps) //ʵ�������ѯ
{
	CWageInput * pd=(CWageInput * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);
//	pd->SetGridHead();
	CString HeadTitle[]={"���","����","����","����","�Ա�","��������","����",\
		"����","��ȹ���","����","Ӧ����","������","�ϼ�","�ʻ����"} ,strTmp;//�� 
	
	long  headWidth[]={800,1000,1000,900,400,1100,400,\
		1200,1400,800,1000,1400,1400,1400};
	CPeculiarInput::SetGridHead(HeadTitle,headWidth,pd->m_grid,sizeof(HeadTitle)/sizeof(CString),5,2);
	
	COleDateTime dt1;
	pd->d1.GetTime(dt1);


	CString strSql,str1,str2;
	pd->e2.GetWindowText(str1);//����
	pd->e3.GetWindowText(str2);//����

	long cols,row,i,col;
	double add[20];
	const int START_COMPUTE=7; //��SQL�����
	for( i=0 ; i< 20 ;i++)add[i]=0.0;
//	CString HeadTitle[]={"���","����","����","����","�Ա�","��������","����",\
		"����","��ȹ���","����","Ӧ����","�ʻ����","�ϼ�"} ,strTmp;//�� 
	try{
 	
		strSql.Format("SELECT ��������,����,����,�Ա�,��������,to_char(sysdate,'yyyy')-to_char(��������,'yyyy') age,��������, \
			 x.n2,decode(to_char(x.n3*100)||'%%','%%',' ',to_char(x.n3*100)||'%%'),n1,n5,n5+n1,����� from lsq_emp_charge x,ְ�����������a,	 �����ű� z	\
			 where x.ds1(+)=a.���� and a.���ű���=z.���ű��� AND ���� like '%s%%' AND ������like '%s%%' and ���='�α�' and x.n4 =%d   ",str1,str2,dt1.GetYear() );
	
		if( pd->c1.GetCurSel() != CB_ERR && pd->c1.GetCurSel() != pd->c1.GetCount()-1 ){
			pd->c1.GetLBText(pd->c1.GetCurSel(),str1);
			strSql+=" AND ��������='"+str1+"'";

		}
		if( pd->c2.GetCurSel() != CB_ERR  && pd->c2.GetCurSel() != pd->c2.GetCount()-1 ){
			pd->c2.GetLBText(pd->c2.GetCurSel(),str1);
			strSql+=" AND ��������='"+str1+"'";

		}

		strSql+=" ORDER by ��������,����";

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		row=1;
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
			
	*/		pd->m_grid.SetMergeRow(row,false);
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

//		str1.Format("�ܼ�: ��ɹ� %ld ��ҩƷ",row-1 );
//		pd->GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(str1);
		pd->m_grid.SetMergeCells(true);
		pd->m_grid.SetMergeRow(row,1); 
		pd->m_grid.SetRow(row);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("����%ld ��",row-1);
		pd->m_grid.SetTextMatrix(row,0,"�ϼ�");	
		
		
		for(int count=1;count<cols+1;count++){
			pd->m_grid.SetTextMatrix(row,count,strSql);	
			pd->m_grid.SetCol(count);
			pd->m_grid.SetCellBackColor(RGB(255,128,0));
			
		}
		
		for(i=START_COMPUTE;i<cols;i++){
			if( i== START_COMPUTE+1 ) strSql="";
			else
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

	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);
	return true;
}
