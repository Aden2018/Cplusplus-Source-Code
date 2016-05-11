// MakeFee.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "MakeFee.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMakeFee dialog


CMakeFee::CMakeFee(CWnd* pParent /*=NULL*/)
	: CDialog(CMakeFee::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMakeFee)
	m_strCmt = _T("");
	m_rq = COleDateTime::GetCurrentTime();
	m_rq2 = COleDateTime::GetCurrentTime();
	m_strFee = _T("");
	//}}AFX_DATA_INIT
}


void CMakeFee::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMakeFee)
	DDX_Control(pDX, IDC_COMBO_MAKE_FACTORY, m_MakeFactory);
	DDX_Control(pDX, IDC_LIST_NUM, m_listBox);
	DDX_Control(pDX, IDC_COMBO_RELEASE_NUM, m_ReleaseNum);
	DDX_Control(pDX, IDC_COMBO_FEE_TYPE, m_FeeType);
	DDX_Text(pDX, IDC_EDIT_CMT2, m_strCmt);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_rq);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_rq2);
	DDX_Text(pDX, IDC_EDIT_FEE, m_strFee);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMakeFee, CDialog)
	//{{AFX_MSG_MAP(CMakeFee)
	ON_CBN_SELCHANGE(IDC_COMBO_FEE_TYPE, OnSelchangeComboFeeType)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakeFee message handlers

BOOL CMakeFee::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	long i=0;

	try{
		
		strSql.LoadString(IDS_SQL_NEWS_TYPE);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			m_arrType.Add(CComFunc::GetSqlItem(i++));
			m_FeeType.AddString(CComFunc::GetSqlItem(i++));
			
			recSet->MoveNext();
	
		}
		recSet->Close();

		strSql.Format(" Select ID,name FROM business Where effect=1 Order by rank ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			m_arrFactory.Add(CComFunc::GetSqlItem(i++));
			m_MakeFactory.AddString(CComFunc::GetSqlItem(i++));
			
			recSet->MoveNext();
	
		}
		recSet->Close();

			
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		


	



	return TRUE; 
	              
}

void CMakeFee::OnSelchangeComboFeeType() 
{
	m_ReleaseNum.ResetContent();
	m_arrISSN.RemoveAll();

/*	m_listBox.ResetContent(); //列表框内容清除
	m_arrList.RemoveAll();
*/
	long i=0;

	try{
		
		strSql.Format(" Select ID,ISSN FROM newsPaper WHERE release_type=%ld Order by release_DATE Desc limit 10 ",
			atol(m_arrType[m_FeeType.GetCurSel()] ) ); 

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			m_arrISSN.Add(CComFunc::GetSqlItem(i++));
			m_ReleaseNum.AddString(CComFunc::GetSqlItem(i++));
			
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return  ;
	}		
	
}

void CMakeFee::OnButtonAdd() 
{
	long i;
	i=m_ReleaseNum.GetCurSel();
	if( CB_ERR == i ){
		AfxMessageBox("请先选择期号...");
		return;
	}

	m_ReleaseNum.GetLBText(i,strSql);
	int x(0); //查找重复项目
	int iCount=m_arrList.GetSize();

	for(;x< iCount ; ++x)
	{
		if( m_arrList[x] == m_arrISSN[i] ) break;
	}
	if( x == iCount ){
		m_listBox.AddString(strSql);
		
		m_arrList.Add(m_arrISSN[i] ); //期号ID
		arrNewsType.Add( m_arrType[m_FeeType.GetCurSel()] ); //报刊类型代码
	}
}

void CMakeFee::OnButtonDel() 
{
	long i;
	i=m_listBox.GetCurSel();
	if( LB_ERR == i ){
		AfxMessageBox("请先选择要删除的条目...");
		return;
	}
	m_listBox.DeleteString(i);
	m_arrList.RemoveAt(i); 
	arrNewsType.RemoveAt(i);
}

void CMakeFee::OnOK() 
{
	UpdateData();
	const int ZERO=0;
	if( CB_ERR == m_FeeType.GetCurSel() || ZERO == m_arrList.GetSize() || m_MakeFactory.GetCurSel() == CB_ERR  )
	{
		AfxMessageBox("请先将参数填写完整...");
		return;

	}

	int i(0),iCount=m_arrList.GetSize(),iID;
	CString strSub,strTmp;
	try{
		strSql.Format("select ifnull(max(id)+1,1) from make_fee");
		strSql=CComFunc::GetString(strSql); //获取ID
		iID=atol(strSql);

		HospitalConnect->BeginTrans();
		
		for( ; i < iCount ; ++i ) //新增期号费用关联表
		{
			m_listBox.GetText(i,strTmp);

			strSub.Format("INSERT INTO Fee_Release_Num(Id,num,news_type) Values(%ld,%ld,%ld)  ",
				iID,atol(strTmp) ,atol(arrNewsType[i]) );

			HospitalConnect->Execute(_bstr_t(strSub),NULL,adCmdText) ;

		}
		

		strSub.Format("INSERT INTO make_fee(ID,price,rq,rq2,cmt,release_type,make_id) values(%ld,%.2f,'%s','%s',\
			'%s',%ld,%ld ) ",iID,atof(m_strFee),m_rq.Format("%Y-%m-%d"),m_rq2.Format("%Y-%m-%d"),m_strCmt,
			atol(m_arrType[m_FeeType.GetCurSel()]),atol(m_arrFactory[m_MakeFactory.GetCurSel()]) );
		
		HospitalConnect->Execute(_bstr_t(strSub),NULL,adCmdText) ;
		HospitalConnect->CommitTrans();
		


		AfxMessageBox("添加成功！");
		ResetData();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}		 



}

BOOL CMakeFee::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){

		pMsg->wParam = VK_TAB;

	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CMakeFee::ResetData()
{
	m_ReleaseNum.ResetContent();
	m_arrISSN.RemoveAll();
	
	m_listBox.ResetContent(); //列表框内容清除
	m_arrList.RemoveAll();
	
	m_strCmt=BLANKSTR;
	m_strFee=BLANKSTR;

	UpdateData(false);

}

void CMakeFee::OnButtonClear() 
{
	m_listBox.ResetContent(); //列表框内容清除
	m_arrList.RemoveAll();
	arrNewsType.RemoveAll();
	
}




