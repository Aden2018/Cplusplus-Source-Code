// MonthConsumeList.h: interface for the CMonthConsumeList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONTHCONSUMELIST_H__1B1EB16B_B4F3_46E3_A03A_269E7241352F__INCLUDED_)
#define AFX_MONTHCONSUMELIST_H__1B1EB16B_B4F3_46E3_A03A_269E7241352F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DoctorWorkLoad.h"

class CMonthConsumeList : public CDoctorWorkLoad  
{
public:
	void OnDblClickMshflexgrid1();
	static UINT QueryMonth(LPVOID ps);
	void SetGridHead();
	void OnOK();
	BOOL OnInitDialog();
	CMonthConsumeList();
	virtual ~CMonthConsumeList();

};

#endif // !defined(AFX_MONTHCONSUMELIST_H__1B1EB16B_B4F3_46E3_A03A_269E7241352F__INCLUDED_)
