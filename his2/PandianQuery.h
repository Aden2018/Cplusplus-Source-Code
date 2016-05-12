// PandianQuery.h: interface for the CPandianQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PANDIANQUERY_H__2F9C1073_4D7A_4E14_A223_3636D8663AA2__INCLUDED_)
#define AFX_PANDIANQUERY_H__2F9C1073_4D7A_4E14_A223_3636D8663AA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FormRkListQuery.h"

class CPandianQuery : public CFormRkListQuery  
{
public:
	BOOL OnInitDialog();
	void OnOK();
	CPandianQuery();
	virtual ~CPandianQuery();

};

#endif // !defined(AFX_PANDIANQUERY_H__2F9C1073_4D7A_4E14_A223_3636D8663AA2__INCLUDED_)
