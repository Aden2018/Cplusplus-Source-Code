// Pandian.h: interface for the CPandian class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PANDIAN_H__A358A092_2836_4016_8032_BF4DDD09939C__INCLUDED_)
#define AFX_PANDIAN_H__A358A092_2836_4016_8032_BF4DDD09939C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MoveKf.h"

class CPandian : public CMoveKf  
{
public:
	void OnOK();
	void OnSearch();
	BOOL OnInitDialog();
	CPandian();
	virtual ~CPandian();

};

#endif // !defined(AFX_PANDIAN_H__A358A092_2836_4016_8032_BF4DDD09939C__INCLUDED_)
