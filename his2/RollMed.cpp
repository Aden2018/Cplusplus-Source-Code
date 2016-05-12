// RollMed.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "RollMed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRollMed dialog


CRollMed::CRollMed(CWnd* pParent /*=NULL*/)
	: CDialog(CRollMed::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRollMed)
	//}}AFX_DATA_INIT
}


void CRollMed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRollMed)
	DDX_Control(pDX, IDC_LIST_ROLLMED, c_listroll);
	DDX_Control(pDX, IDC_LIST_MED, c_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRollMed, CDialog)
	//{{AFX_MSG_MAP(CRollMed)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRollMed message handlers

BOOL CRollMed::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_SICK)->SetWindowText(str2[1]);
	GetDlgItem(IDC_STATIC_DATE)->SetWindowText(str2[4]);
	GetDlgItem(IDC_STATIC_TYPE)->SetWindowText(str2[3]);
/*	roll.str2[1]=m_grid.GetTextMatrix(curRow,3);//姓名
	roll.str2[2]=m_grid.GetTextMatrix(curRow,2); //编码
	roll.str2[3]=m_grid.GetTextMatrix(curRow,8);//挂号类型
	roll.str2[4]=m_grid.GetTextMatrix(curRow,1);//日期
	roll.str2[5]=m_grid.GetTextMatrix(curRow,0);//单据号	
*/
	c_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	c_listroll.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
//			{"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
//		"产地BM","产地","库存量","售价","进价","指导价","取药数"}; //共14列
	int i=0,y=0;
	CString str1[]={"ID","药品编码","药品名","规格","单位","有效期",\
		"产地","进价","售价","购买量","国家指导价"};

	int width[]={0,0,100,90,40,100,80,0,80,80,0};
	while(i<sizeof(str1)/sizeof(CString))
	{
		c_list.InsertColumn(i,str1[i],LVCFMT_LEFT,width[i]);
		c_listroll.InsertColumn(i,str1[i],LVCFMT_LEFT,width[i]);
		
		i++;
	}
	

	CString strSql,s1,s2;
	try{
		strSql.Format("SELECT ID,BM,MC,GG,DW,RQ2,FACTORY,SL,PDJ,NVL(SELLDJ,' ') as selldj,NVL(a.DJ,' ') as DJ FROM \
			ITEMTI a,MEDCODE b WHERE  a.YPBM=b.BM AND a.DANJUHAO='%s' ",str2[5]);
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
	//	AfxMessageBox(strSql);
		i=0;
		while( !recSet->adoEOF )
		{
			AfxMessageBox("trace 1 OK>>>");
			c_list.InsertItem(i," ");
			y=0;
			c_list.SetItemText(i,y++,(char*)_bstr_t(recSet->GetCollect("ID")));
			c_list.SetItemText(i,y++,(char*)_bstr_t(recSet->GetCollect("BM")));
			c_list.SetItemText(i,y++,(char*)_bstr_t(recSet->GetCollect("MC")));
			c_list.SetItemText(i,y++,(char*)_bstr_t(recSet->GetCollect("GG")));
		/*	c_list.SetItemText(i,y++,(char*)_bstr_t(recSet->GetCollect("DW")));
			c_list.SetItemText(i,y++,(char*)_bstr_t(recSet->GetCollect("RQ2")));
			c_list.SetItemText(i,y++,(char*)_bstr_t(recSet->GetCollect("Factory")));
			c_list.SetItemText(i,y++,(char*)_bstr_t(recSet->GetCollect("pdj")));
			c_list.SetItemText(i,y++,(char*)_bstr_t(recSet->GetCollect("dj")));
			c_list.SetItemText(i,y++,(char*)_bstr_t(recSet->GetCollect("SL")));
			c_list.SetItemText(i,y++,(char*)_bstr_t(recSet->GetCollect("SELLDJ")));
		*/	i++;
			recSet->MoveNext();
		}
		recSet->Close();	


	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox(strSql);
		return false;
	}

	
	return TRUE;  

}

HBRUSH CRollMed::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->m_hWnd ==GetDlgItem(IDC_STATIC_SICK)->m_hWnd || \
		pWnd->m_hWnd == GetDlgItem(IDC_STATIC_DATE)->m_hWnd || \
		pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TYPE)->m_hWnd )
		pDC->SetTextColor(RGB(255,0,0));
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CRollMed::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}



BOOL CRollMed::PreTranslateMessage(MSG* pMsg) 
{
/*	CString strTemp;
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN 
		&& GetFocus()->m_hWnd == c_rollSL.m_hWnd ) {
		c_rollSL.GetWindowText(strTemp);
		if( atof(strTemp) > oldSL){
			c_rollSL.SetWindowText("");
			AfxMessageBox("请重新输入,退药数量不能大于已购药数量...");
			c_rollSL.SetFocus();
			return true;
		}else
		{
			UINT nIndex;
			nIndex=c_list.GetNextItem(-1,LVNI_SELECTED);
			if(nIndex== -1 ) {
				AfxMessageBox("请先选择。。。");
				return true;
			}




		}

	}
*/
	return CDialog::PreTranslateMessage(pMsg);
}
