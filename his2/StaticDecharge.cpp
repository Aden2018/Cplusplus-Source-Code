// StaticDecharge.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "StaticDecharge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticDecharge

CStaticDecharge::CStaticDecharge()
{
}

CStaticDecharge::~CStaticDecharge()
{
}


BEGIN_MESSAGE_MAP(CStaticDecharge, CStatic)
	//{{AFX_MSG_MAP(CStaticDecharge)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticDecharge message handlers

HBRUSH CStaticDecharge::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CStatic::OnCtlColor(pDC, pWnd, nCtlColor);
	
	pDC->SetTextColor(RGB(50,150,50));	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

