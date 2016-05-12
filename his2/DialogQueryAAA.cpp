// DialogQueryAAA.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "DialogQueryAAA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogQueryAAA dialog


CDialogQueryAAA::CDialogQueryAAA(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogQueryAAA::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogQueryAAA)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogQueryAAA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogQueryAAA)
	DDX_Control(pDX, IDCANCEL, m_3);
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, ID_BUTTON_CLEAR, m_1);
	DDX_Control(pDX, IDC_LIST3, listC);
	DDX_Control(pDX, IDC_LIST2, listB);
	DDX_Control(pDX, IDC_LIST1, listA);
	DDX_Control(pDX, IDC_COMBO1, combo1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogQueryAAA, CDialog)
	//{{AFX_MSG_MAP(CDialogQueryAAA)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	ON_LBN_DBLCLK(IDC_LIST2, OnDblclkList2)
	ON_LBN_DBLCLK(IDC_LIST3, OnDblclkList3)
	ON_BN_CLICKED(ID_BUTTON_CLEAR, OnButtonClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogQueryAAA message handlers

BOOL CDialogQueryAAA::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

try{
		typeArray.RemoveAll();		
		strSql.Format(" SELECT ds1,ds2 FROM lsq_mixed WHERE ds3='DIALOG3' AND ds4='AAA' order by n1  ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
		
			strSql=(char*)_bstr_t(recSet->GetCollect("ds1").vt==VT_NULL?"":recSet->GetCollect("ds1"));
			combo1.AddString(strSql);
			strSql=(char*)_bstr_t(recSet->GetCollect("ds2").vt==VT_NULL?"":recSet->GetCollect("ds2"));
			typeArray.Add(strSql);

			
			recSet->MoveNext();
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}
	combo1.SetCurSel(0);
	OnSelchangeCombo1();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogQueryAAA::OnSelchangeCombo1() 
{
	if(combo1.GetCurSel() == CB_ERR ) return;
	
	strSql=typeArray.GetAt( combo1.GetCurSel() );
	listA.ResetContent();

	if( strSql == "报销内容") {
		strSql.Format(" SELECT ds3 FROM lsq_economy_rank ORDER BY n1 ");
	}
	else if( strSql == "报销项目"){
		strSql.Format( " SELECT ds2 FROM lsq_gh_type WHERE ds3='B' AND substr(ds1,1,2)='AA' ORDER BY n1" );

	}
	else return;
	try{

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
		
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(0L)->Value);
			listA.AddString(strSql);

			
			recSet->MoveNext();
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return ;
	}



	
	
}

void CDialogQueryAAA::OnDblclkList1() 
{
	if(combo1.GetCurSel() == CB_ERR ) return;
	
	CString strTmp;
	strSql=typeArray.GetAt( combo1.GetCurSel() );

	listA.GetText(listA.GetCurSel(),strTmp);	

	if( strSql == "报销内容" && listB.FindString(-1,strTmp)== LB_ERR ) {
		
		listB.AddString(strTmp);
	}
	else if( strSql == "报销项目" && listC.FindString(-1,strTmp)== LB_ERR){
		listC.AddString(strTmp);
	}
	else return;
	
}

void CDialogQueryAAA::OnDblclkList2() 
{
	listB.DeleteString( listB.GetCurSel() );
	
}

void CDialogQueryAAA::OnDblclkList3() 
{
	// TODO: Add your control notification handler code here
	listC.DeleteString( listC.GetCurSel() );
	
}

void CDialogQueryAAA::OnButtonClear() 
{
	listB.ResetContent();
	listC.ResetContent();
}

void CDialogQueryAAA::OnOK() 
{
	strSql="";
	strSql2="";

	int i=0;
	CString strTmp;

	if( listB.GetCount() !=0 ){ //列出经济内容
		strSql=" IN ( ";
		for(i=0; i< listB.GetCount() ; i++ ){
			listB.GetText(i,strTmp);
			if( i != listB.GetCount()-1 )
				strSql+="'"+strTmp+"',";
			else 
				strSql+="'"+strTmp+"')";
			
		}

	}
	if( listC.GetCount() !=0 ) {//列出报销类别
		
		strSql2=" IN ( ";

		for(i=0; i< listC.GetCount() ; i++ ){
		
			listC.GetText(i,strTmp);
			if( i != listC.GetCount()-1 )
				strSql2+="'"+strTmp+"',";
			else 
				strSql2+="'"+strTmp+"')";
			
		}

	}
	CDialog::OnOK();

	
}
