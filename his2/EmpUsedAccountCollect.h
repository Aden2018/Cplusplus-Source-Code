// EmpUsedAccountCollect.h: interface for the CEmpUsedAccountCollect class.
//
//	类描述:
//		个人帐户使用汇总
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMPUSEDACCOUNTCOLLECT_H__E139F6DF_C3B0_42C3_8012_8B8B856468B8__INCLUDED_)
#define AFX_EMPUSEDACCOUNTCOLLECT_H__E139F6DF_C3B0_42C3_8012_8B8B856468B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PeculiarInput.h"

class CEmpUsedAccountCollect : public CPeculiarInput  
{
public:
	void OnOK();
	static UINT QueryData2(LPVOID ps);
	BOOL OnInitDialog();
	CEmpUsedAccountCollect();
	virtual ~CEmpUsedAccountCollect();

};

#endif // !defined(AFX_EMPUSEDACCOUNTCOLLECT_H__E139F6DF_C3B0_42C3_8012_8B8B856468B8__INCLUDED_)
