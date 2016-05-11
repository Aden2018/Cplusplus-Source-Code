// RightManage.cpp : 实现文件
//

#include "stdafx.h"
#include "his3.h"
#include "RightManage.h"
#include "afxdialogex.h"
#include <sstream>
#include "ComFunc.h"

// CRightManage 对话框

IMPLEMENT_DYNAMIC(CRightManage, CDialogEx)

CRightManage::CRightManage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRightManage::IDD, pParent)
{
		ft.CreatePointFont(220,"姚体");
		font.CreatePointFont(120,"微软雅黑");
}

CRightManage::~CRightManage()
{
}

void CRightManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_GridControl(pDX, IDC_GRID, m_grid);

}


BEGIN_MESSAGE_MAP(CRightManage, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRightManage::OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_GRID, OnGridDblClick)
END_MESSAGE_MAP()


// CRightManage 消息处理程序


BOOL CRightManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_USER)->SetFont(&ft);
	CString strFmt;
	strFmt.Format("账户: %s",strName);
	GetDlgItem(IDC_STATIC_USER)->SetWindowText(strFmt);

	CComFunc::SetGridHeader(m_grid,3/* 表格头部ID*/,vtAlign); 
	m_grid.SetFont(&font);
	m_grid.SetEditable(false);

	vector<string> vtsz;
	vtsz.push_back(MYSQL_PRC_RPT); //存储过程名
	vtsz.push_back("1");			//查询
	vtsz.push_back("B");			//返回结果集
	
	vtsz.push_back((LPCSTR)strUserID);

	_RecordsetPtr rec;

	CComFunc::callSqlPro(vtsz,rec);
	CComFunc::ReadDataForGrid(m_grid,rec,vector<int>(),vector<double>(),vtAlign);	




	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CRightManage::OnBnClickedOk()
{

}

void CRightManage::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
  //  Trace(_T("Double Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	CString strStatus=m_grid.GetItemText(pItem->iRow,3);
	if( strStatus.Compare("禁止") )strStatus.Format("禁止");
	else	strStatus.Format("允许");
	m_grid.SetItemText(pItem->iRow,3,strStatus);
	m_grid.Refresh();
	//写入数据库
	vector<string> vtSz;
	vtSz.push_back( MYSQL_PRC_RPT); //存储过程名
	vtSz.push_back("1");			//查询
	vtSz.push_back("C");			//权限写入数据库
	vtSz.push_back((LPCSTR)strUserID); //用户ID
	vtSz.push_back	((LPCSTR)m_grid.GetItemText(pItem->iRow,0) ); //权限ID
	vtSz.push_back((LPCSTR)strStatus); //状态
	string szRet;

	CComFunc::callSqlPro(vtSz,szRet);
	
	if( ! szRet.compare(SZERROR) )
		 AfxMessageBox("调用存储功能失败");
		 
}