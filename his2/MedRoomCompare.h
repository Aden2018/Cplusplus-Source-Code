// MedRoomCompare.h: interface for the CMedRoomCompare class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDROOMCOMPARE_H__7E24F108_D76C_4C4C_9F44_82F565C5D510__INCLUDED_)
#define AFX_MEDROOMCOMPARE_H__7E24F108_D76C_4C4C_9F44_82F565C5D510__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GenericStockMed.h"

class CMedRoomCompare : public CGenericStockMed  
{
public:
	void OnDblClickMshflexgrid1();
	CStringArray strMc,strBm;
	void SetGridHead();
	void OnOK();
	BOOL OnInitDialog();
	CMedRoomCompare();
	virtual ~CMedRoomCompare();

};

#endif // !defined(AFX_MEDROOMCOMPARE_H__7E24F108_D76C_4C4C_9F44_82F565C5D510__INCLUDED_)
