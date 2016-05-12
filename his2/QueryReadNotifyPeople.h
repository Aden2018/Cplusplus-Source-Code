// QueryReadNotifyPeople.h: interface for the CQueryReadNotifyPeople class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUERYREADNOTIFYPEOPLE_H__DA484631_FC8C_4B58_9A31_61FEE101F2E2__INCLUDED_)
#define AFX_QUERYREADNOTIFYPEOPLE_H__DA484631_FC8C_4B58_9A31_61FEE101F2E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DMessageRead.h"

class CQueryReadNotifyPeople : public CDMessageRead  //查阅已发通知阅读情况
{
public:
	BOOL PreTranslateMessage(MSG* pMsg);
	void OnClickListMessage(NMHDR* pNMHDR, LRESULT* pResult);
	void ListMessage();
	CQueryReadNotifyPeople();
	virtual ~CQueryReadNotifyPeople();

};

#endif // !defined(AFX_QUERYREADNOTIFYPEOPLE_H__DA484631_FC8C_4B58_9A31_61FEE101F2E2__INCLUDED_)
