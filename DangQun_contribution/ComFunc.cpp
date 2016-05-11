// ComFunc.cpp: implementation of the CComFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "ComFunc.h"
#include "progressEx.h"
#include "dialogWait.h"
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace SQ_EXCEL9;
CComFunc::CComFunc()
{

}

CComFunc::~CComFunc()
{

}

CString CComFunc::GetString(CString strSql)
{
	CString strout(BLANKSTR);
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
		
			strout=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(0L)->Value );
		}
		recSet->Close();

		return strout;

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return strout;
	}	

}

BOOL CComFunc::WriteSql(CString strSql)
{
	try{

		HospitalConnect->BeginTrans();
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();

	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox(e.Description());
		return false;
	}
	return true;

}

void CComFunc::writeDebug(CString strout)
{
	CFile fDebug;

	if( ! fDebug.Open("S:\\log.txt",CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite|CFile::modeNoTruncate  ) )
		AfxMessageBox("建立调试文件失败...");
	else fDebug.SeekToEnd();

	COleDateTime curDate=COleDateTime::GetCurrentTime();
	CString strFmt;
	CString strRet("\r\n");
	CString strSpan('-',40);
	strFmt.Format("%s\r\n",curDate.Format("%Y-%m-%d %H:%M:%S") );
	fDebug.Write(strFmt,strFmt.GetLength());
	strSpan+=strRet;
	fDebug.Write(strSpan,strSpan.GetLength());

	fDebug.Write(strout,strout.GetLength());
	fDebug.Write(strRet+strRet,strRet.GetLength()*2 );


	fDebug.Close();

}
#define IDC_PROGRESS_EXCEL WM_USER+1001
void CComFunc::ToExcel(CMSHFlexGrid *pg)
{
/*
	CProgressEx *pp=new CProgressEx();

	CRect r1(0,0,400,25);
	pp->Create(WS_CHILD |PBS_SMOOTH|WS_BORDER ,r1,AfxGetMainWnd()->GetForegroundWindow(),IDC_PROGRESS_EXCEL);
	pp->UpdateWindow();
	pp->ShowWindow(SW_SHOW);
	pp->CenterWindow();
	pp->Invalidate();
	pp->SetRange32(0,pg->GetRows() );
	pp->strView="正在准备导出...请稍等!!";
	
	theApp.pParentGrid.pGrid=pg;
	AfxBeginThread(THREAD_TO_EXCEL,pp);
*/
	_Application app2;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;
	 COleVariant vOpt2(DISP_E_PARAMNOTFOUND,VT_ERROR);

	CProgressEx pp;
	CRect r1(0,0,400,25);
	pp.Create(WS_CHILD |PBS_SMOOTH|WS_BORDER ,r1,AfxGetMainWnd()->GetForegroundWindow(),IDC_PROGRESS_EXCEL);
	pp.UpdateWindow();
	pp.ShowWindow(SW_SHOW);
	pp.CenterWindow();
	pp.Invalidate();
	pp.SetRange32(0,pg->GetRows() );
	pp.strView="正在准备导出...请稍等!!";

	app2.CreateDispatch("excel.application");
	if(!app2){
		AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
		return;
	}
	books2=app2.GetWorkbooks();
	//		book2=books2.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	book2=books2.Add(vOpt2);
	sheets2=book2.GetWorksheets();
	sheet2=sheets2.GetItem(COleVariant((short)1));


	Range vRange;
	SQ_EXCEL9::Font font;
	long x,y;
	CString str1,str2;
	
	app2.SetVisible(false);
	pp.strView="";


	for (x=0; x<pg->GetRows(); x++)
	{
		for( y=0 ; y< pg->GetCols(0) ; y++ )
		{
			if( y<26)str1.Format("%c%ld",'A'+y , x+1 );
			else str1.Format("%c%c%ld",'A'+ ( y/26 -1) ,'A'+y % 26,x+1 );
			vRange=sheet2.GetRange(_variant_t(str1),_variant_t(str1)); // 医疗机构
		//	font=vRange.GetFont();
		//	font.SetName(_O(FONTNAME));
		//	font.SetSize(_O((short)STANDARDFONT));
			vRange.SetValue(COleVariant(pg->GetTextMatrix(x,y)));
		}
		
		pp.strView.Format("%2.0f%%",double(x)/pg->GetRows()*100);
		pp.SetPos(x);
	}
	app2.SetVisible(true);
		
	pp.DestroyWindow();
	sheet2.ReleaseDispatch();

	sheets2.ReleaseDispatch();

	book2.ReleaseDispatch();
	books2.ReleaseDispatch();
	app2.ReleaseDispatch();	

}
/*  根据提供的ID号从数据库中读取相应的列头,设置列标题 
*
*/
BOOL CComFunc::comSetGridHeader(CMSHFlexGrid &m_grid, ULONG id)
{

	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	long GRID_COLS=0, i=0;
	CString strSql;
	try{
		strSql.Format("select mc,width,align from lsq_grid_col  where id=%ld order by rank ",id);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect, adOpenDynamic ,adLockOptimistic,adCmdText); 

		m_grid.SetCols(0,GRID_COLS);
		while(!recSet->adoEOF){
			GRID_COLS++;
			m_grid.SetCols(0,GRID_COLS);
	
			strSql=(char*)_bstr_t(recSet->GetCollect("MC").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("MC"));
			m_grid.SetTextMatrix(HEADER_ROW,i,strSql);
			strSql=(char*)_bstr_t(recSet->GetCollect("width").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("width"));
			m_grid.SetColWidth(i,0,atol(strSql) );
			strSql=(char*)_bstr_t(recSet->GetCollect("align").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("align"));
			m_grid.SetColAlignment(i,atoi(strSql));
			
			i++;
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}		

	m_grid.SetFixedCols(0);
	long  col(0),row(0);
	m_grid.SetSelectionMode(1L);
	m_grid.SetRow(0);

	for(i =0 ; i< GRID_COLS; i++){
		m_grid.SetCol( i );
		m_grid.SetCellAlignment((short)4); //居中对齐
	
	}	
	CComFunc::GridSelRow(m_grid,1);
	return true;

}

UINT CComFunc::THREAD_TO_EXCEL(LPVOID lp)
{
	_Application app2;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;
	 COleVariant vOpt2(DISP_E_PARAMNOTFOUND,VT_ERROR);

	 app2.CreateDispatch("excel.application");
	if(!app2){
		AfxMessageBox("请注意系统中必须装有EXCEL97以上版本 ,否则此功能不能使用...");
		return false;
	}
	books2=app2.GetWorkbooks();
	book2=books2.Add(vOpt2);
	sheets2=book2.GetWorksheets();
	sheet2=sheets2.GetItem(COleVariant((short)1));


	Range vRange;
	SQ_EXCEL9::Font font;
	long x,y;
	CString str1,str2;
	
	app2.SetVisible(false);
	((CProgressEx *)lp)->strView="";
	CMSHFlexGrid *pg=(CMSHFlexGrid *)theApp.pParentGrid.pGrid;
	

	for (x=0; x<pg->GetRows(); x++)
	{
		for( y=0 ; y< pg->GetCols(0) ; y++ )
		{
			if( y<26)str1.Format("%c%ld",'A'+y , x+1 );
			else str1.Format("%c%c%ld",'A'+ ( y/26 -1) ,'A'+y % 26,x+1 );
			vRange=sheet2.GetRange(_variant_t(str1),_variant_t(str1)); // 医疗机构
			vRange.SetValue(COleVariant(pg->GetTextMatrix(x,y)));
		}
		
		((CProgressEx *)lp)->strView.Format("%2.0f%%",double(x)/pg->GetRows()*100);
		((CProgressEx *)lp)->SetPos(x);
	}
	app2.SetVisible(true);
		
	((CProgressEx *)lp)->DestroyWindow();

	sheet2.ReleaseDispatch();

	sheets2.ReleaseDispatch();
//	book.Close(_O((short)0),vOpt,vOpt); //关闭EXCEL,不保存文件

	book2.ReleaseDispatch();
	books2.ReleaseDispatch();
	app2.ReleaseDispatch();	


	return true;
}

bool CComFunc::AssertPriv(UINT id)
{

	vector<string> vtSz;
	vtSz.push_back( MYSQL_PRC_RPT); //存储过程名
	vtSz.push_back("1");			//查询
	vtSz.push_back("D");			//验证权限
	vtSz.push_back((LPCSTR)LoginInformation.user_code); //用户ID
	ostringstream ostr;
	ostr<<id;
	vtSz.push_back	( ostr.str() ); //权限ID
	

	string szRet;

	CComFunc::callSqlPro(vtSz,szRet);

	if( szRet.compare(SZERROR) )
	{
			return true;
	} 
//	else AfxMessageBox("调用存储功能失败");
	return false;
}

void CComFunc::SetExcelCell(_Worksheet &sheetx, int iRow, int iCol, CString &strData)
{

	/* 设置EXCEL单元格字符串 
		sheetx  要操作的工作表
		iRow	要操作工作表所在的行
		iCol	要操作的工作表所在列
		strData 要写入的字符串
	*/
#define _O(x) COleVariant(x)
	
	CString strCell;
	Range vRange;
	strCell.Format("%c%d",iCol+'A',iRow+1);
	vRange=sheetx.GetRange(_O(strCell),_O(strCell));
	vRange.SetValue(_O(strData));

}

void CComFunc::GridSelRow(CMSHFlexGrid &m_grid, ULONG row)
{
	long cols=m_grid.GetCols(0);
	m_grid.SetCol(0);
	m_grid.SetRow(row);
	m_grid.SetRowSel(row);
	m_grid.SetColSel(cols-1);
}
/*
// 根据提供的内部挂号类型,返回程序中使用的相应
// 的数字标识
*/
int CComFunc::GetGhType(CString &strType)
{
	int iRet =0 ;

	if( strType.Compare("QPYB") == 0 || strType.Compare("QPTD") == 0  || strType.Compare("QHMT") == 0 ){ //因为编码前缀不同
		
		iRet=TYPE_QPYB; // 清浦医保
			
	}
	else if( strType.Compare("基本保险") == 0 || strType.Compare("特定门诊") == 0 ||
		strType.Compare("家庭病床")==0  || 
		strType.Compare("GMMT_201001")==0 )
		//20090916,因淮电要求新增“居民门特”类别，内部代号为：GMMT_090916,操作与市基本医保差不多
		//20100105,因淮电要求新增"清河门诊"类别，内部代号为：GMMT_201001,操作与市医保差不多
	{
		iRet=TYPE_HAYB; //市医保基本
	}
	else if( strType.Compare("居民统筹") == 0  || strType.Compare("GMMT_090916") == 0 ){

		iRet=TYPE_JMTC; //市医保居民统筹
	}
	else if ( strType.Compare("补充保险") == 0  )
	{
		iRet=TYPE_BCBX;
	}
	else if ( strType.Compare("供养亲属") == 0  )
	{
		iRet=TYPE_GYQS;
	}
	else if ( strType.Compare("工伤人员") == 0  )
	{
		iRet=TYPE_GS;
	}
	else if ( strType.Compare("离休人员") == 0  )
	{
		iRet=TYPE_LX;
	}
	else if ( strType.Compare("退养人员") == 0  )
	{
		iRet=TYPE_TY;
	}
	else if ( strType.Compare("建国前老工人") == 0  )
	{
		iRet=TYPE_GC;
	}
	else 
		iRet=0;

	return iRet;

}

bool CComFunc::GetString(CString & strSql, CString *pS, int num)
{
	int i;
	for( i=0; i<num; i++ ) pS[i]=BLANKSTR;

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		if(!recSet->adoEOF){
			for( i=0; i< num ;i++ )
				pS[i]=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
		}
			
		recSet->Close();

		return true;

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}	

}

bool CComFunc::GetSql(CString &strOut, UINT id)
{

	CString strSql;
	strOut=BLANKSTR;
	strSql.Format( " SELECT sql FROM lsq_sql_statemnet WHERE id= %ld ",id);

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
		
			strOut=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(0L)->Value );
		}
		recSet->Close();

		return true;

	}
	catch(_com_error e)
	{
		strOut=BLANKSTR;
		AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}	
}

bool CComFunc::BeginCritical(CString strID, bool flag)
{
	int ib;
	CString strSql;
	if( flag ){
		try{
			_CommandPtr cmd;
			_ParameterPtr par;
			cmd.CreateInstance(__uuidof( Command ));
			par.CreateInstance(__uuidof( Parameter));
			
			_variant_t vNULL;
			vNULL.vt = VT_ERROR;
			vNULL.scode = DISP_E_PARAMNOTFOUND;
			
			cmd->put_CommandType(adCmdStoredProc) ;
			par=cmd->CreateParameter(_bstr_t("success"),adUnsignedInt,adParamOutput,20,vNULL);
			cmd->Parameters->Append( par );
			
			par=cmd->CreateParameter(_bstr_t("paraID"),adVarChar,adParamInput,50,_bstr_t( strID ) );
			cmd->Parameters->Append( par );
			
			cmd->put_CommandText(_bstr_t("PRC_gh_check"));
			cmd->ActiveConnection=HospitalConnect;
			cmd->Execute(NULL,NULL,adCmdStoredProc);
			
			ib=cmd->Parameters->GetItem("success")->Value.uintVal;
			cmd.Detach();
			par.Detach();
			if ( ib ) return true;
			else return false;
			
		}
		catch(_com_error e)
		{
			AfxMessageBox(e.ErrorMessage());
			return false;
		}
		



	}
	else{ //解除冲突
	
		strSql.Format(" Delete From lsq_share Where serial='%s' ",strID);
		if( !CComFunc::WriteSql(strSql) )AfxMessageBox("解决共享冲突时出现错误!!");
		return true;
		

	}
}

CString CComFunc::GetSqlItem(long i)
{
	CString str(BLANKSTR);
	str=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
	return str;
}
/*
// 通过传入的SQL语句,自动获取数据填充表格
*/
/*
void CComFunc::ReadDataForGrid(CString &strSql, CMSHFlexGrid &m_grid)
{
	long row(0),i;
	long cols=m_grid.GetCols(0);
	try{

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		m_grid.SetRedraw(false);
		while(! recSet->adoEOF){

			strSql.Format("%ld",row); //显示序列号,重新计算,数据库选择时的行号已被打乱
			m_grid.SetTextMatrix(row,0,strSql);
			for( i=1; i< cols ; i++ )
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
				m_grid.SetTextMatrix(row,i,strSql);
			}
			row++;
			m_grid.AddItem(BLANKSTR,_variant_t(row));
			recSet->MoveNext();

		}
		recSet->Close();
		GridSelRow(m_grid,1);
		m_grid.SetRedraw(true);
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}
}
*/
//**********************************************************
//# 根据表格ID值,将表格相应的列设置颜色
//
//***********************************************************

UINT CComFunc::SetGridColColor( UINT id,CMSHFlexGrid &pGrid)
{
	//数组第一列存放 列号,第二列存放 颜色值

	CUIntArray arrCol,arrBack,arrFore;
	CString strSql;
	int iRgb[3];
	long i(0),x,iLine(0);
	strSql.Format(" Select rank,cR,cG,cB,cR2,cG2,cB2 from lsq_grid_col WHERE id=%ld and color =1  order by rank ",id );
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			strSql= (char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value ) ;
			arrCol.Add( atol(strSql) );
			for(x=0; x< 3; x++ ) //背景色
			{
				++i;
				strSql= (char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value ) ;
				iRgb[x]=atol(strSql);
			}
			arrBack.Add( RGB(iRgb[0],iRgb[1],iRgb[2] ) );

			for(x=0; x< 3; x++ ) //前景色
			{
				++i;
				strSql= (char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value ) ;
				iRgb[x]=atol(strSql);
			}
			arrFore.Add( RGB(iRgb[0],iRgb[1],iRgb[2] ) );

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
	long colorCols=arrCol.GetSize() ; //需要设置色彩的列数

	if( colorCols > 0 ){
		long row=pGrid.GetRows()-1 ;
		while( row > 0 ){
			
			pGrid.SetRow(row);
			for( i=0 ; i<  colorCols ; i++ )
			{
				pGrid.SetCol( arrCol[i] -1 ); //数据库中记录的第一列从零开始
				pGrid.SetCellBackColor(arrBack[i] );
				pGrid.SetCellForeColor(arrFore[i] );
			}
			row -- ;
		}
	}

	return true;
}

UINT CComFunc::ForWait(LPVOID pw)
{
	CDialogWait dw;
	dw.DoModal();

	return true;
}

CDialog * CComFunc::SysWait(CDialog* pt)
{
	CDialogWait *pw=new CDialogWait;
	pw->Create(IDD_DIALOG_WAIT,pt);
	pw->ShowWindow(SW_SHOW);
//	pw->UpdateData();
	return (CDialog*)pw;
}

void CComFunc::ReadDataForGrid(CString &strSql, CMSHFlexGrid &m_grid, int *iCol, int iSum)
{
	long row(0),i;
	long cols=m_grid.GetCols(0);
	double *dbSum=NULL;
	CString strTmp;


	if( iSum > 0 )	{
		dbSum=new double[iSum];
		for(i=0 ; i < iSum; i++ )dbSum[i]=0.0;
	}

	try{

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		m_grid.SetRedraw(false);
		while(! recSet->adoEOF){

			strSql.Format("%ld",row); //显示序列号,重新计算,数据库选择时的行号已被打乱
			m_grid.SetTextMatrix(row,0,strSql);
			for( i=1; i< cols ; i++ )
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
				m_grid.SetTextMatrix(row,i,strSql);
				for(int x=0; x<iSum ; x++ )
				{
					if( iCol[x] == i )dbSum[x]+=atof(strSql);

				}
			}
			row++;
			m_grid.AddItem(BLANKSTR,_variant_t(row));
			recSet->MoveNext();

		}
		recSet->Close();
		for(i=0 ; i< iSum ; i++ )//填写汇总行
		{	
			strTmp.Format("%.2f",dbSum[i]);
			m_grid.SetTextMatrix(row,iCol[i],strTmp);
			

		}
		if(iSum > 0 ) delete[] dbSum;
		GridSelRow(m_grid,1);
		m_grid.SetRedraw(true);
	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		recSet->Close();
		return ;
	}
}

void CComFunc::GetBigMoney(const double &dMoney, CString &strReturnValue)
{
     CString strMoney;

     strMoney.Format ("%.2f" , dMoney);

	 if( strMoney.GetLength() >15 ){
		 strReturnValue="￥"+strMoney;
		 return ; //数值太大
	 }

     CString strUnit = "元拾佰仟万拾佰仟亿拾佰仟";

     CString strNumber = "零壹贰叁肆伍陆柒捌玖";

     CString strOtherUnit = "整角分";

 

     //将数字分整数部份与小数部份处理

     int nPos = strMoney.Find (".");
     int nLength = strMoney.GetLength ();
     if(nPos < 0)
         nPos = nLength;
 //    CString strReturnValue;
     int nCount = 0;
     bool bZero = false;
     bool bNeedLevel = false;    //对段的识别，用于是否需要出现段名，如亿，万等
     //对整数部份进行反相识别处理

     for(int i = nPos - 1;i >= 0;i --)
     {
         TCHAR ch = strMoney.GetAt (i);
         if(nCount % 4 == 0 && nCount > 0)
         {
               //如果处理的数字为第四位（万），或第八位（亿）等，则要求置段
              bNeedLevel = true;
         }
         if(ch == '0')
         {
               //只对拾佰仟位的０进行识别，主要考虑到拾的特殊性，即如１０读壹拾，不会读壹拾零
              if(nCount % 4 != 0)

                   bZero = true;
         }
         else
         {

              CString strTemp(strReturnValue);

              strReturnValue = strNumber.Mid ((ch - 0x30) * 2 , 2);

              if(nCount > 0)

              {

                  strReturnValue += strUnit.Mid (nCount * 2 , 2);

                   if(nCount % 4 != 0 && bNeedLevel)

                   {

                         //这里判断是否需要读段名，如万，亿等

                       strReturnValue += strUnit.Mid (int(nCount / 4) * 8 , 2);

                   }

                   bNeedLevel = false;

              }

              if(bZero)

              {

                   //只有比当前处理的位要低中有数字才补零

                   if(!strTemp.IsEmpty ())

                       strReturnValue += strNumber.Left (2);

                   bZero = false;

              }

              strReturnValue += strTemp;

         }

         nCount ++;

     }

     strReturnValue += strUnit.Left (2);
	 if(strReturnValue.GetLength()<=2) strReturnValue="";
	 //防止整数部分为零

     bool bAllZero = true;

     //下面实现对小数点后面的处理

     //先判断是否为全零，则不需要继续读

     if(nPos < nLength)

     {

         if(nLength > 2)

              nLength = 2;

         for(int i = 0;i < nLength;i ++)

              if(strMoney.GetAt (nPos + i + 1) != '0')

                   bAllZero = false;

     }

     if(bAllZero)

     {

         strReturnValue += strOtherUnit.Left (2);

     }

     else

     {

          //对分角的处理

         for(int i = 0;i < nLength;i ++)

         {

              TCHAR ch = strMoney.GetAt (nPos + 1 + i);

              if(ch == '0' && i > 0)

              {

              }

              else

              {

                   strReturnValue += strNumber.Mid ((ch - 0x30) * 2 , 2);

                   if(ch != '0')

                       strReturnValue += strOtherUnit.Mid ((i + 1) * 2 , 2);

              }

         }

     }

  //   return strReturnValue;
}

bool CComFunc::GetStringCollect(CString &strSql, CStringArray &ary)
{

	ary.RemoveAll();
	const int i=0;

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		while(!recSet->adoEOF){
				ary.Add( (char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value ) );
				recSet->MoveNext();
		}
			
		recSet->Close();

		return true;

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}	

}
// 解密变换后的字符
BOOL CComFunc::DecryptString(const string& encPass, string& decPass)
{
	int iLen=encPass.length();
	decPass="";
	unsigned char tmpCh,r[2];
	int i(0);
	if ( ! iLen ) return false;

	int iIdx=0;

	while( i< iLen )
	{

		r[0]=encPass[i];
		r[1]=encPass[++i];

		iIdx=0;
		while(iIdx<2)
		{
			if( r[iIdx]>='A' )r[iIdx]-=('A'-10);
			else r[iIdx]-='0';
			iIdx++;
		}
		r[1]<<=4;

		r[1]+=r[0];

		r[1]-=(i/2);

		decPass.push_back(r[1]);
		i++;

	}





	return true;
}

// 初始化表格头部标题
BOOL CComFunc::SetGridHeader(CGridCtrl & m_grid,int col_name_id,vector<int> &vtAlign )
{
	CString strSql;
	struct HEADER_STRUCT {
		string col_name;
		unsigned long bk_color;
		unsigned long fc_color;
		long width;
		int align;
	} grid_header;


	vector<HEADER_STRUCT> vHeader;
	strSql.Format(" Select name,bk_color,fc_color,col_width,align FROM gx_col_name Where id=%ld and eft=1 ORDER by sq ",col_name_id);

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		long col=0;
		while(!recSet->adoEOF){
			
			col=0;
			grid_header.col_name=CComFunc::GetSqlItem(col++);
			grid_header.bk_color= CComFunc::GetRGBfromStr( CComFunc::GetSqlItem(col++) ) ;
			grid_header.fc_color=CComFunc::GetRGBfromStr( CComFunc::GetSqlItem(col++)  );
			grid_header.width=atol(CComFunc::GetSqlItem(col++));
			grid_header.align=atol(CComFunc::GetSqlItem(col++));
			vtAlign.push_back(grid_header.align);
			vHeader.push_back(grid_header);

			recSet->MoveNext();
		
		}
		recSet->Close();

	}

	catch(_com_error e)

	{

		AfxMessageBox(TEXT("数据库连接出错！"));

		AfxMessageBox(e.Description());
		return false;


	}

	m_grid.SetColumnCount( vHeader.size() );
	m_grid.SetRowCount(2);
	m_grid.SetFixedRowCount(1);
	m_grid.SetEditable(false);


	


	for(int i=0; i<vHeader.size() ; i++)
	{
		m_grid.SetItemFormat(0,i,37U); //居中对齐
		if( vHeader[0].bk_color )
			m_grid.SetItemBkColour(0,i,vHeader[0].bk_color);	//以列中第一栏背景设置,前景也同样
		if( vHeader[0].fc_color )
			m_grid.SetItemFgColour(0,i,vHeader[0].fc_color);
		m_grid.SetItemText(0,i,vHeader[i].col_name.c_str() );
		m_grid.SetColumnWidth(i,vHeader[i].width);
	
	}

	return true;
}

BOOL CComFunc::SqlComboRead(CComboBox & comboInsert, vector<int> &vtID, CString & strSql)
{

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
	
		while(!recSet->adoEOF){

			vtID.push_back(atoi( CComFunc::GetSqlItem(0L) )) ;
			comboInsert.AddString( CComFunc::GetSqlItem(1L) ) ;


			recSet->MoveNext();
		
		}
		recSet->Close();

	}

	catch(_com_error e)

	{

		AfxMessageBox(TEXT("数据库连接出错！"));

		AfxMessageBox(e.Description());
		return false;


	}

	return true;
}


// 参数：表格控件引用，SQL语句，表格列数，要汇总的列，汇总数据存入位置，序号所在列，单元格对齐数据
BOOL CComFunc::ReadDataForGrid(CGridCtrl& m_grid, CString & strSql,int gridCols,vector<int> &vtCols,vector<double> &vtCount,int sn,
	vector<int> &vtAlign )
{


	m_grid.SetListMode();
	m_grid.SetSingleRowSelection(true);

	m_grid.SetFrameFocusCell(false);
	m_grid.SetTrackFocusCell(false);
	m_grid.SetRowCount(1);

	vector<double>::size_type iCols=vtCols.size();
	vector<int>::iterator  iteTmp;
	int iAry;
	vector<int>::size_type iNum=vtAlign.size(); //测试是否有对齐数据

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		long i(1);
		long col(0);
		//以下变量用于合并单元格
		//vector<	int>  iBegin(gridCols,1),iCounting(gridCols,1);
		//CStringArray aryBegin;
		//aryBegin.SetSize(gridCols);

		while(!recSet->adoEOF){
			m_grid.InsertRow("xx");

			while( col < gridCols ){

				strSql=CComFunc::GetSqlItem(col) ;


				m_grid.SetItemFormat(i,col,iNum==0?0:vtAlign[col] );	

				if( col == sn ){
					strSql.Format("%d",i);
					m_grid.SetItemFormat(i,col,37U);
				}

				m_grid.SetItemText(i,col,strSql);
				//if( col <6 ){
				//	if( iCounting[col] == 1){
				//		aryBegin[col] =strSql;
				//		iCounting[col]++;
				//	}else{ 
				//		if ( strSql.Compare(aryBegin[col] ) == 0 ) iCounting[col]++;
				//		else
				//		{
				//			aryBegin[col]=strSql;
				//			if(  iCounting[col]-1-iBegin[col] !=0  )
				//				m_grid.MergeCells(iBegin[col],col,iCounting[col]-1,col);
				//			iBegin[col]= iCounting[col]++;
				//		}
				//	}
				//}
			if( ( iteTmp= std::find(vtCols.begin(),vtCols.end(),col) )  !=vtCols.end()  && iCols > 0 )
			{

				iAry=iteTmp-vtCols.begin();
				vtCount[iAry]+=atof(strSql);
				m_grid.SetItemFormat(i,col,DT_RIGHT);
			}

			col++;
		}

		col=0;
		i++;

		recSet->MoveNext();

	}
		recSet->Close();






	}

	catch(_com_error e)

	{

		AfxMessageBox(TEXT("数据库连接出错！"));

		AfxMessageBox(e.Description());
		return false;


	}


	return true;
}


void CComFunc::callSqlPro(vector<string> & vtSzPara , string & szRet)
{
	//函数第一参数为存储过程名


	using namespace std;
	ostringstream strFormat;
	int i=1;
	while( i < vtSzPara.size() ){		//构造以字符 "|" 分隔的字符串
		strFormat<<vtSzPara[i]<<"|";
		i++;
	}

	
	_CommandPtr cmd;
	_ParameterPtr par;
	cmd.CreateInstance(__uuidof( Command ));
	par.CreateInstance(__uuidof( Parameter));

	_variant_t vNULL;
	vNULL.vt = VT_ERROR;
	vNULL.scode = DISP_E_PARAMNOTFOUND;

	try{
		cmd->put_CommandType(adCmdStoredProc) ;
	
		//入参
		par=cmd->CreateParameter(_bstr_t("szPara"),adVarChar,adParamInput, strFormat.str().length()  ,  _bstr_t( strFormat.str().c_str() )  );
		cmd->Parameters->Append( par );

		//出参
		par=cmd->CreateParameter(_bstr_t("szRet"),adVarChar,adParamOutput,1024,vNULL);
		cmd->Parameters->Append( par);


		cmd->put_CommandText(_bstr_t( vtSzPara[0].c_str() ));
		cmd->ActiveConnection=HospitalConnect;
		cmd->Execute(NULL,NULL,adCmdStoredProc);
		
		//获取返回值
		szRet=LPCSTR(_bstr_t( cmd->Parameters->GetItem("szRet")->Value) );

		
		cmd.Detach();
		par.Detach();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return;
	}	
}
//元素从 1 开始编号
bool CComFunc::ExtractElement(const string & src, int idx /*提取第idx成员 */, string & dst,char seperateChr)
{
	unsigned int iPos=idx;
	std::size_t iBegin,iEnd;

	dst="";
	
	iPos--;
	iBegin=0;
	while( iPos-- )
	{
		iBegin=src.find(seperateChr,iBegin);
		if ( iBegin ==string::npos ) return false;
		iBegin++;

	}
	
	iEnd=src.find(seperateChr,iBegin);
	if( iEnd == string::npos )  iEnd = src.size(); //末尾无分隔符结束
	
	dst=src.substr(iBegin,iEnd-iBegin);
	
	return true;
}

// 从规范字符串提取数据
bool CComFunc::GenerateSubStr(string & szSrc, CStringArray& strAry, CComboBox& cbDst)
{
	unsigned int i(0);
	string szEle;
	for( i=1; i< szSrc.size() ; i++)
	{
		if(  ! CComFunc::ExtractElement(szSrc,i,szEle) )break;
		if( i % 2 ) strAry.Add(szEle.c_str() );
		else cbDst.AddString( szEle.c_str() );
			
	}
	return true;
}


void CComFunc::callSqlPro(vector<string> & vtSzPara, _RecordsetPtr & localRec)
{
	//函数第一参数为存储过程名


	using namespace std;
	ostringstream strFormat;
	int i=1;
	while( i < vtSzPara.size() ){		//构造以字符 "|" 分隔的字符串
		strFormat<<vtSzPara[i]<<"|";
		i++;
	}

	
	_CommandPtr cmd;
	_ParameterPtr par;
	cmd.CreateInstance(__uuidof( Command ));
	par.CreateInstance(__uuidof( Parameter));

	_variant_t vNULL;
	vNULL.vt = VT_ERROR;
	vNULL.scode = DISP_E_PARAMNOTFOUND;

	try{
		cmd->put_CommandType(adCmdStoredProc) ;
	
		//入参
		par=cmd->CreateParameter(_bstr_t("szPara"),adVarChar,adParamInput, strFormat.str().length()  ,  _bstr_t( strFormat.str().c_str() )  );
		cmd->Parameters->Append( par );

		//出参
		par=cmd->CreateParameter(_bstr_t("szRet"),adVarChar,adParamOutput,1024,vNULL);
		cmd->Parameters->Append( par);


		cmd->put_CommandText(_bstr_t( vtSzPara[0].c_str() ));
		cmd->ActiveConnection=HospitalConnect;
		localRec=cmd->Execute(NULL,NULL,adCmdStoredProc);
		
		//获取返回值
		//szRet=LPCSTR(_bstr_t( cmd->Parameters->GetItem("szRet")->Value) );

		
		cmd.Detach();
		par.Detach();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return;
	}	
}

/*
*	Summary:
*			根据用户提供的结果集，填充表格，并根据用户提供的统计列号进行数据相加放到最后汇总行
*
*	Date：2014/10/29
*   Author:LingShaoQing
*/
BOOL CComFunc::ReadDataForGrid(CGridCtrl& m_grid, _RecordsetPtr &localRec,vector<int> &vtCols,vector<double> &vtCount,
	vector<int> &vtAlign )
{


	m_grid.SetListMode();
	m_grid.SetSingleRowSelection(true);

	m_grid.SetFrameFocusCell(false);
	m_grid.SetTrackFocusCell(false);
	m_grid.SetRowCount(1);

	vector<double>::size_type iCols=vtCols.size();
	vector<int>::iterator  iteTmp;
	int iAry;
	vector<int>::size_type iNum=vtAlign.size(); //测试是否有对齐数据
	int gridCols=localRec->GetFields()->GetCount();
	CString strSql;
			long i(1);
	try{

		long col(0);

		while(!localRec->adoEOF){
			m_grid.InsertRow("xx");
			
			while( col < gridCols ){

				strSql=(char*)_bstr_t(localRec->GetFields()->GetItem(long(col))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):localRec->GetFields()->GetItem(long(col))->Value );

				m_grid.SetItemFormat(i,col,iNum==0?0:vtAlign[col]+DT_SINGLELINE );	
				m_grid.SetItemText(i,col,strSql);
				//统计汇总列
				if( ( iteTmp= std::find(vtCols.begin(),vtCols.end(),col) )  !=vtCols.end()  && iCols > 0 )
				{

					iAry=iteTmp-vtCols.begin();
					vtCount[iAry]+=atof(strSql);
				//	m_grid.SetItemFormat(i,col,DT_RIGHT);
				}
			//增量序号
			strSql.Format("%ld",i);
			m_grid.SetItemText(i,0,(LPCTSTR)strSql);
	
				col++;
			}

			col=0;
			i++;
			localRec->MoveNext();
		}
		localRec->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return false;
	}
	if ( vtCols.size() ){
		m_grid.InsertRow("合计");
		m_grid.SetItemFormat(i,0,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		for( int x=0 ; x< iCols ; x++ )//填写汇总行
		{	
			strSql.Format("%.2f",vtCount[x]);
			m_grid.SetItemText(i,vtCols[x],strSql);
			m_grid.SetItemFormat(i,vtCols[x],vtAlign[vtCols[x]]+DT_SINGLELINE );

		}
		for(int x=0; x< gridCols ;x++)
		{
			m_grid.SetItemBkColour(i,x,RGB(0,89,198));
			m_grid.SetItemFgColour(i,x,RGB(255,255,255));
		}
	}
	m_grid.Refresh();
	return true;
}
//CMSHFlexGrid &
/*
	用于从记录集中猎取数据并显示
	*/
BOOL CComFunc::ReadDataForGrid(CMSHFlexGrid & m_grid, _RecordsetPtr &localRec,vector<int> &vtCols,vector<double> &vtCount,
	vector<int> &vtAlign )
{
	int gridCols=localRec->GetFields()->GetCount();

	vector<double>::size_type iCols=vtCols.size();
	vector<int>::iterator  iteTmp;
	int iAry;
	vector<int>::size_type iNum=vtAlign.size(); //测试是否有对齐数据


	CString strSql;
	try{
		long i(1);
		long col(1);
		m_grid.SetRedraw(false);
		while(!localRec->adoEOF){

			strSql.Format("%ld",i); //显示序列号,重新计算,数据库选择时的行号已被打乱
			m_grid.SetTextMatrix(i,0,strSql);

			while( col < gridCols ){

				strSql=(char*)_bstr_t(localRec->GetFields()->GetItem(long(col))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):localRec->GetFields()->GetItem(long(col))->Value );
				m_grid.SetTextMatrix(i,col,strSql);
				if( ( iteTmp= std::find(vtCols.begin(),vtCols.end(),col) )  !=vtCols.end()  && iCols > 0 )
				{

					iAry=iteTmp-vtCols.begin();
					vtCount[iAry]+=atof(strSql);

				}
				
				col++;
			}

			col=1;
			i++;
		
			m_grid.AddItem(BLANKSTR,_variant_t(i));

			localRec->MoveNext();
		}
		localRec->Close();

		for( int x=0 ; x< iCols ; x++ )//填写汇总行
		{	
			strSql.Format("%.2f",vtCount[x]);
			m_grid.SetTextMatrix(i,vtCols[x],strSql);
			

		}

		m_grid.SetRedraw(true);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return false;
	}
	return true;
}

unsigned long CComFunc::GetRGBfromStr(CString & strRGB)
{
	const char SPERATOR=',';
	const char R_BRACKETS=')';
	unsigned start_pos=4; //数字开始位
	strRGB.Trim(' ');
	int iPos=0;
	unsigned char rgb[4]={0,0,0,0};
	unsigned char x=0;

	while(x<2)
	{
		iPos=strRGB.Find(SPERATOR, start_pos);
		if( iPos != -1 )rgb[x++]=atoi( strRGB.Mid(start_pos,iPos-start_pos) );
		else break;
		start_pos=iPos+1;
	}
	iPos=strRGB.Find(R_BRACKETS,start_pos);
	if( iPos != -1 )rgb[x]=atoi( strRGB.Mid(start_pos,iPos-start_pos) ); //最后一位为括号

	return RGB(rgb[0],rgb[1],rgb[2]);
}


void CComFunc::ToExcel(CGridCtrl& pg)
{
	_Application app2;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;
	 COleVariant vOpt2(DISP_E_PARAMNOTFOUND,VT_ERROR);

	CProgressEx pp;
	CRect r1(0,0,400,25);
	pp.Create(WS_CHILD |PBS_SMOOTH|WS_BORDER ,r1,AfxGetMainWnd()->GetForegroundWindow(),IDC_PROGRESS_EXCEL);
	pp.UpdateWindow();
	pp.ShowWindow(SW_SHOW);
	pp.CenterWindow();
	pp.Invalidate();
	unsigned long iRows=pg.GetRowCount();
	int iCols=pg.GetColumnCount();
	pp.SetRange32(0,iRows );
	pp.strView="正在准备导出...请稍等!!";

	app2.CreateDispatch("excel.application");
	if(!app2){
		AfxMessageBox("请注意系统中必须装有EXCEL97 或者 EXCEL2000 ,否则此功能不能使用...");
		return;
	}
	books2=app2.GetWorkbooks();
	//		book2=books2.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	book2=books2.Add(vOpt2);
	sheets2=book2.GetWorksheets();
	sheet2=sheets2.GetItem(COleVariant((short)1));


	Range vRange;
	SQ_EXCEL9::Font font;
	long x,y;
	CString str1,str2;
	
	app2.SetVisible(false);
	pp.strView="";


	for (x=0; x<iRows; x++)
	{
		for( y=0 ; y< iCols ; y++ )
		{
			if( y<26)str1.Format("%c%ld",'A'+y , x+1 );
			else str1.Format("%c%c%ld",'A'+ ( y/26 -1) ,'A'+y % 26,x+1 );
			vRange=sheet2.GetRange(_variant_t(str1),_variant_t(str1)); // 医疗机构
			vRange.SetValue(COleVariant(pg.GetItemText(x,y)));
		}
		
		pp.strView.Format("%2.0f%%",double(x)/iRows*100);
		pp.SetPos(x);
	}
	app2.SetVisible(true);
		
	pp.DestroyWindow();
	sheet2.ReleaseDispatch();

	sheets2.ReleaseDispatch();

	book2.ReleaseDispatch();
	books2.ReleaseDispatch();
	app2.ReleaseDispatch();	
}
