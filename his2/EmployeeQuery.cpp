// EmployeeQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "EmployeeQuery.h"
#include "gh.h"
#include "excel9.h"
#include "OperatChargeRelateFee.h"
#include "employee.h"
#include "otherDecharge.h"
#include "employeeModify.h"
#include "subsidySet.h"
#include "passwordView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmployeeQuery dialog
#define DOWN_ARROR 0x28
#define UP_ARROR 0x26
#define COLS 8

CEmployeeQuery::CEmployeeQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CEmployeeQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmployeeQuery)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(200,"宋体");
	strKH="";
	curRow=0;
	p=NULL;
	flagRELATE=0; //作为供养亲属报销时使用,报销时代码为: 777;
	flag_EXIT=0;

	iMenuSel=5; //补充保险快捷菜单
}


void CEmployeeQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmployeeQuery)
	DDX_Control(pDX, ID_SEARCH, m_aaa);
	DDX_Control(pDX, ID_TO_EXCEL, m_excel);
	DDX_Control(pDX, IDOK, m_x2);
	DDX_Control(pDX, IDCANCEL, m_x1);
	DDX_Control(pDX, IDC_EDIT2, m_kahao);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_COMBO1, m_depart);
	DDX_Control(pDX, IDC_MSHFLEXGRID2, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmployeeQuery, CDialog)
	//{{AFX_MSG_MAP(CEmployeeQuery)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(ID_TO_EXCEL, OnToExcel)
	ON_COMMAND(ID_MENU_Q_EMP_ADD, OnMenuQEmpAdd)
	ON_COMMAND(ID_MENU_Q_EMP_DEL, OnMenuQEmpDel)
	ON_COMMAND(ID_MENU_Q_EMP_MODIFY, OnMenuQEmpModify)
	ON_COMMAND(ID_MENU_Q_EMP_SUBSIDY, OnMenuQEmpSubsidy)
	ON_BN_CLICKED(ID_SEARCH, OnSearch)
	ON_COMMAND(ID_MENU_Q_PASS_VIEW, OnMenuQPassView)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_MENU_QUICK_BASERY_DEL, OnMenuQuickBaseryDel)
	ON_COMMAND(ID_MENU_QUICK_BASERY_MODIFY, OnMenuQuickBaseryModify)
	ON_COMMAND(ID_MENU_QUICK_BASERY_VIEWPASSWORD, OnMenuQuickBaseryViewpassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmployeeQuery message handlers

BOOL CEmployeeQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString strSql;
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	try{
		strSql.Format("select distinct(所属部) from 厂部门表 ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetCollect("所属部").vt==VT_NULL?" ":recSet->GetCollect("所属部"));
			m_depart.AddString(strSql);
			recSet->MoveNext();
		}
		recSet->Close();
		m_depart.AddString("所有部门");

	}
	catch(_com_error e)
	{
		recSet->Close();
		return false;
	}

	m_grid.SetRows(2);
	m_grid.Clear();

	long j=0, i=0,x=0;
	CString HeadTitle[]={"所属部","卡号","姓名","性别","出生日期","工作日期",\
		"结存金额","工作性质","类别","pass"};

	long  headWidth[]={1400,1200,1200,400,1300,1300,1200,2000,1000};//,2000,1000};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		m_grid.SetColWidth(i,headWidth[count]);

//		p2->m_grid.SetRow(0);
//		p2->m_grid.SetCol(i);
//		p2->m_grid.SetColAlignment(i,4);//flexAlignCenterCenter 4 单元格的内容居中、居中对齐	

		m_grid.SetTextArray(i++,HeadTitle[count]);
	}
	CenterWindow();
//	AnimateWindow(m_hWnd,300,AW_SLIDE|AW_HOR_POSITIVE);
//	Invalidate();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEmployeeQuery::OnOK() 
{
	BeginWaitCursor();
	//卡号,姓名,性别,出生日期,工作日期,部门,结存金额,工作性质
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetRedraw(false);

	long j=0, i=0,x=0;
	CString HeadTitle[]={"所属部","卡号","姓名","性别","出生日期","工作日期",\
		"结存金额","工作性质","类别","pass"},str1;

	long  headWidth[]={1400,1200,1200,400,1300,1300,1600,1000,1000,00,00};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		m_grid.SetColWidth(i,headWidth[count]);

//		p2->m_grid.SetRow(0);
//		p2->m_grid.SetCol(i);
//		p2->m_grid.SetColAlignment(i,4);//flexAlignCenterCenter 4 单元格的内容居中、居中对齐	

		m_grid.SetTextArray(i++,HeadTitle[count]);
	}
	CString strSql,strName,strID,strDepart;
	if(m_depart.GetCurSel()==CB_ERR)strDepart="所有部门";
	else m_depart.GetLBText(m_depart.GetCurSel(),strDepart); 
	double dbWage=0;
	m_name.GetWindowText(strName);
	m_kahao.GetWindowText(strID);
	j=1;
	try{
		if(strDepart=="所有部门")
			strSql.Format("select * from 职工基本情况表 e1,厂部门表 e2 where  e1.部门编码=e2.部门编码 and 卡号 like '%s%%' and 姓名 like '%s%%' and 类别='参保'  order by 姓名 ",strID,strName);
		else
			strSql.Format("select * from 职工基本情况表 e1,厂部门表 e2 where e1.部门编码=e2.部门编码 and \
				卡号 like '%s%%' and 姓名 like '%s%%' and 所属部='%s' and 类别='参保' order by 姓名",strID,strName,strDepart);
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			x=0;
			for(count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
				
				str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(HeadTitle[count])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(HeadTitle[count])));
				if( count == 6 ) dbWage+=atof(str1); //计算结存金额
				m_grid.SetTextMatrix(j,x++,str1);
			}
				
			
			m_grid.AddItem(" ",_variant_t(++j));
			recSet->MoveNext();


		}
		m_grid.SetRedraw(true);
		recSet->Close();		
		
	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox("数据库可能破坏,请检查数据...");
		return;
	}
	m_grid.SetTextMatrix(j,0,"合计");
	strSql.Format("%.2f",dbWage);
	m_grid.SetTextMatrix(j,6,strSql);
	strSql.Format("共查询到: %ld 条信息",j-1);
	GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(strSql);

	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow = 1;
		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
	EndWaitCursor();
}

HBRUSH CEmployeeQuery::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->m_hWnd==GetDlgItem(IDC_STATIC_TITLE)->m_hWnd || pWnd->m_hWnd==GetDlgItem(IDC_STATIC_NOTI)->m_hWnd){
		pDC->SetTextColor(RGB(255,0,0));
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BEGIN_EVENTSINK_MAP(CEmployeeQuery, CDialog)
    //{{AFX_EVENTSINK_MAP(CEmployeeQuery)
	ON_EVENT(CEmployeeQuery, IDC_MSHFLEXGRID2, -601 /* DblClick */, OnDblClickMshflexgrid2, VTS_NONE)
	ON_EVENT(CEmployeeQuery, IDC_MSHFLEXGRID2, -602 /* KeyDown */, OnKeyDownMshflexgrid2, VTS_PI2 VTS_I2)
	ON_EVENT(CEmployeeQuery, IDC_MSHFLEXGRID2, -600 /* Click */, OnClickMshflexgrid2, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CEmployeeQuery::OnDblClickMshflexgrid2() 
{
		if( flag_EXIT== 7777)return ;//作为单独查询时使用,不要消失对话框
		long row=m_grid.GetRow();
		if(row<m_grid.GetRows()-1 && row !=0){
			
			strKH=m_grid.GetTextMatrix(row,1);
			strName=m_grid.GetTextMatrix(row,2);//姓名
			strSex=m_grid.GetTextMatrix(row,3);//性别
			strDate[0]=m_grid.GetTextMatrix(row,4);//出生日期
			strDate[1]=m_grid.GetTextMatrix(row,5);//工作日期
		//后期添加,不改动原来代码
			for(int i=0;i< m_grid.GetCols(0) ;i++)lineInfor[i]=m_grid.GetTextMatrix(row,i);
			
			if(p!=NULL)
				if( flagRELATE == 777 ) //作为报销时使用
				{
					for( i=0;i< m_grid.GetCols(0) ;i++)((COperatChargeRelateFee *)p)->infor[i]=m_grid.GetTextMatrix(row,i);
				}

				else 
					for( i=0;i<COLS;i++)((CGh*)p)->infor[i]=m_grid.GetTextMatrix(row,i);
				
				CDialog::OnOK();
		}


}

void CEmployeeQuery::OnSelchangeCombo1() 
{
	OnOK();
}

BOOL CEmployeeQuery::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN && flag_EXIT != 7777 )
	{
		if(pMsg->wParam == VK_RETURN )OnDblClickMshflexgrid2();
		else if( pMsg->wParam==VK_DOWN)
			m_grid.SetFocus();
	}
		// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CEmployeeQuery::OnKeyDownMshflexgrid2(short FAR* KeyCode, short Shift) 
{
	long rows=m_grid.GetRows()-2;
	if(rows == 0)return; //没有项目则反返回

	if( DOWN_ARROR == * KeyCode){  //下箭头按下动作
	
		m_grid.SetCol(0);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();

		for(int i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
	
		if(curRow < rows && curRow != 0 ) m_grid.SetRow(++curRow);
		else {
				curRow=1;
				m_grid.SetRow(curRow);

		}
		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
		

	}
	else if(UP_ARROR == * KeyCode){ //上箭头按下动作


		m_grid.SetCol(0);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();

		for(int i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
	
		if(curRow <= rows && curRow!= 1) m_grid.SetRow(--curRow);
		else {
				curRow=rows;
				m_grid.SetRow(curRow);

		}
		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}



	}	// TODO: Add your control notification handler code here
	
}

void CEmployeeQuery::OnClickMshflexgrid2() 
{
	if(m_grid.GetCols(0) == 5 ) return ; //职务查询情况下不操作
	const long ENDLINES=2;
	if(m_grid.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		SetSel();
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_MEDLIST);
	CMenu* pmenu=pm.GetSubMenu(iMenuSel);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  

	


	// TODO: Add your control notification handler code here
	
}

void CEmployeeQuery::OnToExcel() 
{
	extern void ToExcel(CMSHFlexGrid * pg);

	if( MessageBox("是否确定要导出到 Excel 表格 ??? ","提示",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	ToExcel(&m_grid);

}

void CEmployeeQuery::SetSel()
{
		long r1;
		r1=m_grid.GetRow();
		if(r1 >= m_grid.GetRows()-1 || curRow == r1)return;
		
		m_grid.SetCol(0);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();
		
		for(int i=1;i<8;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
		m_grid.SetRow(r1);
		curRow=r1;
		for( i=1;i<8;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
}

void CEmployeeQuery::OnMenuQEmpAdd() 
{
	// TODO: Add your command handler code here
	if(!theApp.AssertRole(ROLE_EMP_EDIT))return; 
	CEmployee ee;
	ee.DoModal();
}

void CEmployeeQuery::OnMenuQEmpDel() //
{
	if(!theApp.AssertRole(ROLE_EMP_EDIT))return; 

	long row=m_grid.GetRow();
	if( row != curRow ) return;
	CString strSql;
	strSql.Format("确认要注销 (%s)/(%s) 吗???",m_grid.GetTextMatrix(curRow,1),m_grid.GetTextMatrix(curRow,2) );
	if( AfxMessageBox(strSql,MB_OKCANCEL)== IDCANCEL) return;
/*
	strSql.Format(" INSERT INTO LSQ_EMPLOYEE_DEL SELECT t.*,sysdate,(select \
		sys_context( 'userenv' , 'ip_address') from dual )||'_'||'%s' FROM 职工基本情况表 t \
		WHERE 卡号='%s' ",LoginInformation.user,m_grid.GetTextMatrix(curRow,1) );
*/
	try{
		HospitalConnect->BeginTrans();
	//	HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
	//	strSql.Format("DELETE FROM 职工基本情况表 WHERE 卡号='%s' ",m_grid.GetTextMatrix(curRow,1) );
		strSql.Format(" UPDATE  职工基本情况表 SET 类别='消户',结存金额=0.0,ds1=( SELECT sys_context('USERENV','ip_address')||'.'|| to_char(sysdate,'hh24yyyymimmssdd') ||'EMPOFF' from dual ),d1=sysdate WHERE 卡号='%s' ",m_grid.GetTextMatrix(curRow,1) );
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();
	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox("删除失败...");
		return;
	}
		
	
	AfxMessageBox("删除成功!!!");
	OnOK();
	
}

void CEmployeeQuery::OnMenuQEmpModify()  //补充保险人员性质修改
{
	if(!theApp.AssertRole(ROLE_EMP_EDIT))return; 

	long row=m_grid.GetRow();
	if( row != curRow ) return;

	CEmployeeModify di; 
	di.strTitle.Format("补充保险人员性质修改");
	di.strTmp=m_grid.GetTextMatrix(curRow,1);//卡号
	if(di.DoModal()==IDOK) OnOK();
}

void CEmployeeQuery::OnMenuQEmpSubsidy()  //特殊人员设置
{
	//"所属部","卡号","姓名","性别","出生日期","工作日期",\
		"结存金额","工作性质","类别"},str1;
	if(!theApp.AssertRole(ROLE_EMP_EDIT))return; 

	long row=m_grid.GetRow();
	if( row != curRow ) return;
	
	CSubsidySet di;
	di.strName= m_grid.GetTextMatrix(curRow,2); //姓名
	di.strKh=m_grid.GetTextMatrix(curRow,1); //卡号
	di.DoModal();
//	di.strTmp=m_grid.GetTextMatrix(curRow,1);//卡号

}

void CEmployeeQuery::OnSearch() 
{

	BeginWaitCursor();
	//卡号,姓名,性别,出生日期,工作日期,部门,结存金额,工作性质
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetRedraw(false);

	long j=0, i=0,x=0;
//	CString HeadTitle[]={"所属部","卡号","姓名","性别","出生日期","工作日期",\
		"结存金额","工作性质","类别","补助性质","补助金额"},str1;
	CString HeadTitle[]={"所属部","卡号","姓名","补助性质","补助金额"},str1;

	long  headWidth[]={1400,1200,1200,2200,1300,1300,1200,1000,1000,2000,1000};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<3)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}
	CString strSql,strName,strID,strDepart;
	if(m_depart.GetCurSel()==CB_ERR)strDepart="所有部门";
	else m_depart.GetLBText(m_depart.GetCurSel(),strDepart); 

	m_name.GetWindowText(strName);
	m_kahao.GetWindowText(strID);
	j=1;
	try{
		if(strDepart=="所有部门")
			strSql.Format("select * from 职工基本情况表 e1,厂部门表 e2,\
			(select a.ds1 kh,b.ds1 补助性质,b.n3 补助金额 from lsq_emp_headship a,lsq_upgrade b where \
			a.ds2=b.ds3 and b.ds2='ESUB') e3 \
			where  e1.部门编码=e2.部门编码 and e3.kh(+)=卡号 AND 卡号 like '%s%%' and 姓名 like '%s%%' and 类别 not in( '消户','离休')  order by 姓名 ",strID,strName);
		else
	
		strSql.Format("select * from 职工基本情况表 e1,厂部门表 e2,\
			(select a.ds1 kh,b.ds1 补助性质,b.n3 补助金额 from lsq_emp_headship a,lsq_upgrade b where \
			a.ds2=b.ds3 and b.ds2='ESUB') e3 \
		where e1.部门编码=e2.部门编码 and e3.kh(+)=卡号　AND \
		卡号 like '%s%%' and 姓名 like '%s%%' and 所属部='%s' and 类别 not in( '消户','离休') order by 姓名",strID,strName,strDepart);
			
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			x=0;
			for(count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
				
				str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(HeadTitle[count])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(HeadTitle[count])));
				m_grid.SetTextMatrix(j,x++,str1);
			}
				
			
			m_grid.AddItem(" ",_variant_t(++j));
			recSet->MoveNext();


		}
		m_grid.SetRedraw(true);
		recSet->Close();		
		
	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox("数据库可能破坏,请检查数据...");
		return;
	}
	m_grid.SetTextMatrix(j,0,"合计");
	strSql.Format("共查询到: %ld 条信息",j-1);
	GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(strSql);
/*	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow = 1;
		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
*/	EndWaitCursor();	
}

void CEmployeeQuery::OnMenuQPassView() 
{
//{"所属部","卡号","姓名","性别","出生日期","工作日期",\
		"结存金额","工作性质","类别","pass"},str1;
	if(!theApp.AssertRole(ROLE_EMP_EDIT))return; 

	CPasswordView di;

	di.strTitle="补充保险密码查询";
	for(int i=0; i< 5; i++)
		di.str[i]=m_grid.GetTextMatrix(curRow,i);
	di.str[i]=m_grid.GetTextMatrix(curRow,9);//password

	if(di.DoModal()==IDOK)OnOK();
}

void CEmployeeQuery::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnOK();
}

void CEmployeeQuery::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

void CEmployeeQuery::OnMenuQuickBaseryDel() 
{
	// TODO: Add your command handler code here
	
}

void CEmployeeQuery::OnMenuQuickBaseryModify() 
{
	// TODO: Add your command handler code here
	
}

void CEmployeeQuery::OnMenuQuickBaseryViewpassword() 
{
	// TODO: Add your command handler code here
	
}
