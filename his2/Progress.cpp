// Progress.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "Progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgress dialog


CProgress::CProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CProgress::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgress)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	connectFlag=0;
	fontTitle.CreatePointFont(180,"����");
	flagRun=true;
}


void CProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgress)
	DDX_Control(pDX, IDC_PROGRESS1, m_p);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgress, CDialog)
	//{{AFX_MSG_MAP(CProgress)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgress message handlers

BOOL CProgress::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if( flagRun && ::MessageBox(AfxGetMainWnd()->m_hWnd,strNotify,"��ʾ",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) {
		SendMessage(WM_CLOSE);
		return false ;
	}

	AfxBeginThread(pThreadFunction,(LPVOID)this); //ʵ�ʹ���
	
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strView);	
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CProgress::RelateAutoAddCash(LPVOID ps)
{
	AfxBeginThread(scheduleProgress,ps); //�����߳�ָʾ
	long succ;
	CString str1;

	_CommandPtr cmd;
	_ParameterPtr par;
	cmd.CreateInstance(__uuidof( Command ));
	par.CreateInstance(__uuidof( Parameter));

	_variant_t vNULL;
	vNULL.vt = VT_ERROR;
	vNULL.scode = DISP_E_PARAMNOTFOUND;
	try{
		cmd->put_CommandType(adCmdStoredProc) ;
		par=cmd->CreateParameter(_bstr_t("succ"),adInteger,adParamOutput,0,vNULL);
		cmd->Parameters->Append( par );
		
		cmd->put_CommandText(_bstr_t("PRC_RELATE_REMAIN"));
		cmd->ActiveConnection=HospitalConnect;
		cmd->Execute(NULL,NULL,adCmdStoredProc);
		
		succ=(long)cmd->Parameters->GetItem("succ")->Value;
		((CProgress*)ps)->connectFlag =1; //ֹͣ������
		switch( succ )
		{
		case 0:str1.Format("�ɹ������˳�ֵ�!!");
			break;
		case 1:str1.Format("������Ѿ����й���ֵ�,��ֹ�ٴγ�ֵ!!!");
			break;
		case 2:str1.Format("�����������п��ܳ���һЩ���������ݴ���,��ֵʧ��!!");
			break;
		default:
			str1.Format("��ֵʧ��,����ϵ���������Ա!!!");
		}
		cmd.Detach();
		par.Detach();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		((CProgress*)ps)->connectFlag =1;
		return false;
	}
	AfxMessageBox(str1);
	((CProgress*)ps)->SendMessage(WM_CLOSE);
	return true;

}

UINT CProgress::scheduleProgress(LPVOID ps)
{
	int i=1;

	while( ! ((CProgress*)ps)->connectFlag ){
	
		((CProgress*)ps)->m_p.SetPos(i++);
		if(i==100) i=0;
		Sleep(5);
	
	}
//	((CProgress*)ps)->SendMessage(WM_CLOSE);
	return 1;

}

HBRUSH CProgress::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(GetDlgItem(IDC_STATIC_TITLE)->m_hWnd == pWnd->m_hWnd )
		pDC->SetTextColor(RGB(255,0,0));
	return hbr;
}



UINT CProgress::EmpAutoAddCash(LPVOID ps)
{
	AfxBeginThread(scheduleProgress,ps); //�����߳�ָʾ
	long succ;
	CString str1;

	_CommandPtr cmd;
	_ParameterPtr par;
	cmd.CreateInstance(__uuidof( Command ));
	par.CreateInstance(__uuidof( Parameter));

	_variant_t vNULL;
	vNULL.vt = VT_ERROR;
	vNULL.scode = DISP_E_PARAMNOTFOUND;
	try{
		cmd->put_CommandType(adCmdStoredProc) ;
		par=cmd->CreateParameter(_bstr_t("strName"),adVarChar,adParamInput,40,_bstr_t(LoginInformation.user) );
		cmd->Parameters->Append( par );
	
		par=cmd->CreateParameter(_bstr_t("succ"),adInteger,adParamOutput,0,vNULL);
		cmd->Parameters->Append( par );
		
		cmd->put_CommandText(_bstr_t("PRC_EMP_REMAIN"));
		cmd->ActiveConnection=HospitalConnect;
		cmd->Execute(NULL,NULL,adCmdStoredProc);
		
		succ=(long)cmd->Parameters->GetItem("succ")->Value;
		((CProgress*)ps)->connectFlag =1; //ֹͣ������
		switch( succ )
		{
		case 0:str1.Format("�ɹ������˳�ֵ�!!");
			break;
		case 1:str1.Format("������Ѿ����й���ֵ�,��ֹ�ٴγ�ֵ!!!");
			break;
		case 2:str1.Format("�����������п��ܳ���һЩ���������ݴ���,��ֵʧ��!!");
			break;
		case 3: str1.Format("û��Ҫ��ֵ�Ĺ�����Ϣ!!");
			break;
		default:
			str1.Format("��ֵʧ��,����ϵ���������Ա!!!");
		}
		cmd.Detach();
		par.Detach();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		((CProgress*)ps)->connectFlag =1;
		return false;
	}
	AfxMessageBox(str1);
	((CProgress*)ps)->SendMessage(WM_CLOSE);
	return true;
}

UINT CProgress::createBalanceCount(LPVOID ps) 
// ����oracle�洢��������һ����ʱ����Ϣ
// �� ���䱣�ջ�������
{
	AfxBeginThread(scheduleProgress,ps); //�����߳�ָʾ

	long succ;
	CString str1;

	_CommandPtr cmd;
	_ParameterPtr par;
	cmd.CreateInstance(__uuidof( Command ));
	par.CreateInstance(__uuidof( Parameter));

	_variant_t vNULL;
	vNULL.vt = VT_ERROR;
	vNULL.scode = DISP_E_PARAMNOTFOUND;
	try{
		cmd->put_CommandType(adCmdStoredProc) ;
		par=cmd->CreateParameter(_bstr_t("year"),adInteger,adParamInput,4,(long) ((CProgress*)ps)->iYear);
		cmd->Parameters->Append( par );

		par=cmd->CreateParameter(_bstr_t("ret"),adInteger,adParamOutput,0,vNULL);
		cmd->Parameters->Append( par);

		cmd->put_CommandText(_bstr_t("prc_balance"));
		cmd->ActiveConnection=HospitalConnect;
		cmd->Execute(NULL,NULL,adCmdStoredProc);
		
		succ=(long)cmd->Parameters->GetItem("ret")->Value;
		((CProgress*)ps)->connectFlag =1; //ֹͣ������
		((CProgress*)ps)->flagRun=succ ;
		cmd.Detach();
		par.Detach();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		((CProgress*)ps)->connectFlag =1;
		return false;
	}
//	AfxMessageBox(str1);
	((CProgress*)ps)->SendMessage(WM_CLOSE);
	return true;

}


