// QueryIC.h: interface for the CQueryIC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUERYIC_H__6B73642D_DEC6_480C_A3D4_98AD716261CE__INCLUDED_)
#define AFX_QUERYIC_H__6B73642D_DEC6_480C_A3D4_98AD716261CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DialogGhQuery.h"

class CQueryIC : public CDialogGhQuery  
{
public:
	BOOL OnInitDialog();
	static UINT  QueryICList(LPVOID ps);
	void OnOK();
	CQueryIC();
	virtual ~CQueryIC();

};

#endif // !defined(AFX_QUERYIC_H__6B73642D_DEC6_480C_A3D4_98AD716261CE__INCLUDED_)
