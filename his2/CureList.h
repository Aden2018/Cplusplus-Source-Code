// CureList.h: interface for the CCureList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURELIST_H__4B4EE8A3_A033_42B3_86AD_9E75F66FF461__INCLUDED_)
#define AFX_CURELIST_H__4B4EE8A3_A033_42B3_86AD_9E75F66FF461__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EmployeeQuery.h"

class CCureList : public CEmployeeQuery  
{
public:
	void OnShowWindow(BOOL bShow, UINT nStatus);
	void SetGridHead();
	void OnSelchangeCombo1();
	long curRow;
	void OnClickMshflexgrid2();
	void OnDblClickMshflexgrid2();
	void OnOK();
	BOOL OnInitDialog(void);
	CCureList();
	virtual ~CCureList();

};

#endif // !defined(AFX_CURELIST_H__4B4EE8A3_A033_42B3_86AD_9E75F66FF461__INCLUDED_)
