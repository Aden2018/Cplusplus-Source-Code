// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "his2.h"
#include "huajiaList.h"
#include "logon.h"

#include "MainFrm.h"
#include "test.h"
#include "healthSearch.h"
#include "addHealth.h"
#include "dialogInStorage.h"
#include "excel9.h"
#include "otherHealthSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_TEST_PY, OnTestPy)
	ON_COMMAND(ID_IMP_PY, OnImpPy)
	ON_COMMAND(ID_HEALTH_DATA_SEARCH, OnHealthDataSearch)
	ON_COMMAND(ID_HEALTH_ADD, OnHealthAdd)
	ON_COMMAND(ID_MED_IN_STORAGE, OnMedInStorage)
	ON_COMMAND(ID_MENU_LOGOUT, OnMenuLogout)
	ON_COMMAND(ID_MENU_EXIT, OnMenuExit)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_1,OnUpdateView)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_1,
	ID_INDICATOR_2,
	ID_INDICATOR_COPYRIGHT,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


logon_information LoginInformation;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!Mdiclient.SubclassWindow(m_hWndMDIClient))
	{
		TRACE("Failed to subclass MDI client window\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	this->SetTitle(theApp.strProject);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnTestPy() 
{
	// TODO: Add your command handler code here
/*	CTest t;
	t.DoModal();
	*/
}

void CMainFrame::OnImpPy() 
{
/*	char pf[10000];
	CString str1,str2,str3,strSql;
	UINT count=0,n1,n2,n3;
	try{

		CFile fp("C:\\py.txt",CFile::modeRead);
		count=fp.Read(pf,0xffff);
		str1=pf;
		n1=0;
		HospitalConnect->BeginTrans();
		while(true){
			if((n1=str1.Find('"',n1))!=-1){ 
				
				if((n2=str1.Find('"',n1+1))!=-1){
					
					str2=str1.Mid(n1+1,n2-n1-1);
					
				//	AfxMessageBox(str2);	
					if((n3=str1.Find(',',n2))!=-1){
						if((n2=str1.Find('\n',n3+1))!=-1){

							str3=str1.Mid(n3+1,n2-n3-1);
						//	AfxMessageBox(str3);
							strSql.Format("insert into py(py_c,py_V) values('%s',%ld) ",str2,atol(str3));
							try{

								HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
							}
							catch(_com_error e)
							{
								AfxMessageBox("insert error...");
								return;
							}




						}

						

					}
					
					
				}
				if (n2>=8015)break;
				n1=n2;
				
			}

		}

		
		AfxMessageBox("ok...");
		HospitalConnect->CommitTrans();
	//	AfxMessageBox(pf);
	//	AfxMessageBox(str1);
		fp.Close();

	}
	catch(CFileException e)
	{
		AfxMessageBox("Read file error...");

		return;
	}
*/	
}

void CMainFrame::OnHealthDataSearch() //职工体检资料查询
{
	CHealthSearch hea;
	hea.DoModal();
}

void CMainFrame::OnHealthAdd()  //其它人员体检信息记录
{
/////////////////////////////////////////////////////////////////
//* 其它人员信息记录方式为直接将人员信息填入体检信息表中
//* 其功能主要继承于职工体检信息
////////////////////////////////////////////////////////////////
/*	if(!theApp.AssertRole(ROLE_BODYCHECK_ADD))return;	
	CAddHealth ca;
	ca.DoModal();
*/
	COtherHealthSearch ot;
	ot.DoModal();
}

void CMainFrame::OnUpdateView(CCmdUI *pCmdUI)
{
//	pCmdUI->Enable(true);
	CWindowDC sdc(&m_wndStatusBar);
 	CSize sizeText;
 	int nIndex;
	CString str1;
	m_wndStatusBar.SetPaneStyle(0,SBPS_NORMAL|SBPS_STRETCH);//设定状态栏第一格的样式
	m_wndStatusBar.SetPaneText(0,"系统就绪");
	
	str1="登录名:  ";
	str1+=LoginInformation.user;
	str1+="            职责:  ";
	str1+=LoginInformation.job;
	str1+="            所属部门:  ";
	str1+=LoginInformation.kfmc;
	sizeText=sdc.GetTextExtent(str1);
 	nIndex=m_wndStatusBar.CommandToIndex(ID_INDICATOR_2);
 	m_wndStatusBar.SetPaneInfo(nIndex,ID_INDICATOR_2,m_wndStatusBar.GetPaneStyle(nIndex),sizeText.cx);
	m_wndStatusBar.SetPaneText(nIndex,str1);
 
	str1.Format("版权所有:"+theApp.strProject);
	sizeText=sdc.GetTextExtent(str1);
	nIndex=m_wndStatusBar.CommandToIndex(ID_INDICATOR_COPYRIGHT);
 	m_wndStatusBar.SetPaneInfo(nIndex,ID_INDICATOR_COPYRIGHT,SBPS_STRETCH ,sizeText.cx);
	m_wndStatusBar.SetPaneText(nIndex,str1);

}

void CMainFrame::OnMedInStorage()  //药品入库操作
{

//	AfxMessageBox("药品入库操作...");
	if(!theApp.AssertRole(ROLE_MED_RK))return; 
	CDialogInStorage inStorage;
	inStorage.DoModal();
}
/*
void CMainFrame::OnMedHuajia() //门诊划价操作
{
	CHuaJiaList list;
	list.DoModal();
}
*/
void CMainFrame::OnMenuLogout() 
{
	AfxGetMainWnd()->ShowWindow(SW_HIDE);
	if(theApp.pMedlist != NULL ){ //关闭所有的查询
		::SendMessage(theApp.hMedlist,WM_CLOSE,0,0);
		

	}

	theApp.ClearLogInformation();

	theApp.strLogID="LOGOUT";

	CLogon pl;
	if(pl.DoModal()==IDOK){
		AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);
	}
//	else CMDIFrameWnd::OnClose();
	else OnClose();
}

void CMainFrame::OnMenuExit() 
{
	OnClose();
}

extern _Application app;
extern Workbooks books;
extern _Workbook book;
extern Worksheets sheets;
extern _Worksheet sheet;
extern COleVariant vOpt;
extern CFile fDebug;
void CMainFrame::OnClose() 
{
	if(	theApp.strLogID != "LOGOUT" )
		theApp.ClearLogInformation();
	
	HospitalConnect->Close();
	fDebug.Close();

	if( app){ //EXCEL防止被用户关闭,启动时在数据库中作一记录
		sheet.ReleaseDispatch();
		sheets.ReleaseDispatch();
		book.Close(COleVariant((short)0),vOpt,vOpt); //关闭EXCEL,不保存文件
		book.ReleaseDispatch();
		books.Close();
		books.ReleaseDispatch();
		app.ReleaseDispatch();
		app.Quit();
	}
	CMDIFrameWnd::OnClose();
}



void CMainFrame::CloseIndicate()
{
	OnClose();
}
