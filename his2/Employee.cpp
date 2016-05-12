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
	strTitle.Format("�������䱣����Ա");
	fontTitle.CreatePointFont(200,"����");
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
		strSql.Format("select ��������,���ű��� from �����ű� ORDER BY �������� ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(0L)->Value );
			c_depart.AddString(strSql);
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(1L)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(1L)->Value );
			m_depart.Add(strSql);

			recSet->MoveNext();
		}
		recSet->Close();
		strSql.Format(" SELECT MAX(����)+1 FROM  ְ�����������  ");
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

	strSql.Format("SELECT ���� FROM ְ����������� WHERE ����='%s' ",strTmp);
	if( !COtherDecharge::GetStringTitle( strSql).IsEmpty() ){
		AfxMessageBox("��ǰ�û�����Ѿ�����ʹ��!!!�����³�����������!!!");
		return;
	}
	
	c_name.GetWindowText(strT1);//����
	if( c_depart.GetCurSel() == CB_ERR || c_sort.GetCurSel() == CB_ERR || c_property.GetCurSel() == CB_ERR || strT1.IsEmpty() )
	{
		AfxMessageBox("�뽫������Ŀ��д�������ٵ��ȷ��!!!");
		return;
		
	}
	c_sex.GetWindowText(strT2); //�Ա�
	c_sort.GetWindowText(strT3); //���
	c_property.GetWindowText(strT4); //����
	strSql.Format("INSERT INTO ְ����������� (����,����,�Ա�,��������,��������,���,\
		���ű���,��������,pass ) VALUES('%s','%s','%s',to_date(%s,'yyyymmdd'),\
		to_date(%s,'yyyymmdd'),'%s','%s','%s','%s') ",strTmp,strT1,strT2,\
		m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d"),strT3,m_depart.GetAt(c_depart.GetCurSel()),\
		strT4,strTmp);

	if(COtherDecharge::WriteSQL(strSql)){
		AfxMessageBox("��ǰ��Ա�����ɹ�...");
		strSql.Format(" SELECT MAX(����)+1 FROM  ְ����������� ");
		c_kahao.SetWindowText(COtherDecharge::GetStringTitle(strSql));


	}
	else AfxMessageBox("�����Աʧ��..����ϵ���������Ա!!");



}
