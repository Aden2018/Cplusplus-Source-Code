// BasisInsureList.cpp: implementation of the CBasisInsureList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "BasisInsureList.h"
#include "baseRymodify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBasisInsureList::CBasisInsureList()
{

}

CBasisInsureList::~CBasisInsureList()
{

}

BOOL CBasisInsureList::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	CRect r1,r2;
	GetDlgItem(IDC_STATIC_3)->GetWindowRect(r1);
	ScreenToClient(r1);
	GetDlgItem(IDC_COMBO1)->GetWindowRect(r2);
	ScreenToClient(r2);
	GetDlgItem(IDC_STATIC_2)->MoveWindow(r1);
	GetDlgItem(IDC_EDIT2)->MoveWindow(r2);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("����������Ա��ѯ");
	GetDlgItem(ID_SEARCH)->ShowWindow(SW_HIDE);
	return true;
}

void CBasisInsureList::OnOK()
{
	BeginWaitCursor();
	//����,����,�Ա�,��������,��������,����,�����,��������
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetRedraw(false);

	long j=0, i=0,x=0;
	CString HeadTitle[]={"yc","����","����","�Ա�","pass","2","x","x","x","x"},str1;

	long  headWidth[]={0,2000,1400,800,00,00,00,00,00,0,0};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(long count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����кϲ�
		m_grid.SetColWidth(i,headWidth[count]);


		m_grid.SetTextArray(i++,HeadTitle[count]);
	}
	CString strSql,strName,strID,strDepart;

	m_name.GetWindowText(strName);
	m_kahao.GetWindowText(strID);
	j=1;
	try{
		strSql.Format("select 1,����,����,�Ա�,pass from ҽ����Ա�б� WHERE ���� like '%s%%' and ���� like '%s%%' ORDER BY ���� ",strID,strName);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			x=0;
			for(count=0 ; count < 5 ; count++){
				
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(count))->Value.vt==VT_NULL ? " " : recSet->GetFields()->GetItem(_variant_t(count))->Value );
				
				m_grid.SetTextMatrix(j,x++,str1);
			}
				
			
			m_grid.AddItem(" ",_variant_t(++j));
			recSet->MoveNext();


		}
		m_grid.SetRedraw(true);
		recSet->Close();		
		
	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox("���ݿ�����ƻ�,��������...");
		return;
	}
	m_grid.SetTextMatrix(j,0,"�ϼ�");
	strSql.Format("����ѯ��: %ld ����Ϣ",j-1);
	GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(strSql);
	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow=1;
		for( i=1;i<8;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
	EndWaitCursor();
}

BOOL CBasisInsureList::PreTranslateMessage(MSG *pMsg)
{
	if(pMsg->message == WM_KEYDOWN )
	{
		if(pMsg->wParam == VK_RETURN ){
			OnOK();
			return true;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);

}

void CBasisInsureList::OnClickMshflexgrid2()
{
	const long ENDLINES=2;
	if(m_grid.GetRows() == ENDLINES )return;//�ж��Ƿ���Ҫ��ʾ��ݲ˵�

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202Ϊ������,0x205Ϊ����Ҽ���Ϣ
		CEmployeeQuery::SetSel();
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_MEDLIST);
	CMenu* pmenu=pm.GetSubMenu(iMenuSel+1); //����ҽ����Ա��ݲ˵�
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  

}

void CBasisInsureList::OnMenuQuickBaseryDel()  //* ɾ�����������û�
{
//	if(!theApp.AssertRole(ROLE_EMP_EDIT))return;  //* Ȩ������


	CString strSql;
	long rows=m_grid.GetRows();
	long curRow=m_grid.GetRow();
	if( curRow == 0 || curRow == rows-1 ) return ; //*���ѡ���˱����л����һ�����˳�

	strSql.Format("ȷ��Ҫɾ�� (%s)/(%s) ��???",m_grid.GetTextMatrix(curRow,1),m_grid.GetTextMatrix(curRow,2) );
	if( AfxMessageBox(strSql,MB_OKCANCEL)== IDCANCEL) return;
	try{
		HospitalConnect->BeginTrans();
		strSql.Format("Delete from ҽ����Ա�б� where ����='%s' ",m_grid.GetTextMatrix(curRow,1));
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();
	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox("ɾ��ʧ��...");
		return;
	}
		
	m_grid.RemoveItem(curRow);
	AfxMessageBox("ɾ���ɹ�!!!");

}

void CBasisInsureList::OnMenuQuickBaseryViewpassword() //* �鿴���������û�����
{
	CString strSql;
	long rows=m_grid.GetRows();
	long curRow=m_grid.GetRow();
	if( curRow == 0 || curRow == rows-1 ) return ; //*���ѡ���˱����л����һ�����˳�
	strSql.Format("SELECT pass From ҽ����Ա�б� where ����='%s' ",m_grid.GetTextMatrix(curRow,1));
	strSql.Format("���û�������ϢΪ:\n\n����:%s �Ա�:%s\n����:%s\n����:%s",m_grid.GetTextMatrix(curRow,2),\
		m_grid.GetTextMatrix(curRow,3),m_grid.GetTextMatrix(curRow,1),COtherDecharge::GetStringTitle(strSql));
	AfxMessageBox(strSql);

}

void CBasisInsureList::OnMenuQuickBaseryModify() //* �޸Ļ��������û���Ϣ
{
	CString strSql;
	long rows=m_grid.GetRows();
	long curRow=m_grid.GetRow();
	if( curRow == 0 || curRow == rows-1 ) return ; //*���ѡ���˱����л����һ�����˳�
	CBaseRyModify rm;
	rm.pGrid=&m_grid;
	rm.selRow=curRow;
	rm.DoModal();

}
