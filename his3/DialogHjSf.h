//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#include "RegisterGH.h"
#include "dialogWait.h"
#if !defined(AFX_DIALOGHJSF_H__C626CFDD_4701_4788_B10A_0023FD3A6752__INCLUDED_)
#define AFX_DIALOGHJSF_H__C626CFDD_4701_4788_B10A_0023FD3A6752__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogHjSf.h : header file
//* ҩƷ����\�շ�\����

/////////////////////////////////////////////////////////////////////////////
// CDialogHjSf dialog

class CDialogHjSf : public CDialog
{
// Construction
public:
	CDialogWait *pw;
	CString strBM; //����
	double dbZF;//�ʻ�
	static CString GetChinesePrice(double dMoney);
	CString strGHTYPE; //�ڲ��Һ�����
	void OnKillfocusMoveEdit();
	CDialogHjSf(CWnd* pParent = NULL);   // standard constructor
	CRegisterGh * pGH;
	CEdit editCtrl;
	CFont fontMoveEdit,fontZY;
	CString strDoctorCode;//ҽ������
	CString strDANJUHAO; //���ݺ�
	int selRow,selModify,flagEdit;
	CStringArray arySort01;
	double dbRatio;
	enum { MED_GRID=1,OTHER_GRID=2,ACCOUNT_GRID=3 }; // ��־�༭��һ�����

	enum { COL_ID=0,COL_MC=1,COL_GG=2 ,COL_DW=3,COL_JINJIA=4,
		COL_FACTORY=5,COL_KC=6,COL_PRICE=7,COL_SL= 8,COL_MONEY=9,NOSEL=-1,COL_ZY=11,COL_ZY_COST=4 }; //ҩƷ�������

	enum { EXES_ID=0,EXES_MC_COL=1,EXES_MONEY=2 }; //�����շ���Ŀ����

	enum { ACCOUNT_ID=0, ACCOUNT_YE=3,ACCOUNT_ZFJE=4 ,ACCOUNT_TYPE=5 ,ACCOUNT_MC=2 }; //�ʻ����
	enum { IDC_EDIT_CTRL_MOVE=WM_USER+1000 }; // �Զ���༭�ؼ�
// Dialog Data
	//{{AFX_DATA(CDialogHjSf)
	enum { IDD = IDD_DIALOG_HJ };
	CEdit	m_ZY_PRICE;
	CEdit	m_yuer;
	CEdit	m_Ratio;
	CEdit	m_workunit;
	CEdit	m_tc;
	CEdit	m_jgc;
	CEdit	m_ic;
	CEdit	m_gwy;
	CEdit	m_dbjz;
	CEdit	m_cost;
	CEdit	m_cash;
	CEdit	m_account;
	CEdit	m_age;
	CEdit	m_ys;
	CEdit	m_type;
	CEdit	m_sex;
	CEdit	m_py;
	CEdit	m_num;
	CEdit	m_name;
	CMSHFlexGrid	m_grid1;
	CMSHFlexGrid	m_grid2;
	CMSHFlexGrid	m_grid3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogHjSf)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EnableControl(bool f);

	// Generated message map functions
	//{{AFX_MSG(CDialogHjSf)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickMshflexgrid1();
	afx_msg void OnMenuitemHjAllDel();
	afx_msg void OnMenuitemHjSelDel();
	afx_msg void OnChangeEditPy();
	afx_msg void OnKillfocusEditNum();
	afx_msg void OnDblClickMshflexgrid2();
	afx_msg void OnClickMshflexgrid2();
	afx_msg void OnMenuitemG2aDel();
	afx_msg void OnMenuitemG2sDel();
	afx_msg void OnDblClickMshflexgrid3();
	afx_msg void OnMenuitemMedModify();
	afx_msg void OnMenuitemOtherModify();
	afx_msg void OnClickMshflexgrid3();
	afx_msg void OnMenuitemAccountAdel();
	afx_msg void OnMenuitemAccountModify();
	afx_msg void OnMenuitemAccountSdel();
	afx_msg void OnChangeEditDbjz();
	virtual void OnOK();
	afx_msg void OnButtonPrint();
	virtual void OnCancel();
	afx_msg void OnChangeEditRealSs();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void SetGridHeader();
private:
	void computeBalance();
	void QueryDoctor();
	void ShowEdit(CMSHFlexGrid & grid,int operCol );
	void GetMedNum();
	void ComputeMoney();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGHJSF_H__C626CFDD_4701_4788_B10A_0023FD3A6752__INCLUDED_)
