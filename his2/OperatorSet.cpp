// OperatorSet.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "OperatorSet.h"
#include "dialogMedxL.h"
#include "OtherDecharge.h"
#include "OperatorAdd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COperatorSet dialog


COperatorSet::COperatorSet(CWnd* pParent /*=NULL*/)
	: CDialog(COperatorSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(COperatorSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"����");
	strTitle="ҽԺ���ʹ����Ա����";
}


void COperatorSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COperatorSet)
	DDX_Control(pDX, IDC_COMBO1, combo1);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COperatorSet, CDialog)
	//{{AFX_MSG_MAP(COperatorSet)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDOK_ADD, OnAdd)
	ON_BN_CLICKED(IDBUTN_EXCEL, OnExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COperatorSet message handlers

BOOL COperatorSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	SetWindowText(strTitle);

	if( !CDialogMedXL::ReadName(gstrSql,combo1) ) {
		AfxMessageBox("��ȡ���ݳ���!!!");
		return false;
	}
//	combo1.SetCurSel(0);
	OnOK();
	
	CenterWindow();
	AnimateWindow(m_hWnd,300,AW_SLIDE|AW_HOR_POSITIVE);
	Invalidate();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COperatorSet::OnOK() 
{
	UpdateData();
	CString HeadTitle[]={"���","���ڿⷿ","����","����","ְ��","pass"} ,strTmp;//�� 
	
	long  headWidth[]={600,1600,1100,1200,1600,00,000,000,000,00,0,00,1400};
	
	m_grid.SetRedraw(false);
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(2);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(long count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<5 ){
			m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����к�
			m_grid.SetColAlignment(i,4);
		}
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //���ж���
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}	
	CString kfmc;
	combo1.GetLBText(combo1.GetCurSel(),kfmc);
	CString strSql;
	long cols,x(1);
	try{
		
		strSql.Format("select kfmc,rybm,name,attribute,pass from storeroom a,Operator b where a.kfbm=b.kfbm and KFMC='%s' \
			AND sfdel!='y' ORDER BY name ",kfmc);

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		while(!recSet->adoEOF){
			strSql.Format("%ld",x);
			m_grid.SetTextMatrix(x,0,strSql);
			for(count=0;count< cols;count++){
				
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(count)->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(count)->Value);
				m_grid.SetTextMatrix(x,count+1,strSql);
			}
			
			x++;
			m_grid.AddItem(" ",_variant_t(x));
			recSet->MoveNext();
		
		}
		recSet->Close();

		m_grid.SetTextMatrix(x,0,"�ϼ�");
		m_grid.SetRedraw(true);
	//	strSql.Format("����ѯ��: %ld ����¼",j-1);
	//	GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(strSql);

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		AfxMessageBox(strSql);
		return ;
	}		
		
}

BEGIN_EVENTSINK_MAP(COperatorSet, CDialog)
    //{{AFX_EVENTSINK_MAP(COperatorSet)
	ON_EVENT(COperatorSet, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	ON_EVENT(COperatorSet, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void COperatorSet::OnClickMshflexgrid1()  //ɾ������
{
	const int ENDLINES=2;
	if(m_grid.GetRows() == ENDLINES || m_grid.GetRow() == m_grid.GetRows()-1 )return;//�ж��Ƿ���Ҫ��ʾ��ݲ˵�

	MSG *pms;
	CString strT1,strT2;
	pms=(MSG*)GetCurrentMessage();

	
	if(pms->message == 0x205) {//0x202Ϊ������,0x205Ϊ����Ҽ���Ϣ
		strT1.Format("�Ƿ�Ҫɾ�� (%s / %s) ����",m_grid.GetTextMatrix(m_grid.GetRow(),1),m_grid.GetTextMatrix(m_grid.GetRow(),3) );
		if ( AfxMessageBox(strT1,MB_OKCANCEL)== IDCANCEL ) return;
		strT1.Format(" UPDATE operator SET sfdel='y' WHERE rybm='%s' ",m_grid.GetTextMatrix(m_grid.GetRow(),2) );
		if(!COtherDecharge::WriteSQL(strT1)){
			AfxMessageBox("ɾ��ʧ��!!");
			return;
		}
		OnOK();

	}
}

void COperatorSet::OnDblClickMshflexgrid1()  //���������޸�
{
	COperatorAdd di;
	long i=0;
	
	if( m_grid.GetRows()-1 == m_grid.GetRow() ){
		di.flag= 1; //����
		di.strTitle="�������������Ա";
		if(di.DoModal()==IDOK) OnOK();
		return;

	}else
	{
		di.flag=2; //�޸�
		di.strTitle="�޸����������Ա";
		//�ⷿ��,����,����,����,����
		for( i=0; i< 5; i++ )
			di.str[i]=m_grid.GetTextMatrix(m_grid.GetRow(),i+1);
		
		if( di.DoModal()==IDOK) OnOK();
		return;

	}
		
}


void COperatorSet::OnSelchangeCombo1() 
{
	OnOK();	
}

void COperatorSet::OnAdd() 
{
	COperatorAdd di;
		di.flag= 1; //����
		di.strTitle="�������������Ա";
		if(di.DoModal()==IDOK) OnOK();	
}

void COperatorSet::OnExcel() 
{
	
}
