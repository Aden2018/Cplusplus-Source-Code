// BuySellStockQuery.h: interface for the CBuySellStockQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUYSELLSTOCKQUERY_H__6CB1431C_C1E3_4691_A753_DB9ABF85C5EC__INCLUDED_)
#define AFX_BUYSELLSTOCKQUERY_H__6CB1431C_C1E3_4691_A753_DB9ABF85C5EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EverydayConsumeQuery.h"

class CBuySellStockQuery : public CEverydayConsumeQuery  
{
public:
	static UINT QueryDatabase(LPVOID ps);
	void OnOK();
	BOOL OnInitDialog();
	CBuySellStockQuery();
	virtual ~CBuySellStockQuery();

};

#endif // !defined(AFX_BUYSELLSTOCKQUERY_H__6CB1431C_C1E3_4691_A753_DB9ABF85C5EC__INCLUDED_)
