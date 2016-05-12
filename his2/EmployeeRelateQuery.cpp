// EmployeeRelateQuery.cpp: implementation of the CEmployeeRelateQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "EmployeeRelateQuery.h"
#include "relateadd.h"
#include "relateModify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEmployeeRelateQuery::CEmployeeRelateQuery()
{
	flag_EXIT=0;
	iMenuSel=4; //������Ա��ݲ˵�
}

CEmployeeRelateQuery::~CEmployeeRelateQuery()
{

}
BEGIN_MESSAGE_MAP(CEmployeeRelateQuery, CEmployeeQuery)
	//{{AFX_MSG_MAP(CEmployeeQuery)
	ON_COMMAND(ID_MENU_RELATE_MODIFY, OnMenuRelateModify)
	ON_COMMAND(ID_MENU_RELATE_ADD, OnMenuRelateAdd)
	ON_COMMAND(ID_MENU_RELATE_KILL, OnMenuRelateKill)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEmployeeRelateQuery::OnOK()
{
	BeginWaitCursor();
	//����,����,�Ա�,��������,��������,����,�����,��������
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetRedraw(false);

	long j=0, i=0,x=0;
	CString HeadTitle[]={"bm","BM","XM","XB","XINGZHI","YUER","����","������",\
		"��������","CSRIQI","age"},str1;
	CString HeadTitle2[]={"TEMP","����","����","�Ա�","��������","���","������","������",\
		"��������","��������","����"};
	long  headWidth[]={0,1400,1200,600,1400,1300,1300,2000,00,0,600};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����кϲ�
		m_grid.SetColWidth(i,headWidth[count]);

//		p2->m_grid.SetRow(0);
//		p2->m_grid.SetCol(i);
//		p2->m_grid.SetColAlignment(i,4);//flexAlignCenterCenter 4 ��Ԫ������ݾ��С����ж���	

		m_grid.SetTextArray(i++,HeadTitle2[count]);
	}
	CString strSql,strName,strID,strDepart;
	if(m_depart.GetCurSel()==CB_ERR)strDepart="���в���";
	else m_depart.GetLBText(m_depart.GetCurSel(),strDepart); 
	double dbWage=0;
	m_name.GetWindowText(strName);
	m_kahao.GetWindowText(strID);
	j=1;
	try{
		if(strDepart=="���в���")
			strSql.Format("select bm,xm,xb,xingzhi,yuer,����,������,��������,csriqi,to_char(sysdate,'yyyy')-to_char(csriqi,'yyyy') age from ְ����������� e1,�����ű� e2,codeQingShu e3 where  \
			e1.���ű���=e2.���ű��� and e3.kahao=e1.���� and ��� != '����' AND \
			bm like '%s%%' and xm like '%s%%' AND zxriqi is NULL order by xm",strID,strName);
		else
			strSql.Format("select bm,xm,xb,xingzhi,yuer,����,������,��������,csriqi,to_char(sysdate,'yyyy')-to_char(csriqi,'yyyy') age from ְ����������� e1,�����ű� e2,codeQingShu e3 where \
				e1.���ű���=e2.���ű��� and e3.kahao=e1.���� and \
				bm like '%s%%' and xm like '%s%%' and ������='%s' and ��� != '����' AND zxriqi is NULL order by xm ",strID,strName,strDepart);
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			x=0;
			for(count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
				
				str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(HeadTitle[count])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(HeadTitle[count])));
				if( count == 5) dbWage+=atof(str1);
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
	m_grid.SetTextMatrix(j,1,"�ϼ�");
	strSql.Format("%.2f",dbWage);
	m_grid.SetTextMatrix(j,5,strSql);
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

BOOL CEmployeeRelateQuery::OnInitDialog()
{
	CEmployeeQuery::OnInitDialog();

	SetWindowText("����������Ա��");
	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"TEMP","����","����","�Ա�","��������","���","������","������",\
		"��������"};

	long j=0, i=0,x=0;

	long  headWidth[]={0,1400,1200,600,1400,1300,1300,2000,2000};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����кϲ�
		m_grid.SetColWidth(i,headWidth[count]);

//		p2->m_grid.SetRow(0);
//		p2->m_grid.SetCol(i);
//		p2->m_grid.SetColAlignment(i,4);//flexAlignCenterCenter 4 ��Ԫ������ݾ��С����ж���	

		m_grid.SetTextArray(i++,HeadTitle[count]);
	}


	GetDlgItem(IDC_STATIC_3)->SetWindowText("�����˲���");
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("�������������");

	return true;
}



//DEL void CEmployeeRelateQuery::OnClickMshflexgrid2()
//DEL {
//DEL 	const long ENDLINES=2;
//DEL 	if(m_grid.GetRows() == ENDLINES )return;//�ж��Ƿ���Ҫ��ʾ��ݲ˵�
//DEL 
//DEL 	MSG *pms;
//DEL 	pms=(MSG*)GetCurrentMessage();
//DEL 	if(pms->message != 0x205) {//0x202Ϊ������,0x205Ϊ����Ҽ���Ϣ
//DEL 		
//DEL 		CEmployeeQuery::OnClickMshflexgrid2();
//DEL 		return;
//DEL 	}
//DEL 	CMenu pm;
//DEL 	CPoint p;
//DEL 	pm.LoadMenu(IDR_MENU_MEDLIST);
//DEL 	CMenu* pmenu=pm.GetSubMenu(4);
//DEL 	GetCursorPos(&p);
//DEL 	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  
//DEL }

void CEmployeeRelateQuery::OnMenuRelateModify() //�޸�
{
	//{"TEMP","����","����","�Ա�","��������","���","������","������",\
		"��������","��������","����"};
	if(!theApp.AssertRole(ROLE_RELATE_MODIFY))return; 
	CRelateModify modify;
	for(int i=0 ; i< m_grid.GetCols(0) ; i++ ) modify.strPass[i]=m_grid.GetTextMatrix(curRow,i);
	if(modify.DoModal()==IDOK) OnOK();

}

void CEmployeeRelateQuery::OnMenuRelateKill()
{
//{"TEMP","����","����","�Ա�","��������","���","������","������",\
		"��������","��������"};	AfxMessageBox("add");
	if(!theApp.AssertRole(ROLE_RELATE_KILL))return; 

	CString strView;
	strView.Format("����: %s \n\n����: %s �Ա�: %s \n\n��������: %s ���: %s \n\n������: %s (%s) \n\nȷ��Ҫע����???",\
		m_grid.GetTextMatrix(curRow,1),m_grid.GetTextMatrix(curRow,2),m_grid.GetTextMatrix(curRow,3),\
		m_grid.GetTextMatrix(curRow,4),m_grid.GetTextMatrix(curRow,5),m_grid.GetTextMatrix(curRow,7),m_grid.GetTextMatrix(curRow,6));

	if( MessageBox(strView,"��ʾ",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	try{
		HospitalConnect->BeginTrans();
		strView.Format("UPDATE codeQingShu Set ZXRIQI=sysdate,yuer=0 WHERE BM='%s' AND zxriqi is NULL ",m_grid.GetTextMatrix(curRow,1));
		HospitalConnect->Execute(_bstr_t(strView),NULL,adCmdText);
		HospitalConnect->CommitTrans();
	}catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox(e.ErrorMessage());
		return;
	}
	AfxMessageBox("�ɹ�����ǰ�û�ע��!!!");
	OnOK();

}

void CEmployeeRelateQuery::OnMenuRelateAdd()
{
	if(!theApp.AssertRole(ROLE_RELATE_ADD))return; 
	CRelateAdd add;
	add.DoModal();

}
