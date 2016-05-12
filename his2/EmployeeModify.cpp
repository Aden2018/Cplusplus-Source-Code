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
		strSql.Format("select 卡号,姓名,性别,出生日期,工作日期,部门名称,\
			工作性质,类别 from 职工基本情况表 t,厂部门表 x WHERE x.部门编码=t.部门编码 AND 卡号='%s' ",strTmp);
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


	c_name.GetWindowText(strT1);//姓名
	if( c_depart.GetCurSel() == CB_ERR || c_sort.GetCurSel() == CB_ERR || c_property.GetCurSel() == CB_ERR || strT1.IsEmpty() )
	{
		AfxMessageBox("请将所有项目填写完整后再点击确定!!!");
		return;
		
	}
	c_sex.GetWindowText(strT2); //性别
	c_sort.GetWindowText(strT3); //类别
	c_property.GetWindowText(strT4); //性质
	strSql.Format("UPDATE  职工基本情况表 SET 姓名='%s',性别='%s',出生日期=to_date('%s','yyyymmdd'),\
		工作日期=to_date('%s','yyyymmdd'),类别='%s',部门编码='%s',工作性质='%s'  \
		WHERE 卡号='%s' ",strT1,strT2,m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d"),\
		strT3,m_depart.GetAt(c_depart.GetCurSel()),strT4,strTmp);
	if(COtherDecharge::WriteSQL(strSql)){
		AfxMessageBox("当前人员修改成功...");
		CDialog::OnOK();
		
	}
	else AfxMessageBox("修改人员失败..请联系程序设计人员!!");


}
