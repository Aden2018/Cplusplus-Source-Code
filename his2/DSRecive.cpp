// DSRecive.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "DSRecive.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSRecive dialog


CDSRecive::CDSRecive(CWnd* pParent /*=NULL*/)
	: CDialog(CDSRecive::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDSRecive)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDSRecive::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDSRecive)
	DDX_Control(pDX, IDC_COMBO_DEPART, c_depart);
	DDX_Control(pDX, IDC_LIST2, c_list2);
	DDX_Control(pDX, IDC_LIST1, c_list1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDSRecive, CDialog)
	//{{AFX_MSG_MAP(CDSRecive)
	ON_CBN_SELCHANGE(IDC_COMBO_DEPART, OnSelchangeComboDepart)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
	ON_BN_CLICKED(IDC_BUTTON_ALL, OnButtonAll)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSRecive message handlers

BOOL CDSRecive::OnInitDialog() 
{
	CDialog::OnInitDialog();

	c_list1.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	c_list2.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
//			{"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
//		"产地BM","产地","库存量","售价","进价","指导价","取药数"}; //共14列
	int i=0,y=0;
	CString str1[]={"ID","部门名","姓名"},strSql;
	int width[]={0,100,80};

	while(i<sizeof(str1)/sizeof(CString))
	{
		c_list1.InsertColumn(i,str1[i],LVCFMT_LEFT,width[i]);
		c_list2.InsertColumn(i,str1[i],LVCFMT_LEFT,width[i]);
		i++;
	}

	try{
		strSql.Format("select DISTINCT KFMC from STOREROOM ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetCollect("KFMC").vt==VT_NULL?" ":recSet->GetCollect("KFMC"));
			c_depart.AddString(strSql);
			recSet->MoveNext();

		
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false ;
	}		
	

	if(pList->GetItemCount() > 0)
	{
		for( int i=0,y=0 ; i< pList->GetItemCount() ; i++,y=0 )
		{

			c_list2.InsertItem(i," ");
			c_list2.SetItemText(i,y,pList->GetItemText(i,y));
			y++;
			c_list2.SetItemText(i,y,pList->GetItemText(i,y));
			y++;
			c_list2.SetItemText(i,y,pList->GetItemText(i,y));

		}




	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDSRecive::OnSelchangeComboDepart() 
{
	CString strSql,strTemp;
	if( c_depart.GetCurSel() == CB_ERR )return;
	c_list1.DeleteAllItems();

	c_depart.GetLBText(c_depart.GetCurSel(),strTemp);
	long index=0,y;
	try{
		strSql.Format("select RYBM,KFMC,NAME from operator a,storeroom b where a.KFBM=b.KFBM and SFDEL='n' AND b.KFMC='%s' ",strTemp);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			y=0;
		//	strSql=(char*)_bstr_t(recSet->GetCollect("KFMC").vt==VT_NULL?" ":recSet->GetCollect("KFMC"));
		//	c_depart.AddString(strSql);
			c_list1.InsertItem(index," ");
			c_list1.SetItemText(index,y++,(char*)_bstr_t(recSet->GetCollect("RYBM")));
			c_list1.SetItemText(index,y++,(char*)_bstr_t(recSet->GetCollect("KFMC")));
			c_list1.SetItemText(index,y++,(char*)_bstr_t(recSet->GetCollect("NAME")));
			index++;


			recSet->MoveNext();

		
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}		
	
	
}

void CDSRecive::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UINT nIndex,lines;
	nIndex=c_list1.GetNextItem(-1,LVNI_SELECTED);
	if(nIndex== -1 ) {
		AfxMessageBox("请先选择。。。");
		return ;
	}

	CString strRybm;
	lines = c_list2.GetItemCount();
	strRybm=c_list1.GetItemText(nIndex,0);
	for(int i=0;i<lines;i++)
	{
		if( strRybm == c_list2.GetItemText(i,0) ) return;
	}

	c_list2.InsertItem(lines," ");
	pList->InsertItem(lines," ");
	for(i=0;i<3; i++ )
	{
		c_list2.SetItemText(lines,i,c_list1.GetItemText(nIndex,i));
		pList->SetItemText(lines,i,c_list1.GetItemText(nIndex,i));
	}

	
//	*pResult = 0;
}

void CDSRecive::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) 
{

	UINT nIndex;
	nIndex=c_list2.GetNextItem(-1,LVNI_SELECTED);
	if(nIndex== -1 ) {
		AfxMessageBox("请先选择。。。");
		return ;
	}
	c_list2.DeleteItem(nIndex);
	pList->DeleteItem(nIndex);


//	*pResult = 0;
}

void CDSRecive::OnOK() 
{
	strName="";
	for(int i=0; i< c_list2.GetItemCount() ; i++)
	{
		if(i != 0) strName+=",";
		strName+=c_list2.GetItemText(i,2);
	}
	
	CDialog::OnOK();
}

void CDSRecive::OnButtonAll() 
{
	CString strSql,strT1,strT2,strT3;
	long y=0,index=0;

	c_list2.DeleteAllItems();

	try{
		strSql.Format("select RYBM,KFMC,NAME from operator a,storeroom b where a.KFBM=b.KFBM and SFDEL='n'  ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			y=0;
			c_list2.InsertItem(index," ");
			c_list2.SetItemText(index,y++,strT1=(char*)_bstr_t(recSet->GetCollect("RYBM")));
			c_list2.SetItemText(index,y++,strT2=(char*)_bstr_t(recSet->GetCollect("KFMC")));
			c_list2.SetItemText(index,y++,strT3=(char*)_bstr_t(recSet->GetCollect("NAME")));
			y=0;
			pList->InsertItem(index," ");
			pList->SetItemText(index,y++,strT1);
			pList->SetItemText(index,y++,strT2);
			pList->SetItemText(index,y++,strT3);
			index++;
			recSet->MoveNext();
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}		
	
}

void CDSRecive::OnButtonDelete() 
{
	c_list2.DeleteAllItems();	
	pList->DeleteAllItems();
}
