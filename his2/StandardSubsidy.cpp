// StandardSubsidy.cpp: implementation of the CStandardSubsidy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "StandardSubsidy.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStandardSubsidy::CStandardSubsidy()
{
	strTitle.Format("特殊人员补助标准");
//	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_mixed WHERE ds2='DIALOG' AND ds3='TITLE' and ds4='AAG' ");
}

CStandardSubsidy::~CStandardSubsidy()
{

}

void CStandardSubsidy::OnDblclkListQuery(NMHDR *pNMHDR, LRESULT *pResult)
{

	UINT nIndex;
	nIndex=c_list.GetNextItem(-1,LVNI_SELECTED);
	if(nIndex== -1 ) {
		AfxMessageBox("请先选择。。。");
		return ;
	}
	strKH=c_list.GetItemText(nIndex,0); //编码
	strName=c_list.GetItemText(nIndex,1);//　补助内容
	strSex=c_list.GetItemText(nIndex,2); //金额
	CDialog::OnOK();

}

void CStandardSubsidy::OnOK()
{
	CString str[5];
	long x=0,y=0,z;
	c_list.DeleteAllItems();
	
	strSql.Format(" SELECT ds1,ds3,n3 FROM LSQ_UPGRADE WHERE ds2='ESUB' ORDER BY n2 ");
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF)
		{
			y=0;
			str[y++]=(char*)_bstr_t(recSet->GetCollect("DS3"));	
			str[y++]=(char*)_bstr_t(recSet->GetCollect("DS1")); //编码
			str[y++]=(char*)_bstr_t(recSet->GetCollect("n3")); //补助金额

			c_list.InsertItem(x," ");
			for(z=0; z<y ; z++){
				c_list.SetItemText(x,z,str[z]);
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

BOOL CStandardSubsidy::OnInitDialog()
{
	CDialog::OnInitDialog();
	int i=0;
	CString str1[]={"BM","补助性质","金额"};
	int width[]={0,200,80};
	while(i<sizeof(str1)/sizeof(CString))
	{
		c_list.InsertColumn(i,str1[i],LVCFMT_LEFT,width[i]);
		i++;
	}
	c_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	SetWindowText(strTitle);
	OnOK();
	return TRUE;  // return TRUE unless you set the focus to a control

}
