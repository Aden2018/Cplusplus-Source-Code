// CodeGysQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "CodeGysQuery.h"
#include "codeGysEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeGysQuery dialog


CCodeGysQuery::CCodeGysQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CCodeGysQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCodeGysQuery)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	curRow=0;
	strFlag="";
}


void CCodeGysQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCodeGysQuery)
	DDX_Control(pDX, IDCANCEL, m_x2);
	DDX_Control(pDX, IDOK, m_x1);
	DDX_Control(pDX, IDC_EDIT4, c_name);
	DDX_Control(pDX, IDC_EDIT3, c_bm);
	DDX_Control(pDX, IDC_EDIT1, c_py);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCodeGysQuery, CDialog)
	//{{AFX_MSG_MAP(CCodeGysQuery)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_QM_CODEGYS_ADD, OnQmCodegysAdd)
	ON_COMMAND(ID_QM_CODEGYS_DEL, OnQmCodegysDel)
	ON_COMMAND(ID_QM_CODEGYS_MODIFY, OnQmCodegysModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeGysQuery message handlers

BOOL CCodeGysQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();

	fontTitle.CreatePointFont(200,"宋体");
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);

	m_grid.SetRows(2);
	m_grid.Clear();
//	m_grid.SetRedraw(false);

	CString HeadTitle[]={"编码","名称","拼音"},getTitle[]={"gongbm","gongmc","py"};
	long  headWidth[]={1800,1200,1200,400,1300,1300,1200,2000};

	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		m_grid.SetColWidth(i,headWidth[count]);

//		p2->m_grid.SetRow(0);
//		p2->m_grid.SetCol(i);
//		p2->m_grid.SetColAlignment(i,4);//flexAlignCenterCenter 4 单元格的内容居中、居中对齐	

		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	
	OnOK();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCodeGysQuery::OnOK() 
{
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetRedraw(false);

	CString HeadTitle[]={"编码","名称","拼音","flag"},getTitle[]={"gongbm","gongmc","py","flag"};
	long  headWidth[]={1200,3400,1200,00,1300,1300,1200,2000};

	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0;
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		if(count<2)m_grid.SetMergeCol(i,true);// 前6列单元格进行合并
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}	

	CString strSql,str1,str2,str3;
	long j,x;
	c_py.GetWindowText(str1);
	c_bm.GetWindowText(str2);
	c_name.GetWindowText(str3);
	try{
		
		strSql.Format("select * from codegys where py like '%s%%' and gongbm like '%s%%' and gongmc like '%s%%' ",\
			str1,str2,str3);
		strSql+=strFlag; //查询供应商还是产地由strFlag决定

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		j=1;
		while(!recSet->adoEOF){
			x=0;
			for(count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
				
				str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(getTitle[count])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(getTitle[count])));
				m_grid.SetTextMatrix(j,x++,str1);
			}
				
			
			m_grid.AddItem(" ",_variant_t(++j));
			
			recSet->MoveNext();
		
		}
		recSet->Close();
		m_grid.SetTextMatrix(j,0,"合计");
		m_grid.SetRedraw(true);
		strSql.Format("共查询到: %ld 条记录",j-1);
		GetDlgItem(IDC_STATIC_NOTI)->SetWindowText(strSql);

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		AfxMessageBox(strSql);
		return ;
	}		
	
	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow = 1;
		for( i=1;i<3;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}




}

void CCodeGysQuery::OnChangeEdit1() 
{
//	AfxMessageBox("base ccodeGysQuery");
	OnOK();
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CCodeGysQuery::OnChangeEdit3() 
{

	OnOK();
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CCodeGysQuery::OnChangeEdit4() 
{
	OnOK();
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

HBRUSH CCodeGysQuery::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->m_hWnd == GetDlgItem(IDC_STATIC_NOTI)->m_hWnd)pDC->SetTextColor(RGB(255,0,0));
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BEGIN_EVENTSINK_MAP(CCodeGysQuery, CDialog)
    //{{AFX_EVENTSINK_MAP(CCodeGysQuery)
	ON_EVENT(CCodeGysQuery, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CCodeGysQuery, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CCodeGysQuery::OnDblClickMshflexgrid1() 
{

	long rows=m_grid.GetRows();
	long row=m_grid.GetRow();
	if(rows<3 || row>=rows-1)return;

	strNum=m_grid.GetTextMatrix(row,0);//bm;
	strName=m_grid.GetTextMatrix(row,1);//mc;
	CDialog::OnOK();


}

void CCodeGysQuery::OnClickMshflexgrid1() 
{
	// TODO: Add your control notification handler code here
/*	long r1;
	r1=m_grid.GetRow();
	if(r1 >= m_grid.GetRows()-1 || curRow == r1)return;

	m_grid.SetCol(0);
	m_grid.SetRow(curRow);
	UINT color=m_grid.GetCellBackColor();

	for(int i=1;i<3;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(color);
	}
	m_grid.SetRow(r1);
	curRow=r1;
	for( i=1;i<3;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(RGB(255,0,0));
	}
*/
	const int ENDLINES=2;
	if(m_grid.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		
		long r1;
		r1=m_grid.GetRow();
		if(r1 >= m_grid.GetRows()-1 || curRow == r1)return;
		
		m_grid.SetCol(0);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();
		
		for(int i=1;i<3;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
		m_grid.SetRow(r1);
		curRow=r1;
		for( i=1;i<3;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}	
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_MEDLIST);
	CMenu* pmenu=pm.GetSubMenu(2); //供应商操作
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  

}

void CCodeGysQuery::OnQmCodegysAdd() 
{
	CCodeGysEdit gysedit;
	gysedit.flag = 2;
	if(gysedit.DoModal() == IDOK) OnOK();
	
}

void CCodeGysQuery::OnQmCodegysDel() 
{
	long rows=m_grid.GetRows();
	long row=m_grid.GetRow();
	if(rows<3 || row>=rows-1)return;

	CString strSql;
	strSql.Format("将要删除下列产地或供应商:(%s ,%s) ",m_grid.GetTextMatrix(row,0),m_grid.GetTextMatrix(row,1) );
	if( MessageBox(strSql,"提示",MB_OKCANCEL|MB_ICONINFORMATION) == IDCANCEL) return;
	try{
		strSql.Format("DELETE FROM codegys WHERE gongbm='%s' ",m_grid.GetTextMatrix(row,0));
		HospitalConnect->BeginTrans();
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();


	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		HospitalConnect->RollbackTrans();
		return;

	}

	AfxMessageBox("成功删除当前记录...");
	OnOK();
}

void CCodeGysQuery::OnQmCodegysModify() 
{
	long rows=m_grid.GetRows();
	long row=m_grid.GetRow();
	if(rows<3 || row>=rows-1)return;

	CCodeGysEdit gysedit;

	gysedit.flag = 1;
	gysedit.m_str[0]=m_grid.GetTextMatrix(row,0);//bm;
	gysedit.m_str[1]=m_grid.GetTextMatrix(row,1);//mc;
	gysedit.m_str[2]=m_grid.GetTextMatrix(row,2); // py
	gysedit.m_str[3]=m_grid.GetTextMatrix(row,3);//flag 供应商还是产地
//	CDialog::OnOK();

	if(	gysedit.DoModal()== IDOK) OnOK();
	
}
