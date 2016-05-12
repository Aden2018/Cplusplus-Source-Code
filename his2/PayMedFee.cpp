// PayMedFee.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "PayMedFee.h"
#include "huajia.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPayMedFee dialog


CPayMedFee::CPayMedFee(CWnd* pParent /*=NULL*/)
	: CDialog(CPayMedFee::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPayMedFee)
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"����");

}


void CPayMedFee::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPayMedFee)
	DDX_Control(pDX, ID_BUTTON_PRINT, m_34);
	DDX_Control(pDX, IDC_EDIT_PAY2, m_pay2);
	DDX_Control(pDX, IDC_EDIT_MED, m_med);
	DDX_Control(pDX, IDC_EDIT_ZL, m_zl);
	DDX_Control(pDX, IDCANCEL, m_3);
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, IDC_EDIT_SHOULD_PAY, m_should_pay);
	DDX_Control(pDX, IDC_EDIT_SCALE, m_scale);
	DDX_Control(pDX, IDC_EDIT_REAL_PAY, m_real_pay);
	DDX_Control(pDX, IDC_EDIT_PAY, m_pay);
	DDX_Control(pDX, IDC_EDIT_MORE_PAY, m_more_pay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPayMedFee, CDialog)
	//{{AFX_MSG_MAP(CPayMedFee)
	ON_EN_CHANGE(IDC_EDIT_PAY, OnChangeEditPay)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
/*
const char EMPLOYEE[]="���䱣��";
const char GENERIC[]="������";
const char RELATE[]="��������";
const char NOWORK[]="������Ա";
const char IC[]="��������";

const char GAOQIAN[]="��ǰְ��";
const char GANGSHANG[]="������Ա";
const char TUIYANG[]="������Ա";

*/
// CPayMedFee message handlers
const char R1[]="��������";
const char RR[]="���䱣��";
const char TUIYANG[]="������Ա";

void CPayMedFee::OnOK() 
{
	CString strSql,s1;
	float fMed(0),fZl(0),fPro(0),fMZ,fgetPrice(0);//ҩƷ��,���Ʒ�,����,�ܷ���
	
	m_med.GetWindowText(s1);
	fMed=atof(s1);

	fgetPrice=atof(str[3]);
	fgetPrice=fMed-fgetPrice;

	m_zl.GetWindowText(s1);
	fZl=atof(s1);

	m_real_pay.GetWindowText(s1);
	fMZ=atof(s1);
/*
	if(fMZ != fMed+fZl){
		AfxMessageBox("��ʾ: ��һ���������...");
		fMZ= fMed+fZl;
	}
*/	

	try{ 
		HospitalConnect->BeginTrans();
		if(p->str2[3] == R1 || p->str2[3] == RR ){
		
			if(p->str2[3] == R1 ){ //��������
				strSql.Format("UPDATE codeqingshu SET YUER= YUER-(%.2f) WHERE BM='%s' ",fMZ,p->str2[2] );
			}
			else if( p->str2[3] == RR ){ //ְ������
				strSql.Format("UPDATE ְ����������� SET �����=�����-(%.2f) WHERE ����='%s' ",fMZ,p->str2[2] );
			}
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			
			strSql.Format("UPDATE ItemRegisterTou SET MEDMONEY=%.2f,TREATEMONEY=%.2f,�շ�Ա='%s',\
				�շ�Ա��='%s',PROFIT=%.2f WHERE DANJUHAO='%s' ",fMed,fZl,LoginInformation.user_code,\
				LoginInformation.user ,fgetPrice,p->str2[5] );
		
		}
		else {

			strSql.Format("UPDATE ItemRegisterTou SET MEDMONEY=%.2f,TREATEMONEY=%.2f,�շ�Ա='%s',\
				�շ�Ա��='%s',PROFIT=%.2f,CASH=%.2f WHERE DANJUHAO='%s' ",fMed,fZl,LoginInformation.user_code,\
				LoginInformation.user ,fgetPrice,fMZ,p->str2[5] );


		}
	
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		HospitalConnect->CommitTrans();
		

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
	//	recSet->Close();
		HospitalConnect->RollbackTrans();
		return;
	}

//	GetDlgItem(IDOK)->EnableWindow(false);
	CDialog::OnOK();

}
BOOL CPayMedFee::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_TITLE2)->SetFont(&fontTitle);	
	m_med.SetWindowText(str[0]); //ҩƷ��
	m_zl.SetWindowText(str[1]);//���Ʒ�
	m_should_pay.SetWindowText(str[2]); //Ӧ������

	p=(CHuaJia *)theApp.pParentGrid.p3; // p2 already used
	CString str1;
//	str1.Format("%d%%",p->scale);
//	if(p->scale != 0 ) m_scale.SetWindowText(str1);
	m_scale.SetWindowText("100%");
	m_should_pay.GetWindowText(str1);
	m_real_pay.SetWindowText(str1);

	float fee;
	if(p->str2[3] == R1 || p->str2[3]== RR ){
		
		GetDlgItem(IDC_STATIC_1)->SetWindowText("����");
		GetDlgItem(IDC_STATIC_2)->SetWindowText("���");
		m_pay.SetReadOnly();
		m_pay.SetWindowText(p->str2[1]); //��������
		str1.Format("%.2f",p->balance);//���
		m_pay2.SetWindowText(str1);
		GetDlgItem(IDC_STATIC_3)->SetWindowText("����");
		m_real_pay.GetWindowText(str1);
		fee=atof(str1);
		str1.Format("%.2f",p->balance-fee);
		m_more_pay.SetWindowText(str1);

	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPayMedFee::OnChangeEditPay() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString str1,str2,str3;
	m_pay.GetWindowText(str1);
	float f1=atof(str1),f2; //ʵ�ʸ���
	str1.Format("%.2f",f1);
	m_pay2.SetWindowText(str1);
	m_real_pay.GetWindowText(str2); //ʵ��Ӧ��

/*	
	if(p->scale != 0 ){
		f2=atof(str2);
		str2.Format("%.2f",f2*p->scale/100.0 );

	}
*/
	
	str1.Format("%.2f",f1-atof(str2));

	m_more_pay.SetWindowText(str1);


	


	


}

HBRUSH CPayMedFee::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->m_hWnd == m_real_pay.m_hWnd || pWnd->m_hWnd == m_more_pay.m_hWnd ||
		 pWnd->m_hWnd == m_pay2.m_hWnd || pWnd->m_hWnd == m_pay.m_hWnd )
		pDC->SetTextColor(RGB(255,0,0)); 
	if(pWnd->m_hWnd == m_scale.m_hWnd )
		pDC->SetTextColor(RGB(0,0,255));

	
	return hbr;
}
