// BaseOtherSickSet.h: interface for the CBaseOtherSickSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEOTHERSICKSET_H__E5350797_471C_4AA4_A204_B3B1D264193E__INCLUDED_)
#define AFX_BASEOTHERSICKSET_H__E5350797_471C_4AA4_A204_B3B1D264193E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OtherSickQuery.h"

class CBaseOtherSickSet : public COtherSickQuery  
{
public:
	void OnRclickListQuery(NMHDR* pNMHDR, LRESULT* pResult);
	void OnDblclkListQuery(NMHDR* pNMHDR, LRESULT* pResult);
	BOOL OnInitDialog();
	void OnOK();
	CBaseOtherSickSet();
	virtual ~CBaseOtherSickSet();

};

#endif // !defined(AFX_BASEOTHERSICKSET_H__E5350797_471C_4AA4_A204_B3B1D264193E__INCLUDED_)
