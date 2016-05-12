// ModifyMedRec.h: interface for the CModifyMedRec class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODIFYMEDREC_H__78A0D5E5_36CF_480D_BAC2_AFCAE5A15E4F__INCLUDED_)
#define AFX_MODIFYMEDREC_H__78A0D5E5_36CF_480D_BAC2_AFCAE5A15E4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RelateCharge.h"

class CModifyMedRec : public CRelateCharge  
{
public:
	void OnClickMshflexgrid1();
	void OnButtonDeleteRow();
	void OnButtonAdd();
	void OnOK();
	void SetGridHead();
	BOOL OnInitDialog();
	CModifyMedRec();
	virtual ~CModifyMedRec();

};

#endif // !defined(AFX_MODIFYMEDREC_H__78A0D5E5_36CF_480D_BAC2_AFCAE5A15E4F__INCLUDED_)
