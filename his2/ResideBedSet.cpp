// ResideBedSet.cpp: implementation of the CResideBedSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "ResideBedSet.h"
#include "resideBedSetAdd.h"
#include "resideBedModify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResideBedSet::CResideBedSet()
{
	//分别代表区域  房间  床位 代码和名称位置
	strBedName="";
	strBedCode="";
	strTitle="病床位基本查询";
	arrayLocal.RemoveAll();
	DIALOG_FLAG=DIALOG_BED;
}

CResideBedSet::~CResideBedSet()
{

}

BOOL CResideBedSet::OnInitDialog()
{
	CResideLocalSet::OnInitDialog();
	GetDlgItem(IDC_STATIC_LOCAL)->SetWindowText("所属房间");
	CString strSql;
	strSql.Format(" SELECT Rcode,Rname FROM lsq_reside_room WHERE Reffect='1' ");
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		m_combox.AddString("");
		while(!recSet->adoEOF){
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(0l))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(0l))->Value);
				arrayLocal.Add(strSql);
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(1l))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(1l))->Value);
				m_combox.AddString(strSql);

				recSet->MoveNext();
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description() );
		return false;
	}
	return true;
}

void CResideBedSet::SetGridHead()
{
	CString HeadTitle[]={"区域编码","区域名称","房间编码","房间名称","床位编码","床位名称","价格","备注"};
	long  headWidth[]={0,2000,0,2200,0,2000,1600,2400};
		
	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0,col(0),row(0);
	m_grid.SetRow(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
	
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetCol((long) count);
		m_grid.SetCellAlignment((short)4); //居中对齐
		
		m_grid.SetTextArray(i++,HeadTitle[count]);
		m_grid.SetColAlignment(count,1);//中间左对齐
		
	}
}

void CResideBedSet::OnMenuResideLocalAdd()
{
	CResideBedSetAdd sa;
	sa.DoModal();
}

void CResideBedSet::OnMenuResideLocalDel()
{
	if( CheckSelectRow() == FAIL) return;
	CString strBm1=m_grid.GetTextMatrix(curRow,4);//获取床位编码

	CString strSql;
	strSql.Format("确认要删除: %s / %s ",m_grid.GetTextMatrix(curRow,BEDCODE_POS),m_grid.GetTextMatrix(curRow,BEDNAME_POS) );
	if( MessageBox(strSql,"提示",MB_OKCANCEL|MB_ICONINFORMATION  ) == IDCANCEL) return;

	strSql.Format("update lsq_reside_bed set beffect='0' Where bcode='%s' ",strBm1);
	if( COtherDecharge::WriteSQL(strSql) ){
		AfxMessageBox("删除成功");
		m_grid.RemoveItem(curRow);
	}
	else AfxMessageBox("删除失败");

}

void CResideBedSet::OnMenuResideLocalModify()
{
	if( CheckSelectRow() == FAIL) return;
	CResideBedModify bm;
	bm.m_strBedCode=m_grid.GetTextMatrix(curRow,4);//床位代码
	bm.m_price=atof(m_grid.GetTextMatrix(curRow,6));//价格
	bm.m_strName=m_grid.GetTextMatrix(curRow,5); //名字
	bm.m_strRemark=m_grid.GetTextMatrix(curRow,7);//备注
	bm.strLocal=m_grid.GetTextMatrix(curRow,1);//区域名称
	bm.strRoom=m_grid.GetTextMatrix(curRow,3); //房间名称
	if( bm.DoModal()==IDOK) OnMenuResideLocalRefresh();
}

void CResideBedSet::OnMenuResideLocalRefresh()
{
	UpdateData();
	SetGridHead();
	CString strSql,str1;
	m_grid.SetRedraw(false);
	long row,i,cols;

	try{
		strSql.Format( "select a.llocal,a.lname,b.rcode,b.rname,c.bcode,c.bname,c.bprice,c.bremark from lsq_reside_local a,\
			lsq_residE_Room b ,lsq_reside_bed c where a.llocal=b.rlocal and b.rcode=c.broom and c.beffect='1' \
			AND c.Reff='0' AND c.bcode like '%s%%' AND c.bName like '%s%%' ",m_strBm,m_strMc );
		i=m_combox.GetCurSel();
		if( i== CB_ERR || i == 0 );
		else {
			strSql+=" AND b.rcode='"+arrayLocal.GetAt(i-1)+"'";
		}
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		row=1;
		while(!recSet->adoEOF){
			for(i=0;i< cols ;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?"":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				m_grid.SetTextMatrix(row,i,str1);
			}
			row++;
			m_grid.AddItem("",_variant_t(row));
			recSet->MoveNext();
			
		}
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		recSet->Close();
	
		return ;
	}	


  m_grid.SetRedraw(true);;
}

void CResideBedSet::OnDblClickMshflexgrid1()
{
	if( DIALOG_FLAG == DIALOG_BED ) return;
	if( CheckSelectRow() == FAIL ) return;
	
	strBedCode=m_grid.GetTextMatrix(curRow,BEDCODE_POS);
	strBedName=m_grid.GetTextMatrix(curRow,ROOMNAME_POS)+"/"+m_grid.GetTextMatrix(curRow,BEDNAME_POS);
	CDialog::OnOK();
}
