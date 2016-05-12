// HuaJia.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "HuaJia.h"
#include "queryRybm.h"
#include "medStockList.h" 
#include "cureList.h"
#include "paymedFee.h"
#include "MedCodeQuery.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHuaJia dialog


CHuaJia::CHuaJia(CWnd* pParent /*=NULL*/)
	: CDialog(CHuaJia::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHuaJia)
	//}}AFX_DATA_INIT
	fontSmall.CreatePointFont(100,"����");
}


void CHuaJia::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHuaJia)
	DDX_Control(pDX, IDBUTTON_PRINT, m_223);
	DDX_Control(pDX, IDBUTTON_ROLLMED, c_rollmedbutton);
	DDX_Control(pDX, IDC_EDIT_X7, x7);
	DDX_Control(pDX, IDC_EDIT_X6, x6);
	DDX_Control(pDX, IDC_EDIT_X5, x5);
	DDX_Control(pDX, IDC_EDIT_X4, x4);
	DDX_Control(pDX, IDC_EDIT_X3, x3);
	DDX_Control(pDX, IDC_EDIT_X2, x2);
	DDX_Control(pDX, IDC_EDIT_X1, x1);
	DDX_Control(pDX, IDC_EDIT_MEDNAME, c_medname);
	DDX_Control(pDX, IDC_EDIT_MEDGG, c_medgg);
	DDX_Control(pDX, IDC_EDIT_MED_NUM, c_mednum);
	DDX_Control(pDX, IDBUTTON_CHARGE_PRICE, m_xx);
	DDX_Control(pDX, IDC_EDIT_TYPE, c_type);
	DDX_Control(pDX, IDC_EDIT_SICK, c_sick);
	DDX_Control(pDX, IDC_EDIT_DOCTOR, c_doctor);
	DDX_Control(pDX, IDC_EDIT_DANJUHAO, c_danjuhao);
	DDX_Control(pDX, IDC_BUTTON_DOCTOR, m_34);
	DDX_Control(pDX, IDOK, m_3);
	DDX_Control(pDX, IDCANCEL, m_2);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	DDX_Control(pDX, IDC_MSHFLEXGRID2, m_grid2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHuaJia, CDialog)
	//{{AFX_MSG_MAP(CHuaJia)
	ON_BN_CLICKED(IDC_BUTTON_DOCTOR, OnButtonDoctor)
	ON_EN_KILLFOCUS(IDC_EDIT_DOCTOR, OnKillfocusEditDoctor)
	ON_EN_SETFOCUS(IDC_EDIT_DOCTOR, OnSetfocusEditDoctor)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDBUTTON_CHARGE_PRICE, OnChargePrice)
	ON_EN_KILLFOCUS(IDC_EDIT_MED_NUM, OnKillfocusEditMedNum)
	ON_EN_SETFOCUS(IDC_EDIT_MED_NUM, OnSetfocusEditMedNum)
	ON_EN_CHANGE(IDC_EDIT_X1, OnChangeEditX1)
	ON_BN_CLICKED(IDBUTTON_ROLLMED, OnRollmed)
	ON_BN_CLICKED(IDBUTTON_PRINT, OnPrint)
	ON_EN_CHANGE(IDC_EDIT_X8, OnChangeEditX8)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT_X9, OnChangeEditX9)
	ON_EN_CHANGE(IDC_EDIT_X5, OnChangeEditX5)
	//}}AFX_MSG_MAP
	ON_EN_KILLFOCUS(T_EDIT_HUAJIA,OnKillEditCtrl)
	ON_EN_KILLFOCUS(T_EDIT_CURE,OnKillEdit2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHuaJia message handlers

BOOL CHuaJia::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	CString HeadTitle[]={"���","����","BM","�Һ�����","����","���к�"};
// 							0     1	     2       3        4       5
const int SCALE1= 55 ; //ֱϵ����Ϊ 55%,������ŮΪ��ְ����ҲΪ 55%
const int SCALE2= 20 ; //������ŮΪ˫ְ���� 20%

	c_sick.SetWindowText(str2[1]);
	c_type.SetWindowText(str2[3]);
	c_danjuhao.SetWindowText(str2[5]);
	GetDlgItem(IDC_EDIT_COUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_COUNT)->SetWindowText("");
	GetDlgItem(IDC_EDIT_GH_HUAJIA)->SetWindowText("�Һ�: "+strGhHuajia[0] );
	CString strSql,s1,s2;
	x4.SetWindowText("100%");
	scale=1; //�����Ը�,Ĭ��
	balance=0;
	GetDlgItem(IDOK)->EnableWindow(false); //����OK��ť

	try{
		if(str2[3] == "���䱣��"){
			
		//	GetDlgItem(IDC_STATIC_PRICE)->ShowWindow(SW_SHOW);
		//	GetDlgItem(IDC_STATIC_PRICE2)->ShowWindow(SW_SHOW);

			strSql.Format("select * from ְ����������� where ���� = '%s' ",str2[2]);
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){
				s1=(char*)_bstr_t(recSet->GetCollect("�����").vt == VT_NULL? "0":recSet->GetCollect("�����"));
				balance=atof(s1);
				s2.Format(" %s : %s ","�ʻ����Ϊ",s1);
				x1.SetWindowText(s1);
			}
			recSet->Close();
		}
		else if(str2[3] == "��������"){
			strSql.Format("select NVL(xm,' ') as xm,NVL(xb,' ') as xb,NVL(xingzhi,' ') as xz,\
				NVL(����,' ') as name ,NVL(yuer,'0') as yuer from codeQingShu a,ְ����������� b  where ����=KAHAO and BM = '%s' ",str2[2]);
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){

				GetDlgItem(IDC_STATIC_PRICE)->ShowWindow(SW_SHOW);

				s1=(char*)_bstr_t(recSet->GetCollect("name"));
				s2.Format("������:%s",s1);

				s1=(char*)_bstr_t(recSet->GetCollect("yuer"));
				x1.SetWindowText(s1);
				balance=atof(s1);

				s1=(char*)_bstr_t(recSet->GetCollect("xz"));
				s2+="     "+s1;
				GetDlgItem(IDC_STATIC_PRICE)->SetWindowText(s2);
			

			}

			recSet->Close();

		}
		else if(str2[3]=="�ض�����" || str2[3]=="��������" || str2[3] == "����ͳ��" || str2[3]=="��ͥ����" )
		{
			if(str2[3]=="�ض�����" ){
			
				GetDlgItem(IDC_STATIC_X1)->SetWindowText("ͳ��֧��");
	
				GetDlgItem(IDC_STATIC_X8)->SetWindowText("��ǰ����");
				GetDlgItem(IDC_STATIC_X9)->SetWindowText("����Ա��");
				GetDlgItem(IDC_STATIC_X5)->SetWindowText("IC��֧��");
			
				GetDlgItem(IDC_EDIT_X8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_EDIT_X9)->ShowWindow(SW_SHOW);
				((CEdit*)GetDlgItem(IDC_EDIT_X9))->SetReadOnly(false);
				((CEdit*)GetDlgItem(IDC_EDIT_X5))->SetReadOnly(false);
				GetDlgItem(IDC_STATIC_X8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_X9)->ShowWindow(SW_SHOW);
			
				GetDlgItem(IDC_STATIC_X8)->SetFont(&fontSmall);
				GetDlgItem(IDC_STATIC_X9)->SetFont(&fontSmall);
				GetDlgItem(IDC_STATIC_X5)->SetFont(&fontSmall);
			
			}
			else
			{
				GetDlgItem(IDC_STATIC_X1)->SetWindowText("IC��֧��");
				GetDlgItem(IDC_STATIC_X5)->SetWindowText("�����ϼ�");
			}
			GetDlgItem(IDC_STATIC_X6)->SetWindowText("�ֽ�֧��");
			x1.SetReadOnly(false);
			CRect rt1,rt2;
			GetDlgItem(IDC_STATIC_X5)->GetWindowRect(rt1);
			ScreenToClient(rt1);
			GetDlgItem(IDC_STATIC_X6)->GetWindowRect(rt2);
			ScreenToClient(rt2);
			GetDlgItem(IDC_STATIC_X5)->MoveWindow(rt2);
			GetDlgItem(IDC_STATIC_X6)->MoveWindow(rt1);
		
			GetDlgItem(IDC_EDIT_X5)->GetWindowRect(rt1);
			ScreenToClient(rt1);
			GetDlgItem(IDC_EDIT_X6)->GetWindowRect(rt2);
			ScreenToClient(rt2);
			GetDlgItem(IDC_EDIT_X5)->MoveWindow(rt2);
			GetDlgItem(IDC_EDIT_X6)->MoveWindow(rt1);

		}
		else if( str2[3] == "סԺ��Ա" ){
			strSql.Format("SELECT price FROM lsq_reside_hos WHERE serial  = '%s' ",str2[5]);
			balance=atof(COtherDecharge::GetStringTitle(strSql) );
			s2.Format("%.2f",balance);
			x1.SetWindowText(s2);
		}
		else
		{
			GetDlgItem(IDC_STATIC_X1)->SetWindowText("��  ��");
			x1.SetReadOnly(false);
		}
		
	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox(strSql);
		return false;
	}

//	fontTitle.CreatePointFont(220,"����");
//	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	fontMoveEdit.CreatePointFont(120,"����");

	CRect r1(0,0,0,0);
	editCtrl.Create(WS_CHILD,r1,this,T_EDIT_HUAJIA);
	editCtrl.SetFont(&fontMoveEdit);
	edit2.Create(WS_CHILD,r1,this,T_EDIT_CURE);
	edit2.SetFont(&fontMoveEdit);

	SetGridHead();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHuaJia::OnButtonDoctor() 
{
	CQueryRybm rybm;
	if(rybm.DoModal()==IDOK){
		m_strDoctorBm=rybm.strNum;
		c_doctor.SetWindowText(rybm.strName);

	}
}

void CHuaJia::OnKillfocusEditDoctor() 
{
	CString str1,strSql;
	c_doctor.GetWindowText(str1);
	if(str1.IsEmpty()){
	//	c_doctor.SetFocus();
		return;
	}
	try{
		strSql.Format("select NVL(name,' ') NAME from operator where rybm='%s' ",str1);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			m_strDoctorBm=str1;
			c_doctor.SetWindowText((char*)_bstr_t(recSet->GetCollect("NAME")));
		}
		else {
			m_strDoctorBm="";
			c_doctor.SetWindowText("");
			c_doctor.SetFocus();
		}
		recSet->Close();


	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox(strSql);
		return;
	}
}

void CHuaJia::OnSetfocusEditDoctor() 
{
	c_doctor.SetWindowText(m_strDoctorBm);	
}

void CHuaJia::OnOK()  //ҩƷ����
{
	CString str1,strSql,str_onok[20];
	long row=0,x(0),y(0);
	double medMoney(0.0),zlMoney(0.0),profit(0.0);
	UpdateData();
	if(m_strDoctorBm.IsEmpty() ){
		AfxMessageBox("��ѡ������ҽ��...");
		c_doctor.SetFocus();
		return;
	}
	c_type.GetWindowText(str1);
	c_doctor.GetWindowText(str_onok[0]); //ҽ����
	c_danjuhao.GetWindowText(str_onok[1]);//���ݺ�
	try{
		HospitalConnect->BeginTrans();
	/*	������Ա��10/21�����ϸո�ע�͵���,��Ϊ�����շ�,���۷���һ��,����ȫ����һ�ַ�ʽ��

		if(str1 == "������Ա"){ //ֱ�Ӵ��ʻ��п۳�,ע�����

			for(row=1;row<m_grid.GetRows()-1; row++)
			{
				str[2]=m_grid.GetTextMatrix(row,0);//ID
				str[3]=m_grid.GetTextMatrix(row,10);//�ۼ�
				str[4]=m_grid.GetTextMatrix(row,13);//ȡҩ��
				str[5]=m_grid.GetTextMatrix(row,1);//ypbm
				str[6]=m_grid.GetTextMatrix(row,5);//product date
				str[7]=m_grid.GetTextMatrix(row,6);//effiect date
				str[8]=m_grid.GetTextMatrix(row,8);//����
				str[9]=m_grid.GetTextMatrix(row,11);//����
		
				strSql.Format("insert into ITEMTI (ID,SL,DJ,RIQI,DANJUHAO,KFBM,YPBM,\
					RQ1,RQ2,factory) values(%s,%.2f,%.2f,to_date('%s','yyyy-mm-dd'),'%s','%s',\
					'%s',to_date('%s','yyyy-mm-dd'),to_date('%s','yyyy-mm-dd'),'%s' )",\
					str[2],atof(str[4]),atof(str[3]),str2[4] ,str[1],LoginInformation.kfbm,str[5],\
					str[6],str[7] ,str[8]);
				medMoney+=atof(str[4])*atof(str[3]);//���ۼ۸�
				
				profit+=atof(str[9])*atof(str[4]);//������
			
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			}
		
			for(row=1;row<m_grid2.GetRows()-1;row++)
			{
				str[2]=m_grid2.GetTextMatrix(row,0);//iD
				str[3]=m_grid2.GetTextMatrix(row,2);//dj
				
				strSql.Format("insert into ItemRegisterTiZL (ZLMC,dj,danjuhao ) values(\
					'%s',%.2f,'%s' )",str[2],atof(str[3]),str[1]);
				zlMoney+=atof(str[3]);
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);


			}

			strSql.Format("update ITEMREGISTERTOU set DOCTOR='%s' ,DOCTORNAME='%s',\
				����Ա='%s',����Ա��='%s',KFBM='%s',�շ�Ա='%s',�շ�Ա��='%s', \
				profit=%.2f,MedMoney=%.2f,treateMoney=%.2f where DANJUHAO='%s' ",m_strDoctorBm,\
				str[0],LoginInformation.user_code,LoginInformation.user,LoginInformation.kfbm,\
				LoginInformation.user_code,LoginInformation.user,\
				medMoney-profit,medMoney,zlMoney,str[1]);
			
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
	
			
			
			
			
			
		}
		else {
	*/	
	
	
	//ITEMTI �е� DJ �ڻ����� ��ҩƷ���ۼ�,PDJ �ǽ�����, SELLDJ �ǹ��ұ�׼������
		strSql.Format("update ITEMREGISTERTOU set DOCTOR='%s' ,DOCTORNAME='%s',\
				����Ա='%s',����Ա��='%s',KFBM='%s' where DANJUHAO='%s' ",m_strDoctorBm,\
				str_onok[0],LoginInformation.user_code,LoginInformation.user,LoginInformation.kfbm,\
				str_onok[1]);
			
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
/*			{"ID","ҩƷ����","ҩƷ����","���","��λ","������","��Ч��",\
		"����BM","����","�����","�ۼ�","����","ָ����","ȡҩ��"}; //��14��
*/
		for(row=1;row<m_grid.GetRows()-1; row++)
		{
				str_onok[2]=m_grid.GetTextMatrix(row,0);//ID
				str_onok[3]=m_grid.GetTextMatrix(row,10);//�ۼ�
				str_onok[4]=m_grid.GetTextMatrix(row,13);//ȡҩ��
				str_onok[5]=m_grid.GetTextMatrix(row,1);//ypbm
				str_onok[6]=m_grid.GetTextMatrix(row,5);//product date
				str_onok[7]=m_grid.GetTextMatrix(row,6);//effiect date
				str_onok[8]=m_grid.GetTextMatrix(row,8);//����
		
				strSql.Format("insert into ITEMTI (ID,SL,DJ,RIQI,DANJUHAO,KFBM,YPBM,\
					RQ1,RQ2,factory,PDJ,SELLDJ) values(%s,%.2f,%.2f,to_date('%s','yyyy-mm-dd'),'%s','%s',\
					'%s',to_date('%s','yyyy-mm-dd'),to_date('%s','yyyy-mm-dd'),'%s' ,%.2f,%.2f)",\
					str_onok[2],atof(str_onok[4]),atof(str_onok[3]),str2[4] ,str_onok[1],LoginInformation.kfbm,str_onok[5],\
					str_onok[6],str_onok[7] ,str_onok[8],atof(m_grid.GetTextMatrix(row,11)),atof(m_grid.GetTextMatrix(row,12)));
			 //�ڹҺŻ����� PDJ Ϊ������ SELLDJ Ϊָ����
			//������תΪʱ SELLDJ Ϊ����,PDJ Ϊָ����
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			}
		
			for(row=1;row<m_grid2.GetRows()-1;row++)
			{
				str_onok[2]=m_grid2.GetTextMatrix(row,0);//iD
				str_onok[3]=m_grid2.GetTextMatrix(row,2);//dj
				
				strSql.Format("insert into ItemRegisterTiZL (ZLMC,dj,danjuhao ) values(\
					'%s',%.2f,'%s' )",str_onok[2],atof(str_onok[3]),str_onok[1]);
				
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);


			}


//		}
		
		HospitalConnect->CommitTrans();
	
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		AfxMessageBox("����ҩƷ����...");
		HospitalConnect->RollbackTrans();
		return;
	}
	GetDlgItem(IDOK)->EnableWindow(false);

}

BOOL CHuaJia::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){
		if(GetFocus()->m_hWnd==GetDlgItem(IDC_MSHFLEXGRID1)->m_hWnd){
			OnDblClickMshflexgrid1() ;
			return true;
		}
		else if(GetFocus()->m_hWnd == GetDlgItem(IDC_EDIT_MEDNAME)->m_hWnd){
			CRect r1;
			GetDlgItem(IDC_EDIT_MEDNAME)->GetWindowRect(r1);
		//	ScreenToClient(r1);

			CMedStockList medlist;
			medlist.r1=r1;

			theApp.pParentGrid.pGrid=&m_grid;
			if(medlist.DoModal() == IDOK){
				c_medname.SetWindowText(m_grid.GetTextMatrix(m_grid.GetRows()-2,2));//ҩƷ��
				c_medgg.SetWindowText(m_grid.GetTextMatrix(m_grid.GetRows()-2,3));//ҩƷ���

				ComputerFee();
				GetDlgItem(IDC_EDIT_MED_NUM)->SetFocus();
			}

			return true;


		}else if(GetFocus()->m_hWnd == GetDlgItem(IDC_EDIT_MED_NUM)->m_hWnd){
			GetDlgItem(IDC_EDIT_MEDNAME)->SetFocus();			
			return true;

		}

		else if(GetFocus()->m_hWnd == GetDlgItem(IDC_MSHFLEXGRID2)->m_hWnd) {
			OnDblClickMshflexgrid2();
			return true;
		
		}
		else if(GetFocus()->m_hWnd == edit2.m_hWnd ){
		
			CString str1;
			edit2.GetWindowText(str1);
			double	dX=atof(str1);
			str1.Format("%.2f",dX);
			m_grid2.SetTextMatrix(m_grid2.GetRow(),2,str1);
			
			if(m_grid2.GetRow() < m_grid2.GetRows()-2){
				m_grid2.SetRow(m_grid2.GetRow()+1);
				OnClickMshflexgrid2();
					
			}else edit2.ShowWindow(SW_HIDE);
		
			return true;

		


		}
		else if(GetFocus()->m_hWnd == editCtrl.m_hWnd ) {
			CString str1;
			double flSL;
			
			editCtrl.GetWindowText(str1);
			
			flSL=atof(str1);
			
			if(flSL > atof(m_grid.GetTextMatrix(editRow,9))){ //�����
				
			//	AfxMessageBox("��ȡ��ҩƷ�������ڿ����...");
				//	editCtrl.SetFocus();
				editCtrl.SetWindowText("");
				return true ;
			}
			
			str1.Format("%.2f",flSL);
			
			m_grid.SetTextMatrix(editRow,13,str1); //��ȡ��
			
			
			//	editCtrl.SetWindowText("");
			editCtrl.ShowWindow(SW_HIDE);
			
			if(m_grid.GetRow() < m_grid.GetRows()-2){
				m_grid.SetRow(m_grid.GetRow()+1);
				OnClickMshflexgrid1();
					
			}
			return true;
		
			//return CDialog::PreTranslateMessage(pMsg);
		}
		else
		{
			pMsg->wParam=VK_TAB;
			CDialog::PreTranslateMessage(pMsg);
		}
		
		
	}
	if(pMsg->message==WM_RBUTTONUP && GetFocus()->m_hWnd == GetDlgItem(IDC_MSHFLEXGRID1)->m_hWnd )
	{
		if( m_grid.GetRow() >= m_grid.GetRows()-1)return true;
		m_grid.RemoveItem(m_grid.GetRow());
		ComputerFee();
		return true;

	}
	if(pMsg->message==WM_RBUTTONUP && GetFocus()->m_hWnd == GetDlgItem(IDC_MSHFLEXGRID2)->m_hWnd )
	{
		if( m_grid2.GetRow() >= m_grid2.GetRows()-1)return true;
		m_grid2.RemoveItem(m_grid2.GetRow());
		ComputerFee();
		return true;

	}
	/*
	GetNextDlgTabItem(GetFocus())->SetFocus();
	((CEdit*)GetFocus())->SetSel(0,((CEdit*)GetFocus())->LineLength(-1));
	*/
// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}

BEGIN_EVENTSINK_MAP(CHuaJia, CDialog)
    //{{AFX_EVENTSINK_MAP(CHuaJia)
	ON_EVENT(CHuaJia, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CHuaJia, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CHuaJia, IDC_MSHFLEXGRID2, -601 /* DblClick */, OnDblClickMshflexgrid2, VTS_NONE)
	ON_EVENT(CHuaJia, IDC_MSHFLEXGRID2, -600 /* Click */, OnClickMshflexgrid2, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()
void CHuaJia::OnDblClickMshflexgrid1() 
{
/*	CMedStockList medlist;
	theApp.pParentGrid.pGrid=&m_grid;
	medlist.DoModal();
*/
}

void CHuaJia::OnClickMshflexgrid1() 
{
	if(m_grid.GetRow()==m_grid.GetRows()-1 || m_grid.GetCol() != 13)return; //��13Ϊȡҩ��

	CDC *pCdcGrid=m_grid.GetDC();
	int nWidth=pCdcGrid->GetDeviceCaps(LOGPIXELSX);
	int nHigh=pCdcGrid->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pCdcGrid);

	long    row=m_grid.GetRow();
	editRow=row;
	long 	col=m_grid.GetCol();
	CString str2;
	CString	strOrigin=m_grid.GetTextMatrix(row,col);

	long left=m_grid.GetCellLeft();
	long top=m_grid.GetCellTop();
	long right=m_grid.GetCellWidth();
	long bottom=m_grid.GetCellHeight();

	CRect rectGrid,r2;
	m_grid.GetWindowRect(rectGrid);
	ScreenToClient(rectGrid);
	rectGrid.left+=left*nWidth/1440;
	rectGrid.top+=top*nHigh/1440;
	rectGrid.right=right*nWidth/1440+rectGrid.left-1;
	rectGrid.bottom=bottom*nHigh/1440+rectGrid.top-1;

	editCtrl.MoveWindow(rectGrid);
	editCtrl.ShowWindow(SW_SHOW);
	editCtrl.SetFocus();
	editCtrl.SetWindowText(strOrigin);
	editCtrl.SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	editCtrl.SetSel(0,strOrigin.GetLength());
}

void CHuaJia::OnKillEditCtrl()
{
	CString str1;
	double flSL,price;

	editCtrl.GetWindowText(str1);

	flSL=atof(str1);
	
	if(flSL > atof(m_grid.GetTextMatrix(editRow,9))){ //�����
	
		AfxMessageBox("��ȡ��ҩƷ�������ڿ����...");
		editCtrl.SetWindowText("");
		editCtrl.SetFocus();
		return ;
	}
	price=atof(m_grid.GetTextMatrix(editRow,10) ) ;//���ۼ�

	str1.Format("%.2f",flSL);
	m_grid.SetTextMatrix(editRow,13,str1); //��ȡ��
	str1.Format("%.2f",flSL*price);
	m_grid.SetTextMatrix(editRow,14,str1); //���۶�

	editCtrl.SetWindowText("");
	editCtrl.ShowWindow(SW_HIDE);
	m_3.SetFocus();
	ComputerFee();
}

HBRUSH CHuaJia::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor==CTLCOLOR_EDIT)pDC->SetTextColor(RGB(255,0,0));	
	if(pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd){
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return theApp.titleBrush;


	}
	if(pWnd->m_hWnd == GetDlgItem(IDC_STATIC_PRICE)->m_hWnd)pDC->SetTextColor(RGB(255,0,0));
	if( pWnd->m_hWnd == GetDlgItem(IDC_EDIT_GH_HUAJIA)->m_hWnd )
		pDC->SetTextColor(RGB(255,0,0));
	if( pWnd->m_hWnd == GetDlgItem(IDC_EDIT_COUNT)->m_hWnd )
		pDC->SetTextColor(RGB(255,0,0));
	return hbr;
}

void CHuaJia::OnDblClickMshflexgrid2() 
{
	CCureList curelist;
	theApp.pParentGrid.pGrid=&m_grid2;
	curelist.DoModal();
	ComputerFee();
}

void CHuaJia::OnClickMshflexgrid2() 
{
	if(m_grid2.GetRow()==m_grid2.GetRows()-1 || m_grid2.GetCol() != 2)return; //��2Ϊ�۸�
	CDC *pCdcGrid=m_grid2.GetDC();
	int nWidth=pCdcGrid->GetDeviceCaps(LOGPIXELSX);
	int nHigh=pCdcGrid->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pCdcGrid);

	long	row=m_grid2.GetRow();
	long 	col=m_grid2.GetCol();
	CString str2;
	CString	strOrigin=m_grid2.GetTextMatrix(row,col);

	long left=m_grid2.GetCellLeft();
	long top=m_grid2.GetCellTop();
	long right=m_grid2.GetCellWidth();
	long bottom=m_grid2.GetCellHeight();

	CRect rectGrid,r2;
	m_grid2.GetWindowRect(rectGrid);
	ScreenToClient(rectGrid);
	rectGrid.left+=left*nWidth/1440;
	rectGrid.top+=top*nHigh/1440;
	rectGrid.right=right*nWidth/1440+rectGrid.left-1;
	rectGrid.bottom=bottom*nHigh/1440+rectGrid.top-1;


	edit2.MoveWindow(rectGrid);
	edit2.ShowWindow(SW_SHOW);
	edit2.SetFocus();
	edit2.SetWindowText(strOrigin);
	edit2.SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	edit2.SetSel(0,strOrigin.GetLength());	// TODO: Add your control notification handler code here
	
}

void CHuaJia::OnKillEdit2()
{
	CString str1;
	double dX;
	edit2.GetWindowText(str1);
	dX=atof(str1);
	str1.Format("%.2f",dX);
	m_grid2.SetTextMatrix(m_grid2.GetRow(),2,str1);
	m_grid2.SetWindowText("");

	edit2.ShowWindow(SW_HIDE);
	ComputerFee();
}
const char R1[]="��������";
const char RR[]="���䱣��";
const char IC[]="��������";
const char TUIYANG[]="������Ա";

void CHuaJia::OnChargePrice()  //�շ�
{
	const int SELL_PRICE_COL=10,GET_PRICE_COL=11,GET_MED_COL=13;
	const int ZL_PRICE_COL=2;

	if(m_strDoctorBm.IsEmpty() ){
		AfxMessageBox("��ѡ������ҽ��!!!!");
		c_doctor.SetFocus();
		return;
	}
	CString str[10];
	for(long row=1;row<m_grid.GetRows()-1; row++)
	{
		str[4]=m_grid.GetTextMatrix(row,13);//ȡҩ��
		if ( atof(str[4]) == 0 ){
			str[0].Format("���ֵ� %ld ��ҩƷȡҩ����Ϊ ��",row );
			AfxMessageBox(str[0]);
			return;
		}
	}

/////////////////////////ȡ��ԭ����ONOK()����//////////////////////
//	OnOK();
	
	CString str1,str_onok[20];
	long x(0),y(0);
	double medMoney(0.0),zlMoney(0.0),profit(0.0);
	UpdateData();
	c_type.GetWindowText(str1);
	c_doctor.GetWindowText(str_onok[0]); //ҽ����
	c_danjuhao.GetWindowText(str_onok[1]);//���ݺ�

/////////////////////ȡ��ԭ����ONOK()����/////////////////////////
//	c_type.GetWindowText(str1);

	CString strSql,s1;
	float fMed(0),fZl(0),fPro(0),fMZ,fgetPrice(0);//ҩƷ��,���Ʒ�,����,�ܷ���
	
	x2.GetWindowText(s1);
	fMed=atof(s1);

	
	fgetPrice=fMed-inPrice; //ҩƷ���� 

	x3.GetWindowText(s1);
	fZl=atof(s1);

	x5.GetWindowText(s1);
	fMZ=atof(s1);
	CString strx6;
	x6.GetWindowText(strx6); //�����Ǹ�������
	CString strResideSerial="AB"+COtherDecharge::GetStringTitle("SELECT RPAD(sys_context('USERENV','ip_address'),15,'.')||'.'||to_char(sysdate,'yyyymmddhh24miss')  from dual");
	try{ 
		HospitalConnect->BeginTrans();
//////////////////////////////////insert into onok//////////////////////////////	
	//ITEMTI �е� DJ �ڻ����� ��ҩƷ���ۼ�,PDJ �ǽ�����, SELLDJ �ǹ��ұ�׼������
		if( str2[3] == "סԺ��Ա" ){
			strSql.Format("INSERT INTO lsq_reside_hos_huajia (s1,s2,h1,n1,y1,y2,p1,p2,pr1,r1 ) values \
				('%s','%s','%s','%s','%s','%s',%.2f,%.2f,%.2f,sysdate ) ",str_onok[1],strResideSerial,\
				LoginInformation.user_code,LoginInformation.user,\
				m_strDoctorBm,str_onok[0],fMed,fZl,fgetPrice);
				str_onok[1]=strResideSerial;

		}
		else
			strSql.Format("update ITEMREGISTERTOU set DOCTOR='%s' ,DOCTORNAME='%s',\
				����Ա='%s',����Ա��='%s',KFBM='%s' where DANJUHAO='%s' ",m_strDoctorBm,\
				str_onok[0],LoginInformation.user_code,LoginInformation.user,LoginInformation.kfbm,\
				str_onok[1]);
			
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
/*			{"ID","ҩƷ����","ҩƷ����","���","��λ","������","��Ч��",\
		"����BM","����","�����","�ۼ�","����","ָ����","ȡҩ��"}; //��14��
*/
		for(row=1;row<m_grid.GetRows()-1; row++)
		{
				str_onok[2]=m_grid.GetTextMatrix(row,0);//ID
				str_onok[3]=m_grid.GetTextMatrix(row,10);//�ۼ�
				str_onok[4]=m_grid.GetTextMatrix(row,13);//ȡҩ��
				str_onok[5]=m_grid.GetTextMatrix(row,1);//ypbm
				str_onok[6]=m_grid.GetTextMatrix(row,5);//product date
				str_onok[7]=m_grid.GetTextMatrix(row,6);//effiect date
				str_onok[8]=m_grid.GetTextMatrix(row,8);//����
		
				strSql.Format("insert into ITEMTI (ID,SL,DJ,RIQI,DANJUHAO,KFBM,YPBM,\
					RQ1,RQ2,factory,PDJ,SELLDJ) values(%s,%.2f,%.2f,to_date('%s','yyyy-mm-dd'),'%s','%s',\
					'%s',to_date('%s','yyyy-mm-dd'),to_date('%s','yyyy-mm-dd'),'%s' ,%.2f,%.2f)",\
					str_onok[2],atof(str_onok[4]),atof(str_onok[3]),str2[4] ,str_onok[1],LoginInformation.kfbm,str_onok[5],\
					str_onok[6],str_onok[7] ,str_onok[8],atof(m_grid.GetTextMatrix(row,11)),atof(m_grid.GetTextMatrix(row,12)));
			 //�ڹҺŻ����� PDJ Ϊ������ SELLDJ Ϊָ����
			//������תΪʱ SELLDJ Ϊ����,PDJ Ϊָ����
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			}
		
			for(row=1;row<m_grid2.GetRows()-1;row++)
			{
				str_onok[2]=m_grid2.GetTextMatrix(row,0);//iD
				str_onok[3]=m_grid2.GetTextMatrix(row,2);//dj
				
				strSql.Format("insert into ItemRegisterTiZL (ZLMC,dj,danjuhao ) values(\
					'%s',%.2f,'%s' )",str_onok[2],atof(str_onok[3]),str_onok[1]);
				
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);


			}

		
//////////////////////////////////insert into onok//////////////////////////////	
		
		
		
		
		if(str2[3] == R1 || str2[3] == RR ){
		
			if(str2[3] == R1 ){ //��������
				if( atof(strx6) <= 0 )strSql.Format("UPDATE codeqingshu SET YUER= 0.0 ,ds1=( SELECT sys_context('USERENV','ip_address')||'.'|| to_char(sysdate,'hh24yyyymimmssdd')||'RELMED' from dual ),d1=sysdate  WHERE BM='%s' ",str2[2] );
				else strSql.Format("UPDATE codeqingshu SET YUER= YUER-(%.2f) ,ds1=( SELECT sys_context('USERENV','ip_address')||'.'|| to_char(sysdate,'hh24yyyymimmssdd')||'RELMED' from dual ),d1=sysdate WHERE BM='%s' ",fMZ,str2[2] );
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			}
			else if( str2[3] == RR ){ //ְ������
				if( atof(strx6) <= 0 )strSql.Format("UPDATE ְ����������� SET �����=0.00,ds1=( SELECT sys_context('USERENV','ip_address')||'.'|| to_char(sysdate,'hh24yyyymimmssdd') ||'EMPMED' from dual ),d1=sysdate WHERE ����='%s' ",str2[2] );
				else strSql.Format("UPDATE ְ����������� SET �����=�����-(%.2f),ds1=( SELECT sys_context('USERENV','ip_address')||'.'|| to_char(sysdate,'hh24yyyymimmssdd') ||'EMPMED' from dual ),d1=sysdate WHERE ����='%s' ",fMZ,str2[2] );
				HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			}
			
			strSql.Format("UPDATE ItemRegisterTou SET MEDMONEY=%.2f,TREATEMONEY=%.2f,�շ�Ա='%s',\
				�շ�Ա��='%s',PROFIT=%.2f,cash=%.2f WHERE DANJUHAO='%s' ",fMed,fZl,LoginInformation.user_code,\
				LoginInformation.user ,fgetPrice,atof(strx6)< 0 ? -atof(strx6):0,str2[5] );
		
		}
		else if ( str2[3] == "�ض�����" || str2[3] == IC )
		{
			if( str2[3]== "�ض�����" ) {
				CString s01,s02,s03;
				GetDlgItem(IDC_EDIT_X8)->GetWindowText(s01); // ����ǰ�Ϲ���
				GetDlgItem(IDC_EDIT_X9)->GetWindowText(s02); //����Ա����
				GetDlgItem(IDC_EDIT_X5)->GetWindowText(s03); //IC ��

		    	strSql.Format("UPDATE ItemRegisterTou SET MEDMONEY=%.2f,TREATEMONEY=%.2f,�շ�Ա='%s',\
				�շ�Ա��='%s',PROFIT=%.2f,cash=%.2f,p1=%.2f,p2=%.2f,p3=%.2f WHERE DANJUHAO='%s' ",fMed,fZl,LoginInformation.user_code,\
				LoginInformation.user ,fgetPrice,atof(strx6),atof(s01),atof(s02),atof(s03),str2[5] );
				

			}
			else
		    	strSql.Format("UPDATE ItemRegisterTou SET MEDMONEY=%.2f,TREATEMONEY=%.2f,�շ�Ա='%s',\
				�շ�Ա��='%s',PROFIT=%.2f,cash=%.2f WHERE DANJUHAO='%s' ",fMed,fZl,LoginInformation.user_code,\
				LoginInformation.user ,fgetPrice,atof(strx6),str2[5] );

		}
		else if ( str2[3]== "סԺ��Ա" )
		{
			strSql.Format("UPDATE lsq_reside_hos SET price=price-(%.2f) WHERE serial='%s' ",fMZ,str2[5] );


		}
		else
		{

			strSql.Format("UPDATE ItemRegisterTou SET MEDMONEY=%.2f,TREATEMONEY=%.2f,�շ�Ա='%s',\
				�շ�Ա��='%s',PROFIT=%.2f,CASH=%.2f WHERE DANJUHAO='%s' ",fMed,fZl,LoginInformation.user_code,\
				LoginInformation.user ,fgetPrice,fMZ,str2[5] );


		}
	
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		HospitalConnect->CommitTrans();
		

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		AfxMessageBox("�����շѳ���,�����»����շ�!!!");
		HospitalConnect->RollbackTrans();
		return;
	}


	CDialog::OnOK();
}

void CHuaJia::OnKillfocusEditMedNum() //�����Ƿ񳬳������
{
	CString str1,strtemp;
	c_mednum.GetWindowText(str1);
	str1.Format("%.2f",atof(str1));
	long r=0;
	r=m_grid.GetRows();
	double price;
	if(r>2){
		strtemp=m_grid.GetTextMatrix(r-2,9);//�����
		if( atof(str1) > atof(strtemp) ) {
			AfxMessageBox("�����ҩƷ�������ڿ����!!!����������");
			c_mednum.SetSel(0,c_mednum.LineLength(-1));
			c_mednum.SetFocus();
			return;
		}
		m_grid.SetTextMatrix(r-2,13,str1);

		price=atof(m_grid.GetTextMatrix(r-2,10) );//���ۼ�
		strtemp.Format("%.2f",price*atof(str1) );
		m_grid.SetTextMatrix(r-2,14,strtemp); //���۶�

	}
	ComputerFee();

	c_medname.SetWindowText("");
	c_medgg.SetWindowText("");

}

void CHuaJia::OnSetfocusEditMedNum() 
{
		// TODO: Add your control notification handler code here
	c_mednum.SetWindowText("1.00");
	c_mednum.SetSel(0,c_mednum.LineLength(-1));
	
}

const char NOWORK[]="������Ա";
const char GAOQIAN[]="����ǰ�Ϲ���";
const char GANGSHANG[]="������Ա";
//		if( strGhtype == "��ǰְ��" ) strGhtype="����ǰ�Ϲ���";

void CHuaJia::ComputerFee()
{
	const int SELL_PRICE_COL=10,GET_PRICE_COL=11,GET_MED_COL=13;
	const int ZL_PRICE_COL=2;
	double db1,db2;
	CString str11,str222;
	
	
	float medPrice(0),zlPrice(0);
	theApp.pParentGrid.p3=this; //p2�Ѿ���ҩƷ�б�ʹ��,�벻Ҫ��ʹ��
	inPrice=0;
	for(int i=1;i<m_grid.GetRows()-1;i++){
		medPrice+=atof(m_grid.GetTextMatrix(i,SELL_PRICE_COL))*atof(m_grid.GetTextMatrix(i,GET_MED_COL));
		inPrice+=atof(m_grid.GetTextMatrix(i,GET_PRICE_COL))*atof(m_grid.GetTextMatrix(i,GET_MED_COL));


	}
	for(i=1;i<m_grid2.GetRows()-1;i++){
		zlPrice+=atof(m_grid2.GetTextMatrix(i,ZL_PRICE_COL));

	}
	
	CString str1,str22,str3,str0;
	str0.Format("%.2f",medPrice);
	str1.Format("%.2f",zlPrice);
	str22.Format("%.2f",medPrice+zlPrice);
			 //ҩƷ���ۺϼ�,���ڼ�������
	
	x2.SetWindowText(str0); //ҩƷ��
	x3.SetWindowText(str1); //���Ʒ�
	x7.SetWindowText(str22); //�ܷ���
	if( str2[3]== "�ض�����" ) {
		CString  sx1,sx2,sx3,sx4;
		GetDlgItem(IDC_EDIT_X1)->GetWindowText(sx1); //ͳ��
		GetDlgItem(IDC_EDIT_X5)->GetWindowText(sx2); //IC
		GetDlgItem(IDC_EDIT_X8)->GetWindowText(sx3); //����ǰ�Ϲ���
		GetDlgItem(IDC_EDIT_X9)->GetWindowText(sx4); //����Ա����
		double dx1;
		dx1=atof(str22) -( atof(sx1)+atof(sx2)+atof(sx3)+atof(sx4) );
		sx1.Format("%.2f",dx1);
		x6.SetWindowText(sx1 ); //�ֽ�֧��



	goto END;
	}

	if( str2[3] == TUIYANG ) str0.Format("%.2f",(medPrice+zlPrice)*0.1); //������Ա90%�ۿ�
	else if( str2[3] == NOWORK ) str0.Format("%.2f",0);
	else if( str2[3] == GAOQIAN ) str0.Format("%.2f",0);
	else if( str2[3] == GANGSHANG ) str0.Format("%.2f",0);
	else if( str2[3] == IC ) str0.Format("%.2f",medPrice+zlPrice);
	else	str0.Format("%.2f",(medPrice+zlPrice)*scale);

	x5.SetWindowText(str0);//ʵ�շ�


	if( str2[3] == TUIYANG ) str0.Format("%.2f",balance-(medPrice+zlPrice)*0.1); //������Ա90%�ۿ�
	else if( str2[3] == NOWORK ) str0.Format("%.2f",0);
	else if( str2[3] == GAOQIAN ) str0.Format("%.2f",0);
	else if( str2[3] == GANGSHANG ) str0.Format("%.2f",0);
	else if( str2[3] == IC || str2[3] == "�ض�����" ){

		x5.GetWindowText(str11);//ʵ�շ�
		x1.GetWindowText(str222);//ͳ֧��
		db1=atof(str11);
		db2=atof(str222);
		str0.Format("%.2f",db1-db2 );
		
	}
	else str0.Format("%.2f",balance-(medPrice+zlPrice)*scale);

	x6.SetWindowText(str0);

	if( ( ( balance-(medPrice+zlPrice) ) < 0 && ( str2[3].Compare("���䱣��")==0 || str2[3].Compare("��������")==0 ) ) || str2[3]=="�ض�����"   ){
		GetDlgItem(IDC_STATIC_X8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_X9)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_X8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_X9)->ShowWindow(SW_SHOW);

	}
	else{
		GetDlgItem(IDC_STATIC_X8)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_X9)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_X8)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_X9)->ShowWindow(SW_HIDE);

	}
END:
	ComputeRows();
}

void CHuaJia::OnChangeEditX1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString str1;
	x1.GetWindowText(str1);
	balance=atof(str1);
	
	ComputerFee();
}

void CHuaJia::SetGridHead()
{
	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"ID","ҩƷ����","ҩƷ����","���","��λ","������","��Ч��",\
		"����BM","����","�����","���ۼ�","����","ָ����","ȡҩ��","���ö�"}; //��14��+1
	long  headWidth[]={0,00,2000,1600,600,0,1400,0,1600,1000,1000,0,0,1200,1200};


	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	

	m_grid2.SetRows(2);
	m_grid2.Clear();
	CString HeadTitle2[]={"ID","��������","���Ʒ���"};
	long  headWidth2[]={0,2000,1200,600,0,1400,0,1600,1000,1000,0,0};


	m_grid2.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid2.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid2.SetCols(sizeof(HeadTitle2)/sizeof(CString));
	m_grid2.SetFixedCols(0);
	i=0;
	for(count=0;count<sizeof(HeadTitle2)/sizeof(CString);count++){
		m_grid2.SetColWidth(i,headWidth2[count]);
		m_grid2.SetTextArray(i++,HeadTitle2[count]);
	}	
	
}

void CHuaJia::OnRollmed() 
{
	theApp.pParentGrid.pGrid=&m_grid;
	CMedCodeQuery med;
	med.FlagRollMED=8888; //��Ϊ��ҩ��־
	med.DoModal();
	
}
//	CString HeadTitle[]={"���","����","BM","�Һ�����","����","���к�"};
extern _Application app;
extern Workbooks books;
extern _Workbook book;
extern Worksheets sheets;
extern _Worksheet sheet;
extern COleVariant vOpt;
void CHuaJia::OnPrint() 
{
#define _O(x) COleVariant(x)

	BeginWaitCursor();

	CString strFileName;
	strFileName.Format("%s",LoginInformation.path);
	strFileName+=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_upgrade WHERE ds2='HUAJIA_PRINT_FILE' ");

	if( str2[3] == "��������" || str2[3] == "�ض�����" || str2[3] == "����ͳ��" || str2[3]=="��ͥ����" ){
		AfxMessageBox("����������Ա��ֹ��ӡ");	
		return; //�������ս�ֹ�û���ӡ
	}

	app.CreateDispatch("excel.application");
	if(!app){
		AfxMessageBox("��ע��ϵͳ�б���װ��EXCEL97 ���� EXCEL2000 ,����˹��ܲ���ʹ��...");
		return;
	}
	books=app.GetWorkbooks();
	book=books.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	sheets=book.GetWorksheets();

	sheet=sheets.GetItem(_O("MED_Origin_DATA")); //����ָ��sheet�����Ż�sheet��

	
	Range vRange;
	app.SetVisible(false); //��ʾ

//* EXCEL ��һ������˳��Ϊ ҩƷ���� ������Ŀ���� �շ�Ա 
	const int START_RECORD=2;
	int iUseCol[]={2,3,4,13,10 };  //*ҩƷҪ�������
	int iUseCol2[]={1,2 };          //* ������ĿҪ�������
	int y,x;
	int iMedRows=m_grid.GetRows()-2; //ҩƷ����
	int iZlRows=m_grid2.GetRows()-2; //������Ŀ����
	CString strMedtmp;
	CString strInsert[20]; //* �ֱ��������Ҫ����Ϣ
	
	for ( x=0; x< iMedRows  ; x++)    //* ҩƷԭʼ��Ϣ���
	{
		for(  y=0; y < sizeof(iUseCol) /sizeof(int) ; y++)
		{
			SetExcelCell(sheet,x+START_RECORD,y,m_grid.GetTextMatrix(x+1,iUseCol[y]));
		}
	}

	for ( x=0 ; x < iZlRows; x++ )  //* ���Ʒ���Ϣ���
	{
		for( y=0 ; y < sizeof(iUseCol2)/ sizeof(int) ; y ++)
		{
			SetExcelCell(sheet,x+START_RECORD+iMedRows,y,m_grid2.GetTextMatrix(x+1,iUseCol2[y]));
	
		}
	}

	x=0;
	strMedtmp.Format("%ld",iMedRows); 
	strInsert[x++]=strMedtmp;				//* ҩƷ���� 0
	strMedtmp.Format("%ld",iZlRows);
	strInsert[x++]=strMedtmp;				//* �������� 1
	strInsert[x++]=str2[1];					//* �������� 2
	strInsert[x++]=LoginInformation.user;	//* �շ�Ա�� 3
	strInsert[x++]=str2[3];					//* ��Ա��� 4   �� ������\���䱣��
	c_danjuhao.GetWindowText(strMedtmp);
	strInsert[x++]=strMedtmp;				//* �Һŵ��� 5
	x7.GetWindowText(strMedtmp);
	strInsert[x++]=strMedtmp;				//* �ܽ��   6
	strInsert[x++]=GetChinesePrice(strMedtmp); //* �ܽ���д 7
	x2.GetWindowText(strMedtmp);
	strInsert[x++]=strMedtmp;				//* ҩƷ��  8
	x3.GetWindowText(strMedtmp);		
	strInsert[x++]=strMedtmp;				//*�����Ʒ�  9
	
//* �������� ���䱣�� �������� �����ʻ�����,����ʹ���ֽ�
//* ������ ��ȫ���ֽ�
//* ������Ա ����ǰ�Ϲ��� ������Ա �����ֽ�
//* ������Ա �ֽ�Ϊ����10%
//* ����ͳ����������Ӧ��һ��
//* X2 ҩƷ�� x1 ���
//* x3 ���Ʒ� x5 ʵ��
//* x7 �ܷ��� x6 ����
//* x8 ����	��x9 ���㡡�������ʻ�����ʱ
	CString strType;
    if(str2[3] == R1 || str2[3] == RR   ){  
		x1.GetWindowText(strMedtmp); // �ʻ����
		if( atof(strMedtmp) <= 0.00) strMedtmp="0.00";
	}
	else if( str2[3] == "������" ){
		strMedtmp="0.00" ; //�ܷ��ü��û��ֽ�
	}
	else if( str2[3] == "������Ա" ){
		x1.GetWindowText(strMedtmp); //������Ա
	}
	else 
		strMedtmp="0.00";

	strInsert[x++]=strMedtmp;  //�ʻ���� 10

    if(str2[3] == R1 || str2[3] == RR   ){  
		x6.GetWindowText(strMedtmp); // �ֽ�,ӦΪ����,���ʻ�����֧��
		if( atof( strMedtmp) >= 0.00 ) strMedtmp="0.00";
		else {
			strFileName.Format("%.2f",fabs(atof(strMedtmp)) ); //ȡ����
			strMedtmp=strFileName;
		}
	
	}
	else if( str2[3] == "������" || str2[3]== "������Ա" ){
		x5.GetWindowText(strMedtmp) ; //�ܷ��ü��û��ֽ�
	} 
	else strMedtmp="0.00";
	
	strInsert[x++]=strMedtmp;  //�ֽ�  11


    if(str2[3] == R1 || str2[3] == RR || str2[3] == "������Ա"  ){  
		x6.GetWindowText(strMedtmp);
		if( atof( strMedtmp ) <=0.00 ) strMedtmp="0.00";
	}else
		strMedtmp="0.00";

	strInsert[x++]=strMedtmp;				//* ���λ���  12

	for ( y=0 ; y < x ; y++)
		SetExcelCell(sheet,1,y,strInsert[y]);  //��EXCEL�ĵڶ��е�һ�п�ʼ���,


/*	
//H54 �����ֽ�����
	CString b1;

	/*
	const char R1[]="��������";
const char RR[]="���䱣��";
const char IC[]="��������";
const char TUIYANG[]="������Ա";

	x6.GetWindowText(b1); //�����Ǹ�������
	CString strCash;
	vRange=sheet.GetRange(_O("H54"),_O("H54")); //���λ���
	font=vRange.GetFont();
	font.SetName(_O(FONTNAME));
	font.SetSize(_O((short)STANDARDFONT));
	
	if(str2[3] == R1 || str2[3] == RR || str2[3] == IC ){
		if( atof(b1) < 0 ) {
			strCash.Format("�ֽ�����: %.2f",-atof(b1));
		}
		else{
			strCash.Format("�ֽ�����: 0.00");
		}
		vRange.SetValue(COleVariant(strCash));

	}
	else {
		x5.GetWindowText(b1);
		strCash.Format("�ֽ�����: %.2f",atof(b1));
		vRange.SetValue(COleVariant(strCash));

	}

*/	
	app.Run(COleVariant("thisWorkBook.Print_Invoice"),vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
		vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
		vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt );  //����excel��thisworkbook.print_invoice��
	
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	app.DetachDispatch();

	EndWaitCursor();
	
}

CString CHuaJia::GetChinesePrice(CString strPrice) //strPriceΪ��׼�Ķ�λС����ʽ,�����λ  
{
	return GetBigMoney(atof(strPrice) );
/*	CString strPRC[]={"��","Ҽ","��","��","��","��","½","��","��","��"};
	CString strBIT[]={"Ԫ","ʰ","��","Ǫ","��","��"};
	CString str[30];
	char charPre='1';
	int m=0;
	if(strPrice=="0.00")return "��Ԫ��";
	CString strInteger,strFloat,strINT="",strFLOAT="",strOut="",str1,str2;

	strInteger=strPrice.Left(strPrice.GetLength()-3); //ȡ��������
	strFloat=strPrice.Right(2);//С������
	
	if(strInteger[0] == '-'){
		strOut="��";
		strInteger=strInteger.Right(strInteger.GetLength()-1);
	}
//����������д����
	BOOL flag=0;
	for(int i=0;i<strInteger.GetLength();i++){
		if(strInteger[i]=='0'&&flag==0){
			if(i==strInteger.GetLength()-1){
				strINT+="Ԫ";continue;
			}
			flag=1;
			continue;
		}
		if(strInteger[i]=='0'&&strInteger[i-1]=='0')continue;
		if(flag==1)strINT+="��";
		strINT+=strPRC[strInteger[i]-0x30];//ȡ�ô�д����
		strINT+=strBIT[strInteger.GetLength()-i-1];//�õ���д����
		flag=0;
	}
	if(flag)strINT+="Ԫ";
		
//����С������
	if(strInteger[0]=='0')
	{
		strINT=""; //��ֹ����Ϊ��
		str1="";
	}
	else str1="��";

	if(strFloat=="00"){
		strFLOAT="";
		return strOut+strINT+"��";
	}//С��Ϊ��
	if(strFloat[0]=='0'){
		strFLOAT=strPRC[strFloat[1]-0x30]+"��";
		return strOut+strINT+str1+strFLOAT;

	}
	if(strFloat[1]=='0'){
		strFLOAT=strPRC[strFloat[0]-0x30]+"��"+"��";
		if(strInteger[strInteger.GetLength()-1]=='0')
			return strOut+strINT+str1+strFLOAT;
		return strOut+strINT+strFLOAT;
	}
	strFLOAT=strPRC[strFloat[0]-0x30]+"��"+strPRC[strFloat[1]-0x30]+"��";
	if(strInteger[strInteger.GetLength()-1]=='0')
		return strOut+strINT+str1+strFLOAT;
	return strOut+strINT+strFLOAT;
*/

}

void CHuaJia::OnChangeEditX8()  //�ʻ�����ʱ�Զ�����ְ��Ӧ��������
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if( str2[3]== "�ض�����" ) {
		ComputerFee();
		return;
	}
	CString strx8,strx6;
	double dx8,dx6;
	GetDlgItem(IDC_EDIT_X8)->GetWindowText(strx8);
	GetDlgItem(IDC_EDIT_X6)->GetWindowText(strx6);
	
	dx8=atof(strx8);
	dx6=atof(strx6);
	strx8.Format("%.2f",dx8+dx6); //������û�����������ȥ�û��������ĵ�(����)
	GetDlgItem(IDC_EDIT_X9)->SetWindowText(strx8);
}



void CHuaJia::OnDestroy() 
{
	CDialog::OnDestroy();
	CString strSql;
	try{
		HospitalConnect->BeginTrans();
		strSql.Format("DELETE FROM lsq_share WHERE serial='%s' ",str2[5] );
	
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		
		HospitalConnect->CommitTrans();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("����ϵͳ�Դ���,����ϵϵͳ������Ա...");
		HospitalConnect->RollbackTrans();
		return;
	}
	
}

void CHuaJia::ComputeRows()
{
	CString str1;
	str1.Format("%ld��",m_grid.GetRows()-2 );
	GetDlgItem(IDC_EDIT_COUNT)->SetWindowText(str1);
}

CString CHuaJia::GetBigMoney(double dMoney)
{
     CString strMoney;

     strMoney.Format ("%.2f" , dMoney);

	 if( strMoney.GetLength() >15 ){
		 
		 return "��"+strMoney; //��ֵ̫��
	 }

     CString strUnit = "Ԫʰ��Ǫ��ʰ��Ǫ��ʰ��Ǫ";

     CString strNumber = "��Ҽ��������½��ƾ�";

     CString strOtherUnit = "���Ƿ�";

 

     //�����ַ�����������С�����ݴ���

     int nPos = strMoney.Find (".");

     int nLength = strMoney.GetLength ();

     if(nPos < 0)

         nPos = nLength;

     CString strReturnValue;

     int nCount = 0;

     bool bZero = false;

     bool bNeedLevel = false;    //�Զε�ʶ�������Ƿ���Ҫ���ֶ��������ڣ����

     //���������ݽ��з���ʶ����

     for(int i = nPos - 1;i >= 0;i --)

     {

         TCHAR ch = strMoney.GetAt (i);

         if(nCount % 4 == 0 && nCount > 0)

         {

               //������������Ϊ����λ���򣩣���ڰ�λ���ڣ��ȣ���Ҫ���ö�

              bNeedLevel = true;

         }

         if(ch == '0')

         {

               //ֻ��ʰ��Ǫλ�ģ�����ʶ����Ҫ���ǵ�ʰ�������ԣ����磱����Ҽʰ�������Ҽʰ��

              if(nCount % 4 != 0)

                   bZero = true;

         }

         else

         {

              CString strTemp(strReturnValue);

              strReturnValue = strNumber.Mid ((ch - 0x30) * 2 , 2);

              if(nCount > 0)

              {

                  strReturnValue += strUnit.Mid (nCount * 2 , 2);

                   if(nCount % 4 != 0 && bNeedLevel)

                   {

                         //�����ж��Ƿ���Ҫ�������������ڵ�

                       strReturnValue += strUnit.Mid (int(nCount / 4) * 8 , 2);

                   }

                   bNeedLevel = false;

              }

              if(bZero)

              {

                   //ֻ�бȵ�ǰ�����λҪ���������ֲŲ���

                   if(!strTemp.IsEmpty ())

                       strReturnValue += strNumber.Left (2);

                   bZero = false;

              }

              strReturnValue += strTemp;

         }

         nCount ++;

     }

     strReturnValue += strUnit.Left (2);
	 if(strReturnValue.GetLength()<=2) strReturnValue="";
	 //��ֹ��������Ϊ��

     bool bAllZero = true;

     //����ʵ�ֶ�С�������Ĵ���

     //���ж��Ƿ�Ϊȫ�㣬����Ҫ������

     if(nPos < nLength)

     {

         if(nLength > 2)

              nLength = 2;

         for(int i = 0;i < nLength;i ++)

              if(strMoney.GetAt (nPos + i + 1) != '0')

                   bAllZero = false;

     }

     if(bAllZero)

     {

         strReturnValue += strOtherUnit.Left (2);

     }

     else

     {

          //�ԷֽǵĴ���

         for(int i = 0;i < nLength;i ++)

         {

              TCHAR ch = strMoney.GetAt (nPos + 1 + i);

              if(ch == '0' && i > 0)

              {

              }

              else

              {

                   strReturnValue += strNumber.Mid ((ch - 0x30) * 2 , 2);

                   if(ch != '0')

                       strReturnValue += strOtherUnit.Mid ((i + 1) * 2 , 2);

              }

         }

     }

     return strReturnValue;
}

void CHuaJia::SetExcelCell(_Worksheet &sheetx,int iRow, int iCol, CString &strData)
{
	/* ����EXCEL��Ԫ���ַ��� 
		sheetx  Ҫ�����Ĺ�����
		iRow	Ҫ�������������ڵ���
		iCol	Ҫ�����Ĺ�����������
		strData Ҫд����ַ���
	*/
	
	CString strCell;
	Range vRange;
	strCell.Format("%c%d",iCol+'A',iRow+1);
	vRange=sheetx.GetRange(_O(strCell),_O(strCell));
	vRange.SetValue(_O(strData));

}

void CHuaJia::OnChangeEditX9() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if( str2[3]== "�ض�����" ) {
		ComputerFee();
		return;
	}
	
}

void CHuaJia::OnChangeEditX5() 
{
	if( str2[3]== "�ض�����" ) {
		ComputerFee();
		return;
	}
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
