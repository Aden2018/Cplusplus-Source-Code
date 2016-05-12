// EmployeeRelateQueryForFee.cpp: implementation of the CEmployeeRelateQueryForFee class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "EmployeeRelateQueryForFee.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEmployeeRelateQueryForFee::CEmployeeRelateQueryForFee()
{

}

CEmployeeRelateQueryForFee::~CEmployeeRelateQueryForFee()
{

}

BOOL CEmployeeRelateQueryForFee::OnInitDialog()
{
	CEmployeeQuery::OnInitDialog();

	SetWindowText("����������Ա��");
	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"����","����","�Ա�","����","��������","���","������","������",\
		"��������","����"};

	long j=0, i=0,x=0;

	long  headWidth[]={0,1400,1200,600,1400,1300,1300,2000,2000,2000};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����кϲ�
		m_grid.SetColWidth(i,headWidth[count]);

//		p2->m_grid.SetRow(0);
//		p2->m_grid.SetCol(i);
//		p2->m_grid.SetColAlignment(i,4);//flexAlignCenterCenter 4 ��Ԫ������ݾ��С����ж���	

		m_grid.SetTextArray(i++,HeadTitle[count]);
	}


	GetDlgItem(IDC_STATIC_3)->SetWindowText("�����˲���");
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("�������������");

	return true;
}

void CEmployeeRelateQueryForFee::OnOK()
{
	BeginWaitCursor();
	//����,����,�Ա�,��������,��������,����,�����,��������
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetRedraw(false);

	long j=0, i=0,x=0,z;

	CString HeadTitle2[]={"����","����","�Ա�","��������","���","����","������","������",\
		"��������","����","hao"},str1;
	long  headWidth[]={1400,1000,600,1400,900,800,1000,1400,1200,800,0};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle2)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(long count=0;count<sizeof(HeadTitle2)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����кϲ�
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle2[count]);
	}
	CString strSql,strName,strID,strDepart;
	if(m_depart.GetCurSel()==CB_ERR)strDepart="���в���";
	else m_depart.GetLBText(m_depart.GetCurSel(),strDepart); 

	m_name.GetWindowText(strName);
	m_kahao.GetWindowText(strID);
	j=1;
	try{
		if(strDepart=="���в���")
			strSql.Format("select BM,XM,XB,XINGZHI,YUER,to_char(sysdate,'yyyy')-to_char(csRiQI,'yyyy') ���� ,\
			����,������,��������,to_char(sysdate,'yyyy')-to_char(��������,'yyyy')+1 ����,kahao from ְ����������� e1,�����ű� e2,codeQingShu e3 where  \
			e1.���ű���=e2.���ű��� and e3.kahao=e1.���� and \
			���� like '%s%%' and ���� like '%s%%' AND ZXRIQI IS NULL",strID,strName);
		else
			strSql.Format("select BM,XM,XB,XINGZHI,YUER,to_char(sysdate,'yyyy')-to_char(csRiQI,'yyyy') ���� ,\
			����,������,��������,to_char(sysdate,'yyyy')-to_char(��������,'yyyy')+1 ����,kahao from ְ����������� e1,�����ű� e2,codeQingShu e3 where \
				e1.���ű���=e2.���ű��� and e3.kahao=e1.���� and \
				���� like '%s%%' and ���� like '%s%%' and ������='%s' and ZXriqi is NULL ",strID,strName,strDepart);
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		z=recSet->GetFields()->Count ;
		while(!recSet->adoEOF){
			x=0;
			for(count=0;count< z ;count++){
				
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(count)->Value.vt==VT_NULL ? " ":recSet->GetFields()->GetItem(count)->Value ) ;
				m_grid.SetTextMatrix(j,x++,str1);
			}
				
			
			m_grid.AddItem(" ",_variant_t(++j));
			recSet->MoveNext();


		}
		m_grid.SetRedraw(true);
		recSet->Close();		
		
	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox("���ݿ�����ƻ�,��������...");
		return;
	}
	m_grid.SetTextMatrix(j,0,"�ϼ�");
	strSql.Format("����ѯ��: %ld ����Ϣ",j-1);
	GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(strSql);
	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow=1;
		for( i=1;i<8;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
	EndWaitCursor();
}
