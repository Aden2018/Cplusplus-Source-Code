// GenericStockMed.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "GenericStockMed.h"
#include "excel9.h"
#include "genericMedCode.h"
#include "ProgressIndicate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenericStockMed dialog


CGenericStockMed::CGenericStockMed(CWnd* pParent /*=NULL*/)
	: CDialog(CGenericStockMed::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGenericStockMed)
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	m_date3 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CGenericStockMed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGenericStockMed)
	DDX_Control(pDX, IDC_BUTTON_PRINT, c_print);
	DDX_Control(pDX, IDC_EDIT3, c_edit3);
	DDX_Control(pDX, IDC_EDIT1, c_edit1);
	DDX_Control(pDX, IDCANCEL, m_3);
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, IDC_BUTTON_EXCEL, m_1);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, m_date3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGenericStockMed, CDialog)
	//{{AFX_MSG_MAP(CGenericStockMed)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnButtonExcel)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenericStockMed message handlers

BOOL CGenericStockMed::OnInitDialog() 
{
	CDialog::OnInitDialog();
	fontTitle.CreatePointFont(180,"����");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

#define BK1 RGB(23,169,232)
#define BK2 RGB(244,196,251)
#define BK3 RGB(22,154,68)

void CGenericStockMed::OnOK()  //����ҩƷ�ɹ�����
{
//	{"ҩƷ����","ҩƷ����","���","��λ","����","��������","���","�ƻ�����"} //�� 8 ��

	CProgressIndicate pg;
	pg.pDialog=this;
	pg.pThreadFunction=QueryData;
	pg.DoModal();

}

void CGenericStockMed::SetGridHead()
{
	CString HeadTitle[]={"���","��Ӧ��","ҩƷ����","ҩƷ����","���","��λ","����","�ɹ�����","����","��������","�� ��","�ƻ�����"} ;//�� 8 ��
	
	long  headWidth[]={800,1400,900,1200,1200,400,1600,1200,1000,1000,1000,1000,1600,1300,1300,1300,0,1300,1300,1300,00,00,1400};
	
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetRedraw(false);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetRow(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<5)m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����кϲ�
//		if(count<4)m_grid.SetColAlignment(i,1);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //���ж���
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}

}


void CGenericStockMed::OnButtonExcel() 
{
	extern void ToExcel(CMSHFlexGrid * pg);

	if( MessageBox("�Ƿ�ȷ��Ҫ������ Excel ��� ??? ","��ʾ",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;

	ToExcel(&m_grid);

}

HBRUSH CGenericStockMed::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if( GetDlgItem(IDC_STATIC_NOTIFY)->m_hWnd == pWnd->m_hWnd || \
		GetDlgItem(IDC_STATIC_TITLE)->m_hWnd == pWnd->m_hWnd )
	{
		pDC->SetTextColor(RGB(255,0,0));

	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BEGIN_EVENTSINK_MAP(CGenericStockMed, CDialog)
    //{{AFX_EVENTSINK_MAP(CGenericStockMed)
	ON_EVENT(CGenericStockMed, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CGenericStockMed::OnDblClickMshflexgrid1() 
{
	theApp.pParentGrid.pGrid=&m_grid;
	CGenericMedCode med;
	med.DoModal();
	
}

UINT CGenericStockMed::QueryData(LPVOID ps)
{
	CGenericStockMed * pd=(CGenericStockMed * )((CProgressIndicate *)ps)->pDialog;

	pd->m_grid.SetRedraw(false);
	pd->SetGridHead();
	CString strSql,str1;
	long cols,row,i,col;
	pd->UpdateData();
	try{
		strSql.Format("SELECT gongmc,bm,mc,gg,dw,factory,riqi,dj,sl1,sl2,s3 FROM \
				(SELECT dlbm,xlbm ,bm,mc ,gg,dw,sl1,sl2,trunc((sl1-sl2)+9,-1) s3 \
				FROM ( SELECT sum(a.sl) as sl1 ,a.ypbm  as ypbm1 \
				FROM itemti a where a.riqi between to_date('%s','yyyymmdd') \
				AND to_date('%s','yyyymmdd') AND substr(danjuhao,1,1) in ('G','E') \
				group by a.ypbm ) c,  (SELECT sum(sl) as sl2,ypbm as ypbm2 from medlie group by ypbm )  d,medcode e \
				WHERE c.ypbm1 = d.ypbm2(+) and c.ypbm1=e.bm and sl1!=0 and trunc((sl1-sl2)+9,-1) >0 ) x1,v_six_months_infor x2 \
				WHERE x1.bm =x2.ypbm(+) ",\
				pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d") );

	 	
		strSql+=" ORDER BY dlbm,xlbm,mc " ;
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		cols=recSet->GetFields()->Count;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			str1.Format("%ld",row);
			pd->m_grid.SetTextMatrix(row,col++,str1);
			pd->m_grid.SetRow(row);
			pd->m_grid.SetCol(8);
			pd->m_grid.SetCellBackColor(BK1);
			pd->m_grid.SetCol(9);
			pd->m_grid.SetCellBackColor(BK2);
			for(i=0;i<cols;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				pd->m_grid.SetTextMatrix(row,col++,str1);
				
			//	if( i>=CALC_START && i<CALC_END )add[i-CALC_START]+=atof(str1); //��ҩƷ������ʼ����������
			}
			row++;
			pd->m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();
		pd->m_grid.SetRedraw(true);

		str1.Format("�ܼ�: ��ɹ� %ld ��ҩƷ",row-1 );
		pd->GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(str1);

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
	
		return false;
	}	
	pd->m_grid.SetRedraw(true);
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

}

void CGenericStockMed::OnButtonPrint() 
{
	
}

void CGenericStockMed::OnSelchangeCombo2() 
{
	
}
