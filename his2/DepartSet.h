// DepartSet.h: interface for the CDepartSet class.
// 类描述:
//		厂部门新增修改
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEPARTSET_H__9656FA4B_E147_4719_9003_68212F4551B7__INCLUDED_)
#define AFX_DEPARTSET_H__9656FA4B_E147_4719_9003_68212F4551B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseChargeSet.h"

class CDepartSet : public CBaseChargeSet  
{
public:
	void OnAdd();
	void OnClickMshflexgrid1();
	void OnDblClickMshflexgrid1();
	void OnOK();
	BOOL OnInitDialog();
	CDepartSet();
	virtual ~CDepartSet();

};

#endif // !defined(AFX_DEPARTSET_H__9656FA4B_E147_4719_9003_68212F4551B7__INCLUDED_)
