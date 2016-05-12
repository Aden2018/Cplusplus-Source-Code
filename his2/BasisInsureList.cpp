// BasisInsureList.cpp: implementation of the CBasisInsureList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "BasisInsureList.h"
#include "baseRymodify.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBasisInsureList::CBasisInsureList()
{

}

CBasisInsureList::~CBasisInsureList()
{

}

BOOL CBasisInsureList::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	CRect r1,r2;
	GetDlgItem(IDC_STATIC_3)->GetWindowRect(r1);
	ScreenToClient(r1);
	GetDlgItem(IDC_COMBO1)->GetWindowRect(r2);
	ScreenToClient(r2);
	GetDlgItem(IDC_STATIC_2)->MoveWindow(r1);
	GetDlgItem(IDC_EDIT2)->MoveWindow(r2);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText("基本保险人员查询");
	GetDlgItem(ID_SEARCH)->ShowWindow(SW_HIDE);
	return true;
}

void CBasisInsureList::OnOK()
{
	BeginWaitCursor();
	//卡号,姓名,性别,出生日期,工作日期,部门,结存金额,工作性质
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetRedraw(false);

	long j=0, i=0,x=0;
	CString HeadTitle[]={"yc","卡号","姓名","性别","pass","2","x","x","x","x"},str1;

	long  headWidth[]={0,2000,1400,800,00,00,00,00,00,0,0};
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	for(long count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		m_grid.SetColWidth(i,headWidth[count]);


		m_grid.SetTextArray(i++,HeadTitle[count]);
	}
	CString strSql,strName,strID,strDepart;

	m_name.GetWindowText(strName);
	m_kahao.GetWindowText(strID);
	j=1;
	try{
		strSql.Format("select 1,卡号,姓名,性别,pass from 医保人员列表 WHERE 卡号 like '%s%%' and 姓名 like '%s%%' ORDER BY 姓名 ",strID,strName);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			x=0;
			for(count=0 ; count < 5 ; count++){
				
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(count))->Value.vt==VT_NULL ? " " : recSet->GetFields()->GetItem(_variant_t(count))->Value );
				
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

BOOL CBasisInsureList::PreTranslateMessage(MSG *pMsg)
{
	if(pMsg->message == WM_KEYDOWN )
	{
		if(pMsg->wParam == VK_RETURN ){
			OnOK();
			return true;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);

}

void CBasisInsureList::OnClickMshflexgrid2()
{
	const long ENDLINES=2;
	if(m_grid.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		CEmployeeQuery::SetSel();
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_MEDLIST);
	CMenu* pmenu=pm.GetSubMenu(iMenuSel+1); //基本医保人员快捷菜单
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  

}

void CBasisInsureList::OnMenuQuickBaseryDel()  //* 删除基本保险用户
{
//	if(!theApp.AssertRole(ROLE_EMP_EDIT))return;  //* 权限设置


	CString strSql;
	long rows=m_grid.GetRows();
	long curRow=m_grid.GetRow();
	if( curRow == 0 || curRow == rows-1 ) return ; //*如果选择了标题行或最后一行则退出

	strSql.Format("确认要删除 (%s)/(%s) 吗???",m_grid.GetTextMatrix(curRow,1),m_grid.GetTextMatrix(curRow,2) );
	if( AfxMessageBox(strSql,MB_OKCANCEL)== IDCANCEL) return;
	try{
		HospitalConnect->BeginTrans();
		strSql.Format("Delete from 医保人员列表 where 卡号='%s' ",m_grid.GetTextMatrix(curRow,1));
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();
	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox("删除失败...");
		return;
	}
		
	m_grid.RemoveItem(curRow);
	AfxMessageBox("删除成功!!!");

}

void CBasisInsureList::OnMenuQuickBaseryViewpassword() //* 查看基本保险用户密码
{
	CString strSql;
	long rows=m_grid.GetRows();
	long curRow=m_grid.GetRow();
	if( curRow == 0 || curRow == rows-1 ) return ; //*如果选择了标题行或最后一行则退出
	strSql.Format("SELECT pass From 医保人员列表 where 卡号='%s' ",m_grid.GetTextMatrix(curRow,1));
	strSql.Format("该用户基本信息为:\n\n姓名:%s 性别:%s\n卡号:%s\n密码:%s",m_grid.GetTextMatrix(curRow,2),\
		m_grid.GetTextMatrix(curRow,3),m_grid.GetTextMatrix(curRow,1),COtherDecharge::GetStringTitle(strSql));
	AfxMessageBox(strSql);

}

void CBasisInsureList::OnMenuQuickBaseryModify() //* 修改基本保险用户信息
{
	CString strSql;
	long rows=m_grid.GetRows();
	long curRow=m_grid.GetRow();
	if( curRow == 0 || curRow == rows-1 ) return ; //*如果选择了标题行或最后一行则退出
	CBaseRyModify rm;
	rm.pGrid=&m_grid;
	rm.selRow=curRow;
	rm.DoModal();

}
