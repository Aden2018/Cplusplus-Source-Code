// TreateQuery.cpp: implementation of the CTreateQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "TreateQuery.h"
#include "progressIndicate.h"
#include "treateList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTreateQuery::CTreateQuery()
{

}

CTreateQuery::~CTreateQuery()
{

}

void CTreateQuery::OnOK()
{
	CProgressIndicate pq;
	pq.pDialog= this;
	pq.pThreadFunction = TreateQuery;

	pq.DoModal();

}

UINT CTreateQuery::TreateQuery(LPVOID ps)
{

	CTreateList *pf=(CTreateList*)theApp.pParentGrid.pWnd;
	CTreateQuery * pd =(CTreateQuery *) ((CProgressIndicate *) ps )->pDialog ;

	pd->UpdateData();

	pf->m_grid.SetRedraw(false);
	pf->SetGridHead();
	CString strSql,str1,strGhtype,strname;
	
	const int COMPUTE_COLS= 11 ;
	long row,col,i,cols;
	double price(0),add[]={0,0,0,0,0,0,0,0,0,0,0,0,0};
	//���湲Ҫͳ������
	if( pd->c_type.GetCurSel()==CB_ERR || pd->c_type.GetCurSel() == 0 )strGhtype = "";
	else {
		pd->c_type.GetLBText(pd->c_type.GetCurSel(),strGhtype);
		if( strGhtype == "��ǰְ��" ) strGhtype="����ǰ�Ϲ���";

	}
	pd->c_name.GetWindowText(strname);
	strname.Remove(' ');

	try{
		//��14�в�ѯ
		strSql.Format("SELECT b.danjuhao,to_char(min(riqi),'yyyy-mm-dd') xx ,min(sickname),min(doctorname),\
			min(�Һ�Ա��) ,min(����Ա��) ,min(�շ�Ա��) ,min( ghtype ) ,\
			sum(decode(���ô���,'���Ʒ�',b.dj,NULL )) c1,\
			sum(decode(���ô���,'������',b.dj,NULL )) c2,\
			sum(decode(���ô���,'�����',b.dj,NULL )) c3,\
			sum(decode(���ô���,'B ����',b.dj,NULL )) c4,\
			sum(decode(���ô���,'�ĵ��',b.dj,NULL )) c5,\
			sum(decode(���ô���,'���Ʒ�',b.dj,NULL )) c6,\
			sum(decode(���ô���,'���÷�',b.dj,NULL )) c7,\
			sum(decode(���ô���,'��ǻ��',b.dj,NULL )) c8,\
			sum(decode(���ô���,'�����',b.dj,NULL )) c9,\
			sum(decode(���ô���,'��  ��',b.dj,NULL )) c10,\
			max(nvl(treatemoney,NULL)) \
		FROM itemregistertizl b,������Ŀ�� c,itemregistertou x  where \
			b.zlmc=c.���ñ��� and b.danjuhao=x.danjuhao \
			and x.riqi between to_date(%s,'yyyymmdd') AND to_date(%s,'yyyymmdd') \
			AND x.treatemoney != 0 ",pd->m_date1.Format("%Y%m%d"),pd->m_date2.Format("%Y%m%d"));

		if(! pd->strdoctorbm.IsEmpty())strSql+=" AND doctor='"+pd->strdoctorbm+"'";
		if(! strGhtype.IsEmpty())strSql+=" AND GHTYPE='"+strGhtype+"'";
		if(!strname.IsEmpty())strSql+=" AND SICKNAME like '"+strname+"%'";
		if( pd->strSFY != "" ) strSql+=" AND �շ�Ա='"+pd->strSFY+"'";
	
		if( pd->c_status.GetCurSel() == 0 /*��ȡҩ��Ա*/)
			strSql+=" AND ��ҩԱ>0 ";
		else if( pd->c_status.GetCurSel() == 1 /*δȡҩ��Ա*/)
			strSql+=" AND �շ�Ա>0 AND ��ҩԱ is NULL ";

		
		strSql+=" GROUP BY b.danjuhao ORDER BY xx ";
	
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		
		row=1;
//		double dd;
//		unsigned int tx,bk;
		cols=recSet->GetFields()->Count;

		while(!recSet->adoEOF){
			col=0;
			price=0;
			for(i=0;i<cols;i++)
			{
				str1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?" ":recSet->GetFields()->GetItem(_variant_t(i))->Value);

				if( i >= cols-COMPUTE_COLS ){
					add[i - (cols-COMPUTE_COLS) ]+=atof(str1);
					strSql=str1;
					if( atof(strSql) != 0. )
						str1.Format("%.2f",atof(strSql));

				}

				pf->m_grid.SetTextMatrix(row,col++,str1);
			}
			row++;
			pf->m_grid.AddItem(" ",_variant_t(row));
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

	pf->m_grid.SetMergeRow(row,1);
	pf->m_grid.SetRow(row);
	pf->m_grid.SetCol(1);
	pf->m_grid.SetCellBackColor(RGB(255,0,0));
	strSql.Format("   ���� %ld �������¼ ",row-1);


	pf->m_grid.SetTextMatrix(row,1,"�ϼ�");	
	pf->GetDlgItem(IDC_BUTTON_TO_EXCEL)->SetWindowText(strSql+"         [ ���� Excel ]");

	for(long count=2;count< cols;count++){
		pf->m_grid.SetCol(count);
		pf->m_grid.SetCellBackColor(RGB(255,128,0));
		if( count >= cols-COMPUTE_COLS ){
			str1.Format("%.2f",add[count-(cols-COMPUTE_COLS)]);
			pf->m_grid.SetTextMatrix(row,count,str1);	

		}
		else {
			pf->m_grid.SetTextMatrix(row,count,strSql);	
		}
	}

	pf->m_grid.SetRedraw(true);
	
	((CProgressIndicate *)ps)->ConnectFlag =1;
	((CProgressIndicate *)ps)->SendMessage(WM_CLOSE,NULL,NULL);

	pd->SendMessage(WM_CLOSE,NULL,NULL);
}

BOOL CTreateQuery::OnInitDialog()
{
	CDialogGhQuery::OnInitDialog();
	GetDlgItem(IDC_STATIC_TITLE2)->SetWindowText("������ϸ���ѯ");
	return true;
}
