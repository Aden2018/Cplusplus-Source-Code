// RelateModify.h: interface for the CRelateModify class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RELATEMODIFY_H__DF44A984_95AB_4587_A900_13B41DDB616F__INCLUDED_)
#define AFX_RELATEMODIFY_H__DF44A984_95AB_4587_A900_13B41DDB616F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RelateAdd.h"

class CRelateModify : public CRelateAdd  
{
public:
	CRelateModify();
	virtual ~CRelateModify();
	void OnButton1(){};
	void OnOK();
	void OnSelchangeComboType(){};
	void OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult){};
	BOOL OnInitDialog();
public:
	CString strPass[20];
};

#endif // !defined(AFX_RELATEMODIFY_H__DF44A984_95AB_4587_A900_13B41DDB616F__INCLUDED_)
