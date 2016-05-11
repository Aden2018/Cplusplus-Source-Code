// SpecReporterManager.cpp : 实现文件
//

#include "stdafx.h"
#include "his3.h"
#include "SpecReporterManager.h"
#include "afxdialogex.h"
#include <algorithm>
#include <sstream>
using namespace std;

// CSpecReporterManager 对话框

IMPLEMENT_DYNAMIC(CSpecReporterManager, CDialogEx)

CSpecReporterManager::CSpecReporterManager(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSpecReporterManager::IDD, pParent),szProName("prc_spec_Reporter"),szError("LSQ_ERROR")
{

	m_szName = _T("");
	iStatus= -2 ; //未存储
}

CSpecReporterManager::~CSpecReporterManager()
{
}

void CSpecReporterManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_GridControl(pDX, IDC_GRID, m_grid);
	DDX_Control(pDX, IDC_COMBO_FACTORY, m_cbFactory);
	DDX_Control(pDX, IDC_COMBO_YEAR, m_cbYear);
	DDX_Text(pDX, IDC_EDIT_NAME, m_szName);
	DDX_Control(pDX, IDOK_ADD, m_1);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel3);
}


BEGIN_MESSAGE_MAP(CSpecReporterManager, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSpecReporterManager::OnBnClickedOk)
	ON_BN_CLICKED(IDOK_ADD, &CSpecReporterManager::OnBnClickedAdd)
	ON_EN_KILLFOCUS(IDC_EDIT_NAME, &CSpecReporterManager::OnEnKillfocusEditName)
END_MESSAGE_MAP()


// CSpecReporterManager 消息处理程序


void CSpecReporterManager::OnBnClickedOk()
{
	UpdateData();
	
	vector<string> vtSz;
	vtSz.push_back("prc_spec_reporter"); //存储过程名
	vtSz.push_back("1");			//查询
	vtSz.push_back("6");			//返回结果集
	CString str;
	int iSel=m_cbFactory.GetCurSel();
	int i;
	if( iSel == CB_ERR || iSel == 0  )
	 	 str="";
	else	
		 str.Format("%d",vtFactory[iSel]);
	//单位ID
	vtSz.push_back((LPCSTR)str);
	//年度
	m_cbYear.GetLBText(m_cbYear.GetCurSel(),str);
	vtSz.push_back((LPCSTR)str);
	//姓名
	vtSz.push_back((LPCSTR)m_szName);

	_RecordsetPtr rec;

	CComFunc::callSqlPro(vtSz,rec);
	CComFunc::ReadDataForGrid(m_grid,rec);

	
}


BOOL CSpecReporterManager::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CComFunc::SetGridHeader(m_grid,1,vtAlign); 
	m_grid.SetEditable();

	CString strSql,str;
	strSql.Format(" Select factory_id,factory From factory Where effect=1 order by rank ");
	m_cbFactory.AddString("");
	vtFactory.push_back(-1);
	if( ! CComFunc::SqlComboRead(m_cbFactory,vtFactory,strSql) ) return false;
	
	int iYear=3;
	int iCentury=COleDateTime::GetCurrentTime().GetYear();
	while(iYear--)
	{
		str.Format("%d",iCentury--);
		m_cbYear.AddString(str);
	}
	m_cbYear.SetCurSel(0);

	return TRUE;  
}

/*
*	Copyright @2014 凌绍清
*	summary:
*			添加年度特约通讯员
*	参数传入格式：
*			2|0| 姓名| 单位ID| 年度
*
*
*
*/

void CSpecReporterManager::OnBnClickedAdd()
{
	UpdateData();
	int iSel=m_cbFactory.GetCurSel();
	if( iSel ==CB_ERR || iSel == 0 || m_szName.IsEmpty() )
	{
		AfxMessageBox("请先填写完整信息后,再点击添加");
		return;

	}
	CString strSql,str;

	vector<string> vtSz;
	vtSz.push_back( szProName.c_str() );			//存储过程名
	vtSz.push_back("2|0");								//操作命令
	vtSz.push_back( (LPCSTR) m_szName);		//姓名
	strSql.Format("%d",vtFactory[iSel]);
	vtSz.push_back( (LPCSTR)strSql );			//单位ID
	m_cbYear.GetLBText(m_cbYear.GetCurSel(),strSql);
	vtSz.push_back( (LPCSTR)strSql );			//年度

	string szRet;

	CComFunc::callSqlPro(vtSz,szRet);

	AfxMessageBox(szRet.c_str());


	
}


BOOL CSpecReporterManager::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){
		if( pMsg->hwnd == GetDlgItem(IDOK_ADD)->m_hWnd )
		{
			OnBnClickedAdd();
			return false;
		}
		pMsg->wParam = VK_TAB;

	}
	

	return CDialogEx::PreTranslateMessage(pMsg);
}

//根据输入的姓名在联系人表格中查找,
void CSpecReporterManager::OnEnKillfocusEditName()
{
	UpdateData();
	if( m_szName.IsEmpty() ) return;
	
	CString str[2];
	CString strSql;
	try{
		str[0]=BLANKSTR;
		str[1]=BLANKSTR;
		strSql.Format("Select factory_id from Contacter Where name='%s' ",m_szName);
		str[0]=CComFunc::GetString(strSql);

		if( ! str[0].IsEmpty() ){  //找到
		
			
			std::vector<int>::iterator iteFactory=std::find(vtFactory.begin(),vtFactory.end(),atoi(str[0]) );
			iStatus=iteFactory-vtFactory.begin();
			m_cbFactory.SetCurSel( iStatus );
			
		
		
		
		}
		else
			iStatus=0 ; //没有此联系人

				

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}		 
	
}
