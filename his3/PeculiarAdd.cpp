// PeculiarAdd.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "PeculiarAdd.h"
#include "progressEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPeculiarAdd dialog


CPeculiarAdd::CPeculiarAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CPeculiarAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPeculiarAdd)
	m_strKH = _T("");
	m_strXM = _T("");
	//}}AFX_DATA_INIT
}


void CPeculiarAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPeculiarAdd)
	DDX_Control(pDX, IDOK_QUERY, m_22);
	DDX_Control(pDX, IDOK_EXECUTE_ADD, m_1);
	DDX_Control(pDX, IDOK_EXCEL_IN, m_B_EXCEL_IN);
	DDX_Control(pDX, IDCANCEL, m_b1);
	DDX_Control(pDX, IDC_COMBO_YEAR, comYear);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	DDX_Text(pDX, IDC_EDIT_KH0, m_strKH);
	DDX_Text(pDX, IDC_EDIT_XM, m_strXM);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPeculiarAdd, CDialog)
	//{{AFX_MSG_MAP(CPeculiarAdd)
	ON_BN_CLICKED(IDOK_EXCEL_IN, OnExcelIn)
	ON_BN_CLICKED(IDOK_EXECUTE_ADD, OnExecuteAdd)
	ON_BN_CLICKED(IDOK_QUERY, OnQuery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPeculiarAdd message handlers

BOOL CPeculiarAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();

	const int SEL_YEAR_NUM=4;

	CString str1;
	
	int iyear=atoi(theApp.strOracleYear);
	for(int x=0; x< SEL_YEAR_NUM; x++)
	{
		str1.Format("%d",iyear--);
		comYear.AddString(str1);
	}
	
	comYear.SetCurSel(--x);
	
	CComFunc::comSetGridHeader(m_grid,HEADER_ID);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
#define   IDC_PROGRESS_EXCEL WM_USER+1211

void CPeculiarAdd::OnExcelIn() //���ݵ���excel
{
	CString strFile,filter;
	filter="Excel�ļ� (*.xls)|*.xls||";
	CFileDialog fixls(true,"xls","",0,filter);
	if(fixls.DoModal()==IDCANCEL)return;
	
	strFile=fixls.GetPathName();

	CString strSql;
//	COleDateTime dt1;
//	d1.GetTime(dt1);
	comYear.GetLBText(comYear.GetCurSel(),strSql);
	int iYear=atoi(strSql);
	strSql.Format("��ȷ�����������ļ��������ȷ����(%s,%d��) ",strFile,iYear );
	if( AfxMessageBox(strSql,MB_OKCANCEL) == IDCANCEL ) {
		
		return;
	}

//�������Ƿ��Ѿ�����,û������,�����˳�
COleVariant vOpt(DISP_E_PARAMNOTFOUND,VT_ERROR);//	vOpt.vt=VT_EMPTY;
	Range vr;
	long y(1);
	CString strTemp;
	double dbWage(0),db1;
	try{
		strSql.Format("SELECT count(*) FROM lsq_emp_other_price WHERE n2=%d ",iYear );
		strTemp=CComFunc::GetString(strSql);
/*		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(0l)->Value);
		recSet->Close();
*/		if( atol(strTemp) > 0 ){
			strSql.Format("%d��������Ѿ����ڣ�������ֹ���룡����",iYear );
			AfxMessageBox(strSql);
			return;
		}
//////////////////////////////////////////////////////////////
	BeginWaitCursor();
	CProgressEx pp;
	CRect r1(0,0,400,25);
	pp.Create(WS_CHILD |PBS_SMOOTH|WS_BORDER ,r1,this,IDC_PROGRESS_EXCEL);
	pp.UpdateWindow();
	pp.ShowWindow(SW_SHOW);
	pp.CenterWindow();
	pp.Invalidate();
	pp.strView="����׼������...���Եȣ���";
#define _O(x) COleVariant(x)
	_Application app2 ;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;

	app2.CreateDispatch("excel.application");
	if(!app2){
		AfxMessageBox("��ע��ϵͳ�б���װ��EXCEL97 ���� EXCEL2000 ,����˹��ܲ���ʹ��...");
		return;
	}
	books2=app2.GetWorkbooks();
	book2=books2.Open(strFile,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	sheets2=book2.GetWorksheets();
	
	sheet2=sheets2.GetItem(COleVariant((short)1)); //sheet1 ��Ϊ���ʱ�
	app2.SetVisible(false);


	HospitalConnect->BeginTrans();
	while(true){
	
		filter.Format("A%d",y);
		vr=sheet2.GetRange(_O(filter),_O(filter));
		strTemp=(char*)_bstr_t( vr.GetValue() );
		if( strTemp.IsEmpty() ) {
			break;
		}
	
		filter.Format("B%d",y);
		vr=sheet2.GetRange(_O(filter),_O(filter));
		db1=atof((char*)_bstr_t(vr.GetValue()) );
	

		strSql.Format(" INSERT INTO lsq_emp_other_price(ds1,n1,n2) VALUES('%s',%.2f,%d )  ",strTemp,db1,iYear );
	
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		dbWage+=db1;
		++y;
		pp.strView.Format("�Ѿ�����%ld��ְ������",y-1);
		pp.SetPos( (y-1)%100 );
		
	}


	HospitalConnect->CommitTrans();
	EndWaitCursor();	


//////////////////////////////////////////////


	pp.DestroyWindow();
	sheet2.ReleaseDispatch();
	sheets2.ReleaseDispatch();
	book2.Close(_O((short)0),vOpt,vOpt); //�ر�EXCEL,�������ļ�
	book2.ReleaseDispatch();
	books2.Close();
	books2.ReleaseDispatch();
	app2.ReleaseDispatch();	
	app2.Quit();
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return;
	}
	
	
	strSql.Format("������ %ld ��ְ������,�ܶ�Ϊ��%.2f",y-1 ,dbWage);
	
	AfxMessageBox(strSql);
	
}

void CPeculiarAdd::OnExecuteAdd() //��ֵ
{
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
		
		cmd->put_CommandText(_bstr_t("prc_emp_buZu_call"));
		cmd->ActiveConnection=HospitalConnect;
		cmd->Execute(NULL,NULL,adCmdStoredProc);
		
		succ=(long)cmd->Parameters->GetItem("succ")->Value;
		switch( succ )
		{
		case 0:str1.Format("�ɹ������˳�ֵ�!!");
			break;
		case 1:str1.Format("������Ѿ����й���ֵ�,��ֹ�ٴγ�ֵ!!!");
			break;
		case 2:str1.Format("�洢����ִ���쳣!!");
			break;
		case 3:str1.Format("�޲�����Ϣ����");
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
	}
	AfxMessageBox(str1);	
}



void CPeculiarAdd::OnQuery() 
{
	UpdateData();
	CString str1,str2;
	comYear.GetLBText(comYear.GetCurSel(),str1);
	int i=atol(str1);
	if( i ==0 ) return;
	CComFunc::GetSql(str2,SQL_ID);

	str2.Replace("[PARAM1]",str1);

	if( ! m_strKH.IsEmpty() ){
		str1.Format(" AND a.ds1 like '%s%%' ",m_strKH);
	}
	else if( !m_strXM.IsEmpty() ){
		str1.Format(" AND ���� like '%s%%' ",m_strXM);

	}
	else str1.Format("");
	str2.Replace("[PARAM2]",str1);


	CComFunc::comSetGridHeader(m_grid,HEADER_ID);	
	CComFunc::ReadDataForGrid(str2,m_grid);
}
