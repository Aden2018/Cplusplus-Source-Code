// QueryForCommonUseQuery.h: interface for the CQueryForCommonUseQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUERYFORCOMMONUSEQUERY_H__E13E2C67_247B_48DF_B8D0_00CA36896B70__INCLUDED_)
#define AFX_QUERYFORCOMMONUSEQUERY_H__E13E2C67_247B_48DF_B8D0_00CA36896B70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FormRkListQuery.h"

class CQueryForCommonUseQuery : public CFormRkListQuery  
{
public:
	BOOL OnInitDialog();
	void OnOK();
	CQueryForCommonUseQuery();
	virtual ~CQueryForCommonUseQuery();

};

#endif // !defined(AFX_QUERYFORCOMMONUSEQUERY_H__E13E2C67_247B_48DF_B8D0_00CA36896B70__INCLUDED_)
