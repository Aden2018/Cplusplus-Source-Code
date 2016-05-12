// DialogRoleset.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "DialogRoleset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogRoleset dialog


CDialogRoleset::CDialogRoleset(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogRoleset::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogRoleset)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	flagRy=false;
}


void CDialogRoleset::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogRoleset)
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, IDCANCEL, m_1);
	DDX_Control(pDX, IDC_EDIT_NAME, c_name);
	DDX_Control(pDX, IDC_TREE_RY, c_tree);
	DDX_Control(pDX, IDC_LIST_ROLE, c_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogRoleset, CDialog)
	//{{AFX_MSG_MAP(CDialogRoleset)
	ON_NOTIFY(NM_CLICK, IDC_TREE_RY, OnClickTreeRy)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_RY, OnDblclkTreeRy)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ROLE, OnDblclkListRole)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogRoleset message handlers

BOOL CDialogRoleset::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	c_list.SetBkColor(RGB(65,123,128));
	c_list.SetTextBkColor(RGB(65,123,128));
	c_list.SetTextColor(RGB(255,255,255));
	CString str[]={"序号","权限名称","状态"},strSql,strTemp;
	int width[]={60,200,60},i=0;
	while(i<sizeof(str)/sizeof(CString))
	{
		c_list.InsertColumn(i,str[i],LVCFMT_LEFT,width[i]);
		i++;
	}
	c_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	// TODO: Add extra initialization here
	try{
		strSql.Format("select Name from LSQ_ROLE_DESC ");
				
		i=0;
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
				strSql=(char*)_bstr_t(recSet->GetCollect("NAME"));
				c_list.InsertItem(i," ");
				strTemp.Format("%ld",i+1);
				c_list.SetItemText(i,0,strTemp);
				c_list.SetItemText(i,1,strSql);
				i++;
				recSet->MoveNext();
			}
		RoleLines=i;
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("基础菜单项被破坏，请联系程序设计人员....");
		recSet->Close();
		return false;
	}

	InsertOperator();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogRoleset::InsertOperator()
{
	CString strSql;
	int i=0,j=0;
	HTREEITEM  ptree[40];
//将职工基本信息插入到TREE中
	HTREEITEM root=c_tree.InsertItem("软件操作人员");
	try{
		strSql.Format("select distinct(KFMC) from operator a,storeroom b  where a.kfbm=b.kfbm and sfdel='n' ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
			ptree[i++]=c_tree.InsertItem((char*)_bstr_t(recSet->GetCollect("KFMC")),root);
			recSet->MoveNext();
		}
		recSet->Close();
	
		for(j=0;j<i;j++){
			strSql.Format("select name from operator a,storeroom b where a.kfbm=b.kfbm and KFMC='%s' and sfdel='n' ",c_tree.GetItemText(ptree[j]));
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			while(!recSet->adoEOF){
				c_tree.InsertItem((char*)_bstr_t(recSet->GetCollect("name")),ptree[j]);
				recSet->MoveNext();
			}
			recSet->Close();
		}
	}
	catch(_com_error e)
	{
		AfxMessageBox("读取基础数据库出现错误,请联系程序设计人员....");
		recSet->Close();
		return;
	}
	c_tree.Expand(root,TVE_EXPAND);
}

void CDialogRoleset::OnClickTreeRy(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

//	*pResult = 0;
}

void CDialogRoleset::OnDblclkTreeRy(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	TVITEM  treev;

	HTREEITEM curSel=c_tree.GetSelectedItem(),parentSel;
	treev.mask=TVIF_CHILDREN;
	treev.hItem=curSel;
	c_tree.GetItem(	&treev);
	if(treev.cChildren==0){ //如果是最后结点的话则进行调出显示
		parentSel=c_tree.GetParentItem(curSel);
		CString strRole,strSql;
		int i;
		strSel=c_tree.GetItemText(curSel);
		strParent=c_tree.GetItemText(parentSel);
		c_name.SetWindowText(strSel);
		
		flagRy=true;
		try{
			strSql.Format("select NVL(ROLE,' ') as ROLE from storeroom a,operator b,lsq_role c where a.kfbm=b.kfbm \
				and b.rybm=c.rybm and  b.name ='%s' and a.kfmc='%s' ",strSel,strParent);
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){
				strRole=(char*)_bstr_t(recSet->GetCollect("ROLE"));
			}
			else strRole="";
		
			recSet->Close();
			strSql.Format("select RYBM from storeroom a,operator b where a.kfbm=b.kfbm and kfmc='%s' and name='%s' ",strParent,strSel);
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){
				strRybm=(char*)_bstr_t(recSet->GetCollect("RYBM"));
			}
			recSet->Close();

		}
		catch(_com_error e)
		{
			AfxMessageBox("读取基础数据库出现错误,请联系程序设计人员....");
			AfxMessageBox(strSql);
			recSet->Close();
			return;
		}
		if(strRole.IsEmpty())for(i=0;i<RoleLines;i++)c_list.SetItemText(i,2,"Х");
		else {
			for(i=0;i<strRole.GetLength();i++)
				if(strRole.Mid(i,1)=="1")c_list.SetItemText(i,2,"√");
				else c_list.SetItemText(i,2,"Х");
		}
		
	}
	
	
//	*pResult = 0;
}

void CDialogRoleset::OnDblclkListRole(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(!flagRy)return;
	UINT nIndex;
	nIndex=c_list.GetNextItem(-1,LVNI_SELECTED);
	if(nIndex== -1 ) {
		AfxMessageBox("请先选择。。。");
		return ;
	}
	CString strTemp;
	strTemp=c_list.GetItemText(nIndex,2);
	if(strTemp == "√" )c_list.SetItemText(nIndex,2,"Х");
	else c_list.SetItemText(nIndex,2,"√");


	
//	*pResult = 0;
}

void CDialogRoleset::OnOK() 
{
	if(!flagRy)return; //如果未选则返回
	CString strTemp,strRole(""),strSql;
	for(int i=0;i<RoleLines;i++){
		strTemp=c_list.GetItemText(i,2);
		if(strTemp=="√")strRole+="1";
		else strRole+="0";
	}
	try{
		HospitalConnect->BeginTrans();
		strSql.Format("delete from LSQ_ROLE where RYBM='%s' ",strRybm);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		strSql.Format("Insert into LSQ_ROLE(rybm,role) values('%s','%s') ",strRybm,strRole);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
	
		HospitalConnect->CommitTrans();
		AfxMessageBox("当前用户权限分配成功..");
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		HospitalConnect->RollbackTrans();
		return;
	}
	
		
}
