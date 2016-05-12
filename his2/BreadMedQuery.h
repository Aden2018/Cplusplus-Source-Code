// BreadMedQuery.h: interface for the CBreadMedQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BREADMEDQUERY_H__03AED852_7A73_43B4_932D_731CA836885F__INCLUDED_)
#define AFX_BREADMEDQUERY_H__03AED852_7A73_43B4_932D_731CA836885F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FormRkListQuery.h"

class CBreadMedQuery : public CFormRkListQuery  
{
public:
	BOOL OnInitDialog();
	void OnOK();
	CBreadMedQuery();
	virtual ~CBreadMedQuery();

};

#endif // !defined(AFX_BREADMEDQUERY_H__03AED852_7A73_43B4_932D_731CA836885F__INCLUDED_)
