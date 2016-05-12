// LocalSetModify.h: interface for the CLocalSetModify class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCALSETMODIFY_H__A455DE74_B136_4900_816C_8521CD4ACDE4__INCLUDED_)
#define AFX_LOCALSETMODIFY_H__A455DE74_B136_4900_816C_8521CD4ACDE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LocalSetAdd.h"

class CLocalSetModify : public CLocalSetAdd  
{
public:
	CString strBM;
	CLocalSetModify();
	virtual ~CLocalSetModify();

protected:
	virtual void OnOK();
	virtual BOOL OnInitDialog();
};

#endif // !defined(AFX_LOCALSETMODIFY_H__A455DE74_B136_4900_816C_8521CD4ACDE4__INCLUDED_)
