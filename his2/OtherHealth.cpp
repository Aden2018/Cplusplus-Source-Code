// OtherHealth.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "OtherHealth.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COtherHealth dialog


COtherHealth::COtherHealth(CWnd* pParent /*=NULL*/)
	: CDialog(COtherHealth::IDD, pParent)
{
	//{{AFX_DATA_INIT(COtherHealth)
	m_date = COleDateTime::GetCurrentTime();
	m_xueYa = _T("");
	m_tiZong = _T("");
	m_high = _T("");
	m_story = _T("");
	m_leiKe = _T("");
	m_weKe = _T("");
	m_eye = _T("");
	m_women = _T("");
	m_1 = _T("");
	m_2 = _T("");
	m_3 = _T("");
	m_4 = _T("");
	m_5 = _T("");
	m_6 = _T("");
	m_7 = _T("");
	m_8 = _T("");
	m_9 = _T("");
	m_10 = _T("");
	m_11 = _T("");
	m_12 = _T("");
	m_xinDian = _T("");
	m_B = _T("");
	m_X = _T("");
	m_result = _T("");
	m_suggest = _T("");
	m_comment = _T("");
	m_strEdit0 = _T("");
	m_strEdit1 = _T("");
	m_strEdit2 = _T("");
	m_strName = _T("");
	m_strAge = _T("");
	m_strAddress = _T("");
	m_strPhone = _T("");
	//}}AFX_DATA_INIT

	brushEdit.CreateSolidBrush(RGB(0,0,0));
	backColor=RGB(58,110,165);
	brushDialog.CreateSolidBrush(backColor);

	penRect.CreatePen(PS_COSMETIC,1,RGB(0,255,255));
	pen2.CreatePen(PS_SOLID,2,RGB(255,255,128));
	fontEdit.CreatePointFont(140,"宋体");
	font2.CreatePointFont(120,"宋体");

//	ps[0]=IDC_EDIT1;
	ps[1]=IDC_EDIT2;
	ps[2]=IDC_EDIT3;
	ps[3]=IDC_EDIT4;
	ps[4]=IDC_EDIT5;
	ps[5]=IDC_EDIT6;
	ps[6]=IDC_EDIT7;
	ps[7]=IDC_EDIT8;
	ps[8]=IDC_EDIT9;
	ps[9]=IDC_EDIT10;
	ps[10]=IDC_EDIT11;
	ps[11]=IDC_EDIT12;

	ps[12]=IDC_EDIT13;
	ps[13]=IDC_EDIT14;
	ps[14]=IDC_EDIT15;
	ps[15]=IDC_EDIT16;
	ps[16]=IDC_EDIT17;
	ps[17]=IDC_EDIT18;
	ps[18]=IDC_EDIT19;
	ps[19]=IDC_EDIT20;
	ps[20]=IDC_EDIT21;
	ps[21]=IDC_EDIT22;
	ps[22]=IDC_EDIT23;
	ps[23]=IDC_EDIT24;
	ps[24]=IDC_EDIT25;
	ps[25]=IDC_STATIC_TITLE;//IDC_EDIT27;
	ps[26]=IDC_EDIT27;

	ps[27]=IDC_EDIT27;

	ps[28]=IDC_EDIT27;

	ps[29]=IDC_EDIT27;

	ps[30]=IDC_EDIT27;

	ps[31]=IDC_EDIT27;


	ps[32]=IDC_EDIT31;
	ps[33]=IDC_EDIT32;
	ps[34]=IDC_EDIT33;

	ps[35]=IDC_EDIT26; //备注栏,原先被隐藏掉,现再启有
}


void COtherHealth::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(COtherHealth)
	DDX_Control(pDX, IDC_COMBO8, c_sex);
	DDX_Control(pDX, IDOK, m_x4);
	DDX_Control(pDX, IDCANCEL, m_x3);
	DDX_Control(pDX, IDSEARCH, m_x2);
	DDX_Control(pDX, IDC_COMBO7, m_cab);
	DDX_Control(pDX, IDC_COMBO6, m_eab);
	DDX_Control(pDX, IDC_COMBO5, m_sab);
	DDX_Control(pDX, IDC_COMBO4, m_cag);
	DDX_Control(pDX, IDC_COMBO3, m_eag);
	DDX_Control(pDX, IDC_COMBO2, m_sag);
	DDX_Control(pDX, IDC_COMBO1, c_xuexin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_Text(pDX, IDC_EDIT7, m_xueYa);
	DDX_Text(pDX, IDC_EDIT8, m_tiZong);
	DDX_Text(pDX, IDC_EDIT9, m_high);
	DDX_Text(pDX, IDC_EDIT2, m_story);
	DDX_Text(pDX, IDC_EDIT3, m_leiKe);
	DDX_Text(pDX, IDC_EDIT4, m_weKe);
	DDX_Text(pDX, IDC_EDIT5, m_eye);
	DDX_Text(pDX, IDC_EDIT6, m_women);
	DDX_Text(pDX, IDC_EDIT10, m_1);
	DDX_Text(pDX, IDC_EDIT11, m_2);
	DDX_Text(pDX, IDC_EDIT12, m_3);
	DDX_Text(pDX, IDC_EDIT13, m_4);
	DDX_Text(pDX, IDC_EDIT14, m_5);
	DDX_Text(pDX, IDC_EDIT15, m_6);
	DDX_Text(pDX, IDC_EDIT16, m_7);
	DDX_Text(pDX, IDC_EDIT17, m_8);
	DDX_Text(pDX, IDC_EDIT18, m_9);
	DDX_Text(pDX, IDC_EDIT19, m_10);
	DDX_Text(pDX, IDC_EDIT20, m_11);
	DDX_Text(pDX, IDC_EDIT21, m_12);
	DDX_Text(pDX, IDC_EDIT27, m_xinDian);
	DDX_Text(pDX, IDC_EDIT22, m_B);
	DDX_Text(pDX, IDC_EDIT23, m_X);
	DDX_Text(pDX, IDC_EDIT24, m_result);
	DDX_Text(pDX, IDC_EDIT25, m_suggest);
	DDX_Text(pDX, IDC_EDIT26, m_comment);
	DDX_Text(pDX, IDC_EDIT31, m_strEdit0);
	DDX_Text(pDX, IDC_EDIT32, m_strEdit1);
	DDX_Text(pDX, IDC_EDIT33, m_strEdit2);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT43, m_strAge);
	DDX_Text(pDX, IDC_EDIT44, m_strAddress);
	DDX_Text(pDX, IDC_EDIT45, m_strPhone);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(COtherHealth, CDialog)
	//{{AFX_MSG_MAP(COtherHealth)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDSEARCH, OnSearch)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COtherHealth message handlers

void COtherHealth::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	
	CPen *pold=dc.SelectObject(&penRect);

	dc.SetTextColor(RGB(255,255,255));
	RECT r1;
	int i=1; //第一个不算在内
	while(i<36){
		GetDlgItem(ps[i])->GetWindowRect(&r1);
		ScreenToClient(&r1);
		r1.left--;
	//	r1.top--;
		r1.right++;
		r1.bottom++;
	//	dc.Rectangle(&r1);
	//	dc.FrameRect(&r1,&brushEdit);
		if(i==25){
			dc.SelectObject(&pen2);
			dc.MoveTo(r1.left,r1.bottom);
			dc.LineTo(r1.right,r1.bottom);
			dc.SelectObject(&penRect);
		}
		else{
			dc.MoveTo(r1.left,r1.bottom);
			dc.LineTo(r1.right,r1.bottom);
		}
		i++;
		
	}
	dc.SelectObject(pold);	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

HBRUSH COtherHealth::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
/*
	if(pWnd->m_hWnd==GetDlgItem(IDC_STATIC_XM)->m_hWnd ||pWnd->m_hWnd==GetDlgItem(IDC_STATIC_XB)->m_hWnd \
		||pWnd->m_hWnd==GetDlgItem(IDC_STATIC_BM)->m_hWnd||pWnd->m_hWnd==GetDlgItem(IDC_STATIC_BZ)->m_hWnd \
		|| pWnd->m_hWnd == GetDlgItem(IDC_STATIC_AGE)->m_hWnd )
	{
		pDC->SetTextColor(RGB(0,255,0));
//		pDC->SelectObject(&fontEdit);
		pDC->SetBkMode(TRANSPARENT);

	}
 */ if(nCtlColor==CTLCOLOR_EDIT ){
//		pDC->SelectObject(&fontEdit);
		pDC->SetTextColor(RGB(255,255,0));


	}
	else{
		
		pDC->SetTextColor(RGB(255,255,255));
	
		
	}
	pDC->SetBkColor(RGB(58,110,165));
	return (HBRUSH) brushDialog.GetSafeHandle();
	
}

BOOL COtherHealth::OnInitDialog() 
{
	CDialog::OnInitDialog();

	fontTitle.CreatePointFont(220,"宋体");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("其它人员体检信息录入");
//肝功能六项
	m_cab.SetCurSel(0);
	m_cag.SetCurSel(0);
	m_eab.SetCurSel(0);
	m_eag.SetCurSel(0);
	m_sab.SetCurSel(0);
	m_sag.SetCurSel(0);
//性别	
	c_sex.SetCurSel(0);

	m_x2.backColor2=m_x3.backColor2=m_x4.backColor2=backColor;

	CenterWindow();
//	AnimateWindow(m_hWnd,500,AW_SLIDE|AW_CENTER);

//	Invalidate();
	return TRUE;  // return TRUE un	             
}

BOOL COtherHealth::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){
		
		GetNextDlgTabItem(GetFocus())->SetFocus();
		((CEdit*)GetFocus())->SetSel(0,((CEdit*)GetFocus())->LineLength(-1));
	
	return true;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void COtherHealth::OnOK() 
{
	UpdateData();
	if(m_strName.IsEmpty()){
		AfxMessageBox("请输入要登记人员的姓名...");
		return;
	}
	CString str[7];
	m_tiZong.Remove('\'');
	m_high.Remove('\'');
	m_story.Remove('\'');
	m_leiKe.Remove('\'');
	m_weKe.Remove('\'');
	m_eye.Remove('\'');
	m_women.Remove('\'');

	m_1.Format("%.2f",atof(m_1));  
	m_2.Format("%.2f",atof(m_2));
	m_3.Format("%.2f",atof(m_3));
	m_4.Format("%.2f",atof(m_4));
	m_5.Format("%.2f",atof(m_5));
	m_6.Format("%.2f",atof(m_6));
	m_7.Format("%.2f",atof(m_7));
	m_8.Format("%.2f",atof(m_8));
	m_9.Format("%.2f",atof(m_9));
	m_10.Format("%.2f",atof(m_10)); //原餐后血糖,现用作尿酸
	m_11.Format("%.2f",atof(m_11));
	m_12.Format("%.2f",atof(m_12));
	
	m_strEdit0.Format("%.2f",atof(m_strEdit0));
	m_strEdit1.Format("%.2f",atof(m_strEdit1));
	m_strEdit2.Format("%.2f",atof(m_strEdit2));

	m_xinDian.Remove('\'');
	m_B.Remove('\'');
	m_X.Remove('\'');
	m_result.Remove('\'');
	m_suggest.Remove('\'');
	m_comment.Remove('\'');
	
	c_xuexin.GetLBText(c_xuexin.GetCurSel(),str[0]);
	m_cab.GetLBText(m_cab.GetCurSel(),str[1]);
	m_cag.GetLBText(m_cag.GetCurSel(),str[2]);
	m_eab.GetLBText(m_eab.GetCurSel(),str[3]);
	m_eag.GetLBText(m_eag.GetCurSel(),str[4]);
	m_sab.GetLBText(m_sab.GetCurSel(),str[5]);
	m_sag.GetLBText(m_sag.GetCurSel(),str[6]);

	//数据库中顺序为:sag,eag,cag,sab,eab,cab
	for(int i=1;i<7;i++)
	{
		str[i]=str[i].Mid(6,2);
	}


	CString strSql,strSex;
	c_sex.GetLBText(c_sex.GetCurSel(),strSex);

	try{
//		strSql.Format("insert into tijian(kahao,riqi,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,\
			a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,a31,a32) values('%s',\
			to_date('%s','yyyymmdd'),'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s',\
			'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s') ",\
			strKH,m_date.Format("%Y%m%d"),str[0],m_xueYa,m_tiZong,m_high,m_story,m_leiKe,m_weKe,m_eye,\
			m_women,m_1,m_2,m_3,m_4,m_5,m_6,m_7,m_8,m_9,m_10,m_11,m_12,str[6],str[4],str[2],str[5],str[3],\
			str[1],m_xinDian,m_X,m_B,m_result,m_suggest);
		strSql.Format("insert into other_tijian(rec_xm,rec_xb,rec_age,rec_addr,rec_phone,riqi,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,\
			a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,a31,a32,tsgf,afp,cea,ls,rec_comm) values('%s','%s','%s','%s','%s',\
			to_date('%s','yyyymmdd'),'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s',\
			'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s') ",\
			m_strName,strSex,m_strAge,m_strAddress,m_strPhone,m_date.Format("%Y%m%d"),str[0],m_xueYa,m_tiZong,m_high,m_story,m_leiKe,m_weKe,m_eye,\
			m_women,m_1,m_2,m_3,m_4,m_5,m_6,m_7,m_8,m_9,m_10,m_11,m_12,str[6],str[4],str[2],str[5],str[3],\
			str[1],m_xinDian,m_X,m_B,m_result,m_suggest,m_strEdit0,m_strEdit1,m_strEdit2,m_10,m_comment);

		HospitalConnect->BeginTrans();

		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		HospitalConnect->CommitTrans();
	}
	catch(_com_error e)
	{
		AfxMessageBox("信息未能正常加入...");
		HospitalConnect->RollbackTrans();
		return;
	}
	
	AfxMessageBox("人员信息成功加入库中....");

	m_xueYa = _T("");
	m_tiZong = _T("");
	m_high = _T("");
	m_story = _T("");
	m_leiKe = _T("");
	m_weKe = _T("");
	m_eye = _T("");
	m_women = _T("");
	m_1 = _T("");
	m_2 = _T("");
	m_3 = _T("");
	m_4 = _T("");
	m_5 = _T("");
	m_6 = _T("");
	m_7 = _T("");
	m_8 = _T("");
	m_9 = _T("");
	m_10 = _T("");
	m_11 = _T("");
	m_12 = _T("");
	m_xinDian = _T("");
	m_B = _T("");
	m_X = _T("");
	m_result = _T("");
	m_suggest = _T("");
	m_comment = _T("");
	m_strName=_T("");
	m_strAge=_T("");
	m_strAddress=_T("");
	m_strPhone=_T("");

	UpdateData(false);
	GetDlgItem(IDC_EDIT1)->SetFocus();
	c_sex.SetCurSel(0);
	GetDlgItem(IDC_EDIT31)->SetWindowText("");
	GetDlgItem(IDC_EDIT32)->SetWindowText("");
	GetDlgItem(IDC_EDIT33)->SetWindowText("");

}

void COtherHealth::OnSearch() 
{
	
}

void COtherHealth::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	GetDlgItem(IDC_EDIT1)->SetFocus();	
}
