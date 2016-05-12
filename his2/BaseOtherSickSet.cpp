// BaseOtherSickSet.cpp: implementation of the CBaseOtherSickSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "BaseOtherSickSet.h"
#include "BaseOtherSickAdd.h"
#include "otherDecharge.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseOtherSickSet::CBaseOtherSickSet()
{
	strTitle="������Ա��ѯ";

}

CBaseOtherSickSet::~CBaseOtherSickSet()
{

}

void CBaseOtherSickSet::OnOK()
{
	CString str[5];
	long x=0,y=0;
	c_list.DeleteAllItems();

	try{
		strSql.Format(" SELECT * FROM otherSick order by lb,xm");
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
		AfxMessageBox("SQL ����....");
		recSet->Close();
		return;
	}

	c_list.SetFocus();
	c_list.SetItemState (0, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
}

BOOL CBaseOtherSickSet::OnInitDialog()
{
	COtherSickQuery::OnInitDialog();
	return true;
}

void CBaseOtherSickSet::OnDblclkListQuery(NMHDR *pNMHDR, LRESULT *pResult)
{
	UINT nIndex;
	CBaseOtherSickAdd di;
	nIndex=c_list.GetNextItem(-1,LVNI_SELECTED);
	if(nIndex== -1 ) { //��������
		di.flag=1;
		di.strTitle="����������Ա";
		if(di.DoModal()==IDOK) OnOK();
	//	AfxMessageBox("����ѡ�񡣡���");
		return ;
	}
	//�޸Ĳ���
	for(int i=0;i<5; i++ ) di.str[i]=c_list.GetItemText(nIndex,i);
	di.flag=2;
	di.strTitle="������Ա�����޸�";
	if(di.DoModal()==IDOK) OnOK();

}

void CBaseOtherSickSet::OnRclickListQuery(NMHDR *pNMHDR, LRESULT *pResult)
{
	UINT nIndex;
	nIndex=c_list.GetNextItem(-1,LVNI_SELECTED);
	if(nIndex== -1 ) {
		AfxMessageBox("����ѡ�񡣡���");
		return ;
	}
	strKH.Format("ȷ��Ҫɾ��( %s/ %s)�𣿣�",c_list.GetItemText(nIndex,1),c_list.GetItemText(nIndex,3) );
	if( AfxMessageBox(strKH,MB_OKCANCEL)== IDCANCEL ) return;
	strSql.Format(" DELETE FROM otherSick WHERE bm='%s' ",c_list.GetItemText(nIndex,0) );

	if(!COtherDecharge::WriteSQL(strSql) ){
		AfxMessageBox("ɾ��ʧ�ܣ���");
		return;

	}
	OnOK();

}
