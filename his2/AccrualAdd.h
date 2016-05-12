// AccrualAdd.h: interface for the CAccrualAdd class.
//
//	类描述:
//		有关利率生成操作,包含年度帐户结余利率,以及生成统筹利率
//
//
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCRUALADD_H__029CEB56_A550_4DE6_950B_BA220BD215A9__INCLUDED_)
#define AFX_ACCRUALADD_H__029CEB56_A550_4DE6_950B_BA220BD215A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DoctorWorkLoad.h"

class CAccrualAdd : public CDoctorWorkLoad //CRelateConsumeList  
{
public:
	void OnButtonPrint();
	CComboBox *pc;
	void SetGridHead();
	static UINT  QueryData(LPVOID ps);
	void OnOK();
	BOOL OnInitDialog();
	CAccrualAdd();
	virtual ~CAccrualAdd();

};

#endif // !defined(AFX_ACCRUALADD_H__029CEB56_A550_4DE6_950B_BA220BD215A9__INCLUDED_)
