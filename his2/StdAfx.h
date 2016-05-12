// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__56A1F037_C8BF_4295_96CE_EBD6BF7955B3__INCLUDED_)
#define AFX_STDAFX_H__56A1F037_C8BF_4295_96CE_EBD6BF7955B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define ROLE_BODYCHECK_ADD 1 //体检添加
#define ROLE_BODYCHECK_DELETE 2 //删除
#define ROLE_BODYCHECK_MODIFY 3//修改
#define ROLE_BODYCHECK_PRINT 4 //打印
#define ROLE_STARTDOCTOR_GH 5 //挂号
#define ROLE_STARTDOCTOR_HJ 6 //划价收费
#define ROLE_STARTDOCTOR_CY 7 // 取药
#define ROLE_MED_STATUS_MODIFY 8 //药品状态修改
#define ROLE_STARTDOCTOR_TY 9 //退药
#define ROLE_MED_RK 10 //采购入库
#define ROLE_MED_ZK 11 //转库
#define ROLE_ROLE_SET 12    //权限设置
#define ROLE_MED_BF 13 //药品报废

#define ROLE_MED_CHECK_ACCOUNTS 14 //药品盘盈 盘亏设置
#define ROLE_MED_OTHER_CONSUME  15 //药品其它消耗
#define ROLE_STOCK_GENERIC  16 //采购计划生成
#define ROLE_NOTIFY_DELETE 17 //办公系统中通知删除功能
#define ROLE_NOTIFY_SEND 18 //发送通知功能
#define ROLE_DECHARGE_RELATE 19 //供养亲属外诊费用报销
#define ROLE_MED_DL_MODIFY 20  //药品大类
#define ROLE_MED_XL_MODIFY 21  //小类修改
#define ROLE_LOGIN_DENY     22 //禁止修改其它用户登录情况
#define ROLE_RELATE_AUTO_ADDCASH  23//供养亲属年度自动充钱
#define ROLE_RELATE_ADD 24 //供养人员添加
#define ROLE_RELATE_MODIFY 25 //供养人员修改
#define ROLE_RELATE_KILL 26 //供养人员注销
/////////////////////////////////////
#define ROLE_EMP_EDIT 27 //职工信息修改(包括密码,新增,修改,删除,人员性质设置)
#define ROLE_OTHER_DECHARGE 28 //其它人员充值,删除
#define ROLE_EMP_DECHARGE 29 //职工报销,删除
#define ROLE_BASE_SET 30//厂部门,费用项目,特殊性质设定,操作人员维护
#define ROLE_DECHARGE_DELETE 31 //

#define ROLE_SOCIETY_HEALTH_ADD 32 //社会人员体检信息增加
#define ROLE_SOCIETY_HEALTH_MODIFY 33 //社会人员体检信息修改
#define ROLE_SOCIETY_HEALTH_PRINT 34 //社会人员体检信息打印
#define ROLE_SOCIETY_HEALTH_DEL 35 //社会人员体检信息删除


/////////////////////////////////////////
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
#include "icrsint.h"


extern _ConnectionPtr HospitalConnect;
extern _RecordsetPtr recSet;
void WriteDebug(CString );
extern struct logon_information LoginInformation;

struct logon_information{
	CString user;
	CString kfmc;
	CString kfbm;
	CString job;
	CString user_code;
	char path[MAX_PATH];
};



struct DoublePointer {
		LPVOID pGrid;
		LPVOID pQuery;
		LPVOID p2,p3,p4,pWnd;
	};

#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__56A1F037_C8BF_4295_96CE_EBD6BF7955B3__INCLUDED_)
