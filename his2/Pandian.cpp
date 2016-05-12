// Pandian.cpp: implementation of the CPandian class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "Pandian.h"
#include "medStockList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPandian::CPandian()
{

}

CPandian::~CPandian()
{

}

BOOL CPandian::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	CString strSql;
	try{
		strSql.Format("select distinct(kfmc) from storeroom  ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t(recSet->GetCollect("kfmc").vt==VT_NULL?" ":recSet->GetCollect("kfmc"));
			c_getKf.AddString(strSql);
			recSet->MoveNext();

		
		}
		recSet->Close();

		strSql.Format("select distinct to_char(sysdate,'yyyymmddhh24miss') da from dual" );
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		
		if(!recSet->adoEOF){
			
			strSql=(char*)_bstr_t (recSet->GetCollect("da"));
			m_zktou='P';
			m_zktou+=strSql+LoginInformation.user_code;
			
		}
		recSet->Close();
		c_danjuhao.SetWindowText(m_zktou);
		m_curKf.SetWindowText(LoginInformation.kfmc);


	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		

	CRect r1(0,0,0,0);
	editCtrl.Create(WS_CHILD,r1,this,T_EDIT_YPZK);

	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","售价","进价","指导价","盈亏数","库房","KFBM"}; //共16列
	long  headWidth[]={0,00,2000,1600,600,0,1400,0,1600,1000,000,0,0,1200,1400,0};


	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetMergeCol(14,true);

	m_grid.SetFixedCols(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	

	
	SetWindowText("药品盘点操作");
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("药品盘点操作");
	GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_GET_RYMC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_RYBM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_CUR_KF)->ShowWindow(SW_HIDE);

	CRect rt1;
	GetDlgItem(IDC_EDIT_CUR_KF)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	GetDlgItem(IDC_MSHFLEXGRID2)->GetWindowRect(r1);
	
	ScreenToClient(r1);
	r1.top -= rt1.bottom-rt1.top;
	GetDlgItem(IDC_MSHFLEXGRID2)->MoveWindow(r1);


	return TRUE;  // return TRUE unless you set the focus to a control

}

void CPandian::OnSearch()
{
	CMedStockList medlist;
	if( c_getKf.GetCurSel() == CB_ERR ){
		AfxMessageBox("请先选择要盘点的库房...");
		return;
	}
	theApp.pParentGrid.pGrid=&m_grid;
	GetDlgItem(IDC_COMBO_GET_KF)->GetWindowRect(medlist.r1);
	medlist.flagMoveKF=112; //作为盘点时用,搜寻所有库房药品
	medlist.strSelKF= m_getKfbm;
	flagPANDIAN=888; //盘点时不区分药品数量
	c_getKf.GetLBText(c_getKf.GetCurSel(),medlist.strSelKfName);
	medlist.DoModal();

}

void CPandian::OnOK()
{
	UpdateData();
	CString strSql,danjuhao,ywy,str[20];

	c_getRymc.GetWindowText(ywy);
	c_danjuhao.GetWindowText(danjuhao);



	long rows=m_grid.GetRows()-2; //得到药品行数
	if( 0 == rows)return;
	try{
		HospitalConnect->BeginTrans();

		strSql.Format("insert into ItemPandianTou (danjuhao,riqi,KFBM,OPERATOR ) values('%s',TRUNC(SYSDATE,'dd'),'%s','%s' ) ",\
			danjuhao,LoginInformation.user_code,LoginInformation.user); //KFBM 现改用为操作人员 编码
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		for(long i=0;i<rows;i++){
			str[0]=m_grid.GetTextMatrix(i+1,1/*药品编码*/);
			str[1]=LoginInformation.kfbm;/*库房编码*/
			str[4]=m_grid.GetTextMatrix(i+1,0/*药品ID*/);
			str[3]=m_grid.GetTextMatrix(i+1,15);//药品所在库房编码 //m_getKfbm; //目的库房编码

//	CString HeadTitle[]={"ID","药品编码","药品名称","规格","单位","生产期"(5),"有效期",\
		"产地BM","产地"(8),"库存量","售价"(10),"进价"(11),"指导价","盈亏数","库房","KFBM"}; //共14列
//	long  headWidth[]={0,00,2000,1600,600,0,1400,0,1600,1000,000,0,0,1200,1400,0};

			for(int x=5;x<14;x++)
				str[x]=m_grid.GetTextMatrix(i+1,x);
	      //自动生成药品  ID	
///////////////////////////////////////////////////////////////////////////////			
		
			strSql.Format("UPDATE MEDLIE set SL=SL+(%.2f) where ID='%s' ",atof(str[13]),str[4]);
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

			strSql.Format("insert into ITEMTI (id,sl,dj,selldj,riqi,danjuhao,rq1,rq2,ypbm,kfbm,factory ) values(%s,\
				%.2f,%.2f,%.2f,TRUNC(SYSDATE,'dd'),'%s',to_date('%s','yyyy-mm-dd'),to_date('%s','yyyy-mm-dd'),\
				'%s','%s' ,'%s') ",str[4],atof(str[13]),atof(str[10]),\
				atof(str[11]),danjuhao,	str[5],str[6],str[0],str[3],str[8]);
		
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);

		}


		HospitalConnect->CommitTrans();

		strSql.Format("select distinct to_char(sysdate,'yyyymmddhh24miss') da from dual" );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			strSql=(char*)_bstr_t (recSet->GetCollect("da"));
			m_zktou='P';
			m_zktou+=strSql+LoginInformation.user_code;
		}
		recSet->Close();
		c_danjuhao.SetWindowText(m_zktou);

	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox(strSql);
		AfxMessageBox("盘点出现错误...");
		return;


	}
	AfxMessageBox("盘点成功...");

	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","售价","进价","指导价","盈亏数","库房"}; //共14列
	long  headWidth[]={0,00,2000,1600,600,0,1400,0,1600,1000,000,0,0,1200,1400};


	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	


}
