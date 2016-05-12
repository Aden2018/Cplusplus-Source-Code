// EmployeeBmp.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "EmployeeBmp.h"
#include "OtherDecharge.H"
#include "employeeQueryDecharge.H"
#include "huajia.h"
#include "OperatChargeRelateFee.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmployeeBmp dialog


CEmployeeBmp::CEmployeeBmp(CWnd* pParent /*=NULL*/)
	: CDialog(CEmployeeBmp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmployeeBmp)
	//}}AFX_DATA_INIT
	backBrush.CreateSolidBrush(RGB(255,255,255));
	fontTitle.CreatePointFont(220,"�����п�");
	
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_upgrade WHERE ds2='FEE' ");
	PRINTflag=0;
}


void CEmployeeBmp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmployeeBmp)
	DDX_Control(pDX, IDC_EDIT_KH, c_kh);
	DDX_Control(pDX, IDC_STATIC_BACK, m_sb);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, c_date);
	DDX_Control(pDX, IDC_EDIT5, c_invoice);
	DDX_Control(pDX, IDC_EDIT4, c_personCash);
	DDX_Control(pDX, IDC_EDIT3, c_whole);
	DDX_Control(pDX, IDC_EDIT2, c_cash);
	DDX_Control(pDX, IDC_EDIT1, c_account);
	DDX_Control(pDX, IDC_COMBO1, c_type);
	DDX_Control(pDX, IDPRINT, b4);
	DDX_Control(pDX, IDCANCEL, b3);
	DDX_Control(pDX, IDOK, b2);
	DDX_Control(pDX, IDC_BUTTON_EMP, b1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmployeeBmp, CDialog)
	//{{AFX_MSG_MAP(CEmployeeBmp)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_EMP, OnButtonEmp)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_EDIT_KH, OnKillfocusEditKh)
	ON_EN_SETFOCUS(IDC_EDIT_KH, OnSetfocusEditKh)
	ON_BN_CLICKED(IDPRINT, OnPrint)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT1, IDC_EDIT5, OnChangeEdit1)
	ON_CONTROL_RANGE(EN_SETFOCUS, IDC_EDIT1, IDC_EDIT5, OnSetFocusEdit1)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmployeeBmp message handlers
/*******************************���ؼ���Ӧ��Ŀ*****************
	STATIC1 ��������
	STATIC2 ����
	STATIC3 ƾ֤��
	STATIC_01 ҽ�ƺ���
		   02 �����ת
		   03 �α����
		   04 �ʻ����
		   05 ʹ���ۼ�
		   06 �ʻ����
		   07 ����֧�����
		   08 ��������֧����д
		   09 ����֧��Сд
		   10 �����
		   11 סԺ��
		   12 �����ʻ�֧��
		   13 ͳ�����֧��
		   14 ���䱣��֧����д
		   15 Сд
	EDIT1 �ʻ�֧��
		2 �ֽ�֧��
		3 ͳ��֧��
		4 �����Է�
		5 ��������

******************************************************************/

BOOL CEmployeeBmp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);	
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	ClearInformation();

	CString strout;
	try{
		strout.Format("SELECT DS1 FROM lsq_UPGRADE WHERE ds2='EMP' ORDER BY n2 ");//����ְ���������
		recSet->Open(_bstr_t(strout),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
		
			strout=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt == VT_NULL ? "":recSet->GetFields()->GetItem(0L)->Value );
			c_type.AddString(strout);
			recSet->MoveNext();
		}
		recSet->Close();
		c_type.SetCurSel(0);
		long i=0;
		strout.Format("SELECT ds2, n1 FROM lsq_gh_type WHERE ds3='D' order by n2 ");
		recSet->Open(_bstr_t(strout),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
		
			strout=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? "":recSet->GetFields()->GetItem(i)->Value );
			strName.Add(strout); i++;
			strout=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? "":recSet->GetFields()->GetItem(i)->Value );
			strScale.Add(strout);
			i=0;

			recSet->MoveNext();
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox(strout);
		recSet->Close();
		return false;
	}	

	
	c_account.SetParent( (CWnd*)GetDlgItem(IDC_STATIC_BACK) );
	c_type.SetParent( (CWnd*)GetDlgItem(IDC_STATIC_BACK) );
	c_invoice.SetParent( (CWnd*)GetDlgItem(IDC_STATIC_BACK) );
	c_personCash.SetParent( (CWnd*)GetDlgItem(IDC_STATIC_BACK) );
	c_cash.SetParent( (CWnd*)GetDlgItem(IDC_STATIC_BACK) );
	c_date.SetParent( (CWnd*)GetDlgItem(IDC_STATIC_BACK) );
	c_whole.SetParent((CWnd*)GetDlgItem(IDC_STATIC_BACK) );
	c_kh.SetParent((CWnd*)GetDlgItem(IDC_STATIC_BACK) );


	c_type.EnableWindow(false);
	EnDiControl(false);


	CRect rt;
	GetDlgItem(IDC_STATIC_E1)->GetWindowRect(rt);
	ScreenToClient(rt);
	c_account.MoveWindow(rt);
	GetDlgItem(IDC_STATIC_E2)->GetWindowRect(rt);
	ScreenToClient(rt);
	c_whole.MoveWindow(rt);
	GetDlgItem(IDC_STATIC_E3)->GetWindowRect(rt);
	ScreenToClient(rt);
	c_cash.MoveWindow(rt);
	GetDlgItem(IDC_STATIC_E4)->GetWindowRect(rt);
	ScreenToClient(rt);
	c_personCash.MoveWindow(rt);
	GetDlgItem(IDC_STATIC_E5)->GetWindowRect(rt);
	ScreenToClient(rt);
	c_invoice.MoveWindow(rt);
	GetDlgItem(IDC_STATIC_EC1)->GetWindowRect(rt);
	ScreenToClient(rt);
	rt.bottom+=200;
	c_type.MoveWindow(rt);
	GetDlgItem(IDC_STATIC_ED1)->GetWindowRect(rt);
	ScreenToClient(rt);
	c_date.MoveWindow(rt);

	GetDlgItem(IDC_STATIC2)->GetWindowRect(rt);
	ScreenToClient(rt);
	GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);

	c_kh.MoveWindow(rt);
	

	return TRUE;  // return TRUE unless you set the focus to a control	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



HBRUSH CEmployeeBmp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetBkColor(RGB(255,255,255));
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(58,110,165));
/*	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_BACK)->m_hWnd )
	{
		CDC *pE=GetDlgItem(IDC_STATIC_BACK)->GetDC();
		pE->SetTextColor(RGB(255,0,0));
		c_account.GetDC()->SetTextColor(RGB(255,0,0));

	}
*/	
	if( pWnd->m_hWnd != GetDlgItem(IDC_STATIC_BACK)->m_hWnd )
	{
		pDC->SetTextColor(RGB(255,0,0));
	}


	return (HBRUSH )backBrush.GetSafeHandle();
	
}

void CEmployeeBmp::ClearInformation()
{
	GetDlgItem(IDC_STATIC1)->SetWindowText("");
	GetDlgItem(IDC_STATIC2)->SetWindowText("");
	GetDlgItem(IDC_STATIC3)->SetWindowText("");
	
	GetDlgItem(IDC_STATIC_01)->SetWindowText("");
	GetDlgItem(IDC_STATIC_02)->SetWindowText("");
	GetDlgItem(IDC_STATIC_03)->SetWindowText("");
	GetDlgItem(IDC_STATIC_04)->SetWindowText("");
	GetDlgItem(IDC_STATIC_05)->SetWindowText("");
	GetDlgItem(IDC_STATIC_06)->SetWindowText("");
	GetDlgItem(IDC_STATIC_07)->SetWindowText("");
	GetDlgItem(IDC_STATIC_08)->SetWindowText("");
	GetDlgItem(IDC_STATIC_09)->SetWindowText("");
	GetDlgItem(IDC_STATIC_10)->SetWindowText("");
	GetDlgItem(IDC_STATIC_11)->SetWindowText("");
	GetDlgItem(IDC_STATIC_12)->SetWindowText("");
	GetDlgItem(IDC_STATIC_13)->SetWindowText("");
	GetDlgItem(IDC_STATIC_14)->SetWindowText("");
	GetDlgItem(IDC_STATIC_15)->SetWindowText("");
	GetDlgItem(IDC_STATIC_E1)->SetWindowText("");
	GetDlgItem(IDC_STATIC_E2)->SetWindowText("");
	GetDlgItem(IDC_STATIC_E3)->SetWindowText("");
	GetDlgItem(IDC_STATIC_E4)->SetWindowText("");
	GetDlgItem(IDC_STATIC_E5)->SetWindowText("");

	GetDlgItem(IDC_STATIC_EC1)->SetWindowText("");
	GetDlgItem(IDC_STATIC_ED1)->SetWindowText("");
	clearEdit();
	c_date.SetTime(COleDateTime::GetCurrentTime());

}

void CEmployeeBmp::OnButtonEmp()  //����ְ��������Ϣ
{
	CEmployeeQueryDecharge rybm;
	rybm.p=strInfor;
	if(rybm.DoModal()==IDOK){
		ClearInformation();
/*	CString HeadTitle[]={"������","��������","����","����","�Ա�","����","�����",\
		"���","������","ʹ���ۼ�","ƾ֤��"};
	STATIC1 ��������
	STATIC2 ����
	STATIC3 ƾ֤��
	STATIC_01 ҽ�ƺ���
		   02 �����ת
		   03 �α����
		   04 �ʻ����
		   05 ʹ���ۼ�
		   06 �ʻ����
		   07 ����֧�����
		   08 ��������֧����д
		   09 ����֧��Сд
		   10 �����
		   11 סԺ��
		   12 �����ʻ�֧��
		   13 ͳ�����֧��
		   14 ���䱣��֧����д
		   15 Сд
	EDIT1 �ʻ�֧��
		2 �ֽ�֧��
		3 ͳ��֧��
		4 �����Է�
		5 ��������
*/
		EmpInforWrite();
		c_kh.SetWindowText(" "+strInfor[3]+" /"+strInfor[4]+" /"+strInfor[5]);

	
	}
	
}

BOOL CEmployeeBmp::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN ) {
		if(pMsg->hwnd == c_kh.m_hWnd ){
			if( !GetEmpInformation()) {
				ClearInformation();
				EnDiControl(false);
			}
			EmpInforWrite();
			return true;
		}

		if( pMsg->hwnd == c_type.m_hWnd ) c_account.SetFocus() ;
		else if(pMsg->hwnd == c_account.m_hWnd ) c_whole.SetFocus() ;
		else if(pMsg->hwnd == c_whole.m_hWnd ) c_cash.SetFocus();
		else if(pMsg->hwnd == c_cash.m_hWnd ) c_personCash.SetFocus() ;
		else if(pMsg->hwnd == c_personCash.m_hWnd ) c_invoice.SetFocus() ;
		else if(pMsg->hwnd == c_invoice.m_hWnd ) c_account.SetFocus();
		else goto END_MESSAGE;

		return true;
	}
		
	//	pMsg->wParam=VK_TAB;
END_MESSAGE:

	return CDialog::PreTranslateMessage(pMsg);
}

void CEmployeeBmp::Compute()
{
/*******************************���ؼ���Ӧ��Ŀ*****************
	STATIC1 ��������
	STATIC2 ����
	STATIC3 ƾ֤��
	STATIC_01 ҽ�ƺ���
		   02 �����ת
		   03 �α����
		   04 �ʻ����
		   05 ʹ���ۼ�
		   06 �ʻ����
		   07 ����֧�����
		   08 ��������֧����д
		   09 ����֧��Сд
		   10 �����
		   11 סԺ��
		   12 �����ʻ�֧��
		   13 ͳ�����֧��
		   14 ���䱣��֧����д
		   15 Сд
	EDIT1 �ʻ�֧�� m_acccout
		2 �ֽ�֧�� m_cash
		3 ͳ��֧�� m_whole
		4 �����Է� m_perCash
		5 �������� m_invoice

******************************************************************/
	
	CString m_account,m_cash,m_whole,m_personCash,m_invoice;
	long i=0;
	c_account.GetWindowText(m_account);
	c_cash.GetWindowText(m_cash);
	c_personCash.GetWindowText(m_personCash);
	c_invoice.GetWindowText(m_invoice);
	c_whole.GetWindowText(m_whole);
	double personCash,dbT1,dbT2,countCash;
	CString strT1,strT2;

	countCash= atof( m_account) + atof(m_cash) + atof( m_whole);
//	strT1.Format("%.2f",atof(m_account)+atof(m_whole) ); //�������ս��
	strT1.Format("%.2f",countCash); //�������ս��

	GetDlgItem(IDC_STATIC_09)->SetWindowText(strT1);//"��"
	GetDlgItem(IDC_STATIC_08)->SetWindowText( CHuaJia::GetBigMoney(countCash ) );

	strT1.Format("%.2f",personCash=atof(m_cash)-atof(m_personCash));
	GetDlgItem(IDC_STATIC_07)->SetWindowText(strT1); //����֧��"��"+
//{"������","��������","����","����","�Ա�","����","�����",	"���","������","ʹ���ۼ�","ƾ֤��"};	
	if( c_type.GetCurSel() == 0 ){ //����
		
		dbT2 = atof( strInfor[6] ) > personCash ? personCash :atof( strInfor[6] ) ;
		
		strT1.Format("%.2f",countCash ); //�ܷ���
		GetDlgItem(IDC_STATIC_10)->SetWindowText(strT1);//�������
		
		strT1.Format("%.2f",dbT2);
	
		GetDlgItem(IDC_STATIC_14)->SetWindowText(CHuaJia::GetBigMoney(dbT2 ) );
		GetDlgItem(IDC_STATIC_15)->SetWindowText(strT1 );
		GetDlgItem(IDC_STATIC_12)->SetWindowText(strT1 ); 

		strT1.Format("%.2f",atof(strInfor[6])-dbT2 );
		GetDlgItem(IDC_STATIC_06)->SetWindowText(strT1); //�ʻ�ʣ��
		GetDlgItem(IDC_STATIC_11)->SetWindowText("0"); //סԺ����
		
	}
	else if( c_type.GetCurSel() == 1 || c_type.GetCurSel() == 2 ){ //סԺ������������
		
		GetDlgItem(IDC_STATIC_03)->GetWindowText(strT1);
		if( strT1.IsEmpty() ) {
		//	AfxMessageBox("����ѡ��Ҫ��������Ա!!!!!!!!");
			return;
		}
		for(i=0 ; i < strName.GetSize() ; i++ )
			if( strName.GetAt(i).Compare(strT1) == 0 ) break;

		if( i >= strName.GetSize() ){
				AfxMessageBox("����ϵ�����Աά�����ݿ�,ϵͳ��û�д�����Ա�ı�����׼!!!");
				return;
			}
	
		dbT1=atof(strScale.GetAt(i) ); //ͳ��֧������
		strT1.Format("%.2f",countCash);
		GetDlgItem(IDC_STATIC_11)->SetWindowText(strT1); //סԺ����
		GetDlgItem(IDC_STATIC_10)->SetWindowText("0");//�������
	
		strT2.Format("%.2f", personCash* dbT1) ;
		GetDlgItem(IDC_STATIC_13)->SetWindowText(strT2); //ͳ��֧��

		dbT2 = atof( strInfor[6] ) > personCash* (1-dbT1) ? personCash* (1-dbT1) :atof( strInfor[6] ) ;
		strT2.Format("%.2f",dbT2);
		GetDlgItem(IDC_STATIC_12)->SetWindowText(strT2); //�����ʻ�֧��
	
		
		strT2.Format("%.2f", atof( strInfor[6] ) -dbT2);
		GetDlgItem(IDC_STATIC_06)->SetWindowText(strT2); //�ʻ����

		strT2.Format("%.2f",dbT2+personCash*dbT1);
		GetDlgItem(IDC_STATIC_14)->SetWindowText(CHuaJia::GetBigMoney(dbT2+personCash*dbT1 ) );
		GetDlgItem(IDC_STATIC_15)->SetWindowText(strT2 );

	}
	
}

void CEmployeeBmp::OnChangeEdit1(UINT nID) 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	Compute();
}

void CEmployeeBmp::OnSelchangeCombo1() //�������
{
	CString strT1;
	GetDlgItem(IDC_STATIC2)->GetWindowText(strT1);
	if( strT1.IsEmpty() ){
		AfxMessageBox("����ѡ������Ա!!Ȼ���ٽ��б�������!!!");
		return;

	}
	if( c_type.GetCurSel() == 3 || c_type.GetCurSel() == 4 ) //���ʻ��ߵ���
	{
		clearEdit();
		GetDlgItem(IDC_STATIC_09)->SetWindowText("0");
		GetDlgItem(IDC_STATIC_08)->SetWindowText("0");
		GetDlgItem(IDC_STATIC_10)->SetWindowText("0");
		GetDlgItem(IDC_STATIC_11)->SetWindowText("0");
		GetDlgItem(IDC_STATIC_13)->SetWindowText("0");
		GetDlgItem(IDC_STATIC_12)->SetWindowText(strInfor[6] );
		GetDlgItem(IDC_STATIC_14)->SetWindowText(CHuaJia::GetBigMoney(atof(strInfor[6]) ) );
		GetDlgItem(IDC_STATIC_15)->SetWindowText(strInfor[6] );
		GetDlgItem(IDC_STATIC_06)->SetWindowText("0"); //�ʻ�ʣ��

		EnDiControl(false);
		//���½������ʻ���Ǯ���


	}
	else{
		EnDiControl(true);

		clearEdit();
	
		GetDlgItem(IDC_STATIC_09)->SetWindowText("0");
		GetDlgItem(IDC_STATIC_08)->SetWindowText("0");
		GetDlgItem(IDC_STATIC_10)->SetWindowText("0");
		GetDlgItem(IDC_STATIC_11)->SetWindowText("0");
		GetDlgItem(IDC_STATIC_13)->SetWindowText("0");
		GetDlgItem(IDC_STATIC_12)->SetWindowText("");
		GetDlgItem(IDC_STATIC_14)->SetWindowText("");
		GetDlgItem(IDC_STATIC_15)->SetWindowText("0" );
		GetDlgItem(IDC_STATIC_06)->SetWindowText(strInfor[6]); //�ʻ�ʣ��




	}
}

void CEmployeeBmp::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}

void CEmployeeBmp::OnOK() 
{
	UpdateData();
	CString strType,strSql,strT1,strT2;
	c_type.GetLBText(c_type.GetCurSel(),strType);

	if( strInfor[3].IsEmpty() ){
		AfxMessageBox("����ѡ��Ҫ��������Ա,Ȼ���ٽ�����Ӧ�Ĳ���!!!");
		return ;
	}
	GetDlgItem(IDC_STATIC3)->GetWindowText(strT1);
	double db1,db2,db3,db4,dbT[10];
	c_account.GetWindowText(strT1);
	db1=atof(strT1); //�ʻ�
	c_whole.GetWindowText(strT1);
	db2=atof(strT1); //ͳ��
	c_cash.GetWindowText(strT1);
	db3=atof(strT1); //����
	c_personCash.GetWindowText(strT1);
	db4=atof(strT1); //�Է�
	
	for(long i=0 ; i < strName.GetSize() ; i++ )
		if( strName.GetAt(i).Compare(strInfor[7]) == 0 ) break;
		
		if( i >= strName.GetSize() ){
			AfxMessageBox("����ϵ�����Աά�����ݿ�,ϵͳ��û�д�����Ա�ı�����׼!!!");
			return;
		}
	dbT[0]=atof(strScale.GetAt(i) ); //ͳ��֧������
	if( c_type.GetCurSel()== 0 || c_type.GetCurSel() == 3 || c_type.GetCurSel() == 4 )
		dbT[0]=0.0;
	c_invoice.GetWindowText(strT1); 
	dbT[1]=atof(strT1); //��Ʊ����
	GetDlgItem(IDC_STATIC_12)->GetWindowText(strT1); //�ʻ�֧��
	dbT[2]=atof(strT1); //�ʻ�֧����
	GetDlgItem(IDC_STATIC3)->GetWindowText( strT1);
	COleDateTime md;
	c_date.GetTime(md);
	try{
		HospitalConnect->BeginTrans();
//{"������","��������","����","����","�Ա�","����","�����",\
		"���","������","ʹ���ۼ�","ƾ֤��"};
	strSql.Format(" INSERT INTO lsq_emp_decharge(ds1,ds2,ds3,ds4,ds5,ds6,ds7,n1,\
			n2,n3,n4,n5,n6,n7,n8,n9,d1,d2,ds8 ) VALUES('%s','%s','%s','%s','%s','%s','%s',%ld,\
			%.2f,%.2f,%.2f,%.2f,%.4f,%.2f,%.2f,%.2f,to_date(%s,'yyyymmdd'),sysdate,\
			to_char(sysdate,'yyyymmddhh24miss')||'_'||(select sys_context( 'userenv' , 'ip_address')  from dual)) ",\
			LoginInformation.user,strInfor[1],strInfor[2],strInfor[3],strInfor[4],strInfor[7],strType,\
			atol(strT1),db1,db2,db3,db4,dbT[0],dbT[2],dbT[0]*(db3-db4),dbT[1],md.Format("%Y%m%d") );

		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		strSql.Format(" UPDATE ְ����������� SET �����=(�����)-(%.2f),ds1=( SELECT sys_context('USERENV','ip_address')||'.'|| to_char(sysdate,'hh24yyyymimmssdd') ||'EMPDEC' from dual ),d1=sysdate WHERE ����='%s' ",dbT[2],strInfor[2] );
	
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);



		HospitalConnect->CommitTrans();



	}catch(_com_error e) 
	{
		AfxMessageBox("�����쳣!!!,�����½��>>>>>>");
		HospitalConnect->RollbackTrans();
		return;
	}
	AfxMessageBox("��д�ɹ�!!!");
	PRINTflag=0;

	c_type.SetCurSel(0);
	c_type.EnableWindow(false);
	EnDiControl(false);
	ClearInformation();
	for(int  count=0; count < sizeof( strInfor) /sizeof(CString) ; count++) strInfor[count]="";
	c_kh.SetWindowText("");
	GetDlgItem(IDC_STATIC_06)->SetWindowText("");
	c_kh.SetFocus();
}

void CEmployeeBmp::EnDiControl(BOOL flag)
{
	c_account.EnableWindow(flag);
	c_cash.EnableWindow(flag);
	c_whole.EnableWindow(flag);
	c_personCash.EnableWindow(flag);
	c_invoice.EnableWindow(flag);

	c_account.ShowWindow( flag ? SW_SHOW: SW_HIDE);
	c_cash.ShowWindow( flag ? SW_SHOW: SW_HIDE);
	c_whole.ShowWindow( flag ? SW_SHOW: SW_HIDE);
	c_personCash.ShowWindow( flag ? SW_SHOW: SW_HIDE);
	c_invoice.ShowWindow( flag ? SW_SHOW: SW_HIDE);

	GetDlgItem(IDC_STATIC_E1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_E2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_E3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_E4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_E5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EC1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_ED1)->ShowWindow(SW_HIDE);

}

void CEmployeeBmp::clearEdit()
{
	c_account.SetWindowText("0");
	c_invoice.SetWindowText("0");
	c_personCash.SetWindowText("0");
	c_cash.SetWindowText("0");
	c_whole.SetWindowText("0");

}

void CEmployeeBmp::OnSetFocusEdit1(UINT nID)
{
	CEdit *pE=(CEdit*)GetFocus();
	pE->SetSel(0,-1);
}

BOOL CEmployeeBmp::GetEmpInformation()
{
	CString strSql,strID; 
	long cols,count;
	UpdateData();
	c_kh.GetWindowText(strID);
	for( count=0; count < sizeof( strInfor) /sizeof(CString) ; count++) strInfor[count]="";

	if( strID.IsEmpty() ) return false;

	try{
		strSql.Format(" SELECT * FROM V_EMP_DECHARGE_COUNT WHERE  ���� = '%s' ",strID);
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->GetCount();
		if(!recSet->adoEOF){
			for(count=0;count< cols ;count++){
				
				strID=(char*)_bstr_t( recSet->GetFields()->GetItem(count)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(count)->Value);
				strInfor[count]=strID;
			}
			strInfor[count]="FFFFFFFF";
			recSet->Close();
			return true;
		}
	
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox("���ݿ�����ƻ�,��������...");
		return false;
	}
}

void CEmployeeBmp::EmpInforWrite()
{
	GetDlgItem(IDC_STATIC1)->SetWindowText(strInfor[1]);

	if( strInfor[3].IsEmpty() )GetDlgItem(IDC_STATIC2)->SetWindowText("");
	else
		GetDlgItem(IDC_STATIC2)->SetWindowText(" "+strInfor[3]+" /"+strInfor[4]+" /"+strInfor[5]);
	GetDlgItem(IDC_STATIC3)->SetWindowText(strInfor[10]);
	GetDlgItem(IDC_STATIC_01)->SetWindowText(strInfor[2]);
	GetDlgItem(IDC_STATIC_02)->SetWindowText(strInfor[8]);
	GetDlgItem(IDC_STATIC_03)->SetWindowText(strInfor[7]);
	GetDlgItem(IDC_STATIC_04)->SetWindowText(strInfor[6]);
	GetDlgItem(IDC_STATIC_05)->SetWindowText(strInfor[9]);
	GetDlgItem(IDC_STATIC_06)->SetWindowText(strInfor[6]);
	Compute();
	
	EnDiControl(true);
	c_type.EnableWindow(true);
	c_type.SetFocus();
	c_type.SetCurSel(0);

}

void CEmployeeBmp::OnKillfocusEditKh() 
{
	CString str1;
	GetDlgItem(IDC_STATIC2)->GetWindowText(str1);
	c_kh.SetWindowText(str1);
}

void CEmployeeBmp::OnSetfocusEditKh() 
{
	c_kh.SetWindowText(strInfor[2]);
}

extern _Application app ;
extern Workbooks books;
extern _Workbook book;
extern Worksheets sheets;
extern _Worksheet sheet;
extern COleVariant vOpt;
#define _O(x) COleVariant(x)
#define STANDARDFONT  12
#define FONTNAME	"����"


void CEmployeeBmp::OnPrint() 
{
	UpdateData();

	BeginWaitCursor();

	CString strFileName;
	strFileName.Format("%s",LoginInformation.path);
	strFileName+="chargeprice.xls";


//	if( ! app ){
		app.CreateDispatch("excel.application");
		if(!app){
			AfxMessageBox("��ע��ϵͳ�б���װ��EXCEL97 ���� EXCEL2000 ,����˹��ܲ���ʹ��...");
			return;
		}
		books=app.GetWorkbooks();
		book=books.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
		sheets=book.GetWorksheets();

//	}
	sheet=sheets.GetItem(COleVariant((short)5)); //sheet5��Ϊ������Ա�������

	app.SetVisible(false);

	CString strCell[]={"B3","d3","e3","b4","d4","f4","b5","d5","f5",\
		"f6","b7","d7","f7","b8","d8","f8","b9","f9","b10","e10","f11",\
		"b12","e12","b13","F13"}; //�� 25
	//�ֱ�Ϊ ����,����,ƾ֤��,ҽ�ƺ�,�����ת,�α���,���,�ۼ�ʹ��,Ŀǰ����,\
	����,�ʻ�,����֧��,����,ͳ��,�����Է�,����ʵ��,�ܼƷѴ�д,�ܼƷ�Сд,�����,סԺ��,������ \
	�ʻ�֧��,������,�ܱ�����д,Сд
	
	CString strData[30],strTemp,strT2;

	Range vr;
	long i=0;
//{"������","��������","����","����","�Ա�","����","�����",\
		"���","������","ʹ���ۼ�","ƾ֤��"};
	GetDlgItem(IDC_STATIC1)->GetWindowText(strData[i++] );
	strData[i++]=strInfor[3];
	GetDlgItem(IDC_STATIC3)->GetWindowText(strTemp);
	strT2.Format("%06d",atol(strTemp) );
	strData[i++]="������("+strT2+")��";
	GetDlgItem(IDC_STATIC_01)->GetWindowText(strData[i++]);
	GetDlgItem(IDC_STATIC_02)->GetWindowText(strData[i++]);
	GetDlgItem(IDC_STATIC_03)->GetWindowText(strData[i++]);
	GetDlgItem(IDC_STATIC_04)->GetWindowText(strData[i++]);
	GetDlgItem(IDC_STATIC_05)->GetWindowText(strData[i++]);
	GetDlgItem(IDC_STATIC_06)->GetWindowText(strData[i++]);

	c_type.GetLBText(c_type.GetCurSel(),strData[i++] );
	c_account.GetWindowText( strData[i++] );
	c_cash.GetWindowText( strData[i++] );

	COleDateTime dt1;
	c_date.GetTime(dt1);
	strData[i++]= dt1.Format("%Y-%m-%d");
	c_whole.GetWindowText( strData[i++] );
	c_personCash.GetWindowText( strData[i++] );
	GetDlgItem(IDC_STATIC_07)->GetWindowText( strData[i++] );

	GetDlgItem(IDC_STATIC_08)->GetWindowText(strData[i++]);
	GetDlgItem(IDC_STATIC_09)->GetWindowText(strData[i++]);
	GetDlgItem(IDC_STATIC_10)->GetWindowText(strData[i++]);

	
	GetDlgItem(IDC_STATIC_11)->GetWindowText(strData[i++]);

	c_invoice.GetWindowText(strData[i++]);
	
	GetDlgItem(IDC_STATIC_12)->GetWindowText(strData[i++]);
	GetDlgItem(IDC_STATIC_13)->GetWindowText(strData[i++]);
	GetDlgItem(IDC_STATIC_14)->GetWindowText(strData[i++]);
	GetDlgItem(IDC_STATIC_15)->GetWindowText(strData[i++]);



	
	for(long z=0 ;z < i ; z++ )
		COperatChargeRelateFee::WriteExcelCell(strCell[z],strData[z]);


	PageSetup pageinfo=sheet.GetPageSetup();
//	sheet.PrintPreview(_O((short)1));
	sheet.PrintOut(vOpt,vOpt,_O((short)1),vOpt,vOpt,vOpt,vOpt,vOpt);


//	sheet=sheets.GetItem(COleVariant((short)1)); //sheet1 ��ӡ�շѵ����
	sheet.ReleaseDispatch();

	sheets.ReleaseDispatch();
	book.Close(_O((short)0),vOpt,vOpt); //�ر�EXCEL,�������ļ�

	book.ReleaseDispatch();
	books.Close();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	app.DetachDispatch();
	app.Quit();

	EndWaitCursor();

	PRINTflag=2;
}

void CEmployeeBmp::OnCancel() 
{
	CString strNoti=COtherDecharge::GetStringTitle("SELECT ds2 FROM LSQ_GH_TYPE WHERE ds1='BAA' AND ds3='B' ");

	if( PRINTflag==2 && AfxMessageBox(strNoti,MB_OKCANCEL)==IDCANCEL) return;
	
	CDialog::OnCancel();
}

void CEmployeeBmp::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	c_kh.SetFocus();	
}
