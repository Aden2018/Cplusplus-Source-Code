// ManMedused.h: interface for the CManMedused class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANMEDUSED_H__9C63EF55_B07C_4392_946E_7A1D983C1457__INCLUDED_)
#define AFX_MANMEDUSED_H__9C63EF55_B07C_4392_946E_7A1D983C1457__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DoctorWorkLoad.h"

class CManMedused : public CDoctorWorkLoad  
{
public:
	static UINT QueryData(LPVOID ps);
	void OnOK();
	CString strBM,strTmp[4];
	BOOL OnInitDialog();
	CManMedused();
	virtual ~CManMedused();
	COleDateTime date;
	int iday;

protected:
	void OnDblClickMshflexgrid1();
};

#endif // !defined(AFX_MANMEDUSED_H__9C63EF55_B07C_4392_946E_7A1D983C1457__INCLUDED_)
