// RelateModify.cpp: implementation of the CRelateModify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "RelateModify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRelateModify::CRelateModify()
{

}

CRelateModify::~CRelateModify()
{

}
BOOL CRelateModify::OnInitDialog()
{
	CRelateAdd::OnInitDialog();
	//{"TEMP","编码","姓名","性别","供养性质","余额","供养人","所属部",\
		"工作性质","出生日期","年龄"};
	GetDlgItem(IDC_STATIC_HEAD)->SetWindowText("供养亲属人员修改");
	c_bm.SetWindowText(strPass[1]);
	c_name.SetWindowText(strPass[2]);
	if( strPass[3] == "男" ) c_sex.SetCurSel(0);
	else if ( strPass[3] == "女" ) c_sex.SetCurSel(1);
	c_type.ResetContent();
	c_type.AddString(strPass[4]);
	c_type.SetCurSel(0);
	c_type.EnableWindow(false);

	m_date.ParseDateTime(strPass[9] );
	GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(false);
	c_money.SetWindowText(strPass[5]);
	c_emp.SetWindowText(strPass[6]);
	UpdateData(false);
	return true;
}
void CRelateModify::OnOK()
{
	
	UpdateData();
	CString strName,strSex,strSql;
	if( c_sex.GetCurSel() == CB_ERR ) {
		AfxMessageBox("请先选择好性别再进行操作!!");
		return;
	}
	c_name.GetWindowText(strName);
	c_sex.GetLBText(c_sex.GetCurSel(),strSex);

	if( strName == strPass[2] && strSex== strPass[3] ) CDialog::OnCancel();
	else 
	{
		try{
			strSql.Format(" UPDATE codeQingShu SET xm='%s',xb='%s' WHERE bm='%s' and \
				zxriqi is NULL ",strName,strSex,strPass[1] );
			HospitalConnect->BeginTrans();
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			HospitalConnect->CommitTrans();

		}
		catch(_com_error e)
		{
			AfxMessageBox(strSql);
			AfxMessageBox(e.ErrorMessage() );
			HospitalConnect->RollbackTrans();
			return;
		}
		AfxMessageBox("成功更改当前信息!!!");
		CDialog::OnOK();

	}
	
	
}
