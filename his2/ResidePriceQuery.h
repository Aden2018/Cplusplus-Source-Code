// ResidePriceQuery.h: interface for the CResidePriceQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESIDEPRICEQUERY_H__335D4FEA_611D_4E23_9F2E_87BAEF5FFC3D__INCLUDED_)
#define AFX_RESIDEPRICEQUERY_H__335D4FEA_611D_4E23_9F2E_87BAEF5FFC3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ResideUseMedQuery.h"

class CResidePriceQuery : public CResideUseMedQuery  
{
public:
	static UINT QueryAddPrice(LPVOID ps);
	void SetGridHead();
	void OnOK();
	BOOL OnInitDialog();
	CResidePriceQuery();
	virtual ~CResidePriceQuery();

};

#endif // !defined(AFX_RESIDEPRICEQUERY_H__335D4FEA_611D_4E23_9F2E_87BAEF5FFC3D__INCLUDED_)
