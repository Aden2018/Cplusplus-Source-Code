// ResideCheckOut.h: interface for the CResideCheckOut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESIDECHECKOUT_H__383B2631_260B_42E6_AD16_15BBFA59A4B2__INCLUDED_)
#define AFX_RESIDECHECKOUT_H__383B2631_260B_42E6_AD16_15BBFA59A4B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ResideAddPrice.h"

class CResideCheckOut : public CResideAddPrice  
{
public:
	void OnOK();
	BOOL OnInitDialog();
	CResideCheckOut();
	virtual ~CResideCheckOut();

};

#endif // !defined(AFX_RESIDECHECKOUT_H__383B2631_260B_42E6_AD16_15BBFA59A4B2__INCLUDED_)
