// Employee.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "Employee.h"
#include "otherDecharge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmployee dialog


CEmployee::CEmployee(CWnd* pParent /*=NULL*/)
	: CDialog(CEmployee::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmployee)
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	strTitle.Format("新增补充保险人员");
	fontTitle.CreatePointFont(200,"黑体");
}


void CEmployee::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmployee)
	DDX_Control(pDX, IDC_COMBO_DEPART, c_depart);
	DDX_Control(pDX, IDC_EDIT1, c_kahao);
	DDX_Control(pDX, IDC_EDIT_NAME, c_name);
	DDX_Control(pDX, IDC_COMBO_SORT, c_sort);
	DDX_Control(pDX, IDC_COMBO_SEX, c_sex);
	DDX_Control(pDX, IDC_COMBO_PROPERTY, c_property);
	DDX_Control(pDX, IDCANCEL, m_b3);
	DDX_Control(pDX, IDOK, m_b2);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmployee, CDialog)
	//{{AFX_MSG_MAP(CEmployee)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmployee message handlers

BOOL CEmployee::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_HEAD)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_HEAD)->SetWindowText(strTitle);
	c_sex.SetCurSel(0);
	CString strSql;
	try{
		strSql.Format("select 部门名称,部门编码 from 厂部门表 ORDER BY 部门名称 ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(0L)->Value );
			c_depart.AddString(strSql);
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(1L)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(1L)->Value );
			m_depart.Add(strSql);

			recSet->MoveNext();
		}
		recSet->Close();
		strSql.Format(" SELECT MAX(卡号)+1 FROM  职工基本情况表  ");
		c_kahao.SetWindowText(COtherDecharge::GetStringTitle(strSql));

	}
	catch(_com_error e)
	{
		recSet->Close();
		return false;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEmployee::OnOK() 
{
	UpdateData();
	CString strSql,strTmp,strT1,strT2,strT3,strT4,strT5;
	c_kahao.GetWindowText(strTmp);

	strTmp.Remove(' ');
	if( strTmp.IsEmpty() ) return;

	strSql.Format("SELECT 姓名 FROM 职工基本情况表 WHERE 卡号='%s' ",strTmp);
	if( !COtherDecharge::GetStringTitle( strSql).IsEmpty() ){
		AfxMessageBox("当前用户编号已经有人使用!!!请重新尝试其他编码!!!");
		return;
	}
	
	c_name.GetWindowText(strT1);//姓名
	if( c_depart.GetCurSel() == CB_ERR || c_sort.GetCurSel() == CB_ERR || c_property.GetCurSel() == CB_ERR || strT1.IsEmpty() )
	{
		AfxMessageBox("请将所有项目填写完整后再点击确定!!!");
		return;
		
	}
	c_sex.GetWindowText(strT2); //性别
	c_sort.GetWindowText(strT3); //类别
	c_property.GetWindowText(strT4); //性质
	strSql.Format("INSERT INTO 职工基本情况表 (卡号,姓名,性别,出生日期,工作日期,类别,\
		部门编码,工作性质,pass ) VALUES('%s','%s','%s',to_date(%s,'yyyymmdd'),\
		to_date(%s,'yyyymmdd'),'%s','%s','%s','%s') ",strTmp,strT1,strT2,\
		m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d"),strT3,m_depart.GetAt(c_depart.GetCurSel()),\
		strT4,strTmp);

	if(COtherDecharge::WriteSQL(strSql)){
		AfxMessageBox("当前人员新增成功...");
		strSql.Format(" SELECT MAX(卡号)+1 FROM  职工基本情况表 ");
		c_kahao.SetWindowText(COtherDecharge::GetStringTitle(strSql));


	}
	else AfxMessageBox("添加人员失败..请联系程序设计人员!!");



}
