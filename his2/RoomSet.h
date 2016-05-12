// RoomSet.h: interface for the CRoomSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROOMSET_H__0BCFC50C_F624_4B34_BFD7_15B8EA7E0360__INCLUDED_)
#define AFX_ROOMSET_H__0BCFC50C_F624_4B34_BFD7_15B8EA7E0360__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ResideLocalSet.h"

class CRoomSet : public CResideLocalSet  
{
public:
	void OnMenuResideLocalDel();
	CRoomSet();
	virtual ~CRoomSet();

protected:
	BOOL OnInitDialog();
	void OnMenuResideLocalModify();
	void OnMenuResideLocalRefresh();
	void OnMenuResideLocalAdd();
private:
	void SetGridHead();
protected:
	CStringArray arrayLocal;
};

#endif // !defined(AFX_ROOMSET_H__0BCFC50C_F624_4B34_BFD7_15B8EA7E0360__INCLUDED_)
