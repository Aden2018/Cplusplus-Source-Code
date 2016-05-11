// JournalFee.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "JournalFee.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJournalFee dialog

extern string SZERROR;
CJournalFee::CJournalFee(CWnd* pParent /*=NULL*/)
	: CDialog(CJournalFee::IDD, pParent),szProName("prc_spec_reporter")
{
	//{{AFX_DATA_INIT(CJournalFee)
	m_strEditor = _T("");
	m_Fee = _T("");
	m_layout = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
	iSel=-1; //Ĭ��Ϊ -1

	m_words = _T("");
	ftTitle.CreatePointFont(220,"΢���ź�");

	 cFont.CreateFont(20,0,0,0,FW_SEMIBOLD,FALSE,FALSE,0,
                ANSI_CHARSET,OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
                DEFAULT_PITCH&FF_SWISS,"Arial");


}


void CJournalFee::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJournalFee)
	DDX_Control(pDX, IDC_COMBO_RELEASE_NUM, m_releaseNum);
	DDX_Control(pDX, IDC_COMBO_FACTORY, m_Factory);
	DDX_Control(pDX, IDC_COMBO_RELEASE_TYPE, m_releaseType);
	DDX_Control(pDX, IDC_COMBO_BAOKAN_TYPE, m_newsType);
	DDX_Text(pDX, IDC_EDIT_EDITOR, m_strEditor);
	DDX_Text(pDX, IDC_EDIT_FEE, m_Fee);
	DDX_Text(pDX, IDC_EDIT_LAYOUT_NUM, m_layout);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO_REL_TYPE, m_NewType);
	DDX_Text(pDX, IDC_EDIT_WORDS, m_words);
	
}


BEGIN_MESSAGE_MAP(CJournalFee, CDialog)
	//{{AFX_MSG_MAP(CJournalFee)
	ON_EN_KILLFOCUS(IDC_EDIT_EDITOR, OnKillfocusEditEditor)
	ON_CBN_KILLFOCUS(IDC_COMBO_BAOKAN_TYPE, OnKillfocusComboBaokanType)
	ON_CBN_SELCHANGE(IDC_COMBO_FACTORY, OnSelchangeComboFactory)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO_REL_TYPE, &CJournalFee::OnCbnSelchangeComboRelType)
	ON_EN_CHANGE(IDC_EDIT_WORDS, &CJournalFee::OnEnChangeEditWords)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BOOL CJournalFee::OnInitDialog() 
{
	CDialog::OnInitDialog();

	extern string SZERROR;
	xpButton[0].SubclassDlgItem(IDOK,this);
	xpButton[1].SubclassDlgItem(IDCANCEL,this);

	strSql.LoadString(IDS_STR_JOURNAL_CONTRIBUTION);
	SetWindowText(strSql);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strSql);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&ftTitle);
	GetDlgItem(IDC_EDIT_FEE)->SetFont(&cFont);

	long i=0;
// ����Ϊ�洢���̵��ø�дԭ�е����ݿ����

	vector<string> vtSz;
	string szRet("");
	vtSz.push_back(szProName); //�洢������
	vtSz.push_back("1");						//��������,��ѯ������

	vtSz.push_back("1");			//��ѯ��ֽ�����־����վ
	CComFunc::callSqlPro(vtSz,szRet);
	if( ! szRet.compare(SZERROR)  ) 
	{		AfxMessageBox("��ȡ��������ʧ��");
			return false;
	}
	CComFunc::GenerateSubStr(szRet,arrNewsType,m_newsType);

	vtSz[2]="8";
	CComFunc::callSqlPro(vtSz,szRet); // �������ͷ���,��������ȷ�ϸ�ѱ�׼
	if( ! szRet.compare(SZERROR)  ) 
	{		AfxMessageBox("��ȡ��������ʧ��");
			return false;
	}
	CComFunc::GenerateSubStr(szRet,arrNewType,m_NewType);


	vtSz[2]="3";								// ��λ�����ݣ���������˾��
	CComFunc::callSqlPro(vtSz,szRet);
	if( ! szRet.compare(SZERROR)  ) 
	{		AfxMessageBox("��ȡ��������ʧ��");
			return false;
	}
	CComFunc::GenerateSubStr(szRet, arrFactory,m_Factory);


	



	m_newsType.SetCurSel(0); //��������:���̱�,������־,��վ��
	m_Factory.SetCurSel(0);	//��λ



	
	return TRUE;  
}

BOOL CJournalFee::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){
		if( pMsg->hwnd == GetDlgItem(IDOK)->m_hWnd )
		{
			OnOK();
			return false;
		}
		pMsg->wParam = VK_TAB;

	}
	
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CJournalFee::OnOK() 
{	

	UpdateData();
	if( m_releaseNum.GetCurSel()/*�����ں�*/ ==CB_ERR || m_NewType.GetCurSel()/*�µ���������*/ == CB_ERR || m_Factory.GetCurSel() /*��λ*/== CB_ERR
		|| m_newsType.GetCurSel()/*��������*/ == CB_ERR ){
		
		AfxMessageBox("�뽫�����Ŀ��д��������");
		return;
	}

	vector<string> vtSz;
	vtSz.push_back( szProName ); //�洢������
	vtSz.push_back("0");			//��������
	vtSz.push_back( (LPCSTR)arrReleaseNum[m_releaseNum.GetCurSel()] ); //�ڿ���

	vtSz.push_back( (LPCSTR)m_layout);  //�����
	vtSz.push_back( (LPCSTR) m_strEditor ); //����
	vtSz.push_back( (LPCSTR) m_strTitle); //���±���
//	vtSz.push_back( (LPCSTR) arrReleaseType[m_releaseType.GetCurSel()] ); //��������
	vtSz.push_back( (LPCSTR) arrNewType[ m_NewType.GetCurSel() ] ); //���µ����·����滻�ɵķ����׼

	vtSz.push_back( (LPCSTR) m_Fee); //���
	vtSz.push_back( (LPCSTR) arrNewsType[m_newsType.GetCurSel()] ); //��������
	vtSz.push_back( (LPCSTR)  arrFactory[m_Factory.GetCurSel()]  ) ;//����������λ
	//����һ����
	ostringstream osv;
	osv<<atol(m_words);
	vtSz.push_back( osv.str() );//��������

	//���������û�ID
	vtSz.push_back( (LPCSTR)LoginInformation.user_code);
	string szRet;

	CComFunc::callSqlPro(vtSz,szRet);

	if( szRet.compare(SZERROR) )
	{
			AfxMessageBox("��ɹ���");
			ResetCtrl();
	} 
	else AfxMessageBox("���ô洢����ʧ��");
	

}

void CJournalFee::ResetCtrl()
{
	m_strTitle=BLANKSTR;
	m_strEditor=BLANKSTR;
	m_Fee=BLANKSTR;
	m_words=BLANKSTR;
	iSel=-1;
	
	GetDlgItem(IDC_STATIC_FACTORY)->SetWindowText(BLANKSTR);
	
	UpdateData(false);
	GetDlgItem(IDC_EDIT_TITLE)->SetFocus();


}



void CJournalFee::OnKillfocusEditEditor() //������������ϵ���в���
{
	UpdateData();
	if( m_strEditor.IsEmpty() ) return;

	vector<string> vtSz;
	string szRet(""),szEle;
	vtSz.push_back(szProName.c_str()); //�洢������
	vtSz.push_back("1");			//��������,��ѯ������
	vtSz.push_back("5");			//��ѯͨѶԱ
	vtSz.push_back((LPCSTR)m_strEditor);
	CComFunc::callSqlPro(vtSz,szRet);
	if( ! szRet.compare(SZERROR)  ) 
	{	
			GetDlgItem(IDC_STATIC_FACTORY)->SetWindowText("");
			return ;
	}
	int i(0);
	CString szTmp;
	while(i < arrFactory.GetSize() )
	{
		m_Factory.GetLBText(i,szTmp);
		if( ! szTmp.Compare(szRet.c_str()) ){
			m_Factory.SetCurSel(i);
			iSel=i;
			break;
		}
		i++;
	}
	GetDlgItem(IDC_STATIC_FACTORY)->SetWindowText(szRet.c_str());

/*	
	CString str[2];
	try{
		str[0]=BLANKSTR;
		str[1]=BLANKSTR;
		strSql.Format("Select factory_id from Contacter Where name='%s' ",m_strEditor);
		str[0]=CComFunc::GetString(strSql);

		if( ! str[0].IsEmpty() ){  
		
			strSql.Format("SELECT factory FROM Factory  WHERE factory_id=%ld ",atol(str[0]) );
			str[1]=CComFunc::GetString(strSql);
			int i=0;
			while(i < arrFactory.GetSize() )
			{
				if( ! arrFactory[i].Compare(str[0]) ){
					m_Factory.SetCurSel(i);
					iSel=i;
					break;
				}
				i++;
			}
		
		
		}
		else iSel=-1;
		
		GetDlgItem(IDC_STATIC_FACTORY)->SetWindowText(str[1]);
		

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return ;
	}		 
*/
}



void CJournalFee::OnKillfocusComboBaokanType() 
{
	arrReleaseNum.RemoveAll();
	m_releaseNum.ResetContent();

	vector<string> vtSz;
	vtSz.push_back( szProName.c_str() ); //�洢������
	vtSz.push_back("1");			//��ѯ
	vtSz.push_back("4");			//��ѯ�����ں�
	vtSz.push_back((LPCSTR)arrNewsType[m_newsType.GetCurSel()]); //�ڿ���

	string szRet("");

	CComFunc::callSqlPro(vtSz,szRet);
	if( ! szRet.compare(SZERROR)  ) 
	{		AfxMessageBox("��ȡ��������ʧ��");
			return;
	}
	CComFunc::GenerateSubStr(szRet,arrReleaseNum,m_releaseNum);
	

}

void CJournalFee::OnSelchangeComboFactory() 
{
	
}



//����������������������ȷ�����
void CJournalFee::OnCbnSelchangeComboRelType()
{
	
	if( m_NewType.GetCurSel()== CB_ERR) return;
	UpdateData();

	vector<string> vtSz;
	vtSz.push_back( szProName.c_str() ); //�洢������
	vtSz.push_back("1");			//��ѯ
	vtSz.push_back("9");			//������ţ���ѯ��ѱ�׼���
	vtSz.push_back((LPCSTR) arrNewType[ m_NewType.GetCurSel()] ); //��������
	ostringstream szv;
	szv<<atol(m_words);
	vtSz.push_back( szv.str() );	//��������

	string szRet;

	CComFunc::callSqlPro(vtSz,szRet);
	if( ! szRet.compare(SZERROR)  ) 
	{		AfxMessageBox("��ȡ��������ʧ��");
			return;
	}

	GetDlgItem(IDC_EDIT_FEE)->SetWindowText(szRet.c_str());
	
}


void CJournalFee::OnEnChangeEditWords()
{
	OnCbnSelchangeComboRelType()	;
}


HBRUSH CJournalFee::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	

   
	if( pWnd->m_hWnd == GetDlgItem(IDC_EDIT_FEE)->m_hWnd )
	{
		pDC->SetTextColor(RGB(255,0,0));

		
      
	}

	return hbr;
}
