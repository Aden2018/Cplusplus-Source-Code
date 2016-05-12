#if !defined(AFX_ROOMSETADD_H__CE47B515_DC17_482A_AD72_1C2D39803C6B__INCLUDED_)
#define AFX_ROOMSETADD_H__CE47B515_DC17_482A_AD72_1C2D39803C6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RoomSetAdd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRoomSetAdd dialog

class CRoomSetAdd : public CDialog
{
// Construction
public:
	CString strTitle;
	CRoomSetAdd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRoomSetAdd)
	enum { IDD = IDD_DIALOG_RESIDE_ROOM_ADD };
	CQiuXpButton	m_2;
	CQiuXpButton	m_1;
	CComboBox	m_combox;
	CString	m_name;
	CString	m_remark;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoomSetAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRoomSetAdd)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CStringArray localArray;
	CString strSql;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOMSETADD_H__CE47B515_DC17_482A_AD72_1C2D39803C6B__INCLUDED_)
