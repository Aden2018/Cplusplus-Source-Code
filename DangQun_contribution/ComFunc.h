// ComFunc.h: interface for the CComFunc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMFUNC_H__30CA6A5B_6188_40BF_B4C4_88989FF5E104__INCLUDED_)
#define AFX_COMFUNC_H__30CA6A5B_6188_40BF_B4C4_88989FF5E104__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mshflexgrid.h"
#include "excel9.h"
#include <string>
#include "GridCtrl.h"
#include <vector>
using namespace std;
using namespace SQ_EXCEL9;
class CComFunc  
{
public:
	static bool GetStringCollect(CString &strSql,CStringArray &ary);
	static void GetBigMoney(const double & dMoney,CString & strReturnValue);
	static void  ReadDataForGrid(CString &strSql,CMSHFlexGrid &m_grid,int  *iCol=NULL,int  iSum=0);
	static BOOL ReadDataForGrid(CGridCtrl& m_grid, CString & strSql,int gridCols,vector<int> &vtCols,vector<double> &vtCount,int sn,
	vector<int> &vtAlign );
	//提供_RecordsetPtr,直接填充表格
	static BOOL ReadDataForGrid(CGridCtrl& m_grid, _RecordsetPtr & localRec,vector<int> &vtCols=vector<int>(),
		vector<double> &vtCount=vector<double>(),vector<int> &vtAlign=vector<int>() );
	static BOOL ReadDataForGrid(CMSHFlexGrid & m_grid, _RecordsetPtr & localRec,vector<int> &vtCols=vector<int>(),
		vector<double> &vtCount=vector<double>(),vector<int> &vtAlign=vector<int>() );

	static CDialog * SysWait(CDialog* pt);
	static UINT SetGridColColor(UINT id,CMSHFlexGrid &pGrid );
//	static void ReadDataForGrid(CString &strSql,CMSHFlexGrid &m_grid);
	static CString GetSqlItem(long i);
	static bool BeginCritical(CString strID,bool flag);
	static bool GetSql(CString &strOut,UINT id);
	static bool GetString( CString &strSql,CString *pS,int num);
	enum{ TYPE_QPYB=1,TYPE_HAYB=2,TYPE_JMTC=3,TYPE_BCBX=4,TYPE_GYQS=5,
		TYPE_GS=6,TYPE_LX=7,TYPE_TY=8,TYPE_GC=9 };

	static int GetGhType(CString & strType);
	static void GridSelRow(CMSHFlexGrid &m_grid, ULONG row);
	static void SetExcelCell(_Worksheet &sheetx,int iRow, int iCol, CString &strData);
	static bool AssertPriv(UINT id);
	static UINT THREAD_TO_EXCEL(LPVOID lp);
	static BOOL comSetGridHeader(CMSHFlexGrid &m_grid,ULONG id );
	static BOOL SetGridHeader(CGridCtrl & m_grid,int col_name_id,vector<int> &vtAlign );
	static void ToExcel(CMSHFlexGrid * pg);
	static void writeDebug(CString strout);
	static BOOL WriteSql(CString strSql);
	static CString GetString(CString strSql);
	static UINT ForWait(LPVOID pw);
	CComFunc();
	virtual ~CComFunc();
	static BOOL DecryptString(const string& encPass, string& decPass);
	static BOOL SqlComboRead(CComboBox & comboInsert, vector<int> &vtID, CString & strSql);
	static void callSqlPro(vector<string> & vtSzPara ,string & szRet);
	static bool ExtractElement(const string & src, int idx, string & dst,char seperateChr='|' );
	// 从规范字符串提取数据
	static bool GenerateSubStr(string & szSrc, CStringArray& strAry, CComboBox& cbDst);
	static void callSqlPro(vector<string> & vtSzPara, _RecordsetPtr & localRec);

	static unsigned long GetRGBfromStr(CString & strRGB);
	static void ToExcel(CGridCtrl& pg);
};

#endif // !defined(AFX_COMFUNC_H__30CA6A5B_6188_40BF_B4C4_88989FF5E104__INCLUDED_)
