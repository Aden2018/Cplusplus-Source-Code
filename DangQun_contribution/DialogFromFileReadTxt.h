//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_DIALOGFROMFILEREADTXT_H__A7D694A4_9707_44A9_952E_A9C83A09418B__INCLUDED_)
#define AFX_DIALOGFROMFILEREADTXT_H__A7D694A4_9707_44A9_952E_A9C83A09418B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogFromFileReadTxt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogFromFileReadTxt dialog

class CDialogFromFileReadTxt : public CDialog
{
// Construction
public:
	static UINT readFromTxt(LPVOID ps);
	CDialogFromFileReadTxt(CWnd* pParent = NULL);   // standard constructor
   char szPath[MAX_PATH];     //存放选择的目录路径
   enum { GRID_ID=7 };
// Dialog Data
	//{{AFX_DATA(CDialogFromFileReadTxt)
	enum { IDD = IDD_DIALOG_IMPORT_DATA };
	CListBox	m_list_logfile;
	CListBox	m_listLog;
	CMSHFlexGrid	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogFromFileReadTxt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogFromFileReadTxt)
	afx_msg void OnButtonImportData();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnExcel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGFROMFILEREADTXT_H__A7D694A4_9707_44A9_952E_A9C83A09418B__INCLUDED_)
