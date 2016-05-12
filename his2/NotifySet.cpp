// NotifySet.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "NotifySet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotifySet dialog


CNotifySet::CNotifySet(CWnd* pParent /*=NULL*/)
	: CDialog(CNotifySet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNotifySet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNotifySet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNotifySet)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNotifySet, CDialog)
	//{{AFX_MSG_MAP(CNotifySet)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotifySet message handlers
