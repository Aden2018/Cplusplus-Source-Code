// his2View.h : interface of the CHis2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HIS2VIEW_H__6CAE23C2_8DD6_48B1_91FA_F9B0E25E285B__INCLUDED_)
#define AFX_HIS2VIEW_H__6CAE23C2_8DD6_48B1_91FA_F9B0E25E285B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHis2View : public CFormView
{
protected: // create from serialization only
	CHis2View();
	DECLARE_DYNCREATE(CHis2View)

public:
	//{{AFX_DATA(CHis2View)
	enum{ IDD = IDD_HIS2_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CHis2Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHis2View)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHis2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHis2View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in his2View.cpp
inline CHis2Doc* CHis2View::GetDocument()
   { return (CHis2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIS2VIEW_H__6CAE23C2_8DD6_48B1_91FA_F9B0E25E285B__INCLUDED_)
