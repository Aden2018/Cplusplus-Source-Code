// MedCodeBase.h: interface for the CMedCodeBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDCODEBASE_H__EF02FBB0_1CBE_4616_8EF9_FE592DA392A1__INCLUDED_)
#define AFX_MEDCODEBASE_H__EF02FBB0_1CBE_4616_8EF9_FE592DA392A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MedCodeQuery.h"

class CMedCodeBase : public CMedCodeQuery  
{
public:
	BOOL OnInitDialog();
	void OnDblClickMshflexgrid1();
	CMedCodeBase();
	virtual ~CMedCodeBase();

};

#endif // !defined(AFX_MEDCODEBASE_H__EF02FBB0_1CBE_4616_8EF9_FE592DA392A1__INCLUDED_)
