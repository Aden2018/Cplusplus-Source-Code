// HosModify.cpp: implementation of the CHosModify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "HosModify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHosModify::CHosModify()
{
	strTag.Format("AAD");
	CString strSql;
	strSql.Format("SELECT ds2 FROM LSQ_GH_TYPE WHERE ds1='%s' ",strTag );
	strTitle=GetStringTitle(strSql);
}

CHosModify::~CHosModify()
{

}
