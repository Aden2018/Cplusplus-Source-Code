// EmployeeRelateQuery.h: interface for the CEmployeeRelateQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMPLOYEERELATEQUERY_H__ACDF4367_4EBE_44BA_9936_60E5F15162C3__INCLUDED_)
#define AFX_EMPLOYEERELATEQUERY_H__ACDF4367_4EBE_44BA_9936_60E5F15162C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EmployeeNoworkQuery.h"

class CEmployeeRelateQuery : public CEmployeeQuery  
{
public:
	BOOL OnInitDialog();
	void OnOK();
	CEmployeeRelateQuery();
	virtual ~CEmployeeRelateQuery();

	void OnMenuRelateAdd();
	void OnMenuRelateKill();
	void OnMenuRelateModify();
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_EMPLOYEERELATEQUERY_H__ACDF4367_4EBE_44BA_9936_60E5F15162C3__INCLUDED_)
