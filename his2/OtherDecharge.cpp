// OtherDecharge.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "OtherDecharge.h"
#include "huaJia.h"
#include "OperatChargeRelateFee.h"
#include "OtherDechargeQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COtherDecharge dialog


COtherDecharge::COtherDecharge(CWnd* pParent /*=NULL*/)
	: CDialog(COtherDecharge::IDD, pParent)
{
	//{{AFX_DATA_INIT(COtherDecharge)
	m_date1 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	strTag.Format("AAA");
	CString strSql;
	strSql.Format("SELECT ds2 FROM LSQ_GH_TYPE WHERE ds1='%s' ",strTag );
	strTitle=GetStringTitle(strSql);

	fontTitle.CreatePointFont(200,"黑体");
	PRINTflag=0;
}


void COtherDecharge::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COtherDecharge)
	DDX_Control(pDX, IDPRINT_SEARCH, m_ps);
	DDX_Control(pDX, IDC_EDIT_SCALE1, c_scale);
	DDX_Control(pDX, IDC_EDIT10, c10);
	DDX_Control(pDX, IDC_EDIT9, c9);
	DDX_Control(pDX, IDC_EDIT8, c8);
	DDX_Control(pDX, IDC_EDIT7, c7);
	DDX_Control(pDX, IDC_EDIT6, c6);
	DDX_Control(pDX, IDC_EDIT5, c5);
	DDX_Control(pDX, IDC_EDIT4, c4);
	DDX_Control(pDX, IDC_EDIT3, c3);
	DDX_Control(pDX, IDC_EDIT2, c2);
	DDX_Control(pDX, IDC_EDIT1, c1);
	DDX_Control(pDX, IDC_BUTTON_A, m_a);
	DDX_Control(pDX, IDC_COMBO1, c_type);
	DDX_Control(pDX, IDCANCEL, m_c);
	DDX_Control(pDX, IDOK, m_o);
	DDX_Control(pDX, IDPRINT, m_p);
	DDX_Control(pDX, IDC_RICHTEXTCTRL1, c11);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COtherDecharge, CDialog)
	//{{AFX_MSG_MAP(COtherDecharge)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_EDITCHANGE(IDC_COMBO1, OnEditchangeCombo1)
	ON_CBN_KILLFOCUS(IDC_COMBO1, OnKillfocusCombo1)
	ON_EN_CHANGE(IDC_EDIT9, OnChangeEdit9)
	ON_EN_SETFOCUS(IDC_EDIT9, OnSetfocusEdit9)
	ON_EN_KILLFOCUS(IDC_EDIT9, OnKillfocusEdit9)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit8)
	ON_BN_CLICKED(IDC_BUTTON_A, OnButtonA)
	ON_BN_CLICKED(IDPRINT, OnPrint)
	ON_BN_CLICKED(IDPRINT_SEARCH, OnSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COtherDecharge message handlers

BOOL COtherDecharge::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	SetWindowText(strTitle);
	
	CString strSql;
	c_type.ResetContent();
	try{
		strSql.Format("select ds3 from LSQ_Economy_Rank ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
		
			strSql=(char*)_bstr_t(recSet->GetCollect("ds3").vt==VT_NULL?" ":recSet->GetCollect("ds3"));
			c_type.AddString(strSql);
			
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

	c_type.SetCurSel(0);
	OnKillfocusCombo1();
	c9.SetWindowText("%"); //比例

	c1.SetWindowText(GetStringTitle("SELECT ds1 FROM  lsq_title_list Where ds2='DIALOG' ANd ds3='NAME' and ds4='AAD' "));
	c2.SetWindowText(GetStringTitle("SELECT ds1 FROM lsq_title_list Where ds2='DIALOG' ANd ds3='NAME' and ds4='AAA' "));
	c3.SetWindowText(GetStringTitle("SELECT ds1 FROM  lsq_title_list Where ds2='DIALOG' ANd ds3='NAME' and ds4='AAB' "));
	c4.SetWindowText(GetStringTitle("SELECT ds1 FROM  lsq_title_list Where ds2='DIALOG' ANd ds3='NAME' and ds4='AAC' "));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void COtherDecharge::OnOK() 
{
	UpdateData();
	CString strTmp,strSel,strSql;
	c_type.GetWindowText(strSel);
	
	if( strSel.IsEmpty() ) {
		AfxMessageBox("请先选择一个项目或输入经济内容");
		return;
	}
	
	if( c_type.FindStringExact(-1,strSel) ==CB_ERR ){ //新增一个经济内容方式
	
		c_type.AddString(strSel);
		strSql.Format("INSERT INTO LSQ_ECONOMY_RANK(n1,ds3,d1) \
			values( (SELECT NVL(max(n1),0)+1 FROM LSQ_ECONOMY_RANK ),'%s',sysdate ) ",strSel );
		if( !WriteSQL(strSql) ) {
			AfxMessageBox("写入数据库失败");
			AfxMessageBox(strSql);
		}

	}
/* 日期, 系统日期,序列号,经济内容,描述,使用人,验收人,经手人,审批人,单据张数,附件张数,总金额,比例,操作人
	select substr(sys_context( 'userenv' , 'ip_address'),
	instr(sys_context( 'userenv' , 'ip_address'),'.',-1,2)+1)  from dual	--生成客户端IP的最后两位
	c1 使用人
	c2 验收人
	c3 经手人
	c4 审批人
	c5 凭证号
	c6 单据数
	c7 附件数
	c8 总金额
	c9 比例
	c10 报销额
	c11 备注
	
	*/
	CString strc[11];
	long i=0;
	c1.GetWindowText(strc[i++] );
	c2.GetWindowText(strc[i++] );
	c3.GetWindowText(strc[i++] );
	c4.GetWindowText(strc[i++] );
	c5.GetWindowText(strc[i++] );
	c6.GetWindowText(strc[i++] );
	c7.GetWindowText(strc[i++] );
	c8.GetWindowText(strc[i++] );
	c9.GetWindowText(strc[i++] );
	c10.GetWindowText(strc[i++] );
	c11.GetWindowText(strc[i++] );

	strSql.Format(" INSERT INTO LSQ_OTHER_DECHARGE ( d1,d2,ds1,ds2,ds3,ds4,ds5,ds6,ds7,n5,n1,n2,n3,n4,ds8,ds9) \
		values(to_date(%s,'yyyymmdd'),sysdate,to_char(sysdate,'yyyymmddhh24miss')||'_'||(select substr(sys_context( 'userenv' , 'ip_address'),\
		instr(sys_context( 'userenv' , 'ip_address'),'.',-1,2)+1)  from dual),'%s','%s',\
		'%s','%s','%s','%s',%ld,%ld,%ld,%.2f,%.4f,'%s','%s' ) ",m_date1.Format("%Y%m%d"),strSel,strc[10],strc[0],strc[1],\
		strc[2],strc[3],atol(strc[4]),atol(strc[5]),atol(strc[6]),atof(strc[7]),atof(strc[8])/100,LoginInformation.user,strTag);
	//		               凭证编码		单据张数	 附件张数			总额	比例
	if(WriteSQL(strSql)){
		ClearDialogInformation();
		AfxMessageBox("填写成功");
		PRINTflag=0;
	}
	else AfxMessageBox(strSql);


		
}

BOOL COtherDecharge::WriteSQL(CString strSql) 
{
	try{

		HospitalConnect->BeginTrans();
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();

	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox(e.Description());
		return false;
	}
	return true;
}

void COtherDecharge::OnSelchangeCombo1() 
{
	
}

void COtherDecharge::OnEditchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	
}

void COtherDecharge::OnKillfocusCombo1() 
{
	CString strSql,strTmp;
	c_type.GetWindowText(strTmp);
	try{
		strSql.Format("select count(*)+1  ds3  from LSQ_Other_DECHARGE where ds2='%s' ",strTmp);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
		
			strSql=(char*)_bstr_t(recSet->GetCollect("ds3").vt==VT_NULL?" ":recSet->GetCollect("ds3"));
			strTmp.Format("%06ld",atol(strSql) );
			c5.SetWindowText(strTmp);
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

void COtherDecharge::OnChangeEdit9() //比例调整
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	OnComputeScale();
	// TODO: Add your control notification handler code here
}

void COtherDecharge::OnSetfocusEdit9()  
{
	CString strTmp;
	c9.GetWindowText(strTmp);
	c9.SetSel(0,strTmp.GetLength()-1);	
}

BOOL COtherDecharge::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN ) pMsg->wParam=VK_TAB;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void COtherDecharge::OnKillfocusEdit9() 
{

}

void COtherDecharge::OnComputeScale() 
{
	CString strTmp,strAmount,strScale;
	
	c8.GetWindowText(strAmount); //总金额
	c9.GetWindowText(strTmp); //比例

	strScale.Format("%.2f%%",atof(strTmp) );
	c_scale.SetWindowText(strScale);

	strScale.Format("%.2f",atof(strTmp)/100*atof(strAmount));
	c10.SetWindowText(strScale);

}

void COtherDecharge::OnChangeEdit8()  //总金额
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	OnComputeScale();
	
	// TODO: Add your control notification handler code here
	
}

void COtherDecharge::ClearDialogInformation()
{
	c1.SetWindowText("");
	c2.SetWindowText("");
	c3.SetWindowText("");
	c4.SetWindowText("");
	c5.SetWindowText("");
	c6.SetWindowText("");
	c7.SetWindowText("");
	c8.SetWindowText("");
	c9.SetWindowText("");
	c10.SetWindowText("");
	c11.SetWindowText("");
	c_scale.SetWindowText("");
	c_type.SetFocus();


}

void COtherDecharge::OnButtonA() 
{
	
}

CString COtherDecharge::GetStringTitle(CString strtag)
{
	CString strout;
	try{
		recSet->Open(_bstr_t(strtag),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
		
			strout=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt == VT_NULL ? "":recSet->GetFields()->GetItem(0L)->Value );
		}
		else strout="";
		recSet->Close();

		return strout;

	}
	catch(_com_error e)
	{
		AfxMessageBox(strtag);
		recSet->Close();
		return "";
	}	

}


extern _Application app ;
extern Workbooks books;
extern _Workbook book;
extern Worksheets sheets;
extern _Worksheet sheet;
extern COleVariant vOpt;
#define _O(x) COleVariant(x)
#define STANDARDFONT  12
#define FONTNAME	"宋体"



void COtherDecharge::OnPrint() //打印操作
{
	UpdateData();

	BeginWaitCursor();

	CString strFileName;
	strFileName.Format("%s",LoginInformation.path);
	strFileName+="chargeprice.xls";


//	if( ! app ){
		app.CreateDispatch("excel.application");
		if(!app){
			AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
			return;
		}
		books=app.GetWorkbooks();
		book=books.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
		sheets=book.GetWorksheets();

//	}
	sheet=sheets.GetItem(COleVariant((short)4)); //sheet4 作为其它人员报销情况
	app.SetVisible(false);

	CString strCell[]={"B3","B4","B5","B6","B7","B8","B9","D3","D4","D5","D6","D7","D8","E4" }; //共13
	//分别为 日期,报销内容,使用人,验收人,经手人,审批人,大写,凭证号,单据数,附件数,总额,比例,实报
	
	CString strData[16],strTemp;
/*	c1 使用人
	c2 验收人
	c3 经手人
	c4 审批人
	c5 凭证号
	c6 单据数
	c7 附件数
	c8 总金额
	c9 比例 c_scale
	c10 报销额
	c11 备注	
*/
	Range vr;
	vr=sheet.GetRange(_O("A17"),_O("A17"));
	strTemp=(char*)_bstr_t( vr.GetValue() );
	strTemp+=strTitle;
	vr=sheet.GetRange(_O("B17"),_O("B17"));
	strTemp+=(char*)_bstr_t(vr.GetValue() );
	vr=sheet.GetRange(_O("A1"),_O("A1"));
	vr.SetValue(_O(strTemp));
	long i=0;

	strData[i++]=m_date1.Format("%Y-%m-%d");
	c_type.GetWindowText(strData[i++]);
	c1.GetWindowText(strData[i++]);
	c2.GetWindowText(strData[i++]);
	c3.GetWindowText(strData[i++]);
	c4.GetWindowText(strData[i++]);
//	大写转换
	c10.GetWindowText(strTemp);
	strData[i++]=CHuaJia::GetBigMoney(	atof(strTemp) );
	
	c5.GetWindowText(strData[i++]);
	c6.GetWindowText(strData[i++]);
	strData[i-1]+="张";
	c7.GetWindowText(strData[i++]);
	strData[i-1]+="张";
	c8.GetWindowText(strData[i++]);
	c_scale.GetWindowText(strData[i++]);
	c10.GetWindowText(strData[i++]);

	strData[i++]=c11.GetText();
	
	for(long z=0 ;z < i ; z++ )
		COperatChargeRelateFee::WriteExcelCell(strCell[z],strData[z]);


	PageSetup pageinfo=sheet.GetPageSetup();
/*	pageinfo.SetLeftMargin(0);
	pageinfo.SetRightMargin(0);
	pageinfo.SetTopMargin(0);
	pageinfo.SetBottomMargin(0);
*/
//	sheet.PrintPreview(_O((short)1));
	sheet.PrintOut(vOpt,vOpt,_O((short)1),vOpt,vOpt,vOpt,vOpt,vOpt);


//	sheet=sheets.GetItem(COleVariant((short)1)); //sheet1 打印收费单情况
	sheet.ReleaseDispatch();

	sheets.ReleaseDispatch();
	book.Close(_O((short)0),vOpt,vOpt); //关闭EXCEL,不保存文件

	book.ReleaseDispatch();
	books.Close();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	app.DetachDispatch();
	app.Quit();

	EndWaitCursor();

	PRINTflag=2;
}

void COtherDecharge::OnSearch() 
{
	COtherDechargeQuery od;
	od.DoModal();
	
}

void COtherDecharge::OnCancel() 
{
	CString strNoti=GetStringTitle("SELECT ds2 FROM LSQ_GH_TYPE WHERE ds1='BAA' AND ds3='B' ");

	if( PRINTflag==2 && AfxMessageBox(strNoti,MB_OKCANCEL)==IDCANCEL) return;

	
	CDialog::OnCancel();
}
