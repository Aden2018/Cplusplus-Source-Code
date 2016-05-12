// StandardSubsidySet.h: interface for the CStandardSubsidySet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STANDARDSUBSIDYSET_H__A0A5B5D8_B9E5_49BA_A743_AD170FCA359E__INCLUDED_)
#define AFX_STANDARDSUBSIDYSET_H__A0A5B5D8_B9E5_49BA_A743_AD170FCA359E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StandardSubsidy.h"

class CStandardSubsidySet : public CStandardSubsidy  
{
public:
	void OnDblclkListQuery(NMHDR *pNMHDR, LRESULT *pResult);
	void OnRclickListQuery(NMHDR* pNMHDR, LRESULT* pResult);
	CStandardSubsidySet();
	virtual ~CStandardSubsidySet();

};

#endif // !defined(AFX_STANDARDSUBSIDYSET_H__A0A5B5D8_B9E5_49BA_A743_AD170FCA359E__INCLUDED_)
