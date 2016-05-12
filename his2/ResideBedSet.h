// ResideBedSet.h: interface for the CResideBedSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESIDEBEDSET_H__90F57EA8_8247_4691_85E7_4FA24CA078D9__INCLUDED_)
#define AFX_RESIDEBEDSET_H__90F57EA8_8247_4691_85E7_4FA24CA078D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ResideLocalSet.h"
//* 床位设计
class CResideBedSet : public CResideLocalSet  
{
public:
	int DIALOG_FLAG;
	CResideBedSet();
	virtual ~CResideBedSet();
	CString strBedCode,strBedName;
	CStringArray arrayLocal;
	enum{
		LOCALCODE_POS=0,LOCALNAME_POS,ROOMCODE_POS,ROOMNAME_POS,BEDCODE_POS,BEDNAME_POS,\
			DIALOG_BED=10,DIALOG_SELECT }; //代表列所在的位置


protected:
	void OnDblClickMshflexgrid1();
	void OnMenuResideLocalRefresh();
	void OnMenuResideLocalModify();
	void OnMenuResideLocalDel();
	void OnMenuResideLocalAdd();
	BOOL OnInitDialog();
private:
	void SetGridHead();
};

#endif // !defined(AFX_RESIDEBEDSET_H__90F57EA8_8247_4691_85E7_4FA24CA078D9__INCLUDED_)
