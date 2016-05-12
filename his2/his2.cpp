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
	CString ConnectParameter;// ϵԭ���������ַ���MSDAORA.1
//	strConn.Format("Provider=OraOLEDB.Oracle;\
		User ID=%s;Password=%s;Data Source=%s ",user,pwd,serviceName);

	strConn.Format("Provider=MSDAORA.1;\
		User ID=%s;Password=%s;Data Source=%s ",user,pwd,serviceName);
	
	titleBrush.CreateSolidBrush(RGB(58,165,110));
	pMedlist=NULL; //��Ϊָ��ҩƷ�б���
	search = NULL ; //��Ϊ����ҩƷ�Ի���ʹ��
	pGhList=NULL;
	pRkList=NULL;
	pPDList=NULL; //�̵���ͼ
	pCUList=NULL; //�ڲ�������ͼ
	pBuySellStock=NULL; //ҩƷ�������б� 
	pTreateList=NULL;
	pICList=NULL;
	pResideList=NULL; //סԺ��Ա��ͼ

	strLogID="";
	fontTitle.CreatePointFont(220,"����");
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
		AfxMessageBox("����Ӧ�ó�����ܷ����·��̫��,���ƶ�����Ŀ¼������...\nĳЩ���ܵ�ǰ������...");
	}
	else
	{
		for(int x=strlen(LoginInformation.path); LoginInformation.path[x-1] != '\\'; x--);
		LoginInformation.path[x]=0;

	}
	CSplash startView;
	startView.DoModal();
	if(startView.timer_count != 1){
		if(startView.timer_count == 3)AfxMessageBox("��ʼ��ϵͳ COM ��ʧ��,����ϵͳ COM �����Ƿ�������...");
		else AfxMessageBox("���� Oracle ���ݿ�ʧ��,��������� Oracle �����Ƿ���ȷ...");//,"Oracle ���Ӵ���",MB_OK|MB_ICONWARNING);
		
		return false;
	}
	if(FAILED(recSet.CreateInstance( __uuidof( Recordset ))))
	{
		AfxMessageBox("��ʼ��Recordsetʧ��...");
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

//	OnMenuUpgradeProgram(); //���а汾����

	UINT CheckNotify(LPVOID);
	AfxBeginThread(CheckNotify,NULL);
	
	CString path;
	path.Format("%s%s",LoginInformation.path,"\\debug.txt");

/*	//���Գ���ʱ��
	if( ! fDebug.Open(path,CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite  ) )
		AfxMessageBox("���������ļ�ʧ��...");
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
	CString strCredits = "\t��Ȩ���У�����ؾ�\n\n"
				   "\r�������:\n\n"
				   "������ \n\n\r��ϵ�绰��13151344414\n\n"
				   "\r�ر��л:\n\n�������糧ְ��ҽԺ  ��  ��\n\n�������̳�ְ��ҽԺ  ����Ƽ\n\n�������糧��Ϣ����  ��ѧ��\n\n�������̳���Ϣ����\n\n"
				   "\rCopyright 2003-2005\n\r"
				   "\rAll right reserved.\n\rҽ����Ϣ����ϵͳ����������汾��"+theApp.strVer;
				  
	sh.SetCredits(strCredits);
	sh.SetSubject("ҽ����Ϣ����ϵͳ�������  (2003 - 2005) �汾��"+theApp.strVer+" ");
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


void CHis2App::OnMenuMedlist() // �ⷿҩƷ�б�
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
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
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
	
//	fontTitle.CreatePointFont(140,"������");
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
void CHis2App::OnMenuDoctorStart()  //�������ϵͳ
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
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CGhList));
	AddDocTemplate(pDocTemplate);
	this->pGhList=pDocTemplate; 
	pGhList->OpenDocumentFile(NULL);
	// TODO: Add your command handler code here
	
}

void CHis2App::OnMenuRoleSet() 
{
	if(!AssertRole(ROLE_ROLE_SET))return; // �Ƿ����Ȩ�����ù���
	CDialogRoleset role;
	role.DoModal();
}

BOOL CHis2App::AssertRole(int role) //Ȩ���ж�
{
	if(strRole.GetLength()<role){
		MessageBox(NULL,"����Ȩʹ�ô����,��ȷ������,����ϵϵͳ������Ա!!!","��ʾ",MB_OK|MB_ICONINFORMATION|MB_TASKMODAL);
		return false;
	}
	if(strRole.Mid(role-1,1)=="1")return true;
	else {
		MessageBox(NULL,"����Ȩʹ�ô����,��ȷ������,����ϵϵͳ������Ա!!!","��ʾ",MB_OK|MB_ICONINFORMATION|MB_TASKMODAL);
		return false;
	}
}

void CHis2App::OnMenuCalulate() //������
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

void CHis2App::OnMenuRkQuery() //����ѯ
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
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
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
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CFormZkList));
	AddDocTemplate(pDocTemplate);
	this->pZkList=pDocTemplate; 
	pZkList->OpenDocumentFile(NULL);
	
}




void CHis2App::OnMenuSendNotify() //����֪ͨ
{
	// TODO: Add your command handler code here
	if(  !AssertRole(ROLE_NOTIFY_SEND )  )return; // �Ƿ����ɾ��֪ͨ����
	CDSendNotify send;
	send.DoModal();
}

void CHis2App::OnMenuAlreadySend() 
{
	CQueryReadNotifyPeople query;
	query.DoModal();
}

void CHis2App::OnMenuDelAllNotify()  //֪ͨ���ȫ��ɾ��
{
	if(  !AssertRole(ROLE_NOTIFY_DELETE)  )return; // �Ƿ����ɾ��֪ͨ����

	CString strSql;
	if( ::MessageBox(AfxGetMainWnd()->m_hWnd,"ɾ��ϵͳ������ [֪ͨ��Ϣ] ��??","ɾ��",MB_OKCANCEL|MB_ICONWARNING) == IDOK ){
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
			AfxMessageBox("ɾ������...");
			HospitalConnect->RollbackTrans();
			return ;
		}
		return ;
		
	}
}

void CHis2App::OnMenuPandian()  //ҩƷ�̵����
{
	if(!AssertRole(ROLE_MED_CHECK_ACCOUNTS))return; // �Ƿ�����̵㹦��
	CPandian pan;
	pan.DoModal();
}

void CHis2App::OnMenuOtherConsume()  //�������Ĳ���
{
	if(!AssertRole(ROLE_MED_OTHER_CONSUME))return; // �Ƿ�����������Ĺ���
	CCommonUse cu; //����ʹ��
	cu.DoModal();
	
}

void CHis2App::OnMenuPandianQuery()  //�̵��ѯ
{
	if(pPDList != NULL ){
		BringWindowToTop(hPDList);
		ShowWindow(hPDList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CPandianList) );
	AddDocTemplate(pDocTemplate);
	this->pPDList=pDocTemplate; 
	pPDList->OpenDocumentFile(NULL);
	
}

void CHis2App::OnMenuOtherConsumeQuery()  //�������Ĳ�ѯ
{

	if(pCUList != NULL ){
		BringWindowToTop(hCUList);
		ShowWindow(hCUList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CCommonUseQuery) );
	AddDocTemplate(pDocTemplate);
	this->pCUList=pDocTemplate; 
	pCUList->OpenDocumentFile(NULL);
	
}

void CHis2App::OnMenuStockGeneric()  //�������¼ƻ��Զ����ɵ�ǰ�ƻ�
{
	if(!AssertRole(ROLE_STOCK_GENERIC))return; // �Ƿ����ҩƷ�ɹ����ɹ���
	CGenericStockMed stockMed;
	stockMed.DoModal();
	
}

void CHis2App::OnMenuBreakMedList()  //����ҩƷ��ѯ
{
	if(pBMList != NULL ){
		BringWindowToTop(hBMList);
		ShowWindow(hBMList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
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

void CHis2App::OnMenuCodegys()  //��Ӧ���޸�
{
	CCodeGysQuery gys;
	gys.DoModal();
	
}

void CHis2App::OnMenuMedcode()  //ҩƷ��������
{

	CMedCodeBase qu;
	qu.DoModal();
}

void CHis2App::OnMenuMedroomCompare()  //��ҩ����������Աȱ�
{
	CMedRoomCompare mp;
	mp.DoModal();
	
}

void CHis2App::OnMenuMedusedTable()  //ҩƷ������ϸ��
{
	if(pConsume != NULL ){
		BringWindowToTop(hConsume);
		ShowWindow(hConsume,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CEverydayConsumeList));

	AddDocTemplate(pDocTemplate);
	this->pConsume=pDocTemplate; 
	pConsume->OpenDocumentFile(NULL);
	
}

void CHis2App::OnMenuBuySellStock() //ҩƷ�������б�
{
	if(pBuySellStock != NULL ){
		BringWindowToTop(hBuySellStock);
		ShowWindow(hBuySellStock,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CBuySellStockList));

	AddDocTemplate(pDocTemplate);
	this->pBuySellStock=pDocTemplate; 
	pBuySellStock->OpenDocumentFile(NULL);
	
}
#include "BuySellStockList.h"

void CHis2App::OnMenuRelateCharge()  //�����������ñ���
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
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CQueryICList));

	AddDocTemplate(pDocTemplate);
	this->pICList=pDocTemplate; 
	pICList->OpenDocumentFile(NULL);
	
}

void CHis2App::OnMenuSystemKill()  //ϵͳ��¼��Ա��ѯ
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

void CHis2App::OnMenuZlList() //���������ѯ
{
	if(pTreateList != NULL ){
		BringWindowToTop(hTreateList);
		ShowWindow(hTreateList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CTreateList));

	AddDocTemplate(pDocTemplate);
	this->pTreateList=pDocTemplate; 
	pTreateList->OpenDocumentFile(NULL);

	
}
#define _O(x) COleVariant(x)

void CHis2App::OnMenuImp() //����
{
/*		app.CreateDispatch("excel.application");
		if(!app){
			AfxMessageBox("��ע��ϵͳ�б���װ��EXCEL97 ���� EXCEL2000 ,����˹��ܲ���ʹ��...");
			return;
		}
		books=app.GetWorkbooks();
		book=books.Open("G:\\xx.xls",vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
		sheets=book.GetWorksheets();

	
	sheet=sheets.GetItem(COleVariant((short)1)); //sheet2 ��Ϊ��������������ӡ����
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
		str4=(char*)_bstr_t(vrange.GetValue()); //����
		
		str5=str1.Left(str1.GetLength()-1); //����
	
		strTemp.Format("F%d",i);			
		vrange=sheet.GetRange(_O(strTemp),_O(strTemp));
		str6=(char*)_bstr_t(vrange.GetValue()); //����
	
		strTemp.Format("H%d",i);			
		vrange=sheet.GetRange(_O(strTemp),_O(strTemp));
		str7=(char*)_bstr_t(vrange.GetValue()); //���


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

void CHis2App::OnMenuDoctorWorkload()  //ҽ����������ѯ
{
	CDoctorWorkLoad work;
	work.strTitle="ҽ�����������ͳ�Ʊ�";
	work.DoModal();
	
}

void CHis2App::OnMenuCommitProgram()  //������ǰ�����ύ�����ݿ�
{
/*
	if(CHis2App::GetHttpFile("HTTP://10.43.34.200/database.txt.txt","c:\\test.txt"))
		AfxMessageBox("�ɹ���ȡ�����ļ�...");
*/	
}

void CHis2App::OnMenuRelateAutoAddcash()  //������������Զ���ֵ
{
	if(!theApp.AssertRole(ROLE_RELATE_AUTO_ADDCASH))return; 

	CProgress pd;
	pd.strNotify="�Ƿ�ȷ��Ҫ������Ƚ�ת��ֵ,ÿ���ֻ�������һ�γ�ֵ!!!";
	pd.pThreadFunction=CProgress::RelateAutoAddCash;
	pd.strView="���ڽ����Զ���ֵ,���Ժ�...";
	pd.DoModal();
}

void CHis2App::OnMenuRelateConsume() //�����ʻ��������
{
	CRelateConsumeList li;
	li.strTitle="���������ʻ������ϸ��";
	li.DoModal();
}
/*
	HTTP �ļ���ȡ,��������Զ�����

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
	pp.strView="�������������ļ�!!";
	long i=0,len;

	try
	{
		// �������ӵ�ָ��URL
		file = (CInternetFile*) session.OpenURL(strUrl,1,INTERNET_FLAG_TRANSFER_BINARY); 
	}
	catch (CInternetException* m_pException)
	{
		// ����д���Ļ������ļ�Ϊ��
		file = NULL; 
		AfxMessageBox("�������ļ�λ�ó��ִ���,δ���ҵ�Ҫ�������ļ�...");
		m_pException->Delete();
		return FALSE;
	}

	// ��dataStore�������ȡ���ļ�
	CStdioFile dataStore;
	
	
	if (file)
	{
		BOOL bIsOk = dataStore.Open(strFile,
			CFile::modeCreate | CFile::modeWrite | CFile::typeBinary  );
		
		if (!bIsOk){
			AfxMessageBox("2.�������ļ����ִ���...");
			return FALSE;
		}
		BYTE a[1024];	
		// ��д�ļ���ֱ��Ϊ��
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
	//	dataStore.WriteString(_T("��ָ�������������ӽ���ʧ��..."));	
		AfxMessageBox("3.�������ļ����ִ���...");
		return FALSE;
	}
	
	return TRUE;
}

void CHis2App::OnMenuUpgradeProgram()  //��������
{
	CString strSql,strTmp;
	long fileLength;
			//ɾ�����б����ļ�
	strSql.Format("cmd /c del /Q /F %s",LoginInformation.path);
	strSql+="*.bak";
	WinExec(strSql,SW_HIDE);

	try{
		strSql.Format("select ds1,ds3,n1 from LSQ_UPGRADE WHERE ds2='UPGRADE'  ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
	
			//�汾��
			strSql=(char*)_bstr_t(recSet->GetCollect("ds3").vt==VT_NULL?" ":recSet->GetCollect("ds3"));
			strSql.Remove('.');
			strTmp=strVer;
			strTmp.Remove('.');

			if( atol(strSql) > atol(strTmp) ) // ����汾���ڵ�ǰ�汾,���������...
			{
				strSql.Format("cmd /c Ren  %s",LoginInformation.path);
				strSql+="his2.exe *.bak";
				WinExec(strSql,SW_HIDE);
		
				strSql=(char*)_bstr_t(recSet->GetCollect("ds1").vt==VT_NULL?" ":recSet->GetCollect("ds1"));
				fileLength=atol((char*)_bstr_t(recSet->GetCollect("n1").vt==VT_NULL?" ":recSet->GetCollect("n1")));
				strTmp.Format("%s%s",LoginInformation.path,"his22.exe");
				recSet->Close();
			
				if(!GetHttpFile(strSql,strTmp,fileLength)){
					AfxMessageBox("����ʧ��...");
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
		AfxMessageBox("���ִ���,����SQL���...");
		return ;
	}		
}
//�º���ϸ��
void CHis2App::OnMenuMedUsedMonth() 
{
	
	CMonthConsumeList list;
	list.strTitle="���ⷿ�º���ϸ��";
	list.DoModal();
	
}

int CHis2App::GetMonthDays(int year, int month)
{
	if( month == 2 ) {
		if (  year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) )return 29; //����
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

void CHis2App::OnMenuYearConsumeAna()  //��Ⱦ����������
{
	CYearDataCountAnalyse	 ana;
	ana.DoModal();
}

void CHis2App::OnMenuFinanceReport()  //���������Ա���񱨱�
{
	CFinanceReport fr;
	fr.DoModal();
}

void CHis2App::OnMenuOhterDecharge()  //������Ա���ñ�����ѯ
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	COtherDechargeQuery od;
	od.DoModal();
	
}

void CHis2App::OnMenuModifyMedRec()  //ҩƷ�޸���ϸ��
{
	CModifyMedRec rec;
	rec.DoModal();
}

void CHis2App::OnMenuDaBin()  //��ҽ�����ﱨ��
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	COtherDecharge de;
	de.DoModal();
}

void CHis2App::OnMenuExternJiWe()  //�ƻ����ù����ﱨ��
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CJiHuaWeDecharge de;
	de.DoModal();
}

void CHis2App::OnMenuHosDinner()  //ҽԺ�д���
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosDinner di;
	di.DoModal();
}

void CHis2App::OnMenuHosElse() //ҽԺ�������ñ���
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	// TODO: Add your command handler code here
	CHosElse di;
	di.DoModal();

}

void CHis2App::OnMenuHosInstrumentGet()  //��е����
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosInstrumentGet di;
	di.DoModal();
}

void CHis2App::OnMenuHosMedGet()  //ҩƷ����
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosMedGet di;
	di.DoModal();
}

void CHis2App::OnMenuHosModify() //ҽԺ��е�����
{
	// TODO: Add your command handler code here
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosModify di;
	di.DoModal();
}

void CHis2App::OnMenu30Add()  //����30%���
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHos30Factory di;
	di.DoModal();
}

void CHis2App::OnMenu30Hos() //ҽԺ30%����
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHos30Hospital di;
	di.DoModal();
}

void CHis2App::OnMenu40Add() //ҽԺ40%��չ����
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHos40Factory di;
	di.DoModal();
}

void CHis2App::OnMenuHosEdu() //ҽԺ��������
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	// TODO: Add your command handler code here
	CHosEmpEdu di;
	di.DoModal();
}

void CHis2App::OnMenuHosCheck() //����
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
	di.iType=0; //����
	di.DoModal();
	
}

void CHis2App::OnMenuHosTuiyang() 
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosTuiXiu di;
	di.iType=1; //����
	di.DoModal();
	// TODO: Add your command handler code here
	
}

void CHis2App::OnMenuHosGuoqian() 
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosTuiXiu di;
	di.iType=2; //��ǰ
	di.DoModal();
	// TODO: Add your command handler code here
	
}

void CHis2App::OnMenuHosGangshang() 
{
	if(!theApp.AssertRole(ROLE_OTHER_DECHARGE))return; 
	CHosTuiXiu di;
	di.iType=3; //����
	di.DoModal();
	// TODO: Add your command handler code here
	
}

void CHis2App::OnMenuAccountAdd()  //ְ��������ֵά��
{
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CAccountScale di;
	di.DoModal();
}

void CHis2App::OnMenuDechargeScale() //��������ά��
{
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CDechargeScale di;
	di.DoModal();
}

void CHis2App::OnMenuAccrualAdd()  //��Ϣ����
{
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CAccrualAdd di;
	di.DoModal();
}

void CHis2App::OnMenuDepartSet() 
{
	if(!theApp.AssertRole(ROLE_BASE_SET))return; 
	CDepartSet di;
	di.gstrSql="SELECT distinct ������ FROM �����ű� order by ������";
	di.strTitle="�����ű�����";
	di.DoModal();
}

void CHis2App::OnMenuEmpDecharge() //���䱣����Ա����
{
//	CEmployeeDecharge de;
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CEmployeeBmp de;
	de.DoModal();
	
}

void CHis2App::OnMenuEmpCashAdd()  //�ʻ���ֵ����
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

void CHis2App::OnMenuBaseProjectSet()  //������Ŀ����
{
	if(!theApp.AssertRole(ROLE_BASE_SET))return; 

	CBaseChargeSet di;
	di.strTitle="������Ŀ������Ϣ����";
	di.gstrSql="SELECT distinct  ���ô��� FROM ������Ŀ�� order by ���ô��� ";
	di.DoModal();
	
}

void CHis2App::OnMenuBaseSpecif()  //������Ա�༭
{
	if(!theApp.AssertRole(ROLE_BASE_SET))return; 
	CBaseOtherSickSet di;
	di.DoModal();
}

void CHis2App::OnMenuSpecifSet()  //������Ա�����趨
{
	if(!theApp.AssertRole(ROLE_BASE_SET))return; 
	CStandardSubsidySet di;
	di.DoModal();
}

void CHis2App::OnMenuPeculiarQuery()  //������Ա��ֵ��ѯ
{
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CPeculiarInput di;
	di.DoModal();
	
}
void CHis2App::OnMenuAccountUsedCount()  //�ʻ�ʹ�û���
{
	CEmpUsedAccountCollect di;
	di.DoModal();
	
}

void CHis2App::OnMenuQueryEmpDecharge()  //���䱣�ղ�ѯ
{
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CEmpDechargeQuery di;
	di.DoModal();
	
}

void CHis2App::OnMenuManualAddCash()  //�ֶ���ֵ
{
	if(!theApp.AssertRole(ROLE_EMP_DECHARGE))return; 
	CNewPersonalAddCash di;
	di.DoModal();
	
}

void CHis2App::OnMenuEmpGet()  //���䱣�ջ���������
{
	CEmpGetAccount di;
	di.DoModal();
}

void CHis2App::OnMenuEmpBalanceCount()  //���䱣�ս����
{
	CEmpBalanceCount di;
	di.DoModal();
	
}

void CHis2App::OnMenuCashPurchase()  //����ϵ������
{
	CCashBuySellStock di;
	di.DoModal();
	
}

void CHis2App::OnMenuitemDoctorOther() //ҽ����������ͳ��
{

	CDoctorWorkOther ot;
	ot.DoModal();
	
}

void CHis2App::OnMenuResideCheckin() //סԺ�Ǽ�
{
	CResideCheckIn ci;
	ci.DoModal();
}

void CHis2App::OnMenuResideLocal() //��������
{
	CResideLocalSet ls;
	ls.DoModal();
}

void CHis2App::OnMenuResideRoom() //��������
{
	CRoomSet rs;
	rs.DoModal();
}

void CHis2App::OnMenuResideBed() //��������
{
	CResideBedSet bs;
	bs.DoModal();
	
}

void CHis2App::OnMenuResideQuery() //סԺ��Ա��Ϣ��ѯ
{

	if(pResideList != NULL ){
		BringWindowToTop(hResideList);
		ShowWindow(hResideList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis2Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CResideList));
	AddDocTemplate(pDocTemplate);
	this->pResideList=pDocTemplate; 
	pResideList->OpenDocumentFile(NULL);
	
}
