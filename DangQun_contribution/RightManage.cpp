// RightManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "his3.h"
#include "RightManage.h"
#include "afxdialogex.h"
#include <sstream>
#include "ComFunc.h"

// CRightManage �Ի���

IMPLEMENT_DYNAMIC(CRightManage, CDialogEx)

CRightManage::CRightManage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRightManage::IDD, pParent)
{
		ft.CreatePointFont(220,"Ҧ��");
		font.CreatePointFont(120,"΢���ź�");
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


// CRightManage ��Ϣ�������


BOOL CRightManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_USER)->SetFont(&ft);
	CString strFmt;
	strFmt.Format("�˻�: %s",strName);
	GetDlgItem(IDC_STATIC_USER)->SetWindowText(strFmt);

	CComFunc::SetGridHeader(m_grid,3/* ���ͷ��ID*/,vtAlign); 
	m_grid.SetFont(&font);
	m_grid.SetEditable(false);

	vector<string> vtsz;
	vtsz.push_back(MYSQL_PRC_RPT); //�洢������
	vtsz.push_back("1");			//��ѯ
	vtsz.push_back("B");			//���ؽ����
	
	vtsz.push_back((LPCSTR)strUserID);

	_RecordsetPtr rec;

	CComFunc::callSqlPro(vtsz,rec);
	CComFunc::ReadDataForGrid(m_grid,rec,vector<int>(),vector<double>(),vtAlign);	




	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CRightManage::OnBnClickedOk()
{

}

void CRightManage::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
  //  Trace(_T("Double Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	CString strStatus=m_grid.GetItemText(pItem->iRow,3);
	if( strStatus.Compare("��ֹ") )strStatus.Format("��ֹ");
	else	strStatus.Format("����");
	m_grid.SetItemText(pItem->iRow,3,strStatus);
	m_grid.Refresh();
	//д�����ݿ�
	vector<string> vtSz;
	vtSz.push_back( MYSQL_PRC_RPT); //�洢������
	vtSz.push_back("1");			//��ѯ
	vtSz.push_back("C");			//Ȩ��д�����ݿ�
	vtSz.push_back((LPCSTR)strUserID); //�û�ID
	vtSz.push_back	((LPCSTR)m_grid.GetItemText(pItem->iRow,0) ); //Ȩ��ID
	vtSz.push_back((LPCSTR)strStatus); //״̬
	string szRet;

	CComFunc::callSqlPro(vtSz,szRet);
	
	if( ! szRet.compare(SZERROR) )
		 AfxMessageBox("���ô洢����ʧ��");
		 
}