// EmployeeModify.cpp: implementation of the CEmployeeModify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "EmployeeModify.h"
#include "otherDecharge.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEmployeeModify::CEmployeeModify()
{

}

CEmployeeModify::~CEmployeeModify()
{

}

BOOL CEmployeeModify::OnInitDialog()
{
	CEmployee::OnInitDialog();

	CString strSql;
	long i=0;
	try{
		strSql.Format("select ����,����,�Ա�,��������,��������,��������,\
			��������,��� from ְ����������� t,�����ű� x WHERE x.���ű���=t.���ű��� AND ����='%s' ",strTmp);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(i)->Value );
			c_kahao.SetWindowText(strSql);i++; 
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(i)->Value );
			c_name.SetWindowText(strSql);i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(i)->Value );
			c_sex.SelectString(-1,strSql);i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(i)->Value );
			m_date1.ParseDateTime(strSql);i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(i)->Value );
			m_date2.ParseDateTime(strSql);i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(i)->Value );
			c_depart.SelectString(-1,strSql);i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(i)->Value );
			c_property.SelectString(-1,strSql);i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(i)->Value );
			c_sort.SelectString(-1,strSql);i++;

		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		recSet->Close();
		return false;
	}
	UpdateData(false);
	c_kahao.EnableWindow(false);
	return true;

}

void CEmployeeModify::OnOK()
{
	UpdateData();
	CString strSql,strT1,strT2,strT3,strT4,strT5;


	c_name.GetWindowText(strT1);//����
	if( c_depart.GetCurSel() == CB_ERR || c_sort.GetCurSel() == CB_ERR || c_property.GetCurSel() == CB_ERR || strT1.IsEmpty() )
	{
		AfxMessageBox("�뽫������Ŀ��д�������ٵ��ȷ��!!!");
		return;
		
	}
	c_sex.GetWindowText(strT2); //�Ա�
	c_sort.GetWindowText(strT3); //���
	c_property.GetWindowText(strT4); //����
	strSql.Format("UPDATE  ְ����������� SET ����='%s',�Ա�='%s',��������=to_date('%s','yyyymmdd'),\
		��������=to_date('%s','yyyymmdd'),���='%s',���ű���='%s',��������='%s'  \
		WHERE ����='%s' ",strT1,strT2,m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d"),\
		strT3,m_depart.GetAt(c_depart.GetCurSel()),strT4,strTmp);
	if(COtherDecharge::WriteSQL(strSql)){
		AfxMessageBox("��ǰ��Ա�޸ĳɹ�...");
		CDialog::OnOK();
		
	}
	else AfxMessageBox("�޸���Աʧ��..����ϵ���������Ա!!");


}
