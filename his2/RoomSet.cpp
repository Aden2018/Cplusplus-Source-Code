// RoomSet.cpp: implementation of the CRoomSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "RoomSet.h"
#include "roomsetAdd.h"
#include "roomsetmodify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRoomSet::CRoomSet()
{
	strTitle="��������ѯ";
	arrayLocal.RemoveAll();
}

CRoomSet::~CRoomSet()
{

}

void CRoomSet::OnMenuResideLocalAdd() //����
{
	CRoomSetAdd sa;
	if( sa.DoModal()==IDOK) ;


}

void CRoomSet::OnMenuResideLocalRefresh()
{
	UpdateData();
	SetGridHead();
	CString strSql,str1;
	m_grid.SetRedraw(false);
	long row,i,cols;

	try{
	strSql.Format("select a.llocal,a.lname,b.rcode,b.rname,b.rremark from \
		lsq_reside_local a,lsq_reside_room b where a.llocal=b.rlocal and b.Reffect='1' \
		AND b.rcode like '%s%%'  AND b.rname like '%s%%' ",m_strBm,m_strMc);
	i=m_combox.GetCurSel();
	if( i == CB_ERR || i == 0 );
	else{
		strSql+=" AND a.llocal='"+arrayLocal.GetAt(i-1)+"'";
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
			m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
	
		return ;
	}	


  m_grid.SetRedraw(true);;
	
}

void CRoomSet::OnMenuResideLocalDel()
{
	if( CheckSelectRow() == FAIL) return;

	CString strBm2=m_grid.GetTextMatrix(curRow,2); //�������
	CString strSql;
	strSql.Format("ȷ��Ҫɾ��: %s / %s ",m_grid.GetTextMatrix(curRow,2),m_grid.GetTextMatrix(curRow,3) );
	if( MessageBox(strSql,"��ʾ",MB_OKCANCEL|MB_ICONINFORMATION  ) == IDCANCEL) return;

	strSql.Format("update lsq_reside_room set Reffect='0' Where  rcode='%s' ",strBm2);
	if( COtherDecharge::WriteSQL(strSql) ){
		AfxMessageBox("ɾ���ɹ�");
		m_grid.RemoveItem(curRow);
	}
	else AfxMessageBox("ɾ��ʧ��");

}

void CRoomSet::OnMenuResideLocalModify()
{
	if( CheckSelectRow() == FAIL) return;
	CRoomSetModify sm;

	sm.strLocal=m_grid.GetTextMatrix(curRow,0); //�������;
	sm.strLocalName=m_grid.GetTextMatrix(curRow,1); //��������
	sm.strCode=m_grid.GetTextMatrix(curRow,2); //�������
	sm.m_name=m_grid.GetTextMatrix(curRow,3); //��������
	sm.m_remark=m_grid.GetTextMatrix(curRow,4); //��ע

	if( sm.DoModal()== IDOK) OnMenuResideLocalRefresh();
}

BOOL CRoomSet::OnInitDialog()
{
	CResideLocalSet::OnInitDialog();
	CString strSql;
	strSql.Format(" SELECT llocal,lname FROM lsq_reside_local WHERE leffect='1' ");
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

void CRoomSet::SetGridHead()
{
	CString HeadTitle[]={"�������","��������","�������","��������","��ע"};
	long  headWidth[]={0,2000,1000,2000,2400};
		
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
	m_grid.SetColAlignment(0,4);

}
