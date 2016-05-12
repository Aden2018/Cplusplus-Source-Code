// SubsidySet.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "SubsidySet.h"
#include "standardSubsidy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubsidySet dialog


CSubsidySet::CSubsidySet(CWnd* pParent /*=NULL*/)
	: CDialog(CSubsidySet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubsidySet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"����");
//	strTitle.Format("������Ա��������");
	strTitle=COtherDecharge::GetStringTitle("SELECT ds1 FROM lsq_Title_list WHERE ds2='DIALOG' AND ds3='TITLE' and ds4='AAF' ");
}


void CSubsidySet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubsidySet)
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubsidySet, CDialog)
	//{{AFX_MSG_MAP(CSubsidySet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubsidySet message handlers

BOOL CSubsidySet::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	SetWindowText(strTitle);


	SetGridHead();	
	CString strSql;
	long i,cols,z;
	double dbCount=0;
	try{
		strSql.Format("select t.ds1,c.����,b.ds3, b.ds1,b.n3 from \
			lsq_emp_headship t,lsq_upgrade b,ְ����������� c where t.ds2=b.ds3 \
			and b.ds2='ESUB' and c.����=t.ds1 AND c.����='%s' ",strKh);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		while(!recSet->adoEOF)
		{
			i=m_grid.GetRows();
			m_grid.AddItem("",_variant_t(m_grid.GetRows()));
			for( z=0 ; z< cols ;z++){
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(z)->Value.vt==VT_NULL? "":recSet->GetFields()->GetItem(z)->Value );
				m_grid.SetTextMatrix(i-1,z,strSql);
				if( z== cols-1 ) dbCount+=atof(strSql);
			}

			recSet->MoveNext();
		}
		recSet->Close();
		
		strSql.Format("%.2f",dbCount);
		m_grid.SetTextMatrix(m_grid.GetRows()-1,0,"�ϡ���");
		m_grid.SetTextMatrix(m_grid.GetRows()-1,4,strSql);


	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CSubsidySet, CDialog)
    //{{AFX_EVENTSINK_MAP(CSubsidySet)
	ON_EVENT(CSubsidySet, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CSubsidySet, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSubsidySet::OnDblClickMshflexgrid1() 
{
	CStandardSubsidy di;
	long i,x=0;
	double dbSubsidy(0);

	if(di.DoModal() == IDOK){
		
		for(i=1 ; i< m_grid.GetRows()-1 ;i++ ){
			if( di.strKH == m_grid.GetTextMatrix(i,2 ) ) return;//����Ѿ����ڲ�����׼���˳�
			dbSubsidy+=atof(m_grid.GetTextMatrix(i,4) );
		}

		i=m_grid.GetRows();
		m_grid.AddItem(" ",_variant_t(i));

		m_grid.SetTextMatrix(i-1,x++,strKh);
		m_grid.SetTextMatrix(i-1,x++,strName);
		m_grid.SetTextMatrix(i-1,x++,di.strKH);
		m_grid.SetTextMatrix(i-1,x++,di.strName);
		m_grid.SetTextMatrix(i-1,x++,di.strSex);

		dbSubsidy+=atof(di.strSex); //ͳ�Ƴ��ܺ�
		m_grid.SetTextMatrix(i,0,"�� ��");
		di.strSex.Format("%.2f",dbSubsidy);
		m_grid.SetTextMatrix(i,4,di.strSex);

	}
}

void CSubsidySet::SetGridHead()
{
	CString HeadTitle[]={"����","����","����","��������","���"} ,strTmp;//�� 
	
	long  headWidth[]={1100,1000,00,3000,1000};
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));

	m_grid.SetFixedCols(2);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2){
			m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����к�
			m_grid.SetColAlignment(i,4);
		}
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //���ж���
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}

}

void CSubsidySet::OnOK() 
{
	CString strSql;

	try{
		HospitalConnect->BeginTrans();

		strSql.Format(" DELETE FROM LSQ_EMP_headship WHERE ds1='%s' ",strKh);
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		for(long i=1; i< m_grid.GetRows()-1  ; i++ )
		{
			strSql.Format("INSERT INTO lsq_emp_headship(ds1,ds2,d1,ds3) VALUES('%s',\
				'%s',SYSDATE,'%s' ) ",m_grid.GetTextMatrix(i,0),m_grid.GetTextMatrix(i,2),\
				LoginInformation.user );
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		}
		HospitalConnect->CommitTrans();

	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage() );
		HospitalConnect->RollbackTrans();
		return ;
	}
	strSql.Format("��ǰְ��( %s / %s )�����������óɹ�!!!!",strKh,strName);
	AfxMessageBox(strSql);
	CDialog::OnOK();
}

void CSubsidySet::OnClickMshflexgrid1() 
{
	MSG *pms;
	double db1,db2;
	CString strT1;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message == 0x205) {//0x202Ϊ������,0x205Ϊ����Ҽ���Ϣ
		if( m_grid.GetRow() !=0 && m_grid.GetRow() != m_grid.GetRows()-1 )
		{
			db1=atof(m_grid.GetTextMatrix(m_grid.GetRows()-1,4) ); //�ܺ�
			db2=atof(m_grid.GetTextMatrix(m_grid.GetRow(),4) );//���
			strT1.Format("%.2f",db1-db2);
			m_grid.SetTextMatrix(m_grid.GetRows()-1,4,strT1);
			m_grid.RemoveItem(m_grid.GetRow() );

		}
	}
	
}
/*
//��Ҫ���빤�ʵ�EXCEL�ļ�
	CString strFile,filter;
	filter="Microsoft Excels (*.xls)|*.xls||";
	CFileDialog fixls(true,"xls","",0,filter);
	if(fixls.DoModal()==IDCANCEL)return;
	strFile=fixls.GetPathName();
*/