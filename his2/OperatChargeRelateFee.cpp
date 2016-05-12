// OperatChargeRelateFee.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "OperatChargeRelateFee.h"
#include "EmployeeRelateQueryForFee.h"
#include "qiuXpButton.h"
#include "excel9.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COperatChargeRelateFee dialog


COperatChargeRelateFee::COperatChargeRelateFee(CWnd* pParent /*=NULL*/)
	: CDialog(COperatChargeRelateFee::IDD, pParent)
{
	//{{AFX_DATA_INIT(COperatChargeRelateFee)
	m_date1 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"����");
	c_mRybm="";
	dbQuota=0.0;
}


void COperatChargeRelateFee::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COperatChargeRelateFee)
	DDX_Control(pDX, IDCANCEL, m_3);
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, IDPRINT, m_1);
	DDX_Control(pDX, IDC_EDIT_SCALE_ACCOUNT, c_scaleConsume);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT_SPARE, c_spare);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT_CONSUME, c_accountConsume);
	DDX_Control(pDX, IDC_EDIT_GRZF, c_grzf);
	DDX_Control(pDX, IDC_EDIT_REAL_BX, c_realbao);
	DDX_Control(pDX, IDC_EDIT1, c_rymc);
	DDX_Control(pDX, IDC_EDIT_SEX, c_sex);
	DDX_Control(pDX, IDC_EDIT_SCALE, c_scale);
	DDX_Control(pDX, IDC_EDIT_PROPERTY, c_property);
	DDX_Control(pDX, IDC_EDIT_NAME, c_name);
	DDX_Control(pDX, IDC_EDIT_INVOICE, c_invoice);
	DDX_Control(pDX, IDC_EDIT_AGE, c_age);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, c_account);
	DDX_Control(pDX, IDC_COMBO1, c_combo1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COperatChargeRelateFee, CDialog)
	//{{AFX_MSG_MAP(COperatChargeRelateFee)
	ON_BN_CLICKED(IDC_BUTTON_RELATE, OnButtonRelate)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_EN_SETFOCUS(IDC_EDIT1, OnSetfocusEdit1)
	ON_EN_CHANGE(IDC_EDIT_ALL, OnChangeEditAll)
	ON_BN_CLICKED(IDPRINT, OnPrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COperatChargeRelateFee message handlers

void COperatChargeRelateFee::OnButtonRelate()  //������������
{
//	{"����","����","�Ա�","��������","���","����","������","������",\
		"��������","����"},str1;
			CEmployeeRelateQueryForFee rybm;
			rybm.p=this;
			rybm.flagRELATE=777; //��Ϊ����ʱ����
		
			if( rybm.DoModal() == IDOK ){

				c_rymc.SetWindowText(infor[1]);
				c_sex.SetWindowText(infor[5]+" / "+infor[2]);
				c_property.SetWindowText(infor[3]);
				c_name.SetWindowText(infor[6]);
				c_age.SetWindowText(infor[9]);
				c_account.SetWindowText( infor[4] );//���
				c_mRybm=infor[0];
				c_mRymc=infor[1];
				GetAlreadyUsed() ; //�õ���ʹ�ö�
			}

			GenericScale(); //����Ӧ������
			OnChangeEditAll();	 //����Ӧ���ɱ�����
}

void COperatChargeRelateFee::GenericScale()
{
	CString strProperty,str2,str3;

	c_property.GetWindowText( strProperty );
	if( c_combo1.GetCurSel() == CB_ERR ) return;

	if( c_combo1.GetCurSel() == 0 ){ //����
		c_scale.SetWindowText("");

	}
	else if( c_combo1.GetCurSel() == 1 ) { //סԺ
		if( atol(infor[5]) <= 14 && strProperty=="˫ְ����Ů" )//80%
		{
			c_scale.SetWindowText("80%");

		}
		else if( atol(infor[9]) <= 25 )
		{
			c_scale.SetWindowText("40%");

		}
		else if( atol(infor[9]) >=26 )
		{
			c_scale.SetWindowText("45%");
		}


	}
}

void COperatChargeRelateFee::OnSelchangeCombo1() 
{
	GenericScale();	
	OnChangeEditAll();
}

BOOL COperatChargeRelateFee::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    dbQuota=atof(	COtherDecharge::GetStringTitle(" select n1 from lsq_upgrade where ds2='RELATE_DECHARGE' ") );
	GetDlgItem(IDC_STATIC_HEAD)->SetFont(&fontTitle);
	CString strSql;
	try{
		strSql.Format("select count(*)+1 from lsq_relate_decharge  where de_real !='1' ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		if(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(0l)->Value) ;
			GetDlgItem(IDC_EDIT_NEWROW)->SetWindowText(strSql);
		}
		recSet->Close();		
	
	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox(strSql);
		return false;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COperatChargeRelateFee::OnKillfocusEdit1() 
{
	CString str1,str2;
	c_rymc.GetWindowText(str1);
	if( str1 == c_mRybm )c_rymc.SetWindowText(c_mRymc);
	else {

		GetInformationFromBM(str1);
		GenericScale();	//���ɱ�������
		OnChangeEditAll();	 //����Ӧ���ɱ�����

	}
		
}

void COperatChargeRelateFee::OnSetfocusEdit1() 
{
	c_rymc.SetWindowText( c_mRybm);
}

void COperatChargeRelateFee::GetInformationFromBM(CString strx)
{

	CString strSql,str1;
	long count,z;
	strSql.Format("select BM,XM,XB,XINGZHI,YUER,to_char(sysdate,'yyyy')-to_char(csRiQI,'yyyy'),\
			����,������,��������,to_char(sysdate,'yyyy')-to_char(��������,'yyyy')+1,kahao from ְ����������� e1,�����ű� e2,codeQingShu e3 where \
				e1.���ű���=e2.���ű��� and e3.kahao=e1.���� and \
				bm = '%s'  and ZXriqi is NULL ",strx);
	
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		z=11 ;
		if(!recSet->adoEOF){
			for(count=0;count< z ;count++){
				
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(count)->Value.vt==VT_NULL ? " ":recSet->GetFields()->GetItem(count)->Value ) ;
				infor[count]=str1;
			}
				
			
		}
		else 
			for(count=0 ; count < z ;count++)infor[count]="";
		recSet->Close();		

		c_rymc.SetWindowText(infor[1]);
		c_sex.SetWindowText(infor[5]+" / "+infor[2]);
		c_property.SetWindowText(infor[3]);
		c_name.SetWindowText(infor[6]);
		c_age.SetWindowText(infor[9]);
		c_account.SetWindowText( infor[4] );//���
		c_mRybm=infor[0];
		c_mRymc=infor[1];
		
		GetAlreadyUsed();
	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox("���ݿ�����ƻ�,��������...");
		return;
	}

}

BOOL COperatChargeRelateFee::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam == VK_RETURN )
		pMsg->wParam=VK_TAB;

	return CDialog::PreTranslateMessage(pMsg);
}

void COperatChargeRelateFee::OnChangeEditAll()  //�ܽ��ı�ʱ����Ӧ����
{
	CString strScale,strAll,strAccount,strTemp;
	double dbAll,dbAccount,dbScale,dbUsed;
	c_scale.GetWindowText(strScale);
	c_account.GetWindowText(strAccount);
	GetDlgItem(IDC_EDIT_ALL)->GetWindowText(strAll);
	GetDlgItem(IDC_EDIT_ALREADY_USED)->GetWindowText(strTemp);
	dbUsed=atof(strTemp);


	if( c_combo1.GetCurSel() == 0 ){ //ֻ�ܰ��ʻ�����
	
		if( atof(strAll) > atof(strAccount) ){
			c_realbao.SetWindowText( strAccount);

			c_accountConsume.SetWindowText(strAccount);//�ʻ�֧��
			
			strTemp.Format("%.2f",atof(strAll)-atof(strAccount) );
			c_grzf.SetWindowText(strTemp);
			c_spare.SetWindowText("0.00"); //�ʻ�ʣ��
			
		}
		else{
			c_realbao.SetWindowText( strAll);
			c_accountConsume.SetWindowText(strAll);//�ʻ�֧��
			strTemp.Format("%.2f",atof(strAccount)-atof(strAll) );
			c_spare.SetWindowText(strTemp); //�ʻ�ʣ��
			c_grzf.SetWindowText("0.00");  //�����Ը�

		}
		c_scaleConsume.SetWindowText("0.00"); //��������Ϊ ��

	}
	else if( c_combo1.GetCurSel() == 1) //סԺ
	{
		dbScale=atof(strScale.Left(strScale.GetLength()-1 ) )/100 ; //�����������
		dbAccount=atof(strAccount);
		dbAll=atof(strAll);
		if( dbAll * dbScale+dbUsed  >= dbQuota ){  //�ܽ���һ��Ԫ
			strTemp.Format("%.2f",dbQuota-dbUsed  );
			c_realbao.SetWindowText(strTemp);
			strTemp.Format("%.2f",dbAccount );
			c_accountConsume.SetWindowText(strTemp);//�ʻ�֧��
			strTemp.Format("%.2f",dbQuota-dbUsed-dbAccount);
			c_scaleConsume.SetWindowText(strTemp);
			strTemp.Format("%.2f",dbAll-(dbQuota-dbUsed));
			c_grzf.SetWindowText(strTemp); //����֧��
			c_spare.SetWindowText("0.00"); //�ʻ�ʣ��
		}
		else{
		
		//	strTemp.Format("%.2f",dbAll*dbScale);
			if( dbAll*dbScale+dbUsed+dbAccount >dbQuota ) // ���������������Ѿ�ʹ�ý��ʻ����
			{

				strTemp.Format("%.2f",dbQuota-dbUsed-dbAccount );
			}
			else
			{
				strTemp.Format("%.2f",dbAll*dbScale);
			}
			c_scaleConsume.SetWindowText(strTemp);//������֧��

			double db01=atof(strTemp); //����֧�����
			if( dbAll-db01 >= dbAccount){
				strTemp.Format("%.2f",db01 + dbAccount );
				c_realbao.SetWindowText(strTemp);
				strTemp.Format("%.2f",dbAccount );
				c_accountConsume.SetWindowText(strTemp);//�ʻ�֧��
				c_spare.SetWindowText("0.00"); //�ʻ�ʣ��
				strTemp.Format("%.2f",dbAll-db01- dbAccount );
			}
			else{
				strTemp.Format("%.2f",dbAll);
				c_realbao.SetWindowText(strTemp);
				strTemp.Format("%.2f",dbAll*(1-dbScale) );
				c_accountConsume.SetWindowText(strTemp);//�ʻ�֧��
				strTemp.Format("%.2f",dbAccount-dbAll*(1-dbScale) );
				c_spare.SetWindowText(strTemp); //�ʻ�ʣ��
			
				strTemp.Format("0.00");
			}
			c_grzf.SetWindowText(strTemp);

		}
	}

}

void COperatChargeRelateFee::OnOK() 
{
	if( c_combo1.GetCurSel() == CB_ERR || c_mRybm.IsEmpty() ){
		AfxMessageBox("�뽫�����Ϣ��д�����ٽ��б�������....");
		return;
	}
/*infor[10]Ϊְ������,infor[0]Ϊ��Ů���� */
	CString strSql,strTemp;
	double dbAll,dbAccountConsume,dbScaleConsume,dbScale,dbConsume,invoice;
	double dbUsed;
	UpdateData();
	GetDlgItem(IDC_EDIT_ALREADY_USED)->GetWindowText(strTemp);
	dbUsed=atof(strTemp); //��ʹ�ý��
	if( dbUsed >= dbQuota ){
		MessageBox("��ǰ�û����������Ѵﵽ�����޶�!!��ֹ�����ٱ���!!","����",MB_OK|MB_ICONSTOP);
		return;
	}
	c_account.GetWindowText(strTemp);
	if( atof(strTemp) == 0. && c_combo1.GetCurSel() == 0 ){
		MessageBox("��ǰ�û��ʻ����Ϊ��,��ֹ������ñ���!!","����",MB_OK|MB_ICONSTOP);
		return;

	}

//	OnPrint(); //��ӡ
	try{
		GetDlgItem(IDC_EDIT_ALL)->GetWindowText(strTemp);
		dbAll=atof(strTemp); //�ܷ���
		c_accountConsume.GetWindowText(strTemp);
		dbAccountConsume=atof(strTemp); //�ʻ�������
		c_scaleConsume.GetWindowText(strTemp);
		dbScaleConsume=atof(strTemp);
		c_scale.GetWindowText(strTemp);
		dbScale=atof(strTemp.Left(strTemp.GetLength()-1) )/100;
		c_realbao.GetWindowText(strTemp);
		dbConsume=atof(strTemp);//ʵ�����=�ʻ�֧��+��������
		c_invoice.GetWindowText(strTemp);
		invoice=atof(strTemp);
		c_combo1.GetLBText(c_combo1.GetCurSel(),strTemp);

		strSql.Format("INSERT INTO lsq_relate_decharge (riqi,serial,oper_code,\
			oper_name,all_expense,invoices,account_pay,scale_pay,scale,kahao1,\
			kahao2,dechargetype,all_pay ) VALUES(to_date(%s,'yyyymmdd'),to_char(sysdate,'yyyymmddhh24miss')||'%s','%s',\
			'%s',%.2f,%.2f,%.2f,%.2f,%.2f,'%s',\
			'%s','%s',%.2f ) ",m_date1.Format("%Y%m%d"),LoginInformation.user_code,LoginInformation.user_code,\
			LoginInformation.user,dbAll,invoice,dbAccountConsume,dbScaleConsume,dbScale,infor[0],\
			infor[10],strTemp,dbConsume );

		HospitalConnect->BeginTrans();
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		if( dbAccountConsume != 0 ) //�۳��ʻ�
		{
			strSql.Format("UPDATE codeQingshu SET yuer=yuer-(%.2f),ds1=( SELECT sys_context('USERENV','ip_address')||'.'|| to_char(sysdate,'hh24yyyymimmssdd') ||'RELDEC' from dual ),d1=sysdate WHERE bm='%s' ",dbAccountConsume,infor[0] );
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		}
		HospitalConnect->CommitTrans();


	}catch(_com_error e)
	{
		AfxMessageBox(strSql);
		HospitalConnect->RollbackTrans();
		return;
	}
	
	AfxMessageBox("��ǰ�û������ɹ�...");


	c_name.SetWindowText("");
	c_property.SetWindowText("");
	c_realbao.SetWindowText("");
	c_scaleConsume.SetWindowText("");
	c_accountConsume.SetWindowText("");
	c_account.SetWindowText("");
	c_age.SetWindowText("");
	c_rymc.SetWindowText("");
	c_invoice.SetWindowText("");
	c_scale.SetWindowText("");
	c_sex.SetWindowText("");
	c_mRybm="";
	c_mRybm="";
	GetDlgItem(IDC_EDIT_ALREADY_USED)->SetWindowText("");
	GetDlgItem(IDC_EDIT_ALL)->SetWindowText("");

	GetDlgItem(IDC_EDIT_NEWROW)->GetWindowText(strTemp);
	strSql.Format("%ld",atol(strTemp)+1);
	GetDlgItem(IDC_EDIT_NEWROW)->SetWindowText(strSql);

	c_rymc.SetFocus();

}

void COperatChargeRelateFee::GetAlreadyUsed() //���㵱���ѱ����� 
{
	CString strSql,str1;
	

	strSql.Format("select  NVL(sum(all_pay),0) from lsq_relate_decharge t where \
		kahao1='%s' AND riqi between round(add_months(sysdate,-6)) and sysdate \
		AND De_real !='1' ",c_mRybm);
	
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		if(!recSet->adoEOF){
			str1=(char*)_bstr_t(recSet->GetFields()->GetItem(0l)->Value) ;
			GetDlgItem(IDC_EDIT_ALREADY_USED)->SetWindowText(str1);
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

extern _Application app;
extern Workbooks books;
extern _Workbook book;
extern Worksheets sheets;
extern _Worksheet sheet;
extern COleVariant vOpt;

#define _O(x) COleVariant(x)
#define STANDARDFONT  12
#define FONTNAME	"����"

void COperatChargeRelateFee::OnPrint() 
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
	sheet=sheets.GetItem(COleVariant((short)2)); //sheet2 ��Ϊ��������������ӡ����

//	CString strCell[]={"C6","C8","C9","C10","C12","C14","C15","C16","G6","G8","G9","G10","G12","G14","G15","G16" }; //��14 
	//�ֱ�Ϊ ְ������,��������,�Ա�,��ϵ,����,��������
	//		 ����    ,,�ʻ����  �������� ��Ʊ �ܽ�� ʵ��,����,�ʻ�,����   
	CString strCell[]={"C6","C8","C9","C10","C12","C14","C15","C16","G6","G9","G10","G16","g12","g14","g15","g8"};
	// "G8","G9","G10","G12","G14","G15","G16" };
	CString strData[16],strTemp;
	double dbRealbao;
	int i=0;
	c_name.GetWindowText(strData[i++]);//ְ������
	strData[i++]=c_mRymc; //��������
	c_sex.GetWindowText(strData[i++]);
	c_property.GetWindowText(strData[i++]);
	c_age.GetWindowText(strData[i++] );
	c_scale.GetWindowText(strData[i++]);

	c_combo1.GetLBText(c_combo1.GetCurSel() , strData[i++]); //�ٶ�������ѡ��

	c_spare.GetWindowText(strTemp);
	strData[i++].Format("��%.2fԪ",atof(strTemp) ); //�ʻ����
	
	
	strData[i++]=m_date1.Format("%Y-%m-%d"); //��������

	c_invoice.GetWindowText(strData[i++]); //��Ʊ����

	GetDlgItem(IDC_EDIT_ALL)->GetWindowText(strTemp);
	strData[i++].Format("��%.2fԪ",atof(strTemp) );
	
	c_realbao.GetWindowText(strTemp); //ʵ�����
	dbRealbao=atof(strTemp);

	strData[i++].Format("��%.2fԪ", dbRealbao);
	c_scaleConsume.GetWindowText(strTemp);
	strData[i++].Format("��%.2fԪ",atof(strTemp) );
	c_accountConsume.GetWindowText( strTemp);
	strData[i++].Format("��%.2fԪ",atof(strTemp) );
	c_grzf.GetWindowText( strTemp); //����֧�� 
	strData[i++].Format("��%.2fԪ",atof(strTemp) );

	GetDlgItem(IDC_EDIT_ALREADY_USED)->GetWindowText(strTemp);
	strData[i++].Format("��%.2fԪ",atof(strTemp)+dbRealbao );
	
	
	app.SetVisible(false); //��ʾ
//��ӱ������	
	Range vrange;
	vrange=sheet.GetRange(_O("B4"),_O("B4"));
	strTemp=(char*)_bstr_t(vrange.GetValue());
	
	strFileName=strTemp.Right(32);
	strTemp=strFileName;

	GetDlgItem(IDC_EDIT_NEWROW)->GetWindowText(strFileName);
	CString xstr;
	xstr.Format("NO:%s %s",strFileName,strTemp);
	vrange.SetValue(_O(xstr));
///////////////////////////////////////////////////////////////////
	for( i=0 ;i < sizeof( strCell ) / sizeof( CString ) ; i++ )
		WriteExcelCell(strCell[i],strData[i]);


	PageSetup pageinfo=sheet.GetPageSetup();
/*	pageinfo.SetLeftMargin(0);
	pageinfo.SetRightMargin(0);
	pageinfo.SetTopMargin(0);
	pageinfo.SetBottomMargin(0);
*/
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
//	EndWaitCursor();
}

void COperatChargeRelateFee::WriteExcelCell(CString strCell, CString strData)
{
	Range vRange;
	Font font;
	vRange=sheet.GetRange(_O(strCell),_O(strCell)); // ҽ�ƻ���
	font=vRange.GetFont();
	font.SetName(_O(FONTNAME));
	font.SetSize(_O((short)STANDARDFONT));
	vRange.SetValue(COleVariant(strData));

}
