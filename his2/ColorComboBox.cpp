// ColorComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "ColorComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorComboBox

CColorComboBox::CColorComboBox()
{
}

CColorComboBox::~CColorComboBox()
{
}


BEGIN_MESSAGE_MAP(CColorComboBox, CComboBox)
	//{{AFX_MSG_MAP(CColorComboBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorComboBox message handlers

void CColorComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	CRect rect(&(lpDrawItemStruct->rcItem));
	

	CBrush brush(RGB(255,0,0)),bru2(RGB(255,255,255));

	CString str1;
	this->GetLBText(lpDrawItemStruct->itemID,str1);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0, 0, 0)); //RGB(0,0,0) color is black 
	
	if(lpDrawItemStruct->itemID==0){
		dc.FillRect(rect, &bru2);
		
	}
	else{
		
		dc.FillRect(rect,&brush);
	
	}
	dc.DrawText(str1, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	
	// Draw the focus rect if the mouse is either over the item, or if the item
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		
		this->GetLBText(lpDrawItemStruct->itemID,str1);
	//	CSize textSize = dc.GetOutputTextExtent(str1);
		dc.DrawText(str1, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		rect.InflateRect(-2,-2);

		dc.DrawFocusRect(rect);
	}

//	dc.FrameRect(&lpDrawItemStruct->rcItem,&brush);
	
	dc.Detach();
	
}
