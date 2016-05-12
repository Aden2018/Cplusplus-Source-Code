// PayMedNum.h: interface for the CPayMedNum class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAYMEDNUM_H__97533BE3_EF42_48E5_A3DC_6D0938ABA06B__INCLUDED_)
#define AFX_PAYMEDNUM_H__97533BE3_EF42_48E5_A3DC_6D0938ABA06B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HuaJiaList.h"

class CPayMedNum : public CHuaJiaList  
{
public:
	void OnDblClickMshflexgrid1();
	void OnOK();
	BOOL OnInitDialog();
	CPayMedNum();
	virtual ~CPayMedNum();

private:
	void ShowReside();
	void ShowPublic();
};

#endif // !defined(AFX_PAYMEDNUM_H__97533BE3_EF42_48E5_A3DC_6D0938ABA06B__INCLUDED_)
