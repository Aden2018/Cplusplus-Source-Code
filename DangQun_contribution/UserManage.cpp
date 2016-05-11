// UserManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "his3.h"
#include "UserManage.h"
#include "afxdialogex.h"
#include "RightManage.h"
#include "ComFunc.h"
#include <string>
#include <vector>
#include "gridcellcombo.h"
// CUserManage �Ի���

IMPLEMENT_DYNAMIC(CUserManage, CDialogEx)

		extern string SZERROR;

CUserManage::CUserManage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserManage::IDD, pParent)
{
		ft.CreatePointFont(220,"Ҧ��");
		font.CreatePointFont(120,"΢���ź�");
		iRow=0;
		iCol=0;
}

CUserManage::~CUserManage()
{
}

void CUserManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_GridControl(pDX, IDC_GRID, m_grid);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDOK_ADD, m_ts);
	DDX_Control(pDX, IDOK_RIGHT_MANAGE, m_btsd);
}


BEGIN_MESSAGE_MAP(CUserManage, CDialogEx)
	ON_BN_CLICKED(IDOK_ADD, &CUserManage::OnBnClickedAdd)
	ON_BN_CLICKED(IDOK, &CUserManage::OnBnClickedOk)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	ON_BN_CLICKED(IDOK_RIGHT_MANAGE, &CUserManage::OnBnClickedRightManage)
	ON_NOTIFY(NM_CLICK,IDC_GRID,OnClick)
	ON_CBN_SELCHANGE(IDC_COMBO_STATUS, OnCbnSelchangeComboStatus)
	ON_CBN_KILLFOCUS(IDC_COMBO_STATUS,OnCbnKillFocus)
END_MESSAGE_MAP()


// CUserManage ��Ϣ�������


BOOL CUserManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowTextA("ϵͳ�û��޹���");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&ft);
	
	cb.Create(WS_CHILD|WS_VSCROLL|CBS_DROPDOWNLIST|WS_TABSTOP,CRect(0,0,0,100),this,IDC_COMBO_STATUS);
	cb.AddString("����");
	cb.AddString("��ֹ");
	cb.SetFont(&font);
	CComFunc::SetGridHeader(m_grid,2/* ���ͷ��ID*/,vtAlign); 
	m_grid.SetFont(&font);
	m_grid.SetEditable();

	OnBnClickedOk();

	

	return TRUE;  
}



//�����û�,��ȡ�µ�ID,Ȼ�����һ�е�����������
void CUserManage::OnBnClickedAdd()
{
	vector<string> vtCols;
	CString strPrc;
	strPrc.LoadString(IDS_PRC_NAME);
	vtCols.push_back( (LPCSTR)strPrc ); //�洢������
	vtCols.push_back("3");				//����������
	vtCols.push_back("1");				//ȡ���ID��,�����뵽�����

	string szRet;

	CComFunc::callSqlPro(vtCols,szRet);
	
	if(  szRet.compare(SZERROR) )
	{
		m_grid.InsertRow("");
		m_grid.SetItemText(m_grid.GetRowCount()-1,0,szRet.c_str());
		m_grid.Refresh();
	}
	else
		AfxMessageBox("���ô洢����ʧ��");
		 
}


void CUserManage::OnBnClickedOk()
{
	
	vector<string> vtSz;
	vtSz.push_back(MYSQL_PRC_RPT); //�洢������
	vtSz.push_back("1");			//��ѯ
	vtSz.push_back("A");			//���ؽ����

	
	_RecordsetPtr rec;

	CComFunc::callSqlPro(vtSz,rec);

	CComFunc::ReadDataForGrid(m_grid,rec,vector<int>(),vector<double>(),vtAlign);	
}



void CUserManage::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{

    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;

	CString szItem=m_grid.GetItemText(pItem->iRow,pItem->iColumn);
	int iCols=m_grid.GetColumnCount();
	if( pItem->iColumn ==2 || pItem->iRow ==0  ) {
		*pResult=0;
		return;
	}
	iRow=pItem->iRow;
	StoreDatabase();

	
	*pResult =0; //0��ʾ�����޸�
}

void CUserManage::OnBnClickedRightManage()
{
	if(! CComFunc::AssertPriv(5) ){
		AfxMessageBox("��û��Щ��Ȩ��,����˹���,����ϵ������Ա");
		return;

	}
	unsigned int iRow=m_grid.GetFocusCell().row; //ȡ���û�ID,���ݴ�ID�����û�Ȩ�ޱ�
	CRightManage rm;
	rm.strUserID=m_grid.GetItemText(iRow,0) ;
	rm.strName=m_grid.GetItemText(iRow,1);
	rm.DoModal();	
}

void CUserManage::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
{

	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CString szItem=m_grid.GetItemText(pItem->iRow,pItem->iColumn);
	CRect rt,rtBase;
	iRow=pItem->iRow;

	if( pItem->iColumn == 2 && pItem->iRow != 0  ){
		//��ȡ��Ԫ����Ա��ؼ�����
		m_grid.GetCellRect(pItem->iRow,2,&rtBase);

		//��ȡ�����Ļ����
		m_grid.GetWindowRect(&rt);

		//����Ļ����ת���ɶԻ���������
		 ScreenToClient(&rt);
		 //ת����Ԫ������Ϊ�Ի���������
		rtBase.left+=rt.left;
		rtBase.top+=rt.top;
		rtBase.right+=rt.left;
		rtBase.bottom+=rt.bottom;
		

		cb.MoveWindow(&rtBase);
	
		cb.BringWindowToTop();
		cb.ShowWindow(SW_SHOW);

		iCol=2;
	

	}

}




void CUserManage::OnCbnSelchangeComboStatus(void)
{
	CString strSel;
	cb.GetLBText(cb.GetCurSel(),strSel);
	m_grid.SetItemText(iRow,iCol,(LPCSTR)strSel);
	cb.ShowWindow(SW_HIDE);
}


void CUserManage::OnCbnKillFocus(void)
{
	cb.ShowWindow(SW_HIDE);
	StoreDatabase();
}


void CUserManage::StoreDatabase(void)
{
	vector<string> vtCols;
	
	vtCols.push_back(MYSQL_PRC_RPT ); //�洢������
	vtCols.push_back("3");				//����������
	vtCols.push_back("0");				//������
	int iCols=m_grid.GetColumnCount();
	
	for(int idx=0; idx< iCols ; idx++)
		vtCols.push_back( (LPCSTR)m_grid.GetItemText(iRow,idx) );

	string szRet;

	CComFunc::callSqlPro(vtCols,szRet);
	
	if( ! szRet.compare(SZERROR) )
		 AfxMessageBox("���ô洢����ʧ��");
		 
}
