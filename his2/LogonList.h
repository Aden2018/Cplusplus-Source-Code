// LogonList.h: interface for the CLogonList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGONLIST_H__41A6B267_332A_46EF_A1C6_E6A53715667A__INCLUDED_)
#define AFX_LOGONLIST_H__41A6B267_332A_46EF_A1C6_E6A53715667A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OtherSickQuery.h"

class CLogonList : public COtherSickQuery  
{
public:
	void OnRclickListQuery(NMHDR* pNMHDR, LRESULT* pResult);
	BOOL PreTranslateMessage(MSG* pMsg);
	void OnOK();
	void OnDblclkListQuery(NMHDR* pNMHDR, LRESULT* pResult);
	BOOL OnInitDialog();
	CLogonList();
	virtual ~CLogonList();

};

#endif // !defined(AFX_LOGONLIST_H__41A6B267_332A_46EF_A1C6_E6A53715667A__INCLUDED_)
