// MedDetail.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "MedDetail.h"
#include "msHflexGrid.h"
#include "codegysQuery.h"
#include "dialoginStorage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedDetail dialog


CMedDetail::CMedDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CMedDetail::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMedDetail)
	m_riqi1 = COleDateTime::GetCurrentTime();
	m_riqi2 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
//	brush2.CreateSolidBrush(RGB(58,110,165));
	FlagRollMED=0;
}


void CMedDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedDetail)
	DDX_Control(pDX, IDC_EDIT_CURRENT_PRICE, CcurrentPrice);
	DDX_Control(pDX, IDC_EDIT11, c_coach);
	DDX_Control(pDX, IDC_EDIT10, c_factory);
	DDX_Control(pDX, IDC_EDIT9, c_out_price);
	DDX_Control(pDX, IDC_EDIT8, c_in_price);
	DDX_Control(pDX, IDC_EDIT7, c_sl);
	DDX_Control(pDX, IDC_EDIT6, c_dw);
	DDX_Control(pDX, IDC_EDIT5, c_gg);
	DDX_Control(pDX, IDC_EDIT4, c_mc);
	DDX_Control(pDX, IDC_EDIT3, c_bm);
	DDX_Control(pDX, IDC_EDIT2, c_xl);
	DDX_Control(pDX, IDC_EDIT1, c_dl);
	DDX_Control(pDX, IDC_BUTTON_GYS, m_x3);
	DDX_Control(pDX, IDCANCEL, m_x2);
	DDX_Control(pDX, IDOK, m_x1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_riqi1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_riqi2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMedDetail, CDialog)
	//{{AFX_MSG_MAP(CMedDetail)
	ON_BN_CLICKED(IDC_BUTTON_GYS, OnButtonGys)
	ON_EN_KILLFOCUS(IDC_EDIT10, OnKillfocusEdit10)
	ON_EN_SETFOCUS(IDC_EDIT10, OnSetfocusEdit10)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedDetail message handlers

BOOL CMedDetail::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	fontTitle.CreatePointFont(220,"宋体");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	long row=((CMSHFlexGrid*)theApp.pParentGrid.pQuery)->GetRow();
	c_dl.SetWindowText(((CMSHFlexGrid*)theApp.pParentGrid.pQuery)->GetTextMatrix(row,0));
	c_xl.SetWindowText(((CMSHFlexGrid*)theApp.pParentGrid.pQuery)->GetTextMatrix(row,1));
	c_bm.SetWindowText(((CMSHFlexGrid*)theApp.pParentGrid.pQuery)->GetTextMatrix(row,2));
	c_mc.SetWindowText(((CMSHFlexGrid*)theApp.pParentGrid.pQuery)->GetTextMatrix(row,3));
	c_gg.SetWindowText(((CMSHFlexGrid*)theApp.pParentGrid.pQuery)->GetTextMatrix(row,4));
	c_dw.SetWindowText(((CMSHFlexGrid*)theApp.pParentGrid.pQuery)->GetTextMatrix(row,5));
	CString strSql,strbm;
	c_bm.GetWindowText(strbm);
//	strSql.Format("select sell_price from medlie a where ypbm='%s' and rownum = 1\
		order by  get_date desc ",strbm );
//* 获取药品最近一次购进价格
	strSql.Format("select  sell_price from (select sell_price from medlie  where ypbm='%s'  order by get_date desc ) where rownum=1 ",strbm);

	try{

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		
		if(!recSet->adoEOF){
					
				strbm=(char*)_bstr_t(recSet->GetCollect("sell_price"));
				CcurrentPrice.SetWindowText(strbm);
	
		}else 
			CcurrentPrice.SetWindowText("未查到");

		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox("没有查询到最后一次药品价格...");
		recSet->Close();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMedDetail::OnOK() 
{
	UpdateData();
	CString str[25],strSql;
	c_sl.GetWindowText(str[0]);
	if(c_factoryID.IsEmpty()){
		AfxMessageBox("请先选择好产地...");
		c_factory.SetFocus();
		return;
	}
	CMSHFlexGrid *pg=(CMSHFlexGrid*)theApp.pParentGrid.pGrid;
	long row=pg->GetRows()-1,j;
	pg->AddItem(" ",_variant_t(row));
	int i=1;

	str[0].Format("%ld",row);
	c_dl.GetWindowText(str[i++]); //1
	c_xl.GetWindowText(str[i++]); //2
	c_bm.GetWindowText(str[i++]); //3
	c_mc.GetWindowText(str[i++]); //4
	c_gg.GetWindowText(str[i++]); //5
	c_dw.GetWindowText(str[i++]); //6
	
	
	c_factory.GetWindowText(str[i++]); //7
	str[i++]=c_factoryID; //8
	
	c_sl.GetWindowText(str[i++]); //9
	str[i-1].Format("%.2f",atof(str[i-1])); 
	c_in_price.GetWindowText(str[i++]); //10
	str[i-1].Format("%.2f",atof(str[i-1])); 
	c_out_price.GetWindowText(str[i++]); //11
	str[i-1].Format("%.2f",atof(str[i-1]));
	str[i++]=m_riqi2.Format("%Y/%m/%d");  //12 
	str[i++]=m_riqi1.Format("%Y/%m/%d"); //13
	c_coach.GetWindowText(str[i++]);  //14
	str[i-1].Format("%.2f",atof(str[i-1])/1.15);

	if( FlagRollMED != 8888){ //正常入库
		
		((CDialogInStorage*)theApp.pDialog)->c_paoju.GetWindowText(str[i++]);
		((CDialogInStorage*)theApp.pDialog)->c_gys.GetWindowText(str[i++]);
		str[i++]=((CDialogInStorage*)theApp.pDialog)->c_gysID;

		((CDialogInStorage*)theApp.pDialog)->c_ywy.GetWindowText(str[i++]);
		str[i++]=((CDialogInStorage*)theApp.pDialog)->c_ywyID;

		for(j=0;j<i;j++)
			pg->SetTextMatrix(row,j,str[j]);
	}
	else { //是否要生成一个新的 ID 编码 

		try{
			HospitalConnect->BeginTrans();

			strSql.Format("select * from medlie where kfbm='%s' and sl=0 ",LoginInformation.kfbm);
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){
				str[2]/*药品ID*/=(char*)_bstr_t(recSet->GetCollect("ID"));
				
			}
			else {
				recSet->Close();
				strSql.Format("select max(ID)+1 newID from medlie ");
				recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
				str[2]=(char*)_bstr_t(recSet->GetCollect("newID"));
			}
			recSet->Close();
			
			strSql.Format("delete from  medlie where id=%s ",str[2]);
			
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			c_bm.GetWindowText(str[3]);
		
			strSql.Format("insert into medlie (id,kfbm,ypbm,factorycode,rq1,rq2,sl,\
				jinjia,sell_price,coach_price) \
				values(%s,'%s','%s','%s',to_date('%s','yyyymmdd'),to_date('%s','yyyymmdd'),0,%.2f,\
				%.2f,%.2f  ) ",str[2],LoginInformation.kfbm,str[3],c_factoryID,m_riqi1.Format("%Y%m%d"),m_riqi2.Format("%Y%m%d"),\
				atof(str[10]),atof(str[11]),atof(str[14])); //数量留待下面来数
			
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			
			
			
		
		
			HospitalConnect->CommitTrans();
		
		}
		catch(_com_error e)
		{
			HospitalConnect->RollbackTrans();
			AfxMessageBox(strSql);
			AfxMessageBox("退药失败,请重启应用程序然后重新操作一次...");
			return;
			
			
		}		
		str[0]=str[2]; // ID
		i=1;
		c_bm.GetWindowText(str[i++]);
		c_mc.GetWindowText(str[i++]);
		c_gg.GetWindowText(str[i++]);
		c_dw.GetWindowText(str[i++]);
		
		str[i++]=m_riqi1.Format("%Y/%m/%d");
		str[i++]=m_riqi2.Format("%Y/%m/%d");
		str[i++]=c_factoryID;
	
		c_factory.GetWindowText(str[i++]);
		
		str[i++]="0";
	
		c_out_price.GetWindowText(str[i++]);
		str[i-1].Format("%.2f",atof(str[i-1]));

		c_in_price.GetWindowText(str[i++]);
		str[i-1].Format("%.2f",atof(str[i-1]));
		
		
		c_coach.GetWindowText(str[i++]);
		str[i-1].Format("%.2f",atof(str[i-1])/1.15);
		
		c_sl.GetWindowText(str[i++]);
		str[i-1].Format("%.2f",0. );//atof(str[i-1]));
	
		for(j=0;j<i;j++)
			pg->SetTextMatrix(row,j,str[j]);
		
		
		
	}
	CDialog::OnOK();


}

void CMedDetail::OnButtonGys() 
{
	CCodeGysQuery gys;
	if(gys.DoModal()==IDOK){
		c_factory.SetWindowText(gys.strName);
		c_factoryID=gys.strNum;

	}
}

BOOL CMedDetail::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){
		if(GetFocus()->m_hWnd==GetDlgItem(IDOK)->m_hWnd){
			return CDialog::PreTranslateMessage(pMsg);
		}
	
		GetNextDlgTabItem(GetFocus())->SetFocus();
		((CEdit*)GetFocus())->SetSel(0,((CEdit*)GetFocus())->LineLength(-1));
	
		return true;
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

void CMedDetail::OnKillfocusEdit10() //用户编码填写出
{
	CString strSql,str1;
	c_factory.GetWindowText(str1);
	try{
		strSql.Format("select * from CODEGYS where GONGBM='%s' ",str1);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			c_factoryID=str1;
			strSql=(char*)_bstr_t(recSet->GetCollect("GONGMC").vt==VT_NULL?" ":recSet->GetCollect("GONGMC"));
			c_factory.SetWindowText(strSql);
		}
		else {
			c_factoryID="";
			c_factory.SetWindowText("");
		//	c_factory.SetFocus();

		}
		recSet->Close();


	}
	catch(_com_error e)
	{
		AfxMessageBox("输入有误,请重新进行正确输入...");
		recSet->Close();
		return;
	}

	



}

void CMedDetail::OnSetfocusEdit10() 
{
	c_factory.SetWindowText(c_factoryID);	
}

HBRUSH CMedDetail::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return theApp.titleBrush;


	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
