// RegisterGh.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "RegisterGh.h"
#include "comfunc.h"
#include "dialogHjsf.h"
#include "personQuery.h"
#include "personQueryRelate.h"
#include "personQueryOthersick.h"
#include "PersonQueryHayb.h"
#include "personQueryJmtc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegisterGh dialog


CRegisterGh::CRegisterGh(CWnd* pParent /*=NULL*/)
	: CDialog(CRegisterGh::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegisterGh)
	//}}AFX_DATA_INIT
	ybFlag=GH_NORMAL;
	strYbCode=BLANKSTR;
	strBCBXcode=BLANKSTR;
	strGYQScode=BLANKSTR;
	strOHTERcode=BLANKSTR;
}


void CRegisterGh::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegisterGh)
	DDX_Control(pDX, IDC_EDIT_ADDRESS, m_addr);
	DDX_Control(pDX, IDC_EDIT_AGE, m_age);
	DDX_Control(pDX, IDC_EDIT_NAME, m_name);
	DDX_Control(pDX, IDC_COMBO_SEX, m_se);
	DDX_Control(pDX, IDC_EDIT_KH, m_kh);
	DDX_Control(pDX, IDC_COMBO_GH_TYPE, m_ghType);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegisterGh, CDialog)
	//{{AFX_MSG_MAP(CRegisterGh)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_CBN_SELCHANGE(IDC_COMBO_GH_TYPE, OnSelchangeComboGhType)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_GRID_DEL, OnButtonGridDel)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegisterGh message handlers

BOOL CRegisterGh::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString strSql;
	m_ghTypeArray.RemoveAll();
	try{
	//	strSql="select ds1,ds3 from lsq_upgrade t where ds2=upper('gh_type') and n3 > 0 order by n1";
		CComFunc::GetSql(strSql,22);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetCollect("ds1").vt==VT_NULL?" ":recSet->GetCollect("ds1"));
			m_ghType.AddString(strSql);
			strSql=(char*)_bstr_t(recSet->GetCollect("ds3").vt==VT_NULL?" ":recSet->GetCollect("ds3"));
			m_ghTypeArray.Add(strSql);
			recSet->MoveNext();
	
		}
		recSet->Close();
		
		QueryGh();
	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return false;
	}		

	m_ghType.SetCurSel(0);

	//SetWindowText(theApp.strProject);
	m_se.SetCurSel(0);
	CenterWindow();




	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRegisterGh::OnButtonCancel() 
{
	if( ybFlag == GH_ADD ){
		GetDlgItem(IDC_BUTTON_ADD)->ShowWindow(SW_HIDE);
		ybFlag=GH_NORMAL;
		m_kh.EnableWindow(true);

		return;


	}
	CDialog::OnCancel();	
}

void CRegisterGh::OnButtonOk() 
{
	if( ybFlag == GH_ADD) return; //��ҽ����Ա��Ϣ����ʱ,ֱ�ӷ���

	UpdateData();
	
	CString strSerial(BLANKSTR);
	CString strCODE(BLANKSTR);
	strSql=BLANKSTR;

	try{
		strSql=CComFunc::GetString( CComFunc::GetString("SELECT sql FROM lsq_sql_statemnet WHere id=4 ") );
		if( strSql.IsEmpty() ){
			AfxMessageBox("�Զ��������б������������!");
			return;
		}
		strSerial=strSql+LoginInformation.user_code; //�������к�
		CString str1,strSex,strMC,strAddr;
		m_name.GetWindowText(str1); //����
		m_se.GetLBText(m_se.GetCurSel(),strSex);//�Ա�
//		m_age.GetWindowText(strAge);
//		strAge.Format("%d",atoi(strAge));
//		m_ghType.GetWindowText(strMC);

		m_addr.GetWindowText(strAddr);
		int iTypeSel=m_ghType.GetCurSel();
		

		switch( CComFunc::GetGhType(m_ghTypeArray[iTypeSel] ) )
		{
		case CComFunc::TYPE_QPYB:
		case CComFunc::TYPE_HAYB:
		case CComFunc::TYPE_JMTC:		//����ҽ��,����ͳ��\��������
			if( strYbCode.IsEmpty() ){
				AfxMessageBox("��������ҽ������");
				return;
			}
			strCODE=strYbCode;
			break;

		case CComFunc::TYPE_BCBX: //���䱣��
			if( strBCBXcode.IsEmpty() )
			{
				AfxMessageBox("���ȵ������䱣����Ա��Ϣ!!!");
				return;

			}
			strCODE=strBCBXcode;
			break;

		case CComFunc::TYPE_GYQS: //��������
			if( strGYQScode.IsEmpty() )
			{
				AfxMessageBox("���ȵ�������������Ա��Ϣ!!!");
				return;

			}
			strCODE=strGYQScode;
			break;

		case CComFunc::TYPE_GC:
		case CComFunc::TYPE_TY:
		case CComFunc::TYPE_LX:
		case CComFunc::TYPE_GS: //��ǰ,����,����,����
			if( strOHTERcode.IsEmpty() )
			{
				AfxMessageBox("���ȵ�����Ա��Ϣ!!!");
				return;

			}
			strCODE=strOHTERcode;
			break;
			
		}

		strSql.Format(" INsert into  ItemRegisterTou(Danjuhao,ghType,riqi,sickbm,sickname,�Һ�Ա,�Һ�Ա��,sex,address ) \
			  values('%s','%s',trunc(sysdate,'dd'),'%s','%s','%s','%s','%s','%s' ) "
			  ,strSerial,m_ghTypeArray[iTypeSel],strCODE,str1,LoginInformation.user_code,LoginInformation.user,strSex,strAddr);

		if( !CComFunc::WriteSql(strSql) )
		{	
			AfxMessageBox("�Һų��ִ���,������!");
			return;
		}

		AfxMessageBox("�Һųɹ�!");
		
		clearView();
		QueryGh();
		OnSelchangeComboGhType();

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return ;
	}		

	
}

void CRegisterGh::OnSelchangeComboGhType() 
{
	CString strTmp(BLANKSTR);
	int iTypeSel=m_ghType.GetCurSel();

	switch ( CComFunc::GetGhType(m_ghTypeArray[iTypeSel]) )
	{
	case CComFunc::TYPE_QPYB:		
		strTmp=CComFunc::GetString(" select ds1 from lsq_upgrade t where ds2=upper('QPYBQ01') ") ; //��ȡ ҽ����Աǰ׺
		break;
	case CComFunc::TYPE_HAYB:
		strTmp=CComFunc::GetString(" select ds1 from lsq_upgrade t where ds2=upper('HASYB02') ") ; 
		break;
	case CComFunc::TYPE_JMTC:
		strTmp=CComFunc::GetString(" select ds1 from lsq_upgrade t where ds2=upper('HASYB01') ") ; 
		break;
	default:
		m_kh.EnableWindow();
		GetDlgItem(IDC_BUTTON_ADD)->ShowWindow(SW_HIDE);
		
		strTmp=BLANKSTR;

	}

	m_kh.SetFocus();
	m_kh.SetWindowText(strTmp);
	m_kh.SetSel(strTmp.GetLength(),strTmp.GetLength());

	clearView();

}

BOOL CRegisterGh::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN ) {
		CString str1=m_ghTypeArray[m_ghType.GetCurSel()];
		if( pMsg->hwnd == m_kh.m_hWnd ){
			switch( CComFunc::GetGhType(m_ghTypeArray[m_ghType.GetCurSel()] ) ){
			case CComFunc::TYPE_QPYB:
				queryPerson();
				break;
			case CComFunc::TYPE_HAYB:
			case CComFunc::TYPE_JMTC:
				queryHayb();
				break;
			case CComFunc::TYPE_BCBX:
			case CComFunc::TYPE_GYQS:
			case CComFunc::TYPE_GC:
			case CComFunc::TYPE_GS:
			case CComFunc::TYPE_TY:
			case CComFunc::TYPE_LX:
				queryAccount();
				break;
			default: 
				pMsg->wParam =VK_TAB ;
				goto JMPIF;
			}
			return true;

		}
		else {
			pMsg->wParam= VK_TAB;
			goto JMPIF;
		}
	}
JMPIF:	
	return CDialog::PreTranslateMessage(pMsg);
}

bool CRegisterGh::queryPerson()  //��ѯҽ����Ա��Ϣ
{
	CString strSql,strTmp;
	m_kh.GetWindowText(strTmp);
	if( strTmp.IsEmpty() ) return false;

	try{
		strSql="select name,sex,age from lsq_qingpuyibao Where id='"+strTmp+"' and effect=1 ";
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			
			strYbCode=strTmp;
			strSql=(char*)_bstr_t(recSet->GetCollect("name").vt==VT_NULL?" ":recSet->GetCollect("name"));
			m_name.SetWindowText(strSql);

			strSql=(char*)_bstr_t(recSet->GetCollect("age").vt==VT_NULL?" ":recSet->GetCollect("age"));
			m_age.SetWindowText(strSql);

			strSql=(char*)_bstr_t(recSet->GetCollect("sex").vt==VT_NULL?" ":recSet->GetCollect("sex"));
			m_se.SetCurSel( strSql.Compare("��")== 0 ? 0:1 );
			
	
		}
		else 
		{
			if( AfxMessageBox("����ҽ��ϵͳ�в����ڴ˿�����Ϣ���Ƿ�Ҫ���??",MB_YESNO) == IDYES )
			{
				m_name.SetFocus();
				ybFlag=GH_ADD;
				GetDlgItem(IDC_BUTTON_ADD)->ShowWindow(SW_SHOW);
				m_kh.EnableWindow(false);
				

			}

		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return false;
	}		
	
	return true;

}

void CRegisterGh::OnButtonAdd() //ҽ����Ա��Ϣ����
{
	CString strSql,str1,str2,strKh;
	int iAge=0;
	m_name.GetWindowText(str1);
	if( str1.IsEmpty() ) {
		AfxMessageBox("�뽫��������Ϣ��д�������ٵ������");
		return;
	}
	m_se.GetLBText( m_se.GetCurSel(),str2); //�Ա�
	m_age.GetWindowText(strSql);
	iAge=atoi(strSql);
	m_kh.GetWindowText(strKh);
	
	if ( CComFunc::GetGhType( m_ghTypeArray[m_ghType.GetCurSel()] ) == CComFunc::TYPE_QPYB )
		strSql.Format(" Insert into lsq_qingpuyibao(id,name,sex) values('%s','%s','%s') ",strKh,str1,str2 );
	else
		strSql.Format(" INSERT INTO ҽ����Ա�б�(����,����,�Ա�,pass) values('%s','%s','%s','%s' ) ",strKh,str1,str2,strKh);
	CComFunc::WriteSql(strSql); 

	GetDlgItem(IDC_BUTTON_ADD)->ShowWindow(SW_HIDE);
	ybFlag=GH_NORMAL;
	m_kh.EnableWindow(true);
	strYbCode=strKh;
	
	if( AfxMessageBox("ҽ����Ϣ�Ѿ����棬�Ƿ�Ҫ�Һ� ?? ",MB_YESNO) == IDYES ){
		OnButtonOk();
	}
}

void CRegisterGh::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	OnSelchangeComboGhType();	
	
}

void CRegisterGh::clearView()
{
	m_name.SetWindowText(BLANKSTR);
	m_name.SetReadOnly(false);
	m_se.SetCurSel(0);
	m_se.EnableWindow();
	m_age.SetWindowText(BLANKSTR);

	strYbCode=BLANKSTR; //ҽ����
	strBCBXcode=BLANKSTR; //���䱣��
	strGYQScode=BLANKSTR; // ����
	strOHTERcode=BLANKSTR; //����ǰ\����\����\����
}

HBRUSH CRegisterGh::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CRegisterGh::QueryGh() //�ѹҺ���Ա��ѯ
{

	long i,cols,row(1);

	try{
		CComFunc::comSetGridHeader(m_grid,7);
		cols=m_grid.GetCols(0);
		CComFunc::GetSql(strSql,10);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(! recSet->adoEOF){

			for( i=0; i< cols ; i++ )
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ? "":recSet->GetFields()->GetItem(long(i))->Value );
				if( i== 1 )strSql.Format("%d",row); //��ʾ���к�,���¼���,���ݿ�ѡ��ʱ���к��ѱ�����
				m_grid.SetTextMatrix(row,i,strSql);
			}
			row++;
			m_grid.AddItem(BLANKSTR,_variant_t(row));
			recSet->MoveNext();
			

		}
		recSet->Close();

		CComFunc::GridSelRow(m_grid,1);
	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return ;
	}		

}

void CRegisterGh::OnButtonGridDel() // ����ɾ���պ�,������,��ֹɾ�������Ѵ������Ŀ 
{
/*	int i=m_grid.GetRowSel();

	if( i ==0 || i== m_grid.GetRows()-1 ) return;

	strSql.Format(" ȷ��Ҫɾ��\n\n �Һ�����: %s   ����: %s  �Ա�: %s  ����: %s ",m_grid.GetTextMatrix(i,COL_TYPE),m_grid.GetTextMatrix(i,COL_NAME),\
		m_grid.GetTextMatrix(i,COL_SEX),m_grid.GetTextMatrix(i,COL_AGE) );

	if( AfxMessageBox(strSql,MB_YESNO) == IDYES )
	{
		strSql.Format(" Delete from ItemregisterTou Where danjuhao='%s' ",m_grid.GetTextMatrix(i,COL_DANJUHAO) );
		CComFunc::WriteSql(strSql);
		m_grid.RemoveItem(i);
//		CComFunc::writeDebug(strSql);
		computeRowView();
	}
*/	
}

void CRegisterGh::computeRowView()
{
	long i=m_grid.GetRows()-1;
	for(int x=1; x< i ; x++ )
	{
		strSql.Format("%d",x);
		m_grid.SetTextMatrix(x,COL_SEQ,strSql);
	}
}

BEGIN_EVENTSINK_MAP(CRegisterGh, CDialog)
    //{{AFX_EVENTSINK_MAP(CRegisterGh)
	ON_EVENT(CRegisterGh, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CRegisterGh::OnDblClickMshflexgrid1()  //���۴��� 
{

	CDialog *pw;
	pw=CComFunc::SysWait(this);

	if( ! CComFunc::AssertPriv(2) ){
		pw->PostMessage(WM_CLOSE);
		return; 
	}
	int i=m_grid.GetRowSel();
	if( i ==0 || i== m_grid.GetRows()-1 ){
		pw->PostMessage(WM_CLOSE);
		return;
	}
	if( !CComFunc::BeginCritical(m_grid.GetTextMatrix(i,COL_DANJUHAO),true) ){
	
		pw->PostMessage(WM_CLOSE);
		AfxMessageBox("��ȴ�,�Ѿ����û��ڻ��۲���!!!");
		return;

	}
	
	CDialogHjSf hs;
	hs.pw =(CDialogWait*)pw;
	hs.pGH=this;

	if( hs.DoModal() == IDOK ){
		QueryGh();	
		
	};




	
}


bool CRegisterGh::queryHayb()
{
	CString strSql,strTmp;
	m_kh.GetWindowText(strTmp);
	if( strTmp.IsEmpty() ) return false;

	try{
		strSql="select ����,�Ա� from ҽ����Ա�б� Where ����='"+strTmp+"'  ";
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			
			strYbCode=strTmp;
			strSql=(char*)_bstr_t(recSet->GetCollect("����").vt==VT_NULL?_variant_t(BLANKSTR):recSet->GetCollect("����"));
			m_name.SetWindowText(strSql);

			strSql=(char*)_bstr_t(recSet->GetCollect("�Ա�").vt==VT_NULL?_variant_t(BLANKSTR):recSet->GetCollect("�Ա�"));
			m_se.SetCurSel( strSql.Compare("��")== 0 ? 0:1 );
			
	
		}
		else 
		{
			if( AfxMessageBox("��ҽ��ϵͳ�в����ڴ˿�����Ϣ���Ƿ�Ҫ���??",MB_YESNO) == IDYES )
			{
				m_name.SetFocus();
				ybFlag=GH_ADD;
				GetDlgItem(IDC_BUTTON_ADD)->ShowWindow(SW_SHOW);
				m_kh.EnableWindow(false);
				

			}

		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return false;
	}		
	
	return true;

}

void CRegisterGh::OnButtonQuery()  //�����ʺŲ�ѯ
{
	int iSel=m_ghType.GetCurSel();
	int iRet= CComFunc::GetGhType(m_ghTypeArray[iSel]);
	CString strView,s1;
	CString t1,t2,t3,t4;
	m_ghType.GetLBText(iSel,t1); //�Һ�����

	if( iRet== CComFunc::TYPE_BCBX ){
		CPersonQuery pq;
		pq.lp=this;
		if( pq.DoModal() == IDOK )
		{
			s1=strBCBXcode;
			goto VIEWOK;
		}
	}
	else if( iRet == CComFunc::TYPE_GYQS ){  //����������
		CPersonQueryRelate pqr;
		pqr.lp=this;
		if( pqr.DoModal() == IDOK )
		{
			s1=strBCBXcode;
			goto VIEWOK;
		}
	}
	else if( iRet == CComFunc::TYPE_GC || iRet == CComFunc::TYPE_LX || iRet==CComFunc::TYPE_TY || iRet==CComFunc::TYPE_GS )
	{
		CPersonQueryOtherSick pos;
		pos.strTYPE=m_ghTypeArray[iSel];
		pos.lp=this;
		if( pos.DoModal() == IDOK )
		{
			s1=strBCBXcode;
			goto VIEWOK;
		}

	}
	else if ( iRet == CComFunc::TYPE_QPYB ) //����ҽ��
	{	
		CPersonQueryQpyb pqq;
		pqq.lp=this;
		if( pqq.DoModal() == IDOK )
		{
			s1=strYbCode;
			goto VIEWOK;
		}

	}
	else if( iRet == CComFunc::TYPE_HAYB  /*����ҽ��*/)
	{
		CPersonQueryHayb pqq;
		pqq.lp=this;
		if( pqq.DoModal() == IDOK )
		{
			s1=strYbCode;
			goto VIEWOK;
		}

	}
	else if (  iRet == CComFunc::TYPE_JMTC /*����ͳ��*/ )
	{
		CPersonQueryJMTC jmtc;
		jmtc.lp=this;
		if( jmtc.DoModal() == IDOK )
		{
			s1=strYbCode;
			goto VIEWOK;
		}


	}
	return ;
VIEWOK:
	m_name.GetWindowText(t2);
	m_se.GetLBText(m_se.GetCurSel(),t3);
	strView.Format(" ������Ϣ�ѵ��� : %s : %s , %s , %s \n �Ƿ�Ҫ�Һ�??",t1,s1,t2,t3);
	if( AfxMessageBox(strView,MB_YESNO) == IDYES ){
		OnButtonOk();
	}
	

}

void CRegisterGh::queryAccount()
{
	CString strSql,strTmp,s1,s2,strView;
	int iSel=m_ghType.GetCurSel();
//	int iRet=GetGhType(iSel);
	int iRet = CComFunc::GetGhType(m_ghTypeArray[iSel] );
	long i(0);

	m_kh.GetWindowText(strTmp);
	if( strTmp.IsEmpty() ) return ;

	try{
		switch( iRet ){
		case CComFunc::TYPE_BCBX :
			strSql.Format(" SELECT ����,����,�Ա� FROM ְ����������� WHERE ���='�α�' AND ����='%s' ",strTmp);
			break;
		case CComFunc::TYPE_GYQS:
			strSql.Format(" SELECT BM,XM,XB FROM codeQingshu WHERE zxriqi is NULL AND bm='%s' ",strTmp );
			break;
		case CComFunc::TYPE_TY:
		case CComFunc::TYPE_GC:
		case CComFunc::TYPE_LX:
		case CComFunc::TYPE_GS:
			s1=CComFunc::GetString(" SELECT sql FROM lsq_sql_statemnet WHERE id= 9 "); //��ǰ,���ݵȱ�
			s1+= " AND LB='"+m_ghTypeArray[iSel]+"'";
			strSql.Format(" SELECT BM,XM,XB FROM ( %s ) WHERE BM='%s' ",s1,strTmp);
			break;
		default:
			AfxMessageBox("������˼��!!������!!");
			return;

		}


		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			i=0;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			switch( iRet ){
			case CComFunc::TYPE_BCBX :
				strBCBXcode=strSql;
				break;
			case CComFunc::TYPE_GYQS:
				strGYQScode=strSql;
				break;
			case CComFunc::TYPE_TY:
			case CComFunc::TYPE_GC:
			case CComFunc::TYPE_LX:
			case CComFunc::TYPE_GS:
				strOHTERcode=strSql;
				break;
			}
			
			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			m_name.SetWindowText(strSql);
			m_name.SetReadOnly();
			
			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value );
			m_se.SetCurSel( strSql.Compare("��")== 0 ? 0:1 );
			m_se.EnableWindow(false);
			
	
		}
		recSet->Close();
		if( i > 0 )
		{
			m_ghType.GetWindowText(s1);
			m_name.GetWindowText(strSql);
			m_se.GetWindowText(s2);

			strView.Format(" ������Ϣ�ѵ��� : %s : %s , %s , %s \n �Ƿ�Ҫ�Һ�??",s1,strTmp,strSql,s2);
			if( AfxMessageBox(strView,MB_YESNO) == IDYES ){
				OnButtonOk();
			}
		}

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return ;
	}		
}
