// CodeGysEdit.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "CodeGysEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeGysEdit dialog


CCodeGysEdit::CCodeGysEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CCodeGysEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCodeGysEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	flag=0; //作为修改或添加使用 1 为修改,2 为添加 
}


void CCodeGysEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCodeGysEdit)
	DDX_Control(pDX, IDC_COMBO1, combo1);
	DDX_Control(pDX, IDC_EDIT_PY, c_py);
	DDX_Control(pDX, IDC_EDIT_MC, c_mc);
	DDX_Control(pDX, IDC_EDIT_BM, c_bm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCodeGysEdit, CDialog)
	//{{AFX_MSG_MAP(CCodeGysEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeGysEdit message handlers

void CCodeGysEdit::OnOK() 
{
	CString str1,str2,str3,strSql;
	c_bm.GetWindowText(str1);
	c_mc.GetWindowText(str2);
	c_py.GetWindowText(str3);



	try{
	
		if( flag == 1 ){
			if( combo1.GetCurSel() == 0 ) //产地
				strSql.Format("UPDATE codegys SET gongmc='%s',py='%s',flag='B' WHERE gongbm='%s' ",str2,str3,str1);
			else //供应商
				strSql.Format("UPDATE codegys SET gongmc='%s',py='%s',flag='A' WHERE gongbm='%s' ",str2,str3,str1);

		}
		else if( flag ==2 ){
			if( combo1.GetCurSel() == 0 ) //产地
				strSql.Format("INSERT INTO codegys(gongbm,gongmc,py,flag) values('%s','%s','%s','B') ",str1,str2,str3);
			else
				strSql.Format("INSERT INTO codegys(gongbm,gongmc,py,flag) values('%s','%s','%s','A') ",str1,str2,str3);
		}
		
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
	AfxMessageBox("成功完成当前的操作...");
	CDialog::OnOK();
}

BOOL CCodeGysEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString strSql;
	if( flag == 1 ){ //修改
		
		c_bm.SetWindowText(m_str[0]);
		c_mc.SetWindowText(m_str[1]);
		c_py.SetWindowText(m_str[2]);
		if ( m_str[3] == 'A' ) combo1.SetCurSel(1);
		else combo1.SetCurSel(0);
		c_bm.SetReadOnly();
		


	}
	else if ( flag == 2){ //新增

		try{
			strSql.Format("select max( NVL(gongbm,0) )+1 as bm from codegys ");
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){
				strSql=(char*)_bstr_t(recSet->GetCollect("bm").vt==VT_NULL?" ":recSet->GetCollect("bm"));
				
			}
			recSet->Close();
			combo1.SetCurSel(0);
			
		}
		catch(_com_error e)
		{
			AfxMessageBox("出现错误,请检查SQL语句...");
			recSet->Close();
			return false;
		}	
		c_bm.SetWindowText(strSql);
		c_bm.SetReadOnly();


	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
