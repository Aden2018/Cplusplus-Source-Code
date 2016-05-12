#if !defined(AFX_BUTTONEX_H__CDC5D613_DFB5_494E_BAA7_1BC6F4550315__INCLUDED_)
#define AFX_BUTTONEX_H__CDC5D613_DFB5_494E_BAA7_1BC6F4550315__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButtonEx window

class CButtonEx : public CButton
{
// Construction
public:
	CButtonEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	CPen pen2;
	virtual ~CButtonEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CButtonEx)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONEX_H__CDC5D613_DFB5_494E_BAA7_1BC6F4550315__INCLUDED_)
