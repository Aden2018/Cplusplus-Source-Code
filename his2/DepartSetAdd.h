// DepartSetAdd.h: interface for the CDepartSetAdd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEPARTSETADD_H__E3D992D8_D6E8_4DFF_8136_1C01BD6E12F6__INCLUDED_)
#define AFX_DEPARTSETADD_H__E3D992D8_D6E8_4DFF_8136_1C01BD6E12F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseProjectSet.h"

class CDepartSetAdd : public CBaseProjectSet  
{
public:
	void OnCancel();
	void OnOK();
	BOOL OnInitDialog();
	CDepartSetAdd();
	virtual ~CDepartSetAdd();

};

#endif // !defined(AFX_DEPARTSETADD_H__E3D992D8_D6E8_4DFF_8136_1C01BD6E12F6__INCLUDED_)
