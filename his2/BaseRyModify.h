// BaseRyModify.h: interface for the CBaseRyModify class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASERYMODIFY_H__D5292E3F_B70F_4B0D_BF5E_70E26A2B28FE__INCLUDED_)
#define AFX_BASERYMODIFY_H__D5292E3F_B70F_4B0D_BF5E_70E26A2B28FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseRyAdd.h"
#include "mshflexgrid.h"	// Added by ClassView

class CBaseRyModify : public CBaseRyAdd  
{
public:
	BOOL OnInitDialog();
	void OnOK();
	long selRow;
	CMSHFlexGrid *pGrid;
	CBaseRyModify();
	virtual ~CBaseRyModify();

};

#endif // !defined(AFX_BASERYMODIFY_H__D5292E3F_B70F_4B0D_BF5E_70E26A2B28FE__INCLUDED_)
