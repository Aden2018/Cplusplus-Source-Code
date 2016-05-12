// BaseChargeSet.h: interface for the CBaseChargeSet class.
//
// 类描述:
//		费用项目名称设置
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASECHARGESET_H__D8FFFE3A_74A9_4596_AFA0_C26DD0F36A6C__INCLUDED_)
#define AFX_BASECHARGESET_H__D8FFFE3A_74A9_4596_AFA0_C26DD0F36A6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OperatorSet.h"

class CBaseChargeSet : public COperatorSet  
{
public:
	void OnExcel();
	void OnAdd();
	void OnOK();
	BOOL OnInitDialog();
	void OnSelchangeCombo1();
	void OnClickMshflexgrid1();
	void OnDblClickMshflexgrid1();
	CBaseChargeSet();
	virtual ~CBaseChargeSet();

};

#endif // !defined(AFX_BASECHARGESET_H__D8FFFE3A_74A9_4596_AFA0_C26DD0F36A6C__INCLUDED_)
