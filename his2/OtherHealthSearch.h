// OtherHealthSearch.h: interface for the COtherHealthSearch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTHERHEALTHSEARCH_H__F692E2FD_02A2_45F3_ABFC_977A1B3F2792__INCLUDED_)
#define AFX_OTHERHEALTHSEARCH_H__F692E2FD_02A2_45F3_ABFC_977A1B3F2792__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HealthSearch.h"

class COtherHealthSearch : public CHealthSearch  
{
public:
	BOOL OnInitDialog();
	void OnFastMenuSelect();
	void OnDelete();
	void OnPrintSelect(void);
	void OnModify();
	void OnOK();
	void OnAdd();
	COtherHealthSearch();
	virtual ~COtherHealthSearch();

};

#endif // !defined(AFX_OTHERHEALTHSEARCH_H__F692E2FD_02A2_45F3_ABFC_977A1B3F2792__INCLUDED_)
