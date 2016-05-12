// DepartSet.cpp: implementation of the CDepartSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "DepartSet.h"
#include "departSetAdd.h"
#include "otherDecharge.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDepartSet::CDepartSet()
{

}

CDepartSet::~CDepartSet()
{

}

BOOL CDepartSet::OnInitDialog()
{
	COperatorSet::OnInitDialog();
	return true;
}

void CDepartSet::OnOK()
{
	UpdateData();
	CString HeadTitle[]={"���","������","����","��������"} ,strTmp;//�� 
	
	long  headWidth[]={600,2000,0,2000,00,0,00,1400};
	
	m_grid.SetRedraw(false);
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(2);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(long count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2){
			m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����к�
			m_grid.SetColAlignment(i,4);
		}
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //���ж���
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}	
	CString kfmc;
	CString strSql;
	long cols,x(1);
	try{
		
		strSql.Format("select ������,���ű���,�������� from �����ű� ");
		if( combo1.GetCurSel() == CB_ERR )strSql+=" ORDER BY ������,���ű���";
		else {
			combo1.GetLBText(combo1.GetCurSel(),kfmc);
			strSql+=" WHERE ������='"+kfmc+"' ORDER BY ������,���ű��� ";
		}
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		while(!recSet->adoEOF){
			strSql.Format("%ld",x);
			m_grid.SetTextMatrix(x,0,strSql);
			for(count=0;count< cols;count++){
				
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(count)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(count)->Value);
				m_grid.SetTextMatrix(x,count+1,strSql);
			}
			
			x++;
			m_grid.AddItem(" ",_variant_t(x));
			recSet->MoveNext();
		
		}
		recSet->Close();

		m_grid.SetTextMatrix(x,0,"�ϼ�");
		m_grid.SetRedraw(true);

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		AfxMessageBox(strSql);
		return ;
	}		
		
}

void CDepartSet::OnDblClickMshflexgrid1()
{
	CDepartSetAdd di;
	di.strSql.Format(" SELECT distinct ������ FROM �����ű� order by ������ ");

	long i=0;

	if( m_grid.GetRows()-1 == m_grid.GetRow() ){
		di.flag= 1; //����
		di.strTitle="������������";
		if(di.DoModal()==IDOK) OnOK();
		return;
 
	}else
	{
		di.flag=2; //�޸�
		di.strTitle="���������޸�";
	
		//����,����,����
		for( i=0; i< 3; i++ )
			di.str[i]=m_grid.GetTextMatrix(m_grid.GetRow(),i+1);
		
		if( di.DoModal()==IDOK) OnOK();
		return;

	}
}

void CDepartSet::OnClickMshflexgrid1()
{
	const int ENDLINES=2;
	if(m_grid.GetRows() == ENDLINES || m_grid.GetRow() == m_grid.GetRows()-1 )return;//�ж��Ƿ���Ҫ��ʾ��ݲ˵�

	MSG *pms;
	CString strT1,strT2;
	pms=(MSG*)GetCurrentMessage();

	
	if(pms->message == 0x205) {//0x202Ϊ������,0x205Ϊ����Ҽ���Ϣ
		strT1.Format("�Ƿ�Ҫɾ�� (%s / %s) ����",m_grid.GetTextMatrix(m_grid.GetRow(),1),m_grid.GetTextMatrix(m_grid.GetRow(),3) );
		if ( AfxMessageBox(strT1,MB_OKCANCEL)== IDCANCEL ) return;
	
		strT1.Format(" DELETE FROM �����ű� WHERE�����ű���='%s' ",m_grid.GetTextMatrix(m_grid.GetRow(),2) );
		if(!COtherDecharge::WriteSQL(strT1)){
			AfxMessageBox("ɾ��ʧ��!!");
			return;
		}
		OnOK();

	}
}

void CDepartSet::OnAdd()
{
	CDepartSetAdd di;
	di.strSql.Format(" SELECT distinct ������ FROM �����ű� order by ������ ");
		di.flag= 1; //����
		di.strTitle="������������";
		if(di.DoModal()==IDOK) OnOK();

}
