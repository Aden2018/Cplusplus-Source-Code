// Gh.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "Gh.h"
#include "EmployeeQuery.h"
#include "employeeNoworkQuery.h"
#include "otherSickQuery.h"
#include "employeeRelateQuery.h"
#include "baseRyAdd.h"
#include "BasisInsureList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGh dialog
//////////////////////////////////////////////////////////////////////////////////////
//		�޸ļ�¼:
//			����:������							2005-02-26 10:00			
//------------------------------------------------------------------------------------
//			���Һ��д���ְ������(��ְ,����ǰ����,����������),�����Ժ�ͳ��
//		����ԭ����ѯ��( ��� not in ('����','����') )������( ���='�α�')
//		������ͬ,�����Ը���SQL��ѯ����,�� CGh������һpublic CString strWorkType
//		����,��Ϊ��¼ְ��������.
//------------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////

const char EMPLOYEE[]="���䱣��";
const char GENERIC[]="������";
const char RELATE[]="��������";
const char NOWORK[]="������Ա";
const char IC[]="��������";

const char GAOQIAN[]="��ǰְ��";
const char GANGSHANG[]="������Ա";
const char TUIYANG[]="������Ա";

CGh::CGh(CWnd* pParent /*=NULL*/)
	: CDialog(CGh::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGh)
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"������");
	strWorkType="";

}


void CGh::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGh)
	DDX_Control(pDX, IDC_COMBO_SEX, c_sex);
	DDX_Control(pDX, IDC_STATIC_MESSAGE, c_message);
	DDX_Control(pDX, IDC_COMBO_TYPE, c_type);
	DDX_Control(pDX, IDC_EDIT_GHF, c_ghf);
	DDX_Control(pDX, IDC_EDIT_NAME, c_name);
	DDX_Control(pDX, IDC_BUTTON_GETINFORMATION, m_4);
	DDX_Control(pDX, IDOK, m_2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGh, CDialog)
	//{{AFX_MSG_MAP(CGh)
	ON_BN_CLICKED(IDC_BUTTON_GETINFORMATION, OnButtonGetinformation)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_EN_KILLFOCUS(IDC_EDIT_NAME, OnKillfocusEditName)
	ON_EN_SETFOCUS(IDC_EDIT_NAME, OnSetfocusEditName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGh message handlers

BOOL CGh::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	c_type.SetCurSel(0); //default ���䱣��
	GetDlgItem(IDC_STATIC_TITLE2)->SetFont(&fontTitle);
	c_ghf.SetWindowText("0");

	CRect r1,r2;
	GetClientRect(r1);
	GetDlgItem(IDC_STATIC_TITLE2)->GetClientRect(r2);
	GetDlgItem(IDC_STATIC_TITLE2)->MoveWindow(0,0,r1.right,r2.bottom);
	CString strSql;
	try{
		strSql.Format("select distinct to_char(sysdate,'yyyymmddhh24miss') da from dual" );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		
		if(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t (recSet->GetCollect("da"));
			
			strDanjuhao='G'+strSql+LoginInformation.user_code;
			
		}
		recSet->Close();

		strSql.Format("select ds1,ds3  from lsq_upgrade WHERE ds2='GH_TYPE' and n2=1 order by n1 " ); // ds1 ������ʾ�� ds3 ���ڲ�����
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		c_type.ResetContent();
		arrWorkType.RemoveAll();

		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt == VT_NULL ? "":recSet->GetFields()->GetItem(0L)->Value );
			c_type.AddString(strSql);
		
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(1L)->Value.vt == VT_NULL ? "":recSet->GetFields()->GetItem(1L)->Value );
			arrWorkType.Add(strSql);
			
			recSet->MoveNext();
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return false;
	}	
	

	c_sex.SetCurSel(2) ;//����ȷ
	c_type.SetCurSel(1);//���䱣��
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGh::OnButtonGetinformation()  /*������ѡ����,���ͬ����*/
{
	CString strType;
	c_type.GetLBText(c_type.GetCurSel(),strType);

	
	if(strType == EMPLOYEE || strType== RELATE || strType == NOWORK ){
		if(strType == EMPLOYEE)	{
			CEmployeeQuery rybm;
			rybm.p=this;
			if(rybm.DoModal()==IDOK){
				strKH=rybm.strKH;
				strName=rybm.strName;
				strSql=rybm.strSex;
				if( strSql== "��" )c_sex.SetCurSel(0);
				else if(strSql== "Ů")c_sex.SetCurSel(1);
				else c_sex.SetCurSel(2);
				strDate[0]=rybm.strDate[0];
				strDate[1]=rybm.strDate[1];
				strWorkType=infor[7]; //ְ������
				c_name.SetWindowText(strName);

				
			}
		}
		else if( strType == RELATE ) 
		{
			CEmployeeRelateQuery rybm;
			rybm.p=this;
			if(rybm.DoModal()==IDOK){
				strKH=rybm.strKH;
				strName=rybm.strName;
				strSql=rybm.strSex;
				if( strSql== "��" )c_sex.SetCurSel(0);
				else if(strSql== "Ů")c_sex.SetCurSel(1);
				else c_sex.SetCurSel(2);
				
				c_name.SetWindowText(strName);
				
			}
		}
		else {
			CEmployeeNoworkQuery rybm;
			rybm.p=this;
			if(rybm.DoModal()==IDOK){
				strKH=rybm.strKH;
				strName=rybm.strName;
				strSql=rybm.strSex;
				if( strSql== "��" )c_sex.SetCurSel(0);
				else if(strSql== "Ů")c_sex.SetCurSel(1);
				else c_sex.SetCurSel(2);
				
				c_name.SetWindowText(strName);
				
			}
		}
		
		
		return;
	}
	else if( strType== GAOQIAN || strType == GANGSHANG || strType == TUIYANG )//��ǰְ��
	{
		COtherSickQuery other;
		other.p=this;
	
		if(strType == GAOQIAN )
		{
			other.strSql.Format("SELECT * from OTHERSICK WHERE LB='����ǰ�Ϲ���' ");
			other.strTitle="����ǰ�Ϲ�����Ϣ";
		}
		else if ( strType == GANGSHANG )
		{
			other.strSql.Format("SELECT * From OtherSick Where LB='������Ա' ");
			other.strTitle="������Ա��Ϣ";
		
		}
		else 
		{
			other.strSql.Format("SELECT * FROM OtherSick Where LB='������Ա' ");
			other.strTitle="������Ա��Ϣ";

		}

		if(other.DoModal()==IDOK){
			strName=other.strName;
			strKH=other.strKH;
			c_name.SetWindowText(strName);
			if(other.strSex == "��" ) c_sex.SetCurSel(0);
			else if(other.strSex == "Ů" ) c_sex.SetCurSel(1);
			else c_sex.SetCurSel(2);
		}


	}
	else if( strType == IC || strType== "�ض�����"  || strType == "����ͳ��" || strType== "��ͥ����")
	{
		CBasisInsureList qu;
		qu.DoModal();
	
		strName=qu.strName;
		strKH=qu.strKH;
		c_name.SetWindowText(strName);
	
		if(qu.strSex == "��" ) c_sex.SetCurSel(0);
		else if(qu.strSex == "Ů" ) c_sex.SetCurSel(1);
		


	}
	else	return;
	



}

void CGh::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect r1,r2;
	GetDlgItem(IDC_STATIC_TITLE2)->GetWindowRect(&r1);
	ScreenToClient(&r1);
	GetClientRect(&r2);

	dc.MoveTo(0,r1.bottom+5);
	dc.LineTo(r2.right,r1.bottom+5);
	// Do not call CDialog::OnPaint() for painting messages
}
/*
const char EMPLOYEE[]="���䱣��";
const char GENERIC[]="������";
const char RELATE[]="��������";
const char NOWORK[]="������Ա";
const char IC[]="��������";

const char GAOQIAN[]="��ǰְ��";
const char GANGSHANG[]="������Ա";
const char TUIYANG[]="������Ա";

*/

void CGh::OnOK() 
{
	if(!theApp.AssertRole(ROLE_STARTDOCTOR_GH))return ;	

	CString strType,str1,strGHF,strSex;
	c_name.GetWindowText(strName); //����
//	c_type.GetLBText(c_type.GetCurSel(),strType); //�Һ�����
	strType=arrWorkType[c_type.GetCurSel()];
	c_ghf.GetWindowText(strGHF); //�Һŷ�
	c_sex.GetLBText(c_sex.GetCurSel(),strSex); //�Ա�
	int year=COleDateTime::GetCurrentTime().GetYear();

	
	try{
		
//{"������","����","����","�Ա�","��������","��������",	"�����","��������"}
		if(strType == EMPLOYEE){  //���䱣��
			if(strKH.IsEmpty()){
				AfxMessageBox("����ѡ��Һ���Ա����...");
				return;
			}else
			{
			
			str1.Format("����: %s\n\n����: %s    ����/����: %d / %d \n\n�ʺ����: %s\n\n�Һųɹ�",\
				strType,strName,year-atol(strDate[0].Left(4)),year-atol(strDate[1].Left(4)),infor[6]);
		
			}
		}
		else if(strType == RELATE){ //��������
			if(strKH.IsEmpty() ) {
				AfxMessageBox("�ȹҺ�...");
				return;
			}
			else 
				str1.Format("����: %s\n\n����: %s\n\n�ʺ����: %s\n\n������: %s\n\n�Һųɹ�",\
				strType,strName,infor[5],infor[6]);

					
		}
		else if(strType == NOWORK ) //������Ա
		{
			if(strKH.IsEmpty() ) {
				AfxMessageBox("�ȹҺ�...");
				return;
			}
			else 
				str1.Format("����: %s\n\n����: %s\n\n��������: 100%\n\n�Һųɹ�",\
				strType,strName);
		}
		else if(strType == IC || strType== "�ض�����" || strType=="����ͳ��" || strType=="��ͥ����" ) //ҽ����}}Ա
		{
			if( ! GetBaseRy() )return;
			strIC.Format("�û���: %s /%s ,�Ƿ�Һ�???",strName,infor[0]);
			if(::MessageBox(this->m_hWnd,strIC,"",MB_OKCANCEL) != IDOK){
				return;
			}

			str1.Format("����: ҽ����Ա\n\n����: %s\n\n�Һųɹ�",strName);

		}
//{"BM","����","�Ա�","����","��������"};
		else if( strType ==GAOQIAN ) //����ǰְ�� 
		{
			if(strKH.IsEmpty()){
				AfxMessageBox("����ѡ�񽨹�ǰ��ְ��");
				return;
			}else
			{
				strType="����ǰ�Ϲ���";  //Ϊ�˺���ǰ��ͬ��,�����Ϊ"����ǰ�Ϲ���"

				str1.Format("����: ����ǰְ��\n\n����: %s \n\n��������: %s%%\n\n�Һųɹ�",\
				strName,infor[4]);

			}

		}
		else if( strType == GANGSHANG ) //����
		{
			if(strKH.IsEmpty()){
				AfxMessageBox("����ѡ���˵�ְ��");
				return;
			}else
				str1.Format("����: ������Ա\n\n����: %s \n\n��������: %s%%\n\n�Һųɹ�",\
				strName,infor[4]);



		}else if( strType == TUIYANG ) //����
		{
			if(strKH.IsEmpty()){
				AfxMessageBox("����ѡ���˵�ְ��");
				return;
			}else
				str1.Format("����: ������Ա\n\n����: %s \n\n��������: %s%%\n\n�Һųɹ�",\
				strName,infor[4]);

		}
		else { // if (strType == GENERIC ){ //������
			c_name.GetWindowText(strName);
			if(strName.IsEmpty() ){
				AfxMessageBox("����������...");
				return;
			}
			strKH=strSex;			
			str1.Format("����: %s\n\n����: %s\n\n�Һųɹ� ",strType,strName);

		}

/*		
const char IC[]="��������";

const char GAOQIAN[]="��ǰְ��";
const char GANGSHANG[]="������Ա";
const char TUIYANG[]="������Ա";
*/	
		if( !(strType == EMPLOYEE) )strWorkType="";

		strSql.Format("INSERT INTO ItemRegisterTou (danjuhao,riqi,sickbm,sickname,\
				�Һ�Ա,�Һ�Ա��,GHTYPE,GHF,ds1) values('%s',TRUNC(sysdate,'dd'),'%s','%s',\
				'%s','%s','%s',%.2f ,'%s') ",strDanjuhao,strKH,strName,LoginInformation.user_code,\
				LoginInformation.user,strType ,atof(strGHF),strWorkType);

		HospitalConnect->BeginTrans();

		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();
		
		strSql.Format("select to_char(sysdate,'yyyymmddhh24miss') da from dual" );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t (recSet->GetCollect("da"));
			
			strDanjuhao='G'+strSql+LoginInformation.user_code;
			
		}
		recSet->Close();
		
		c_message.SetWindowText(str1);
		strKH="";
		strName="";
		c_name.SetWindowText(strKH);
		
		
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("���ϵͳ�е�SQL���޴���...");
		HospitalConnect->RollbackTrans();
		return;
	}
	c_type.SetCurSel(1) ;//���䱣��
	c_name.SetFocus();
}

void CGh::OnCancel() 
{
}

void CGh::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void CGh::OnSelchangeComboType() 
{
	
	strName="";
	strKH="";
	c_type.GetLBText(c_type.GetCurSel(),strSql);
	
	if( strSql == IC || strSql== "�ض�����" || strSql == "����ͳ��" || strSql == "��ͥ����" ){
		strKH="300000000";
	}

	c_name.SetWindowText(strKH);
	c_name.SetFocus();
	c_name.SetSel(9,9);

	// TODO: Add your control notification handler code here
	
}

BOOL CGh::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){
		if(GetFocus()->m_hWnd==c_name.m_hWnd){
			OnGetEmployeeInformation();
			return true;

		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CGh::OnKillfocusEditName() 
{
/*
	CString strType;
	c_type.GetLBText(c_type.GetCurSel(),strType); //�Һ�����
	if( strType == GENERIC ) return ;
	c_name.SetWindowText(strName);
*/
}

void CGh::OnSetfocusEditName() 
{
	c_name.SetWindowText(strKH);	

}

BOOL CGh::GetBaseRy()
{
	CString strSql;
	if( strKH.IsEmpty() ) c_name.GetWindowText(strKH);

	try{
		strSql.Format("select NVL(����,' ') ����,NVL(�Ա�,' ') �Ա� from  ҽ����Ա�б� where ����='%s' ",strKH);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			strName=(char*) _bstr_t(recSet->GetCollect("����"));
			infor[0]=(char*)_bstr_t(recSet->GetCollect("�Ա�"));
			recSet->Close();
		}
		else {
			recSet->Close();

			if(::MessageBox(this->m_hWnd,"��ǰ��Ա���в�����,�Ƿ���� ??? ","��ʾ",MB_OKCANCEL)==IDOK){
				CBaseRyAdd ryadd;
				ryadd.str[0]=strKH;
				if(ryadd.DoModal()==IDOK){
					strName=ryadd.str[1];
					infor[0]=ryadd.str[2];
				}
				else 
					return false;

			}
			else return false;


		

		}

		

	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox("��ѯSQL����...");
		return false;


	}
	return true;

}

void CGh::OnGetEmployeeInformation()
{
//{"������","����","����","�Ա�","��������","��������","�����","��������"}	
	CString strType;
	c_type.GetLBText(c_type.GetCurSel(),strType);
	c_name.GetWindowText(strKH);

	
	try{	
		if(strType == EMPLOYEE || strType== RELATE || strType == NOWORK ){
			if(strType == EMPLOYEE)	{
				strSql.Format("select NVL(����,' ') as NAME,NVL(�Ա�,'����ȷ') as SEX \
					,NVL(�����,0) AS YUER ,NVL(��������,'') as TYPE,�������� as birthday,\
					�������� as workday from ְ����������� e1,�����ű� e2 where  e1.���ű���=e2.���ű��� \
					and ���� = '%s' and ���='�α�'  ",strKH); //not in('����','����')
			
				recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
				if(!recSet->adoEOF){
					strName=(char*)_bstr_t(recSet->GetCollect("NAME"));
					strSql=(char*)_bstr_t(recSet->GetCollect("SEX"));
					infor[6]=(char*)_bstr_t(recSet->GetCollect("YUER"));
					if( strSql== "��" )c_sex.SetCurSel(0);
					else if(strSql== "Ů")c_sex.SetCurSel(1);
				//	else c_sex.SetCurSel(2);
					strDate[0]=(char*)_bstr_t(recSet->GetCollect("birthday"));
					strDate[1]=(char*)_bstr_t(recSet->GetCollect("workday"));
					strWorkType=(char*)_bstr_t(recSet->GetCollect("type"));
					
					GetDlgItem(IDOK)->SetFocus();
					c_name.SetWindowText(strName);
					
				}
				else {
					strKH="";
					c_name.SetWindowText(strKH);
				}
				recSet->Close();
			
			}
			else if( strType == RELATE ) 
			{
				//={"TEMP","����","����","�Ա�","��������","���","������","������","��������"};
				
				strSql.Format("select * from ְ����������� e1,�����ű� e2,codeQingShu e3\
					where e1.���ű���=e2.���ű��� and e3.kahao=e1.���� and \
					e3.bm='%s' AND ��� != '����' ",strKH);
				recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
				
				if(!recSet->adoEOF){
					strName=(char*)_bstr_t(recSet->GetCollect("XM"));
					strSql=(char*)_bstr_t(recSet->GetCollect("XB"));
					infor[5]=(char*)_bstr_t(recSet->GetCollect("YUER"));
					infor[6]=(char*)_bstr_t(recSet->GetCollect("����"));
					if( strSql== "��" )c_sex.SetCurSel(0);
					else if(strSql== "Ů")c_sex.SetCurSel(1);
					else c_sex.SetCurSel(2);
					GetDlgItem(IDOK)->SetFocus();
		
					c_name.SetWindowText(strName);
					
				}
				else {
					strKH="";
					c_name.SetWindowText(strKH);
				}
				recSet->Close();
			}
			else { //������Ա����
				strSql.Format("select NVL(����,' ') as NAME,NVL(�Ա�,'����ȷ') as SEX \
					from ְ����������� e1,�����ű� e2 where  e1.���ű���=e2.���ű��� \
					and ���� = '%s' and ��� ='����' ",strKH);
				recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
				if(!recSet->adoEOF){
					strName=(char*)_bstr_t(recSet->GetCollect("NAME"));
					strSql=(char*)_bstr_t(recSet->GetCollect("SEX"));
					if( strSql== "��" )c_sex.SetCurSel(0);
					else if(strSql== "Ů")c_sex.SetCurSel(1);
					else c_sex.SetCurSel(2);
				
					c_name.SetWindowText(strName);
					GetDlgItem(IDOK)->SetFocus();
				
				}
			else {
				strKH="";
				c_name.SetWindowText(strKH);
			}
			recSet->Close();
			
			}
			
			
		//	return;
		}
		else if( strType== GAOQIAN || strType == GANGSHANG || strType == TUIYANG )//��ǰְ��
		{
			if(strType == GAOQIAN )
				strSql.Format("SELECT * from OTHERSICK WHERE LB='����ǰ�Ϲ���' AND BM='%s' ",strKH);
			else if ( strType == GANGSHANG )
				strSql.Format("SELECT * From OtherSick Where LB='������Ա' AND BM='%s' ",strKH);
			else 
				strSql.Format("SELECT * FROM OtherSick Where LB='������Ա' AND BM='%s' ",strKH);
			
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){
				strName=(char*)_bstr_t(recSet->GetCollect("XM"));
				strSql=(char*)_bstr_t(recSet->GetCollect("XB"));
				if(strSql == "��" ) c_sex.SetCurSel(0);
				else if(strSql == "Ů" ) c_sex.SetCurSel(1);
				else c_sex.SetCurSel(2);
				infor[4]=(char*)_bstr_t(recSet->GetCollect("PRO"));
				c_name.SetWindowText(strName);
				GetDlgItem(IDOK)->SetFocus();
			}
			else {
				strKH="";
				c_name.SetWindowText(strKH);
			}
			recSet->Close();
			
			
		}
		//else if(strType == IC || strType== "�ض�����" )
		else
		{
			OnOK();
			return;
		}
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return ;
	}
}
