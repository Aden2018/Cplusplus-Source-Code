// EmpDechargeQuery.cpp: implementation of the CEmpDechargeQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "EmpDechargeQuery.h"
#include "otherDecharge.h"
#include "progressIndicate.h"
#include "employeeBmp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEmpDechargeQuery::CEmpDechargeQuery()
{
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_upgrade WHERE ds2='EMP_DECHARGE_QUERY' ");

}

CEmpDechargeQuery::~CEmpDechargeQuery()
{

}

BOOL CEmpDechargeQuery::OnInitDialog()
{
	CBaseAddCash::OnInitDialog();
	m_sx3.SetWindowText("��ʼʱ��");
	m_sx4.SetWindowText("����ʱ��");
	m_sx1.SetWindowText("����");
	m_sx2.SetWindowText("����");
	
	m_b4.ShowWindow(SW_SHOW);
	m_b6.ShowWindow(SW_HIDE);
	m_b2.SetWindowText("��ѯ(&S)");
	m_b3.SetWindowText("����...");
	m_b4.SetWindowText("ɾ��");

	

	CRect rt;
	m_sx1.ShowWindow(SW_SHOW);
	m_sx2.ShowWindow(SW_SHOW);
	m_sx3.ShowWindow(SW_SHOW);
	m_sx4.ShowWindow(SW_SHOW);

	m_xe1.GetWindowRect(rt);
	ScreenToClient(rt);
	e2.MoveWindow(rt);
	e2.ShowWindow(SW_SHOW);

	m_xe2.GetWindowRect(rt);
	ScreenToClient(rt);
	e3.MoveWindow(rt);
	e3.ShowWindow(SW_SHOW);

	m_xe3.GetWindowRect(rt);
	ScreenToClient(rt);
	d1.MoveWindow(rt);
	d1.ShowWindow(SW_SHOW);

	m_xe4.GetWindowRect(rt);
	ScreenToClient(rt);
	d2.MoveWindow(rt);
	d2.ShowWindow(SW_SHOW);
	COleDateTime t2(COleDateTime::GetCurrentTime().GetYear(),1,1,0,0,0);

	d1.SetTime(t2);

	e2.SetFocus();
//	OnOK();
	CString px[]={"s","����","����Ա","��������","����","����","�Ա�","���","��������","ƾ֤��","IC��֧��","����ͳ��","�����Ը�","�����Է�","�����ϼ�","��������","�ʻ�֧��","ͳ��֧��","����ϼ�"};
	long pl[]={0,1100,00,1300,1100,800,400,1100,1100,600,1000,1000,1000,1000,1000,700,1000,1000,1000,1000,1000,1000};
	CPeculiarInput::SetGridHead(px,pl,m_grid,sizeof(px)/sizeof(CString),6,2);

	return true;
}



UINT CEmpDechargeQuery::QueryData2(LPVOID ps)
{
	CEmpDechargeQuery * pd=(CEmpDechargeQuery * )((CProgressIndicate *)ps)->pDialog;
	pd->UpdateData();
	pd->m_grid.SetRedraw(false);

																																		 //����											//����
	CString px[]={"s","����","����Ա","��������","����","����","�Ա�","���","��������","ƾ֤��","IC��֧��","����ͳ��","�����Ը�","�����Է�","�����ϼ�","��������","�ʻ�֧��","ͳ��֧��","����ϼ�"};
	long pl[]={0,1100,00,1300,1100,800,400,1100,1100,600,1000,1000,1000,1000,1000,700,1000,1000,1000,1000,1000,1000};
	CPeculiarInput::SetGridHead(px,pl,pd->m_grid,sizeof(px)/sizeof(CString),6,2);

	pd->m_grid.SetColAlignment(5,4); //�Ա������ʾ
	pd->m_grid.SetColAlignmentFixed(3,4);// ���ž�����ʾ

	COleDateTime dt1,dt2;
	pd->d1.GetTime(dt1);
	pd->d2.GetTime(dt2);


	CString strSql,str1,str2,str3,str4;
	pd->e2.GetWindowText(str1);
	pd->e3.GetWindowText(str2);

	long cols,row,i,col;
	double add[20];
	const int START_COMPUTE=9+1; //��SQL�����
	for( i=0 ; i< 20 ;i++)add[i]=0.0;

	try{
//���к�,{"����","����Ա","��������","����","����","�Ա�","���","��������","ƾ֤��","��������","ͳ��","�����Ը�","�����Է�","����","�ʻ�֧��","����֧��"};
		strSql.Format("SELECT ds8,d1,ds1,ds2,ds3,ds4,ds5,ds6,ds7,n1,n2,n3,n4,n5,n2+n3+n4,to_char(n6*100)||'%%',n7,n8,n7+n8 from lsq_emp_decharge \
			WHERE d1 BETWEEN to_date(%s,'yyyymmdd') AND to_date(%s,'yyyymmdd') AND ds3 like '%s%%' AND ds4 like '%s%%' order by n1 ",\
			dt1.Format("%Y%m%d"),dt2.Format("%Y%m%d"),str1,str2);

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		row=1;
		double dX;
		while(!recSet->adoEOF){
			col=0;
		//	str1.Format("%ld",row);
		//	pd->m_grid.SetTextMatrix(row,col++,str1);
	/*		pd->m_grid.SetRow(row);
			pd->m_grid.SetCol(6);
			pd->m_grid.SetCellBackColor(BK1);
			pd->m_grid.SetCol(9);
			pd->m_grid.SetCellBackColor(BK2);
	*/	
			pd->m_grid.SetMergeRow(row,false);
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

		pd->m_grid.SetMergeCells(2);
		pd->m_grid.SetRow(row);
		pd->m_grid.SetMergeRow(row,true);
		pd->m_grid.SetCellBackColor(RGB(255,0,0));
		strSql.Format("����%ld ��",row-1);
		pd->m_grid.SetTextMatrix(row,0,"�ϼ�");	
		
		
		for(int count=1;count<cols;count++){
			pd->m_grid.SetTextMatrix(row,count,strSql);	
			pd->m_grid.SetCol(count);
			pd->m_grid.SetCellBackColor(RGB(255,128,0));
			
		}
		
		for(i=START_COMPUTE;i<cols;i++){
			if( i== cols-4) {
				pd->m_grid.SetTextMatrix(row,i,"");
			}
			else{
				strSql.Format("%.2f",add[i-START_COMPUTE]);
				pd->m_grid.SetTextMatrix(row,i,strSql);
			}
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

void CEmpDechargeQuery::OnOK()
{
	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryData2;
	pg.DoModal();

}

void CEmpDechargeQuery::OnB1()
{
	CEmployeeBmp di;
	di.DoModal();
}
void CEmpDechargeQuery::OnDblClickMshflexgrid1()
{
	if(!theApp.AssertRole(ROLE_DECHARGE_DELETE))return; 

	if( m_grid.GetRows() < 3 ) return; //������С������,��Ϊ��
	CString str1,strID=m_grid.GetTextMatrix(m_grid.GetRow(),0 );
	
	str1="�Ƿ�Ҫɾ�� "+m_grid.GetTextMatrix(m_grid.GetRow(),3)+" / "+m_grid.GetTextMatrix(m_grid.GetRow(),4)+" / "+m_grid.GetTextMatrix(m_grid.GetRow(),5)+" /ƾ֤�ţ�"+m_grid.GetTextMatrix(m_grid.GetRow(),9);
	
	if( MessageBox(str1,"��ʾ",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;



	_CommandPtr cmd;
	_ParameterPtr par;
	cmd.CreateInstance(__uuidof( Command ));
	par.CreateInstance(__uuidof( Parameter));
	int succ=0;

	_variant_t vNULL;
	vNULL.vt = VT_ERROR;
	vNULL.scode = DISP_E_PARAMNOTFOUND;
	try{

		par=cmd->CreateParameter(_bstr_t("id"),adVarChar,adParamInput,strID.GetLength(),_variant_t(strID));
		cmd->Parameters->Append( par );

		par=cmd->CreateParameter(_bstr_t("suc"),adInteger,adParamOutput,0,vNULL);
		cmd->Parameters->Append( par );
		
		cmd->put_CommandText(_bstr_t("prc_emp_decharge_del"));
		cmd->ActiveConnection=HospitalConnect;
	
		cmd->put_CommandType(adCmdStoredProc) ;
		cmd->Execute(NULL,NULL,adCmdStoredProc);
		
		succ=(long)cmd->Parameters->GetItem("suc")->Value;
		switch( succ )
		{
		case 0:str1.Format("�ɹ�ɾ��!!");
					break;
		case 1:str1.Format("�������ش���,����ϵϵͳά����Ա!!!");
			break;
		case 5:str1.Format("ɾ��ʧ��,����ϵͳ����!!");
			break;
		default:
			str1.Format("����ʧ��,����ϵ���������Ա!!!");
		}
		cmd.Detach();
		par.Detach();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	//	((CProgress*)ps)->connectFlag =1;
		return ;
	}
	OnOK();
	AfxMessageBox(str1);
}
void CEmpDechargeQuery::OnClickMshflexgrid1()
{
//	AfxMessageBox("click");
}

void CEmpDechargeQuery::OnB2() //ɾ�����һ��
{

}
