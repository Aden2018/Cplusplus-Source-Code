// DialogMedDL.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "DialogMedDL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogMedDL dialog


CDialogMedDL::CDialogMedDL(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogMedDL::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogMedDL)
	m_strName = _T("");
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"黑体");
}


void CDialogMedDL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogMedDL)
	DDX_Control(pDX, IDOK_MODIFY, m_4);
	DDX_Control(pDX, IDOK_DELETE, m_3);
	DDX_Control(pDX, IDOK_ADD, m_2);
	DDX_Control(pDX, IDCANCEL, m_1);
	DDX_Control(pDX, IDC_EDIT_NAME, m_xx);
	DDX_Control(pDX, IDC_COMBO_NAME, m_xcCombo);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogMedDL, CDialog)
	//{{AFX_MSG_MAP(CDialogMedDL)
	ON_BN_CLICKED(IDOK_ADD, OnAdd)
	ON_BN_CLICKED(IDOK_DELETE, OnDelete)
	ON_BN_CLICKED(IDOK_MODIFY, OnModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogMedDL message handlers

void CDialogMedDL::OnAdd() 
{
	UpdateData();
	if(m_strName.IsEmpty()){
		AfxMessageBox("请输入药品的大类别...然后再添加...");
		return;
	}
	try{
		CString strSql;
		HospitalConnect->BeginTrans();
		
		strSql.Format("INSERT INTO meddl(dlbm,dlmc) values( (SELECT NVL(\
			MAX(dlbm),10)+1 FROM meddl),'%s' ) ",m_strName );
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
	
		HospitalConnect->CommitTrans();

		
	}
	catch(_com_error e)
	{
		AfxMessageBox("读写大类错误 ");
		HospitalConnect->RollbackTrans();
		
		return;
	}
	m_strName="";
	UpdateData(false);
	ReadName(); //更改用户所做的类别改变
	AfxMessageBox("当前类别成功加入数据库...");
	GetDlgItem(IDC_EDIT_NAME)->SetFocus();	
}

void CDialogMedDL::OnDelete() 
{
	UpdateData();
	CString strSql,bm,str;
	if(m_xcCombo.GetCurSel()==CB_ERR){
		AfxMessageBox("请先选择要删除的类别....");
		return;
	}
	m_xcCombo.GetLBText(m_xcCombo.GetCurSel(),str);

	try{
		strSql.Format("select * from meddl where dlmc='%s' ",str);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF)
		{
			bm=(char*)_bstr_t(recSet->GetCollect("dlbm"));
		}
		else bm="";
		recSet->Close();
		if(bm.IsEmpty())return ;
		HospitalConnect->BeginTrans();
		strSql.Format("delete from meddl where dlbm='%s' ",bm);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		strSql.Format("delete from medxl where dlbm='%s' ",bm);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();

		
	}
	catch(_com_error e)
	{
		AfxMessageBox("请检查数据库是否有异常...");
		recSet->Close();
		HospitalConnect->RollbackTrans();
		return ;
	}

	m_strName="";
	ReadName(); 
	MessageBox("当前所选的类别成功删除...","提示",MB_OK|MB_ICONINFORMATION);
	UpdateData(false);	
}

void CDialogMedDL::OnModify() 
{
	UpdateData();
	CString strSql,str;
	if(m_xcCombo.GetCurSel()==CB_ERR){
		AfxMessageBox("请先选择要修改的类别....");
		return;
	}
	m_xcCombo.GetLBText(m_xcCombo.GetCurSel(),str);
	strSql.Format("update meddl set dlmc='%s' where dlmc='%s' ",m_strName,str);
	try{
		HospitalConnect->BeginTrans();
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		HospitalConnect->RollbackTrans();
		
		return;		
	}

	MessageBox("类别成功修改...","提示",MB_OK|MB_ICONINFORMATION);
	ReadName();	
	m_strName="";
	ReadName();
	UpdateData(false);// TODO: Add your control notification handler code here
	
}

BOOL CDialogMedDL::ReadName()
{
	try{
		m_xcCombo.ResetContent();
		CString strSql;
		strSql.Format("select dlmc from meddl ORDER BY DLBM");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF)
		{
			strSql=(char*)_bstr_t(recSet->GetCollect("dlmc").vt==VT_NULL?" ":recSet->GetCollect("dlmc"));
			m_xcCombo.AddString(strSql);
			recSet->MoveNext();
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox("请检查数据库是否有异常...");
		recSet->Close();
		return false;
	}
	return true;
}

BOOL CDialogMedDL::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	if(!ReadName())return false;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
