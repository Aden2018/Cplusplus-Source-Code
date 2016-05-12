// HealthSearch.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "HealthSearch.h"
#include "progress.h"
#include "addHealth.h"
#include "Excel9.h"
#include "addHealthForModify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHealthSearch dialog
extern UINT progressIndication(LPVOID); 
//***************************************************************************
//* ����ѯ����,�ɶ��̲߳���
//*
//***************************************************************************
UINT Tsearch(LPVOID p)
{
	CHealthSearch *p2=(CHealthSearch *)((DoublePointer*)p)->pGrid;
	CQuery *p3=(CQuery*)((DoublePointer*)p)->pQuery;
	CString strBM,strBZ,strKH,strXM; //������,���� ,����,����
	
	p2->lRow=0; //����ǰ��ѡ��ȫ����λ
	p2->flagConti=0;
	CWinThread *th1=AfxBeginThread(progressIndication,p2);


	if(p3->m_bm.GetCurSel()==CB_ERR)strBM="";
	else p3->m_bm.GetLBText(p3->m_bm.GetCurSel(),strBM);
	if(p3->m_bz.GetCurSel()==CB_ERR)strBZ="";
	else p3->m_bz.GetLBText(p3->m_bz.GetCurSel(),strBZ);

	p3->m_kh.GetWindowText(strKH);
	strKH.TrimLeft();
	strKH.TrimRight();
	p3->m_xm.GetWindowText(strXM);
	strXM.TrimLeft();
	strXM.TrimRight();


	
	p2->m_grid.SetRows(2);
	p2->m_grid.Clear();
	p2->m_grid.SetRedraw(false);

	long j=0, i=0,x=0;


//	CString HeadTitle[]={"������","��������","����","����","�Ա�","�������","Ѫ��","Ѫѹ","����","���","����ʷ","�ڿƼ��",\
		"��Ƽ��","�۵׼��","���Ƽ��","�ιȱ�","���ܵ���","�ιȲ�",\
		"���ܵ���","��R-�Ȱ�","�ΰ׵���","�����ص�","������","�ո�Ѫ��",\
		"�ͺ�Ѫ��","������֬","���̴�","HBsAg","HBeAg","HBcAg","HBsAb","HBeAb","HBcAb",\
		"�ĵ���","X����","B�����","����","���ƽ���","age","workage","workdate"};
	//sag,eag,cag-->������
	//sag,eab,cab->С����
	CString HeadTitle[]={"������","��������","����","����","�Ա�","�������","Ѫ��","Ѫѹ","����","���","����ʷ","�ڿƼ��",\
		"��Ƽ��","�۵׼��","���Ƽ��","�ιȱ�","���ܵ���","�ιȲ�",\
		"���ܵ���","��R-�Ȱ�","�ΰ׵���","�����ص�","������","�ո�Ѫ��",\
		"����","������֬","���̴�","HBsAg","HBeAg","HBcAg","HBsAb","HBeAb","HBcAb",\
		"�ĵ���","X����","B�����","����","���ƽ���","age","workage","workdate","rq","TSGF","AFP","CEA","��ע"};
																					//����������
	long  headWidth[]={1400,1400,1200,1000,400,1200,600,900,600,600,1200,1200,\
		1200,1200,1200,600,600,600,\
		600,600,600,600,600,600,\
		600,600,600,400,400,400,400,400,400,\
		4200,4200,4200,4200,0,0,0,0,0,600,600,600,1200},cc;


	p2->m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	p2->m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	p2->m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	p2->m_grid.SetFixedCols(5);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)p2->m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����кϲ�
		p2->m_grid.SetColWidth(i,headWidth[count]);

//		p2->m_grid.SetRow(0);
//		p2->m_grid.SetCol(i);
//		p2->m_grid.SetColAlignment(i,4);//flexAlignCenterCenter 4 ��Ԫ������ݾ��С����ж���	

		p2->m_grid.SetTextArray(i++,HeadTitle[count]);
	}


	
	CString strSql;
	try{
		
		if(strBM=="���в���")strBM="";
		if(strBZ=="���а���")strBZ="";
		if(p3->m_bLastCheck){
			if(p3->m_bD3)strSql.Format("select * from v_tijian  e1 where \
				riqi=(select max(riqi) from tijian where e1.����=kahao ) and \
				a22='��' and a23='��' and a24 ='��' and riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd') and \
				������ like '%s%%' and �������� like '%s%%' and ���� like '%s%%' \
				and ���� like '%s%%' order by ������,��������,���� ,riqi",p3->m_date1.Format("%Y%m%d"),p3->m_date2.Format("%Y%m%d"),\
				strBM,strBZ,strXM,strKH);
		
			else if(p3->m_bX3)strSql.Format("select * from v_tijian  e1 where riqi=(select max(riqi) from tijian where e1.����=kahao ) \
				and a22='��' and a26='��' and a27='��' and riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd') \
				and ������ like '%s%%' and �������� like '%s%%' and ���� like '%s%%' and\
				���� like '%s%%' 	order by ������,��������,���� ,riqi",p3->m_date1.Format("%Y%m%d"),p3->m_date2.Format("%Y%m%d"),\
				strBM,strBZ,strXM,strKH);
			else
				strSql.Format("select * from v_tijian  e1 where riqi=(select max(riqi) from tijian where e1.����=kahao ) and \
				riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd') and ������ like '%s%%' and ��������  \
				like '%s%%' and ���� like '%s%%' and ���� like '%s%%' \
				order by ������,��������,���� ,riqi",p3->m_date1.Format("%Y%m%d"),p3->m_date2.Format("%Y%m%d"),\
				strBM,strBZ,strXM,strKH);

		}else 
		{
		//	strSql.Format("select * from v_tijian where ������ like '%s%%' and �������� like '%s%%' and ���� like '%s%%' and ���� like '%s%%' order by ������,��������,���� ,riqi",strBM,strBZ,strXM,strKH);
			if(p3->m_bD3)strSql.Format("select * from v_tijian  e1 where \
					a22='��' and a23='��' and a24 ='��' and riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd') and \
				������ like '%s%%' and �������� like '%s%%' and ���� like '%s%%' \
				and ���� like '%s%%' order by ������,��������,���� ,riqi",p3->m_date1.Format("%Y%m%d"),p3->m_date2.Format("%Y%m%d"),\
				strBM,strBZ,strXM,strKH);
			else if(p3->m_bX3)strSql.Format("select * from v_tijian  e1 where  \
				a22='��' and a26='��' and a27='��' and riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd') \
				and ������ like '%s%%' and �������� like '%s%%' and ���� like '%s%%' and\
				���� like '%s%%' order by ������,��������,���� ,riqi",p3->m_date1.Format("%Y%m%d"),p3->m_date2.Format("%Y%m%d"),\
				strBM,strBZ,strXM,strKH);
			else
				strSql.Format("select * from v_tijian  e1 where  riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd') and \
					������ like '%s%%' and �������� like '%s%%' and ���� like '%s%%' and ���� like '%s%%' \
				  order by ������,��������,���� ,riqi",p3->m_date1.Format("%Y%m%d"),p3->m_date2.Format("%Y%m%d"),\
				  strBM,strBZ,strXM,strKH);
		}
			
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(recSet->adoEOF){
			p3->GetDlgItem(IDOK)->EnableWindow(true);
		//	p2->flagConti=2;
			p2->m_grid.SetRedraw(true);
			recSet->Close();
			TerminateThread(th1->m_hThread,2);
		
		
			p2->GetDlgItem(IDC_STATIC_NOTI)->SetWindowText("  û�в鵽�κ���Ϣ!!!!");		
			return 3;
		}
		j=1,i=0;
		while(!recSet->adoEOF)
		{
			i++;
			recSet->MoveNext();
		} 

		p2->flagConti=1;
		p2->uint_AllRecords=i;
		i=0;
		recSet->MoveFirst();

		while(!recSet->adoEOF){
		
	//		p2->GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(	str1+ltoa(j,buff,10));
				
			p2->uint_records=j;
		
		
			for(cc=0;cc<recSet->GetFields()->Count  ;cc++) 
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(cc))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(cc))->Value);
				if(strSql=="��"){
					p2->m_grid.SetCol(cc);
					p2->m_grid.SetRow(j);
					p2->m_grid.SetCellBackColor(RGB(255,0,0));
				}
				p2->m_grid.SetTextMatrix(j,cc,strSql);


			}
			recSet->MoveNext();
			p2->m_grid.AddItem(" ",_variant_t(++j));

		
		}
		recSet->Close();
		p2->flagConti=2;

		p2->m_grid.SetRedraw(true);
		
		TerminateThread(th1->m_hThread,2);
	
		p2->m_grid.SetTextMatrix(j,0,"�ϼ�");

		strSql.Format("  ��ѯ��: %ld �˴�",j-1);
	
		p2->GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(strSql);		

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return 3;
	}
	p3->GetDlgItem(IDOK)->EnableWindow(true);

	return 2;


}
UINT Tsearch2(LPVOID p) //������� ��Ա��ѯ��
{
	CHealthSearch *p2=(CHealthSearch *)((DoublePointer*)p)->pGrid;
	CQuery *p3=(CQuery*)((DoublePointer*)p)->pQuery;
	CString strBM,strBZ,strKH,strXM; //������,���� ,����,����
	
	p2->lRow=0; //����ǰ��ѡ��ȫ����λ
	p2->flagConti=0;
	CWinThread *th1=AfxBeginThread(progressIndication,p2);


	if(p3->m_bm.GetCurSel()==CB_ERR)strBM="";
	else p3->m_bm.GetLBText(p3->m_bm.GetCurSel(),strBM);
	if(p3->m_bz.GetCurSel()==CB_ERR)strBZ="";
	else p3->m_bz.GetLBText(p3->m_bz.GetCurSel(),strBZ);

	p3->m_kh.GetWindowText(strKH);
	strKH.TrimLeft();
	strKH.TrimRight();
	p3->m_xm.GetWindowText(strXM);
	strXM.TrimLeft();
	strXM.TrimRight();


	
	p2->m_grid.SetRows(2);
	p2->m_grid.Clear();
	p2->m_grid.SetRedraw(false);

	long j=0, i=0,x=0;


	CString HeadTitle[]={"����","�Ա�","����","סַ","�绰","�������","Ѫ��","Ѫѹ","����","���","����ʷ","�ڿƼ��",\
		"��Ƽ��","�۵׼��","���Ƽ��","�ιȱ�","���ܵ���","�ιȲ�",\
		"���ܵ���","��R-�Ȱ�","�ΰ׵���","�����ص�","������","�ո�Ѫ��",\
		"����","������֬","���̴�","HBsAg","HBeAg","HBcAg","HBsAb","HBeAb","HBcAb",\
		"�ĵ���","X����","B�����","����","���ƽ���","age","workage","workdate","rq","TSGF","AFP","CEA","��ע"};																					//����������
	long  headWidth[]={1200,600,600,2200,1600,1200,600,900,600,600,1200,1200,\
		1200,1200,1200,600,600,600,\
		600,600,600,600,600,600,\
		600,600,600,400,400,400,400,400,400,\
		4200,4200,4200,4200,0,0,0,0,0,600,600,600,1200},cc;


	p2->m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	p2->m_grid.SetMergeCells(true); //�趨��Ԫ����Խ��кϲ�
	p2->m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	p2->m_grid.SetFixedCols(5);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)p2->m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����кϲ�
		p2->m_grid.SetColWidth(i,headWidth[count]);

//		p2->m_grid.SetRow(0);
//		p2->m_grid.SetCol(i);
//		p2->m_grid.SetColAlignment(i,4);//flexAlignCenterCenter 4 ��Ԫ������ݾ��С����ж���	

		p2->m_grid.SetTextArray(i++,HeadTitle[count]);
	}


	
	CString strSql;
	try{
		
		if(strBM=="���в���")strBM="";
		if(strBZ=="���а���")strBZ="";

		strSql.Format("select * from v_other_tijian  e1 where 	riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd')  \
				and rec_xm like '%s%%' 	order by riqi,rec_xm",p3->m_date1.Format("%Y%m%d"),p3->m_date2.Format("%Y%m%d"),\
				strXM);
/*		if(p3->m_bLastCheck){
			if(p3->m_bD3)strSql.Format("select * from v_tijian  e1 where \
				riqi=(select max(riqi) from tijian where e1.����=kahao ) and \
				a22='��' and a23='��' and a24 ='��' and riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd') and \
				������ like '%s%%' and �������� like '%s%%' and ���� like '%s%%' \
				and ���� like '%s%%' order by ������,��������,���� ,riqi",p3->m_date1.Format("%Y%m%d"),p3->m_date2.Format("%Y%m%d"),\
				strBM,strBZ,strXM,strKH);
		
			else if(p3->m_bX3)strSql.Format("select * from v_tijian  e1 where riqi=(select max(riqi) from tijian where e1.����=kahao ) \
				and a22='��' and a26='��' and a27='��' and riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd') \
				and ������ like '%s%%' and �������� like '%s%%' and ���� like '%s%%' and\
				���� like '%s%%' 	order by ������,��������,���� ,riqi",p3->m_date1.Format("%Y%m%d"),p3->m_date2.Format("%Y%m%d"),\
				strBM,strBZ,strXM,strKH);
			else
				strSql.Format("select * from v_tijian  e1 where riqi=(select max(riqi) from tijian where e1.����=kahao ) and \
				riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd') and ������ like '%s%%' and ��������  \
				like '%s%%' and ���� like '%s%%' and ���� like '%s%%' \
				order by ������,��������,���� ,riqi",p3->m_date1.Format("%Y%m%d"),p3->m_date2.Format("%Y%m%d"),\
				strBM,strBZ,strXM,strKH);

		}else 
		{
		//	strSql.Format("select * from v_tijian where ������ like '%s%%' and �������� like '%s%%' and ���� like '%s%%' and ���� like '%s%%' order by ������,��������,���� ,riqi",strBM,strBZ,strXM,strKH);
			if(p3->m_bD3)strSql.Format("select * from v_tijian  e1 where \
					a22='��' and a23='��' and a24 ='��' and riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd') and \
				������ like '%s%%' and �������� like '%s%%' and ���� like '%s%%' \
				and ���� like '%s%%' order by ������,��������,���� ,riqi",p3->m_date1.Format("%Y%m%d"),p3->m_date2.Format("%Y%m%d"),\
				strBM,strBZ,strXM,strKH);
			else if(p3->m_bX3)strSql.Format("select * from v_tijian  e1 where  \
				a22='��' and a26='��' and a27='��' and riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd') \
				and ������ like '%s%%' and �������� like '%s%%' and ���� like '%s%%' and\
				���� like '%s%%' order by ������,��������,���� ,riqi",p3->m_date1.Format("%Y%m%d"),p3->m_date2.Format("%Y%m%d"),\
				strBM,strBZ,strXM,strKH);
			else
				strSql.Format("select * from v_tijian  e1 where  riqi between to_date('%s','yyyymmdd') and to_date('%s','yyyymmdd') and \
					������ like '%s%%' and �������� like '%s%%' and ���� like '%s%%' and ���� like '%s%%' \
				  order by ������,��������,���� ,riqi",p3->m_date1.Format("%Y%m%d"),p3->m_date2.Format("%Y%m%d"),\
				  strBM,strBZ,strXM,strKH);
		}
*/			
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(recSet->adoEOF){
			p3->GetDlgItem(IDOK)->EnableWindow(true);
		//	p2->flagConti=2;
			p2->m_grid.SetRedraw(true);
			recSet->Close();
			TerminateThread(th1->m_hThread,2);
		
		
			p2->GetDlgItem(IDC_STATIC_NOTI)->SetWindowText("  û�в鵽�κ���Ϣ!!!!");		
			return 3;
		}
		j=1,i=0;
		while(!recSet->adoEOF)
		{
			i++;
			recSet->MoveNext();
		} 

		p2->flagConti=1;
		p2->uint_AllRecords=i;
		i=0;
		recSet->MoveFirst();

		while(!recSet->adoEOF){
		
	//		p2->GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(	str1+ltoa(j,buff,10));
				
			p2->uint_records=j;
		
		
			for(cc=0;cc<recSet->GetFields()->Count  ;cc++) 
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(cc))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(cc))->Value);
				if(strSql=="��"){
					p2->m_grid.SetCol(cc);
					p2->m_grid.SetRow(j);
					p2->m_grid.SetCellBackColor(RGB(255,0,0));
				}
				p2->m_grid.SetTextMatrix(j,cc,strSql);


			}
			recSet->MoveNext();
			p2->m_grid.AddItem(" ",_variant_t(++j));

		
		}
		recSet->Close();
		p2->flagConti=2;

		p2->m_grid.SetRedraw(true);
		
		TerminateThread(th1->m_hThread,2);
	
		p2->m_grid.SetTextMatrix(j,0,"�ϼ�");

		strSql.Format("  ��ѯ��: %ld �˴�",j-1);
	
		p2->GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(strSql);		

	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return 3;
	}
	p3->GetDlgItem(IDOK)->EnableWindow(true);

	return 2;


}
UINT progressIndication(LPVOID p2)
{
	CHealthSearch * p3=(CHealthSearch * )p2;
	CString str1="���ڴ����ݿ��в�ѯ����",str2;

	int i=0;
	while(p3->flagConti<1 ){
			str1+=">";
			i++;
			Sleep(50);
			if(i>15){
				str1="���ڴ����ݿ��в�ѯ����>>";
				i=0;
			}
			p3->GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(str1);
	 

	}
	
	str1.Format("������:%ld,���ڴ���:",p3->uint_AllRecords);
	i=0;
	while(p3->flagConti<2){
			
			Sleep(50);
			str2.Format("%ld",p3->uint_records);
			p3->GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(str1+str2);


	}
	return true;

}


CHealthSearch::CHealthSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CHealthSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHealthSearch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	backColor=RGB(58,110,165);
	staticBrush.CreateSolidBrush(backColor);
	flagQuery=false;
	lRow=0; //��¼��ǰ��ѡ�����
	selBackColor=RGB(222,111,111); //ѡ�еı���ɫ
	
}


void CHealthSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHealthSearch)
	DDX_Control(pDX, ID_PRINT, m_3333);
	DDX_Control(pDX, IDCANCEL, m_54);
	DDX_Control(pDX, IDOK, m_5);
	DDX_Control(pDX, ID_ADD, m_3);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHealthSearch, CDialog)
	//{{AFX_MSG_MAP(CHealthSearch)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_ADD, OnAdd)
	ON_BN_CLICKED(ID_PRINT, OnPrint)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FASTMENU_MODIFY,OnModify)
	ON_COMMAND(ID_FASTMENU_DELETE,OnDelete)
	ON_COMMAND(ID_FASTMENU_PRINT,OnFastMenuPrint)
	ON_COMMAND(ID_FASTMENU_SELECT,OnFastMenuSelect)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHealthSearch message handlers

void CHealthSearch::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	const int DISTANCE_TO_EDGE=10;
	int width,high;
	
	RECT r1,r2;
	GetDlgItem(IDC_STATIC_TITLE)->GetWindowRect(&r1);
	ScreenToClient(&r1);
	GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(0,0,cx,r1.bottom);

	GetDlgItem(IDC_STATIC_NOTI)->GetClientRect(&r1);
	GetDlgItem(IDC_STATIC_NOTI)->MoveWindow(0,cy-r1.bottom,r1.right,r1.bottom);
	
	GetDlgItem(IDOK)->GetWindowRect(&r1);
	ScreenToClient(&r1);

	GetDlgItem(IDC_MSHFLEXGRID1)->GetWindowRect(&r2);
	ScreenToClient(&r2);
	r2.right=cx;
	r2.bottom=cy-(r1.bottom-r1.top)*2;
	GetDlgItem(IDC_MSHFLEXGRID1)->MoveWindow(&r2);

	GetDlgItem(ID_PRINT)->GetWindowRect(&r1);
	width=r1.right-r1.left;
	high=r1.bottom-r1.top;
	ScreenToClient(&r1);
	r1.left=cx-width*4-DISTANCE_TO_EDGE-40;
	r1.top=cy-high-10;
	r1.right=r1.left+width;
	r1.bottom=r1.top+high;
	GetDlgItem(ID_PRINT)->MoveWindow(&r1);

	GetDlgItem(ID_ADD)->GetWindowRect(&r1);
//	width=r1.right-r1.left;
//	high=r1.bottom-r1.top;
	ScreenToClient(&r1);
	r1.left=cx-width*3-DISTANCE_TO_EDGE-30;
	r1.top=cy-high-10;
	r1.right=r1.left+width;
	r1.bottom=r1.top+high;
	GetDlgItem(ID_ADD)->MoveWindow(&r1);

	GetDlgItem(IDOK)->GetWindowRect(&r1);
//	width=r1.right-r1.left;
//	high=r1.bottom-r1.top;
	ScreenToClient(&r1);
	r1.left=cx-width*2-DISTANCE_TO_EDGE-20;
	r1.top=cy-high-10;
	r1.right=r1.left+width;
	r1.bottom=r1.top+high;
	GetDlgItem(IDOK)->MoveWindow(&r1);


	GetDlgItem(IDCANCEL)->GetWindowRect(&r1);
//	width=r1.right-r1.left;
//	high=r1.bottom-r1.top;
	ScreenToClient(&r1);
	r1.left=cx-width-DISTANCE_TO_EDGE-10;
	r1.top=cy-high-10;
	r1.right=r1.left+width;
	r1.bottom=r1.top+high;
	GetDlgItem(IDCANCEL)->MoveWindow(&r1);

	



}

BOOL CHealthSearch::OnInitDialog() 
{
	CDialog::OnInitDialog();

	fontTitle.CreatePointFont(220,"����");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	fontTitle.CreatePointFont(120,"����");
	GetDlgItem(IDC_STATIC_NOTI)->SetFont(&fontTitle);

	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("ְ�������Ϣ����");
	
	condiQuery.Create(IDD_DIALOG_QUERY,this);
//	condiQuery.UpdateData();

	flagQuery=true; //��Ϊ��ѯ�Ի����Ƿ񴴽��ı�־

	CString HeadTitle[]={"������","��������","����","����","�Ա�","�������","Ѫ��","Ѫѹ","����","���","����ʷ","�ڿƼ��",\
		"��Ƽ��","�۵׼��","���Ƽ��","�ιȱ�","���ܵ���","�ιȲ�",\
		"���ܵ���","��R-�Ȱ�","�ΰ׵���","�����ص�","������","�ո�Ѫ��",\
		"�ͺ�Ѫ��(���ᣩ","������֬","���̴�","HBsAg","HBeAg","HBcAg","HBsAb","HBeAb","HBcAb",\
		"�ĵ���","X����","B�����","����","���ƽ���"}; //�ֹ�38��

	long  headWidth[]={1400,1400,1200,1000,400,1200,600,900,600,600,1200,1200,\
		1200,1200,1200,600,600,600,\
		600,600,600,600,600,600,\
		600,600,600,400,400,400,400,400,400,\
		1200,1200,1200,1200,1200,0,0},i=0;


	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(5);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// ǰ6�е�Ԫ����кϲ�
		m_grid.SetColWidth(i,headWidth[count]);

//		p2->m_grid.SetRow(0);
//		p2->m_grid.SetCol(i);
//		p2->m_grid.SetColAlignment(i,4);//flexAlignCenterCenter 4 ��Ԫ������ݾ��С����ж���	

		m_grid.SetTextArray(i++,HeadTitle[count]);
	}
	ShowWindow(SW_MAXIMIZE);

	m_3333.backColor2=m_3.backColor2=m_5.backColor2=m_54.backColor2=backColor;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CHealthSearch::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->m_hWnd==GetDlgItem(IDC_STATIC_TITLE)->m_hWnd){
		pDC->SetBkMode(TRANSPARENT);

		pDC->SetTextColor(RGB(255,255,128));
		
	}
	else if (pWnd->m_hWnd==GetDlgItem(IDC_STATIC_NOTI)->m_hWnd){
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,251,0));
	
	}
	// TODO: Change any attributes of the DC here
	return (HBRUSH)staticBrush.GetSafeHandle();
	
	// TODO: Return a different brush if the default is not desired
//	return hbr;
}

void CHealthSearch::OnOK() 
{

	
	condiQuery.pParent.pGrid=(LPVOID)this;
	

	condiQuery.SetWindowPos(&wndTop,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE  );
	
	condiQuery.ShowWindow(SW_SHOW);

}

void CHealthSearch::OnCancel() 
{
	// TODO: Add extra cleanup here

	if(flagQuery)condiQuery.DestroyWindow();
	
	CDialog::OnCancel();
}

void CHealthSearch::OnAdd() 
{
//	AfxMessageBox("���ְ�������Ϣ...");
//	ShowWindow(SW_HIDE);
	if(!theApp.AssertRole(ROLE_BODYCHECK_ADD))return ;	
	CAddHealth h2;
	h2.DoModal();
//	ShowWindow(SW_SHOW);
	
}

BEGIN_EVENTSINK_MAP(CHealthSearch, CDialog)
    //{{AFX_EVENTSINK_MAP(CHealthSearch)
	ON_EVENT(CHealthSearch, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CHealthSearch, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CHealthSearch::OnClickMshflexgrid1() 
{

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message==0x205){ //0x202Ϊ������,0x205Ϊ����Ҽ���Ϣ
		if(!lRow)return;

		CMenu me2;
		me2.CreatePopupMenu();
		me2.AppendMenu(0,ID_FASTMENU_MODIFY,"��ѯ�޸ĸ�������");
		me2.AppendMenu(MF_SEPARATOR,0,"");
		me2.AppendMenu(0,ID_FASTMENU_DELETE,"ɾ����ǰ��������");
		me2.AppendMenu(MF_SEPARATOR,0,"");
		me2.AppendMenu(0,ID_FASTMENU_PRINT,"��ӡ��������");
		me2.AppendMenu(MF_SEPARATOR,0,"");
		me2.AppendMenu(0,ID_FASTMENU_SELECT,"ȫ����ӡ");


		CPoint pt;
		GetCursorPos(&pt);
		me2.TrackPopupMenu(TPM_RIGHTBUTTON,pt.x,pt.y,this);
	}
    else {
		long col=m_grid.GetCol();
		m_grid.SetCol(1);
		
		COLORREF oldColor=m_grid.GetCellBackColor();
		m_grid.SetCol(4);
		COLORREF curColor=m_grid.GetCellBackColor();
		long count=m_grid.GetRows();
		long curRow=m_grid.GetRow();
		if(curRow==count-1)return;
		//�ָ�������ѡ�е���

		if(lRow<count-1){
			m_grid.SetRow(lRow);
			for(int i=2;i<5;i++){
				m_grid.SetCol(i);
				m_grid.SetCellBackColor(oldColor);
			}
		}
		m_grid.SetRow(curRow); //����ǰ��ѡ��
		if(oldColor==curColor)
			for(int i=2;i<5;i++){
				m_grid.SetCol(i);
				m_grid.SetCellBackColor(selBackColor);
			}
		else 
			for(int i=2;i<5;i++){
				m_grid.SetCol(i);
				m_grid.SetCellBackColor(oldColor);
			}

		m_grid.SetCol(col);
		lRow=curRow;
	}
}

void CHealthSearch::OnDelete()
{
	if(!theApp.AssertRole(ROLE_BODYCHECK_DELETE))return ;	
	CString strSql;
	if(lRow==0){
		AfxMessageBox("����ѡ��Ҫɾ������...");
		return;
	}
	
	try{
		strSql.Format("delete from tijian where kahao='%s' and riqi=to_date('%s','yyyy-mm-dd') ",m_grid.GetTextMatrix(lRow,2),m_grid.GetTextMatrix(lRow,5));

		HospitalConnect->BeginTrans();
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();

	}
	catch(_com_error e)
	{
		AfxMessageBox("ɾ�����ִ���,���������������ٳ���ɾ��...");
		HospitalConnect->RollbackTrans();



	}
	m_grid.RemoveItem(lRow);
	AfxMessageBox("�ɹ�ɾ���˵�ǰ��ѡ��¼...");

}
/*****************************************************************************/
//   ��������:2005-8-18 19:15
//	 ����:������
//	 �޸�Ŀ��:
//		 ԭ����x���b�������ڵ���޸�ʱ���ֵߵ�,�ֵ�������,����ԭ��ϵ�ӱ����
//	 ��ȡ������
//   �޸ĺ���:void CHealthSearch::OnModify()
//-----------------------------------------------------------------------------

/*****************************************************************************/
void CHealthSearch::OnModify()
{
// AfxMessageBox("Modify menu...");
/*
	CString HeadTitle[]={"������","��������","����","����","�Ա�","�������","Ѫ��","Ѫѹ","����","���","����ʷ","�ڿƼ��",\
		"��Ƽ��","�۵׼��","���Ƽ��","�ιȱ�","���ܵ���","�ιȲ�",\
		"���ܵ���","��R-�Ȱ�","�ΰ׵���","�����ص�","������","�ո�Ѫ��",\
		"�ͺ�Ѫ��","������֬","���̴�","HBsAg","HBeAg","HBcAg","HBsAb","HBeAb","HBcAb",\
		"�ĵ���","X����","B�����","����","���ƽ���"};
*/
	if(!theApp.AssertRole(ROLE_BODYCHECK_MODIFY))return ;	
	CAddHealthForModify heal;

	heal.str[0]=m_grid.GetTextMatrix(lRow,3);
	heal.str[1]=m_grid.GetTextMatrix(lRow,4);
	heal.str[2]=m_grid.GetTextMatrix(lRow,0);
	heal.str[3]=m_grid.GetTextMatrix(lRow,1);
	heal.str[4]=m_grid.GetTextMatrix(lRow,38); // ����
	heal.str[5]=m_grid.GetTextMatrix(lRow,39); //����
	
	heal.m_xueYa = m_grid.GetTextMatrix(lRow,7);
	heal.m_tiZong = m_grid.GetTextMatrix(lRow,8);
	heal.m_high = m_grid.GetTextMatrix(lRow,9);
	heal.m_story = m_grid.GetTextMatrix(lRow,10);
	heal.m_leiKe = m_grid.GetTextMatrix(lRow,11);
	heal.m_weKe = m_grid.GetTextMatrix(lRow,12);
	heal.m_eye = m_grid.GetTextMatrix(lRow,13);
	heal.m_women = m_grid.GetTextMatrix(lRow,14);
	heal.m_1 = m_grid.GetTextMatrix(lRow,15);
	heal.m_2 = m_grid.GetTextMatrix(lRow,16);
	heal.m_3 = m_grid.GetTextMatrix(lRow,17);
	heal.m_4 = m_grid.GetTextMatrix(lRow,18);
	heal.m_5 = m_grid.GetTextMatrix(lRow,19);
	heal.m_6 = m_grid.GetTextMatrix(lRow,20);
	heal.m_7 = m_grid.GetTextMatrix(lRow,21);
	heal.m_8 = m_grid.GetTextMatrix(lRow,22);
	heal.m_9 = m_grid.GetTextMatrix(lRow,23);
	heal.m_10 = m_grid.GetTextMatrix(lRow,24);
	heal.m_11 = m_grid.GetTextMatrix(lRow,25);
	heal.m_12 = m_grid.GetTextMatrix(lRow,26);
	heal.m_xinDian =m_grid.GetTextMatrix(lRow,33);
	heal.m_B = m_grid.GetTextMatrix(lRow,35);   //B��
	heal.m_X = m_grid.GetTextMatrix(lRow,34);   //X��
	heal.m_result =m_grid.GetTextMatrix(lRow,36);
	heal.m_suggest =m_grid.GetTextMatrix(lRow,37);
//	m_comment = _T("");
	heal.m_strEdit0=m_grid.GetTextMatrix(lRow,42);//��������һ
	heal.m_strEdit1=m_grid.GetTextMatrix(lRow,43);// ��
	heal.m_strEdit2=m_grid.GetTextMatrix(lRow,44);// ��

	heal.m_comment=m_grid.GetTextMatrix(lRow,45);//��ע
	heal.m_kahao = m_grid.GetTextMatrix(lRow,2);
	heal.xuexin=m_grid.GetTextMatrix(lRow,6);
	for(int i=0;i<6;i++){
		heal.gan[i]=m_grid.GetTextMatrix(lRow,27+i);
	}

	heal.riqi=m_grid.GetTextMatrix(lRow,5);
	
	if(heal.DoModal()==IDOK){
		AfxBeginThread(Tsearch,&condiQuery.pParent);


	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//* �����Excel
//* ����ǰѡ����а���ǰ˳�������EXCEL�е�ԭʼ���ݱ���,������Excel�ĺ���д�ӡ����
//*
////////////////////////////////////////////////////////////////////////////////////////////////////

void CHealthSearch::OnPrintSelect() //���˴�ӡ����
{
	if(!theApp.AssertRole(ROLE_BODYCHECK_PRINT))return ;	

	if(lRow==0)return;
	BeginWaitCursor();
	_Application app;
	COleVariant vOpt(DISP_E_PARAMNOTFOUND,VT_ERROR);
	app.CreateDispatch("excel.application");
	if(!app){
		AfxMessageBox("��ע��ϵͳ�б���װ��EXCEL97 ���� EXCEL2000 ,����˹��ܲ���ʹ��...");
		return;
	}
	
	Workbooks books=app.GetWorkbooks();
	
	CString strFileName,strLocate;
	strFileName.Format("%s",LoginInformation.path);
	strFileName+="book_p.xls";

	_Workbook book=books.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);

	
	Worksheets sheets=book.GetWorksheets();
	_Worksheet sheet=sheets.GetItem(COleVariant((short)1)); //ԭʼ���ݱ�
	


	Range vRange;
	app.SetVisible(true);
	
	for(int i=0; i< m_grid.GetCols(0) ; i++ )
	{
		strLocate.Format("A%d",i+1);
		(Range(sheet.GetRange(COleVariant( strLocate),COleVariant(strLocate)))).SetValue(COleVariant(m_grid.GetTextMatrix(lRow,i)));


	}
	
/*	
	

	
	PageSetup pageinfo=sheet.GetPageSetup();
	str1.Format("��&pҳ");
	pageinfo.SetCenterFooter(str1);
	pageinfo.SetPrintTitleRows("$3:$3");
	pageinfo.SetCenterHorizontally(true);
//	sheet.PrintPreview(_O((short)1));
*/
/*	sheet.PrintOut(vOpt,vOpt,COleVariant((short)1),vOpt,vOpt,vOpt,vOpt,vOpt);
	
	sheet.ReleaseDispatch();

	sheets.ReleaseDispatch();
//	book.Close(_O((short)0),_O("c:\\tt.xls"),vOpt); //�ر�EXCEL
	book.Close(COleVariant((short)0),vOpt,vOpt); //�ر�EXCEL,�������ļ�

	book.ReleaseDispatch();
	books.Close();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	app.Quit();
	EndWaitCursor();
	
*/
	app.Run(COleVariant("thisWorkBook.PrintSheet"),vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
		vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
		vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt );

	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	books.Close();
	app.ReleaseDispatch();	
	app.Quit();

	EndWaitCursor();


}


void CHealthSearch::OnPrint() //����Excel
{

	extern void ToExcel(CMSHFlexGrid * pg);
	if( MessageBox("�Ƿ�ȷ��Ҫ������ Excel ��� ??? ","��ʾ",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	ToExcel(&m_grid);

}

void CHealthSearch::OnFastMenuPrint()
{
	OnPrintSelect();
}

void CHealthSearch::OnFastMenuSelect() //ȫ����ӡ
{
	if(!theApp.AssertRole(ROLE_BODYCHECK_PRINT))return ;	

	
	_Application app;
	COleVariant vOpt(DISP_E_PARAMNOTFOUND,VT_ERROR);
	app.CreateDispatch("excel.application");
	if(!app){
		AfxMessageBox("��ע��ϵͳ�б���װ��EXCEL97 ���� EXCEL2000 ,����˹��ܲ���ʹ��...");
		return;
	}
	
	Workbooks books=app.GetWorkbooks();
	
	CString strFileName,strLocate;
	strFileName.Format("%s",LoginInformation.path);
	strFileName+="book_p.xls";

	_Workbook book=books.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);

	
	Worksheets sheets=book.GetWorksheets();
	_Worksheet sheet=sheets.GetItem(COleVariant((short)1));

	Range vRange;
	app.SetVisible(true);
	
	for(int x=1; x< m_grid.GetRows()-1 ; x++){

		for(int i=0; i< m_grid.GetCols(0) ; i++ )
		{
			strLocate.Format("A%d",i+1);
			(Range(sheet.GetRange(COleVariant( strLocate),COleVariant(strLocate)))).SetValue(COleVariant(m_grid.GetTextMatrix(lRow,i)));
			
			
		}

		app.Run(COleVariant("thisWorkBook.Print_all"),vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
			vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
			vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt ); //���ô�ӡ���˳���

	}
	


		
		

	sheet.ReleaseDispatch();
	
	sheets.ReleaseDispatch();
//	book.Close(_O((short)0),_O("c:\\tt.xls"),vOpt); //�ر�EXCEL
	book.Close(COleVariant((short)0),vOpt,vOpt); //�ر�EXCEL,�������ļ�
	
	book.ReleaseDispatch();
	books.Close();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	app.Quit();
	

	EndWaitCursor();
	
}

void CHealthSearch::OnDblClickMshflexgrid1() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}
