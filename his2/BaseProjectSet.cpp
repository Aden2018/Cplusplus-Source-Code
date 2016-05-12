// BaseProjectSet.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "BaseProjectSet.h"
#include "DialogMedXL.h"
#include "otherDecharge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseProjectSet dialog


CBaseProjectSet::CBaseProjectSet(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseProjectSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBaseProjectSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"����");
	strTitle="Please Set title";
	flag=0;
}


void CBaseProjectSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBaseProjectSet)
	DDX_Control(pDX, IDC_EDIT_CASH_STANDARD, editStandardCash);
	DDX_Control(pDX, IDC_EDIT_CODE, editCode);
	DDX_Control(pDX, IDC_EDIT_PY, editPY);
	DDX_Control(pDX, IDC_EDIT2, edit2);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_COMBO1, combo1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBaseProjectSet, CDialog)
	//{{AFX_MSG_MAP(CBaseProjectSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseProjectSet message handlers

BOOL CBaseProjectSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_HEAD)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_HEAD)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_CASH_STANDARD)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_CASH_STANDARD)->ShowWindow(SW_SHOW);

	SetWindowText(strTitle);
	

	if( !CDialogMedXL::ReadName(strSql,combo1) ) {
		AfxMessageBox("��ȡ���ݳ���!!!");
		return false;
	}

	if( flag == 1 ) { //����



	}
	else if(flag == 2) { //�޸�
		combo1.SelectString(-1,str[0]);
		edit1.SetWindowText(str[2]);
		edit2.SetWindowText(str[3]);

		editPY.SetWindowText(str[4]);
		editCode.SetWindowText(str[5]);
		editStandardCash.SetWindowText(str[6]);
		

	}
	else return false;

	CenterWindow();
	AnimateWindow(m_hWnd,300,AW_SLIDE|AW_HOR_POSITIVE);
	Invalidate();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBaseProjectSet::OnOK() 
{
	
	UpdateData();

	CString strT1,strT2,strSql,strT3,strT4,strT5,strT6;
	combo1.GetWindowText(strT1);
	edit1.GetWindowText(strT2);
	edit2.GetWindowText(strT3);
	editPY.GetWindowText(strT4);
	editCode.GetWindowText(strT5);
	editStandardCash.GetWindowText(strT6);

	if( strT1.IsEmpty() || strT2.IsEmpty() || strT3.IsEmpty() || strT4.IsEmpty() || strT5.IsEmpty() ){
		AfxMessageBox("�뽫����������д��ȷ�ٽ��в���!!!");
		return;
	}

	if( flag == 1 ){ //����
		strSql.Format(" INSERT INTO ������Ŀ��(���ñ���,���ô���,��������,��׼���,name_py,name_BM,standard_cash ) \
			VALUES( (select NVL(max(���ñ���),0)+1 FROM ������Ŀ��),'%s','%s',\
			%.2f ,'%s','%s' ,%.2f ) ",strT1,strT2,atof(strT3),strT4,strT5,atof(strT6) );
		if(!COtherDecharge::WriteSQL(strSql)){
			AfxMessageBox("���ʧ��");
			return;
		}
	

	}
	else if(flag == 2){ 

		strSql.Format(" UPDATE ������Ŀ�� SET ���ô���='%s',��������='%s',��׼���=%.2f ,name_py='%s',name_bm='%s',standard_cash=%.2f \
			WHERE ���ñ���='%s' ",strT1,strT2,atof(strT3),strT4,strT5,atof(strT6),str[1] );

		if(!COtherDecharge::WriteSQL(strSql)){
			AfxMessageBox("�޸�ʧ��");
			return;
		}

	}
	CDialog::OnOK();	
}

void CBaseProjectSet::OnCancel() 
{
	
	CDialog::OnCancel();
}
