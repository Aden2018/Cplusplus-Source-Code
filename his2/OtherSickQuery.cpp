// OtherSickQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "OtherSickQuery.h"
#include "gh.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COtherSickQuery dialog


COtherSickQuery::COtherSickQuery(CWnd* pParent /*=NULL*/)
	: CDialog(COtherSickQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(COtherSickQuery)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	flagWhatDo=0;
	fontTitle.CreatePointFont(200,"宋体");
}


void COtherSickQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COtherSickQuery)
	DDX_Control(pDX, IDC_LIST_QUERY, c_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COtherSickQuery, CDialog)
	//{{AFX_MSG_MAP(COtherSickQuery)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_QUERY, OnDblclkListQuery)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_RCLICK, IDC_LIST_QUERY, OnRclickListQuery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COtherSickQuery message handlers

void COtherSickQuery::OnOK() 
{
	// TODO: Add extra validation here
	CString str[5];
	long x=0,y=0;
	c_list.DeleteAllItems();

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF)
		{
			y=0;
			str[y++]=(char*)_bstr_t(recSet->GetCollect("BM"));	
			str[y++]=(char*)_bstr_t(recSet->GetCollect("XM"));
			str[y++]=(char*)_bstr_t(recSet->GetCollect("XB"));
			str[y++]=(char*)_bstr_t(recSet->GetCollect("LB"));
			str[y++]=(char*)_bstr_t(recSet->GetCollect("PRO"));
			c_list.InsertItem(x," ");
			for(y=0;y<5;y++){
				c_list.SetItemText(x,y,str[y]);
			}
			x++;

			recSet->MoveNext();
			
		}
		recSet->Close();
		


	}
	catch(_com_error e)
	{
		AfxMessageBox("SQL 错误....");
		recSet->Close();
		return;
	}

	c_list.SetFocus();
	c_list.SetItemState (0, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
}

BOOL COtherSickQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i=0;
	CString str1[]={"BM","姓名","性别","性质","报销比例"};
	int width[]={0,100,60,150,80};
	while(i<sizeof(str1)/sizeof(CString))
	{
		c_list.InsertColumn(i,str1[i],LVCFMT_LEFT,width[i]);
		i++;
	}
	c_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	OnOK();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL COtherSickQuery::PreTranslateMessage(MSG* pMsg) 
{
	UINT nIndex=0;
	if(pMsg->message==WM_KEYDOWN&& pMsg->wParam==VK_RETURN){
		if(GetDlgItem(IDC_LIST_QUERY)==GetFocus()){

			OnDblclkListQuery(NULL,NULL);
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void COtherSickQuery::OnDblclkListQuery(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UINT nIndex;
	nIndex=c_list.GetNextItem(-1,LVNI_SELECTED);
	if(nIndex== -1 ) {
		AfxMessageBox("请先选择。。。");
		return ;
	}
	strKH=c_list.GetItemText(nIndex,0);
	strName=c_list.GetItemText(nIndex,1);
	strSex=c_list.GetItemText(nIndex,2);
	if( flagWhatDo == 0 )
		for(int i=0;i<5; i++ ) ((CGh*)p)->infor[i]=c_list.GetItemText(nIndex,i);
	CDialog::OnOK();
			
				
//	*pResult = 0;
}

HBRUSH COtherSickQuery::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd )
	{
		pDC->SetTextColor(RGB(255,0,0));
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void COtherSickQuery::OnRclickListQuery(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
//	*pResult = 0;
}
