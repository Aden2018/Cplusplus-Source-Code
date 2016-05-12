// DMessageRead.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "DMessageRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMessageRead dialog


CDMessageRead::CDMessageRead(CWnd* pParent /*=NULL*/)
	: CDialog(CDMessageRead::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDMessageRead)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INI

	if(FAILED(rec2.CreateInstance( __uuidof( Recordset ))))
	{
		AfxMessageBox("初始化 全局线程Recordset失败...");
		return  ;
	}

}


void CDMessageRead::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDMessageRead)
	DDX_Control(pDX, IDC_LIST_MESSAGE, c_message);
	DDX_Control(pDX, IDC_EDIT_BODY, c_body);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDMessageRead, CDialog)
	//{{AFX_MSG_MAP(CDMessageRead)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MESSAGE, OnClickListMessage)
	ON_NOTIFY(HDN_ITEMCHANGED, IDC_LIST_MESSAGE, OnItemchangedListMessage)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MESSAGE, OnItemchangedListMessage)
	ON_BN_CLICKED(IDOK_DELETEALL, OnDeleteall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMessageRead message handlers

void CDMessageRead::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}

BOOL CDMessageRead::OnInitDialog() 
{
	CDialog::OnInitDialog();
	long index=0,i;
	c_message.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	c_message.InsertColumn(index++,"ID",LVCFMT_LEFT,0);
	c_message.InsertColumn(index++,"发送时间",LVCFMT_LEFT,180);
	c_message.InsertColumn(index++,"发送人",LVCFMT_LEFT,180);
	c_message.InsertColumn(index++,"标题",LVCFMT_LEFT,200);
	c_message.InsertColumn(index++,"内容",LVCFMT_LEFT,0);
	c_message.InsertColumn(index++,"FLAG",LVCFMT_LEFT,0);
	
	ListMessage();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDMessageRead::OnClickListMessage(NMHDR* pNMHDR, LRESULT* pResult) 
{
/*	c_message.InsertColumn(index++,"ID",LVCFMT_LEFT,0);
	c_message.InsertColumn(index++,"发送时间",LVCFMT_LEFT,100);
	c_message.InsertColumn(index++,"发送人",LVCFMT_LEFT,100);
	c_message.InsertColumn(index++,"标题",LVCFMT_LEFT,200);
	c_message.InsertColumn(index++,"内容",LVCFMT_LEFT,200);
*/	
	const int SENDNAME=2;
	const int SENDTIME=1;
	const int SENDTITLE=3;
	const int SENDBODY=4;
	const int READ=5;
	UINT nIndex;
	CString strTitle;
	nIndex=c_message.GetNextItem(-1,LVNI_SELECTED);
	if(nIndex== -1 ) {
		return ;
	}

	GetDlgItem(IDC_STATIC_1)->SetWindowText(c_message.GetItemText(nIndex,SENDNAME));	
	GetDlgItem(IDC_STATIC_2)->SetWindowText(c_message.GetItemText(nIndex,SENDTIME));
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(c_message.GetItemText(nIndex,SENDTITLE));
	c_body.SetWindowText(c_message.GetItemText(nIndex,SENDBODY));
	if ( c_message.GetItemText(nIndex,READ) != "1"  ){
	//更新已读标志
		try{
			strTitle.Format("UPDATE LSQ_NOTIFY_LIST SET ReadTime=sysdate WHERE ID='%s' AND \
				RYBM='%s' ",c_message.GetItemText(nIndex,0),LoginInformation.user_code );
			HospitalConnect->BeginTrans();

			HospitalConnect->Execute(_bstr_t(strTitle),NULL,adCmdText);
			HospitalConnect->CommitTrans();


		}
		catch(_com_error e )
		{
			HospitalConnect->RollbackTrans();
			AfxMessageBox(strTitle);
			return;

		}
		c_message.SetItemText(nIndex,READ,"1");

	}


//	*pResult = 0;
}





void CDMessageRead::OnItemchangedListMessage(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	OnClickListMessage(NULL, NULL) ;
	
//	*pResult = 0;
}

HBRUSH CDMessageRead::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_1)->m_hWnd || pWnd->m_hWnd == GetDlgItem(IDC_STATIC_2)->m_hWnd \
		|| pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd )
		pDC->SetTextColor(RGB(255,0,0));
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CDMessageRead::OnOK() 
{

	CDialog::OnOK();
}

void CDMessageRead::ListMessage()
{
	CString strSql;

	GetDlgItem(IDOK_DELETEALL)->ShowWindow(SW_HIDE);

	long index=0,i;
	try{
		strSql.Format("select a.ID,a.SENdTIME,a.SENDNAME,a.TITLE,a.BODY \
			from LSQ_NOTIFY_BODY a ,LSQ_NOTIFY_LIST b WHERE a.ID=b.ID and B.RYBM='%s' and b.ReadTime is NULL ",LoginInformation.user_code);

		rec2->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!rec2->adoEOF){
			c_message.InsertItem(index," ");
			for( i=0 ; i<rec2->GetFields()->Count ; i++ )
			{
				c_message.SetItemText(index,i,(char*)_bstr_t(rec2->GetFields()->GetItem(i)->Value.vt == VT_NULL ? " " : rec2->GetFields()->GetItem(i)->Value ) );
			}
			rec2->MoveNext();
			index++;
		}
		rec2->Close();


	}
	catch(_com_error e)
	{
		rec2->Close();
		AfxMessageBox(strSql);
		return ;
	}	

}

BOOL CDMessageRead::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDMessageRead::OnDeleteall() 
{
	CString strSql;
	try{
		strSql.Format("DELETE FROM lsq_notify_list WHERE id like '%%%s' ",LoginInformation.user_code );
		
		HospitalConnect->BeginTrans();
		//	AfxMessageBox(strSql);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		
		strSql.Format("DELETE FROM lsq_notify_body WHERE rybm='%s' ",LoginInformation.user_code );
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		
		HospitalConnect->CommitTrans();
		c_message.DeleteAllItems();
	}
	catch(_com_error e)
	{
		AfxMessageBox("删除出错...");
		HospitalConnect->RollbackTrans();
		return ;
	}
	
}
