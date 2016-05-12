// GenericMedCode.h: interface for the CGenericMedCode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERICMEDCODE_H__3CB0B063_9429_4603_975C_A6E12AC7165E__INCLUDED_)
#define AFX_GENERICMEDCODE_H__3CB0B063_9429_4603_975C_A6E12AC7165E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MedCodeQuery.h"

class CGenericMedCode : public CMedCodeQuery  
{
public:
	void OnDblClickMshflexgrid1();
	BOOL OnInitDialog();
	CGenericMedCode();
	virtual ~CGenericMedCode();

};

#endif // !defined(AFX_GENERICMEDCODE_H__3CB0B063_9429_4603_975C_A6E12AC7165E__INCLUDED_)
