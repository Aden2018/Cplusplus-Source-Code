// Journal.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "Journal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Journal dialog


Journal::Journal(CWnd* pParent /*=NULL*/)
	: CDialog(Journal::IDD, pParent)
{
	//{{AFX_DATA_INIT(Journal)
	m_strExpressFee = _T("");
	m_strGetFee = _T("");
	m_ISSN = _T("");
	m_strMakeFee = _T("");
	m_strPostFee = _T("");
	m_strNums = _T("");
	m_date = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	strTitle.LoadString(IDS_STR_JOURNAL_BASE);
	ft.CreatePointFont(180,"微软雅黑");
}


void Journal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Journal)
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboType);
	DDX_Text(pDX, IDC_EDIT_EXPRESS_FEE, m_strExpressFee);
	DDX_Text(pDX, IDC_EDIT_GET_FEE, m_strGetFee);
	DDX_Text(pDX, IDC_EDIT_ISSN, m_ISSN);
	DDX_Text(pDX, IDC_EDIT_MAKE_FEE, m_strMakeFee);
	DDX_Text(pDX, IDC_EDIT_POST_FEE, m_strPostFee);
	DDX_Text(pDX, IDC_EDIT_RE_NUMS, m_strNums);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(Journal, CDialog)
	//{{AFX_MSG_MAP(Journal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Journal message handlers

BOOL Journal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	long i;
	arrType.RemoveAll();

	SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&ft);
	try{
		strSql.Format("Select news_id,news_name from news_type order by rank ");
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			arrType.Add(CComFunc::GetSqlItem(i++));
			m_comboType.AddString(CComFunc::GetSqlItem(i++));
		
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		
	
	m_comboType.SetCurSel(0);
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL Journal::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){

		pMsg->wParam = VK_TAB;

	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void Journal::OnOK()  //添加 
{
	UpdateData();
	CString str[2];
	
	if( m_ISSN.IsEmpty() ){

		AfxMessageBox("请先填写报刊发行期号等基本信息");
		return;
	}
	
	try{
		str[0]=arrType[m_comboType.GetCurSel()]; //类型
		str[1]=m_date.Format("%Y-%m-%d");

		strSql.Format(" Insert into newspaper(release_date,layout_nums,release_type ,get_contribution_fee,ISSN,write_time,\
				make_fee,post_fee,express_fee )  values('%s',%d,%ld,%.2f,%ld,now(),%.2f,%.2f,%.2f ) ",
				str[1],atol(m_strNums),atol(str[0]),atof(m_strGetFee),atol(m_ISSN),atof(m_strMakeFee),atof(m_strPostFee),atof(m_strExpressFee) );

		if( !CComFunc::WriteSql(strSql) )
		{	
			AfxMessageBox("添加出现错误,请重试!");
			return;
		}

		ResetCtrl();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}		
}

void Journal::ResetCtrl()
{
	strSql="0";
	m_strExpressFee=strSql;
	m_strMakeFee=strSql;
	m_strPostFee=strSql;
	m_ISSN=BLANKSTR;
	m_strNums=strSql;
	m_strGetFee=strSql;
	UpdateData(false);
	GetDlgItem(IDC_DATETIMEPICKER1)->SetFocus();
}
