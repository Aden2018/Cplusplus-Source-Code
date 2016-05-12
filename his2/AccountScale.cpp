// AccountScale.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "AccountScale.h"
#include "otherDecharge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccountScale dialog


CAccountScale::CAccountScale(CWnd* pParent /*=NULL*/)
	: CDialog(CAccountScale::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAccountScale)
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"宋体");
	strTitle="请设标题";

}


void CAccountScale::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccountScale)
	DDX_Control(pDX, IDC_EDIT35, c5);
	DDX_Control(pDX, IDC_EDIT34, c4);
	DDX_Control(pDX, IDC_EDIT33, c3);
	DDX_Control(pDX, IDC_EDIT32, c2);
	DDX_Control(pDX, IDC_EDIT31, c1);
	DDX_Control(pDX, IDC_EDIT25, oc5);
	DDX_Control(pDX, IDC_EDIT24, oc4);
	DDX_Control(pDX, IDC_EDIT23, oc3);
	DDX_Control(pDX, IDC_EDIT22, oc2);
	DDX_Control(pDX, IDC_EDIT21, oc1);
	DDX_Control(pDX, IDCANCEL, m_2);
	DDX_Control(pDX, IDOK, m_1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAccountScale, CDialog)
	//{{AFX_MSG_MAP(CAccountScale)
	ON_EN_SETFOCUS(IDC_EDIT21, OnSetfocusEdit21)
	ON_EN_SETFOCUS(IDC_EDIT22, OnSetfocusEdit22)
	ON_EN_SETFOCUS(IDC_EDIT23, OnSetfocusEdit23)
	ON_EN_SETFOCUS(IDC_EDIT24, OnSetfocusEdit24)
	ON_EN_SETFOCUS(IDC_EDIT25, OnSetfocusEdit25)
	ON_EN_CHANGE(IDC_EDIT21, OnChangeEdit21)
	ON_EN_CHANGE(IDC_EDIT22, OnChangeEdit22)
	ON_EN_CHANGE(IDC_EDIT23, OnChangeEdit23)
	ON_EN_CHANGE(IDC_EDIT24, OnChangeEdit24)
	ON_EN_CHANGE(IDC_EDIT25, OnChangeEdit25)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccountScale message handlers

BOOL CAccountScale::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	strTitle.Format("职工年度充值比例维护");
	SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	
	CString strSql;
	for( long i=0; i< 5 ; i++ ){ //获取各利比例情况
		strSql.Format("SELECT n1 FROM LSQ_GH_TYPE WHERE ds3='C' and ds1='%d' ",i+1);
		dbScale[i]=atof(COtherDecharge::GetStringTitle(strSql));
	}
	i=0;
	strSql.Format("%.2f%%",dbScale[i++]*100);
	oc1.SetWindowText(strSql);
	c1.SetWindowText(strSql);
	strSql.Format("%.2f%%",dbScale[i++]*100);
	oc2.SetWindowText(strSql);
	c2.SetWindowText(strSql);
	strSql.Format("%.2f%%",dbScale[i++]*100);
	oc3.SetWindowText(strSql);
	c3.SetWindowText(strSql);
	strSql.Format("%.2f%%",dbScale[i++]*100);
	oc5.SetWindowText(strSql);
	c5.SetWindowText(strSql);
	strSql.Format("%.2f%%",dbScale[i++]*100);
	oc4.SetWindowText(strSql);
	c4.SetWindowText(strSql);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CAccountScale::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN ) pMsg->wParam=VK_TAB;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CAccountScale::OnSetfocusEdit21() 
{
	selEdit(&oc1);	
}

void CAccountScale::OnSetfocusEdit22() 
{
	// TODO: Add your control notification handler code here
	selEdit(&oc2);	
	
}

void CAccountScale::OnSetfocusEdit23() 
{
	// TODO: Add your control notification handler code here
	selEdit(&oc3);	
	
}

void CAccountScale::OnSetfocusEdit24() 
{
	// TODO: Add your control notification handler code here
	selEdit(&oc4);	
	
}

void CAccountScale::OnSetfocusEdit25() 
{
	// TODO: Add your control notification handler code here
	selEdit(&oc5);	
	
}

void CAccountScale::selEdit(CEdit *pe)
{
	CString strTmp;
	pe->GetWindowText(strTmp);
	pe->SetSel(0,strTmp.GetLength()-1);	
	
}

void CAccountScale::OnChangeEdit21() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	changeEdit(&oc1,&c1);
	
}

void CAccountScale::OnChangeEdit22() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	changeEdit(&oc2,&c2);
	// TODO: Add your control notification handler code here
	
}

void CAccountScale::OnChangeEdit23() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	changeEdit(&oc3,&c3);
	
}

void CAccountScale::OnChangeEdit24() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	changeEdit(&oc4,&c4);
	
}

void CAccountScale::OnChangeEdit25() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	changeEdit(&oc5,&c5);
	
}

void CAccountScale::changeEdit(CEdit *pe1, CEdit *pe2)
{
	CString strTmp,strOut;
	pe1->GetWindowText(strTmp);
	strOut.Format("%.2f%%",atof(strTmp));
	pe2->SetWindowText(strOut);
}

void CAccountScale::OnOK() 
{
	long i(0);
	CString strTmp;
	c1.GetWindowText(strTmp);
	dbScale[i++]=atof(strTmp);
	c2.GetWindowText(strTmp);
	dbScale[i++]=atof(strTmp);
	c3.GetWindowText(strTmp);
	dbScale[i++]=atof(strTmp);
	
	c5.GetWindowText(strTmp);
	dbScale[i++]=atof(strTmp);
	
	c4.GetWindowText(strTmp);
	dbScale[i++]=atof(strTmp);
//分五种情况 1.在职(<=35) 2.在职(36-45) 3.在职(>=46) 4.建国后退休 5.建国前退休

	for(i=0; i< 5; i++)
	{
		strTmp.Format(" UPDATE LSQ_GH_TYPE SET n1=%.4f WHERE DS3='C' AND ds1='%d' ",dbScale[i]/100,i+1);
		COtherDecharge::WriteSQL(strTmp);
	}
	AfxMessageBox("成功更改当前职工充值比例");

}
