// GhQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "GhQuery.h"
#include "progressIndicate.h"
#include "formGhList.h"
#include "comFunc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGhQuery dialog


CGhQuery::CGhQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CGhQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGhQuery)
	m_date = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	m_strEditor = _T("");
	m_strEnd = _T("");
	m_strStart = _T("");
	m_strTitle = _T("");
	m_strLayoutNum = _T("");
	//}}AFX_DATA_INIT
}


void CGhQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGhQuery)
	DDX_Control(pDX, IDC_COMBO_TYPE, m_Type);
	DDX_Control(pDX, IDC_COMBO_FACTORY, m_Factory);
	DDX_Control(pDX, IDC_COMBO_ARTICLE_TYPE, m_articleType);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	DDX_Text(pDX, IDC_EDIT_EDITOR, m_strEditor);
	DDX_Text(pDX, IDC_EDIT_END, m_strEnd);
	DDX_Text(pDX, IDC_EDIT_START, m_strStart);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_LAYOUT_NUM, m_strLayoutNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGhQuery, CDialog)
	//{{AFX_MSG_MAP(CGhQuery)
	ON_BN_CLICKED(IDOK_CLASSIFY, OnClassify)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK_CLASSIFY_EXCEL, &CGhQuery::OnBnClickedClassifyExcel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGhQuery message handlers

BOOL CGhQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString strSql;
	m_Factory.AddString(BLANKSTR);
	m_Type.AddString(BLANKSTR);
	m_articleType.AddString(BLANKSTR);
	
	arrArticleType.Add(BLANKSTR);
	arrFactory.Add(BLANKSTR);
	arrType.Add(BLANKSTR);

	long i(0);
	try{
		strSql.LoadString(IDS_SQL_NEWS_TYPE);
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			arrType.Add(CComFunc::GetSqlItem(i++));
			m_Type.AddString(CComFunc::GetSqlItem(i++));
		
			recSet->MoveNext();
	
		}
		recSet->Close();

		strSql.Format("Select factory_id,factory from factory order by rank ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			arrFactory.Add(CComFunc::GetSqlItem(i++));
			m_Factory.AddString(CComFunc::GetSqlItem(i++));
		
			recSet->MoveNext();
	
		}
		recSet->Close();

	//	strSql.Format("Select type_id,name from contribution_type order by rank ");
		strSql.Format("Select id,title from article_type where effect=1 order by rank ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			arrArticleType.Add(CComFunc::GetSqlItem(i++));
			m_articleType.AddString(CComFunc::GetSqlItem(i++));
		
			recSet->MoveNext();
	
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGhQuery::OnOK() 
{

	CProgressIndicate pq;
	pq.pDialog= this;

	pq.pThreadFunction = QueryGhList;
	pq.DoModal();

	CDialog::OnOK();
}
// 查询操作 改为存储过程调用
UINT CGhQuery::QueryGhList(LPVOID ps)
{
	
	CFormGhList *pf=(CFormGhList*)theApp.pParentGrid.pGrid;
	CGhQuery * pd =(CGhQuery *) ((CProgressIndicate *) ps )->pDialog ;

	CComFunc::SetGridHeader(pf->m_grid,CFormGhList::GRID_ID/* 表格头部ID*/,pf->vtAlign); 


	pd->UpdateData();

	pf->m_grid.SetRowCount(2);

	int iSel(0);


	vector<string> vtSz;
	vtSz.push_back(MYSQL_PRC_RPT); //存储过程名
	vtSz.push_back("1");			//查询
	vtSz.push_back("7");			//稿费查询
	CString str("");

	//日期
	vtSz.push_back((LPCSTR)pd->m_date.Format("%Y-%m-%d"));
	vtSz.push_back((LPCSTR)pd->m_date2.Format("%Y-%m-%d"));

	//报刊类型
	iSel= pd->m_Type.GetCurSel();
	if( !(iSel == CB_ERR || iSel == 0 ))
		str=pd->arrType[iSel] ;
	vtSz.push_back((LPCSTR)str);
	//姓名
	pd->m_strEditor.TrimRight();
	vtSz.push_back((LPCSTR)pd->m_strEditor );
	//起止期号 
	vtSz.push_back((LPCSTR)pd->m_strStart);
	vtSz.push_back((LPCSTR)pd->m_strEnd);
	//单位ID
	iSel=pd->m_Factory.GetCurSel();
	str="";
	if( !(iSel == CB_ERR || iSel == 0 ))
		str=pd->arrFactory[iSel] ;
	vtSz.push_back((LPCSTR)str);
	//文章类型
	iSel= pd->m_articleType.GetCurSel();
	str="";
	if( !(iSel == CB_ERR || iSel == 0 ))
		str=pd->arrArticleType[iSel] ;
	vtSz.push_back((LPCSTR)str);
	//标题

	pd->m_strTitle.TrimRight();
	vtSz.push_back((LPCSTR)pd->m_strTitle);
	//版面号
	pd->m_strLayoutNum.TrimRight();
	vtSz.push_back((LPCSTR) pd->m_strLayoutNum);
	
	_RecordsetPtr rec;
	CComFunc::callSqlPro(vtSz,rec);
	vector<int> vtCol;
	vtCol.push_back(10);
	vector<double> vtCount(1,0);

	CComFunc::ReadDataForGrid(pf->m_grid,rec,vtCol,vtCount,pf->vtAlign);

	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

	pd->SendMessage(WM_CLOSE,NULL,NULL);
	
	

	return true;
	
}

BOOL CGhQuery::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
		pMsg->wParam =VK_TAB;
	
	return CDialog::PreTranslateMessage(pMsg);
}


void CGhQuery::OnClassify() //人员汇总明细
{ 
	CFormGhList *pf=(CFormGhList*)theApp.pParentGrid.pGrid;


	CComFunc::SetGridHeader(pf->m_grid,GRID_ID/* 表格头部ID*/,vtAlign); 

	UpdateData();


	pf->m_grid.SetRowCount(2);
	
	CString strConstruct(BLANKSTR);

	vector<string> vtSz;
	vtSz.push_back( MYSQL_PRC_RPT); //存储过程名
	vtSz.push_back("1");			//查询
	vtSz.push_back("E");			//返回结果集
	
	unsigned long iStart(0),iEnd(0);
	int iSel(0);

	CString strSql;

//	if( ! m_strStart.IsEmpty() ){ //期号范围

		strSql.Format("%ld",atol(m_strStart) ); //开始期号 
		vtSz.push_back( (LPCSTR)strSql);
		strSql.Format("%ld",atol(m_strEnd) ); //结束期号
		vtSz.push_back( (LPCSTR)strSql);

//	}
	


	vtSz.push_back( (LPCSTR)m_date.Format("%Y-%m-%d") );
	vtSz.push_back( (LPCSTR)m_date2.Format("%Y-%m-%d") );

	
	iSel=m_Factory.GetCurSel();
	if( !(iSel == CB_ERR || iSel == 0 ))
		strConstruct.Format("%ld",atol(arrFactory[iSel] ) );
	else  strConstruct=BLANKSTR;
	
	vtSz.push_back((LPCSTR)strConstruct);
	

	vtSz.push_back((LPCSTR) m_strEditor);



	iSel= m_Type.GetCurSel();
	if( !(iSel == CB_ERR || iSel == 0 ))
		strConstruct.Format("%ld",atol(arrType[iSel] ) );
	else strConstruct=BLANKSTR;
	
	vtSz.push_back(  (LPCSTR)strConstruct );


	_RecordsetPtr rec;

	CComFunc::callSqlPro(vtSz,rec);
	vector<int> vtCol;
	vtCol.push_back(3);
	vector<double> vtCount(1,0);
	CComFunc::ReadDataForGrid(pf->m_grid,rec,vtCol,vtCount,vtAlign);	

	
}

//将已经按照姓名汇总的数据分别输出到excel文件中
void CGhQuery::OnBnClickedClassifyExcel()
{
	// 添加文件保存目录

    CString str,strPath;
	
//    ZeroMemory(szPath, sizeof(szPath));   

    BROWSEINFO bi;   
    bi.hwndOwner = m_hWnd;   
    bi.pidlRoot = NULL;   
	bi.pszDisplayName = str.GetBuffer(MAX_PATH);   
    bi.lpszTitle = "请选择汇总信息存放目录：";   
    bi.ulFlags = 0;   
    bi.lpfn = NULL;   
    bi.lParam = 0;   
    bi.iImage = 0;   
    //弹出选择目录对话框
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);   
	str.ReleaseBuffer();

	SHGetPathFromIDList(lp,strPath.GetBuffer(MAX_PATH)) ;
    strPath.ReleaseBuffer();
    
	if(strPath.GetLength() <3){
		AfxMessageBox("选择的目录无效,请重新选择可读写的目录....");
		return;
	}


	UpdateData();

	CFormGhList *pf=(CFormGhList*)theApp.pParentGrid.pGrid;
	int iRows=pf->m_grid.GetRowCount();
	int iCols=pf->m_grid.GetColumnCount();
	if( iRows < 3) {
		AfxMessageBox("没有数据需要进行分类汇总输出,请先进行数据分类汇总....");
		return;
	}
	int iType=m_Type.GetCurSel();
	CString strJournalType;
	if( iType == CB_ERR || iType == 1 )strJournalType="报刊合计";
	else m_Type.GetLBText(iType,strJournalType);

	CString strPath2;
	strPath2.Format("(%s)%s-%s",strJournalType,m_strStart,m_strEnd);
	if( strPath.Right(1) == '\\' )  //路径选择为根目录时,目录后会自动附加'\\'字符,如果是正常的目录,则没有附加的'\\',所以要进行判断
		strPath=strPath+strPath2;
	else 
		strPath=strPath+"\\"+strPath2;

	//判断目录是否存在    
	WIN32_FIND_DATA fd;  
    HANDLE hFind = FindFirstFile(strPath, &fd);  
   // BOOL bFilter = (FALSE == dwFilter) ? TRUE : fd.dwFileAttributes & dwFilter;  
   // BOOL RetValue = ((hFind != INVALID_HANDLE_VALUE) && bFilter) ? TRUE : FALSE;  

    FindClose(hFind);  
	if( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			AfxMessageBox("当前目前下已存在要导出的文件目录,如需导出,请重新选择目录...");
			return;
	}
	


	if( ! CreateDirectory(strPath,NULL) ){
		AfxMessageBox("Create directory is error !!");
		return;
	}
	strPath+="\\";
	const int COL_FACTORY=1,COL_NAME=2,COL_PRICE=3,COL_SQ=0;

	_Application app2;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;
	 COleVariant vOpt(DISP_E_PARAMNOTFOUND,VT_ERROR);
const int  IDC_PROGRESS_EXCEL=WM_USER+10003;
	CProgressEx pp;
	CRect r1(0,0,400,25);
	pp.Create(WS_CHILD |PBS_SMOOTH|WS_BORDER ,r1,AfxGetMainWnd()->GetForegroundWindow(),IDC_PROGRESS_EXCEL);
	pp.UpdateWindow();
	pp.ShowWindow(SW_SHOW);
	pp.CenterWindow();
	pp.Invalidate();
	pp.SetRange32(0,iRows );
	pp.strView="正在准备导出...请稍等!!";

	app2.CreateDispatch("excel.application");
	if(!app2){
		AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
		return;
	}
	CString strFileName;
	strFileName.Format("%sspec.xls",LoginInformation.path);
	books2=app2.GetWorkbooks();


	Range vRange;
	SQ_EXCEL9::Font font;
	long x,y;
	CString str1,str2;
	
	app2.SetVisible(false);
//	pp.strView="";
	books2=app2.GetWorkbooks(); //OPEN excel template
	book2=books2.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	sheets2=book2.GetWorksheets();
	sheet2=sheets2.GetItem(COleVariant((short)1));


	CString szFlgFactory,szTmp;
	CString szOutFile,szCell;
	int xlsRow(3),clrRow(0);	//clrRow记录文件最后一行行号
	for(int i=1; i< iRows ;i++)
	{
		szFlgFactory=pf->m_grid.GetItemText(i,COL_FACTORY);

		if( xlsRow ==3 ){			
			szCell="a1";
			vRange=sheet2.GetRange(_variant_t(szCell),_variant_t(szCell) );
			vRange.SetValue(_variant_t(szFlgFactory));
			szOutFile.Format("%s%s(%s-%s).xls",strPath,szFlgFactory,m_strStart,m_strEnd);
			if(  clrRow ){
				szCell.Format("A3:%c%d",'A'+COL_PRICE,clrRow+1);
				vRange=sheet2.GetRange(_variant_t(szCell),_variant_t(szCell) );
				szCell="";
				vRange.SetValue(_variant_t(szCell));
				clrRow=0;
			}
		}

		if( i !=1 && xlsRow!= 3 ){
	
			szTmp=pf->m_grid.GetItemText(i-1,COL_FACTORY);
			if( szTmp.Compare(szFlgFactory) !=0 ){
	
				szCell.Format("%c%d",'A'+COL_PRICE,xlsRow);
				vRange=sheet2.GetRange(_variant_t(szCell),_variant_t(szCell) );
				szCell.Format("=sum(D3:D%d)",xlsRow-1);
				vRange.SetValue(_variant_t(szCell));
			
				book2.SaveAs(_variant_t(szOutFile),vOpt,vOpt,vOpt,vOpt,vOpt,0L,vOpt,vOpt,vOpt,vOpt);
			
				xlsRow=3;
				i--;
				continue;
			}

		}
		for(int iCol=0; iCol< iCols ; iCol++){	//输出到excel表格
			szCell.Format("%c%d",'A'+iCol,xlsRow);
			vRange=sheet2.GetRange(_variant_t(szCell),_variant_t(szCell) );
			if( iCol == 0 ) szCell.Format("%d",xlsRow-2);   //xlsRow 起始行为3，第一列为序号列，
			else 	
				szCell=pf->m_grid.GetItemText(i,iCol);
			vRange.SetValue(_variant_t(szCell));
		}
		xlsRow++;
		clrRow=xlsRow;
	
		pp.strView.Format("%2.0f%%",double(i)/iRows*100);
		pp.SetPos(i);

	}

	pp.SendMessage(WM_CLOSE);

	sheet2.ReleaseDispatch();

	sheets2.ReleaseDispatch();

	book2.SetSaved(true);	//设置已存储标志，在quit是不提示更改保存
	book2.Close(_variant_t(false ),vOpt,vOpt);

	books2.Close();
	book2.ReleaseDispatch();
	books2.ReleaseDispatch();
	app2.Quit();
	app2.ReleaseDispatch();	
	
}
