// CostConsumeAdd.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "CostConsumeAdd.h"
#include "costClassAb.H"
#include "operatorSel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCostConsumeAdd dialog


CCostConsumeAdd::CCostConsumeAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CCostConsumeAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCostConsumeAdd)
	m_date = COleDateTime::GetCurrentTime();
	m_jsr = _T("");
	m_rss = _T("");
	m_spr = _T("");
	m_iFujian = 0;
	m_iPiaoju = 0;
	m_dbFee = 0.0;
	m_strUser = _T("");
	m_strCmt = _T("");
	//}}AFX_DATA_INIT
	m_Brush.CreateSolidBrush(RGB(255,0,128));
	fPrint=false;
	fontTitle.CreatePointFont(220,"Ҧ��");
}


void CCostConsumeAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCostConsumeAdd)
	DDX_Control(pDX, IDC_EDIT_CREDENCE, m_credence);
	DDX_Control(pDX, IDC_EDIT_BALANCE2, m_balance2);
	DDX_Control(pDX, IDC_EDIT_100SCALE, m_cScale);
	DDX_Control(pDX, IDC_EDIT_SJBS, m_sjFee);
	DDX_Control(pDX, IDC_EDIT_SCALE, m_scale);
	DDX_Control(pDX, IDC_EDIT_BALANCE, m_balance);
	DDX_Control(pDX, IDC_COMBO_COST_B, m_departB);
	DDX_Control(pDX, IDC_COMBO_COST_A, m_departA);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_CUR, m_date);
	DDX_Text(pDX, IDC_EDIT_JSR, m_jsr);
	DDX_Text(pDX, IDC_EDIT_RSS, m_rss);
	DDX_Text(pDX, IDC_EDIT_SPR, m_spr);
	DDX_Text(pDX, IDC_EDIT_FUJIAN, m_iFujian);
	DDX_Text(pDX, IDC_EDIT_PIAOJU, m_iPiaoju);
	DDX_Text(pDX, IDC_EDIT_ZHONGFEIYONG, m_dbFee);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
	DDX_Text(pDX, IDC_EDIT_CMMT, m_strCmt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCostConsumeAdd, CDialog)
	//{{AFX_MSG_MAP(CCostConsumeAdd)
	ON_CBN_SELCHANGE(IDC_COMBO_COST_A, OnSelchangeComboCostA)
	ON_CBN_SELCHANGE(IDC_COMBO_COST_B, OnSelchangeComboCostB)
	ON_BN_CLICKED(IDOK_RY1, OnRy1)
	ON_BN_CLICKED(IDOK_RY2, OnRy2)
	ON_BN_CLICKED(IDOK_RY3, OnRy3)
	ON_BN_CLICKED(IDOK2, OnOk2)
	ON_EN_CHANGE(IDC_EDIT_SCALE, OnChangeEditScale)
	ON_EN_CHANGE(IDC_EDIT_ZHONGFEIYONG, OnChangeEditZhongfeiyong)
	ON_WM_CTLCOLOR()
	ON_EN_KILLFOCUS(IDC_EDIT_USER, OnKillfocusEditUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCostConsumeAdd message handlers

BOOL CCostConsumeAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	SetWindowText("���ñ���");
	arrayA.RemoveAll();
	long i;
	CComFunc::GetSql(strSql,CCostClassAb::COST_A_SQLID);
//��ʼ������
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(! recSet->adoEOF){
			i=0;
			arrayA.Add(CComFunc::GetSqlItem(i++));
			m_departA.AddString(CComFunc::GetSqlItem(i));

			recSet->MoveNext();
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		strSql.Format("���ִ���,����SQL=%ld ���...",CCostClassAb::COST_A_SQLID);
		AfxMessageBox(strSql);
		return false;
	}		
//��ʼ�������˵�
	const char * param="[XT001]";
	CString strTmp[2],s1;
	CComFunc::GetSql(strSql,SQL_ID_OPERATOR_SEL);
	s1=strSql;
	strSql.Replace(param,"001"); //������
	CComFunc::GetString(strSql,strTmp,2);
	m_rss_id=strTmp[0];
	m_rss=strTmp[1];

	strSql=s1;
	strSql.Replace(param,"002"); //������
	CComFunc::GetString(strSql,strTmp,2);
	m_jsr_id=strTmp[0];
	m_jsr=strTmp[1];

	strSql=s1;
	strSql.Replace(param,"003"); //������
	CComFunc::GetString(strSql,strTmp,2);
	m_spr_id=strTmp[0];
	m_spr=strTmp[1];

	strSql="select ds1 from lsq_title_list t where ds2='PARAM' and ds3='OTHER' and ds4='004' ";
	 //Ĭ�ϱ���������
	m_strUser=CComFunc::GetString(strSql);


	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCostConsumeAdd::OnSelchangeComboCostA() 
{
	const char * argu_01="[XT001]";
	arrayB.RemoveAll();
	m_departB.ResetContent();
	CComFunc::GetSql(strSql,CCostClassAb::COST_B_SQLID);
	int i;
	CString str2;
	str2.Format(" ID2=%s AND ",arrayA[m_departA.GetCurSel()] );

	strSql.Replace(argu_01,str2);
	try{
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		while(! recSet->adoEOF){
			i=0;
			arrayB.Add(CComFunc::GetSqlItem(i++));
			m_departB.AddString(CComFunc::GetSqlItem(i));

			recSet->MoveNext();

		}
		recSet->Close();


	}
	catch(_com_error e)
	{
		strSql.Format("���ִ���,����SQL=%ld ���...",CCostClassAb::COST_B_SQLID);
		AfxMessageBox(strSql);
		return ;
	}		
	m_balance.SetWindowText(BLANKSTR);
	m_balance2.SetWindowText(BLANKSTR);
	GenericSerial();//����ƾ֤���
}

void CCostConsumeAdd::OnSelchangeComboCostB() 
{  //��ȡԤ�㼰������� 
	UpdateData();
	const char * argu_01="[XT_YEAR]";
	const char * argu_02="[XT_ID]";
	CComFunc::GetSql(strSql,SQL_ID_BALANCE_BUDGET);
	CString str1,str2,s[2];
	str1.Format("%ld",m_date.GetYear() );
	str2.Format("%s",arrayB[m_departB.GetCurSel()]);
	strSql.Replace(argu_01,str1);
	strSql.Replace(argu_02,str2);

	CComFunc::GetString(strSql,s,2);

	m_balance.SetWindowText(s[0]+"/"+s[1]);

	dbBalance=atof(s[0])-atof(s[1]) ;
	str1.Format("%.2f",dbBalance );
	m_balance2.SetWindowText(str1); //��ǰ����

	

}

void CCostConsumeAdd::OnRy1() //������
{
	COperatorSel os;
	if( os.DoModal() == IDOK)
	{
		m_rss=os.strName;
		m_rss_id=os.strID;
		UpdateData(false);
	}

}

void CCostConsumeAdd::OnRy2() //������
{
	COperatorSel os;
	if( os.DoModal() == IDOK)
	{
		m_jsr=os.strName;
		m_jsr_id=os.strID;
		UpdateData(false);
	}
	
}

void CCostConsumeAdd::OnRy3() //������
{
	COperatorSel os;
	if( os.DoModal() == IDOK)
	{
		m_spr=os.strName;
		m_spr_id=os.strID;
		UpdateData(false);
	}
	
}

BOOL CCostConsumeAdd::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN ) {
		pMsg->wParam=VK_TAB;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}




void CCostConsumeAdd::OnOk2() //��ӡ
{
 _Application app ;
 Workbooks books;
_Workbook book;
 Worksheets sheets;
 _Worksheet sheet;
 COleVariant vOpt(DISP_E_PARAMNOTFOUND,VT_ERROR);
#define _O(x) COleVariant(x)
#define STANDARDFONT  12
#define FONTNAME	"����"

	UpdateData();
	fPrint=true; //�Ѵ�ӡ��־
	const short int useSheetNumber=4;//sheet4 ��Ϊ������Ա�������
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
		
		book=books.Open(strFileName,vOpt,vOpt,
			vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
		sheets=book.GetWorksheets();

//	}
	sheet=sheets.GetItem(COleVariant(useSheetNumber)); 
	app.SetVisible(false);

	CString strCell[]=
	{"B3","B4","B5","B6","B7","B8","B9","D3","D4","D5","D6","D7","D8","E4" }; //��13
	//�ֱ�Ϊ ����,��������,ʹ����,������,������,������,��д,ƾ֤��,������,
	//������,�ܶ�,����,ʵ��
	
	CString strData[16],strTemp;
/*	c1 ʹ����
	c2 ������
	c3 ������
	c4 ������
	c5 ƾ֤��
	c6 ������
	c7 ������
	c8 �ܽ��
	c9 ���� c_scale
	c10 ������
	c11 ��ע	
*/
	Range vr;
	vr=sheet.GetRange(_O("A1"),_O("A1"));
	m_departA.GetLBText(m_departA.GetCurSel(),strTemp); 
	vr.SetValue(_O(strTemp)); //���ñ���
	long i=0;

	strData[i++]=m_date.Format("%Y-%m-%d");
	m_departB.GetLBText(m_departB.GetCurSel(),strData[i++] );
	strData[i++]=m_strUser;
	strData[i++]=m_rss;
	strData[i++]=m_jsr;
	strData[i++]=m_spr;
//	��дת��
	m_sjFee.GetWindowText(strTemp);
	CComFunc::GetBigMoney(	atof(strTemp),strData[i++] );
	
	m_credence.GetWindowText(strData[i++]);
	strData[i++].Format("%ld��",m_iPiaoju);
	strData[i++].Format("%ld��",m_iFujian);

	strData[i++].Format("%.2f",m_dbFee);
	m_cScale.GetWindowText(strData[i++]);
	m_sjFee.GetWindowText(strData[i++]);

	strData[i++]=m_strCmt;
	
	for(long z=0 ;z < i ; z++ )
	{
		vr=sheet.GetRange(_O(strCell[z]),_O(strCell[z])); // ҽ�ƻ���
		vr.SetValue(COleVariant(strData[z]));

	}

	PageSetup pageinfo=sheet.GetPageSetup();
//	sheet.PrintPreview(_O((short)1));
	sheet.PrintOut(vOpt,vOpt,_O((short)1),vOpt,vOpt,vOpt,vOpt,vOpt);


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

}

void CCostConsumeAdd::OnOK() //����
{
	UpdateData();
	if ( m_strUser.IsEmpty() || m_rss_id.IsEmpty() || m_jsr_id.IsEmpty() || m_spr_id.IsEmpty()
		|| m_departA.GetCurSel()==CB_ERR || m_departB.GetCurSel()==CB_ERR )
	{
		AfxMessageBox("������д�û�����Ϣ��Ȼ���ٵ����������");
		return;
	}
	if(!fPrint){
		if( AfxMessageBox("��δ��ӡ���Ƿ�Ҫ������������",MB_YESNO)==IDNO )
			return;
	}
	CString strSql,str;
	double dbScale,dbFee;
	const char * SPECIAL_CHAR="'";
	const char * REPLACE_SPC="''";
	m_cScale.GetWindowText(str);
	dbScale=atof(str);
	m_sjFee.GetWindowText(str);
	dbFee=atof(str);
	//���кţ����ڣ����ID�������ˣ������ˣ������ˣ������ˣ����������������������ܶ������ʵ�����
	//��ע������ԱID
	m_strCmt.Replace(SPECIAL_CHAR,REPLACE_SPC); //����ע�е������޳�����ֹSQL��䱨��
	m_strUser.Replace(SPECIAL_CHAR,REPLACE_SPC);
	strSql.Format(" INSERT INTO lsq_cost_balance_budget(ds1,d1,id2,syr,ysr,jsr,spr,n1,n2,n3,n4,n5,\
		ds2,opid) values (generateSerial(),to_date(%s,'yyyymmdd'),%ld,'%s',%ld,%ld,%ld,%ld,%ld,%.2f,\
		%.2f,%.2f,'%s',%ld ) ",m_date.Format("%Y%m%d"),atol(arrayB[m_departB.GetCurSel()] ),m_strUser,
		atol(m_rss_id),atol(m_jsr_id),atol(m_spr_id),m_iPiaoju,m_iFujian,m_dbFee,dbScale,dbFee,
		m_strCmt,atol(LoginInformation.user_code ) );

	if( !CComFunc::WriteSql(strSql) )
	{	
		AfxMessageBox("д����ִ���,������!");
		return;
	}

	InitControl();
	AfxMessageBox("д��ɹ�!");
	


}

void CCostConsumeAdd::OnChangeEditScale() 
{

	UpdateData();
	
	CString s1,s2;
	double f1,f2,fee;
	m_scale.GetWindowText(s1);
	f1=atof(s1);
	s2.Format("%.2f",f1);
	f2=atof(s2);
	s2+="%";
	m_cScale.SetWindowText(s2);

	fee=m_dbFee*f2/100;
	s2.Format("%.2f",fee);
	m_sjFee.SetWindowText(s2);

	s2.Format("%.2f",dbBalance-fee);
	m_balance2.SetWindowText(s2);



}

void CCostConsumeAdd::OnChangeEditZhongfeiyong() 
{
	
	OnChangeEditScale();	
}

void CCostConsumeAdd::InitControl()
{
	m_departA.SetCurSel(CB_ERR);
	m_departB.ResetContent();
	m_balance.SetWindowText(BLANKSTR);
	m_sjFee.SetWindowText(BLANKSTR); //ʵ�ʱ���
	m_scale.SetWindowText(BLANKSTR); //����
	m_cScale.SetWindowText(BLANKSTR);//��������
	m_balance2.SetWindowText(BLANKSTR);
	m_credence.SetWindowText(BLANKSTR);

	dbBalance=0;
	m_dbFee=0;
	m_strUser=BLANKSTR;
	m_strCmt=BLANKSTR;
	m_iPiaoju=0,m_iFujian=0;
	fPrint=false;

	UpdateData(false);

}

HBRUSH CCostConsumeAdd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if( pWnd->m_hWnd == GetDlgItem(IDC_EDIT_BALANCE)->m_hWnd ||
		pWnd->m_hWnd ==GetDlgItem(IDC_EDIT_BALANCE2)->m_hWnd ||
		pWnd->m_hWnd ==GetDlgItem(IDC_EDIT_100SCALE)->m_hWnd ||
		pWnd->m_hWnd ==GetDlgItem(IDC_EDIT_SJBS)->m_hWnd )
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return m_Brush;
	}
	
	return hbr;
}

void CCostConsumeAdd::GenericSerial() //����ƾ֤���
{
	int iSel=m_departA.GetCurSel();
	const char *pOld="[XT001]",
		*pYear="[XT002]";
	CString syear;
	syear.Format("%d",m_date.GetYear() );
	//SQL_CREDENCE_ID,36
	CComFunc::GetSql(strSql,SQL_CREDENCE_ID);
	strSql.Replace(pOld,arrayA[iSel]);
	strSql.Replace(pYear,syear);

	m_credence.SetWindowText(CComFunc::GetString(strSql));

	
}

void CCostConsumeAdd::OnKillfocusEditUser() 
{
	UpdateData();	
}

