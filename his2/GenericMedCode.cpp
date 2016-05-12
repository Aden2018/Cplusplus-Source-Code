// GenericMedCode.cpp: implementation of the CGenericMedCode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "GenericMedCode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGenericMedCode::CGenericMedCode()
{

}

CGenericMedCode::~CGenericMedCode()
{

}

BOOL CGenericMedCode::OnInitDialog()
{
	CMedCodeQuery::OnInitDialog();

	return true;

}

void CGenericMedCode::OnDblClickMshflexgrid1() //根据所双击的行计算出上期消耗及现在库存
{
//{"编号","药品编码","药品名称","规格","单位","进价","上月消耗","库存","计划购进"} ;//共 8 列
//	CString HeadTitle[]={"大类","小类","编码","名称","规格","单位","拼音"}
	long row=m_grid.GetRow();
	long allRow=m_grid.GetRows();
	if(allRow<3 || 0==row || allRow-1 == row ){
		AfxMessageBox("请双击要选择的药品条目......");
		return;
	}
	long prows=((CMSHFlexGrid *)theApp.pParentGrid.pGrid)->GetRows()-1;

	CString str1,strSql;
	str1.Format("%ld",prows);
	((CMSHFlexGrid *)theApp.pParentGrid.pGrid)->SetTextMatrix(prows,0,str1);

	for( int i=0; i<4 ; i++){
		((CMSHFlexGrid *)theApp.pParentGrid.pGrid)->SetTextMatrix(prows,i+1,m_grid.GetTextMatrix(row,i+2));
	}
	

	prows++; //最大的一行
	((CMSHFlexGrid *)theApp.pParentGrid.pGrid)->AddItem(" ",_variant_t(prows) );

	try{
		strSql.Format("SELECT SUM(sl),MIN(jinjia) FROM MEDLIE WHERE YPBM='%s'",m_grid.GetTextMatrix(row,2) );
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(1l))->Value.vt==VT_NULL?"0":recSet->GetFields()->GetItem(_variant_t(1l))->Value);
			str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(0l))->Value.vt==VT_NULL?"0":recSet->GetFields()->GetItem(_variant_t(0l))->Value);
			((CMSHFlexGrid *)theApp.pParentGrid.pGrid)->SetTextMatrix(prows-1,5,strSql) ;
			((CMSHFlexGrid *)theApp.pParentGrid.pGrid)->SetTextMatrix(prows-1,6,"0") ;
		
			((CMSHFlexGrid *)theApp.pParentGrid.pGrid)->SetTextMatrix(prows-1,7,str1) 	;
			recSet->Close();
		}
	}
	catch(_com_error e)
	{
		AfxMessageBox("查询库存数量ERROR...");
		recSet->Close();
		return;
	}








}

