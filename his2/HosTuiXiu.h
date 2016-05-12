// HosTuiXiu.h: interface for the CHosTuiXiu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOSTUIXIU_H__2901CA19_F13A_45F5_B959_73A0D73E519F__INCLUDED_)
#define AFX_HOSTUIXIU_H__2901CA19_F13A_45F5_B959_73A0D73E519F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OtherDecharge.h"

class CHosTuiXiu : public COtherDecharge  
{
public:
	BOOL OnInitDialog();
	void OnOK();
	UINT iType;
	CString strBm,strName,strSex;
	void OnButtonA();
	CHosTuiXiu();
	virtual ~CHosTuiXiu();

};

#endif // !defined(AFX_HOSTUIXIU_H__2901CA19_F13A_45F5_B959_73A0D73E519F__INCLUDED_)
