// EmployeeNoworkQuery.h: interface for the CEmployeeNoworkQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMPLOYEENOWORKQUERY_H__F3A56A3C_9570_4C55_9326_ECB5E022302C__INCLUDED_)
#define AFX_EMPLOYEENOWORKQUERY_H__F3A56A3C_9570_4C55_9326_ECB5E022302C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EmployeeQuery.h"

class CEmployeeNoworkQuery : public CEmployeeQuery  
{
public:
	void OnSelchangeCombo1();
	void OnOK();
	BOOL OnInitDialog();
	CEmployeeNoworkQuery();
	virtual ~CEmployeeNoworkQuery();

};

#endif // !defined(AFX_EMPLOYEENOWORKQUERY_H__F3A56A3C_9570_4C55_9326_ECB5E022302C__INCLUDED_)
