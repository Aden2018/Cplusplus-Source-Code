// RelateCharge.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "RelateCharge.h"
#include "OperatChargeRelateFee.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRelateCharge dialog


CRelateCharge::CRelateCharge(CWnd* pParent /*=NULL*/)
	: CDialog(CRelateCharge::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRelateCharge)
	m_date1 = COleDateTime::GetCurrentTime();
	m_date2 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"黑体");
	preRow=0;
}


void CRelateCharge::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRelateCharge)
	DDX_Control(pDX, IDC_BUTTON_COST_QUERY, m_33);
	DDX_Control(pDX, IDC_COMBO2, c_combo2);
	DDX_Control(pDX, IDC_BUTTON_DELETE_ROW, m_267);
	DDX_Control(pDX, IDC_EDIT_NAME, c_name);
	DDX_Control(pDX, IDC_EDIT_BM, m_bm);
	DDX_Control(pDX, IDCANCEL, m_26);
	DDX_Control(pDX, IDOK, m_25);
	DDX_Control(pDX, IDC_BUTTON_TOEXCEL, m_24);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_23);
	DDX_Control(pDX, IDC_COMBO1, c_combo1);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_date2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRelateCharge, CDialog)
	//{{AFX_MSG_MAP(CRelateCharge)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_TOEXCEL, OnButtonToexcel)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ROW, OnButtonDeleteRow)
	ON_BN_CLICKED(IDC_BUTTON_COST_QUERY, OnButtonCostQuery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRelateCharge message handlers

void CRelateCharge::OnButtonAdd() 
{
	if(!theApp.AssertRole(ROLE_DECHARGE_RELATE))return;  //供养亲属报销功能

	COperatChargeRelateFee fee;

	fee.DoModal();
}

BOOL CRelateCharge::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_HEAD)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_HEAD)->SetWindowText("供养亲属费用报销查询");
	SetGridHead();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRelateCharge::OnOK() 
{
	
	UpdateData();

	CString strSql,strTemp;
	long cc,row,cols,i;
	double add[8]={0.,.0,.0,0,0,0,0,0};
	CONST int COMPUTE_COLS=6;
	m_grid.SetRedraw( false);

	SetGridHead();
	try{
		strSql.Format("SELECT rownum,l1.serial,l1.riqi,l1.oper_code,l1.oper_name,l1.dechargetype,l1.kahao1,\
			l2.xm,l2.xb,l2.xingzhi,to_char(sysdate,'yyyy')-to_char(l2.csriqi,'yyyy'),l3.卡号,l3.姓名, \
			to_char(sysdate,'yyyy')-to_char(l3.工作日期,'yyyy')+1,invoices,l1.all_expense,to_char(l1.scale*100,'99')||'%%',l1.scale_pay,\
			l1.account_pay,l1.all_pay,yuer \
			FROM lsq_relate_decharge l1,codeqingshu l2,职工基本情况表 l3 \
			WHERE l1.kahao1=l2.bm and l1.kahao2=l3.卡号 AND l1.riqi between to_date(%s,'yyyymmdd') \
			AND to_date(%s,'yyyymmdd') AND de_real !='1' ",m_date1.Format("%Y%m%d"),m_date2.Format("%Y%m%d") );
	
		if( c_combo1.GetCurSel() != CB_ERR && c_combo1.GetCurSel() != 0 ){
			c_combo1.GetLBText(c_combo1.GetCurSel(), strTemp);
			strSql+=" AND l1.dechargeType='"+strTemp+"'";
		}
	
		m_bm.GetWindowText(strTemp);
		if( !strTemp.IsEmpty() ) strSql+=" AND l1.kahao1 like '"+strTemp+"%'";
	
		c_name.GetWindowText(strTemp);
		if( !strTemp.IsEmpty() ) strSql+=" AND l2.xm like '"+strTemp+"%'";

		strSql+=" ORDER BY l1.riqi,l1.dechargetype ";
				
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		cols=recSet->GetFields()->Count;
		row=1;

		while(!recSet->adoEOF){
			i=0;
			for(cc=0;cc<cols;cc++)
			{
				
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(cc))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(cc))->Value);
				if( cc >=cols-6 && cc != cols-5 ){
					strTemp=strSql;
					strSql.Format("%.2f",atof(strTemp) );
				}
				m_grid.SetTextMatrix(row,cc,strSql);
				if(cc>=cols-COMPUTE_COLS)add[i++]+=atof(strSql);
			}
			row++;
			m_grid.AddItem(" ",_variant_t(row));
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
	
	

	m_grid.SetRow(row);
	m_grid.SetCol(0);
	m_grid.SetMergeCells(true);
	m_grid.SetMergeRow(row,1); 
	m_grid.SetCellBackColor(RGB(255,0,0));
	strSql.Format("   共有 %ld 条记录 ",row-1);
	m_grid.SetTextMatrix(row,0,"合计");	


	for(int count=1;count<cols;count++){
		m_grid.SetTextMatrix(row,count,strSql);	
		m_grid.SetCol(count);
		m_grid.SetCellBackColor(RGB(255,128,0));

	}

	for(i=0;i<COMPUTE_COLS;i++){
		strSql.Format("%.2f",add[i]);
		if ( i== 1) m_grid.SetTextMatrix(row,cols-COMPUTE_COLS+i,"");
		else	m_grid.SetTextMatrix(row,cols-COMPUTE_COLS+i,strSql);
	}
	
	m_grid.SetRedraw(true);
	preRow=0;

}

void CRelateCharge::SetGridHead()
{
	//                                                                      6
	CString HeadTitle[]={"序号","serial","报销日期","BM","操作员","类型","供养编码","被供养人",\
		"性别","性质","年龄",\
		"卡号","供养人","工龄","发票数","总费用","比例","比例费用","帐户支付","实报费用","帐户余额"	}; 
	//共 20 列                                                     17     18          19
	
	long  headWidth[]={600,0,1000,00,800,500,1000,800,400,1000,500,00,1000,500,600,1000,600,1000,\
		1000,1000,1000,11400,1400,1400,1400};
	
	
	m_grid.SetRows(2);
	m_grid.Clear();

	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0,col(0),row(0);
	m_grid.SetRow(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<6){
			m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		}
		if( count < 14 )
			m_grid.SetColAlignment((long)count,short(4));
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
	
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
		
	}
}

void CRelateCharge::OnButtonToexcel() 
{
	extern void ToExcel(CMSHFlexGrid * pg);

	if( MessageBox("是否确定要导出到 Excel 表格 ??? ","提示",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	ToExcel(&m_grid);
	
}

BEGIN_EVENTSINK_MAP(CRelateCharge, CDialog)
    //{{AFX_EVENTSINK_MAP(CRelateCharge)
	ON_EVENT(CRelateCharge, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CRelateCharge::OnClickMshflexgrid1() 
{
	long r1,i;
	CONST int COLS=12;
	r1=m_grid.GetRow();

	if(r1>=m_grid.GetRows()-1 || preRow== r1 )return;
	
//	m_grid.SetCol(0);
	m_grid.SetCol(5);
	m_grid.SetRow(preRow);
	UINT color=m_grid.GetCellBackColor();
	
	for( i=8;i<COLS;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(color);
	}
	m_grid.SetRow(r1);
	preRow=r1;
	for( i=8;i<COLS;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(RGB(255,0,0));
	}
		
	
}

void CRelateCharge::OnButtonDeleteRow() 
{
	if(! theApp.AssertRole(ROLE_DECHARGE_RELATE) )return;  //供养亲属报销功能

	if ( preRow != m_grid.GetRow()  ){
		MessageBox("请先选择要删除的行 !!!!","警告",MB_OK|MB_ICONWARNING);
		return;
	}
	CString strSql,strTemp;
	double dbTemp;
	try{
		strSql.Format("UPDATE lsq_relate_decharge SET de_real='1' WHERE serial='%s' ",\
			m_grid.GetTextMatrix(preRow,1) );
		HospitalConnect->BeginTrans();
	
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		
		dbTemp=atof(m_grid.GetTextMatrix(preRow,18)); //帐户支付
	
		if( dbTemp != 0.0 )
		{
			strSql.Format("UPDATE codeQingshu SET yuer=yuer+(%.2f) WHERE bm='%s' ",dbTemp,m_grid.GetTextMatrix(preRow,6) );
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		}

		HospitalConnect->CommitTrans();

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		HospitalConnect->RollbackTrans();
		return;
	}
	MessageBox("当前行删除成功!!!","提示",MB_OK|MB_ICONINFORMATION);
	OnOK();
}

void CRelateCharge::OnButtonCostQuery() 
{
	
}
