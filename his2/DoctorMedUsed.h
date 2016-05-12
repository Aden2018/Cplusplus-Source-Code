// DoctorMedUsed.h: interface for the CDoctorMedUsed class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCTORMEDUSED_H__CC746E25_89EA_43BA_B577_4D0CF24E6F77__INCLUDED_)
#define AFX_DOCTORMEDUSED_H__CC746E25_89EA_43BA_B577_4D0CF24E6F77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "manMedused.h"

class CDoctorMedUsed : public CManMedused  
{
public:
	int last_day;
	void OnOK();
	void OnDblClickMshflexgrid1();
	static	UINT QueryDataX(LPVOID ps);
	BOOL OnInitDialog();
	CDoctorMedUsed();
	virtual ~CDoctorMedUsed();

};

#endif // !defined(AFX_DOCTORMEDUSED_H__CC746E25_89EA_43BA_B577_4D0CF24E6F77__INCLUDED_)
