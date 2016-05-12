// FormRkListQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "FormRkListQuery.h"
#include "FormRklist.h"
#include "CodeGysQuery.h"
#include "queryRybm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormRkListQuery dialog


CFormRkListQuery::CFormRkListQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CFormRkListQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFormRkListQuery)
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	strFactoryID="";
	strYwyID="";
}


void CFormRkListQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormRkListQuery)
	DDX_Control(pDX, IDC_EDIT_YPBM, c_editYpbm);
	DDX_Control(pDX, IDC_EDIT_RKY, c_editRky);
	DDX_Control(pDX, IDC_BUTTON_RKY, c_brk);
	DDX_Control(pDX, IDC_BUTTON_FACTORY, m_fa);
	DDX_Control(pDX, IDC_EDIT_FACTORY, c_editFactory);
	DDX_Control(pDX, IDC_EDIT_YWY, c_editYwy);
	DDX_Control(pDX, IDC_BUTTON_YWY, c_ywy);
	DDX_Control(pDX, IDOK, m_3);
	DDX_Control(pDX, IDCANCEL, m_2);
	DDX_Control(pDX, IDC_BUTTON_GYS, m_1);
	DDX_Control(pDX, IDC_COMBO2, c_combo2);
	DDX_Control(pDX, IDC_COMBO1, c_combo1);
	DDX_Control(pDX, IDC_EDIT_PY, c_py);
	DDX_Control(pDX, IDC_EDIT_GYS, c_gys);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormRkListQuery, CDialog)
	//{{AFX_MSG_MAP(CFormRkListQuery)
	ON_BN_CLICKED(IDC_BUTTON_GYS, OnButtonGys)
	ON_BN_CLICKED(IDC_BUTTON_FACTORY, OnButtonFactory)
	ON_BN_CLICKED(IDC_BUTTON_YWY, OnButtonYwy)
	ON_BN_CLICKED(IDC_BUTTON_RKY, OnButtonRky)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormRkListQuery message handlers

void CFormRkListQuery::OnOK() 
{
	CFormRkList * pf=(CFormRkList *)theApp.pParentGrid.pWnd;
	pf->SetGridHead();
	UpdateData();
	CString strSql,strTemp;
	long cc,row,i,cols;
	double add[9]={0.,.0,.0,0,0,0,0,0,0};

	pf->m_grid.SetRedraw(false); 
	try{
/*		strSql.Format("select b.danjuhao ,b.riqi,b.piaojuhao ,D.GONGMC,\
			b.业务员名 ,b.入库员名 ,c.mc,c.gg,c.dw,a.rq1,a.rq2,a.factory ,\
			a.sl , a.dj as jinjia,a.pdj as coach, a.selldj as sellDj ,\
			round(a.dj*a.sl,2) as allJInjia,round(a.pdj*a.sl,2) as AllCoach,\
			round(a.selldj*a.sl,2) as allselldj , round((a.pdj-a.dj)*a.sl,2) as preferential\
			from ITEMTI a,ITEMRKTOU b,MEDCODE c,CODEGYS d,STOREROOM e,\
			MEDDL f,MEDXL g  WHERE   a.danjuhao=b.danjuhao and a.ypbm=c.bm and b.kfbm=e.kfbm and \
			b.gongbm=d.gongbm and c.dlbm=g.dlbm and  c.xlbm=g.xlbm and g.dlbm=f.dlbm\
			and  b.riqi between to_date('%s','yyyymmdd') and \
			to_date('%s','yyyymmdd') ",m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d") );
*/
		strSql.Format("select b.danjuhao ,b.riqi,b.piaojuhao ,D.GONGMC,\
			b.业务员名 ,b.入库员名 ,c.mc,c.gg,c.dw,a.rq1,a.rq2,a.factory ,\
			a.sl , a.dj as jinjia,a.pdj as coach, a.selldj as sellDj ,\
			round(a.dj*a.sl,2) as allJInjia,round(a.pdj*a.sl,2) as AllCoach,\
			round(a.selldj*a.sl,2) as allselldj , round((a.pdj-a.dj)*a.sl,2) as preferential\
			from ITEMTI a,ITEMRKTOU b,MEDCODE c,CODEGYS d,STOREROOM e \
		    WHERE   a.danjuhao=b.danjuhao and a.ypbm=c.bm and b.kfbm=e.kfbm and \
			b.gongbm=d.gongbm and  b.riqi between to_date('%s','yyyymmdd') and \
			to_date('%s','yyyymmdd') ",m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d") );

		c_py.GetWindowText(strTemp);
	//	strTemp.Remove(' ');
		if(!strTemp.IsEmpty())strSql+=" and C.Py like '"+strTemp+"%'";
		c_gys.GetWindowText(strTemp);
		if(!strTemp.IsEmpty())strSql+=" and d.GONGMC='"+strTemp+"'";
		c_editFactory.GetWindowText(strTemp);
//		strTemp.Remove(' ');
		if(! strTemp.IsEmpty() ) strSql+=" AND a.factory ='"+strTemp+"'";
		c_editYwy.GetWindowText(strTemp);
//		strTemp.Remove(' ');
		if(! strTemp.IsEmpty() ) strSql+= " AND b.业务员名='"+strTemp+"'";
		
		c_editRky.GetWindowText(strTemp);
		if( ! strTemp.IsEmpty() ) strSql+=" AND b.入库员='"+strRkyID+"'";
	
		c_editYpbm.GetWindowText(strTemp);
//		strTemp.Remove(' ');
		if(! strTemp.IsEmpty() )strSql+=" AND c.bm like '"+strTemp+"%'";
		
		strSql+=" ORDER BY B.RIQI ";

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		cols=recSet->GetFields()->Count;
		double dX;
		while(!recSet->adoEOF){
			i=0;
			for(cc=0;cc<cols;cc++)
			{
				
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(cc))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(cc))->Value);
				if( cc > 12) {
					dX=atof(strSql);
					strSql.Format("%.2f",dX);

				}
				pf->m_grid.SetTextMatrix(row,cc,strSql);
				if(cc>=cols-8)add[i++]+=atof(strSql);
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
		return;
	}

	pf->m_grid.SetMergeRow(row,1);
	pf->m_grid.SetRow(row);
	pf->m_grid.SetCol(1);
	pf->m_grid.SetCellBackColor(RGB(255,0,0));
	strSql.Format("   共有 %ld 条药品记录 ",row-1);
	pf->m_grid.SetTextMatrix(row,1,"合计");	
	
	pf->GetDlgItem(IDC_BUTTON_TO_EXCEL)->SetWindowText(strSql+"         [ 导入 Excel ]");
	for(int count=2;count<cols;count++){
		pf->m_grid.SetTextMatrix(row,count,strSql);	
		pf->m_grid.SetCol(count);
		pf->m_grid.SetCellBackColor(RGB(255,128,0));

	}

	for(i=0;i<8;i++){
		strSql.Format("%.2f",add[i]);
		pf->m_grid.SetTextMatrix(row,cols-8+i,strSql);
	}

	pf->m_grid.SetRedraw(true);
	CDialog::OnOK();
}

void CFormRkListQuery::OnButtonGys() 
{
	CCodeGysQuery gys;
	if(gys.DoModal()==IDOK){
		c_gys.SetWindowText(gys.strName);
	
	}else c_gys.SetWindowText("");
		
}

BOOL CFormRkListQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect rt1,rtGys;
	GetDlgItem(IDC_EDIT_GYS)->GetWindowRect(rtGys);
	ScreenToClient(rtGys);

	GetDlgItem(IDC_COMBO1)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	rt1.right =rt1.left+ rtGys.right-rtGys.left ;
	GetDlgItem(IDC_EDIT_YWY)->MoveWindow(rt1);

	GetDlgItem(IDC_COMBO2)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	rt1.right =rt1.left+ rtGys.right-rtGys.left;
	GetDlgItem(IDC_EDIT_FACTORY)->MoveWindow(rt1);

	GetDlgItem(IDC_STATIC_3)->SetWindowText("业务员");
	GetDlgItem(IDC_STATIC_4)->SetWindowText("产地");
	// TODO: Add extra initialization here
	GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_YWY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_FACTORY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_YWY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_FACTORY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_RKY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_RKY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_YPBM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_5)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFormRkListQuery::OnButtonFactory() //选择产地信息
{
	CCodeGysQuery codegys;
	if(	codegys.DoModal() == IDOK)
	{
		strYwyID=codegys.strNum;
		strYwyName=codegys.strName;
	}
	else {
		strYwyID="";
		strYwyName="";

	}
	c_editFactory.SetWindowText(strYwyName);
}

void CFormRkListQuery::OnButtonYwy()  //选择业务员信息
{
	CQueryRybm rybm;
	if( rybm.DoModal() == IDOK)
	{
		strFactoryID=rybm.strNum;
		strFactoryName=rybm.strName;

	}
	else
	{
		strFactoryID="";
		strFactoryName="";
	}
	c_editYwy.SetWindowText(strFactoryName);
}

void CFormRkListQuery::OnButtonRky() //入库员
{
	CQueryRybm rybm;
	if( rybm.DoModal() == IDOK)
	{
		strRkyID=rybm.strNum;
		strRkyName=rybm.strName;

	}
	else
	{
		strRkyID="";
		strRkyName="";
	}
	c_editRky.SetWindowText(strRkyName);
	
}

void CFormRkListQuery::OnSelchangeCombo1() 
{
	CString strSql,str2;
	if( !(c_combo1.GetCurSel() == CB_ERR || c_combo1.GetCurSel() == 0 ) ){
		c_combo1.GetLBText(c_combo1.GetCurSel(),str2);
	}
	else return;

	try{
		strSql.Format("select kfbm from storeroom where kfmc='%s' ",str2); //有药品的库房
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			
			strCombo1Kfbm=(char*)_bstr_t(recSet->GetCollect("kfbm").vt==VT_NULL?" ":recSet->GetCollect("kfbm"));
		
		}
		recSet->Close();
		


	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}
}
