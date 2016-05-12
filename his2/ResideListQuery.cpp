// ResideListQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "ResideListQuery.h"
#include "progressIndicate.h"
#include "resideList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResideListQuery dialog


CResideListQuery::CResideListQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CResideListQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResideListQuery)
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	m_radio = 0;
	//}}AFX_DATA_INIT
}


void CResideListQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResideListQuery)
	DDX_Control(pDX, IDCANCEL, m_2);
	DDX_Control(pDX, IDOK, m_1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	DDX_Radio(pDX, IDC_RADIO2, m_radio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResideListQuery, CDialog)
	//{{AFX_MSG_MAP(CResideListQuery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResideListQuery message handlers

void CResideListQuery::OnOK() 
{
	CProgressIndicate pq;
	pq.pDialog= this;
	pq.pThreadFunction = QueryResideList;

	pq.DoModal();
}

UINT CResideListQuery::QueryResideList(LPVOID ps)
{
	CResideList *pf=(CResideList*)theApp.pParentGrid.pGrid;
	CResideListQuery * pd =(CResideListQuery *) ((CProgressIndicate *) ps )->pDialog ;
	pd->UpdateData();
	pf->m_grid.SetRedraw(false);
	pf->SetGridHead();
	CString strSql,str1,strGhtype,strname;  

	long row,cols,i;
	double price(0),add[]={0,0,0,0,0,0,0,0,0,0,0};

	try{
		//共14列查询
		switch  ( pd->m_radio) 
		{
	
		case 1: //治疗中
	    	strSql.Format(" select serial , xm,xb,age,phone,work_addr,home_addr,ill_desc,doctorName,rq,d.bname,price,rec_name,a.rq2  from \
			  lsq_reside_hos  a,lsq_reside_bed d \
			where  a.bed_id=d.bcode and  rq between  to_date('%s000000','yyyymmddhh24miss') and  to_date('%s235959','yyyymmddhh24miss')  ",pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d"));
			
			break;
		case 2: //已出院
	    	strSql.Format(" select serial , xm,xb,age,phone,work_addr,home_addr,ill_desc,doctorName,rq,d.bname,price,rec_name,a.rq2  from \
			  lsq_reside_hos_complete  a,lsq_reside_bed d \
			where  a.bed_id=d.bcode and  rq between  to_date('%s000000','yyyymmddhh24miss') and  to_date('%s235959','yyyymmddhh24miss')  ",pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d"));
			
			break;
		default: //全部信息
		  strSql.Format("select serial , xm,xb,age,phone,work_addr,home_addr,ill_desc,doctorName,rq,d.bname,price,rec_name,a.rq2  from \
			(select * from lsq_reside_hos  \
				union \
			select * from lsq_reside_hos_complete ) a,lsq_reside_bed d \
			where  a.bed_id=d.bcode and  rq between  to_date('%s000000','yyyymmddhh24miss') and  to_date('%s235959','yyyymmddhh24miss')  ",pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d"));
		}


		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		
		row=1;
		cols=recSet->GetFields()->Count;
		CString strFmt;
		while(!recSet->adoEOF){
			strFmt.Format("%d",row);
			pf->m_grid.SetTextMatrix(row,0,strFmt);
			for(i=0;i<cols;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(i))->Value);
//				pf->m_grid.SetMergeRow(row,false);
				pf->m_grid.SetTextMatrix(row,i+1,str1);
			}
			row++;
			pf->m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
	
		return false;
	}	

//	pf->m_grid.SetMergeRow(row,1);

	pf->m_grid.SetRedraw(true);
	
//	((CProgressIndicate *) ps )->ConnectFlag = 1;
	
//	pd->SendMessage(WM_CLOSE,NULL,NULL);
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

	pd->SendMessage(WM_CLOSE,NULL,NULL);

}



BOOL CResideListQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	const CString strTitle="住院人员信息查询";
	SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&CHis2App::fontTitle);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
