// EmployeeRelateQuery.cpp: implementation of the CEmployeeRelateQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "EmployeeRelateQuery.h"
#include "relateadd.h"
#include "relateModify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEmployeeRelateQuery::CEmployeeRelateQuery()
{
	flag_EXIT=0;
	iMenuSel=4; //供养人员快捷菜单
}

CEmployeeRelateQuery::~CEmployeeRelateQuery()
{

}
BEGIN_MESSAGE_MAP(CEmployeeRelateQuery, CEmployeeQuery)
	//{{AFX_MSG_MAP(CEmployeeQuery)
	ON_COMMAND(ID_MENU_RELATE_MODIFY, OnMenuRelateModify)
	ON_COMMAND(ID_MENU_RELATE_ADD, OnMenuRelateAdd)
	ON_COMMAND(ID_MENU_RELATE_KILL, OnMenuRelateKill)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEmployeeRelateQuery::OnOK()
{
	BeginWaitCursor();
	//卡号,姓名,性别,出生日期,工作日期,部门,结存金额,工作性质
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetRedraw(false);

	long j=0, i=0,x=0;
	CString HeadTitle[]={"bm","BM","XM","XB","XINGZHI","YUER","姓名","所属部",\
		"工作性质","CSRIQI","age"},str1;
	CString HeadTitle2[]={"TEMP","编码","姓名","性别","供养性质","余额","供养人","所属部",\
		"工作性质","出生日期","年龄"};
	long  headWidth[]={0,1400,1200,600,1400,1300,1300,2000,00,0,600};
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

		m_grid.SetTextArray(i++,HeadTitle2[count]);
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
			strSql.Format("select bm,xm,xb,xingzhi,yuer,姓名,所属部,工作性质,csriqi,to_char(sysdate,'yyyy')-to_char(csriqi,'yyyy') age from 职工基本情况表 e1,厂部门表 e2,codeQingShu e3 where  \
			e1.部门编码=e2.部门编码 and e3.kahao=e1.卡号 and 类别 != '消户' AND \
			bm like '%s%%' and xm like '%s%%' AND zxriqi is NULL order by xm",strID,strName);
		else
			strSql.Format("select bm,xm,xb,xingzhi,yuer,姓名,所属部,工作性质,csriqi,to_char(sysdate,'yyyy')-to_char(csriqi,'yyyy') age from 职工基本情况表 e1,厂部门表 e2,codeQingShu e3 where \
				e1.部门编码=e2.部门编码 and e3.kahao=e1.卡号 and \
				bm like '%s%%' and xm like '%s%%' and 所属部='%s' and 类别 != '消户' AND zxriqi is NULL order by xm ",strID,strName,strDepart);
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			x=0;
			for(count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
				
				str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(HeadTitle[count])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(HeadTitle[count])));
				if( count == 5) dbWage+=atof(str1);
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
	m_grid.SetTextMatrix(j,1,"合计");
	strSql.Format("%.2f",dbWage);
	m_grid.SetTextMatrix(j,5,strSql);
	strSql.Format("共查询到: %ld 条信息",j-1);
	GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(strSql);
	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow=1;
		for( i=1;i<8;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}
	EndWaitCursor();
}

BOOL CEmployeeRelateQuery::OnInitDialog()
{
	CEmployeeQuery::OnInitDialog();

	SetWindowText("供养亲属人员表");
	m_grid.SetRows(2);
	m_grid.Clear();
	CString HeadTitle[]={"TEMP","编码","姓名","性别","供养性质","余额","供养人","所属部",\
		"工作性质"};

	long j=0, i=0,x=0;

	long  headWidth[]={0,1400,1200,600,1400,1300,1300,2000,2000};
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


	GetDlgItem(IDC_STATIC_3)->SetWindowText("供养人部门");
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("供养亲属情况表");

	return true;
}



//DEL void CEmployeeRelateQuery::OnClickMshflexgrid2()
//DEL {
//DEL 	const long ENDLINES=2;
//DEL 	if(m_grid.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单
//DEL 
//DEL 	MSG *pms;
//DEL 	pms=(MSG*)GetCurrentMessage();
//DEL 	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
//DEL 		
//DEL 		CEmployeeQuery::OnClickMshflexgrid2();
//DEL 		return;
//DEL 	}
//DEL 	CMenu pm;
//DEL 	CPoint p;
//DEL 	pm.LoadMenu(IDR_MENU_MEDLIST);
//DEL 	CMenu* pmenu=pm.GetSubMenu(4);
//DEL 	GetCursorPos(&p);
//DEL 	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  
//DEL }

void CEmployeeRelateQuery::OnMenuRelateModify() //修改
{
	//{"TEMP","编码","姓名","性别","供养性质","余额","供养人","所属部",\
		"工作性质","出生日期","年龄"};
	if(!theApp.AssertRole(ROLE_RELATE_MODIFY))return; 
	CRelateModify modify;
	for(int i=0 ; i< m_grid.GetCols(0) ; i++ ) modify.strPass[i]=m_grid.GetTextMatrix(curRow,i);
	if(modify.DoModal()==IDOK) OnOK();

}

void CEmployeeRelateQuery::OnMenuRelateKill()
{
//{"TEMP","编码","姓名","性别","供养性质","余额","供养人","所属部",\
		"工作性质","出生日期"};	AfxMessageBox("add");
	if(!theApp.AssertRole(ROLE_RELATE_KILL))return; 

	CString strView;
	strView.Format("编码: %s \n\n姓名: %s 性别: %s \n\n供养性质: %s 余额: %s \n\n供养人: %s (%s) \n\n确认要注销吗???",\
		m_grid.GetTextMatrix(curRow,1),m_grid.GetTextMatrix(curRow,2),m_grid.GetTextMatrix(curRow,3),\
		m_grid.GetTextMatrix(curRow,4),m_grid.GetTextMatrix(curRow,5),m_grid.GetTextMatrix(curRow,7),m_grid.GetTextMatrix(curRow,6));

	if( MessageBox(strView,"提示",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	try{
		HospitalConnect->BeginTrans();
		strView.Format("UPDATE codeQingShu Set ZXRIQI=sysdate,yuer=0 WHERE BM='%s' AND zxriqi is NULL ",m_grid.GetTextMatrix(curRow,1));
		HospitalConnect->Execute(_bstr_t(strView),NULL,adCmdText);
		HospitalConnect->CommitTrans();
	}catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox(e.ErrorMessage());
		return;
	}
	AfxMessageBox("成功将当前用户注销!!!");
	OnOK();

}

void CEmployeeRelateQuery::OnMenuRelateAdd()
{
	if(!theApp.AssertRole(ROLE_RELATE_ADD))return; 
	CRelateAdd add;
	add.DoModal();

}
