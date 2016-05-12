// EmployeeDecharge.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "EmployeeDecharge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmployeeDecharge dialog


CEmployeeDecharge::CEmployeeDecharge(CWnd* pParent /*=NULL*/)
	: CDialog(CEmployeeDecharge::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmployeeDecharge)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEmployeeDecharge::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmployeeDecharge)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmployeeDecharge, CDialog)
	//{{AFX_MSG_MAP(CEmployeeDecharge)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmployeeDecharge message handlers

void CEmployeeDecharge::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
/*	
	CPen *pold=dc.SelectObject(&penRect);
	dc.SetTextColor(RGB(255,255,255));
	RECT r1;
	int i=0;
	while(i<32){
		GetDlgItem(ps[i])->GetWindowRect(&r1);
		ScreenToClient(&r1);
		r1.left--;
		r1.right++;
		r1.bottom++;

		if(i==25){
			dc.SelectObject(&pen2);
			dc.MoveTo(r1.left,r1.bottom);
			dc.LineTo(r1.right,r1.bottom);
			dc.SelectObject(&penRect);
		}
		else{
			dc.MoveTo(r1.left,r1.bottom);
			dc.LineTo(r1.right,r1.bottom);
		}
		i++;
		
	}

	
	
	dc.SelectObject(pold); */
}
