// MedCodeQuery.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "MedCodeQuery.h"
#include "medDetail.h"
#include "medcodeModify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedCodeQuery dialog


CMedCodeQuery::CMedCodeQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CMedCodeQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMedCodeQuery)
	//}}AFX_DATA_INIT
	fontTitle.CreatePointFont(220,"宋体");
	FlagRollMED=0;
	curRow=0;
}


void CMedCodeQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedCodeQuery)
	DDX_Control(pDX, IDOK, m_2);
	DDX_Control(pDX, IDCANCEL, m_1);
	DDX_Control(pDX, IDC_COMBO_DL, c_comDL);
	DDX_Control(pDX, IDC_COMBO_XL, c_comXL);
	DDX_Control(pDX, IDC_EDIT_PY, c_py);
	DDX_Control(pDX, IDC_EDIT_MC, c_mc);
	DDX_Control(pDX, IDC_EDIT_BM, c_bm);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedCodeQuery, CDialog)
	//{{AFX_MSG_MAP(CMedCodeQuery)
	ON_CBN_SELCHANGE(IDC_COMBO_DL, OnSelchangeComboDl)
	ON_CBN_SELCHANGE(IDC_COMBO_XL, OnSelchangeComboXl)
	ON_EN_CHANGE(IDC_EDIT_PY, OnChangeEditPy)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_MENU_MEDCODE_MODIFY, OnMenuMedcodeModify)
	ON_COMMAND(ID_MENU_MEDCODE_ADD, OnMenuMedcodeAdd)
	ON_COMMAND(ID_MENU_MEDCODE_DELETE, OnMenuMedcodeDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedCodeQuery message handlers

BOOL CMedCodeQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fontTitle);
	m_grid.SetRows(2);
	m_grid.Clear();
//	m_grid.SetRedraw(false);

//	CString HeadTitle[]={"大类","小类","名称","规格","拼音"};
	CString HeadTitle[]={"大类","小类","编码","名称","规格","单位","拼音"};

	long  headWidth[]={1400,1400,1600,1600,1200,1300,1200,2000};

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

	CString strSql;
	try{
		c_comDL.AddString("   ");
		strSql.Format("select dlmc from meddl ");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetCollect("dlmc").vt==VT_NULL?" ":recSet->GetCollect("dlmc"));
			c_comDL.AddString(strSql);
			recSet->MoveNext();
		
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return false;
	}	// TODO: Add extra initialization here

	
	
	
	
	
	
	CenterWindow();
//	AnimateWindow(m_hWnd,500,AW_SLIDE|AW_CENTER);
//	Invalidate();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMedCodeQuery::OnSelchangeComboDl() 
{
	if(c_comDL.GetCurSel() == CB_ERR || c_comDL.GetCurSel() == 0 )return;
	while(c_comXL.DeleteString(0)!=CB_ERR);

	CString strSql,str1;
	c_comDL.GetLBText(c_comDL.GetCurSel(),str1);
	try{
		c_comXL.AddString("   ");
		strSql.Format("select xlmc from medxl,medDL where medxl.dlbm = meddl.dlbm and dlmc='%s' ",str1);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			strSql=(char*)_bstr_t(recSet->GetCollect("xlmc").vt==VT_NULL?" ":recSet->GetCollect("xlmc"));
			c_comXL.AddString(strSql);
			recSet->MoveNext();
		
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}	//	// TODO: Add your control notification handler code here
	OnOK();
}

void CMedCodeQuery::OnOK() 
{
	// TODO: Add extra validation here
	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetRedraw(false);
	curRow=0;

	CString HeadTitle[]={"大类","小类","编码","名称","规格","单位","拼音"},\
		getTitle[]={"dlmc","xlmc","bm","mc","gg","dw","py"};

	long  headWidth[]={1400,1600,1200,2000,1600,800,1300,1200,2000};

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

	CString strSql,str1,str2,str3,strdl,strxl;
	long j,x;
	c_py.GetWindowText(str1);
	c_bm.GetWindowText(str2);
	c_mc.GetWindowText(str3);
	try{
		if(c_comDL.GetCurSel()==0 || c_comDL.GetCurSel()==CB_ERR){
			strSql.Format("select * from medcode t,meddl x,medxl y where t.dlbm=x.dlbm \
				and t.xlbm=y.xlbm and y.dlbm=t.dlbm and py like '%s%%' and bm like '%s%%' \
				and mc like '%s%%' ",str1,str2,str3);

		}
		else {
			c_comDL.GetLBText(c_comDL.GetCurSel(),strdl);
			if(c_comXL.GetCurSel()== 0 || c_comXL.GetCurSel()==CB_ERR){
				strSql.Format("select * from medcode t,meddl x,medxl y where t.dlbm=x.dlbm \
					 and t.xlbm=y.xlbm and y.dlbm=t.dlbm and dlmc='%s' and py like '%s%%' and bm like '%s%%' \
					 and mc like '%s%%'  ",strdl,str1,str2,str3);


			}else
			{
				c_comXL.GetLBText(c_comXL.GetCurSel(),strxl);
				strSql.Format("select * from medcode t,meddl x,medxl y where t.dlbm=x.dlbm \
					 and t.xlbm=y.xlbm and y.dlbm=t.dlbm and dlmc='%s' and \
					 xlmc='%s' and py like '%s%%' and bm like '%s%%' \
					 and mc like '%s%%'  ",strdl,strxl,str1,str2,str3);


			}


		}
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
	


	
//	CDialog::OnOK();
}

void CMedCodeQuery::OnSelchangeComboXl() 
{

	OnOK();
}

void CMedCodeQuery::OnChangeEditPy() 
{

	OnOK();// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

HBRUSH CMedCodeQuery::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	

	if(pWnd->m_hWnd == GetDlgItem(IDC_STATIC_TITLE)->m_hWnd || pWnd->m_hWnd == \
		GetDlgItem(IDC_STATIC_NOTI)->m_hWnd)pDC->SetTextColor(RGB(255,0,0));
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BEGIN_EVENTSINK_MAP(CMedCodeQuery, CDialog)
    //{{AFX_EVENTSINK_MAP(CMedCodeQuery)
	ON_EVENT(CMedCodeQuery, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CMedCodeQuery, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CMedCodeQuery::OnDblClickMshflexgrid1() 
{

	long row=m_grid.GetRow();
	long allRow=m_grid.GetRows();
	if(allRow<3 || 0==row || allRow-1 == row ){
		AfxMessageBox("请双击要选择的药品条目......");
		return;
	}
	theApp.pParentGrid.pQuery=&m_grid;
	CMedDetail med;
	if( FlagRollMED == 8888 ) med.FlagRollMED=8888; //是否为退药标志
	else med.FlagRollMED=0;
	med.DoModal();

}

void CMedCodeQuery::OnClickMshflexgrid1() 
{
/*	const int STARTCOL=2,ENDCOL=7;

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		long r1;
		r1=m_grid.GetRow();
		if(r1 >= m_grid.GetRows()-1 || curRow == r1)return;
		
		m_grid.SetCol(0);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();
		
		for(int i=STARTCOL;i<ENDCOL;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
		m_grid.SetRow(r1);
		curRow=r1;
		for( i=STARTCOL;i<ENDCOL;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
		return ;
	}	

*/
	const int ENDLINES=2;
	if(m_grid.GetRows() == ENDLINES )return;//判断是否需要显示快捷菜单

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202为鼠标左键,0x205为鼠标右键消息
		
		const int STARTCOL=2,ENDCOL=7;
		long r1;
		r1=m_grid.GetRow();
		if(r1 >= m_grid.GetRows()-1 || curRow == r1)return;
		
		m_grid.SetCol(0);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();
		
		for(int i=STARTCOL;i<ENDCOL;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
		m_grid.SetRow(r1);
		curRow=r1;
		for( i=STARTCOL;i<ENDCOL;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_MEDLIST);
	CMenu* pmenu=pm.GetSubMenu(3); //药品操作
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  



}

void CMedCodeQuery::OnMenuMedcodeModify()  //修改
{
// HeadTitle[]={"大类","小类","编码","名称","规格","单位","拼音"
	CMedcodeModify med;

	CString strSql;
	long i=0;
	med.strOldBm=m_grid.GetTextMatrix(curRow,2);
	try{
		strSql.Format("select dlmc,xlmc,mc,gg,dw,maxkc,minkc,py,bz from medcode a,meddl b,medxl c WHERE a.dlbm=b.dlbm \
			AND a.xlbm=c.xlbm AND b.dlbm=c.dlbm AND bm='%s' ",med.strOldBm);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			med.dlmc=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL ? " ":recSet->GetFields()->GetItem(i)->Value );
			i++;
			med.xlmc=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL ? " ":recSet->GetFields()->GetItem(i)->Value );
			i++;
			med.m_mc=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL ? " ":recSet->GetFields()->GetItem(i)->Value );
			i++;
			med.m_gg=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL ? " ":recSet->GetFields()->GetItem(i)->Value );
			i++;
			med.m_dw=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL ? " ":recSet->GetFields()->GetItem(i)->Value );
			i++;
			med.m_max=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL ? " ":recSet->GetFields()->GetItem(i)->Value );
			i++;
			med.m_min=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL ? " ":recSet->GetFields()->GetItem(i)->Value );
			i++;
			med.m_py=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL ? " ":recSet->GetFields()->GetItem(i)->Value );
			i++;
			med.m_comment=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt==VT_NULL ? " ":recSet->GetFields()->GetItem(i)->Value );
	
		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox("出现错误,请检查SQL语句...");
		return ;
	}	// TODO: Add extra initialization here
	med.flagMode =CMedcodeModify::MODIFY; //ADD
	med.DoModal();
	
}

void CMedCodeQuery::OnMenuMedcodeAdd() // 新增
{
	CMedcodeModify med;
	med.DoModal();
	// TODO: Add your command handler code here
	
}

void CMedCodeQuery::OnMenuMedcodeDelete() //删除
{
	
}
