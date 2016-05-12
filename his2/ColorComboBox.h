#if !defined(AFX_COLORCOMBOBOX_H__C45DFB3B_6CF7_43D1_A0BD_62411D0B934B__INCLUDED_)
#define AFX_COLORCOMBOBOX_H__C45DFB3B_6CF7_43D1_A0BD_62411D0B934B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorComboBox window

class CColorComboBox : public CComboBox
{
// Construction
public:
	CColorComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORCOMBOBOX_H__C45DFB3B_6CF7_43D1_A0BD_62411D0B934B__INCLUDED_)
