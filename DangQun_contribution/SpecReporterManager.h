#pragma once


// CSpecReporterManager �Ի���
#include "GridCtrl.h"
#include <vector>
#include "QiuXpButton.h"
#include <string>
using namespace std;
class CSpecReporterManager : public CDialogEx
{
	DECLARE_DYNAMIC(CSpecReporterManager)

public:
	CSpecReporterManager(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSpecReporterManager();
 
	CGridCtrl m_grid;
	vector<int> vtAlign;
	vector<int> vtFactory;
	int iStatus; //��Ա״̬,�Ƿ������ͨѶ¼��
// �Ի�������
	enum { IDD = IDD_DIALOG_SPECREPORT_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CComboBox m_cbFactory;
	CComboBox m_cbYear;
	CString m_szName;
	afx_msg void OnBnClickedAdd();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnKillfocusEditName();
	CQiuXpButton m_1;
	CQiuXpButton m_btnOK;
	CQiuXpButton m_btnCancel3;

	string szProName;
	string szError;
};
