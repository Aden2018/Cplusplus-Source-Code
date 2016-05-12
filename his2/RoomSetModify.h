// RoomSetModify.h: interface for the CRoomSetModify class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROOMSETMODIFY_H__601FC371_51D4_4CC6_B096_C3E141BBC966__INCLUDED_)
#define AFX_ROOMSETMODIFY_H__601FC371_51D4_4CC6_B096_C3E141BBC966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "roomSetAdd.h"

class CRoomSetModify : public CRoomSetAdd  
{
public:
	CString strLocalName;
	CString strCode;
	CString strLocal;
	CRoomSetModify();
	virtual ~CRoomSetModify();

protected:
	void OnOK();
	BOOL OnInitDialog();
};

#endif // !defined(AFX_ROOMSETMODIFY_H__601FC371_51D4_4CC6_B096_C3E141BBC966__INCLUDED_)
