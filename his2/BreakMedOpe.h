// BreakMedOpe.h: interface for the CBreakMedOpe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BREAKMEDOPE_H__AD9D674D_03ED_4B91_A203_4BBD1CD8EE7B__INCLUDED_)
#define AFX_BREAKMEDOPE_H__AD9D674D_03ED_4B91_A203_4BBD1CD8EE7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MoveKf.h"

class CBreakMedOpe : public CMoveKf  
{
public:
	void OnEffiect();
	void OnSearch();
	void OnKillfocusEditGetRymc();
	void OnSetfocusEditGetRymc();
	void OnOK();
	BOOL OnInitDialog();
	CBreakMedOpe();
	virtual ~CBreakMedOpe();

};

#endif // !defined(AFX_BREAKMEDOPE_H__AD9D674D_03ED_4B91_A203_4BBD1CD8EE7B__INCLUDED_)
