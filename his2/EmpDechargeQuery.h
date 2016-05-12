// EmpDechargeQuery.h: interface for the CEmpDechargeQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMPDECHARGEQUERY_H__6BA8F4B4_EADB_4B31_ACA5_9603B2DC836A__INCLUDED_)
#define AFX_EMPDECHARGEQUERY_H__6BA8F4B4_EADB_4B31_ACA5_9603B2DC836A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "peculiarInput.h"

class CEmpDechargeQuery : public CPeculiarInput  
{
public:
	void OnB2();
	void OnB1();
	void OnOK();
	static UINT QueryData2(LPVOID ps);
	BOOL OnInitDialog();
	CEmpDechargeQuery();
	virtual ~CEmpDechargeQuery();
	virtual void OnDblClickMshflexgrid1();
	virtual void OnClickMshflexgrid1();
};

#endif // !defined(AFX_EMPDECHARGEQUERY_H__6BA8F4B4_EADB_4B31_ACA5_9603B2DC836A__INCLUDED_)
