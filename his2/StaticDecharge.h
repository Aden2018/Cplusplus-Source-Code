#if !defined(AFX_STATICDECHARGE_H__1818C97E_5F08_4398_81F6_62B4FB7B4158__INCLUDED_)
#define AFX_STATICDECHARGE_H__1818C97E_5F08_4398_81F6_62B4FB7B4158__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticDecharge.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticDecharge window

class CStaticDecharge : public CStatic
{
// Construction
public:
	CStaticDecharge();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticDecharge)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticDecharge();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticDecharge)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICDECHARGE_H__1818C97E_5F08_4398_81F6_62B4FB7B4158__INCLUDED_)
