// QueryReadNotifyPeople.cpp: implementation of the CQueryReadNotifyPeople class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "QueryReadNotifyPeople.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQueryReadNotifyPeople::CQueryReadNotifyPeople()
{

}

CQueryReadNotifyPeople::~CQueryReadNotifyPeople()
{

}

void CQueryReadNotifyPeople::ListMessage()
{
	CString strSql;
/*	c_message.InsertColumn(index++,"ID",LVCFMT_LEFT,0);
	c_message.InsertColumn(index++,"发送时间",LVCFMT_LEFT,100);
	c_message.InsertColumn(index++,"发送人",LVCFMT_LEFT,100);
	c_message.InsertColumn(index++,"标题",LVCFMT_LEFT,200);
	c_message.InsertColumn(index++,"内容",LVCFMT_LEFT,200);
*/
	long index=0,i;
	try{
		strSql.Format("select id,sendtime,sendname,title,body from LSQ_NOTIFY_BODY \
			WHERE RYBM='%s' ORDER BY SENDTIME ",LoginInformation.user_code);
		rec2->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!rec2->adoEOF){
			c_message.InsertItem(index," ");
			for( i=0 ; i<rec2->GetFields()->Count ; i++ )
			{
				c_message.SetItemText(index,i,(char*)_bstr_t(rec2->GetFields()->GetItem(i)->Value ));
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

void CQueryReadNotifyPeople::OnClickListMessage(NMHDR *pNMHDR, LRESULT *pResult)
{
	const int SENDNAME=2;
	const int SENDTIME=1;
	const int SENDTITLE=3;
	const int SENDBODY=4;
	const int READ=5;
	long nIndex,index,i;
	CString strTitle,str[3],strSql,strT1;
	nIndex=c_message.GetNextItem(-1,LVNI_SELECTED);
	if(nIndex== -1 ) {
		return ;
	}

	GetDlgItem(IDC_STATIC_1)->SetWindowText(c_message.GetItemText(nIndex,SENDNAME));	
	GetDlgItem(IDC_STATIC_2)->SetWindowText(c_message.GetItemText(nIndex,SENDTIME));
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(c_message.GetItemText(nIndex,SENDTITLE));
	strTitle=c_message.GetItemText(nIndex,SENDBODY);
	strTitle+="\r\n------------------------------------------------\r\n";

	try{
		strSql.Format("select C.KFMC,B.NAME,A.READTIME FROM lsq_notify_list a,Operator b,storeroom c \
			WHERE a.RYBM=b.RYBM and B.KFBM=c.KFBM and A.ID='%s' ORDER BY c.KFBM ",c_message.GetItemText(nIndex,0));
		rec2->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		index=0;
		while(!rec2->adoEOF){
			for( i=0 ; i<rec2->GetFields()->Count ; i++ )
			{
				str[i]=(char*)_bstr_t(rec2->GetFields()->GetItem(i)->Value.vt==VT_NULL ?"未 知 ": rec2->GetFields()->GetItem(i)->Value);
			
			}
			strT1.Format("%-15s %-10s %-25s\r\n",str[0],str[1],str[2]);
			strTitle+=strT1;
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

	c_body.SetWindowText(strTitle);






}





BOOL CQueryReadNotifyPeople::PreTranslateMessage(MSG *pMsg) //获取鼠标右击
{

	if(pMsg->message==WM_RBUTTONDOWN && GetFocus()->m_hWnd == GetDlgItem(IDC_LIST_MESSAGE)->m_hWnd )
	{
		if( ::MessageBox(this->m_hWnd,"删除本条信息吗?","删除",MB_OKCANCEL) == IDOK ){
			long Index;
			CString strSql;
			Index=c_message.GetNextItem(-1,LVNI_SELECTED);
			if(Index== -1 ) {
				return true;
			}
			try{
				strSql.Format("DELETE FROM lsq_notify_list WHERE id='%s' ",c_message.GetItemText(Index,0) );
			
				HospitalConnect->BeginTrans();
			//	AfxMessageBox(strSql);
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			
				strSql.Format("DELETE FROM lsq_notify_body WHERE id='%s' " ,c_message.GetItemText(Index,0) );
			//	AfxMessageBox(strSql);
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

				HospitalConnect->CommitTrans();
				c_message.DeleteItem(Index);				

			}
			catch(_com_error e)
			{
				AfxMessageBox("删除出错...");
				HospitalConnect->RollbackTrans();
				return true;
			}
			return true;
			
			
			
			
			
		}

	}
	return CDialog::PreTranslateMessage(pMsg);

}
