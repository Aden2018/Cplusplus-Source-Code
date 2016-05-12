// PayMed.h: interface for the CPayMed class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAYMED_H__EAF1EF90_6F94_4F65_BEF6_742258BB2C95__INCLUDED_)
#define AFX_PAYMED_H__EAF1EF90_6F94_4F65_BEF6_742258BB2C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HuaJia.h"

class CPayMed : public CHuaJia  
{
public:
	void OnRollmed();
	void OnButtonDoctor();
	BOOL PreTranslateMessage(MSG* pMsg);
	void OnOK();
	BOOL OnInitDialog();
	CPayMed();
	virtual ~CPayMed();
	void OnKillfocusEditDoctor(){};
	void OnSetfocusEditDoctor(){};
	void OnDblClickMshflexgrid1(){};
	void OnClickMshflexgrid1(){};
	void OnDblClickMshflexgrid2(){};
	void OnClickMshflexgrid2(){};
	void OnChargePrice(){};
	void OnKillfocusEditMedNum(){};
	void OnSetfocusEditMedNum(){};
	void OnChangeEditX1(){};

};

#endif // !defined(AFX_PAYMED_H__EAF1EF90_6F94_4F65_BEF6_742258BB2C95__INCLUDED_)
