// BaseOtherSickAdd.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "BaseOtherSickAdd.h"
#include "DialogMedXL.h"
#include "otherDecharge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseOtherSickAdd dialog


CBaseOtherSickAdd::CBaseOtherSickAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseOtherSickAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBaseOtherSickAdd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"黑体");
	flag=0;
}


void CBaseOtherSickAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBaseOtherSickAdd)
	DDX_Control(pDX, IDC_EDIT2, edit2);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_COMBO2, attr);
	DDX_Control(pDX, IDC_COMBO1, sex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBaseOtherSickAdd, CDialog)
	//{{AFX_MSG_MAP(CBaseOtherSickAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseOtherSickAdd message handlers

BOOL CBaseOtherSickAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	SetWindowText(strTitle);
	
	strSql.Format("SELECT distinct LB FROM othersick order by LB ");
	if( !CDialogMedXL::ReadName(strSql,attr) ) {
		AfxMessageBox("读取数据出错!!!");
		return false;
	}
	
	if(flag == 1){ //新增
		
		sex.SetCurSel(0);
	}
	else if(flag ==2 ){ //修改
/*			str[y++]=(char*)_bstr_t(recSet->GetCollect("BM"));	
			str[y++]=(char*)_bstr_t(recSet->GetCollect("XM"));
			str[y++]=(char*)_bstr_t(recSet->GetCollect("XB"));
			str[y++]=(char*)_bstr_t(recSet->GetCollect("LB"));
			str[y++]=(char*)_bstr_t(recSet->GetCollect("PRO"));
*/
		edit1.SetWindowText(str[1]);
		sex.SelectString(-1,str[2]);
		attr.SelectString(-1,str[3]);
		edit2.SetWindowText(str[4]);

	}

	CenterWindow();
	AnimateWindow(m_hWnd,300,AW_SLIDE|AW_HOR_POSITIVE);
	Invalidate();
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBaseOtherSickAdd::OnOK() 
{
	UpdateData();
	edit1.GetWindowText(str[9]);
	sex.GetLBText(sex.GetCurSel(),str[8]);
	attr.GetWindowText(str[7]);
	edit2.GetWindowText(str[6]);

	if( str[7].IsEmpty() || str[6].IsEmpty() || str[9].IsEmpty() )
	{
		AfxMessageBox("请将所要求的资料填写完整再进行操作");
		return;
	}

	if( flag == 1){ //新增
	
		strSql.Format(" INSERT INTO othersick (bm,xm,xb,lb,pro) VALUES( (select \
			NVL(max(bm),0)+1 FROM othersick ),'%s','%s','%s',%.2f ) ",str[9],\
			str[8],str[7],atof(str[6]) );
	}
	else if( flag == 2 ){ //修改

		strSql.Format(" UPDATE otherSick SET xm='%s',xb='%s',lb='%s',pro=%.2f \
			WHERE bm='%s' ",str[9],str[8],str[7],atof(str[6]),str[0] );

	}
	else return;

	if(!COtherDecharge::WriteSQL(strSql)){
		AfxMessageBox("操作失败");
		return;
	}

	CDialog::OnOK();
	
}
