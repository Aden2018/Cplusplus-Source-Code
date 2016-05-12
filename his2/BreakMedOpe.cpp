// BreakMedOpe.cpp: implementation of the CBreakMedOpe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "BreakMedOpe.h"
#include "medStockList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBreakMedOpe::CBreakMedOpe()
{

}

CBreakMedOpe::~CBreakMedOpe()
{
}

BOOL CBreakMedOpe::OnInitDialog()
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
			m_zktou='B'; //报损操作
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
/*	CString HeadTitle[]={"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","售价","进价","指导价","取药数"}; //共14列
	long  headWidth[]={0,00,2000,1600,600,0,1400,0,1600,1000,000,0,0,1200};
*/
	CString HeadTitle[]={"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","售价","进价","指导价","报损数","库房","KFBM"}; //共14列
	long  headWidth[]={0,00,2000,1600,600,0,1400,0,1600,1000,000,0,0,1200,1400,0};

	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	m_grid.SetMergeCol(14,true);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	

	SetWindowText("药品 [ 报损 ] 操作");
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("药品 [ 报损 ] 操作");
	m_4.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC1)->SetWindowText("药  房");
	GetDlgItem(IDC_STATIC4)->SetWindowText("原  因:");
	GetDlgItem(IDC_STATIC3)->SetWindowText("操作员");
	GetDlgItem(IDC_STATIC5)->SetWindowText("有效期至");
	
	GetDlgItem(IDC_STATIC5)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DATETIMEPICKER1)->ShowWindow(SW_SHOW);
	CRect rt1,rt2;
	GetDlgItem(IDC_EDIT_DANJUHAO)->GetWindowRect(rt1);
	ScreenToClient(rt1);
	GetDlgItem(IDC_EDIT_GET_RYMC)->GetWindowRect(rt2);
	ScreenToClient(rt2);
	GetDlgItem(IDC_EDIT_GET_RYMC)->MoveWindow(rt2.left,rt2.top,rt1.right-rt1.left,rt1.bottom-rt1.top);
	
	GetDlgItem(IDOK_EFFIECT)->ShowWindow(SW_SHOW);
	
	c_getRymc.SetWindowText("过期报损");
	m_curKf.SetWindowText(LoginInformation.user);

	return TRUE;
}

void CBreakMedOpe::OnOK()
{
	UpdateData();
	CString strSql,danjuhao,ywy,str[20];

	c_getRymc.GetWindowText(ywy); //报损原因
	c_danjuhao.GetWindowText(danjuhao);



	long rows=m_grid.GetRows()-2; //得到药品行数
	if( 0 == rows)return;
	try{
		HospitalConnect->BeginTrans();

		strSql.Format("insert into 报废表 (danjuhao,riqi,KFBM,OPERATOR,BEizhu ) values('%s',TRUNC(SYSDATE,'dd'),'%s','%s','%s' ) ",\
			danjuhao,LoginInformation.user_code,LoginInformation.user,ywy); //KFBM 现改用为操作人员 编码
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
		
			strSql.Format("UPDATE MEDLIE set SL=SL-(%.2f) where ID='%s' ",atof(str[13]),str[4]);
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
			m_zktou='B'; //药品报损
			m_zktou+=strSql+LoginInformation.user_code;
		}
		recSet->Close();
		c_danjuhao.SetWindowText(m_zktou);

	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox(strSql);
		AfxMessageBox("报损出现错误...");
		return;


	}
	AfxMessageBox("当前所列药品报损成功...");

	m_grid.SetRows(2);
	m_grid.Clear();

	CString HeadTitle[]={"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","售价","进价","指导价","报损数","库房","KFBM"}; //共14列
	long  headWidth[]={0,00,2000,1600,600,0,1400,0,1600,1000,000,0,0,1200,1400,0};


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

void CBreakMedOpe::OnSetfocusEditGetRymc()
{

}

void CBreakMedOpe::OnKillfocusEditGetRymc()
{

}

void CBreakMedOpe::OnSearch()
{
	CMedStockList medlist;
	if( c_getKf.GetCurSel() == CB_ERR ){
		AfxMessageBox("请先选择要盘点的库房...");
		return;
	}
	theApp.pParentGrid.pGrid=&m_grid;
	GetDlgItem(IDC_COMBO_GET_KF)->GetWindowRect(medlist.r1);
	medlist.flagMoveKF=113; //作为报损时用,搜寻所有库房药品
	medlist.strSelKF= m_getKfbm;
	flagPANDIAN=999 ; //报损时用，指示输入数量时不应小于等于零或大于当前药品数量
	c_getKf.GetLBText(c_getKf.GetCurSel(),medlist.strSelKfName);
	medlist.DoModal();

}

void CBreakMedOpe::OnEffiect()//列出过期药品
{
	UpdateData();
	m_grid.Clear();
	m_grid.SetRows(2L);

	CString HeadTitle[]={"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","售价","进价","指导价","报损数","库房","KFBM"}; //共14列
//	long  headWidth[]={0,00,2000,1600,600,0,1400,0,1600,1000,000,0,0,1200,1400,0},i;
	long i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
//		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	

	CString strSql,str1;
	if( c_getKf.GetCurSel() == CB_ERR || c_getKf.GetCurSel() == 0 )
		strSql.Format("SELECT id,bm,mc,gg,dw,rq1,rq2,\
			 gongbm,gongmc,sl,sell_price,jinjia,Coach_price,\
			 sl,s.KFMC,s.KFBM  from medlie t,medcode x,codegys y,storeroom s where t.ypbm=x.bm \
			 and y.gongbm=t.factorycode AND s.kfbm=t.kfbm AND sl != 0 AND rq2 < to_date('%s','yyyymmdd') \
			 order by t.kfbm,bm",m_date.Format("%Y%m%d") );
	else 
	{
	
		strSql.Format("SELECT id,bm,mc,gg,dw,rq1,rq2,\
			 gongbm,gongmc,sl,sell_price,jinjia,Coach_price,\
			 sl,s.KFMC ,s.KFBM from medlie t,medcode x,codegys y,storeroom s where t.ypbm=x.bm \
			 and y.gongbm=t.factorycode AND s.kfbm=t.kfbm AND sl != 0 AND rq2 < to_date('%s','yyyymmdd') \
			 and t.kfbm='%s' order by t.kfbm,bm",m_date.Format("%Y%m%d"),m_getKfbm );
	}
	try{	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		long row,i,col;
		row=1;
		while(!recSet->adoEOF){
			col=0;
			for(i=0;i< 16 ;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				m_grid.SetTextMatrix(row,col++,str1);
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
}
