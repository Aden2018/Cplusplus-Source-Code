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

#define ROLE_BODYCHECK_ADD 1 //������
#define ROLE_BODYCHECK_DELETE 2 //ɾ��
#define ROLE_BODYCHECK_MODIFY 3//�޸�
#define ROLE_BODYCHECK_PRINT 4 //��ӡ
#define ROLE_STARTDOCTOR_GH 5 //�Һ�
#define ROLE_STARTDOCTOR_HJ 6 //�����շ�
#define ROLE_STARTDOCTOR_CY 7 // ȡҩ
#define ROLE_MED_STATUS_MODIFY 8 //ҩƷ״̬�޸�
#define ROLE_STARTDOCTOR_TY 9 //��ҩ
#define ROLE_MED_RK 10 //�ɹ����
#define ROLE_MED_ZK 11 //ת��
#define ROLE_ROLE_SET 12    //Ȩ������
#define ROLE_MED_BF 13 //ҩƷ����

#define ROLE_MED_CHECK_ACCOUNTS 14 //ҩƷ��ӯ �̿�����
#define ROLE_MED_OTHER_CONSUME  15 //ҩƷ��������
#define ROLE_STOCK_GENERIC  16 //�ɹ��ƻ�����
#define ROLE_NOTIFY_DELETE 17 //�칫ϵͳ��֪ͨɾ������
#define ROLE_NOTIFY_SEND 18 //����֪ͨ����
#define ROLE_DECHARGE_RELATE 19 //��������������ñ���
#define ROLE_MED_DL_MODIFY 20  //ҩƷ����
#define ROLE_MED_XL_MODIFY 21  //С���޸�
#define ROLE_LOGIN_DENY     22 //��ֹ�޸������û���¼���
#define ROLE_RELATE_AUTO_ADDCASH  23//������������Զ���Ǯ
#define ROLE_RELATE_ADD 24 //������Ա���
#define ROLE_RELATE_MODIFY 25 //������Ա�޸�
#define ROLE_RELATE_KILL 26 //������Աע��
/////////////////////////////////////
#define ROLE_EMP_EDIT 27 //ְ����Ϣ�޸�(��������,����,�޸�,ɾ��,��Ա��������)
#define ROLE_OTHER_DECHARGE 28 //������Ա��ֵ,ɾ��
#define ROLE_EMP_DECHARGE 29 //ְ������,ɾ��
#define ROLE_BASE_SET 30//������,������Ŀ,���������趨,������Աά��
#define ROLE_DECHARGE_DELETE 31 //

#define ROLE_SOCIETY_HEALTH_ADD 32 //�����Ա�����Ϣ����
#define ROLE_SOCIETY_HEALTH_MODIFY 33 //�����Ա�����Ϣ�޸�
#define ROLE_SOCIETY_HEALTH_PRINT 34 //�����Ա�����Ϣ��ӡ
#define ROLE_SOCIETY_HEALTH_DEL 35 //�����Ա�����Ϣɾ��


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
