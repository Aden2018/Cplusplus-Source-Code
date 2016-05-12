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

void CGenericMedCode::OnDblClickMshflexgrid1() //������˫�����м�����������ļ����ڿ��
{
//{"���","ҩƷ����","ҩƷ����","���","��λ","����","��������","���","�ƻ�����"} ;//�� 8 ��
//	CString HeadTitle[]={"����","С��","����","����","���","��λ","ƴ��"}
	long row=m_grid.GetRow();
	long allRow=m_grid.GetRows();
	if(allRow<3 || 0==row || allRow-1 == row ){
		AfxMessageBox("��˫��Ҫѡ���ҩƷ��Ŀ......");
		return;
	}
	long prows=((CMSHFlexGrid *)theApp.pParentGrid.pGrid)->GetRows()-1;

	CString str1,strSql;
	str1.Format("%ld",prows);
	((CMSHFlexGrid *)theApp.pParentGrid.pGrid)->SetTextMatrix(prows,0,str1);

	for( int i=0; i<4 ; i++){
		((CMSHFlexGrid *)theApp.pParentGrid.pGrid)->SetTextMatrix(prows,i+1,m_grid.GetTextMatrix(row,i+2));
	}
	

	prows++; //����һ��
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
		AfxMessageBox("��ѯ�������ERROR...");
		recSet->Close();
		return;
	}








}

