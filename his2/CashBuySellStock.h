// CashBuySellStock.h: interface for the CCashBuySellStock class.
// Describe:
//		����ϵ������ͳ��,Ҳ������ҩ�������,�������Ľ��,��ǰ
//	������ϵ.
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
