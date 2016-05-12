// OtherHealthSearch.cpp: implementation of the COtherHealthSearch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "OtherHealthSearch.h"
#include "otherhealth.h"
#include "otherHealthForModify.h"
#include "excel9.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define ROLE_SOCIETY_HEALTH_ADD 32 //社会人员体检信息增加
#define ROLE_SOCIETY_HEALTH_MODIFY 33 //社会人员体检信息修改
#define ROLE_SOCIETY_HEALTH_PRINT 34 //社会人员体检信息打印
#define ROLE_SOCIETY_HEALTH_DEL 35 //社会人员体检信息删除

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//* 其它人员体检信息检索,此类继承于 CHealthSearch,CHealthSearch的作用是
//* 进行职工体检信息检索,现生成新类 COtherHealthSearch,此类用于其它人员
//* 人员的信息体检工作,
//* 作者:凌绍清				日期:2005/12/08
//////////////////////////////////////////////////////////////////////

COtherHealthSearch::COtherHealthSearch()
{

}

COtherHealthSearch::~COtherHealthSearch()
{

}

void COtherHealthSearch::OnAdd()
{
	if(!theApp.AssertRole(ROLE_SOCIETY_HEALTH_ADD))return ;	

	COtherHealth he;
	he.DoModal();
}



void COtherHealthSearch::OnOK()
{
	condiQuery.pParent.pGrid=(LPVOID)this;
	condiQuery.strFlag="其它人员";

	condiQuery.SetWindowPos(&wndTop,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE  );
	
	condiQuery.ShowWindow(SW_SHOW);

}

////////////////////////////////////////////////////////////////////////////
//* 其它人员体检信息修改
//* 主要界面继承于为体检信息新增,其它同职工体检信息类似
//* 凌绍清 2005/12/08
/////////////////////////////////////////////////////////////////////////////
void COtherHealthSearch::OnModify()
{
	if(!theApp.AssertRole(ROLE_SOCIETY_HEALTH_MODIFY))return ;	

//	if(!theApp.AssertRole(ROLE_BODYCHECK_MODIFY))return ;	
//	CString HeadTitle[]={"姓名","性别","年龄","住址","电话","体检日期","血型","血压","体重","身高","既往史","内科检查",\
		"外科检查","眼底检查","妇科检查","肝谷丙","肝总胆红","肝谷草",\
		"肝总蛋白","肝R-谷氨","肝白蛋白","肾尿素氮","肾肌酐","空腹血糖",\
		"尿酸","甘油三脂","胆固醇","HBsAg","HBeAg","HBcAg","HBsAb","HBeAb","HBcAb",\
		"心电检查","X光检查","B超检查","结论","治疗建议","age","workage","workdate","rq","TSGF","AFP","CEA","备注"};																					//新增后五项
	COtherHealthForModify heal;

	for( int x=0; x < 5 ; x++ )
		heal.str[x]=m_grid.GetTextMatrix(lRow,x);
/*	heal.str[1]=m_grid.GetTextMatrix(lRow,4);
	heal.str[2]=m_grid.GetTextMatrix(lRow,0);
	heal.str[3]=m_grid.GetTextMatrix(lRow,1);
	heal.str[4]=m_grid.GetTextMatrix(lRow,38); // 年龄
	heal.str[5]=m_grid.GetTextMatrix(lRow,39); //工龄
*/	
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
	heal.m_B = m_grid.GetTextMatrix(lRow,35);   //B超
	heal.m_X = m_grid.GetTextMatrix(lRow,34);   //X光
	heal.m_result =m_grid.GetTextMatrix(lRow,36);
	heal.m_suggest =m_grid.GetTextMatrix(lRow,37);
//	m_comment = _T("");
	heal.m_strEdit0=m_grid.GetTextMatrix(lRow,42);//肿瘤三项一
	heal.m_strEdit1=m_grid.GetTextMatrix(lRow,43);// 二
	heal.m_strEdit2=m_grid.GetTextMatrix(lRow,44);// 三

	heal.m_comment=m_grid.GetTextMatrix(lRow,45);//备注
	heal.xuexin=m_grid.GetTextMatrix(lRow,6);
	for(int i=0;i<6;i++){
		heal.gan[i]=m_grid.GetTextMatrix(lRow,27+i);
	}

	heal.riqi=m_grid.GetTextMatrix(lRow,5);
extern UINT Tsearch2(LPVOID p);	
	if(heal.DoModal()==IDOK){
		AfxBeginThread(Tsearch2,&condiQuery.pParent);


	}
}

void COtherHealthSearch::OnPrintSelect() //其它体检信息人员打印
{
	if(!theApp.AssertRole(ROLE_SOCIETY_HEALTH_PRINT))return ;	

	if(lRow==0)return;
	BeginWaitCursor();
	_Application app;
	COleVariant vOpt(DISP_E_PARAMNOTFOUND,VT_ERROR);
	app.CreateDispatch("excel.application");
	if(!app){
		AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
		return;
	}
	
	Workbooks books=app.GetWorkbooks();
	
	CString strFileName,strLocate;
	strFileName.Format("%s",LoginInformation.path);
	strFileName+="book_p.xls";

	_Workbook book=books.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);

	
	Worksheets sheets=book.GetWorksheets();
	_Worksheet sheet=sheets.GetItem(COleVariant((short)1)); //原始数据表
	


	Range vRange;
	app.SetVisible(true);
	
	for(int i=0; i< m_grid.GetCols(0) ; i++ )
	{
		strLocate.Format("A%d",i+1);
		(Range(sheet.GetRange(COleVariant( strLocate),COleVariant(strLocate)))).SetValue(COleVariant(m_grid.GetTextMatrix(lRow,i)));


	}
	
/*	
	

	
	PageSetup pageinfo=sheet.GetPageSetup();
	str1.Format("第&p页");
	pageinfo.SetCenterFooter(str1);
	pageinfo.SetPrintTitleRows("$3:$3");
	pageinfo.SetCenterHorizontally(true);
//	sheet.PrintPreview(_O((short)1));
*/
/*	sheet.PrintOut(vOpt,vOpt,COleVariant((short)1),vOpt,vOpt,vOpt,vOpt,vOpt);
	
	sheet.ReleaseDispatch();

	sheets.ReleaseDispatch();
//	book.Close(_O((short)0),_O("c:\\tt.xls"),vOpt); //关闭EXCEL
	book.Close(COleVariant((short)0),vOpt,vOpt); //关闭EXCEL,不保存文件

	book.ReleaseDispatch();
	books.Close();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	app.Quit();
	EndWaitCursor();
	
*/
	app.Run(COleVariant("thisWorkBook.PrintSheet_Other"),vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
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

void COtherHealthSearch::OnDelete()
{
	if(!theApp.AssertRole(ROLE_SOCIETY_HEALTH_DEL))return ;	
	CString strSql;
	if(lRow==0){
		AfxMessageBox("请先选择要删除的行...");
		return;
	}
	
	try{
		strSql.Format("delete from other_tijian where rec_xm='%s' and riqi=to_date('%s','yyyy-mm-dd') ",m_grid.GetTextMatrix(lRow,0),m_grid.GetTextMatrix(lRow,5));

		HospitalConnect->BeginTrans();
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();

	}
	catch(_com_error e)
	{
		AfxMessageBox("删除出现错误,请重新启动程序再尝试删除...");
		HospitalConnect->RollbackTrans();



	}
	m_grid.RemoveItem(lRow);
	AfxMessageBox("成功删除了当前所选记录...");
}

void COtherHealthSearch::OnFastMenuSelect()
{
	if(!theApp.AssertRole(ROLE_SOCIETY_HEALTH_PRINT))return ;	

	
	_Application app;
	COleVariant vOpt(DISP_E_PARAMNOTFOUND,VT_ERROR);
	app.CreateDispatch("excel.application");
	if(!app){
		AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
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

		app.Run(COleVariant("thisWorkBook.PrintSheet_Other_all"),vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
			vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,\
			vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt ); //调用打印后不退出宏

	}
	


		
		

	sheet.ReleaseDispatch();
	
	sheets.ReleaseDispatch();
//	book.Close(_O((short)0),_O("c:\\tt.xls"),vOpt); //关闭EXCEL
	book.Close(COleVariant((short)0),vOpt,vOpt); //关闭EXCEL,不保存文件
	
	book.ReleaseDispatch();
	books.Close();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	app.Quit();
	

	EndWaitCursor();
	
}

BOOL COtherHealthSearch::OnInitDialog()
{
	CHealthSearch::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("其它人员体检信息检索");
	return true;

}
