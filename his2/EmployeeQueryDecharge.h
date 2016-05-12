// EmployeeQueryDecharge.h: interface for the CEmployeeQueryDecharge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMPLOYEEQUERYDECHARGE_H__E46C15F7_E0F8_49A8_A47B_04FEDEDB4363__INCLUDED_)
#define AFX_EMPLOYEEQUERYDECHARGE_H__E46C15F7_E0F8_49A8_A47B_04FEDEDB4363__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EmployeeQuery.h"

class CEmployeeQueryDecharge : public CEmployeeQuery  
{
public:
	void OnClickMshflexgrid2();
	void OnDblClickMshflexgrid2();
	void OnOK();
	void SetGridHead(void);
	BOOL OnInitDialog();
	CEmployeeQueryDecharge();
	virtual ~CEmployeeQueryDecharge();

};

#endif // !defined(AFX_EMPLOYEEQUERYDECHARGE_H__E46C15F7_E0F8_49A8_A47B_04FEDEDB4363__INCLUDED_)
