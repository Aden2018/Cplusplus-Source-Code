// MedCodeBase.cpp: implementation of the CMedCodeBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "MedCodeBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMedCodeBase::CMedCodeBase()
{

}

CMedCodeBase::~CMedCodeBase()
{

}

void CMedCodeBase::OnDblClickMshflexgrid1()
{

}



BOOL CMedCodeBase::OnInitDialog()
{
	CMedCodeQuery::OnInitDialog();
	return true;
}
