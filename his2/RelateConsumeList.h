// RelateConsumeList.h: interface for the CRelateConsumeList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RELATECONSUMELIST_H__6B201FA0_FAEF_4BFF_BDCE_56D72910B69E__INCLUDED_)
#define AFX_RELATECONSUMELIST_H__6B201FA0_FAEF_4BFF_BDCE_56D72910B69E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DoctorWorkLoad.h"

class CRelateConsumeList : public CDoctorWorkLoad  
{
public:
	BOOL OnInitDialog();
	void SetGridHead();
	static UINT QueryConsume(LPVOID ps);
	void OnOK();
	CRelateConsumeList();
	virtual ~CRelateConsumeList();

};

#endif // !defined(AFX_RELATECONSUMELIST_H__6B201FA0_FAEF_4BFF_BDCE_56D72910B69E__INCLUDED_)
