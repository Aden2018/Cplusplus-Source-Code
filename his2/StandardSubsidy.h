// StandardSubsidy.h: interface for the CStandardSubsidy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STANDARDSUBSIDY_H__F704AA12_A1F1_466E_B766_96396229C477__INCLUDED_)
#define AFX_STANDARDSUBSIDY_H__F704AA12_A1F1_466E_B766_96396229C477__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OtherSickQuery.h"

class CStandardSubsidy : public COtherSickQuery  
{
public:
	BOOL OnInitDialog();
	void OnOK();
	void OnDblclkListQuery(NMHDR* pNMHDR, LRESULT* pResult);
	CStandardSubsidy();
	virtual ~CStandardSubsidy();

};

#endif // !defined(AFX_STANDARDSUBSIDY_H__F704AA12_A1F1_466E_B766_96396229C477__INCLUDED_)
