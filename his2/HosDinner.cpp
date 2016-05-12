// HosDinner.cpp: implementation of the CHosDinner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "HosDinner.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHosDinner::CHosDinner()
{
	strTag.Format("AAJ");
	CString strSql;
	strSql.Format("SELECT ds2 FROM LSQ_GH_TYPE WHERE ds1='%s' ",strTag );
	strTitle=GetStringTitle(strSql);
}

CHosDinner::~CHosDinner()
{

}
