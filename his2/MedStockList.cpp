// MedStockList.cpp : implementation file
//

#include "stdafx.h"
#include "his2.h"
#include "MedStockList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedStockList dialog
#define COLS 11
#define DOWN_ARROR 0x28
#define UP_ARROR 0x26

CMedStockList::CMedStockList(CWnd* pParent /*=NULL*/)
	: CDialog(CMedStockList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMedStockList)
	//}}AFX_DATA_INIT
	curRow=0;
	brushBack.CreateSolidBrush(RGB(58,110,165));
	flagMoveKF=0;
}


void CMedStockList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedStockList)
	DDX_Control(pDX, IDC_EDIT_MESSAGE, c_message);
	DDX_Control(pDX, IDC_EDIT_PY, c_py);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedStockList, CDialog)
	//{{AFX_MSG_MAP(CMedStockList)
	ON_EN_CHANGE(IDC_EDIT_PY, OnChangeEditPy)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedStockList message handlers

BOOL CMedStockList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect r2;
	GetWindowRect(r2);

	long x,y;
	y=r2.bottom-r2.top;
	x=r2.right-r2.left;

	r2.top=r1.bottom;
	r2.bottom=r2.top+y;
	r2.left=r1.left;
	r2.right=r2.left+x;

	MoveWindow(r2);

	OnOK();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMedStockList::OnOK() 
{
	UpdateData();

	CString HeadTitle[]={"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","售价","进价","指导价"}; //共 13 列

	long  headWidth[]={0,00,2000,1600,600,0,1400,0,1600,1000,1000,0,0};
														//6
	CString getTitle[]={"ID","BM","MC","GG","DW","RQ1","RQ2","GONGBM","GONGMC","SL",\
		"SELL_PRICE","JINJIA","COACH_PRICE"};

	m_grid.SetRows(2);
	m_grid.Clear();
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 列。用户可以用鼠标来重新调整列的大小。 
	m_grid.SetMergeCells(true); //设定单元格可以进行合并
	m_grid.SetCols(sizeof(HeadTitle)/sizeof(CString));
	m_grid.SetFixedCols(0);
	long  i=0,col(0),row(0);
	for(int count=0;count<sizeof(HeadTitle)/sizeof(CString);count++){
		m_grid.SetColWidth(i,headWidth[count]);
		m_grid.SetTextArray(i++,HeadTitle[count]);
	}		

	CString strSql,str1;
	int y1,y2,m1,m2 ;
	c_py.GetWindowText(str1);
	if(str1.IsEmpty())return;
	try{
		//选出药品数量大于0,且不过期的药品
		if( flagMoveKF == 112 ) //盘点时用
			strSql.Format("SELECT id,bm,mc,sl,rq1,to_char(rq2,'yyyy-mm-dd') as rq2,\
				gongbm,gongmc,gg,dw, jinjia,to_char(sysdate,'yyyy-mm-dd') as curdate,\
				sell_price,Coach_price,kfbm ,x.py py,get_date \
				from medlie t,medcode x,codegys y where t.ypbm=x.bm \
				and y.gongbm=t.factorycode and kfbm='%s' and x.py like '%s%%' order by bm,get_date ",\
				strSelKF,str1);
		else if ( flagMoveKF == 113 ) //报损时用
		{
			strSql.Format("SELECT id,bm,mc,sl,rq1,to_char(rq2,'yyyy-mm-dd') as rq2,\
				gongbm,gongmc,gg,dw, jinjia,to_char(sysdate,'yyyy-mm-dd') as curdate,\
				sell_price,Coach_price,kfbm ,x.py py,get_date \
				from medlie t,medcode x,codegys y where t.ypbm=x.bm \
				and y.gongbm=t.factorycode and kfbm='%s' and x.py like '%s%%' \
				AND sl > 0 order by bm,get_date ",\
				strSelKF,str1);

			
		}
		else 
			strSql.Format("select * from V_MEDLIST where kfbm='%s' and py like '%s%%'  order by bm,get_date ",LoginInformation.kfbm,str1 );
		
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
	
		row=1;
		double dX;
		while(!recSet->adoEOF){
			col=0;
			for(i=0;i<sizeof(getTitle)/sizeof(CString);i++)
			{
				str1=(char*)_bstr_t(recSet->GetCollect(_variant_t(getTitle[i])).vt==VT_NULL?" ":recSet->GetCollect(_variant_t(getTitle[i])));
				if( 6 == i ){
					strSql=(char*)_bstr_t(recSet->GetCollect("CURDATE"));
					y1=atoi(str1.Left(4));
					m1=atoi(str1.Mid(5,2)); //日期
					
					y2=atoi(strSql.Left(4)); //当前日期
					m2=atoi(strSql.Mid(5,2));

				//	if( (y1 == y2 && m1-3<m2) || (y1-1 == y2 && 12+m1-3<m2) ) { //大于三个月的特显
					if( (y1-y2)*12+m1-3 <= m2 ){
						m_grid.SetRow(row);
						m_grid.SetCol(col);
						m_grid.SetCellBackColor(RGB(255,128,0));
					}

				}
				if( 10 == i){
					dX=atof(str1);
					str1.Format("%.2f",dX);
				}
				m_grid.SetTextMatrix(row,col++,str1);
			}
			row++;
			m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();

		}
		recSet->Close();

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return;
	}
	strSql.Format("共查询到:  %ld  条信息",row-1);
	c_message.SetWindowText(strSql);
	if(m_grid.GetRows()>2)
	{
		m_grid.SetRow(1);
		curRow=1;
		for( i=1;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
	}


}

void CMedStockList::OnChangeEditPy() 
{
	OnOK();
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
BOOL CMedStockList::PreTranslateMessage(MSG* pMsg) 
{
	
/*	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){
		if(GetFocus()->m_hWnd==GetDlgItem(IDC_EDIT_PY)->m_hWnd)
		{
				if(m_grid.GetRows()<3){
					c_py.SetFocus();
					return true;
				}

				m_grid.SetFocus();
				curRow=1;
				m_grid.SetRow(1);
			
				for(int i=0;i<11;i++){
					m_grid.SetCol(i);
					m_grid.SetCellBackColor(RGB(255,0,0));
				}
				return true;

			}else if(GetFocus()->m_hWnd==GetDlgItem(IDC_MSHFLEXGRID1)->m_hWnd )
			{
				CMSHFlexGrid * pGrid=(CMSHFlexGrid *) theApp.pParentGrid.pGrid;
				
				long row=pGrid->GetRows()-1;
				if( 0 == curRow || curRow == m_grid.GetRows()-1 )return true;			

				for(int i=0;i<13;i++){
					pGrid->SetTextMatrix(row,i,m_grid.GetTextMatrix(curRow,i));
				}
				CString str1;
				c_sl.GetWindowText(str1);
				if(str1.IsEmpty() || atof(str1) == 0.0 )str1="1";
			
				if(atof(str1) > atof(m_grid.GetTextMatrix(curRow,9) ))//库存量 
					str1.Format("%.2f",atof(m_grid.GetTextMatrix(curRow,9) ));
				else str1.Format("%.2f",atof(str1));

				pGrid->SetTextMatrix(row,i,str1);
				row++;
				pGrid->AddItem(" ",_variant_t(row));
					
				c_sl.SetWindowText("");
				m_grid.Clear();
				m_grid.SetRows(2);
				c_py.SetWindowText("");
				c_py.SetFocus();
			
				OnCancel();
			
				return true;


			}
			else{

				GetNextDlgTabItem(GetFocus())->SetFocus();
				((CEdit*)GetFocus())->SetSel(0,((CEdit*)GetFocus())->LineLength(-1));
				
				return true;
				

			}
	
	}
*/
	if(pMsg->message == WM_KEYDOWN )
		if(pMsg->wParam == VK_RETURN )OnDblClickMshflexgrid1();
		else if( pMsg->wParam==VK_DOWN)
			m_grid.SetFocus();

	return CDialog::PreTranslateMessage(pMsg);
}

BEGIN_EVENTSINK_MAP(CMedStockList, CDialog)
    //{{AFX_EVENTSINK_MAP(CMedStockList)
	ON_EVENT(CMedStockList, IDC_MSHFLEXGRID1, -602 /* KeyDown */, OnKeyDownMshflexgrid1, VTS_PI2 VTS_I2)
	ON_EVENT(CMedStockList, IDC_MSHFLEXGRID1, -601 /* DblClick */, OnDblClickMshflexgrid1, VTS_NONE)
	ON_EVENT(CMedStockList, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CMedStockList::OnKeyDownMshflexgrid1(short FAR* KeyCode, short Shift) 
{
	long rows=m_grid.GetRows()-2;

	if( DOWN_ARROR == * KeyCode){  //下箭头按下动作
	
		m_grid.SetCol(12);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();

		for(int i=0;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
	
		if(curRow < rows && curRow!= 0 ) m_grid.SetRow(++curRow);
		else {
				curRow=1;
				m_grid.SetRow(curRow);

		}
		for( i=0;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}
		

	}
	else if(UP_ARROR == * KeyCode){ //上箭头按下动作


		m_grid.SetCol(12);
		m_grid.SetRow(curRow);
		UINT color=m_grid.GetCellBackColor();

		for(int i=0;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(color);
		}
	
		if(curRow <= rows && curRow!= 1) m_grid.SetRow(--curRow);
		else {
				curRow=rows;
				m_grid.SetRow(curRow);

		}
		for( i=0;i<COLS;i++){
			m_grid.SetCol(i);
			m_grid.SetCellBackColor(RGB(255,0,0));
		}



	}
}


HBRUSH CMedStockList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	pDC->SetBkMode(TRANSPARENT);
	if(nCtlColor == CTLCOLOR_EDIT || pWnd->m_hWnd == c_message.m_hWnd
		|| nCtlColor== CTLCOLOR_STATIC ){
		pDC->SetTextColor(RGB(255,255,0));
		pDC->SetBkColor(RGB(58,110,165));
	}
	return brushBack;
//	return (HBRUSH) brushBack.GetSafeHandle();
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
#define COLOR_FOR_EDIT RGB(0,36,72)
void CMedStockList::OnDblClickMshflexgrid1() 
{
	CMSHFlexGrid * pGrid=(CMSHFlexGrid *) theApp.pParentGrid.pGrid;
	long row=pGrid->GetRows()-1;
	if( 0 == curRow || curRow == m_grid.GetRows()-1 )return ;			
	for(int i=0;i<13;i++){
		pGrid->SetTextMatrix(row,i,m_grid.GetTextMatrix(curRow,i));
		
	}
	pGrid->SetRow(row);
	pGrid->SetCol(i);
	pGrid->SetCellBackColor(COLOR_FOR_EDIT);
	if( 112 == flagMoveKF || 113 == flagMoveKF  ){

		pGrid->SetTextMatrix(row,i+1,strSelKfName);
		pGrid->SetTextMatrix(row,i+2,strSelKF);
	}
	row++;
	pGrid->AddItem(" ",_variant_t(row));
				
	if( 111 == flagMoveKF || 112 == flagMoveKF || 113 == flagMoveKF) { //111为转库用,112为盘点用
			c_py.SetWindowText("");
			c_message.SetWindowText("");
			c_py.SetFocus();
			
					
	}
	else CDialog::OnOK();
				
				
				
}

void CMedStockList::OnClickMshflexgrid1() 
{
	long r1;
	r1=m_grid.GetRow();
	if(r1>=m_grid.GetRows()-1 || curRow== r1)return;

	m_grid.SetCol(0);
	m_grid.SetRow(curRow);
	UINT color=m_grid.GetCellBackColor();

	for(int i=1;i<COLS;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(color);
	}
	m_grid.SetRow(r1);
	curRow=r1;
	for( i=1;i<COLS;i++){
		m_grid.SetCol(i);
		m_grid.SetCellBackColor(RGB(255,0,0));
	}
	// TODO: Add your control notification handler code here
	
}
