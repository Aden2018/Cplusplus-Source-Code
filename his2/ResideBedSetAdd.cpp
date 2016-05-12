// ResideBedSetAdd.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "ResideBedSetAdd.h"
#include "qiuXpbutton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResideBedSetAdd dialog


CResideBedSetAdd::CResideBedSetAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CResideBedSetAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResideBedSetAdd)
	m_strName = _T("");
	m_strRemark = _T("");
	m_price = 0.0;
	//}}AFX_DATA_INIT
	localArray.RemoveAll();
	roomArray.RemoveAll();

	strTitle="新增床位";

}


void CResideBedSetAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResideBedSetAdd)
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, IDCANCEL, m_1);
	DDX_Control(pDX, IDC_COMBO_ROOM, m_combox_room);
	DDX_Control(pDX, IDC_COMBO_LOCAL, m_combox_local);
	DDX_Text(pDX, IDC_EDIT_BED_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_BED_REMARK, m_strRemark);
	DDX_Text(pDX, IDC_EDIT_BED_PRICE, m_price);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResideBedSetAdd, CDialog)
	//{{AFX_MSG_MAP(CResideBedSetAdd)
	ON_CBN_SELCHANGE(IDC_COMBO_LOCAL, OnSelchangeComboLocal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResideBedSetAdd message handlers

void CResideBedSetAdd::OnOK() 
{
	UpdateData();
	if( m_combox_local.GetCurSel() == CB_ERR || m_combox_room.GetCurSel() == CB_ERR ) {
		AfxMessageBox("请先选择所属的病区或房间");
		return;
	}
	strSql.Format("Insert into lsq_reside_bed ( blocal,broom,bCode,bname,bprice,bremark) values( \
		'%s','%s',(select Ltrim(to_char(NVL(max(Bcode),0)+1,'000000009')) from lsq_reside_Bed ),\
		'%s',%.2f,'%s' ) ",localArray.GetAt(m_combox_local.GetCurSel()),roomArray.GetAt(m_combox_room.GetCurSel()),\
		m_strName,m_price,m_strRemark);

	if( COtherDecharge::WriteSQL(strSql) ) {
		AfxMessageBox("新增成功");
		CDialog::OnOK();

	}
	else AfxMessageBox("新增失败");


}

BOOL CResideBedSetAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&CHis2App::fontTitle);
	const long NAME=1;   //名称
	const long CODE=0;	//代码
	strSql.Format("Select llocal,lname from lsq_reside_local Where leffect='1' ");
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(CODE))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(CODE))->Value);
				localArray.Add(strSql);
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(NAME))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(NAME))->Value);
				m_combox_local.AddString(strSql);

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

void CResideBedSetAdd::OnSelchangeComboLocal() 
{
	const long NAME=1;   //名称
	const long CODE=0;	//代码
	int curSel=m_combox_local.GetCurSel();
	m_combox_room.ResetContent();
	if( curSel == CB_ERR ){
		return;
	}
	
	strSql.Format("Select RCode,Rname from lsq_reside_room Where Reffect='1' and rlocal='%s' ",localArray.GetAt(curSel));
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(CODE))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(CODE))->Value);
				roomArray.Add(strSql);
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(NAME))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(NAME))->Value);
				m_combox_room.AddString(strSql);

				recSet->MoveNext();
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage() );
		recSet->Close();
		return ;
	}
	
}
