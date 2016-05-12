// his2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "his2.h"
#include "qiuXpButton.h"
#include "formMedlist.h"
#include "searchmed.h"
#include "gh.h"
#include "startdoctor.h"
#include "ghList.h"
#include "dialogRoleSet.h"
#include "employeeQuery.h"
#include "employeeRelateQuery.h"
#include "DSendNotify.h"
#include "QueryReadNotifyPeople.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "his2Doc.h"
#include "his2View.h"
#include "QiuXpButton.h"
#include "movekf.h"
#include "formRkList.h"
#include "formZkList.h"
#include "afxInet.h"
#include "modifymedRec.h"

#include "splash.h"
#include "logon.h"
#include "pandian.h"
#include "commonUse.h"
#include "commonUseQuery.h"
#include "pandianlist.h"
#include "GenericStockMed.h"
#include "breadMedlist.h"
#include "breakMedope.h"
#include "medcodebase.h"
#include "MedRoomCompare.h"
#include "EverydayConsumeList.h"
#include "BuySellStockList.h"
#include "relateCharge.h"
#include "dialogMeddl.h"
#include "dialogMedxl.h"
#include "passwordChange.h"
#include "QueryICList.h"
#include "logonList.h"
#include "treateList.h"
#include "DoctorWorkLoad.h"
#include "progress.h"
#include "RelateConsumeList.H"
#include "monthConsumeList.h"
#include "chartSell.h"
#include "yeardatacount.h"
#include "storeroomEdit.h"
#include "YearDataCountAnalyse.h"
#include "financeReport.h"
#include "otherDechargeQuery.h"

#include "otherDecharge.h"
#include "JiHuaWeDecharge.h"
#include "hos30Factory.h"
#include "Hos30Hospital.h"
#include "hos40Factory.h"
#include "HosDinner.h"
#include "hosElse.h"
#include "HosInstrumentGet.h"
#include "HosMedGet.h"
#include "HosModify.h"
#include "HosEmpEdu.h"
#include "HosEmpCheck.h"
#include "Hosplan.H"
#include "hosTuiXiu.h"

#include "accountScale.h"
#include "dechargeScale.h"
#include "accrualAdd.h"
#include "employeeDecharge.H"
#include "employeeBmp.h"
#include "WageInput.h"
#include "operatorSet.h"
#include "baseChargeSet.h"
#include "departSet.h"
#include "BaseOtherSickSet.h"
#include "standardSubsidySet.h"

#include "peculiarInput.h"
#include "empDechargeQuery.h"
#include "EmpUsedAccountCollect.h"
#include "newPersonalAddCash.h"
#include "empGetAccount.h"
#include "EmpBalanceCount.h"
#include "CashBuySellStock.h"
#include "doctorWorkOther.h"
#include "aboutCtrl.h"
#include "resideCheckIn.h"
#include "resideLocalSet.h"
#include "roomSet.h"
#include "resideBedset.h"
#include "resideList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHis2App

BEGIN_MESSAGE_MAP(CHis2App, CWinApp)
	//{{AFX_MSG_MAP(CHis2App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_MENU_MEDLIST, OnMenuMedlist)
	ON_COMMAND(ID_MENU_SEARCH_MED, OnMenuSearchMed)
	ON_COMMAND(ID_MENU_MOVE_KF, OnMenuMoveKf)
	ON_COMMAND(ID_MENU_DOCTOR_START, OnMenuDoctorStart)
	ON_COMMAND(ID_MENU_GH_LIST, OnMenuGhList)
	ON_COMMAND(ID_MENU_ROLE_SET, OnMenuRoleSet)
	ON_COMMAND(ID_MENU_CALULATE, OnMenuCalulate)
	ON_COMMAND(ID_MENU_EMPLOYEE, OnMenuEmployee)
	ON_COMMAND(ID_MENU_EMPLOYEE_RELATE, OnMenuEmployeeRelate)
	ON_COMMAND(ID_MENU_RK_QUERY, OnMenuRkQuery)
	ON_COMMAND(ID_MENU_ZK_QUERY, OnMenuZkQuery)
	ON_COMMAND(ID_MENU_SEND_NOTIFY, OnMenuSendNotify)
	ON_COMMAND(ID_MENU_ALREADY_SEND, OnMenuAlreadySend)
	ON_COMMAND(ID_MENU_DEL_ALL_NOTIFY, OnMenuDelAllNotify)
	ON_COMMAND(ID_MENU_PANDIAN, OnMenuPandian)
	ON_COMMAND(ID_MENU_OTHER_CONSUME, OnMenuOtherConsume)
	ON_COMMAND(ID_MENU_PANDIAN_QUERY, OnMenuPandianQuery)
	ON_COMMAND(ID_MENU_OTHER_CONSUME_QUERY, OnMenuOtherConsumeQuery)
	ON_COMMAND(ID_MENU_STOCK_GENERIC, OnMenuStockGeneric)
	ON_COMMAND(ID_MENU_BREAK_MED_LIST, OnMenuBreakMedList)
	ON_COMMAND(ID_MENU_SET_BREAK_MED, OnMenuSetBreakMed)
	ON_COMMAND(ID_MENU_CODEGYS, OnMenuCodegys)
	ON_COMMAND(ID_MENU_MEDCODE, OnMenuMedcode)
	ON_COMMAND(ID_MENU_MEDROOM_COMPARE, OnMenuMedroomCompare)
	ON_COMMAND(ID_MENU_MEDUSED_TABLE, OnMenuMedusedTable)
	ON_COMMAND(ID_MENU_BUY_SELL_STOCK, OnMenuBuySellStock)
	ON_COMMAND(ID_MENU_RELATE_CHARGE, OnMenuRelateCharge)
	ON_COMMAND(ID_MENU_MED_DL, OnMenuMedDl)
	ON_COMMAND(ID_MENU_MED_XL, OnMenuMedXl)
	ON_COMMAND(ID_MENU_PASSWORD_CHANGE, OnMenuPasswordChange)
	ON_COMMAND(ID_MENU_IC_QUERY, OnMenuIcQuery)
	ON_COMMAND(ID_MENU_SYSTEM_KILL, OnMenuSystemKill)
	ON_COMMAND(ID_MENU_ZL_LIST, OnMenuZlList)
	ON_COMMAND(ID_MENU_IMP, OnMenuImp)
	ON_COMMAND(ID_MENU_DOCTOR_WORKLOAD, OnMenuDoctorWorkload)
	ON_COMMAND(ID_MENU_COMMIT_PROGRAM, OnMenuCommitProgram)
	ON_COMMAND(ID_MENU_RELATE_AUTO_ADDCASH, OnMenuRelateAutoAddcash)
	ON_COMMAND(ID_MENU_RELATE_CONSUME, OnMenuRelateConsume)
	ON_COMMAND(ID_MENU_UPGRADE_PROGRAM, OnMenuUpgradeProgram)
	ON_COMMAND(ID_MENU_MED_USED_MONTH, OnMenuMedUsedMonth)
	ON_COMMAND(ID_MENU_SELL_CHART, OnMenuSellChart)
	ON_COMMAND(ID_MENU_YEAR_COUNTCUR, OnMenuYearCountcur)
	ON_COMMAND(ID_MENU_HOSPITAL_DEPART, OnMenuHospitalDepart)
	ON_COMMAND(ID_MENU_YEAR_CONSUME_ANA, OnMenuYearConsumeAna)
	ON_COMMAND(ID_MENU_FINANCE_REPORT, OnMenuFinanceReport)
	ON_COMMAND(ID_MENU_OHTER_DECHARGE, OnMenuOhterDecharge)
	ON_COMMAND(ID_MENU_MODIFY_MED_REC, OnMenuModifyMedRec)
	ON_COMMAND(ID_MENU_DA_BIN, OnMenuDaBin)
	ON_COMMAND(ID_MENU_EXTERN_JI_WE, OnMenuExternJiWe)
	ON_COMMAND(ID_MENU_HOS_DINNER, OnMenuHosDinner)
	ON_COMMAND(ID_MENU_HOS_ELSE, OnMenuHosElse)
	ON_COMMAND(ID_MENU_HOS_INSTRUMENT_GET, OnMenuHosInstrumentGet)
	ON_COMMAND(ID_MENU_HOS_MED_GET, OnMenuHosMedGet)
	ON_COMMAND(ID_MENU_HOS_MODIFY, OnMenuHosModify)
	ON_COMMAND(ID_MENU_30_ADD, OnMenu30Add)
	ON_COMMAND(ID_MENU_30_HOS, OnMenu30Hos)
	ON_COMMAND(ID_MENU_40_ADD, OnMenu40Add)
	ON_COMMAND(ID_MENU_HOS_EDU, OnMenuHosEdu)
	ON_COMMAND(ID_MENU_HOS_CHECK, OnMenuHosCheck)
	ON_COMMAND(ID_MENU_PLAN_PROCREATE, OnMenuPlanProcreate)
	ON_COMMAND(ID_MENU_HOS_LIXIU, OnMenuHosLixiu)
	ON_COMMAND(ID_MENU_HOS_TUIYANG, OnMenuHosTuiyang)
	ON_COMMAND(ID_MENU_HOS_GUOQIAN, OnMenuHosGuoqian)
	ON_COMMAND(ID_MENU_HOS_GANGSHANG, OnMenuHosGangshang)
	ON_COMMAND(ID_MENU_ACCOUNT_ADD, OnMenuAccountAdd)
	ON_COMMAND(ID_MENU_DECHARGE_SCALE, OnMenuDechargeScale)
	ON_COMMAND(ID_MENU_ACCRUAL_ADD, OnMenuAccrualAdd)
	ON_COMMAND(ID_MENU_DEPART_SET, OnMenuDepartSet)
	ON_COMMAND(ID_MENU_EMP_DECHARGE, OnMenuEmpDecharge)
	ON_COMMAND(ID_MENU_EMP_CASH_ADD, OnMenuEmpCashAdd)
	ON_COMMAND(ID_MENU_OPERATOR, OnMenuOperator)
	ON_COMMAND(ID_MENU_BASE_PROJECT_SET, OnMenuBaseProjectSet)
	ON_COMMAND(ID_MENU_BASE_SPECIF, OnMenuBaseSpecif)
	ON_COMMAND(ID_MENU_SPECIF_SET, OnMenuSpecifSet)
	ON_COMMAND(ID_MENU_PECULIAR_QUERY, OnMenuPeculiarQuery)
	ON_COMMAND(ID_MENU_ACCOUNT_USED_COUNT, OnMenuAccountUsedCount)
	ON_COMMAND(ID_MENU_QUERY_EMP_DECHARGE, OnMenuQueryEmpDecharge)
	ON_COMMAND(ID_MENU_MANUAL_ADD_CASH, OnMenuManualAddCash)
	ON_COMMAND(ID_MENU_EMP_GET, OnMenuEmpGet)
	ON_COMMAND(ID_MENU_EMP_BALANCE_COUNT, OnMenuEmpBalanceCount)
	ON_COMMAND(ID_MENU_CASH_PURCHASE, OnMenuCashPurchase)
	ON_COMMAND(ID_MENUITEM_DOCTOR_OTHER, OnMenuitemDoctorOther)
	ON_COMMAND(ID_MENU_RESIDE_CHECKIN, OnMenuResideCheckin)
	ON_COMMAND(ID_MENU_RESIDE_LOCAL, OnMenuResideLocal)
	ON_COMMAND(ID_MENU_RESIDE_ROOM, OnMenuResideRoom)
	ON_COMMAND(ID_MENU_RESIDE_BED, OnMenuResideBed)
	ON_COMMAND(ID_MENU_RESIDE_QUERY, OnMenuResideQuery)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHis2App construction
CFont CHis2App::fontTitle;


CHis2App::CHis2App()
{
	strVer.Format("6.01.04");
	CString user,pwd,serviceName;
	user="his";
	pwd="his";
	serviceName="hospital";
	CString ConnectParameter;// 系原来的连接字符串MSDAORA.1
//	strConn.Format("Provider=OraOLEDB.Oracle;\
		User ID=%s;Password=%s;Data Source=%s ",user,pwd,serviceName);

	strConn.Format("Provider=MSDAORA.1;\
		User ID=%s;Password=%s;Data Source=%s ",user,pwd,serviceName);
	
	titleBrush.CreateSolidBrush(RGB(58,165,110));
	pMedlist=NULL; //作为指向药品列表用
	search = NULL ; //作为搜索药品对话框使用
	pGhList=NULL;
	pRkList=NULL;
	pPDList=NULL; //盘点视图
	pCUList=NULL; //内部消耗视图
	pBuySellStock=NULL; //药品进销存列表 
	pTreateList=NULL;
	pICList=NULL;
	pResideList=NULL; //住院人员视图

	strLogID="";
	fontTitle.CreatePointFont(220,"宋体");
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHis2App object

CHis2App theApp;

/////////////////////////////////////////////////////////////////////////////
// CHis2App initialization
_Application app;
Workbooks books;
_Workbook book;
Worksheets sheets;
_Worksheet sheet;
COleVariant vOpt(DISP_E_PARAMNOTFOUND,VT_ERROR);

CFile fDebug;

BOOL CHis2App::InitInstance()
{
	AfxEnableControlContainer();


#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)


	if(!::GetModuleFileName(NULL,LoginInformation.path,MAX_PATH)){
		AfxMessageBox("您的应用程序可能放入的路径太深,请移动到根目录下再试...\n某些功能当前不可用...");
	}
	else
	{
		for(int x=strlen(LoginInformation.path); LoginInformation.path[x-1] != '\\'; x--);
		LoginInformation.path[x]=0;

	}
	CSplash startView;
	startView.DoModal();
	if(startView.timer_count != 1){
		if(startView.timer_count == 3)AfxMessageBox("初始化系统 COM 库失败,请检查系统 COM 配置是否有问题...");
		else AfxMessageBox("连接 Oracle 数据库失败,请检查网络和 Oracle 配置是否正确...");//,"Oracle 连接错误",MB_OK|MB_ICONWARNING);
		
		return false;
	}
	if(FAILED(recSet.CreateInstance( __uuidof( Recordset ))))
	{
		AfxMessageBox("初始化Recordset失败...");
		return false ;
	}

	strProject=COtherDecharge::GetStringTitle("SELECT ds2 FROM lsq_gh_type WHERE ds3='B' AND ds1='PROJECT' ");

	CLogon log2;
	if(log2.DoModal()==IDCANCEL)return false;

	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	
	// Parse command line for standard shell commands, DDE, file open
	m_nCmdShow=SW_SHOWMAXIMIZED;
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	
	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);


	pMainFrame->SetWindowText(strProject);
	pMainFrame->UpdateWindow();

//	OnMenuUpgradeProgram(); //进行版本升级

	UINT CheckNotify(LPVOID);
	AfxBeginThread(CheckNotify,NULL);
	
	CString path;
	path.Format("%s%s",LoginInformation.path,"\\debug.txt");

/*	//调试程序时用
	if( ! fDebug.Open(path,CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite  ) )
		AfxMessageBox("建立调试文件失败...");
	else fDebug.SeekToEnd();
*/
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	CAboutCtrl sh;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	CString strCredits = "\t版权所有，盗版必究\n\n"
				   "\r程序设计:\n\n"
				   "凌绍清 \n\n\r联系电话：13151344414\n\n"
				   "\r特别感谢:\n\n淮阴发电厂职工医院  陈  辉\n\n淮阴卷烟厂职工医院  郝寿萍\n\n淮阴发电厂信息中心  鲍学军\n\n淮阴卷烟厂信息中心\n\n"
				   "\rCopyright 2003-2005\n\r"
				   "\rAll right reserved.\n\r医疗信息管理系统解决方案　版本："+theApp.strVer;
				  
	sh.SetCredits(strCredits);
	sh.SetSubject("医疗信息管理系统解决方案  (2003 - 2005) 版本："+theApp.strVer+" ");
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX,IDC_ABOUTCTRL,sh);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CHis2App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CHis2App message handlers


void CHis2App::OnMenuMedlist() // 库房药品列表
{
	// TODO: Add your command handler code here
	if(pMedlist != NULL ){
		BringWindowToTop(hMedlist);
		ShowWindow(hMedlist,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CFormMedList));
	AddDocTemplate(pDocTemplate);
	this->pMedlist=pDocTemplate; 
	pMedlist->OpenDocumentFile(NULL);
	
}

void CHis2App::OnMenuSearchMed() 
{
	// TODO: Add your command handler code here
	if(pMedlist == NULL )OnMenuMedlist();

	BringWindowToTop(hMedlist);
	ShowWindow(hMedlist,SW_SHOWMAXIMIZED);
	
	if(search != NULL) {
		search->ShowWindow(SW_SHOW);
		return;
	}

	search =new CSearchMed;
	search->Create( IDD_QUERY_MED );
	search->ShowWindow(SW_SHOW);
	search->UpdateWindow();
}

void CHis2App::OnMenuMoveKf() 
{
	if(!AssertRole(ROLE_MED_ZK))return; 

	CMoveKf mkf;
	mkf.DoModal();
}



BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	fontTitle.CreatePointFont(140,"新宋体");
//	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
/*	CString strTitle;
	GetDlgItem(IDC_STATIC_1)->GetWindowText(strTitle);
	strTitle+="("+theApp.strVer+")";
	GetDlgItem(IDC_STATIC_1)->SetWindowText(strTitle);

	backBrush.CreateSolidBrush(RGB(0,0,132));
*/
	CBitmap bm;
	BITMAP sz;
	bm.LoadBitmap(IDB_BACKGROUND);
	bm.GetBitmap(&sz);

	MoveWindow(0,0,sz.bmWidth,sz.bmHeight);	

	GetDlgItem(IDC_ABOUTCTRL)->MoveWindow(0,0,sz.bmWidth,sz.bmHeight);
	CenterWindow();
	bm.DeleteObject();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/*
void CHis2App::OnMenuGh() 
{
	// TODO: Add your command handler code here
	CGh gh;
	gh.DoModal();
	
}
*/
void CHis2App::OnMenuDoctorStart()  //门诊服务系统
{
	// TODO: Add your command handler code here
	CStartDoctor start;
	start.DoModal();
}

void CHis2App::OnMenuGhList() 
{
	if(pGhList != NULL ){
		BringWindowToTop(hGhList);
		ShowWindow(hGhList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CGhList));
	AddDocTemplate(pDocTemplate);
	this->pGhList=pDocTemplate; 
	pGhList->OpenDocumentFile(NULL);
	// TODO: Add your command handler code here
	
}

void CHis2App::OnMenuRoleSet() 
{
	if(!AssertRole(ROLE_ROLE_SET))return; // 是否具有权限设置功能
	CDialogRoleset role;
	role.DoModal();
}

BOOL CHis2App::AssertRole(int role) //权限判断
{
	if(strRole.GetLength()<role){
		MessageBox(NULL,"您无权使用此项功能,如确需此项功能,请联系系统管理人员!!!","提示",MB_OK|MB_ICONINFORMATION|MB_TASKMODAL);
		return false;
	}
	if(strRole.Mid(role-1,1)=="1")return true;
	else {
		MessageBox(NULL,"您无权使用此项功能,如确需此项功能,请联系系统管理人员!!!","提示",MB_OK|MB_ICONINFORMATION|MB_TASKMODAL);
		return false;
	}
}

void CHis2App::OnMenuCalulate() //计算器
{
	::WinExec("calc.exe",SW_SHOW);
}

void CHis2App::OnMenuEmployee() 
{
	// TODO: Add your command handler code here
	CEmployeeQuery employe;
	employe.flag_EXIT=7777;

	employe.DoModal();
}

void CHis2App::OnMenuEmployeeRelate() 
{
	// TODO: Add your command handler code here
	CEmployeeRelateQuery qu;
	qu.flag_EXIT=7777;
	qu.DoModal();
}

void CHis2App::OnMenuRkQuery() //入库查询
{
	// TODO: Add your command handler code here
	if(pRkList != NULL ){
		BringWindowToTop(hRkList);
		ShowWindow(hRkList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CFormRkList));
	AddDocTemplate(pDocTemplate);
	this->pRkList=pDocTemplate; 
	pRkList->OpenDocumentFile(NULL);
	
}

void CHis2App::OnMenuZkQuery() 
{
	// TODO: Add your command handler code here
	if(pZkList != NULL ){
		BringWindowToTop(hZkList);
		ShowWindow(hZkList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CFormZkList));
	AddDocTemplate(pDocTemplate);
	this->pZkList=pDocTemplate; 
	pZkList->OpenDocumentFile(NULL);
	
}




void CHis2App::OnMenuSendNotify() //发送通知
{
	// TODO: Add your command handler code here
	if(  !AssertRole(ROLE_NOTIFY_SEND )  )return; // 是否具有删除通知功能
	CDSendNotify send;
	send.DoModal();
}

void CHis2App::OnMenuAlreadySend() 
{
	CQueryReadNotifyPeople query;
	query.DoModal();
}

void CHis2App::OnMenuDelAllNotify()  //通知情况全部删除
{
	if(  !AssertRole(ROLE_NOTIFY_DELETE)  )return; // 是否具有删除通知功能

	CString strSql;
	if( ::MessageBox(AfxGetMainWnd()->m_hWnd,"删除系统中所有 [通知信息] 吗??","删除",MB_OKCANCEL|MB_ICONWARNING) == IDOK ){
		try{
			strSql.Format("TRUNCATE TABLE lsq_notify_list");
			
			HospitalConnect->BeginTrans();
			//	AfxMessageBox(strSql);
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			
			strSql.Format("TRUNCATE TABLE lsq_notify_body " );
			//	AfxMessageBox(strSql);
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			
			HospitalConnect->CommitTrans();
		
			
		}
		catch(_com_error e)
		{
			AfxMessageBox("删除出错...");
			HospitalConnect->RollbackTrans();
			return ;
		}
		return ;
		
	}
}

void CHis2App::OnMenuPandian()  //药品盘点操作
{
	if(!AssertRole(ROLE_MED_CHECK_ACCOUNTS))return; // 是否具有盘点功能
	CPandian pan;
	pan.DoModal();
}

void CHis2App::OnMenuOtherConsume()  //其它消耗操作
{
	if(!AssertRole(ROLE_MED_OTHER_CONSUME))return; // 是否具有其它消耗功能
	CCommonUse cu; //公共使用
	cu.DoModal();
	
}

void CHis2App::OnMenuPandianQuery()  //盘点查询
{
	if(pPDList != NULL ){
		BringWindowToTop(hPDList);
		ShowWindow(hPDList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CPandianList) );
	AddDocTemplate(pDocTemplate);
	this->pPDList=pDocTemplate; 
	pPDList->OpenDocumentFile(NULL);
	
}

void CHis2App::OnMenuOtherConsumeQuery()  //其它消耗查询
{

	if(pCUList != NULL ){
		BringWindowToTop(hCUList);
		ShowWindow(hCUList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CCommonUseQuery) );
	AddDocTemplate(pDocTemplate);
	this->pCUList=pDocTemplate; 
	pCUList->OpenDocumentFile(NULL);
	
}

void CHis2App::OnMenuStockGeneric()  //根据上月计划自动生成当前计划
{
	if(!AssertRole(ROLE_STOCK_GENERIC))return; // 是否具有药品采购生成功能
	CGenericStockMed stockMed;
	stockMed.DoModal();
	
}

void CHis2App::OnMenuBreakMedList()  //报损药品查询
{
	if(pBMList != NULL ){
		BringWindowToTop(hBMList);
		ShowWindow(hBMList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CBreadMedList) );
	AddDocTemplate(pDocTemplate);
	this->pBMList=pDocTemplate; 
	pBMList->OpenDocumentFile(NULL);
	
}

void CHis2App::OnMenuSetBreakMed() 
{
	if(!theApp.AssertRole(ROLE_MED_BF))return; 
	CBreakMedOpe brea;
	brea.DoModal();
}

void CHis2App::OnMenuCodegys()  //供应商修改
{
	CCodeGysQuery gys;
	gys.DoModal();
	
}

void CHis2App::OnMenuMedcode()  //药品基本编码
{

	CMedCodeBase qu;
	qu.DoModal();
}

void CHis2App::OnMenuMedroomCompare()  //各药房库存数量对比表
{
	CMedRoomCompare mp;
	mp.DoModal();
	
}

void CHis2App::OnMenuMedusedTable()  //药品消耗明细表
{
	if(pConsume != NULL ){
		BringWindowToTop(hConsume);
		ShowWindow(hConsume,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CEverydayConsumeList));

	AddDocTemplate(pDocTemplate);
	this->pConsume=pDocTemplate; 
	pConsume->OpenDocumentFile(NULL);
	
}

void CHis2App::OnMenuBuySellStock() //药品进销存列表
{
	if(pBuySellStock != NULL ){
		BringWindowToTop(hBuySellStock);
		ShowWindow(hBuySellStock,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CBuySellStockList));

	AddDocTemplate(pDocTemplate);
	this->pBuySellStock=pDocTemplate; 
	pBuySellStock->OpenDocumentFile(NULL);
	
}
#include "BuySellStockList.h"

void CHis2App::OnMenuRelateCharge()  //供养亲属费用报销
{
	CRelateCharge re;
	re.DoModal();
	
}

void CHis2App::OnMenuMedDl() 
{
	if(!theApp.AssertRole(ROLE_MED_XL_MODIFY))return; 
	CDialogMedDL dl;
	dl.DoModal();
}

void CHis2App::OnMenuMedXl() 
{
	if(!theApp.AssertRole(ROLE_MED_DL_MODIFY))return; 
	CDialogMedXL xl;
	xl.DoModal();

}

void CHis2App::OnMenuPasswordChange() 
{
	CPasswordChange ch;
	ch.DoModal();
}

void CHis2App::OnMenuIcQuery() 
{
	if(pICList != NULL ){
		BringWindowToTop(hICList);
		ShowWindow(hICList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CQueryICList));

	AddDocTemplate(pDocTemplate);
	this->pICList=pDocTemplate; 
	pICList->OpenDocumentFile(NULL);
	
}

void CHis2App::OnMenuSystemKill()  //系统登录人员查询
{
	CLogonList list;
	list.DoModal();
}

void CHis2App::ClearLogInformation()
{
	CString strSql;
	try{
		HospitalConnect->BeginTrans();
		
		strSql.Format("INSERT INTO lsq_log_record \
			select rybm,name,logtime,sysdate,logid from lsq_log_operator  where logid='%s' ",\
			theApp.strLogID);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		
		strSql.Format("DELETE FROM lsq_log_operator where logid=%s ",theApp.strLogID);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();
	
	//	HospitalConnect->Close();
		
	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox(strSql);
		return;
	
	}		
}

void CHis2App::OnMenuZlList() //治疗情况查询
{
	if(pTreateList != NULL ){
		BringWindowToTop(hTreateList);
		ShowWindow(hTreateList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CTreateList));

	AddDocTemplate(pDocTemplate);
	this->pTreateList=pDocTemplate; 
	pTreateList->OpenDocumentFile(NULL);

	
}
#define _O(x) COleVariant(x)

void CHis2App::OnMenuImp() //导入
{
/*		app.CreateDispatch("excel.application");
		if(!app){
			AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
			return;
		}
		books=app.GetWorkbooks();
		book=books.Open("G:\\xx.xls",vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
		sheets=book.GetWorksheets();

	
	sheet=sheets.GetItem(COleVariant((short)1)); //sheet2 作为供养亲属报销打印报表
	CString str1,str2,str3,str4,str5,str6,str7,str8,strTemp		;
	Range vrange;
	HospitalConnect->BeginTrans();	
	for ( int i=1 ;i < 97 ;i++)
	{
		strTemp.Format("A%d",i);			
		vrange=sheet.GetRange(_O(strTemp),_O(strTemp));
		str1=(char*)_bstr_t(vrange.GetValue()); //bm

		strTemp.Format("B%d",i);			
		vrange=sheet.GetRange(_O(strTemp),_O(strTemp));
		str2=(char*)_bstr_t(vrange.GetValue()); //xm
	
		strTemp.Format("C%d",i);			
		vrange=sheet.GetRange(_O(strTemp),_O(strTemp));
		str3=(char*)_bstr_t(vrange.GetValue()); //xb
	
		strTemp.Format("D%d",i);			
		vrange=sheet.GetRange(_O(strTemp),_O(strTemp));
		str4=(char*)_bstr_t(vrange.GetValue()); //日期
		
		str5=str1.Left(str1.GetLength()-1); //卡号
	
		strTemp.Format("F%d",i);			
		vrange=sheet.GetRange(_O(strTemp),_O(strTemp));
		str6=(char*)_bstr_t(vrange.GetValue()); //性质
	
		strTemp.Format("H%d",i);			
		vrange=sheet.GetRange(_O(strTemp),_O(strTemp));
		str7=(char*)_bstr_t(vrange.GetValue()); //余额


		str8.Format("INSERT INTO lsq_test(bm,xm,xb,csriqi,xingzhi,kahao,yuer) \
			values('%s','%s','%s',to_date('%s','yyyy-mm-dd'),'%s','%s',to_number('%s','99999.99') )\
			",str1,str2,str3,str4,str6,str5,str7);
		HospitalConnect->Execute(_bstr_t(str8),NULL,adCmdText);

		
		
	}
	HospitalConnect->CommitTrans();
	AfxMessageBox("ok...");
*/
}

void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
/*	CDialog::OnLButtonDown(nFlags, point);

	PostMessage(WM_NCLBUTTONDOWN, 2, 0);
*/
	CDialog::OnCancel();
}

void CHis2App::OnMenuDoctorWorkload()  //医生工作量查询
{
	CDoctorWorkLoad work;
	work.strTitle="医生工作量情况统计表";
	work.DoModal();
	
}

void CHis2App::OnMenuCommitProgram()  //将程序当前内容提交入数据库
{
/*
	if(CHis2App::GetHttpFile("HTTP://10.43.34.200/database.txt.txt","c:\\test.txt"))
		AfxMessageBox("成功读取升级文件...");
*/	
}

void CHis2App::OnMenuRelateAutoAddcash()  //供养亲属年度自动充值
{
	if(!theApp.AssertRole(ROLE_RELATE_AUTO_ADDCASH))return; 

	CProgress pd;
	pd.strNotify="是否确定要进行年度结转充值,每年度只允许进行一次充值!!!";
	pd.pThreadFunction=CProgress::RelateAutoAddCash;
	pd.strView="正在进行自动充值,请稍候...";
	pd.DoModal();
}

void CHis2App::OnMenuRelateConsume() //家属帐户消耗情况
{
	CRelateConsumeList li;
	li.strTitle="供养亲属帐户情况明细表";
	li.DoModal();
}
/*
	HTTP 文件读取,用于软件自动升级

*/
#define   IDC_PROGRESS_EXCEL WM_USER+1211
BOOL CHis2App::GetHttpFile(CString strUrl,CString strFile,long fileLength)
{
	CInternetSession session;
	CInternetFile* file = NULL;

	CProgressEx pp;
	CRect r1(0,0,400,25);
	pp.Create(WS_CHILD |PBS_SMOOTH|WS_BORDER ,r1,AfxGetMainWnd()->GetActiveWindow(),IDC_PROGRESS_EXCEL);
	pp.UpdateWindow();
	pp.ShowWindow(SW_SHOW);
	pp.CenterWindow();
	pp.Invalidate();
	pp.SetRange32(0,fileLength );
	CString strTmp;
	pp.strView="正在连接升级文件!!";
	long i=0,len;

	try
	{
		// 试着连接到指定URL
		file = (CInternetFile*) session.OpenURL(strUrl,1,INTERNET_FLAG_TRANSFER_BINARY); 
	}
	catch (CInternetException* m_pException)
	{
		// 如果有错误的话，置文件为空
		file = NULL; 
		AfxMessageBox("打开升级文件位置出现错误,未能找到要升级的文件...");
		m_pException->Delete();
		return FALSE;
	}

	// 用dataStore来保存读取的文件
	CStdioFile dataStore;
	
	
	if (file)
	{
		BOOL bIsOk = dataStore.Open(strFile,
			CFile::modeCreate | CFile::modeWrite | CFile::typeBinary  );
		
		if (!bIsOk){
			AfxMessageBox("2.建立新文件出现错误...");
			return FALSE;
		}
		BYTE a[1024];	
		// 读写文件，直到为空
		while( (len=file->Read(a,1024)) != 0 ){
			dataStore.Write(a,len);
			pp.strView.Format("%2.0f%%",double(i++)/(fileLength/1024)*100);
			pp.SetPos(i*1024);
			
		}
		file->Close();
		dataStore.Close();
		delete file;
		CString strSql;
		strSql.Format("cmd /c Ren  ");
		strSql+=strFile+" his2.exe";
		WinExec(strSql,SW_HIDE);
		
	}
	else
	{
	//	dataStore.WriteString(_T("到指定服务器的连接建立失败..."));	
		AfxMessageBox("3.建立新文件出现错误...");
		return FALSE;
	}
	
	return TRUE;
}

void CHis2App::OnMenuUpgradeProgram()  //程序升级
{
	CString strSql,strTmp;
	long fileLength;
			//删除所有备份文件
	strSql.Format("cmd /c del /Q /F %s",LoginInformation.path);
	strSql+="*.bak";
	WinExec(strSql,SW_HIDE);

	try{
		strSql.Format("select ds1,ds3,n1 from LSQ_UPGRADE WHERE ds2='UPGRADE'  ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
	
			//版本号
			strSql=(char*)_bstr_t(recSet->GetCollect("ds3").vt==VT_NULL?" ":recSet->GetCollect("ds3"));
			strSql.Remove('.');
			strTmp=strVer;
			strTmp.Remove('.');

			if( atol(strSql) > atol(strTmp) ) // 如果版本大于当前版本,则进行升级...
			{
				strSql.Format("cmd /c Ren  %s",LoginInformation.path);
				strSql+="his2.exe *.bak";
				WinExec(strSql,SW_HIDE);
		
				strSql=(char*)_bstr_t(recSet->GetCollect("ds1").vt==VT_NULL?" ":recSet->GetCollect("ds1"));
				fileLength=atol((char*)_bstr_t(recSet->GetCollect("n1").vt==VT_NULL?" ":recSet->GetCollect("n1")));
				strTmp.Format("%s%s",LoginInformation.path,"his22.exe");
				recSet->Close();
			
				if(!GetHttpFile(strSql,strTmp,fileLength)){
					AfxMessageBox("升级失败...");
					recSet->Close();
					return;
				}
			
				Sleep(500);
				strSql.Format("%s%s",LoginInformation.path,"his2.exe");
				WinExec(strSql,SW_SHOW);
					
				ExitProcess(0);
			}
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}		
}
//月耗明细表
void CHis2App::OnMenuMedUsedMonth() 
{
	
	CMonthConsumeList list;
	list.strTitle="各库房月耗明细表";
	list.DoModal();
	
}

int CHis2App::GetMonthDays(int year, int month)
{
	if( month == 2 ) {
		if (  year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) )return 29; //闰年
		else return 28;
	}
	if ( month > 7){
		if( month % 2 == 0 ) return 31 ;
		else return 30;
	}
	else {
		if( month % 2 != 0 ) return 31;
		else return 30;
	}



}

void CHis2App::OnMenuSellChart() 
{
	CChartSell se;
	se.DoModal();
}

void CHis2App::OnMenuYearCountcur() 
{
	CYearDataCount data;
	data.DoModal();
}

void CHis2App::OnMenuHospitalDepart() 
{
	if(!theApp.AssertRole(ROLE_BASE_SET))return; 
	CStoreRoomEdit ed;
	ed.DoModal();
}

void CHis2App::OnMenuYearConsumeAna()  //年度就诊金额分析表
{
	CYearDataCountAnalyse	 ana;
	ana.DoModal();
}

void CHis2App::OnMenuFinanceReport()  //各类就诊人员财务报表
{
	CFinanceReport fr;
	fr.DoModal();
}

void CHis2App::OnMenuOhterDecharge()  //其它人员费用报销查询
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	COtherDechargeQuery od;
	od.DoModal();
	
}

void CHis2App::OnMenuModifyMedRec()  //药品修改明细表
{
	CModifyMedRec rec;
	rec.DoModal();
}

void CHis2App::OnMenuDaBin()  //大病医保外诊报销
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	COtherDecharge de;
	de.DoModal();
}

void CHis2App::OnMenuExternJiWe()  //计划外用工外诊报销
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CJiHuaWeDecharge de;
	de.DoModal();
}

void CHis2App::OnMenuHosDinner()  //医院招待费
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosDinner di;
	di.DoModal();
}

void CHis2App::OnMenuHosElse() //医院其他费用报销
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	// TODO: Add your command handler code here
	CHosElse di;
	di.DoModal();

}

void CHis2App::OnMenuHosInstrumentGet()  //器械购进
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosInstrumentGet di;
	di.DoModal();
}

void CHis2App::OnMenuHosMedGet()  //药品购进
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosMedGet di;
	di.DoModal();
}

void CHis2App::OnMenuHosModify() //医院器械修理费
{
	// TODO: Add your command handler code here
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosModify di;
	di.DoModal();
}

void CHis2App::OnMenu30Add()  //厂部30%提成
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHos30Factory di;
	di.DoModal();
}

void CHis2App::OnMenu30Hos() //医院30%奖励
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHos30Hospital di;
	di.DoModal();
}

void CHis2App::OnMenu40Add() //医院40%发展基金
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHos40Factory di;
	di.DoModal();
}

void CHis2App::OnMenuHosEdu() //医院教育经费
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	// TODO: Add your command handler code here
	CHosEmpEdu di;
	di.DoModal();
}

void CHis2App::OnMenuHosCheck() //体检费
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	// TODO: Add your command handler code here
	CHosEmpCheck di;
	di.DoModal();
}

void CHis2App::OnMenuPlanProcreate() 
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosPlan di;
	di.DoModal();
}

void CHis2App::OnMenuHosLixiu() 
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosTuiXiu di;
	di.iType=0; //离休
	di.DoModal();
	
}

void CHis2App::OnMenuHosTuiyang() 
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosTuiXiu di;
	di.iType=1; //退养
	di.DoModal();
	// TODO: Add your command handler code here
	
}

void CHis2App::OnMenuHosGuoqian() 
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosTuiXiu di;
	di.iType=2; //国前
	di.DoModal();
	// TODO: Add your command handler code here
	
}

void CHis2App::OnMenuHosGangshang() 
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosTuiXiu di;
	di.iType=3; //工伤
	di.DoModal();
	// TODO: Add your command handler code here
	
}

void CHis2App::OnMenuAccountAdd()  //职工比例充值维护
{
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CAccountScale di;
	di.DoModal();
}

void CHis2App::OnMenuDechargeScale() //报销比例维护
{
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CDechargeScale di;
	di.DoModal();
}

void CHis2App::OnMenuAccrualAdd()  //利息结算
{
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CAccrualAdd di;
	di.DoModal();
}

void CHis2App::OnMenuDepartSet() 
{
	if(!theApp.AssertRole(ROLE_BASE_SET))return; 
	CDepartSet di;
	di.gstrSql="SELECT distinct 所属部 FROM 厂部门表 order by 所属部";
	di.strTitle="厂部门表设置";
	di.DoModal();
}

void CHis2App::OnMenuEmpDecharge() //补充保险人员报销
{
//	CEmployeeDecharge de;
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CEmployeeBmp de;
	de.DoModal();
	
}

void CHis2App::OnMenuEmpCashAdd()  //帐户充值汇总
{
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CWageInput di;
	di.DoModal();
}

void CHis2App::OnMenuOperator() 
{
	if(!theApp.AssertRole(ROLE_BASE_SET))return; 
	COperatorSet di;
	di.gstrSql="SELECT kfmc FROM storeRoom order by kfmc ";

	di.DoModal();
}

void CHis2App::OnMenuBaseProjectSet()  //治疗项目设置
{
	if(!theApp.AssertRole(ROLE_BASE_SET))return; 

	CBaseChargeSet di;
	di.strTitle="治疗项目基础信息设置";
	di.gstrSql="SELECT distinct  费用大类 FROM 费用项目表 order by 费用大类 ";
	di.DoModal();
	
}

void CHis2App::OnMenuBaseSpecif()  //其它人员编辑
{
	if(!theApp.AssertRole(ROLE_BASE_SET))return; 
	CBaseOtherSickSet di;
	di.DoModal();
}

void CHis2App::OnMenuSpecifSet()  //特殊人员性质设定
{
	if(!theApp.AssertRole(ROLE_BASE_SET))return; 
	CStandardSubsidySet di;
	di.DoModal();
}

void CHis2App::OnMenuPeculiarQuery()  //特殊人员充值查询
{
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CPeculiarInput di;
	di.DoModal();
	
}
void CHis2App::OnMenuAccountUsedCount()  //帐户使用汇总
{
	CEmpUsedAccountCollect di;
	di.DoModal();
	
}

void CHis2App::OnMenuQueryEmpDecharge()  //补充保险查询
{
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CEmpDechargeQuery di;
	di.DoModal();
	
}

void CHis2App::OnMenuManualAddCash()  //手动充值
{
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CNewPersonalAddCash di;
	di.DoModal();
	
}

void CHis2App::OnMenuEmpGet()  //补充保险基金征集表
{
	CEmpGetAccount di;
	di.DoModal();
}

void CHis2App::OnMenuEmpBalanceCount()  //补充保险结算表
{
	CEmpBalanceCount di;
	di.DoModal();
	
}

void CHis2App::OnMenuCashPurchase()  //金额关系进销存
{
	CCashBuySellStock di;
	di.DoModal();
	
}

void CHis2App::OnMenuitemDoctorOther() //医生化验费情况统计
{

	CDoctorWorkOther ot;
	ot.DoModal();
	
}

void CHis2App::OnMenuResideCheckin() //住院登记
{
	CResideCheckIn ci;
	ci.DoModal();
}

void CHis2App::OnMenuResideLocal() //病区设置
{
	CResideLocalSet ls;
	ls.DoModal();
}

void CHis2App::OnMenuResideRoom() //房间设置
{
	CRoomSet rs;
	rs.DoModal();
}

void CHis2App::OnMenuResideBed() //病床设置
{
	CResideBedSet bs;
	bs.DoModal();
	
}

void CHis2App::OnMenuResideQuery() //住院人员信息查询
{

	if(pResideList != NULL ){
		BringWindowToTop(hResideList);
		ShowWindow(hResideList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CResideList));
	AddDocTemplate(pDocTemplate);
	this->pResideList=pDocTemplate; 
	pResideList->OpenDocumentFile(NULL);
	
}
