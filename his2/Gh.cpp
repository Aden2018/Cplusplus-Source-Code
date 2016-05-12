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
//		修改记录:
//			作者:凌绍清							2005-02-26 10:00			
//------------------------------------------------------------------------------------
//			将挂号中带入职工性质(在职,建国前退休,建国后退休),便于以后统计
//		并将原来查询中( 类别 not in ('消户','离休') )更换成( 类别='参保')
//		含义相同,但可以改善SQL查询性能,在 CGh中新增一public CString strWorkType
//		变量,作为记录职工性质用.
//------------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////

const char EMPLOYEE[]="补充保险";
const char GENERIC[]="社会就诊";
const char RELATE[]="供养亲属";
const char NOWORK[]="离休人员";
const char IC[]="基本保险";

const char GAOQIAN[]="国前职工";
const char GANGSHANG[]="工伤人员";
const char TUIYANG[]="退养人员";

CGh::CGh(CWnd* pParent /*=NULL*/)
	: CDialog(CGh::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGh)
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"新宋体");
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
	
	c_type.SetCurSel(0); //default 补充保险
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

		strSql.Format("select ds1,ds3  from lsq_upgrade WHERE ds2='GH_TYPE' and n2=1 order by n1 " ); // ds1 对外显示用 ds3 对内操作用
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
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}	
	

	c_sex.SetCurSel(2) ;//不明确
	c_type.SetCurSel(1);//补充保险
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGh::OnButtonGetinformation()  /*根据所选类型,激活不同窗口*/
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
				if( strSql== "男" )c_sex.SetCurSel(0);
				else if(strSql== "女")c_sex.SetCurSel(1);
				else c_sex.SetCurSel(2);
				strDate[0]=rybm.strDate[0];
				strDate[1]=rybm.strDate[1];
				strWorkType=infor[7]; //职工性质
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
				if( strSql== "男" )c_sex.SetCurSel(0);
				else if(strSql== "女")c_sex.SetCurSel(1);
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
				if( strSql== "男" )c_sex.SetCurSel(0);
				else if(strSql== "女")c_sex.SetCurSel(1);
				else c_sex.SetCurSel(2);
				
				c_name.SetWindowText(strName);
				
			}
		}
		
		
		return;
	}
	else if( strType== GAOQIAN || strType == GANGSHANG || strType == TUIYANG )//国前职工
	{
		COtherSickQuery other;
		other.p=this;
	
		if(strType == GAOQIAN )
		{
			other.strSql.Format("SELECT * from OTHERSICK WHERE LB='建国前老工人' ");
			other.strTitle="建国前老工人信息";
		}
		else if ( strType == GANGSHANG )
		{
			other.strSql.Format("SELECT * From OtherSick Where LB='工伤人员' ");
			other.strTitle="工伤人员信息";
		
		}
		else 
		{
			other.strSql.Format("SELECT * FROM OtherSick Where LB='退养人员' ");
			other.strTitle="退养人员信息";

		}

		if(other.DoModal()==IDOK){
			strName=other.strName;
			strKH=other.strKH;
			c_name.SetWindowText(strName);
			if(other.strSex == "男" ) c_sex.SetCurSel(0);
			else if(other.strSex == "女" ) c_sex.SetCurSel(1);
			else c_sex.SetCurSel(2);
		}


	}
	else if( strType == IC || strType== "特定门诊"  || strType == "居民统筹" || strType== "家庭病床")
	{
		CBasisInsureList qu;
		qu.DoModal();
	
		strName=qu.strName;
		strKH=qu.strKH;
		c_name.SetWindowText(strName);
	
		if(qu.strSex == "男" ) c_sex.SetCurSel(0);
		else if(qu.strSex == "女" ) c_sex.SetCurSel(1);
		


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
const char EMPLOYEE[]="补充保险";
const char GENERIC[]="社会就诊";
const char RELATE[]="供养亲属";
const char NOWORK[]="离休人员";
const char IC[]="基本保险";

const char GAOQIAN[]="国前职工";
const char GANGSHANG[]="工伤人员";
const char TUIYANG[]="退养人员";

*/

void CGh::OnOK() 
{
	if(!theApp.AssertRole(ROLE_STARTDOCTOR_GH))return ;	

	CString strType,str1,strGHF,strSex;
	c_name.GetWindowText(strName); //姓名
//	c_type.GetLBText(c_type.GetCurSel(),strType); //挂号类型
	strType=arrWorkType[c_type.GetCurSel()];
	c_ghf.GetWindowText(strGHF); //挂号费
	c_sex.GetLBText(c_sex.GetCurSel(),strSex); //性别
	int year=COleDateTime::GetCurrentTime().GetYear();

	
	try{
		
//{"所属部","卡号","姓名","性别","出生日期","工作日期",	"结存金额","工作性质"}
		if(strType == EMPLOYEE){  //补充保险
			if(strKH.IsEmpty()){
				AfxMessageBox("请先选择挂号人员名单...");
				return;
			}else
			{
			
			str1.Format("类型: %s\n\n姓名: %s    年龄/工龄: %d / %d \n\n帐号余额: %s\n\n挂号成功",\
				strType,strName,year-atol(strDate[0].Left(4)),year-atol(strDate[1].Left(4)),infor[6]);
		
			}
		}
		else if(strType == RELATE){ //供养亲属
			if(strKH.IsEmpty() ) {
				AfxMessageBox("先挂号...");
				return;
			}
			else 
				str1.Format("类型: %s\n\n姓名: %s\n\n帐号余额: %s\n\n供养人: %s\n\n挂号成功",\
				strType,strName,infor[5],infor[6]);

					
		}
		else if(strType == NOWORK ) //离休人员
		{
			if(strKH.IsEmpty() ) {
				AfxMessageBox("先挂号...");
				return;
			}
			else 
				str1.Format("类型: %s\n\n姓名: %s\n\n报销比例: 100%\n\n挂号成功",\
				strType,strName);
		}
		else if(strType == IC || strType== "特定门诊" || strType=="居民统筹" || strType=="家庭病床" ) //医保人}}员
		{
			if( ! GetBaseRy() )return;
			strIC.Format("用户名: %s /%s ,是否挂号???",strName,infor[0]);
			if(::MessageBox(this->m_hWnd,strIC,"",MB_OKCANCEL) != IDOK){
				return;
			}

			str1.Format("类型: 医保人员\n\n姓名: %s\n\n挂号成功",strName);

		}
//{"BM","姓名","性别","性质","报销比例"};
		else if( strType ==GAOQIAN ) //建国前职工 
		{
			if(strKH.IsEmpty()){
				AfxMessageBox("请先选择建国前的职工");
				return;
			}else
			{
				strType="建国前老工人";  //为了和以前的同步,将其改为"建国前老工人"

				str1.Format("类型: 建国前职工\n\n姓名: %s \n\n报销比例: %s%%\n\n挂号成功",\
				strName,infor[4]);

			}

		}
		else if( strType == GANGSHANG ) //工伤
		{
			if(strKH.IsEmpty()){
				AfxMessageBox("请先选择工伤的职工");
				return;
			}else
				str1.Format("类型: 工伤人员\n\n姓名: %s \n\n报销比例: %s%%\n\n挂号成功",\
				strName,infor[4]);



		}else if( strType == TUIYANG ) //退养
		{
			if(strKH.IsEmpty()){
				AfxMessageBox("请先选择工伤的职工");
				return;
			}else
				str1.Format("类型: 退养人员\n\n姓名: %s \n\n报销比例: %s%%\n\n挂号成功",\
				strName,infor[4]);

		}
		else { // if (strType == GENERIC ){ //社会就诊
			c_name.GetWindowText(strName);
			if(strName.IsEmpty() ){
				AfxMessageBox("先输入姓名...");
				return;
			}
			strKH=strSex;			
			str1.Format("类型: %s\n\n姓名: %s\n\n挂号成功 ",strType,strName);

		}

/*		
const char IC[]="基本保险";

const char GAOQIAN[]="国前职工";
const char GANGSHANG[]="工伤人员";
const char TUIYANG[]="退养人员";
*/	
		if( !(strType == EMPLOYEE) )strWorkType="";

		strSql.Format("INSERT INTO ItemRegisterTou (danjuhao,riqi,sickbm,sickname,\
				挂号员,挂号员名,GHTYPE,GHF,ds1) values('%s',TRUNC(sysdate,'dd'),'%s','%s',\
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
		AfxMessageBox("检查系统中的SQL有无错误...");
		HospitalConnect->RollbackTrans();
		return;
	}
	c_type.SetCurSel(1) ;//补充保险
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
	
	if( strSql == IC || strSql== "特定门诊" || strSql == "居民统筹" || strSql == "家庭病床" ){
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
	c_type.GetLBText(c_type.GetCurSel(),strType); //挂号类型
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
		strSql.Format("select NVL(姓名,' ') 姓名,NVL(性别,' ') 性别 from  医保人员列表 where 卡号='%s' ",strKH);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			strName=(char*) _bstr_t(recSet->GetCollect("姓名"));
			infor[0]=(char*)_bstr_t(recSet->GetCollect("性别"));
			recSet->Close();
		}
		else {
			recSet->Close();

			if(::MessageBox(this->m_hWnd,"当前人员库中不存在,是否添加 ??? ","提示",MB_OKCANCEL)==IDOK){
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
		AfxMessageBox("查询SQL出错...");
		return false;


	}
	return true;

}

void CGh::OnGetEmployeeInformation()
{
//{"所属部","卡号","姓名","性别","出生日期","工作日期","结存金额","工作性质"}	
	CString strType;
	c_type.GetLBText(c_type.GetCurSel(),strType);
	c_name.GetWindowText(strKH);

	
	try{	
		if(strType == EMPLOYEE || strType== RELATE || strType == NOWORK ){
			if(strType == EMPLOYEE)	{
				strSql.Format("select NVL(姓名,' ') as NAME,NVL(性别,'不明确') as SEX \
					,NVL(结存金额,0) AS YUER ,NVL(工作性质,'') as TYPE,出生日期 as birthday,\
					工作日期 as workday from 职工基本情况表 e1,厂部门表 e2 where  e1.部门编码=e2.部门编码 \
					and 卡号 = '%s' and 类别='参保'  ",strKH); //not in('消户','离休')
			
				recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
				if(!recSet->adoEOF){
					strName=(char*)_bstr_t(recSet->GetCollect("NAME"));
					strSql=(char*)_bstr_t(recSet->GetCollect("SEX"));
					infor[6]=(char*)_bstr_t(recSet->GetCollect("YUER"));
					if( strSql== "男" )c_sex.SetCurSel(0);
					else if(strSql== "女")c_sex.SetCurSel(1);
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
				//={"TEMP","编码","姓名","性别","供养性质","余额","供养人","所属部","工作性质"};
				
				strSql.Format("select * from 职工基本情况表 e1,厂部门表 e2,codeQingShu e3\
					where e1.部门编码=e2.部门编码 and e3.kahao=e1.卡号 and \
					e3.bm='%s' AND 类别 != '消户' ",strKH);
				recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
				
				if(!recSet->adoEOF){
					strName=(char*)_bstr_t(recSet->GetCollect("XM"));
					strSql=(char*)_bstr_t(recSet->GetCollect("XB"));
					infor[5]=(char*)_bstr_t(recSet->GetCollect("YUER"));
					infor[6]=(char*)_bstr_t(recSet->GetCollect("姓名"));
					if( strSql== "男" )c_sex.SetCurSel(0);
					else if(strSql== "女")c_sex.SetCurSel(1);
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
			else { //离休人员查阅
				strSql.Format("select NVL(姓名,' ') as NAME,NVL(性别,'不明确') as SEX \
					from 职工基本情况表 e1,厂部门表 e2 where  e1.部门编码=e2.部门编码 \
					and 卡号 = '%s' and 类别 ='离休' ",strKH);
				recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
				if(!recSet->adoEOF){
					strName=(char*)_bstr_t(recSet->GetCollect("NAME"));
					strSql=(char*)_bstr_t(recSet->GetCollect("SEX"));
					if( strSql== "男" )c_sex.SetCurSel(0);
					else if(strSql== "女")c_sex.SetCurSel(1);
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
		else if( strType== GAOQIAN || strType == GANGSHANG || strType == TUIYANG )//国前职工
		{
			if(strType == GAOQIAN )
				strSql.Format("SELECT * from OTHERSICK WHERE LB='建国前老工人' AND BM='%s' ",strKH);
			else if ( strType == GANGSHANG )
				strSql.Format("SELECT * From OtherSick Where LB='工伤人员' AND BM='%s' ",strKH);
			else 
				strSql.Format("SELECT * FROM OtherSick Where LB='退养人员' AND BM='%s' ",strKH);
			
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){
				strName=(char*)_bstr_t(recSet->GetCollect("XM"));
				strSql=(char*)_bstr_t(recSet->GetCollect("XB"));
				if(strSql == "男" ) c_sex.SetCurSel(0);
				else if(strSql == "女" ) c_sex.SetCurSel(1);
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
		//else if(strType == IC || strType== "特定门诊" )
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
