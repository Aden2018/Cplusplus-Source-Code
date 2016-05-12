// EmployeeQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "EmployeeQuery.h"
#include "gh.h"
#include "excel9.h"
#include "OperatChargeRelateFee.h"
#include "employee.h"
#include "otherDecharge.h"
#include "employeeModify.h"
#include "subsidySet.h"
#include "passwordView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmployeeQuery dialog
#define DOWN_ARROR 0x28
#define UP_ARROR 0x26
#define COLS 8

CEmployeeQuery::CEmployeeQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CEmployeeQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmployeeQuery)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"����");
	strKH="";
	curRow=0;
	p=NULL;
	flagRELATE=0; //��Ϊ������������ʱʹ��,����ʱ����Ϊ: 777;
	flag_EXIT=0;

	iMenuSel=5; //���䱣�տ�ݲ˵�
}


void CEmployeeQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmployeeQuery)
	DDX_Control(pDX, ID_SEARCH, m_aaa);
	DDX_Control(pDX, ID_TO_EXCEL, m_excel);
	DDX_Control(pDX, IDOK, m_x2);
	DDX_Control(pDX, IDCANCEL, m_x1);
	DDX_Control(pDX, IDC_EDIT2, m_kahao);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_COMBO1, m_depart);
	DDX_Control(pDX, IDC_MSHFLEXGRID2, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmployeeQuery, CDialog)
	//{{AFX_MSG_MAP(CEmployeeQuery)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(ID_TO_EXCEL, OnToExcel)
	ON_COMMAND(ID_MENU_Q_EMP_ADD, OnMenuQEmpAdd)
	ON_COMMAND(ID_MENU_Q_EMP_DEL, OnMenuQEmpDel)
	ON_COMMAND(ID_MENU_Q_EMP_MODIFY, OnMenuQEmpModify)
	ON_COMMAND(ID_MENU_Q_EMP_SUBSIDY, OnMenuQEmpSubsidy)
	ON_BN_CLICKED(ID_SEARCH, OnSearch)
	ON_COMMAND(ID_MENU_Q_PASS_VIEW, OnMenuQPassView)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_MENU_QUICK_BASERY_DEL, OnMenuQuickBaseryDel)
	ON_COMMAND(ID_MENU_QUICK_BASERY_MODIFY, OnMenuQuickBaseryModify)
	ON_COMMAND(ID_MENU_QUICK_BASERY_VIEWPASSWORD, OnMenuQuickBaseryViewpassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmployeeQuery message handlers

BOOL CEmployeeQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString strSql;
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	try{
		strSql.Format("select distinct(������) from �����ű� ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetCollect("������").vt==VT_NULL?" ":recSet->GetCollect("������"));
			m_depart.AddString(strSql);
			recSet->MoveNext();
		}
		recSet->Close();
		m_depart.AddString("���в���");

	}
	catch(_com_error e)
	{
		recSet->Close();
		return false;
	}

	m_grid.SetRows(2);
	m_grid.Clear();

	long j=0, i=0,x=0;
	CString HeadTitle[]={"������","����","����","�Ա�","��������","��������",\
		"�����","��������","���","pass"};

	long  headWidth[]={1400,1200,1200,400,1300,1300,1200,2000,1000};//,2000,1000};
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
	CenterWindow();
//	AnimateWindow(m_hWnd,300,AW_SLIDE|AW_HOR_POSITIVE);
//	Invalidate();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEmployeeQuery::OnOK() 
{
	BeginWaitCursor();
	//����,����,�Ա�,��������,��������,����,�����,��������
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetRedraw(false);

	long j=0, i=0,x=0;
	CString HeadTitle[]={"������","����","����","�Ա�","��������","��������",\
		"�����","��������","���","pass"},str1;

	long  headWidth[]={1400,1200,1200,400,1300,1300,1600,1000,1000,00,00};
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
	CString strSql,strName,strID,strDepart;
	if(m_depart.GetCurSel()==CB_ERR)strDepart="���в���";
	else m_depart.GetLBText(m_depart.GetCurSel(),strDepart); 
	double dbWage=0;
	m_name.GetWindowText(strName);
	m_kahao.GetWindowText(strID);
	j=1;
	try{
		if(strDepart=="���в���")
			strSql.Format("select * from ְ����������� e1,�����ű� e2 where  e1.���ű���=e2.���ű��� and ���� like '%s%%' and ���� like '%s%%' and ���='�α�'  order by ���� ",strID,strName);
		else
			strSql.Format("select * from ְ����������� e1,�����ű� e2 where e1.���ű���=e2.���ű��� and \
				���� like '%s%%' and ���� like '%s%%' and ������='%s' and ���='�α�' order by ����",strID,strName,strDepart);
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			x=0;
			for(count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
				
				str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(HeadTitle[count])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(HeadTitle[count])));
				if( count == 6 ) dbWage+=atof(str1); //��������
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
	strSql.Format("%.2f",dbWage);
	m_grid.SetTextMatrix(j,6,strSql);
	strSql.Format("����ѯ��: %ld ����Ϣ",j-1);
	GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(strSql);

	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow = 1;
		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
	EndWaitCursor();
}

HBRUSH CEmployeeQuery::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->m_hWnd==GetDlgItem(IDC_STATIC_TITLE)->m_hWnd || pWnd->m_hWnd==GetDlgItem(IDC_STATIC_NOTI)->m_hWnd){
		pDC->SetTextColor(RGB(255,0,0));
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BEGIN_EVENTSINK_MAP(CEmployeeQuery, CDialog)
    //{{AFX_EVENTSINK_MAP(CEmployeeQuery)
	ON_EVENT(CEmployeeQuery, IDC_MSHFLEXGRID2, -601 /* DblClick */, OnDblClickMshflexgrid2, VTS_NONE)
	ON_EVENT(CEmployeeQuery, IDC_MSHFLEXGRID2, -602 /* KeyDown */, OnKeyDownMshflexgrid2, VTS_PI2 VTS_I2)
	ON_EVENT(CEmployeeQuery, IDC_MSHFLEXGRID2, -600 /* Click */, OnClickMshflexgrid2, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CEmployeeQuery::OnDblClickMshflexgrid2() 
{
		if( flag_EXIT== 7777)return ;//��Ϊ������ѯʱʹ��,��Ҫ��ʧ�Ի���
		long row=m_grid.GetRow();
		if(row<m_grid.GetRows()-1 && row !=0){
			
			strKH=m_grid.GetTextMatrix(row,1);
			strName=m_grid.GetTextMatrix(row,2);//����
			strSex=m_grid.GetTextMatrix(row,3);//�Ա�
			strDate[0]=m_grid.GetTextMatrix(row,4);//��������
			strDate[1]=m_grid.GetTextMatrix(row,5);//��������
		//�������,���Ķ�ԭ������
			for(int i=0;i< m_grid.GetCols(0) ;i++)lineInfor[i]=m_grid.GetTextMatrix(row,i);
			
			if(p!=NULL)
				if( flagRELATE == 777 ) //��Ϊ����ʱʹ��
				{
					for( i=0;i< m_grid.GetCols(0) ;i++)((COperatChargeRelateFee *)p)->infor[i]=m_grid.GetTextMatrix(row,i);
				}

				else 
					for( i=0;i<COLS;i++)((CGh*)p)->infor[i]=m_grid.GetTextMatrix(row,i);
				
				CDialog::OnOK();
		}


}

void CEmployeeQuery::OnSelchangeCombo1() 
{
	OnOK();
}

BOOL CEmployeeQuery::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN && flag_EXIT != 7777 )
	{
		if(pMsg->wParam == VK_RETURN )OnDblClickMshflexgrid2();
		else if( pMsg->wParam==VK_DOWN)
			m_grid.SetFocus();
	}
		// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CEmployeeQuery::OnKeyDownMshflexgrid2(short FAR* KeyCode, short Shift) 
{
	long rows=m_grid.GetRows()-2;
	if(rows == 0)return; //û����Ŀ�򷴷���

	if( DOWN_ARROR == * KeyCode){  //�¼�ͷ���¶���
	
		m_grid.SetCol(0);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();

		for(int i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
	
		if(curRow < rows && curRow != 0 ) m_grid.SetRow(++curRow);
		else {
				curRow=1;
				m_grid.SetRow(curRow);

		}
		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
		

	}
	else if(UP_ARROR == * KeyCode){ //�ϼ�ͷ���¶���


		m_grid.SetCol(0);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();

		for(int i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
	
		if(curRow <= rows && curRow!= 1) m_grid.SetRow(--curRow);
		else {
				curRow=rows;
				m_grid.SetRow(curRow);

		}
		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}



	}	// TODO: Add your control notification handler code here
	
}

void CEmployeeQuery::OnClickMshflexgrid2() 
{
	if(m_grid.GetCols(0) == 5 ) return ; //ְ���ѯ����²�����
	const long ENDLINES=2;
	if(m_grid.GetRows() == ENDLINES )return;//�ж��Ƿ���Ҫ��ʾ��ݲ˵�

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202Ϊ������,0x205Ϊ����Ҽ���Ϣ
		SetSel();
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_MEDLIST);
	CMenu* pmenu=pm.GetSubMenu(iMenuSel);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  

	


	// TODO: Add your control notification handler code here
	
}

void CEmployeeQuery::OnToExcel() 
{
	extern void ToExcel(CMSHFlexGrid * pg);

	if( MessageBox("�Ƿ�ȷ��Ҫ������ Excel ��� ??? ","��ʾ",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	ToExcel(&m_grid);

}

void CEmployeeQuery::SetSel()
{
		long r1;
		r1=m_grid.GetRow();
		if(r1 >= m_grid.GetRows()-1 || curRow == r1)return;
		
		m_grid.SetCol(0);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();
		
		for(int i=1;i<8;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
		m_grid.SetRow(r1);
		curRow=r1;
		for( i=1;i<8;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
}

void CEmployeeQuery::OnMenuQEmpAdd() 
{
	// TODO: Add your command handler code here
	if(!theApp.AssertRole(ROLE_EMP_EDIT))return; 
	CEmployee ee;
	ee.DoModal();
}

void CEmployeeQuery::OnMenuQEmpDel() //
{
	if(!theApp.AssertRole(ROLE_EMP_EDIT))return; 

	long row=m_grid.GetRow();
	if( row != curRow ) return;
	CString strSql;
	strSql.Format("ȷ��Ҫע�� (%s)/(%s) ��???",m_grid.GetTextMatrix(curRow,1),m_grid.GetTextMatrix(curRow,2) );
	if( AfxMessageBox(strSql,MB_OKCANCEL)== IDCANCEL) return;
/*
	strSql.Format(" INSERT INTO LSQ_EMPLOYEE_DEL SELECT t.*,sysdate,(select \
		sys_context( 'userenv' , 'ip_address') from dual )||'_'||'%s' FROM ְ����������� t \
		WHERE ����='%s' ",LoginInformation.user,m_grid.GetTextMatrix(curRow,1) );
*/
	try{
		HospitalConnect->BeginTrans();
	//	HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
	//	strSql.Format("DELETE FROM ְ����������� WHERE ����='%s' ",m_grid.GetTextMatrix(curRow,1) );
		strSql.Format(" UPDATE  ְ����������� SET ���='����',�����=0.0,ds1=( SELECT sys_context('USERENV','ip_address')||'.'|| to_char(sysdate,'hh24yyyymimmssdd') ||'EMPOFF' from dual ),d1=sysdate WHERE ����='%s' ",m_grid.GetTextMatrix(curRow,1) );
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();
	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox("ɾ��ʧ��...");
		return;
	}
		
	
	AfxMessageBox("ɾ���ɹ�!!!");
	OnOK();
	
}

void CEmployeeQuery::OnMenuQEmpModify()  //���䱣����Ա�����޸�
{
	if(!theApp.AssertRole(ROLE_EMP_EDIT))return; 

	long row=m_grid.GetRow();
	if( row != curRow ) return;

	CEmployeeModify di; 
	di.strTitle.Format("���䱣����Ա�����޸�");
	di.strTmp=m_grid.GetTextMatrix(curRow,1);//����
	if(di.DoModal()==IDOK) OnOK();
}

void CEmployeeQuery::OnMenuQEmpSubsidy()  //������Ա����
{
	//"������","����","����","�Ա�","��������","��������",\
		"�����","��������","���"},str1;
	if(!theApp.AssertRole(ROLE_EMP_EDIT))return; 

	long row=m_grid.GetRow();
	if( row != curRow ) return;
	
	CSubsidySet di;
	di.strName= m_grid.GetTextMatrix(curRow,2); //����
	di.strKh=m_grid.GetTextMatrix(curRow,1); //����
	di.DoModal();
//	di.strTmp=m_grid.GetTextMatrix(curRow,1);//����

}

void CEmployeeQuery::OnSearch() 
{

	BeginWaitCursor();
	//����,����,�Ա�,��������,��������,����,�����,��������
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetRedraw(false);

	long j=0, i=0,x=0;
//	CString HeadTitle[]={"������","����","����","�Ա�","��������","��������",\
		"�����","��������","���","��������","�������"},str1;
	CString HeadTitle[]={"������","����","����","��������","�������"},str1;

	long  headWidth[]={1400,1200,1200,2200,1300,1300,1200,1000,1000,2000,1000};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<3)m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����кϲ�
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}
	CString strSql,strName,strID,strDepart;
	if(m_depart.GetCurSel()==CB_ERR)strDepart="���в���";
	else m_depart.GetLBText(m_depart.GetCurSel(),strDepart); 

	m_name.GetWindowText(strName);
	m_kahao.GetWindowText(strID);
	j=1;
	try{
		if(strDepart=="���в���")
			strSql.Format("select * from ְ����������� e1,�����ű� e2,\
			(select a.ds1 kh,b.ds1 ��������,b.n3 ������� from lsq_emp_headship a,lsq_upgrade b where \
			a.ds2=b.ds3 and b.ds2='ESUB') e3 \
			where  e1.���ű���=e2.���ű��� and e3.kh(+)=���� AND ���� like '%s%%' and ���� like '%s%%' and ��� not in( '����','����')  order by ���� ",strID,strName);
		else
	
		strSql.Format("select * from ְ����������� e1,�����ű� e2,\
			(select a.ds1 kh,b.ds1 ��������,b.n3 ������� from lsq_emp_headship a,lsq_upgrade b where \
			a.ds2=b.ds3 and b.ds2='ESUB') e3 \
		where e1.���ű���=e2.���ű��� and e3.kh(+)=���š�AND \
		���� like '%s%%' and ���� like '%s%%' and ������='%s' and ��� not in( '����','����') order by ����",strID,strName,strDepart);
			
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			x=0;
			for(count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
				
				str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(HeadTitle[count])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(HeadTitle[count])));
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
/*	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow = 1;
		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
*/	EndWaitCursor();	
}

void CEmployeeQuery::OnMenuQPassView() 
{
//{"������","����","����","�Ա�","��������","��������",\
		"�����","��������","���","pass"},str1;
	if(!theApp.AssertRole(ROLE_EMP_EDIT))return; 

	CPasswordView di;

	di.strTitle="���䱣�������ѯ";
	for(int i=0; i< 5; i++)
		di.str[i]=m_grid.GetTextMatrix(curRow,i);
	di.str[i]=m_grid.GetTextMatrix(curRow,9);//password

	if(di.DoModal()==IDOK)OnOK();
}

void CEmployeeQuery::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnOK();
}

void CEmployeeQuery::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

void CEmployeeQuery::OnMenuQuickBaseryDel() 
{
	// TODO: Add your command handler code here
	
}

void CEmployeeQuery::OnMenuQuickBaseryModify() 
{
	// TODO: Add your command handler code here
	
}

void CEmployeeQuery::OnMenuQuickBaseryViewpassword() 
{
	// TODO: Add your command handler code here
	
}
