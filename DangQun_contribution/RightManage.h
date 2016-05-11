#pragma once


// CRightManage 对话框
#include <vector>
class CRightManage : public CDialogEx
{
	DECLARE_DYNAMIC(CRightManage)

public:
	CRightManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRightManage();
	CGridCtrl m_grid;
	vector<int> vtAlign;
	CString strUserID,strName;
	CFont ft,font;
// 对话框数据
	enum { IDD = IDD_DIALOG_RIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* pResult);
protected:
//	afx_msg LRESULT OnNmDblclk(WPARAM wParam, LPARAM lParam);
};
