// ResideBedSet.cpp: implementation of the CResideBedSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "ResideBedSet.h"
#include "resideBedSetAdd.h"
#include "resideBedModify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResideBedSet::CResideBedSet()
{
	//�ֱ��������  ����  ��λ ���������λ��
	strBedName="";
	strBedCode="";
	strTitle="����λ������ѯ";
	arrayLocal.RemoveAll();
	DIALOG_FLAG=DIALOG_BED;
}

CResideBedSet::~CResideBedSet()
{

}

BOOL CResideBedSet::OnInitDialog()
{
	CResideLocalSet::OnInitDialog();
	GetDlgItem(IDC_STATIC_LOCAL)->SetWindowText("��������");
	CString strSql;
	strSql.Format(" SELECT Rcode,Rname FROM lsq_reside_room WHERE Reffect='1' ");
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		m_combox.AddString("");
		while(!recSet->adoEOF){
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(0l))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(0l))->Value);
				arrayLocal.Add(strSql);
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(1l))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(1l))->Value);
				m_combox.AddString(strSql);

				recSet->MoveNext();
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description() );
		return false;
	}
	return true;
}

void CResideBedSet::SetGridHead()
{
	CString HeadTitle[]={"�������","��������","�������","��������","��λ����","��λ����","�۸�","��ע"};
	long  headWidth[]={0,2000,0,2200,0,2000,1600,2400};
		
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0,col(0),row(0);
	m_grid.SetRow(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
	
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //���ж���
		
		m_grid.SetTextArray(i++,HeadTitle[count]);
		m_grid.SetColAlignment(count,1);//�м������
		
	}
}

void CResideBedSet::OnMenuResideLocalAdd()
{
	CResideBedSetAdd sa;
	sa.DoModal();
}

void CResideBedSet::OnMenuResideLocalDel()
{
	if( CheckSelectRow() == FAIL) return;
	CString strBm1=m_grid.GetTextMatrix(curRow,4);//��ȡ��λ����

	CString strSql;
	strSql.Format("ȷ��Ҫɾ��: %s / %s ",m_grid.GetTextMatrix(curRow,BEDCODE_POS),m_grid.GetTextMatrix(curRow,BEDNAME_POS) );
	if( MessageBox(strSql,"��ʾ",MB_OKCANCEL|MB_ICONINFORMATION  ) == IDCANCEL) return;

	strSql.Format("update lsq_reside_bed set beffect='0' Where bcode='%s' ",strBm1);
	if( COtherDecharge::WriteSQL(strSql) ){
		AfxMessageBox("ɾ���ɹ�");
		m_grid.RemoveItem(curRow);
	}
	else AfxMessageBox("ɾ��ʧ��");

}

void CResideBedSet::OnMenuResideLocalModify()
{
	if( CheckSelectRow() == FAIL) return;
	CResideBedModify bm;
	bm.m_strBedCode=m_grid.GetTextMatrix(curRow,4);//��λ����
	bm.m_price=atof(m_grid.GetTextMatrix(curRow,6));//�۸�
	bm.m_strName=m_grid.GetTextMatrix(curRow,5); //����
	bm.m_strRemark=m_grid.GetTextMatrix(curRow,7);//��ע
	bm.strLocal=m_grid.GetTextMatrix(curRow,1);//��������
	bm.strRoom=m_grid.GetTextMatrix(curRow,3); //��������
	if( bm.DoModal()==IDOK) OnMenuResideLocalRefresh();
}

void CResideBedSet::OnMenuResideLocalRefresh()
{
	UpdateData();
	SetGridHead();
	CString strSql,str1;
	m_grid.SetRedraw(false);
	long row,i,cols;

	try{
		strSql.Format( "select a.llocal,a.lname,b.rcode,b.rname,c.bcode,c.bname,c.bprice,c.bremark from lsq_reside_local a,\
			lsq_residE_Room b ,lsq_reside_bed c where a.llocal=b.rlocal and b.rcode=c.broom and c.beffect='1' \
			AND c.Reff='0' AND c.bcode like '%s%%' AND c.bName like '%s%%' ",m_strBm,m_strMc );
		i=m_combox.GetCurSel();
		if( i== CB_ERR || i == 0 );
		else {
			strSql+=" AND b.rcode='"+arrayLocal.GetAt(i-1)+"'";
		}
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		row=1;
		while(!recSet->adoEOF){
			for(i=0;i< cols ;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				m_grid.SetTextMatrix(row,i,str1);
			}
			row++;
			m_grid.AddItem("",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		recSet->Close();
	
		return ;
	}	


  m_grid.SetRedraw(true);;
}

void CResideBedSet::OnDblClickMshflexgrid1()
{
	if( DIALOG_FLAG == DIALOG_BED ) return;
	if( CheckSelectRow() == FAIL ) return;
	
	strBedCode=m_grid.GetTextMatrix(curRow,BEDCODE_POS);
	strBedName=m_grid.GetTextMatrix(curRow,ROOMNAME_POS)+"/"+m_grid.GetTextMatrix(curRow,BEDNAME_POS);
	CDialog::OnOK();
}
