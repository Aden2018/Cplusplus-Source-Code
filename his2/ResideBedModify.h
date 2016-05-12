// ResideBedModify.h: interface for the CResideBedModify class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESIDEBEDMODIFY_H__030A147A_8F08_4922_B7B5_6DDA1BA4AABB__INCLUDED_)
#define AFX_RESIDEBEDMODIFY_H__030A147A_8F08_4922_B7B5_6DDA1BA4AABB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ResideBedSetAdd.h"

class CResideBedModify : public CResideBedSetAdd  
{
public:
	CString strRoom;
	CString strLocal;
	BOOL OnInitDialog();
	CString m_strBedCode;
	void OnOK();
	CResideBedModify();
	virtual ~CResideBedModify();

};

#endif // !defined(AFX_RESIDEBEDMODIFY_H__030A147A_8F08_4922_B7B5_6DDA1BA4AABB__INCLUDED_)
