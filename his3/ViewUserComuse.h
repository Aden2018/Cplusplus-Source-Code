// ViewUserComuse.h: interface for the CViewUserComuse class.
//* ���:	2008/11/1   ������
//* ��ʾ�û�������ϸ�б�
//*
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWUSERCOMUSE_H__E46E6949_A040_46AB_8FD7_9785A12C0C40__INCLUDED_)
#define AFX_VIEWUSERCOMUSE_H__E46E6949_A040_46AB_8FD7_9785A12C0C40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SickGetMedView.h"

class CViewUserComuse : public CSickGetMedView  
{
public:
	BOOL OnInitDialog();
	void OnOK();
	CViewUserComuse();
	virtual ~CViewUserComuse();

};

#endif // !defined(AFX_VIEWUSERCOMUSE_H__E46E6949_A040_46AB_8FD7_9785A12C0C40__INCLUDED_)
