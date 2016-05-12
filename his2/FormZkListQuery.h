// FormZkListQuery.h: interface for the CFormZkListQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMZKLISTQUERY_H__5FE93A1D_BD87_4D27_9CC1_D7285AA61F90__INCLUDED_)
#define AFX_FORMZKLISTQUERY_H__5FE93A1D_BD87_4D27_9CC1_D7285AA61F90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FormRkListQuery.h"

class CFormZkListQuery : public CFormRkListQuery  
{
public:
	BOOL OnInitDialog();
	void OnOK();
	CFormZkListQuery();
	virtual ~CFormZkListQuery();

};

#endif // !defined(AFX_FORMZKLISTQUERY_H__5FE93A1D_BD87_4D27_9CC1_D7285AA61F90__INCLUDED_)
