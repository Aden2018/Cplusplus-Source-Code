// UserMed.h: interface for the CUserMed class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERMED_H__B65C33D3_D19E_4787_8863_6CBD4E2A7D00__INCLUDED_)
#define AFX_USERMED_H__B65C33D3_D19E_4787_8863_6CBD4E2A7D00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PayMed.h"

class CUserMed : public CPayMed  
{
public:
	double dbAccount;
	double dbCash;
	BOOL OnInitDialog();
	void OnOK();
	CUserMed();
	virtual ~CUserMed();

protected:
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

#endif // !defined(AFX_USERMED_H__B65C33D3_D19E_4787_8863_6CBD4E2A7D00__INCLUDED_)
