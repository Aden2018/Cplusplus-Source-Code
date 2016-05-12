// OperatorAdd.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "OperatorAdd.h"
#include "dialogMedXl.h"
#include "otherDecharge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COperatorAdd dialog


COperatorAdd::COperatorAdd(CWnd* pParent /*=NULL*/)
	: CDialog(COperatorAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(COperatorAdd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	flag=0;
	fontTitle.CreatePointFont(200,"宋体");
}


void COperatorAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COperatorAdd)
	DDX_Control(pDX, IDC_EDIT_PASSWORD2, pass2);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, pass1);
	DDX_Control(pDX, IDC_EDIT_NAME, name);
	DDX_Control(pDX, IDC_EDIT_ATTRIBUTE, attr);
	DDX_Control(pDX, IDC_COMBO1, combo1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COperatorAdd, CDialog)
	//{{AFX_MSG_MAP(COperatorAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COperatorAdd message handlers

BOOL COperatorAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	SetWindowText(strTitle);

	CString strSql;
	strSql.Format("SELECT kfmc FROM storeRoom order by kfmc ");
	if( !CDialogMedXL::ReadName(strSql,combo1) ) {
		AfxMessageBox("读取数据出错!!!");
		return false;
	}

	if( flag == 1 ) { //新增



	}
	else if(flag == 2) { //修改
		name.SetWindowText(str[2]);
		pass1.SetWindowText(str[4]);
		pass2.SetWindowText(str[4]);
		attr.SetWindowText(str[3]);
		combo1.SelectString(-1,str[0]);

	}
	else return false;

	CenterWindow();
	AnimateWindow(m_hWnd,300,AW_SLIDE|AW_HOR_POSITIVE);
	Invalidate();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COperatorAdd::OnOK() 
{
	UpdateData();
	CString strT1,strT2,strSql,strT3,strT4;
	pass1.GetWindowText(strT3);
	pass2.GetWindowText(strT1);
	if( combo1.GetCurSel() == CB_ERR || strT3.Compare(strT1) !=0 ){
		AfxMessageBox("您没有选择所属库房或者两次密码输入不一致！！");
		return;
	}
	name.GetWindowText(strT1); //姓名
	attr.GetWindowText(strT2);//职责
	combo1.GetLBText(combo1.GetCurSel(),strT4);//库房名称

	if( flag == 1 ){ //新增
		strSql.Format(" INSERT INTO OPERATOR (rybm,name,attribute,kfbm,pass,sfdel) \
			VALUES( (select NVL(max(rybm),0)+1 FROM operator),'%s','%s',\
			(SELECT distinct kfbm FROM storeroom WHERE kfmc='%s'),'%s','n') ",\
			strT1,strT2,strT4,strT3 );
		if(!COtherDecharge::WriteSQL(strSql)){
			AfxMessageBox("添加失败");
			return;
		}
	

	}
	else if(flag == 2){
		strSql.Format(" UPDATE operator SET name='%s',attribute='%s',kfbm=\
			(SELECT distinct kfbm FROM storeroom WHERE kfmc='%s'),\
			pass='%s' WHERE rybm='%s' ",strT1,strT2,strT4,strT3,str[1] );
		if(!COtherDecharge::WriteSQL(strSql)){
			AfxMessageBox("修改失败");
			return;
		}

	}
	CDialog::OnOK();
}
