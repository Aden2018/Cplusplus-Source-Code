// OtherHealthForModify.h: interface for the COtherHealthForModify class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTHERHEALTHFORMODIFY_H__6D687AFB_D9D7_4049_8B16_14945C8537D3__INCLUDED_)
#define AFX_OTHERHEALTHFORMODIFY_H__6D687AFB_D9D7_4049_8B16_14945C8537D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OtherHealth.h"

class COtherHealthForModify : public COtherHealth  
{
public:
	CString xuexin;
	CString str[6],gan[6],riqi;
	void OnOK();
	BOOL OnInitDialog();
	COtherHealthForModify();
	virtual ~COtherHealthForModify();

};

#endif // !defined(AFX_OTHERHEALTHFORMODIFY_H__6D687AFB_D9D7_4049_8B16_14945C8537D3__INCLUDED_)
