// CommonUse.cpp: implementation of the CCommonUse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "CommonUse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommonUse::CCommonUse()
{

}

CCommonUse::~CCommonUse()
{

}

BOOL CCommonUse::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	CString strSql;
	try{
		
		strSql.Format("select distinct to_char(sysdate,'yyyymmddhh24miss') da from dual" );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t (recSet->GetCollect("da"));
			m_zktou='E';
			m_zktou+=strSql+LoginInformation.user_code;
			
		}
		recSet->Close();
		c_danjuhao.SetWindowText(m_zktou);
		m_curKf.SetWindowText(LoginInformation.kfmc);


	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return false;
	}		

	CRect r1(0,0,0,0);
	editCtrl.Create(WS_CHILD,r1,this,T_EDIT_YPZK);

	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"ID","ҩƷ����","ҩƷ����","���","��λ","������","��Ч��",\
		"����BM","����","�����","�ۼ�","����","ָ����","ȡҩ��"}; //��14��
	long  headWidth[]={0,00,2000,1600,600,0,1400,0,1600,1000,000,0,0,1200};


	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	
//	SetWindowLong(c_getKf.m_hWnd,GWL_STYLE,GetWindowLong(c_getKf.m_hWnd,GWL_STYLE) | CBS_SIMPLE     );
	SetWindowText("�ڲ����Ĳ���");
	CRect rt1;
	c_getKf.GetWindowRect(rt1);
	ScreenToClient(rt1);
	c_use.MoveWindow(rt1);
	c_use.ShowWindow(SW_SHOW);
	c_getKf.ShowWindow(SW_HIDE);
	c_use.SetCurSel(0);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("�ڲ����Ĳ���");
	GetDlgItem(IDC_STATIC1)->SetWindowText("��  ;");

	return true;
}

void CCommonUse::OnOK()
{
	UpdateData();
	CString strSql,danjuhao,ywy,str[20],strt1;

	c_getRymc.GetWindowText(ywy);
	c_danjuhao.GetWindowText(danjuhao);

	c_use.GetWindowText(strt1); //�ڲ�������;

	if( strt1.IsEmpty() || ywy.IsEmpty() ){
		AfxMessageBox("�뽫������Ŀ��д�����ٽ��в���...");
		return;
	}

	long rows=m_grid.GetRows()-2; //�õ�ҩƷ����
	if( 0 == rows)return;
/*	CString HeadTitle[]={"ID","ҩƷ����","ҩƷ����","���","��λ","������","��Ч��",\
																	5		  6
	  "����BM","����","�����","�ۼ�","����","ָ����","ȡҩ��"}; //��14��
						9        10              12      13
*/
	try{
		HospitalConnect->BeginTrans();

		strSql.Format("insert into ItemCK1Tou (danjuhao,riqi,����Ա,����Ա��,\
			����Ա,����Ա��,��; ) values('%s',TRUNC(SYSDATE,'dd'),'%s','%s',\
			'%s','%s','%s' ) ",danjuhao,c_getRymcID,ywy,LoginInformation.user_code,LoginInformation.user,strt1);
	
	
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		for(long i=0;i<rows;i++){
			str[0]=m_grid.GetTextMatrix(i+1,1/*ҩƷ����*/);
			str[1]=LoginInformation.kfbm;/*�ⷿ����*/
			str[4]=m_grid.GetTextMatrix(i+1,0/*ҩƷID*/);
		//	str[3]=m_getKfbm; //Ŀ�Ŀⷿ����

			for(int x=5;x<14;x++)
				str[x]=m_grid.GetTextMatrix(i+1,x);
	      //�Զ�����ҩƷ  ID	
			strSql.Format("UPDATE MEDLIE set SL=SL- (%.2f) where ID=%s and KFBM='%s' ",atof(str[13]),str[4],str[1]);
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

			strSql.Format("insert into ITEMTI (id,sl,dj,selldj,riqi,danjuhao,rq1,rq2,ypbm,kfbm,factory ) values(%s,\
				%.2f,%.2f,%.2f,TRUNC(SYSDATE,'dd'),'%s',to_date('%s','yyyy-mm-dd'),to_date('%s','yyyy-mm-dd'),\
				'%s','%s' ,'%s') ",str[4],atof(str[13]),atof(str[10]),\
				atof(str[11]),danjuhao,	str[5],str[6],str[0],LoginInformation.kfbm,str[8]);
		
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		}


		HospitalConnect->CommitTrans();
		strSql.Format("select distinct to_char(sysdate,'yyyymmddhh24miss') da from dual" );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			strSql=(char*)_bstr_t (recSet->GetCollect("da"));
			m_zktou='E'; //�ڲ�����
			m_zktou+=strSql+LoginInformation.user_code;
		}
		recSet->Close();
		c_danjuhao.SetWindowText(m_zktou);
	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox(strSql);
		AfxMessageBox("���ִ���,������Ӧ�ó���Ȼ�����²���һ��...");
		return;
	}
	AfxMessageBox("ҩƷ�ɹ�����,�뵽��Ӧҩ��ȡҩ...");

	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"ID","ҩƷ����","ҩƷ����","���","��λ","������","��Ч��",\
		"����BM","����","�����","�ۼ�","����","ָ����","ȡҩ��"}; //��14��
	long  headWidth[]={0,00,2000,1600,600,0,1400,0,1600,1000,000,0,0,1200};


	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	


}
