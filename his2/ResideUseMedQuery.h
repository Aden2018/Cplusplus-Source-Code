// ResideUseMedQuery.h: interface for the CResideUseMedQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESIDEUSEMEDQUERY_H__A0B70A70_C32D_46D2_9FE6_7FAFD79751AA__INCLUDED_)
#define AFX_RESIDEUSEMEDQUERY_H__A0B70A70_C32D_46D2_9FE6_7FAFD79751AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DoctorWorkLoad.h"

class CResideUseMedQuery : public CDoctorWorkLoad  
{
public:
	CString strSerial;
	static UINT QueryUseMed(LPVOID ps);
	void OnOK();
	void SetGridHead();
	BOOL OnInitDialog();
	CResideUseMedQuery();
	virtual ~CResideUseMedQuery();

};

#endif // !defined(AFX_RESIDEUSEMEDQUERY_H__A0B70A70_C32D_46D2_9FE6_7FAFD79751AA__INCLUDED_)
