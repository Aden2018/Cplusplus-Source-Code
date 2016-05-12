// EmployeeModify.h: interface for the CEmployeeModify class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMPLOYEEMODIFY_H__984E1427_3DA3_41F8_BC6D_FD1F53A8D4B3__INCLUDED_)
#define AFX_EMPLOYEEMODIFY_H__984E1427_3DA3_41F8_BC6D_FD1F53A8D4B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Employee.h"

class CEmployeeModify : public CEmployee  
{
public:
	CString strTmp;
	void OnOK();
	BOOL OnInitDialog();
	CEmployeeModify();
	virtual ~CEmployeeModify();

};

#endif // !defined(AFX_EMPLOYEEMODIFY_H__984E1427_3DA3_41F8_BC6D_FD1F53A8D4B3__INCLUDED_)
