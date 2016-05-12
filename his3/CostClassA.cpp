// CostClassA.cpp : implementation file
//

#include "stdafx.h"
#include "his3.h"
#include "CostClassA.h"
#include "costClassaAdd.h"
#include "costClassAmodify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCostClassA dialog


CCostClassA::CCostClassA(CWnd* pParent /*=NULL*/)
	: CDialog(CCostClassA::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCostClassA)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCostClassA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCostClassA)
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCostClassA, CDialog)
	//{{AFX_MSG_MAP(CCostClassA)
	ON_COMMAND(ID_MENU_COST_ADD, OnMenuCostAdd)
	ON_COMMAND(ID_MENU_COST_MODIFY, OnMenuCostModify)
	ON_COMMAND(ID_MENU_COST_DEL, OnMenuCostDel)
	ON_COMMAND(ID_MENU_COST_RESTORE, OnMenuCostRestore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCostClassA message handlers

BOOL CCostClassA::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	OnOK();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCostClassA::OnOK() 
{
	CString strSql;

	CComFunc::comSetGridHeader(m_grid,GRID_HEADER_ID); 
	CComFunc::GetSql(strSql,SQL_QUERY_ID);
	
	CComFunc::ReadDataForGrid(strSql,m_grid);
	
}

BEGIN_EVENTSINK_MAP(CCostClassA, CDialog)
    //{{AFX_EVENTSINK_MAP(CCostClassA)
	ON_EVENT(CCostClassA, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CCostClassA::OnClickMshflexgrid1() //�����Ҽ��˵�
{
//	const int ENDLINES=2;
//	if(m_grid.GetRows() == ENDLINES )return;//�ж��Ƿ���Ҫ��ʾ��ݲ˵�

	MSG *pms;
	pms=(MSG*)GetCurrentMessage();
	if(pms->message != 0x205) {//0x202Ϊ������,0x205Ϊ����Ҽ���Ϣ
		return;
	}
	CMenu pm;
	CPoint p;
	pm.LoadMenu(IDR_MENU_QUICK);
	CMenu* pmenu=pm.GetSubMenu(4);
	GetCursorPos(&p);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON ,p.x,p.y,this);  	
	// TODO: Add your control notification handler code here
	
}

void CCostClassA::OnMenuCostAdd() //����µ�֧����Ŀ
{
	CCostClassAadd aa;
	if( aa.DoModal()== IDOK)
		OnOK();
	// TODO: Add your command handler code here
	
}

void CCostClassA::OnMenuCostModify() //�޸�֧����Ŀ
{
	long selRow=m_grid.GetRow();
	if( selRow== 0 ||  selRow==m_grid.GetRows()-1 )
	{
		AfxMessageBox("����ѡ��Ҫ�޸ĵ���");
		return;//�ж��Ƿ���Ҫ��ʾ��ݲ˵�
	}

	CCostClassAmodify am;
	am.m_id=atol(m_grid.GetTextMatrix(selRow,GRID_ID));
	am.m_name=m_grid.GetTextMatrix(selRow,GRID_NAME);
	am.m_order=atol(m_grid.GetTextMatrix(selRow,GRID_SEQ));
	am.m_cmt=m_grid.GetTextMatrix(selRow,GRID_CMT);
	if ( am.DoModal()==IDOK) OnOK();

}

void CCostClassA::OnMenuCostDel() //ɾ��������Ŀ
{
	long selRow=m_grid.GetRow();
	if( selRow== 0 ||  selRow==m_grid.GetRows()-1 )
	{
		AfxMessageBox("����ѡ��Ҫ�޸ĵ���");
		return;//�ж��Ƿ���Ҫ��ʾ��ݲ˵�
	}
	CString strName,strCmt,strPrompt;
	UINT nID;

	nID=atol(m_grid.GetTextMatrix(selRow,GRID_ID));
	strName=m_grid.GetTextMatrix(selRow,GRID_NAME);
	strCmt=m_grid.GetTextMatrix(selRow,GRID_CMT);
	strPrompt.Format("ȷ��Ҫɾ����\n\r%s,%s ?? ",strName,strCmt );
	if( AfxMessageBox(strPrompt,MB_OKCANCEL )== IDOK ){
		strName.Format(" UPDATE lsq_cost_class_a SET effect=0 WHERE��id=%ld ",nID );
		if( !CComFunc::WriteSql(strName) )
		{	
			AfxMessageBox("ɾ������ʧ��,������!");
			return;
		}
		AfxMessageBox("ɾ���ɹ�!");
		OnOK();		
	}

}

void CCostClassA::OnMenuCostRestore() //�ָ�
{
	long selRow=m_grid.GetRow();
	if( selRow== 0 ||  selRow==m_grid.GetRows()-1 )
	{
		AfxMessageBox("����ѡ��Ҫ�޸ĵ���");
		return;//�ж��Ƿ���Ҫ��ʾ��ݲ˵�
	}
	CString strName,strCmt,strPrompt;
	UINT nID,effect;

	nID=atol(m_grid.GetTextMatrix(selRow,GRID_ID));
	strName=m_grid.GetTextMatrix(selRow,GRID_NAME);
	effect=atol(m_grid.GetTextMatrix(selRow,GRID_EFFECT));
	strCmt=m_grid.GetTextMatrix(selRow,GRID_CMT);
	if (effect > 0 )	return; //����״̬
	strPrompt.Format("ȷ��Ҫ�ָ���\n\r%s,%s ?? ",strName,strCmt );
	if( AfxMessageBox(strPrompt,MB_OKCANCEL )== IDOK ){
		strName.Format(" UPDATE lsq_cost_class_a SET effect=1 WHERE��id=%ld ",nID );
		if( !CComFunc::WriteSql(strName) )
		{	
			AfxMessageBox("�ָ�����ʧ��,������!");
			return;
		}
		AfxMessageBox("�ָ��ɹ�!");
		OnOK();		
	}	// TODO: Add your command handler code here
	
}
