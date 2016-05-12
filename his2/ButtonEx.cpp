// ButtonEx.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "ButtonEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonEx

CButtonEx::CButtonEx()
{
	pen2.CreatePen(PS_SOLID,1,RGB(255,0,0));
}

CButtonEx::~CButtonEx()
{
}


BEGIN_MESSAGE_MAP(CButtonEx, CButton)
	//{{AFX_MSG_MAP(CButtonEx)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonEx message handlers

void CButtonEx::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	dc.SelectObject(&pen2);
	CRect r1;
	GetWindowRect(&r1);
	ScreenToClient(&r1);
	dc.Rectangle(&r1);
	//dc.Ellipse(&r1);
	r1.left=r1.right-18;
	dc.Rectangle(&r1);

		
	// TODO: Add your message handler code here
	
	// Do not call CButton::OnPaint() for painting messages
}
