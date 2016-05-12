// YearDataCountAnalyse.h: interface for the CYearDataCountAnalyse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YEARDATACOUNTANALYSE_H__A2857A89_37D2_41A1_98F2_106CD45A76AE__INCLUDED_)
#define AFX_YEARDATACOUNTANALYSE_H__A2857A89_37D2_41A1_98F2_106CD45A76AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "YearDataCount.h"

class CYearDataCountAnalyse : public CYearDataCount  
{
public:
	void OnDblClickMshflexgrid1();
	static UINT QueryAnalyse(LPVOID ps);
	void SetGridHead();
	void OnOK();
	BOOL OnInitDialog();
	CYearDataCountAnalyse();
	virtual ~CYearDataCountAnalyse();

};

#endif // !defined(AFX_YEARDATACOUNTANALYSE_H__A2857A89_37D2_41A1_98F2_106CD45A76AE__INCLUDED_)
