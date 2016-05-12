// MedcodeModify.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "MedcodeModify.h"
#include "qiuXpButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedcodeModify dialog


CMedcodeModify::CMedcodeModify(CWnd* pParent /*=NULL*/)
	: CDialog(CMedcodeModify::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMedcodeModify)
	m_comment = _T("");
	m_dw = _T("");
	m_gg = _T("");
	m_max = _T("");
	m_mc = _T("");
	m_min = _T("");
	m_py = _T("");
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"����");
	flagMode=ADD;
}


void CMedcodeModify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedcodeModify)
	DDX_Control(pDX, IDC_EDIT_BM, c_bm);
	DDX_Control(pDX, IDC_COMBO2, c_comXL);
	DDX_Control(pDX, IDC_COMBO1, c_comDL);
	DDX_Text(pDX, IDC_EDIT_COMMENT, m_comment);
	DDX_Text(pDX, IDC_EDIT_DW, m_dw);
	DDX_Text(pDX, IDC_EDIT_GG, m_gg);
	DDX_Text(pDX, IDC_EDIT_MAX, m_max);
	DDX_Text(pDX, IDC_EDIT_MC, m_mc);
	DDX_Text(pDX, IDC_EDIT_MIN, m_min);
	DDX_Text(pDX, IDC_EDIT_PY, m_py);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedcodeModify, CDialog)
	//{{AFX_MSG_MAP(CMedcodeModify)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedcodeModify message handlers

BOOL CMedcodeModify::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString strSql;
	try{
		c_comDL.AddString("   ");
		strSql.Format("select dlmc from meddl ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetCollect("dlmc").vt==VT_NULL?" ":recSet->GetCollect("dlmc"));
			c_comDL.AddString(strSql);
			recSet->MoveNext();
		
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return false;
	}	// TODO: Add extra initialization here
	c_bm.SetReadOnly();
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("ҩƷ��������ά��");

	if( flagMode == MODIFY ) {
		UpdateData(false);
		c_bm.SetWindowText(strOldBm);
		c_comDL.SelectString(-1,dlmc);
		try{
			strSql.Format("select xlmc from medxl a,meddl b WHERE a.dlbm=b.dlbm AND DLmc='%s' ",dlmc);
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			while(!recSet->adoEOF){
				strSql=(char*)_bstr_t(recSet->GetCollect("xlmc").vt==VT_NULL?" ":recSet->GetCollect("xlmc"));
				c_comXL.AddString(strSql);
				recSet->MoveNext();
				
			}
			recSet->Close();
			
		}
		catch(_com_error e)
		{
			AfxMessageBox("���ִ���,����SQL���...");
			return false;
		}	
		c_comXL.SelectString(-1,xlmc);
		
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMedcodeModify::OnSelchangeCombo1()  //����ѡ��
{
	CString strSql,strmc;

	if( c_comDL.GetCurSel() == 0 || c_comDL.GetCurSel() == CB_ERR ) return;

	c_comXL.ResetContent();

	c_comDL.GetLBText(c_comDL.GetCurSel(),strmc);
	try{
		strSql.Format("select xlmc from medxl a,meddl b WHERE a.dlbm=b.dlbm AND DLmc='%s' ",strmc);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetCollect("xlmc").vt==VT_NULL?" ":recSet->GetCollect("xlmc"));
			c_comXL.AddString(strSql);
			recSet->MoveNext();
		
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return ;
	}	
	c_bm.SetWindowText("");
	
}

void CMedcodeModify::OnSelchangeCombo2() //С��ѡ��
{
	CString strSql,strdl,strxl;
	if( c_comDL.GetCurSel() == 0 || c_comDL.GetCurSel() == CB_ERR
		|| c_comXL.GetCurSel() == CB_ERR ) return;

	c_comDL.GetLBText(c_comDL.GetCurSel(),strdl);
	c_comXL.GetLBText(c_comXL.GetCurSel(),strxl);
	try{
		strSql.Format("select a.dlbm dlbm,a.xlbm xlbm from \
			medxl a,meddl b WHERE a.dlbm=b.dlbm AND DLmc='%s' and xlmc='%s' ",strdl,strxl);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			strdl=(char*)_bstr_t(recSet->GetCollect("dlbm").vt==VT_NULL?" ":recSet->GetCollect("dlbm"));
			strxl=(char*)_bstr_t(recSet->GetCollect("xlbm").vt==VT_NULL?" ":recSet->GetCollect("xlbm"));
			recSet->Close();
		
		}
		else{

			recSet->Close();
			return;
		}
		strdl+=strxl;
		strSql.Format(" SELECT max(bm)+1 xlbm FROM medcode where substr(bm,1,4)='%s' ",strdl );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			strxl=(char*)_bstr_t(recSet->GetCollect("xlbm").vt==VT_NULL?" ":recSet->GetCollect("xlbm"));
		
		}
		recSet->Close();
		if( strxl.GetLength() > 8 ) {
			AfxMessageBox("����ϵ���������Ա,��ǰϵͳ�б�����ܷ�������...");
			return;
		}
		c_bm.SetWindowText(strxl);


	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return ;
	}	

	
}
void CMedcodeModify::OnOK() 
{
	if( c_comXL.GetCurSel() == CB_ERR ){
		AfxMessageBox("����ѡ��С�����...");
		return;
	}

	UpdateData();
	CString strSql,strbm;
	c_bm.GetWindowText(strbm);
	try{
		HospitalConnect->BeginTrans();
		if ( flagMode == MODIFY ) 
		{
			strSql.Format(" DELETE FROM medcode WHERE bm='%s' ",strOldBm);
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		}
		strSql.Format("INSERT INTO medcode(dlbm,xlbm,bm,mc,gg,dw,maxkc,minkc,py,bz ) \
			values('%s','%s','%s','%s','%s','%s',%.2f,%.2f,'%s','%s' ) ",strbm.Left(2),\
			strbm.Mid(2,2),strbm,m_mc,m_gg,m_dw,atof(m_max),atof(m_min),m_py,m_comment );
	
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		
		HospitalConnect->CommitTrans();

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		HospitalConnect->RollbackTrans();
		return;
	}
	switch( flagMode )
	{
	case ADD	:AfxMessageBox("��������ɹ�...");break;
	case MODIFY :AfxMessageBox("�޸ı���ɹ�...");break;
	}

	CDialog::OnOK();
}

BOOL CMedcodeModify::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam == VK_RETURN && GetFocus()->m_hWnd != GetDlgItem(IDOK)->m_hWnd ) 
		pMsg->wParam = VK_TAB ;
	
	return CDialog::PreTranslateMessage(pMsg);
}
