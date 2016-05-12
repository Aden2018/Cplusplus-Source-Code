// TreateQuery.h: interface for the CTreateQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREATEQUERY_H__ED1AFC58_5102_4762_88DA_16B4EDDEC962__INCLUDED_)
#define AFX_TREATEQUERY_H__ED1AFC58_5102_4762_88DA_16B4EDDEC962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DialogGhQuery.h"

class CTreateQuery : public CDialogGhQuery  
{
public:
	BOOL OnInitDialog();
	static UINT TreateQuery(LPVOID ps);
	void OnOK();
	CTreateQuery();
	virtual ~CTreateQuery();

};

#endif // !defined(AFX_TREATEQUERY_H__ED1AFC58_5102_4762_88DA_16B4EDDEC962__INCLUDED_)
