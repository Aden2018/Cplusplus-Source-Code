// SearchMed.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "SearchMed.h"
#include "FormMedList.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchMed dialog
const long COLS=10;
CSearchMed::CSearchMed(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchMed::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchMed)
	m_date2 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"宋体");
	strGysName="";
	strGysBm="";
}


void CSearchMed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchMed)
	DDX_Control(pDX, IDC_BUTTON_FACTORY, m_3);
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, IDCANCEL, m_1);
	DDX_Control(pDX, IDC_COMBO_KF, c_kf);
	DDX_Control(pDX, IDC_EDIT_SL, m_sl);
	DDX_Control(pDX, IDC_EDIT_FACTORY, m_factory);
	DDX_Control(pDX, IDC_EDIT_BM, m_bm);
	DDX_Control(pDX, IDC_COMBO_ORDER, c_order);
	DDX_Control(pDX, IDC_COMBO_COMPARE, c_compare);
	DDX_Control(pDX, IDC_COMBO_XL, c_comXL);
	DDX_Control(pDX, IDC_COMBO_DL, c_comDL);
	DDX_Control(pDX, IDC_EDIT_PY, m_py);
	DDX_Control(pDX, IDC_EDIT_MC, m_mc);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchMed, CDialog)
	//{{AFX_MSG_MAP(CSearchMed)
	ON_CBN_SELCHANGE(IDC_COMBO_DL, OnSelchangeComboDl)
	ON_BN_CLICKED(IDC_BUTTON_FACTORY, OnButtonFactory)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchMed message handlers

BOOL CSearchMed::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE2)->SetFont(&fontTitle);
	
	m_date2.SetDate(COleDateTime::GetCurrentTime().GetYear()+20,COleDateTime::GetCurrentTime().GetMonth(),COleDateTime::GetCurrentTime().GetDay());
	CString strSql;
	try{
		c_comDL.AddString("   ");
		strSql.Format("select dlmc from meddl ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetCollect("dlmc").vt==VT_NULL?" ":recSet->GetCollect("dlmc"));
			c_comDL.AddString(strSql);
			recSet->MoveNext();
		
		}
		recSet->Close();

		strSql.Format("SELECT NVL(KFMC,' ') as KFMC FROM STOREROOM ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		c_kf.AddString( "    ");
		
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetCollect("KFMC"));
			c_kf.AddString(strSql);
			recSet->MoveNext();
		
		}
		recSet->Close();


	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}	// TODO: Addextra ini	
	c_compare.SetCurSel(0); //default
	c_order.SetCurSel(0); //default
	UpdateData(false);
	CenterWindow();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchMed::OnOK() 
{
	CFormMedList * pf=(CFormMedList *) theApp.pParentGrid.p2;
	const int CALC_START=9,CALC_END=16;//需计算总额的开始列与结束列
	UpdateData();
	COleDateTime nowDate=COleDateTime::GetCurrentTime(),date1;
/*
	CString HeadTitle[]={"ID","FACTORYBM","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地","库存量","售价","进价","指导价","大类","小类","库房名"}; //共 13 列
*/
	long  i=0,col(0),row(0),count,cols;
	pf->SetGridHead();
/*	CString getTitle[]={"ID","GONGBM","BM","MC","GG","DW","RQ1","RQ2","GONGMC","SL",\
		"SELL_PRICE","JINJIA","COACH_PRICE","DLMC","XLMC","KFMC"};
*/
	pf->m_grid.SetRedraw(false);
	CString strSql,str1,strpy,strmc,strdl,strxl,strsel,strbm;
	double add[7]={0,0,0,0,0,0,0};
	m_py.GetWindowText(strpy);
	m_mc.GetWindowText(strmc);
	m_bm.GetWindowText(strbm);

//	strSql.Format("select * from V_MED_QUERY_DETAIL where py like '%s%%' and mc like '%s%%' ",strpy,strmc);

/*	strSql.Format("SELECT E.ID ,D.GONGBM,C.BM,C.MC,C.GG,C.DW,to_char(E.RQ1,'YYYY-MM-DD'),\
		to_char(E.RQ2,'YYYY-MM-DD'),D.GONGMC,E.SL ,E.JINJIA,E.SELL_PRICE, \
		E.COACH_PRICE,ROUND(E.JINJIA*E.SL,2),ROUND(E.SL*E.SELL_PRICE,2),\
		ROUND(E.SL*(E.SELL_PRICE-E.JINJIA),2),A.DLMC,B.XLMC ,F.KFMC \
		from medcode c,medlie e,codegys d,storeroom f,meddl a,medxl b \
		where a.dlbm=c.dlbm and  b.xlbm=c.xlbm and e.factorycode=d.gongbm and \
		e.ypbm=c.bm and e.kfbm=f.kfbm and a.dlbm=b.dlbm and sl!=0 ");
*/
	strSql.Format("SELECT E.ID ,D.GONGBM,C.BM,C.MC,C.GG,C.DW,to_char(E.RQ1,'YYYY-MM-DD'),\
		to_char(E.RQ2,'YYYY-MM-DD'),D.GONGMC,E.SL ,E.JINJIA,E.SELL_PRICE, \
		E.COACH_PRICE,ROUND(E.JINJIA*E.SL,2),ROUND(E.SL*E.SELL_PRICE,2),\
		ROUND(E.SL*(E.SELL_PRICE-E.JINJIA),2),c.DLbm,c.XLbm ,F.KFMC \
		from medcode c,medlie e,codegys d,storeroom f \
		where  e.factorycode=d.gongbm and \
		e.ypbm=c.bm and e.kfbm=f.kfbm  and sl!=0 ");
	
	
	strpy.Remove(' ');
	if(!strpy.IsEmpty())strSql+=" AND C.PY LIKE '"+strpy+"%'";
	strmc.Remove(' ');
	if(!strmc.IsEmpty())strSql+=" AND C.MC LIKE '"+strmc+"%'";
	strbm.Remove(' ');
	if(!strbm.IsEmpty())strSql+=" AND C.BM LIKE '"+strbm+"%'";

	if(c_comDL.GetCurSel() == CB_ERR || c_comDL.GetCurSel() == 0 ) strsel= "";
	else {
			c_comDL.GetLBText(c_comDL.GetCurSel(),str1);
			strsel.Format(" and  C.DLBM=(SELECT dlbm FROM meddl where DLMC='%s' ) ",str1);
			if(c_comXL.GetCurSel() == CB_ERR || c_comXL.GetCurSel() == 0);
			else {
				c_comXL.GetLBText(c_comXL.GetCurSel(),str1);
				strsel+="and c.xlbm=(SELECT XLBM From MEDXL where xlmc='"+str1+"' and medxl.dlbm=c.dlbm )";
			}

	}
	strSql+=strsel;

	float ta=0.0;
	m_sl.GetWindowText(str1);
	if(!str1.IsEmpty()){
		ta=atof(str1);

		if( ta!=0.0 ){
			str1.Format("%.2f",ta);
			c_compare.GetLBText(c_compare.GetCurSel(),strsel);
			strSql += " and sl"+strsel+str1;
		}
	}

	if(! strGysBm.IsEmpty() )strSql+=" and gongbm='"+strGysBm+"'";

	strsel.Format(" and rq2 < to_date('%s','yyyymmdd') ",m_date2.Format("%Y%m%d") );

	strSql+=strsel;

	if( c_kf.GetCurSel() == CB_ERR || c_kf.GetCurSel() == 0 );
	else {
		c_kf.GetLBText(c_kf.GetCurSel(),strsel);
		strSql+="  and KFMC='"+strsel+"'";

	}
	
	
	if(c_order.GetCurSel() == 0 || c_order.GetCurSel() == CB_ERR )strSql+=" order by bm ";
	else if(c_order.GetCurSel() == 1 ) strSql+=" order by kfmc ";
	else strSql+=" order by SL ";


	
	try{
		//选出药品数量大于0,且不过期的药品
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		
		row=1;
		cols=recSet->GetFields()->Count;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			for(i=0;i<cols;i++)
			{
			//	str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(getTitle[i])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(getTitle[i])));
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				if( i == 7 ) //有效期
				{
					date1.SetDate(atoi(str1.Left(4)),atoi(str1.Mid(5,2)),atoi(str1.Right(2)) );
					if( date1 < nowDate ){
						pf->m_grid.SetRow(row);
						pf->m_grid.SetCol(i+3);
						pf->m_grid.SetCellBackColor(RGB(255,128,128));

					}


				}
				if ( i>=10 && i<16 ){
					dX=atof(str1);
					str1.Format("%.2f",dX);

				}
				pf->m_grid.SetTextMatrix(row,col++,str1);
				if( i>=CALC_START && i<CALC_END )add[i-CALC_START]+=atof(str1); //从药品数量开始到利润共七列
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
	pf->m_grid.SetCol(3);
	pf->m_grid.SetCellBackColor(RGB(255,0,0));
	strSql.Format("   共有 %ld 条药品记录 ",row-1);
	pf->GetDlgItem(IDC_BUTTON_TO_EXCEL)->SetWindowText(strSql+"     [ 导出 Excel ]");
	pf->m_grid.SetTextMatrix(row,3,"合计");	
	for(count=4;count<CALC_END;count++){
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
	ShowWindow(SW_HIDE);

	if(pf->m_grid.GetRows()>2)
	{
		pf->m_grid.SetRow(1);
		pf->curRow=1;
		for( i=1;i<COLS;i++){
			pf->m_grid.SetCol(i);
			pf->m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
	pf->m_grid.SetRedraw(true);

}

void CSearchMed::OnCancel() 
{
	ShowWindow(SW_HIDE);	
}



void CSearchMed::OnSelchangeComboDl() 
{
	// TODO: Add your control notification handler code here
	CString strSql,str1;
	if(c_comDL.GetCurSel() != CB_ERR && c_comDL.GetCurSel() != 0 ){
		c_comDL.GetLBText(c_comDL.GetCurSel(),str1);
	}
	else return;
	while(c_comXL.DeleteString(0)!=CB_ERR);
	try{
		c_comXL.AddString("   ");
		strSql.Format("select xlmc from medxl,medDL where medxl.dlbm = meddl.dlbm and dlmc='%s' ",str1);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetCollect("xlmc").vt==VT_NULL?" ":recSet->GetCollect("xlmc"));
			c_comXL.AddString(strSql);
			recSet->MoveNext();
		
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}	

}

void CSearchMed::OnButtonFactory() 
{
	// TODO: Add your control notification handler code here
	CCodeGysQuery codegys;
	if(codegys.DoModal() == IDOK) 
	{
		strGysName=codegys.strName;
		strGysBm=codegys.strNum;
		m_factory.SetWindowText(strGysName);
	}
	else {

		strGysName="";
		strGysBm="";
		m_factory.SetWindowText(strGysName);


	}

}

void CSearchMed::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect r1,r2;
	GetDlgItem(IDC_STATIC_TITLE2)->GetWindowRect(&r1);
	ScreenToClient(&r1);
	GetClientRect(&r2);

	dc.MoveTo(0,r1.bottom+5);
	dc.LineTo(r2.right,r1.bottom+5);
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

HBRUSH CSearchMed::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if( pWnd->m_hWnd == GetDlgItem(IDC_STATIC_NOTIFY)->m_hWnd )
		pDC->SetTextColor(RGB(255,0,0) );
		
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
