// AddHealthForModify.h: interface for the CAddHealthForModify class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADDHEALTHFORMODIFY_H__686BF890_2CC0_46B1_A3DF_4B832426E575__INCLUDED_)
#define AFX_ADDHEALTHFORMODIFY_H__686BF890_2CC0_46B1_A3DF_4B832426E575__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AddHealth.h"

class CAddHealthForModify : public CAddHealth  
{
public:
	CString xuexin;
	void OnOK();
	CString str[6],gan[6],riqi;
	BOOL OnInitDialog();
	CAddHealthForModify();
	virtual ~CAddHealthForModify();

};

#endif // !defined(AFX_ADDHEALTHFORMODIFY_H__686BF890_2CC0_46B1_A3DF_4B832426E575__INCLUDED_)
