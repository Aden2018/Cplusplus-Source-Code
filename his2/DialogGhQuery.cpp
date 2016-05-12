// DialogGhQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "DialogGhQuery.h"
#include "ghList.h"
#include "queryRybm.h"
#include "ProgressIndicate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogGhQuery dialog


CDialogGhQuery::CDialogGhQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogGhQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogGhQuery)
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	m_sf = FALSE;
	//}}AFX_DATA_INIT
	strSFY="";
	strdoctorbm="";
}


void CDialogGhQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogGhQuery)
	DDX_Control(pDX, IDC_COMBO_EMP_TYPE, c_empType);
	DDX_Control(pDX, IDC_COMBO_STATUS, c_status);
	DDX_Control(pDX, IDC_EDIT_SFY, c_sfy);
	DDX_Control(pDX, IDC_BUTTON_SFY, m_342);
	DDX_Control(pDX, IDOK, m_3);
	DDX_Control(pDX, IDCANCEL, m_2);
	DDX_Control(pDX, IDC_BUTTON_DOCTOR, m_1);
	DDX_Control(pDX, IDC_EDIT_NAME, c_name);
	DDX_Control(pDX, IDC_EDIT_DOCTORNAME, c_doctorname);
	DDX_Control(pDX, IDC_COMBO_GHTYPE, c_type);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	DDX_Check(pDX, IDC_CHECK1, m_sf);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogGhQuery, CDialog)
	//{{AFX_MSG_MAP(CDialogGhQuery)
	ON_BN_CLICKED(IDC_BUTTON_DOCTOR, OnButtonDoctor)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_SFY, OnButtonSfy)
	ON_CBN_SELCHANGE(IDC_COMBO_GHTYPE, OnSelchangeComboGhtype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogGhQuery message handlers
const long COLS=4,CALC_START=9,CALC_END=16;

void CDialogGhQuery::OnOK() 
{


	CProgressIndicate pq;
	pq.pDialog= this;
	pq.pThreadFunction = QueryGhList;

	pq.DoModal();

}

BOOL CDialogGhQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	fontTitle.CreatePointFont(200,"宋体");
	GetDlgItem(IDC_STATIC_TITLE2)->SetFont(&fontTitle);
	c_status.SetCurSel(0);
	
	CString strSql;
	try{
		strSql.Format("select ds1,ds3 da from lsq_upgrade WHERE ds2='GH_TYPE' and n2=1 order by n1 " );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		c_type.ResetContent();
		arrGHType.RemoveAll();
		c_type.AddString("");
		arrGHType.Add("");
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt == VT_NULL ? "":recSet->GetFields()->GetItem(0L)->Value );
			c_type.AddString(strSql);
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(1L)->Value.vt == VT_NULL ? "":recSet->GetFields()->GetItem(1L)->Value );
			arrGHType.Add(strSql);

			recSet->MoveNext();
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}	
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogGhQuery::OnButtonDoctor() 
{
	CQueryRybm rybm;
	if(rybm.DoModal()==IDOK)// TODO: Add your control notification handler code here
	{
		c_doctorname.SetWindowText(rybm.strName);
		strdoctorbm=rybm.strNum;

	}
	else {
		strdoctorbm="";
		c_doctorname.SetWindowText("");
	}
}

void CDialogGhQuery::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
/*	CRect r1,r2;
	GetDlgItem(IDC_STATIC_TITLE2)->GetWindowRect(&r1);
	ScreenToClient(&r1);
	GetClientRect(&r2);

	dc.MoveTo(0,r1.bottom+5);
	dc.LineTo(r2.right,r1.bottom+5);
*/	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CDialogGhQuery::OnButtonSfy() 
{
	CQueryRybm rybm;
	if(rybm.DoModal()==IDOK)// TODO: Add your control notification handler code here
	{
		c_sfy.SetWindowText(rybm.strName);
		strSFY=rybm.strNum;

	}
	else {
		strSFY="";
		c_sfy.SetWindowText("");
	}
	
}

UINT CDialogGhQuery::QueryGhList(LPVOID ps)
{
	CGhList *pf=(CGhList*)theApp.pParentGrid.pGrid;
	CDialogGhQuery * pd =(CDialogGhQuery *) ((CProgressIndicate *) ps )->pDialog ;
	pd->UpdateData();
	pf->m_grid.SetRedraw(false);
	pf->SetGridHead();
	CString strSql,str1,strGhtype,strname;

	long row,col,i;
	double price(0),add[]={0,0,0,0,0,0,0,0,0,0,0};

	if( pd->c_type.GetCurSel()==CB_ERR || pd->c_type.GetCurSel() == 0 )strGhtype = "";
	else {
	//	pd->c_type.GetLBText(pd->c_type.GetCurSel(),strGhtype);
		strGhtype=pd->arrGHType[pd->c_type.GetCurSel()];

		if( strGhtype == "国前职工" ) strGhtype="建国前老工人";

	}
	pd->c_name.GetWindowText(strname);

	try{
		//共14列查询
		strSql.Format("SELECT DANJUHAO,RIQI,decode(substr(SICKBM,1), '男',' ','女',' ',sickbm) sickbm2,SICKNAME,DOCTORNAME,划价员名,收费员名,发药员名,\
			GHTYPE,GHF,CASH,MEDMONEY,TREATEMoney,MEDMONEY+TreateMONEY,PROFIT,Medmoney-profit FROM ITEMREGISTERTOU WHERE riqi BETWEEN to_date('%s','yyyymmdd') \
			and to_date('%s','yyyymmdd')  ",pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d"));
//AND 发药员 IS NOT NULL
		if(! pd->strdoctorbm.IsEmpty())strSql+=" AND doctor='"+pd->strdoctorbm+"'";
	
		if(!strname.IsEmpty())strSql+=" AND SICKNAME like '"+strname+"%'";
		
		if( pd->strSFY != "" ) strSql+=" AND 收费员='"+pd->strSFY+"'";
		
		if( pd->c_status.GetCurSel() == 0 /*已取药人员*/)
			strSql+=" AND 发药员>0 ";
		else if( pd->c_status.GetCurSel() == 1 /*未取药人员*/)
			strSql+=" AND 收费员>0 AND 发药员 is NULL ";
		
		CString strTmp1,strSql2;
	
		if(! strGhtype.IsEmpty()){
			strSql+=" AND GHTYPE='"+strGhtype+"'";
			if( strGhtype == "补充保险" ){
				if(  pd->c_empType.GetCurSel() == CB_ERR) strTmp1="";
				else
					pd->c_empType.GetLBText( pd->c_empType.GetCurSel(), strTmp1 );
				if( strTmp1.IsEmpty() ) strSql2=strSql;
				else
					strSql2.Format("SELECT a.* FROM  ( %s ) a,( SELECT * FROM 职工基本情况表 WHERE  工作性质='%s' ) b WHERE a.sickbm2 = b.卡号　 ",strSql ,strTmp1);
			}
			else strSql2=strSql;
		
		}
		else strSql2=strSql;
	
////////////////////////////////////////
		CString strSql001;
		strSql001.Format("select z.s2,z.r1,y.xb,y.xm,z.y2,z.n1,z.n1,z.n2,'家庭病床',0,0,0,0,0,0,0 from \
			lsq_reside_hos_huajia_complete z,lsq_reside_hos y where z.s1=y.serial AND z.r1 between to_date(\
			'%s000000','yyyymmddhh24miss') and to_date('%s235959','yyyymmddhh24miss') ",pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d") );

		if( pd->c_type.GetCurSel() == CB_ERR || pd->c_type.GetCurSel() == 0 )
			strSql.Format("  %s  union  %s  ",strSql2,strSql001); 
		else 
			strSql = strSql2;
////////////////////////////////////////


		strSql+=" ORDER by riqi,danjuhao";

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		double dd;
		unsigned int tx,bk;
		while(!recSet->adoEOF){
			col=0;
			price=0;
			for(i=0;i<16;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				if( i == 8 )
				{
					if(str1 == "建国前老工人" || str1 == "离休人员") //标注
					{
						if(str1 == "建国前老工人" )
							bk=RGB(0,128,192);
						
						else if( str1 == "离休人员")	
							bk=RGB(255,128,255);
						
						for( tx =9 ; tx< 15 ;tx ++ )
						{	
							pf->m_grid.SetRow(row);
							pf->m_grid.SetCol(tx);
							pf->m_grid.SetCellBackColor(bk);
							
						}
					}

					if( ! strTmp1.IsEmpty() )str1+="."+strTmp1;

				}
				if(i>=9 ){
					add[i-9]+=atof(str1);

				}
				if(i == 14 || i == 10){
					pf->m_grid.SetCol(i);
					pf->m_grid.SetRow(row);
					pf->m_grid.SetCellBackColor(RGB(248,135,244));
				}
				pf->m_grid.SetMergeRow(row,false);
				pf->m_grid.SetTextMatrix(row,col++,str1);
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
	pf->m_grid.SetMergeCells(1);
	pf->m_grid.SetMergeRow(row,1);

	////////////////////////
	pf->m_grid.SetRow(row);
	pf->m_grid.SetCol(1);
	pf->m_grid.SetCellBackColor(RGB(255,0,0));
	strSql.Format("   共有 %ld 条药品记录 ",row-1);

	pf->m_grid.SetTextMatrix(row,1,"合计");	
	pf->GetDlgItem(IDC_BUTTON_TO_EXCEL)->SetWindowText(strSql+"         [ 导入 Excel ]");
	for(long count=2;count<CALC_END;count++){
		pf->m_grid.SetCol(count);
		pf->m_grid.SetCellBackColor(RGB(255,128,0));
		if( count>=CALC_START ){
			str1.Format("%.2f",add[count-CALC_START]);
			pf->m_grid.SetTextMatrix(row,count,str1);	

		//	add[i-CALC_START]+=atof(str1); //从药品数量开始到利润共七列
		}
		else {
			pf->m_grid.SetTextMatrix(row,count,strSql);	
		}
	}
	for(count=CALC_END;count<CALC_END+7;count++){
	
		pf->m_grid.SetCol(count);
		pf->m_grid.SetCellBackColor(RGB(255,128,0));


	}
	

	if(pf->m_grid.GetRows()>2)
	{
		pf->m_grid.SetRow(1);
		pf->curRow=1;
		for( i=2;i<COLS;i++){
			pf->m_grid.SetCol(i);
			pf->m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}

	pf->m_grid.SetRedraw(true);
	
//	((CProgressIndicate *) ps )->ConnectFlag = 1;
	
//	pd->SendMessage(WM_CLOSE,NULL,NULL);
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

	pd->SendMessage(WM_CLOSE,NULL,NULL);
	
	
}

void CDialogGhQuery::OnSelchangeComboGhtype() 
{
	if( c_type.GetCurSel() == CB_ERR ) return;
	CString strTmp1;
	c_type.GetLBText( c_type.GetCurSel(),strTmp1);
	if( strTmp1== "补充保险") {
		GetDlgItem(IDC_STATIC_EMP_TYPE)->ShowWindow(SW_SHOW);
		c_empType.ShowWindow(SW_SHOW);
		if( c_empType.GetCount() == 0 ){

			CDialogMedXL::ReadName("SELECT distinct 工作性质　FROM 职工基本情况表 where 类别='参保' order by 工作性质",c_empType);
			c_empType.AddString("");
		}

	}
	else{
		GetDlgItem(IDC_STATIC_EMP_TYPE)->ShowWindow(SW_HIDE);
		c_empType.ShowWindow(SW_HIDE);
	}
	
}
