// his2Doc.h : interface of the CHis2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HIS2DOC_H__9A2FDFCD_E9C5_4C0F_8AF6_667FA5A33C80__INCLUDED_)
#define AFX_HIS2DOC_H__9A2FDFCD_E9C5_4C0F_8AF6_667FA5A33C80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHis2Doc : public CDocument
{
protected: // create from serialization only
	CHis2Doc();
	DECLARE_DYNCREATE(CHis2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHis2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHis2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHis2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIS2DOC_H__9A2FDFCD_E9C5_4C0F_8AF6_667FA5A33C80__INCLUDED_)
