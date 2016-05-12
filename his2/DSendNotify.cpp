// DSendNotify.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "DSendNotify.h"
#include "DSRecive.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSendNotify dialog


CDSendNotify::CDSendNotify(CWnd* pParent /*=NULL*/)
	: CDialog(CDSendNotify::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDSendNotify)
	//}}AFX_DATA_INIT
}


void CDSendNotify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDSendNotify)
	DDX_Control(pDX, IDC_LIST_RECIVE, c_recive);
	DDX_Control(pDX, IDC_EDIT2, c_richbody);
	DDX_Control(pDX, IDC_EDIT_TITLE, c_title);
	DDX_Control(pDX, IDC_EDIT1, c_send_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDSendNotify, CDialog)
	//{{AFX_MSG_MAP(CDSendNotify)
	ON_BN_CLICKED(IDC_BUTTON_RECEVIE, OnButtonRecevie)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSendNotify message handlers

void CDSendNotify::OnOK() 
{
	UpdateData();
	CString strSql,strTemp1,strTemp2,strID;
	c_richbody.GetWindowText(strTemp1);

	c_title.GetWindowText(strTemp2);
	if(strTemp2.IsEmpty())return;
	if(strTemp1.GetLength()>=4000 || c_recive.GetItemCount() == 0 ){
		AfxMessageBox("您输入的文字太多,请以其它方式通知,本通知只能容纳2000汉字,请注意收件人不能为空");
		return;
	}
	try{
		strSql.Format("select to_char(sysdate,'yyyymmddhh24miss') da from dual" );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			strSql=(char*)_bstr_t (recSet->GetCollect("da"));
			strID=strSql+LoginInformation.user_code;
		}
		recSet->Close();

		HospitalConnect->BeginTrans();
		strSql.Format("INSERT INTO LSQ_NOTIFY_BODY(id,sendTime,title,body,RorN,SendName,rybm) values\
			('%s',sysdate,'%s','%s',0,'%s','%s' ) ",strID,strTemp2,strTemp1,\
			LoginInformation.kfmc+" - "+LoginInformation.user,LoginInformation.user_code);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		for(int i=0 ;i<c_recive.GetItemCount() ;i++)
		{
			strSql.Format("INSERT INTO LSQ_NOTIFY_List (ID,RYBM ) values('%s','%s') \
				",strID,c_recive.GetItemText(i,0) );
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		}
		
		HospitalConnect->CommitTrans();

		

	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox(strSql);
		return;
	}
	strTemp1.Format("信息成功发送....");
	AfxMessageBox(strTemp1);
	CDialog::OnOK();
}

BOOL CDSendNotify::PreTranslateMessage(MSG* pMsg) 
{
	CString strTemp;
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){
		if(GetFocus()->m_hWnd==c_richbody.m_hWnd){
			
			c_richbody.GetWindowText(strTemp);
			strTemp+="\r\n";
			c_richbody.SetWindowText(strTemp);
			c_richbody.SetSel(strTemp.GetLength(),strTemp.GetLength());
			c_richbody.SetFocus();
			return true;
			
			//c_richbody.GetLineCount()
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDSendNotify::OnButtonRecevie() 
{
	CDSRecive recive;
	recive.pList=&c_recive;
	if(	recive.DoModal() == IDOK ) c_send_name.SetWindowText(recive.strName);
}

BOOL CDSendNotify::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	c_recive.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	c_recive.InsertColumn(0," ",LVCFMT_LEFT,50);
	c_recive.InsertColumn(1," ",LVCFMT_LEFT,50);
	c_recive.InsertColumn(2," ",LVCFMT_LEFT,50);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
