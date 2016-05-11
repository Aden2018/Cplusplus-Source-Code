// his3.h : main header file for the HIS3 application
//

#if !defined(AFX_HIS3_H__DC12DA59_7926_4015_9F5A_67E233573A7B__INCLUDED_)
#define AFX_HIS3_H__DC12DA59_7926_4015_9F5A_67E233573A7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "comFunc.h"
/////////////////////////////////////////////////////////////////////////////
// CHis3App:
// See his3.cpp for the implementation of this class
//

struct DoublePointer {
		LPVOID pGrid;
		LPVOID pQuery;
		LPVOID p2,p3,p4,pWnd;
	};


class CHis3App : public CWinApp
{
public:
	enum{HWND_MAX=20,DOC_MAX=20,MED_POINT=0,MED_CONSUME=1 };
	bool CheckUpgrade();
	CHis3App();
	CString strConn,strVer,strProject,strLogID,strRole;
	DoublePointer pParentGrid;
	CMultiDocTemplate *pGhList ,*pGhList_del,*pDechargeList,*pUsedAll ;
	HWND hGhList,hGhList_del,hDechargeList,
		hUsedAll;
	HWND hwndList[HWND_MAX];

	CMultiDocTemplate *docList[DOC_MAX];
	CString strOracleYear; //数据库当前年份
	CString _IniFile;				//应用程序配置参数文件名
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHis3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHis3App)
	afx_msg void OnAppAbout();
	afx_msg void OnMenuitemGhoper();
	afx_msg void OnMenuReportMzcx();
	afx_msg void OnMenuReportView();
	afx_msg void OnMenuGhGetmed();
	afx_msg void OnMenuSysPriviSet();
	afx_msg void OnMenuBaseDepartSet();
	afx_msg void OnMenuBaseDepart2Set();
	afx_msg void OnMenuLock();
	afx_msg void OnMenuReportDelMzcq();
	afx_msg void OnMenuCostClassA();
	afx_msg void OnMenuCostClassB();
	afx_msg void OnMenuCostBudget();
	afx_msg void OnMenuCostConsume();
	afx_msg void OnMenuReportDecharge();
	afx_msg void OnMenuReportBcbxHz();
	afx_msg void OnMenuitemPeculiarAdd();
	afx_msg void OnMenuitemMedQuery();
	afx_msg void OnMenuMedcodeManager();
	afx_msg void OnMenuitemBcybZjb();
	afx_msg void OnMenuitemBcybJsb();
	afx_msg void OnMenuitemMedConsume();
	afx_msg void OnMenuMedcodeSort();
	afx_msg void OnJournalBaseAdd();
	afx_msg void OnJournalContributionFee();
	afx_msg void OnJournalFeeQuery();
	afx_msg void OnJournalRelease();
	afx_msg void OnJournalCount();
	afx_msg void OnMenuMakeFee();
	afx_msg void OnMenuMakefeeList();
	afx_msg void OnMenuFeeReleaseNum();
	afx_msg void OnMenuTmpIndata();
	afx_msg void OnMenuTmpIndataDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	bool ReadFileAndInsert(const CString & fullName);
	afx_msg void OnMenuReporterSalary();
	afx_msg void OnMenuSpecReportManager();
	afx_msg void OnMenuAdoTest();
	afx_msg void OnUserManage();
	afx_msg void OnUpdateJournalContributionFee(CCmdUI *pCmdUI);
	afx_msg void OnUpdateUserManage(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuSpecReportManager(CCmdUI *pCmdUI);
	afx_msg void OnUpdateJournalBaseAdd(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuReporterSalary(CCmdUI *pCmdUI);
};

extern CHis3App theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIS3_H__DC12DA59_7926_4015_9F5A_67E233573A7B__INCLUDED_)
