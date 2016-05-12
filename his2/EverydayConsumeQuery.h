// EverydayConsumeQuery.h: interface for the CEverydayConsumeQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVERYDAYCONSUMEQUERY_H__DFE42551_6F68_4943_9EA7_414155367965__INCLUDED_)
#define AFX_EVERYDAYCONSUMEQUERY_H__DFE42551_6F68_4943_9EA7_414155367965__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FormZkListQuery.h"

class CEverydayConsumeQuery : public CFormZkListQuery  
{
public:
	static UINT  QueryConsume(LPVOID pd);
	void OnOK();
	BOOL OnInitDialog();
	CEverydayConsumeQuery();
	virtual ~CEverydayConsumeQuery();

};

#endif // !defined(AFX_EVERYDAYCONSUMEQUERY_H__DFE42551_6F68_4943_9EA7_414155367965__INCLUDED_)
