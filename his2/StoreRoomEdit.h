// StoreRoomEdit.h: interface for the CStoreRoomEdit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STOREROOMEDIT_H__C9F79850_C298_4201_AECD_9B2E0BD5E175__INCLUDED_)
#define AFX_STOREROOMEDIT_H__C9F79850_C298_4201_AECD_9B2E0BD5E175__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DialogMedDL.h"

class CStoreRoomEdit : public CDialogMedDL  
{
public:
	BOOL OnInitDialog();
	void OnDelete();
	void OnModify();
	void OnAdd();
	BOOL ReadName();
	CStoreRoomEdit();
	virtual ~CStoreRoomEdit();

};

#endif // !defined(AFX_STOREROOMEDIT_H__C9F79850_C298_4201_AECD_9B2E0BD5E175__INCLUDED_)
