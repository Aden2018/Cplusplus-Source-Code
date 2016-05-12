// EmployeeRelateQueryForFee.h: interface for the CEmployeeRelateQueryForFee class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMPLOYEERELATEQUERYFORFEE_H__0FAC2437_1358_4D4B_8F5D_C7622F1656F9__INCLUDED_)
#define AFX_EMPLOYEERELATEQUERYFORFEE_H__0FAC2437_1358_4D4B_8F5D_C7622F1656F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EmployeeQuery.h"

class CEmployeeRelateQueryForFee : public CEmployeeQuery  
{
public:
	void OnOK();
	BOOL OnInitDialog();
	CEmployeeRelateQueryForFee();
	virtual ~CEmployeeRelateQueryForFee();

};

#endif // !defined(AFX_EMPLOYEERELATEQUERYFORFEE_H__0FAC2437_1358_4D4B_8F5D_C7622F1656F9__INCLUDED_)
