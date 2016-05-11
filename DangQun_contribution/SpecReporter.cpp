// SpecReporter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "his3.h"
#include "SpecReporter.h"
#include "afxdialogex.h"
#include <sstream>

// CSpecReporter �Ի���

IMPLEMENT_DYNAMIC(CSpecReporter, CDialogEx)

CSpecReporter::CSpecReporter(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSpecReporter::IDD, pParent),szProName("prc_compute_reporter2"),SZERROR("LSQ_ERROR")
{

	m_szStart = _T("");
	m_szEnd = _T("");
}

CSpecReporter::~CSpecReporter()
{
}

void CSpecReporter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cbType);
	DDX_Control(pDX, IDC_COMBO_YEAR, m_cbYear);
	DDX_Text(pDX, IDC_EDIT_END, m_szEnd);
	DDX_Text(pDX, IDC_EDIT_START, m_szStart);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CSpecReporter, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSpecReporter::OnBnClickedOk)
END_MESSAGE_MAP()



//Date:2014/09/23
//Brief��
//		���ô洢����prc_compute_reporter������ԼͨѶԱ��괦��

void CSpecReporter::OnBnClickedOk()
{
	UpdateData();
	ostringstream szFmt("");
	vector<string> vtSz;

	vtSz.push_back( szProName ); //�洢������
	
	vtSz.push_back((LPCSTR)m_szStart);
	vtSz.push_back((LPCSTR)m_szEnd);

	szFmt<<vtType[m_cbType.GetCurSel()] ;
	vtSz.push_back(szFmt.str() );

	CString str;
	m_cbYear.GetLBText(m_cbYear.GetCurSel(),str);
	vtSz.push_back( (LPCSTR)str);


	string szRet;

	CComFunc::callSqlPro(vtSz,szRet);

	if( szRet.compare(SZERROR) )
	{
			AfxMessageBox("��ɹ���");
		
	} 
	else AfxMessageBox("���ô洢����ʧ��");
	//_CommandPtr cmd;
	//_ParameterPtr par;
	//cmd.CreateInstance(__uuidof( Command ));
	//par.CreateInstance(__uuidof( Parameter));

	//_variant_t vNULL;
	//vNULL.vt = VT_ERROR;
	//vNULL.scode = DISP_E_PARAMNOTFOUND;
	//try{
	//	cmd->put_CommandType(adCmdStoredProc) ;
	//	//��ʼ�ں�
	//	par=cmd->CreateParameter(_bstr_t("start_issn"),adInteger,adParamInput,4,atol(m_szStart));
	//	cmd->Parameters->Append( par );
	//	//��ֹ�ں�
	//	par=cmd->CreateParameter(_bstr_t("end_issn"),adInteger,adParamInput,4,atol(m_szEnd));
	//	cmd->Parameters->Append( par );
	//	//�ڿ����
	//	par=cmd->CreateParameter(_bstr_t("type_issn"),adInteger,adParamInput,4,vtType[m_cbType.GetCurSel()] );
	//	cmd->Parameters->Append( par );
	//	//��ԼͨѶԱ�������
	//	CString str;
	//	m_cbYear.GetLBText(m_cbYear.GetCurSel(),str);
	//	par=cmd->CreateParameter(_bstr_t("year"),adInteger,adParamInput,4,atol(str) );
	//	cmd->Parameters->Append( par );
	//
	///*	par=cmd->CreateParameter(_bstr_t("ret"),adInteger,adParamOutput,0,vNULL);
	//	cmd->Parameters->Append( par);*/

	//	cmd->put_CommandText(_bstr_t("prc_compute_reporter"));
	//	cmd->ActiveConnection=HospitalConnect;
	//	cmd->Execute(NULL,NULL,adCmdStoredProc);
	//	
	////	succ=(long)cmd->Parameters->GetItem("ret")->Value;

	//	cmd.Detach();
	//	par.Detach();
	//}
	//catch(_com_error e)
	//{
	//	AfxMessageBox(e.ErrorMessage());
	//	return;
	//}	
	//
	//AfxMessageBox("�ɹ�ִ����ԼͨѶԱ������������");

}


BOOL CSpecReporter::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	long i=0;
	CString strSql;
	try{

		//��ʼ���ڿ�����
		strSql.Format(" SELECT news_id,news_name FROM news_type  ORDER BY Rank");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			vtType.push_back(atoi( CComFunc::GetSqlItem(i++) ) );
			m_cbType.AddString(CComFunc::GetSqlItem(i++));
			
			recSet->MoveNext();
		}
		recSet->Close();
		
		int year=COleDateTime::GetCurrentTime().GetYear();
		i=3;
		CString strFmt;
		while(i-- )
		{
			strFmt.Format("%d",year--);
			m_cbYear.AddString(strFmt);
		}
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return false;
	}		
	m_cbType.SetCurSel(0);
	m_cbYear.SetCurSel(0);

	return TRUE;  
}
