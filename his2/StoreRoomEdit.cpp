// StoreRoomEdit.cpp: implementation of the CStoreRoomEdit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "StoreRoomEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStoreRoomEdit::CStoreRoomEdit()
{

}

CStoreRoomEdit::~CStoreRoomEdit()
{

}

BOOL CStoreRoomEdit::ReadName()
{
	try{
		m_xcCombo.ResetContent();
		CString strSql;
		strSql.Format("select KFMC from StoreRoom ORDER BY KFMC");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF)
		{
			strSql=(char*)_bstr_t(recSet->GetCollect("KFMC").vt==VT_NULL?" ":recSet->GetCollect("KFMC"));
			m_xcCombo.AddString(strSql);
			recSet->MoveNext();
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox("�������ݿ��Ƿ����쳣...");
		recSet->Close();
		return false;
	}
	return true;
}

void CStoreRoomEdit::OnAdd()
{
	UpdateData();
	if(m_strName.IsEmpty()){
		AfxMessageBox("������ҽԺ��������...Ȼ���ٵ�����!!!");
		return;
	}
	try{
		CString strSql;
		HospitalConnect->BeginTrans();
		
		strSql.Format("INSERT INTO storeROOM(KFBM,KFMC) values( (SELECT NVL(\
			MAX(kfbm),10)+1 FROM storeroom),'%s' ) ",m_strName );
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
	
		HospitalConnect->CommitTrans();

		
	}
	catch(_com_error e)
	{
		AfxMessageBox("��д������� ");
		HospitalConnect->RollbackTrans();
		
		return;
	}
	m_strName="";
	UpdateData(false);
	ReadName(); //�����û����������ı�
	AfxMessageBox("��ǰ���Ƴɹ��������ݿ�...");
	GetDlgItem(IDC_EDIT_NAME)->SetFocus();	
}

void CStoreRoomEdit::OnModify()
{
	UpdateData();
	CString strSql,str;
	if(m_xcCombo.GetCurSel()==CB_ERR){
		AfxMessageBox("����ѡ��Ҫ�޸ĵ����....");
		return;
	}
	m_xcCombo.GetLBText(m_xcCombo.GetCurSel(),str);
	strSql.Format("update storeROOm set kfmc='%s' where kfmc='%s' ",m_strName,str);
	try{
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

	MessageBox("ҽԺ�������Ƴɹ��޸�...","��ʾ",MB_OK|MB_ICONINFORMATION);
	ReadName();	
	m_strName="";
	ReadName();
	UpdateData(false);//
}

void CStoreRoomEdit::OnDelete()
{
	UpdateData();
	CString strSql,bm,str;
	if(m_xcCombo.GetCurSel()==CB_ERR){
		AfxMessageBox("����ѡ��Ҫɾ��������....");
		return;
	}
	m_xcCombo.GetLBText(m_xcCombo.GetCurSel(),str);

	try{
		strSql.Format("select * from storeroom where kfmc='%s' ",str);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF)
		{
			bm=(char*)_bstr_t(recSet->GetCollect("kfbm"));
		}
		else bm="";
		recSet->Close();
		if(bm.IsEmpty())return ;
		HospitalConnect->BeginTrans();
		strSql.Format("delete from storeroom where kfbm='%s' ",bm);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		strSql.Format("delete from operator where kfbm='%s' ",bm);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();

		
	}
	catch(_com_error e)
	{
		AfxMessageBox("�������ݿ��Ƿ����쳣...");
		recSet->Close();
		HospitalConnect->RollbackTrans();
		return ;
	}

	m_strName="";
	ReadName(); 
	MessageBox("��ǰ��ѡ�����Ƴɹ�ɾ��...","��ʾ",MB_OK|MB_ICONINFORMATION);
	UpdateData(false);	
}

BOOL CStoreRoomEdit::OnInitDialog()
{
	if( !CDialogMedDL::OnInitDialog()  ) return false;
	const CString strName="ҽԺ������������";
	SetWindowText(strName);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strName);
	GetDlgItem(IDC_STATIC1)->SetWindowText("ԭ����");
	GetDlgItem(IDC_STATIC2)->SetWindowText("�޸�����");
	return true;
}
