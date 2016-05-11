// GhQuery_del.cpp: implementation of the CGhQuery_del class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "GhQuery_del.h"
#include "progressIndicate.h"
#include "formghlist_del.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGhQuery_del::CGhQuery_del()
{

}

CGhQuery_del::~CGhQuery_del()
{

}



void CGhQuery_del::OnOK()
{
	CProgressIndicate pq;
	pq.pDialog= this;

	pq.pThreadFunction = Query;
	pq.DoModal();

	CDialog::OnOK();

}

UINT CGhQuery_del::Query(LPVOID ps)
{
	return true;

}
