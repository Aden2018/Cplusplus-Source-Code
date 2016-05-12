// EmployeeQueryDecharge.cpp: implementation of the CEmployeeQueryDecharge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "EmployeeQueryDecharge.h"
#include "employeeBmp.H"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEmployeeQueryDecharge::CEmployeeQueryDecharge()
{

}

CEmployeeQueryDecharge::~CEmployeeQueryDecharge()
{

}

BOOL CEmployeeQueryDecharge::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString strSql;
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	try{
		strSql.Format("select distinct(������) from �����ű� ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetCollect("������").vt==VT_NULL?" ":recSet->GetCollect("������"));
			m_depart.AddString(strSql);
			recSet->MoveNext();
		}
		recSet->Close();
		m_depart.AddString("���в���");

	}
	catch(_com_error e)
	{
		recSet->Close();
		return false;
	}
	SetGridHead();
	return true;
}

void CEmployeeQueryDecharge::SetGridHead()
{
	m_grid.SetRows(2);
	m_grid.Clear();

	long j=0, i=0,x=0;
	CString HeadTitle[]={"������","��������","����","����","�Ա�","����","�����",\
		"����","������","ʹ���ۼ�","ƾ֤��"};

	long  headWidth[]={1200,1200,1200,1000,600,600,1200,1000,1000,1000,1000};
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
}

void CEmployeeQueryDecharge::OnOK()
{
	BeginWaitCursor();
	//����,����,�Ա�,��������,��������,����,�����,��������
	SetGridHead();
	m_grid.SetRedraw(false);

	CString strSql,strName,strID,strDepart,str1;
	if(m_depart.GetCurSel()==CB_ERR)strDepart="���в���";
	else m_depart.GetLBText(m_depart.GetCurSel(),strDepart); 

	m_name.GetWindowText(strName);
	m_kahao.GetWindowText(strID);
	long count,cols,j,x;
	j=1;
	try{
		if(strDepart=="���в���")

			strSql.Format(" SELECT * FROM V_EMP_DECHARGE_COUNT WHERE  ���� like '%s%%' AND ���� like '%s%%' ",strID,strName);


		else
			strSql.Format(" SELECT * FROM V_EMP_DECHARGE_COUNT WHERE  ���� like '%s%%' AND ���� like '%s%%' AND ������='%s' ",strID,strName,strDepart );

		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->GetCount();
		while(!recSet->adoEOF){
			x=0;
			for(count=0;count< cols ;count++){
				
			//	str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(HeadTitle[count])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(HeadTitle[count])));
				str1=(char*)_bstr_t( recSet->GetFields()->GetItem(count)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(count)->Value);

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
	m_grid.SetRedraw(true);
	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow = 1;
		for( int i=2;i<8;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
	EndWaitCursor();
}

void CEmployeeQueryDecharge::OnDblClickMshflexgrid2()
{
	long row=m_grid.GetRow();
	if(row<m_grid.GetRows()-1 && row !=0){
		
		if(p!=NULL){
			for(int i=0; i< m_grid.GetCols(0) ;i++)((CString*)p)[i]=m_grid.GetTextMatrix(row,i);
			((CString*)p)[i]="FFFFFFFF";
			CDialog::OnOK();
		}
	}

}

void CEmployeeQueryDecharge::OnClickMshflexgrid2()
{
	long r1;
	r1=m_grid.GetRow();
	if(r1 >= m_grid.GetRows()-1 || curRow == r1)return;
	
	m_grid.SetCol(0);
	m_grid.SetRow(curRow);
	UINT color=m_grid.GetCellBackColor();
	
	for(int i=2;i<8;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(color);
	}
	m_grid.SetRow(r1);
	curRow=r1;
	for( i=2;i<8;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(RGB(255,0,0));
	}
}
