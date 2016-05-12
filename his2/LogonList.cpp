// LogonList.cpp: implementation of the CLogonList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "LogonList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogonList::CLogonList()
{

}

CLogonList::~CLogonList()
{

}

BOOL CLogonList::OnInitDialog()
{
	CDialog::OnInitDialog();
	int i=0;
	CString str1[]={"LOGID","BM","姓名","工作职责","库房","登录时间"};
	int width[]={0,0,100,100,100,240};
	while(i<sizeof(str1)/sizeof(CString))
	{
		c_list.InsertColumn(i,str1[i],LVCFMT_LEFT,width[i]);
		i++;
	}
	c_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	fontTitle.CreatePointFont(200,"宋体");
	strTitle="系统登录人员列表";
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	OnOK();
	return true;
}

void CLogonList::OnDblclkListQuery(NMHDR *pNMHDR, LRESULT *pResult)
{
//	OnOK();
}

void CLogonList::OnOK()
{
	CString strTemp;
	long x=0,y=0;
	c_list.DeleteAllItems();
	
	strSql.Format("select logid,a.rybm,b.name,attribute,kfmc,logtime \
         from lsq_log_operator a, operator b,  storeroom c \
         where a.rybm=b.rybm and b.kfbm=c.kfbm and killflag is NULL " );
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF)
		{
			c_list.InsertItem(x," ");
			for(y=0;y< recSet->GetFields()->Count;y++){ //一共应是六列
				strTemp=(char*)_bstr_t(recSet->GetFields()->GetItem( y)->Value.vt==VT_NULL ? " ":recSet->GetFields()->GetItem( y)->Value);
				c_list.SetItemText(x,y,strTemp);
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

BOOL CLogonList::PreTranslateMessage(MSG *pMsg)
{
	return CDialog::PreTranslateMessage(pMsg);

}

void CLogonList::OnRclickListQuery(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(!theApp.AssertRole(ROLE_LOGIN_DENY ))return; 

	UINT nIndex;
	nIndex=c_list.GetNextItem(-1,LVNI_SELECTED);
	if(nIndex== -1 ) {
		MessageBox("请先选择...","提示",MB_OK|MB_ICONINFORMATION);
		return ;
	}

	strKH=c_list.GetItemText(nIndex,0);
	if(MessageBox("确认要禁止此用户使用系统吗???","提示",MB_OKCANCEL|MB_ICONINFORMATION)==IDOK){
		c_list.DeleteItem(nIndex);
		try{
			HospitalConnect->BeginTrans();
			strSql.Format("UPDATE LSQ_LOG_OPERATOR SET killflag='1' WHERE logid='%s' ",strKH );
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			HospitalConnect->CommitTrans();


		}
		catch(_com_error e)
		{
			AfxMessageBox(strSql);
			return;
		}


	}

}
