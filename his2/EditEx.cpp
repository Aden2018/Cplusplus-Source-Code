// EditEx.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "EditEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditEx

CEditEx::CEditEx()
{

}

CEditEx::~CEditEx()
{
}


BEGIN_MESSAGE_MAP(CEditEx, CEdit)
	//{{AFX_MSG_MAP(CEditEx)
	ON_WM_CHAR()
//	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditEx message handlers


void CEditEx::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar=='\''||nChar=='\"'||nChar=='['||nChar==']')return;
	
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}




//DEL void CEditEx::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	CDC *pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
//DEL 	pDC->SetTextColor(RGB(255,0,0));
//DEL 	CEdit::OnDrawItem(nIDCtl, lpDrawItemStruct);
//DEL }

//DEL HBRUSH CEditEx::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
//DEL {
//DEL 	HBRUSH hbr = CEdit::OnCtlColor(pDC, pWnd, nCtlColor);
//DEL 	pDC->SetTextColor(RGB(255,0,0));
//DEL 	// TODO: Change any attributes of the DC here
//DEL 	
//DEL 	// TODO: Return a different brush if the default is not desired
//DEL 	return hbr;
//DEL }

//DEL HBRUSH CEditEx::CtlColor(CDC* pDC, UINT nCtlColor) 
//DEL {
//DEL 	// TODO: Change any attributes of the DC here
//DEL 	
//DEL 	// TODO: Return a non-NULL brush if the parent's handler should not be called
//DEL 	return NULL;
//DEL }
