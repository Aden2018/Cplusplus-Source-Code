// BasisInsureList.h: interface for the CBasisInsureList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASISINSURELIST_H__75541443_174F_4444_8F9B_42EC77DE9011__INCLUDED_)
#define AFX_BASISINSURELIST_H__75541443_174F_4444_8F9B_42EC77DE9011__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EmployeeQuery.h"

class CBasisInsureList : public CEmployeeQuery  
{
public:
	void OnMenuQuickBaseryModify();
	void OnMenuQuickBaseryViewpassword();
	void OnMenuQuickBaseryDel();
	void OnClickMshflexgrid2();
	BOOL PreTranslateMessage(MSG* pMsg);
	void OnOK();
	BOOL OnInitDialog();
	CBasisInsureList();
	virtual ~CBasisInsureList();

};

#endif // !defined(AFX_BASISINSURELIST_H__75541443_174F_4444_8F9B_42EC77DE9011__INCLUDED_)
