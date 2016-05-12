// StandardSubsidyAdd.h: interface for the CStandardSubsidyAdd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STANDARDSUBSIDYADD_H__48901187_982F_41B0_B615_456A72EAFCFB__INCLUDED_)
#define AFX_STANDARDSUBSIDYADD_H__48901187_982F_41B0_B615_456A72EAFCFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseProjectSet.h"

class CStandardSubsidyAdd : public CBaseProjectSet  
{
public:
	void OnCancel();
	void OnOK();
	BOOL OnInitDialog();
	CStandardSubsidyAdd();
	virtual ~CStandardSubsidyAdd();

};

#endif // !defined(AFX_STANDARDSUBSIDYADD_H__48901187_982F_41B0_B615_456A72EAFCFB__INCLUDED_)
