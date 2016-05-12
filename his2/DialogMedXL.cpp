// DialogMedXL.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "DialogMedXL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogMedXL dialog


CDialogMedXL::CDialogMedXL(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogMedXL::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogMedXL)
	m_name = _T("");
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"黑体");
}


void CDialogMedXL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogMedXL)
	DDX_Control(pDX, IDOK_MODIFY, m_15);
	DDX_Control(pDX, IDOK_DELETE, m_14);
	DDX_Control(pDX, IDOK_ADD, m_13);
	DDX_Control(pDX, IDCANCEL, m_12);
	DDX_Control(pDX, IDC_EDIT_NAME, m_1);
	DDX_Control(pDX, IDC_COMBO_XL, m_xComboXL);
	DDX_Control(pDX, IDC_COMBO_DL, m_xComboDL);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogMedXL, CDialog)
	//{{AFX_MSG_MAP(CDialogMedXL)
	ON_BN_CLICKED(IDOK_DELETE, OnDelete)
	ON_BN_CLICKED(IDOK_ADD, OnAdd)
	ON_BN_CLICKED(IDOK_MODIFY, OnModify)
	ON_CBN_SELCHANGE(IDC_COMBO_DL, OnSelchangeComboDl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogMedXL message handlers

void CDialogMedXL::OnDelete() 
{
	// TODO: Add your control notification handler code here
	if(m_xComboDL.GetCurSel()==CB_ERR||m_xComboXL.GetCurSel()==CB_ERR)return; //如果未选择则返回
	CString strSql,strDLbm,strName;

	m_xComboDL.GetLBText(m_xComboDL.GetCurSel(),strDLbm);
	m_xComboXL.GetLBText(m_xComboXL.GetCurSel(),strName);

	strSql.Format("select dlbm from meddl where dlmc='%s' ",strDLbm);
	GetBm(strSql,strDLbm);
	try{
		HospitalConnect->BeginTrans();
		strSql.Format("delete from medxl where dlbm='%s' and xlmc='%s' ",strDLbm,strName);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		HospitalConnect->RollbackTrans();
		return;
	}
	MessageBox("成功将当前的小类别删除...","提示",MB_OK|MB_ICONINFORMATION);
	
//	strSql.Format("select xlmc from medxl where dlbm='%s' ",strDLbm);
//	ReadName(strSql,m_xComboXL);
	OnSelchangeComboDl();		
}

BOOL CDialogMedXL::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);	
	CString strSql;
	strSql.Format("select dlmc name from meddl");
	if(!ReadName(strSql,m_xComboDL))return false;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogMedXL::OnAdd() 
{
	// TODO: Add your control notification handler code here
	if(m_xComboDL.GetCurSel()==CB_ERR){
		MessageBox("请先选择要添加所属的大类别...","警告",MB_OK|MB_ICONINFORMATION);
		return;
	}
	CString strSql,DLname,DLbm,strAdd;

	m_xComboDL.GetLBText(m_xComboDL.GetCurSel(),DLname);
	strSql.Format("select dlbm from meddl where dlmc='%s' ",DLname);

	if(!GetBm(strSql,DLbm)){ //获取的大类别编码
		AfxMessageBox("READ DATABASE ERROR");
		return;
	}

	UpdateData();
	try{
		HospitalConnect->BeginTrans();

		strSql.Format("INSERT INTO  medxl (dlbm,xlbm,xlmc) values('%s', \
			(SELECT NVL(MAX(xlbm),10)+1 FROM medxl WHERE dlbm='%s' ),'%s') ",DLbm,DLbm,m_name);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		HospitalConnect->CommitTrans();

	}
	catch(_com_error e)
	{
		AfxMessageBox("read dl table error ");
		HospitalConnect->RollbackTrans();
		
		return;
	}
	MessageBox("成功将当前类别加入...","提示",MB_OK|MB_ICONINFORMATION);
	m_name="";
	UpdateData(false);
	OnSelchangeComboDl();	
}

void CDialogMedXL::OnModify() 
{
	if(m_xComboDL.GetCurSel()==CB_ERR||m_xComboXL.GetCurSel()==CB_ERR)return; //如果未选择则返回
	// TODO: Add your control notification handler code here
	CString dlbm,xlbm,strSql;
	m_xComboDL.GetLBText(m_xComboDL.GetCurSel(),dlbm);
	m_xComboXL.GetLBText(m_xComboXL.GetCurSel(),xlbm);

	strSql.Format("select dlbm from meddl where dlmc='%s' ",dlbm);
	if(!GetBm(strSql,dlbm))return;
	strSql.Format("select xlbm from medxl where dlbm='%s' and xlmc='%s' ",dlbm,xlbm);
	if(!GetBm(strSql,xlbm))return;

	UpdateData();
	strSql.Format("update medxl set xlmc='%s' where dlbm='%s' and xlbm='%s' ",m_name,dlbm,xlbm);
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
	MessageBox("小类别名称成功修改...","提示",MB_OK|MB_ICONINFORMATION);
	UpdateData(false);
	OnSelchangeComboDl();		// TODO: Add your control notification handler code here
	
}

BOOL CDialogMedXL::ReadName(CString strSql, CComboBox &combo)
{
	try{
		combo.ResetContent();
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF)
		{
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(0L)->Value);
			combo.AddString(strSql);
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

void CDialogMedXL::OnSelchangeComboDl() 
{
	if(m_xComboDL.GetCurSel()==CB_ERR)return; //如果未选择则返回

	CString strDL,strSql;
	m_xComboDL.GetLBText(m_xComboDL.GetCurSel(),strDL);

	strSql.Format("select medxl.xlmc from medxl,meddl where meddl.dlbm=medxl.dlbm AND dlmc='%s' ",strDL);

	if(!ReadName(strSql,m_xComboXL))return;
	
}

BOOL CDialogMedXL::GetBm(CString strSql, CString &bm)
{
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF)
		{
			bm=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value);
		}
		else bm="";
		recSet->Close();
		if(bm.IsEmpty())return false;
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("请检查数据库是否有异常...");
		recSet->Close();
		return false;
	}
	return true;
}
