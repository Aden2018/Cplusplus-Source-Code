// DialogFromFileReadTxt.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "DialogFromFileReadTxt.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogFromFileReadTxt dialog


CDialogFromFileReadTxt::CDialogFromFileReadTxt(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogFromFileReadTxt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogFromFileReadTxt)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogFromFileReadTxt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogFromFileReadTxt)
	DDX_Control(pDX, IDC_LIST_LOG_FILE, m_list_logfile);
	DDX_Control(pDX, IDC_LIST_LOG, m_listLog);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogFromFileReadTxt, CDialog)
	//{{AFX_MSG_MAP(CDialogFromFileReadTxt)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_DATA, OnButtonImportData)
	ON_BN_CLICKED(IDOK_EXCEL, OnExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogFromFileReadTxt message handlers

void CDialogFromFileReadTxt::OnButtonImportData() 
{
   CString str;

    ZeroMemory(szPath, sizeof(szPath));  

    BROWSEINFO bi;  
    bi.hwndOwner = theApp.m_pMainWnd->m_hWnd;  
    bi.pidlRoot = NULL;  
    bi.pszDisplayName = szPath;  
    bi.lpszTitle = "百件大事数据存储目录选择：";  
    bi.ulFlags = 0;  
    bi.lpfn = NULL;  
    bi.lParam = 0;  
    bi.iImage = 0;  


    //弹出选择目录对话框
    LPITEMIDLIST lp ;
	
	lp = SHBrowseForFolder(&bi);  

    if(lp && SHGetPathFromIDList(lp, szPath))  
    {
		AfxBeginThread(readFromTxt,this);
       
    }


	

	
}

UINT CDialogFromFileReadTxt::readFromTxt(LPVOID ps)
{
	using namespace std;

	CDialogFromFileReadTxt * pFromTxtDialog=(CDialogFromFileReadTxt*)ps;
	
	CFileFind ff;

	CString fPath;
	fPath.Format("%s\\*.*",pFromTxtDialog->szPath);
	

	ifstream irTxt;

	CString fileName,strSql,strName;

	
	int i,icount(0);
	int iFiles(0);

	BOOL res = ff.FindFile(fPath);

	if( ! res ) {

		AfxMessageBox("Open Directory Error!!!!");
		return false;
	}

	while(res)
	{
		
		res = ff.FindNextFile();
		
		// 不遍历子目录
		
		if(! ff.IsDirectory() && !ff.IsDots())
			
		{
			fileName=ff.GetFilePath();
			
			//输出文件名
			strName=fileName.Mid(fileName.ReverseFind('\\')+1);
		
			strSql.Format("%d  ,%s",iFiles++,strName);
			pFromTxtDialog->m_list_logfile.AddString(strSql);
			pFromTxtDialog->m_list_logfile.SetCurSel(pFromTxtDialog->m_list_logfile.GetCount()-1);
		
		
			irTxt.open(fileName);

			icount=0;

			while(!irTxt.eof()) 
			{
				
				irTxt >> i;
				

				if( !i ) break;   
				
				++icount;	
				strSql.Format("%s   %d ,%ld ",strName,i,icount); //文件导入数量
				pFromTxtDialog->m_listLog.AddString(strSql);
				pFromTxtDialog->m_listLog.SetCurSel(pFromTxtDialog->m_listLog.GetCount()-1);
				
				
				strSql.Format(" Insert into HundredSelect(depart_name,order_num) values('%s',%d ) ",strName,i );
				if(! CComFunc::WriteSql(strSql) )
				{
					AfxMessageBox("ERROR，write_SQL error");
					break;
				}
				
			}
			irTxt.close();
			irTxt.clear();
			
		}
		
	}
	
	ff.Close(); 
	
	

	return true;

}

void CDialogFromFileReadTxt::OnOK() //export Excel
{

	
	CString strSql;
	strSql.Format("select 1,order_num,sum(num_times) nums ,\
		concat(cast(Round(sum(num_times)/(select count(distinct depart_name) from hundredselect )*100 ,0)  as char) ,'%%') \
		FROM hundredselect group by  order_num order by  nums desc ,order_num   ");




	CComFunc::ReadDataForGrid(strSql,m_grid );

	
}

BOOL CDialogFromFileReadTxt::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CComFunc::comSetGridHeader(m_grid,GRID_ID);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogFromFileReadTxt::OnExcel() 
{
	CComFunc::ToExcel(&m_grid);	
}
