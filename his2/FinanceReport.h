// FinanceReport.h: interface for the CFinanceReport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FINANCEREPORT_H__5F38148E_0E6B_4415_94A2_5EFEF1840645__INCLUDED_)
#define AFX_FINANCEREPORT_H__5F38148E_0E6B_4415_94A2_5EFEF1840645__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DoctorWorkLoad.h"

class CFinanceReport : public CDoctorWorkLoad  
{
public:
	void OnButtonPrint();
	static UINT QueryReport(LPVOID ps);
	void OnOK();
	BOOL OnInitDialog();
	void SetGridHead();
	CFinanceReport();
	virtual ~CFinanceReport();

};

#endif // !defined(AFX_FINANCEREPORT_H__5F38148E_0E6B_4415_94A2_5EFEF1840645__INCLUDED_)
