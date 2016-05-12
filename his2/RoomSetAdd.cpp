// RoomSetAdd.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "RoomSetAdd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomSetAdd dialog


CRoomSetAdd::CRoomSetAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomSetAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoomSetAdd)
	m_name = _T("");
	m_remark = _T("");
	//}}AFX_DATA_INIT
	localArray.RemoveAll();  //��λ
	m_combox.ResetContent(); //
	strTitle="��������";
}


void CRoomSetAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomSetAdd)
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, IDCANCEL, m_1);
	DDX_Control(pDX, IDC_COMBO1, m_combox);
	DDX_Text(pDX, IDC_EDIT_ROOM_ADD, m_name);
	DDX_Text(pDX, IDC_EDIT_ROOM_REMARK, m_remark);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRoomSetAdd, CDialog)
	//{{AFX_MSG_MAP(CRoomSetAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomSetAdd message handlers

BOOL CRoomSetAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&CHis2App::fontTitle);
	const long NAME=1;   //����
	const long CODE=0;	//����
	strSql.Format("Select llocal,lname from lsq_reside_local Where leffect='1' ");
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(CODE))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(CODE))->Value);
				localArray.Add(strSql);
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(NAME))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(NAME))->Value);
				m_combox.AddString(strSql);

				recSet->MoveNext();
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage() );
		recSet->Close();
		return false;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRoomSetAdd::OnOK() 
{
	const int NOFIND=-1;
	UpdateData();
	if ( ! (m_name.Find("'") == NOFIND && m_name.Find(";") == NOFIND  && \
		m_remark.Find("'") == NOFIND && m_remark.Find(";") == NOFIND && ! m_name.IsEmpty() && m_combox.GetCurSel() != CB_ERR )  )
		AfxMessageBox("����������в��ܺ��õ����ż��ֺŵ������ַ�");
	CString strLocal=localArray.GetAt(m_combox.GetCurSel());

	strSql.Format("Insert into lsq_reside_room ( rlocal,rcode,rname,rremark) values('%s',\
		(select Ltrim(to_char(NVL(max(rcode),0)+1,'009')) from lsq_reside_room ),\
		'%s','%s' ) ",strLocal,m_name,m_remark);
	if( COtherDecharge::WriteSQL(strSql) )AfxMessageBox("�����ɹ�");
	else  AfxMessageBox("����ʧ��...");
	CDialog::OnOK();
}
