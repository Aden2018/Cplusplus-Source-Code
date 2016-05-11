// his3.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "his3.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "his3Doc.h"
#include "his3View.h"

#include "splash.h"
#include "logon.h"
#include "registerGh.h"
#include "comfunc.h"
#include "formGhList.h"
#include "dialogReportView.h"
#include "dialogSickGetMed.h"
#include "privilegeQuota.h"
#include "dialogUpgrade.h"
#include "lock.h"
#include "FormGhlist_del.h"
#include "costClassA.h"
#include "costClassAb.h"
#include "costBudget.h"
#include "costConsumeAdd.h"
#include "reportDechargeList.h"
#include "ReportUsedAll1.h"
#include "peculiarAdd.h"
#include "ReportUsedAll.h"
#include "medcode.h"
#include "ReportEmpCount.h"

#include "ReportEmpJSB.h"
#include "ReportMedConsume.h"

#include "journal.h"
#include "journalFee.h"

#include "makeFee.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "DialogFromFileReadTxt.H"
#include "aes.h"
#include "SpecReporter.h"
#include "SpecReporterManager.h"
#include "AdoTest.h"

#include "UserManage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHis3App

BEGIN_MESSAGE_MAP(CHis3App, CWinApp)
	//{{AFX_MSG_MAP(CHis3App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_MENUITEM_GHOPER, OnMenuitemGhoper)
	ON_COMMAND(ID_MENU_REPORT_MZCX, OnMenuReportMzcx)
	ON_COMMAND(ID_MENU_REPORT_VIEW, OnMenuReportView)
	ON_COMMAND(ID_MENU_GH_GETMED, OnMenuGhGetmed)
	ON_COMMAND(ID_MENU_SYS_PRIVI_SET, OnMenuSysPriviSet)
	ON_COMMAND(ID_MENU_BASE_DEPART_SET, OnMenuBaseDepartSet)
	ON_COMMAND(ID_MENU_BASE_DEPART2_SET, OnMenuBaseDepart2Set)
	ON_COMMAND(ID_MENU_LOCK, OnMenuLock)
	ON_COMMAND(ID_MENU_REPORT_DEL_MZCQ, OnMenuReportDelMzcq)
	ON_COMMAND(ID_MENU_COST_CLASS_A, OnMenuCostClassA)
	ON_COMMAND(ID_MENU_COST_CLASS_B, OnMenuCostClassB)
	ON_COMMAND(ID_MENU_COST_BUDGET, OnMenuCostBudget)
	ON_COMMAND(ID_MENU_COST_CONSUME, OnMenuCostConsume)
	ON_COMMAND(ID_MENU_REPORT_DECHARGE, OnMenuReportDecharge)
	ON_COMMAND(ID_MENU_REPORT_BCBX_HZ, OnMenuReportBcbxHz)
	ON_COMMAND(ID_MENUITEM_PECULIAR_ADD, OnMenuitemPeculiarAdd)
	ON_COMMAND(ID_MENUITEM_MED_QUERY, OnMenuitemMedQuery)
	ON_COMMAND(ID_MENU_MEDCODE_MANAGER, OnMenuMedcodeManager)
	ON_COMMAND(ID_MENUITEM_BCYB_ZJB, OnMenuitemBcybZjb)
	ON_COMMAND(ID_MENUITEM_BCYB_JSB, OnMenuitemBcybJsb)
	ON_COMMAND(ID_MENUITEM_MED_CONSUME, OnMenuitemMedConsume)
	ON_COMMAND(ID_MENU_MEDCODE_SORT, OnMenuMedcodeSort)
	ON_COMMAND(ID_JOURNAL_BASE_ADD, OnJournalBaseAdd)
	ON_COMMAND(ID_JOURNAL_CONTRIBUTION_FEE, OnJournalContributionFee)
	ON_COMMAND(ID_JOURNAL_FEE_QUERY, OnJournalFeeQuery)
	ON_COMMAND(ID_JOURNAL_RELEASE, OnJournalRelease)
	ON_COMMAND(ID_JOURNAL_COUNT, OnJournalCount)
	ON_COMMAND(ID_MENU_MAKE_FEE, OnMenuMakeFee)
	ON_COMMAND(ID_MENU_MAKEFEE_LIST, OnMenuMakefeeList)
	ON_COMMAND(ID_MENU_FEE_RELEASE_NUM, OnMenuFeeReleaseNum)
	ON_COMMAND(ID_MENU_TMP_INDATA, OnMenuTmpIndata)
	ON_COMMAND(ID_MENU_TMP_INDATA_DIALOG, OnMenuTmpIndataDialog)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_MENU_REPORTER_SALARY, &CHis3App::OnMenuReporterSalary)
	ON_COMMAND(ID_MENU_SPEC_REPORT_MANAGER, &CHis3App::OnMenuSpecReportManager)
	ON_COMMAND(ID_MENU_ADO_TEST, &CHis3App::OnMenuAdoTest)
	ON_COMMAND(ID_USER_MANAGE, &CHis3App::OnUserManage)
	ON_UPDATE_COMMAND_UI(ID_JOURNAL_CONTRIBUTION_FEE, &CHis3App::OnUpdateJournalContributionFee)
	ON_UPDATE_COMMAND_UI(ID_USER_MANAGE, &CHis3App::OnUpdateUserManage)
	ON_UPDATE_COMMAND_UI(ID_MENU_SPEC_REPORT_MANAGER, &CHis3App::OnUpdateMenuSpecReportManager)
	ON_UPDATE_COMMAND_UI(ID_JOURNAL_BASE_ADD, &CHis3App::OnUpdateJournalBaseAdd)
	ON_UPDATE_COMMAND_UI(ID_MENU_REPORTER_SALARY, &CHis3App::OnUpdateMenuReporterSalary)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHis3App construction

CHis3App::CHis3App()
{
	// TODO: add construction code here,
	_IniFile=".\\mysql.ini";
	strVer.Format("1.00.01"); //****20090512,�Ѿ���Ч
	const int STR_NUM=6,STR_LEN=36;
//	string str[STR_NUM],strDec[STR_NUM];
	CString cs[STR_NUM];
	
	GetPrivateProfileString("Login","server","ERROR",cs[0].GetBuffer(STR_LEN),STR_LEN,theApp._IniFile);
	GetPrivateProfileString("Login","User","ERROR",cs[1].GetBuffer(STR_LEN),STR_LEN,theApp._IniFile);
	GetPrivateProfileString("Login","pwd","ERROR",cs[2].GetBuffer(STR_LEN),STR_LEN,theApp._IniFile);
	GetPrivateProfileString("Login","DRIVER","ERROR",cs[3].GetBuffer(STR_LEN),STR_LEN,theApp._IniFile);
	GetPrivateProfileString("Login","PORT","ERROR",cs[4].GetBuffer(STR_LEN),STR_LEN,theApp._IniFile);
	GetPrivateProfileString("Login","Database","ERROR",cs[5].GetBuffer(STR_LEN),STR_LEN,theApp._IniFile);
	for(int i=0; i<STR_NUM;i++)cs[i].ReleaseBuffer();
	//	CString ConnectParameter;// ϵԭ���������ַ���MSDAORA.1
	//str[0]=cs[1];
	//str[1]=cs[2];
	//CComFunc::DecryptString(str[0],strDec[0]);
	//CComFunc::DecryptString(str[1],strDec[1]);
	//�������ݿ��˺ż�����,�˼��ܷ�ʽΪAES����,���ܴ�ǰ������
	//һ�û��Զ����ַ�

	if (cs[1][0] + cs[1][cs[1].GetLength()-1] !='A'+'Z' ||
		cs[2][0] + cs[2][cs[2].GetLength()-1] != 'A'+'Z' )
	{
		AfxMessageBox("Դ�����ļ����޸�  ���������ļ�");
		return ;
	}		
	AES aes;
	string src[2],dst[2];
	src[0]=cs[1].Mid(1,cs[1].GetLength()-2);
	src[1]=cs[2].Mid(1,cs[2].GetLength()-2);
	aes.Str2Hex(src[0],dst[0]);
	aes.Str2Hex(src[1],dst[1]);
	aes.InvCipher((unsigned char*)dst[0].c_str());
	aes.InvCipher((unsigned char*)dst[1].c_str());

	strConn.Format("Driver=%s;SERVER=%s;UID=%s;PWD=%s;DATABASE=%s;PORT=%s",
		cs[3],cs[0],dst[0].c_str(),dst[1].c_str(),cs[5],cs[4] );



	// Place all significant initialization in InitInstance
	pGhList=NULL;
	hGhList=NULL;
	pGhList_del=NULL;
	hGhList_del=NULL;
	pDechargeList=NULL;
	hDechargeList=NULL;
	pUsedAll=NULL;
		hUsedAll=NULL;
	strOracleYear="";
	int i;
	for( i=0;i< DOC_MAX; ++i)docList[i]=NULL;
	for(i=0 ; i< HWND_MAX; ++i) hwndList[i]=NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHis3App object

CHis3App theApp;

/////////////////////////////////////////////////////////////////////////////
// CHis3App initialization

BOOL CHis3App::InitInstance()
{



	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.


	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
/*
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_HIS3TYPE,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CHis3View));
	AddDocTemplate(pDocTemplate);
*/
	AfxOleInit() ;
	int x;
	// ��λӦ�ó�������Ŀ¼
	if(!::GetModuleFileName(NULL,LoginInformation.path,MAX_PATH)){
		AfxMessageBox("����Ӧ�ó�����ܷ����·��̫��,���ƶ�����Ŀ¼������...\nĳЩ���ܵ�ǰ������...");
	}
	else
	{
		for( x=strlen(LoginInformation.path); LoginInformation.path[x-1] != '\\'; x--);
		LoginInformation.path[x]=0;

	}
	//�������ݿ�
	CSplash startView;
	startView.DoModal();
	if(startView.timer_count != 1){
		if(startView.timer_count == 3)AfxMessageBox("��ʼ��ϵͳ COM ��ʧ��,����ϵͳ COM �����Ƿ�������...");
		else AfxMessageBox("���� Mysql ���ݿ�ʧ��,��������� Mysql �����Ƿ���ȷ...");//,"Oracle ���Ӵ���",MB_OK|MB_ICONWARNING);
		
		return false;
	}
	if(FAILED(recSet.CreateInstance( __uuidof( Recordset ))))
	{
		AfxMessageBox("��ʼ��Recordsetʧ��...");
		return false ;
	}
//����Ƿ��п���������
//	if( !CheckUpgrade() ) return false;

//	strOracleYear=CComFunc::GetString("select to_char(sysdate,'yyyy') from dual");

	CLogon log2;
	if(log2.DoModal()==IDCANCEL)return false;

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();
	CStatusBar *pStatus=(CStatusBar*)AfxGetApp()->GetMainWnd()->GetDescendantWindow(ID_VIEW_STATUS_BAR);
	int i=1;
//	pStatus->SetPaneText(i++," ��  �� :    "+LoginInformation.user);
	pStatus->SetPaneText(i++," �� �� :"+LoginInformation.kfmc);

	

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

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaticVer();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
	ON_STN_CLICKED(IDC_STATIC_VER, &CAboutDlg::OnStnClickedStaticVer)
END_MESSAGE_MAP()

// App command to run the dialog
void CHis3App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CHis3App message handlers


void CHis3App::OnMenuitemGhoper()  //�Һž���
{
	//����Ȩ���ж�
	if( ! CComFunc::AssertPriv(1) ) return; 

	CRegisterGh gh;
	gh.DoModal();
	
}

void CHis3App::OnMenuReportMzcx()  // ��Ѳ�ѯ
{
	if(pGhList != NULL ){
		BringWindowToTop(hGhList);
		ShowWindow(hGhList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CFormGhList));
	AddDocTemplate(pDocTemplate);
	this->pGhList=pDocTemplate; 
	pGhList->OpenDocumentFile(NULL);
	
}

void CHis3App::OnMenuReportView() 
{
	CDialogReportView rv;
	rv.DoModal();
}

void CHis3App::OnMenuGhGetmed()  //��ȡҩ��Ա�б�
{
	if( ! CComFunc::AssertPriv(3) ) return;  //

	CDialogSickGetMed gm;
	gm.DoModal();
}

void CHis3App::OnMenuSysPriviSet()  //Ӧ�ó���Ȩ�޷���
{
	if( ! CComFunc::AssertPriv(5) ) return; 
	CPrivilegeQuota pq;
	pq.DoModal();
	
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString strVer;
	strVer.LoadString(IDS_STR_VERSION);
	GetDlgItem(IDC_STATIC_VER)->SetWindowText("������ѹ��� : "+strVer);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CHis3App::CheckUpgrade()
{
	CString strVer,strNew[2],strSql;
	strVer.LoadString(IDS_STR_VERSION); //�õ�ϵͳ��ǰ�汾
	strVer.Remove('.');

	strSql=" SELECT ds3,ds1 FROM lsq_upgrade Where ds2='UPGRADE2' ";

	CComFunc::GetString(strSql,strNew,2);
	strNew[0].Remove('.');

	if( atol(strVer) < atol(strNew[0]) ){

		//AfxMessageBox("��ǰ�汾�ϵ�,������...");
		CDialogUpgrade du;
		du.strURL=strNew[1];
		du.strFILE.Format("%s\\down.dat",LoginInformation.path);
		du.DoModal();

		HospitalConnect->Close();

		
		strVer.Format("%s\\up.exe",LoginInformation.path);
		::ShellExecute(NULL,"open",strVer,NULL,NULL,SW_HIDE);
		return false;
	}
	return true;
}

void CAboutDlg::OnOK() 
{
	// TODO: Add extra validation here
/*	try{
		HospitalConnect->BeginTrans();
		CString strSql;
		strSql.Format("SElect * from medlie where id=2479 for update ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenStatic,adLockPessimistic,adCmdText); 
		if(!recSet->adoEOF){
		
		//	strout=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(0L)->Value );
		}
		recSet->Close();

		AfxMessageBox("ok...locked ");
		HospitalConnect->CommitTrans();
	}

	catch(...)
	{
		AfxMessageBox("error...");
		recSet->Close();
		HospitalConnect->RollbackTrans();
		return;
	
	}
*/	
	CDialog::OnOK();
}

void CHis3App::OnMenuBaseDepartSet() //�����Ż���������
{
	//����Ȩ���ж�
		
}

void CHis3App::OnMenuBaseDepart2Set() // ������������
{
	// TODO: Add your command handler code here
	
}

void CHis3App::OnMenuLock()  //��������
{
	// TODO: Add your command handler code here
	CLock lk;
	lk.DoModal();
}

void CHis3App::OnMenuReportDelMzcq()  // 
{
	if( ! CComFunc::AssertPriv(6) ) return; 

	if(pGhList_del != NULL ){
		BringWindowToTop(hGhList_del);
		ShowWindow(hGhList_del,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CFormGhList_del));
	AddDocTemplate(pDocTemplate);
	this->pGhList_del =pDocTemplate; 
	pGhList_del->OpenDocumentFile(NULL);
	
}

void CHis3App::OnMenuCostClassA() //֧��Ŀ¼����
{
	// TODO: Add your command handler code here
	if( ! CComFunc::AssertPriv(7) ) return; 
	CCostClassA ca;
	ca.DoModal();
	
}

void CHis3App::OnMenuCostClassB() //֧����ϸĿ¼����
{
	if( ! CComFunc::AssertPriv(7) ) return; 
	CCostClassAb ab;
	ab.DoModal();
}

void CHis3App::OnMenuCostBudget() // ��ȷ���Ԥ��
{
	if( ! CComFunc::AssertPriv(7) ) return; 
	CCostBudget bg;
	bg.DoModal();
}

void CHis3App::OnMenuCostConsume() //���ñ���
{
	if( ! CComFunc::AssertPriv(8) ) return; 
	CCostConsumeAdd ca;
	ca.DoModal();
}

void CHis3App::OnMenuReportDecharge() // ���ñ�����ѯ
{
	if( ! CComFunc::AssertPriv(8) ) return; 
	if(pDechargeList != NULL ){
		BringWindowToTop(hDechargeList);
		ShowWindow(hDechargeList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CReportDechargeList));
	AddDocTemplate(pDocTemplate);
	pDechargeList =pDocTemplate; 
	pDechargeList->OpenDocumentFile(NULL);
	
}

void CHis3App::OnMenuReportBcbxHz() //���䱣��ʹ���������
{

	
}

void CHis3App::OnMenuitemPeculiarAdd() //��ȶ��⣨���⣩����
{
	//ID_MENUITEM_PECULIAR_ADD
	if( ! CComFunc::AssertPriv(ID_MENUITEM_PECULIAR_ADD) ) return; 

	CPeculiarAdd ca;
	ca.DoModal();
}

void CHis3App::OnMenuitemMedQuery() // ���ҩƷ��ѯ
{

	if(docList[MED_POINT] != NULL ){
		BringWindowToTop(hwndList[MED_POINT] );
		ShowWindow(hwndList[MED_POINT],SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CReportMedQuery));
	AddDocTemplate(pDocTemplate);
	this->docList[MED_POINT]=pDocTemplate; 
	docList[MED_POINT]->OpenDocumentFile(NULL);
	
}

void CHis3App::OnMenuMedcodeManager() //ҩƷ������� 
{
	//ID_MENU_MEDCODE_MANAGER
	if( ! CComFunc::AssertPriv(ID_MENU_MEDCODE_MANAGER) ) return; 
	CMedcode mc;
	mc.DoModal();
}

void CHis3App::OnMenuitemBcybZjb() //������
{
	if( ! CComFunc::AssertPriv(ID_MENUITEM_BCYB_ZJB) ) return; 

	CReportEmpCount rc;
	rc.DoModal();
}

void CHis3App::OnMenuitemBcybJsb() //�����
{
	if( ! CComFunc::AssertPriv(ID_MENUITEM_BCYB_JSB) ) return; 

	CReportEmpJSB	js;
	js.DoModal();
}

void CHis3App::OnMenuitemMedConsume() //ҩƷ����ͳ��
{
	if(docList[MED_CONSUME] != NULL ){
		BringWindowToTop(hwndList[MED_CONSUME] );
		ShowWindow(hwndList[MED_CONSUME],SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CReportMedConsume));
	AddDocTemplate(pDocTemplate);
	this->docList[MED_CONSUME]=pDocTemplate; 
	docList[MED_CONSUME]->OpenDocumentFile(NULL);	
}

void CHis3App::OnMenuMedcodeSort() 
{
	// TODO: Add your command handler code here
	
}
//�����ںŵǼ�
void CHis3App::OnJournalBaseAdd() 
{
	Journal jn;
	jn.DoModal();
}

//��ѵǼ�
void CHis3App::OnJournalContributionFee() 
{
	CJournalFee jf;
	jf.DoModal();
}

void CHis3App::OnJournalFeeQuery()  //��Ѳ�ѯ
{
	if(pGhList != NULL ){
		BringWindowToTop(hGhList);
		ShowWindow(hGhList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CFormGhList));
	AddDocTemplate(pDocTemplate);
	this->pGhList=pDocTemplate; 
	pGhList->OpenDocumentFile(NULL);
	
}

void CHis3App::OnJournalRelease() 
{
	if(pDechargeList != NULL ){
		BringWindowToTop(hDechargeList);
		ShowWindow(hDechargeList,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CReportDechargeList));
	AddDocTemplate(pDocTemplate);
	pDechargeList =pDocTemplate; 
	pDechargeList->OpenDocumentFile(NULL);
	
	
}

void CHis3App::OnJournalCount() 
{
	if(docList[MED_CONSUME] != NULL ){
		BringWindowToTop(hwndList[MED_CONSUME] );
		ShowWindow(hwndList[MED_CONSUME],SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), 
		RUNTIME_CLASS(CReportMedConsume));
	AddDocTemplate(pDocTemplate);
	this->docList[MED_CONSUME]=pDocTemplate; 
	docList[MED_CONSUME]->OpenDocumentFile(NULL);	
	
}



void CHis3App::OnMenuMakeFee() //�����ѵǼ� 
{
	CMakeFee mf;
	mf.DoModal();
}

void CHis3App::OnMenuMakefeeList() 
{
	if(pUsedAll != NULL ){
		BringWindowToTop(hUsedAll);
		ShowWindow(hUsedAll,SW_SHOWMAXIMIZED);
		return;
	};
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHis3Doc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CReportUsedAll));
	AddDocTemplate(pDocTemplate);
	this->pUsedAll=pDocTemplate; 
	pUsedAll->OpenDocumentFile(NULL);	
	
}

void CHis3App::OnMenuFeeReleaseNum()  //�����ںŶ�Ӧ���ò�ѯ
{
	CPeculiarAdd pa;
	pa.DoModal();
}

void CHis3App::OnMenuTmpIndata() //��ʾĿ¼ѡ��Ի���
{
   char szPath[MAX_PATH];     //���ѡ���Ŀ¼·��
   CString str;

    ZeroMemory(szPath, sizeof(szPath));  

    BROWSEINFO bi;  
    bi.hwndOwner = theApp.m_pMainWnd->m_hWnd;  
    bi.pidlRoot = NULL;  
    bi.pszDisplayName = szPath;  
    bi.lpszTitle = "�ټ��������ݴ洢Ŀ¼ѡ��";  
    bi.ulFlags = 0;  
    bi.lpfn = NULL;  
    bi.lParam = 0;  
    bi.iImage = 0;  

AllocConsole();
freopen("CON", "r", stdin );
freopen("CON", "w", stdout);
freopen("CON", "w", stderr);
//HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);


    //����ѡ��Ŀ¼�Ի���
    LPITEMIDLIST lp ;
	
OPENFILE:
	lp = SHBrowseForFolder(&bi);  

    if(lp && SHGetPathFromIDList(lp, szPath))  
    {
     //   str.Format("ѡ���Ŀ¼Ϊ %s",  szPath);
     //   AfxMessageBox(str);

       
    }
    else
	{
        AfxMessageBox("��Ч��Ŀ¼��������ѡ��");  

		goto OPENFILE;
	}

	CFileFind ff;

	CString fPath;
	fPath.Format("%s\\*.*",szPath);
	
	BOOL res = ff.FindFile(fPath);

//	SetWindowPos((HWND) CWnd::FromHandle((HWND)hConsole), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE||SWP_NOSIZE);
	
	while(res)
		
	{
		
		res = ff.FindNextFile();
		
		// ��������Ŀ¼
		
		if(! ff.IsDirectory() && !ff.IsDots())
			
		{
			ReadFileAndInsert( ff.GetFilePath() );

				
		}
		
	}
	
	ff.Close(); // ��Ҫ���ǹر�
	
	system("pause");
	
	FreeConsole();


	
}
#define IDC_PROGRESS_EXCEL WM_USER+1002

bool CHis3App::ReadFileAndInsert(const CString  &fullName)
{
	using namespace std;
	
	ifstream irTxt(fullName);
	CString strName(fullName);
	CString fileName,strSql;
	fileName=strName.Mid(strName.ReverseFind('\\')+1);

    int i,icount(0);
     
   
  //   cout<<"***************�ļ���д��ʼ*************"<<endl;
     while (!irTxt.eof())
	 {
		 
		 irTxt>>i;
		 
		 if( !i ) break;   
		 
		 ++icount;	
		 
		 strSql.Format(" Insert into HundredSelect(depart_name,order_num) values('%s',%d ) ",fileName,i );
		 if(! CComFunc::WriteSql(strSql) ) {
			 AfxMessageBox("ERROR��write_SQL error");
			 break;
		 }
		 
	 }

	 strSql.Format("%s   %d  ",fileName,icount); //�ļ���������
	 LPCTSTR pStr=strSql;
	 cout<< pStr <<endl;
 
  
  //   cout<<"***************����******************"<<endl;
      
     
     irTxt.close();

	 
	 return true;

}

void CHis3App::OnMenuTmpIndataDialog() 
{
	CDialogFromFileReadTxt df;
	df.DoModal();
}

//����ԼͨѶԱ���ӱ�����ͳ��ĳ������ͨѶԱ��꣬Ȼ���ٲ��뵽���������
//DATE:2014/09/23

void CHis3App::OnMenuReporterSalary()
{
	CSpecReporter rp;
	rp.DoModal();

}

//��ԼͨѶԱ����
void CHis3App::OnMenuSpecReportManager()
{
	CSpecReporterManager mg;
	mg.DoModal();
}

//����ado
void CHis3App::OnMenuAdoTest()
{
	CAdoTest ad;
	ad.DoModal();
	// TODO: �ڴ���������������
}


void CAboutDlg::OnStnClickedStaticVer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CHis3App::OnUserManage()
{
	
	CUserManage um;
	um.DoModal();
	
}


void CHis3App::OnUpdateJournalContributionFee(CCmdUI *pCmdUI)
{
	//���¼��
	if(! CComFunc::AssertPriv(1) ){
		pCmdUI->Enable(false);
	}

}


void CHis3App::OnUpdateUserManage(CCmdUI *pCmdUI)
{
	//ϵͳ�û�����
	if(! CComFunc::AssertPriv(6) ){
		pCmdUI->Enable(false);

	}
}


void CHis3App::OnUpdateMenuSpecReportManager(CCmdUI *pCmdUI)
{
	// ��ԼͨѶԱ����
	if(! CComFunc::AssertPriv(3) ){
		pCmdUI->Enable(false);

	}
}


void CHis3App::OnUpdateJournalBaseAdd(CCmdUI *pCmdUI)
{
	// TODO:�����ں�����
	if(! CComFunc::AssertPriv(2) ){
		pCmdUI->Enable(false);

	}
}


void CHis3App::OnUpdateMenuReporterSalary(CCmdUI *pCmdUI)
{
	// TODO: ��ԼͨѶԱ����
	if(! CComFunc::AssertPriv(4) ){
		pCmdUI->Enable(false);

	}
}
