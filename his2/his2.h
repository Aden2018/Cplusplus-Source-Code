// his2.h : main header file for the HIS2 application
//
#include "searchMed.h"
#if !defined(AFX_HIS2_H__4ABAF145_0D15_4148_83C7_8E25773C584D__INCLUDED_)
#define AFX_HIS2_H__4ABAF145_0D15_4148_83C7_8E25773C584D__INCLUDED_

#include "SearchMed.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "StdAfx.h"	// Added by ClassView
#include "otherDecharge.h"
#include "dialogMedxl.h"
/////////////////////////////////////////////////////////////////////////////
// CHis2App:
// See his2.cpp for the implementation of this class
//
#define BK1 RGB(23,169,232)
#define BK2 RGB(244,196,251)
#define BK3 RGB(22,154,68)

class CHis2App : public CWinApp
{
public:
	CString strProject;
	static int GetMonthDays(int year,int month);
	CString strVer;
	static BOOL GetHttpFile(CString strUrl,CString strFile,long fileLength);
	void ClearLogInformation();
	CString strLogID;
	BOOL AssertRole(int role);
	CString strRole;
	
	CSearchMed * search;
//	CSearchMed *search;
	HWND hMedlist,hGhList,hRkList,hZkList,hCUList,hPDList,\
		hBMList,hConsume,hBuySellStock,hICList,hTreateList;
	HWND hResideList;
	CMultiDocTemplate *pMedlist,*pGhList,*pRkList,*pZkList,*pCUList,*pPDList,\
		*pBMList,*pConsume,*pBuySellStock,*pICList,*pTreateList;
	CMultiDocTemplate *pResideList;
	DoublePointer pParentGrid;
	CDialog * pDialog; //新增一个用于入库时保存
	CString strConn;
	CBrush titleBrush;
	CHis2App();
public:
	static CFont fontTitle;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHis2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHis2App)
	afx_msg void OnAppAbout();
	afx_msg void OnMenuMedlist();
	afx_msg void OnMenuSearchMed();
	afx_msg void OnMenuMoveKf();
	afx_msg void OnMenuDoctorStart();
	afx_msg void OnMenuGhList();
	afx_msg void OnMenuRoleSet();
	afx_msg void OnMenuCalulate();
	afx_msg void OnMenuEmployee();
	afx_msg void OnMenuEmployeeRelate();
	afx_msg void OnMenuRkQuery();
	afx_msg void OnMenuZkQuery();
	afx_msg void OnMenuSendNotify();
	afx_msg void OnMenuAlreadySend();
	afx_msg void OnMenuDelAllNotify();
	afx_msg void OnMenuPandian();
	afx_msg void OnMenuOtherConsume();
	afx_msg void OnMenuPandianQuery();
	afx_msg void OnMenuOtherConsumeQuery();
	afx_msg void OnMenuStockGeneric();
	afx_msg void OnMenuBreakMedList();
	afx_msg void OnMenuSetBreakMed();
	afx_msg void OnMenuCodegys();
	afx_msg void OnMenuMedcode();
	afx_msg void OnMenuMedroomCompare();
	afx_msg void OnMenuMedusedTable();
	afx_msg void OnMenuBuySellStock();
	afx_msg void OnMenuRelateCharge();
	afx_msg void OnMenuMedDl();
	afx_msg void OnMenuMedXl();
	afx_msg void OnMenuPasswordChange();
	afx_msg void OnMenuIcQuery();
	afx_msg void OnMenuSystemKill();
	afx_msg void OnMenuZlList();
	afx_msg void OnMenuImp();
	afx_msg void OnMenuDoctorWorkload();
	afx_msg void OnMenuCommitProgram();
	afx_msg void OnMenuRelateAutoAddcash();
	afx_msg void OnMenuRelateConsume();
	afx_msg void OnMenuUpgradeProgram();
	afx_msg void OnMenuMedUsedMonth();
	afx_msg void OnMenuSellChart();
	afx_msg void OnMenuYearCountcur();
	afx_msg void OnMenuHospitalDepart();
	afx_msg void OnMenuYearConsumeAna();
	afx_msg void OnMenuFinanceReport();
	afx_msg void OnMenuOhterDecharge();
	afx_msg void OnMenuModifyMedRec();
	afx_msg void OnMenuDaBin();
	afx_msg void OnMenuExternJiWe();
	afx_msg void OnMenuHosDinner();
	afx_msg void OnMenuHosElse();
	afx_msg void OnMenuHosInstrumentGet();
	afx_msg void OnMenuHosMedGet();
	afx_msg void OnMenuHosModify();
	afx_msg void OnMenu30Add();
	afx_msg void OnMenu30Hos();
	afx_msg void OnMenu40Add();
	afx_msg void OnMenuHosEdu();
	afx_msg void OnMenuHosCheck();
	afx_msg void OnMenuPlanProcreate();
	afx_msg void OnMenuHosLixiu();
	afx_msg void OnMenuHosTuiyang();
	afx_msg void OnMenuHosGuoqian();
	afx_msg void OnMenuHosGangshang();
	afx_msg void OnMenuAccountAdd();
	afx_msg void OnMenuDechargeScale();
	afx_msg void OnMenuAccrualAdd();
	afx_msg void OnMenuDepartSet();
	afx_msg void OnMenuEmpDecharge();
	afx_msg void OnMenuEmpCashAdd();
	afx_msg void OnMenuOperator();
	afx_msg void OnMenuBaseProjectSet();
	afx_msg void OnMenuBaseSpecif();
	afx_msg void OnMenuSpecifSet();
	afx_msg void OnMenuPeculiarQuery();
	afx_msg void OnMenuAccountUsedCount();
	afx_msg void OnMenuQueryEmpDecharge();
	afx_msg void OnMenuManualAddCash();
	afx_msg void OnMenuEmpGet();
	afx_msg void OnMenuEmpBalanceCount();
	afx_msg void OnMenuCashPurchase();
	afx_msg void OnMenuitemDoctorOther();
	afx_msg void OnMenuResideCheckin();
	afx_msg void OnMenuResideLocal();
	afx_msg void OnMenuResideRoom();
	afx_msg void OnMenuResideBed();
	afx_msg void OnMenuResideQuery();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CHis2App theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIS2_H__4ABAF145_0D15_4148_83C7_8E25773C584D__INCLUDED_)
