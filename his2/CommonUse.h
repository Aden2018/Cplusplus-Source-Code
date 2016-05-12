// CommonUse.h: interface for the CCommonUse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMONUSE_H__52AF374D_2666_404C_9F82_D1E36A2A0E8B__INCLUDED_)
#define AFX_COMMONUSE_H__52AF374D_2666_404C_9F82_D1E36A2A0E8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MoveKf.h"

class CCommonUse : public CMoveKf  
{
public:
	void OnOK();
	BOOL OnInitDialog();
	CCommonUse();
	virtual ~CCommonUse();

};

#endif // !defined(AFX_COMMONUSE_H__52AF374D_2666_404C_9F82_D1E36A2A0E8B__INCLUDED_)
