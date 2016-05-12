// his2Doc.cpp : implementation of the CHis2Doc class
//

#include "stdafx.h"
#include "his2.h"

#include "his2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHis2Doc

IMPLEMENT_DYNCREATE(CHis2Doc, CDocument)

BEGIN_MESSAGE_MAP(CHis2Doc, CDocument)
	//{{AFX_MSG_MAP(CHis2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHis2Doc construction/destruction

CHis2Doc::CHis2Doc()
{
	// TODO: add one-time construction code here

}

CHis2Doc::~CHis2Doc()
{
}

BOOL CHis2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHis2Doc serialization

void CHis2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHis2Doc diagnostics

#ifdef _DEBUG
void CHis2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHis2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHis2Doc commands
