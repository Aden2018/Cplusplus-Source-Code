// DechargeScale.h: interface for the CDechargeScale class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECHARGESCALE_H__21D460EF_B1BB_44C9_974C_4A7548A5A266__INCLUDED_)
#define AFX_DECHARGESCALE_H__21D460EF_B1BB_44C9_974C_4A7548A5A266__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AccountScale.h"

class CDechargeScale : public CAccountScale  
{
public:
	void OnOK();
	BOOL OnInitDialog();
	CDechargeScale();
	virtual ~CDechargeScale();

};

#endif // !defined(AFX_DECHARGESCALE_H__21D460EF_B1BB_44C9_974C_4A7548A5A266__INCLUDED_)
