// CashBuySellStock.h: interface for the CCashBuySellStock class.
// Describe:
//		金额关系进销存统计,也即上其药房库存金额,本期消耗金额,当前
//	库存金额关系.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CASHBUYSELLSTOCK_H__C83F12AD_9347_4C9D_AD5C_1A993457557C__INCLUDED_)
#define AFX_CASHBUYSELLSTOCK_H__C83F12AD_9347_4C9D_AD5C_1A993457557C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AccrualAdd.h"

class CCashBuySellStock : public CAccrualAdd  
{
public:
	static UINT QueryDatax(LPVOID ps);
	void OnOK();
	void OnSelchangeCombo2();
	BOOL OnInitDialog();
	CCashBuySellStock();
	virtual ~CCashBuySellStock();

};

#endif // !defined(AFX_CASHBUYSELLSTOCK_H__C83F12AD_9347_4C9D_AD5C_1A993457557C__INCLUDED_)
