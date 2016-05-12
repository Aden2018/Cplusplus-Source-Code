// ResideCheckIn.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "ResideCheckIn.h"
#include "QueryRybm.h"
#include "resideBedSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResideCheckIn dialog


CResideCheckIn::CResideCheckIn(CWnd* pParent /*=NULL*/)
	: CDialog(CResideCheckIn::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResideCheckIn)
	m_date = COleDateTime::GetCurrentTime();
	m_age = 0;
	m_strHome = _T("");
	m_strill = _T("");
	m_strPhone = _T("");
	m_dbPrice = 0.0;
	m_dbRebate = 1;
	m_strRemark = _T("");
	m_strWork = _T("");
	m_strXm = _T("");
	//}}AFX_DATA_INIT
	m_strDoctorName="";
	m_strDoctorBm="";
	

}


void CResideCheckIn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResideCheckIn)
	DDX_Control(pDX, IDOK_PRINT, m_okprint);
	DDX_Control(pDX, IDC_COMBO_RE_XB, m_cSex);
	DDX_Control(pDX, IDC_EDIT_RE_DOCTOR, c_doctor);
	DDX_Control(pDX, IDC_BUTTON_RE_DOCTOR, m_doctor);
	DDX_Control(pDX, IDC_BUTTON_RE_BED, m_bed);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_Text(pDX, IDC_EDIT_RE_AGE, m_age);
	DDX_Text(pDX, IDC_EDIT_RE_HOME, m_strHome);
	DDX_Text(pDX, IDC_EDIT_RE_ILL_DESC, m_strill);
	DDX_Text(pDX, IDC_EDIT_RE_PHONE, m_strPhone);
	DDX_Text(pDX, IDC_EDIT_RE_PRICE, m_dbPrice);
	DDX_Text(pDX, IDC_EDIT_RE_REBATE, m_dbRebate);
	DDX_Text(pDX, IDC_EDIT_RE_REMARK, m_strRemark);
	DDX_Text(pDX, IDC_EDIT_RE_WORK, m_strWork);
	DDX_Text(pDX, IDC_EDIT_RE_XM, m_strXm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResideCheckIn, CDialog)
	//{{AFX_MSG_MAP(CResideCheckIn)
	ON_BN_CLICKED(IDC_BUTTON_RE_DOCTOR, OnButtonReDoctor)
	ON_BN_CLICKED(IDC_BUTTON_RE_BED, OnButtonReBed)
	ON_EN_KILLFOCUS(IDC_EDIT_RE_DOCTOR, OnKillfocusEditReDoctor)
	ON_EN_SETFOCUS(IDC_EDIT_RE_DOCTOR, OnSetfocusEditReDoctor)
	ON_BN_CLICKED(IDOK_PRINT, OnPrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResideCheckIn message handlers

BOOL CResideCheckIn::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN ) pMsg->wParam=VK_TAB;
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CResideCheckIn::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString strTitle="住院登记操作";
	SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&CHis2App::fontTitle);
	InitControl();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CResideCheckIn::OnButtonReDoctor()  //查找医生
{
	CQueryRybm rybm;
	if(rybm.DoModal()==IDOK){
		m_strDoctorBm=rybm.strNum;	//医生编码
		m_strDoctorName=rybm.strName;  //医生姓名
		c_doctor.SetWindowText(m_strDoctorName);   
	}	
}

void CResideCheckIn::OnButtonReBed() 
{
	CResideBedSet bs;
	bs.DIALOG_FLAG=CResideBedSet::DIALOG_SELECT;
	if( bs.DoModal() ==IDOK) {
		m_strBedCode=bs.strBedCode;
		m_strBedName=bs.strBedName;
		GetDlgItem(IDC_EDIT_RE_BED)->SetWindowText(m_strBedName);
	}
}

void CResideCheckIn::OnKillfocusEditReDoctor() 
{
	CString str1,strSql;
	c_doctor.GetWindowText(str1);
	if( m_strDoctorBm == str1 ){
		c_doctor.SetWindowText(m_strDoctorName);
		return;
	}
	else if (str1.IsEmpty() ){
		m_strDoctorBm=m_strDoctorName="";
		return;
	}
	strSql.Format("select NVL(name,'') NAME from operator where rybm='%s' ",str1);
	m_strDoctorName=COtherDecharge::GetStringTitle(strSql);
	if( m_strDoctorName.IsEmpty() ) 
	{
		m_strDoctorBm="";
		c_doctor.SetWindowText(m_strDoctorName);
		c_doctor.SetFocus();
	}
	else
	{
		c_doctor.SetWindowText(m_strDoctorName);
		m_strDoctorBm=str1;
	}
}

void CResideCheckIn::OnSetfocusEditReDoctor() 
{
	c_doctor.SetWindowText(m_strDoctorBm);	
}

void CResideCheckIn::OnOK() 
{
	if( ! CheckAvail() ) return;
	CString strSql;
	CString strSex;
	m_cSex.GetLBText(m_cSex.GetCurSel(),strSex);
	//生成的序列号为IP的最后一位扩展成3位,然后与当前时间组成序列号

	strSql.Format(" INSERT INTO lsq_reside_hos ( xm,xb,doctor,bed_id,age,work_addr,home_addr,ill_desc,\
		rq,price,serial,chk ,rec_bm,rec_name,phone,doctorName ) values('%s','%s','%s','%s',%d,'%s','%s','%s',\
		sysdate ,%.2f,'%s', Encrypt(%.2f),'%s','%s' ,'%s','%s' ) ",\
		m_strXm,strSex,m_strDoctorBm,m_strBedCode,m_age,m_strWork,m_strHome,m_strill,\
		m_dbPrice,strSerial,m_dbPrice,LoginInformation.user_code,LoginInformation.user,m_strPhone,m_strDoctorName );
//	AfxMessageBox(strSql);
	if ( COtherDecharge::WriteSQL(strSql) ){
		AfxMessageBox("住院写入成功");
		InitControl();
	}
	else AfxMessageBox("住院写入失败");

}

void CResideCheckIn::InitControl()
{
	m_age=0;
	m_strXm="";
	m_strWork="";
	m_strPhone="";
	m_strHome="";
	m_strill="";
	m_cSex.SetCurSel(0);
	c_doctor.SetWindowText("");
	m_dbPrice=0.0;
	m_dbRebate=1;
	m_strRemark="";
	m_strBedCode="";
	m_strBedName="";
	GetDlgItem(IDC_EDIT_RE_BED)->SetWindowText(m_strBedName);
	m_strDoctorBm="";
	m_strDoctorName="";

	 strSerial="H"+COtherDecharge::GetStringTitle("select to_char(sysdate,'yyyymmddhh24miss')|| \
		Ltrim(to_char(substr( sys_context('USERENV','ip_address'),instr( sys_context('USERENV','ip_address') ,'.',-1,1)+1),'009')) \
		from dual")+LoginInformation.user_code;

	UpdateData(false);
}

void CResideCheckIn::OnPrint()  //住院打印
{
	if( ! CheckAvail() ) return;
#define _O(x) COleVariant(x)

extern _Application app;
extern Workbooks books;
extern _Workbook book;
extern Worksheets sheets;
extern _Worksheet sheet;
extern COleVariant vOpt;
	CString strCurDate;
	strCurDate=m_date.Format("%Y-%m-%d");
	BeginWaitCursor();

	CString strFileName;
	strFileName.Format("%s",LoginInformation.path); //根据数据库中记录的文件来选择要输出的EXCEl
	strFileName+=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_upgrade WHERE ds2='RESIDEHOS_PRINT_FILE' ");

	app.CreateDispatch("excel.application");
	if(!app){
		AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
		return;
	}
	books=app.GetWorkbooks();
	book=books.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	sheets=book.GetWorksheets();

	sheet=sheets.GetItem(COleVariant((short)1));

	app.SetVisible(true); //显示
	CString strSex,strPrice,strDate;
	m_cSex.GetLBText(m_cSex.GetCurSel(),strSex);
	strPrice.Format("%.2f",m_dbPrice);
	CString str[]={ 
		LoginInformation.user,  //操作人姓名
		strSerial,				//登记序列号
		m_strXm,				//病人姓名
		strSex,					//性别
		m_strBedName,			//病床名称
		m_strDoctorName,		//诊断医生名称
		m_strHome,				//家庭住址
		m_strPhone,				//电话
		m_strWork,				//工作单位
		m_strill,				//病情描述
		strPrice,				//首次交纳的金额
		strCurDate				

	};

	SetValue(sheet,sizeof(str)/sizeof(CString),str);
	
//Call VBA macro
	app.Run(COleVariant("thisWorkBook.Print_reside_Hos"),vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
		vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
		vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt );
/*	
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();

	book.ReleaseDispatch();
	books.ReleaseDispatch();

	app.ReleaseDispatch();
	app.Quit();
*/	
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();

	book.ReleaseDispatch();
	books.ReleaseDispatch();

	app.ReleaseDispatch();

	EndWaitCursor();	
}





void CResideCheckIn::SetValue(_Worksheet &sheet, int count, CString *pStr)
{
	Range vRange;
	CString cell;
	
	for (  int i =0 ; i < count ; i ++ ){
		cell.Format("A%d",i+1);
		vRange=sheet.GetRange(_O(cell),_O(cell)); //单据
		vRange.SetValue(COleVariant(pStr[i]));
	}

}

BOOL CResideCheckIn::CheckAvail()
{
	UpdateData();
	if( m_strXm.IsEmpty() || m_cSex.GetCurSel()==CB_ERR || m_strBedCode.IsEmpty() || m_strDoctorBm.IsEmpty() ){
		AfxMessageBox("请将必要信息填写完整");
		return false;
	}
	return true;
}
