// SickGetMedView.cpp: implementation of the CSickGetMedView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "SickGetMedView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSickGetMedView::CSickGetMedView()
{
	DANJUHAO=BLANKSTR;
	GHTYPE=BLANKSTR;
}

CSickGetMedView::~CSickGetMedView()
{

}
BEGIN_MESSAGE_MAP(CSickGetMedView, CDialog)
	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CSickGetMedView, CDialog)
END_EVENTSINK_MAP()
    //{{AFX_EVENTSINK_MAP(CDialogHjSf)
//	ON_EVENT(CDialogHjSf, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
//	ON_EVENT(CDialogHjSf, IDC_MSHFLEXGRID2, -601 /* DblClick */, OnDblClickMshflexgrid2, VTS_NONE)
//	ON_EVENT(CDialogHjSf, IDC_MSHFLEXGRID2, -600 /* Click */, OnClickMshflexgrid2, VTS_NONE)
//	ON_EVENT(CDialogHjSf, IDC_MSHFLEXGRID3, -601 /* DblClick */, OnDblClickMshflexgrid3, VTS_NONE)
//	ON_EVENT(CDialogHjSf, IDC_MSHFLEXGRID3, -600 /* Click */, OnClickMshflexgrid3, VTS_NONE)
	//}}AFX_EVENTSINK_MAP

BOOL CSickGetMedView::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_BUTTON_PRINT)->ShowWindow(SW_HIDE);//���ش�ӡ
	GetDlgItem(IDOK)->SetWindowText("ȡҩ����");

	SetGridHeader();
	InitData();
	unbundle(); //�� ���ѽ��ֱ�Ժ�



	return true;
}

void CSickGetMedView::OnOK() //ȡҩ
{

	UINT flag=1;
	try{
		_CommandPtr cmd;
		_ParameterPtr par;
		cmd.CreateInstance(__uuidof( Command ));
		par.CreateInstance(__uuidof( Parameter));
		
		_variant_t vNULL;
		vNULL.vt = VT_ERROR;
		vNULL.scode = DISP_E_PARAMNOTFOUND;
		
		cmd->put_CommandType(adCmdStoredProc) ;
		par=cmd->CreateParameter(_bstr_t("success"),adUnsignedInt,adParamOutput,20,vNULL);
		cmd->Parameters->Append( par );

		par=cmd->CreateParameter(_bstr_t("paraID"),adVarChar,adParamInput,20,_bstr_t( DANJUHAO ) );
		cmd->Parameters->Append( par );

		par=cmd->CreateParameter(_bstr_t("uid"),adVarChar,adParamInput,20,_bstr_t( LoginInformation.user_code ) );
		cmd->Parameters->Append( par );

		par=cmd->CreateParameter(_bstr_t("umc"),adVarChar,adParamInput,20,_bstr_t( LoginInformation.user) );
		cmd->Parameters->Append( par );
		
		cmd->put_CommandText(_bstr_t("PRC_pay_med"));
		cmd->ActiveConnection=HospitalConnect;
		cmd->Execute(NULL,NULL,adCmdStoredProc);
		
		flag=cmd->Parameters->GetItem("success")->Value.uintVal;
		if ( flag ) {
			AfxMessageBox("ȡҩ����ʧ��,������!!");
		}
		
		cmd.Detach();
		par.Detach();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
		return;
	}

	AfxMessageBox("�ɹ�ȡҩ!!");
	CDialog::OnOK();
}

void CSickGetMedView::InitData()
{
	CString strSql,strTmp,strCODE(BLANKSTR);
	CString strGh,strSf;
	long i(0),j(0),cols(0);
	long selCol[]={ COL_MC,COL_GG,COL_DW,COL_FACTORY,COL_KC,COL_PRICE,COL_SL,COL_MONEY};
	double dbSum(0);
	double db01,db02,db03;
	try{
//������Ϣ��ʾ
		strSql.Format("select (select ds1 from lsq_upgrade where ds2=upper('gh_type') and ds3=ghtype ) dss1 ,\
			sickname,doctorname,sex,age,medmoney,treateMoney,cash,p1,p2,p3,p4,p5,p6,ghtype,sickbm ,�Һ�Ա��,�շ�Ա�� from itemregistertou where danjuhao='%s'  ",DANJUHAO );

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			i=0;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
			m_type.SetWindowText(strSql);
			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
			m_name.SetWindowText(strSql);
			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
			m_ys.SetWindowText(strSql);
			m_ys.SetReadOnly();

			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
			m_sex.SetWindowText(strSql);
			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
			m_age.SetWindowText(strSql);
			
			i++; //ҩƷ���� 
			dbSum=0;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
			dbSum+=atof(strSql);
			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
			dbSum+=atof(strSql);
			strSql.Format("%.2f",dbSum); // �ܷ���
			m_cost.SetWindowText(strSql);

			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
			m_cash.SetWindowText(strSql);
	
			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
			m_jgc.SetWindowText(strSql);
			m_jgc.SetReadOnly();

			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
			m_gwy.SetWindowText(strSql);
			m_gwy.SetReadOnly();

			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
			m_ic.SetWindowText(strSql);
			m_ic.SetReadOnly();

			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
			m_dbjz.SetWindowText(strSql);
			m_dbjz.SetReadOnly();

			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
			m_tc.SetWindowText(strSql);
			m_tc.SetReadOnly();

			i++;
			strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
			m_account.SetWindowText(strSql);
			
			i++; //�Һ�����
			GHTYPE=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );

			i++; //��Ա����
			strCODE=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );

					i++; //��Ա����
			strGh=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );

						i++; //��Ա����
			strSf=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );

		}
		recSet->Close();
		GetWindowText(strSql);
		strSql.Format("%s-------[ �Һ� : %s  ���շ� : %s ] ",strSql,strGh,strSf);
		SetWindowText(strSql);

		switch ( CComFunc::GetGhType( GHTYPE ) )
		{
		case CComFunc::TYPE_GC:
		case CComFunc::TYPE_LX:
		case CComFunc::TYPE_TY:
		case CComFunc::TYPE_GS:
			m_cost.GetWindowText(strTmp);
			db01=atof(strTmp);
			m_cash.GetWindowText(strTmp);
			db02=atof(strTmp);
			strTmp.Format("%.2f",db01-db02);
			m_workunit.SetWindowText(strTmp); //��λ֧������
			CComFunc::GetSql(strSql,9); //������ԱSQL��� 
			strSql+=" AND bm='"+strCODE+"' AND LB='"+GHTYPE+"'";
			strTmp.Format("SELECT pro FROM (%s) ",strSql);
			strSql=CComFunc::GetString(strTmp);
			m_Ratio.SetWindowText(strSql+"%");
		}


//ҩƷ��ʾ
		strSql.Format("select b.mc,b.gg,b.dw,a.factory,\
			(select sum(sl) from medlie where ypbm=b.bm and kfbm=a.kfbm group by ypbm),\
			a.dj,a.sl,a.SL*a.DJ from itemti a,medcode b,medlie c where a.id=c.id and c.ypbm=b.bm AND a.DANJUHAO='%s' ",DANJUHAO );

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
		j=1; //��ʹ��
		dbSum=0;
		while(!recSet->adoEOF){
			for( i=0; i< cols ;i ++)
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
				m_grid1.SetTextMatrix(j,selCol[i] ,strSql);
				if( i== cols-1 )dbSum+=atof(strSql);

			}
			j++;
			m_grid1.AddItem(BLANKSTR,_variant_t(j) );
			recSet->MoveNext();
		}
		recSet->Close();
		if( j !=1 ){
			strSql.Format("�ܼ�:%ld", j-1 );
			m_grid1.SetTextMatrix(j,COL_MC,strSql);
			strSql.Format("%.2f",dbSum);

			m_grid1.SetTextMatrix(j,COL_MONEY,strSql);

			m_grid1.SetCol(0);
			m_grid1.SetRow(j);
			m_grid1.SetColSel(COL_MONEY);
			m_grid1.SetRowSel(j);
		}
//����������ʾ
		strSql.Format("select ��������,dj from itemregistertizl ,������Ŀ�� where zlmc=���ñ���  and danjuhao='%s' ",DANJUHAO);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
	
		j=1; //��ʹ��
		dbSum=0;

		while(!recSet->adoEOF){
			for( i=0; i< cols ;i ++)
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
				m_grid2.SetTextMatrix(j,i+1 ,strSql);
				if( i== cols-1 )dbSum+=atof(strSql);

			}
			j++;
			m_grid2.AddItem(BLANKSTR,_variant_t(j) );
			recSet->MoveNext();
		}
		recSet->Close();
		if( j!=1 ){
			strSql.Format("�ܼ�:%ld", j-1 );
			m_grid2.SetTextMatrix(j,EXES_MC_COL,strSql);
			strSql.Format("%.2f",dbSum);
			m_grid2.SetTextMatrix(j,EXES_MONEY,strSql);
			m_grid2.SetCol(0);
			m_grid2.SetRow(j);
			m_grid2.SetColSel(EXES_MONEY);
			m_grid2.SetRowSel(j);
		}
//�ʻ�ʹ����ʾ
		strSql.Format("select id,mc,n1,n2 FROM lsq_account_use where serial='%s' ",DANJUHAO);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		cols=recSet->GetFields()->Count;
	
		j=1; //��ʹ��
		dbSum=0;
		selCol[0]=ACCOUNT_ID;
		selCol[1]=ACCOUNT_MC;
		selCol[2]=ACCOUNT_YE;
		selCol[3]=ACCOUNT_ZFJE;

		while(!recSet->adoEOF){
			for( i=0; i< cols ;i ++)
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ? _variant_t(BLANKSTR) :recSet->GetFields()->GetItem(i)->Value );
				m_grid3.SetTextMatrix(j,selCol[i] ,strSql);
				if( i== cols-1 )dbSum+=atof(strSql);

			}
			j++;
			m_grid3.AddItem(BLANKSTR,_variant_t(j) );
			recSet->MoveNext();
		}
		recSet->Close();
		if( j!=1 ){
			strSql.Format("�ܼ�:%ld", j-1 );
			m_grid3.SetTextMatrix(j,ACCOUNT_ID, strSql);
			strSql.Format("%.2f",dbSum);
			m_grid3.SetTextMatrix(j,ACCOUNT_ZFJE,strSql);
			
			m_grid3.SetCol(0);
			m_grid3.SetRow(j);
			m_grid3.SetColSel(ACCOUNT_ZFJE);
			m_grid3.SetRowSel(j);
		}


		
	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return ;
	}		


}

BOOL CSickGetMedView::PreTranslateMessage(MSG *pMsg)
{
	return CDialog::PreTranslateMessage(pMsg);

}

HBRUSH CSickGetMedView::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if( pWnd->m_hWnd == m_cost.m_hWnd || pWnd->m_hWnd == m_cash.m_hWnd )
		pDC->SetTextColor(LSQ_RED);
	if( pWnd->m_hWnd == m_account.m_hWnd )
		pDC->SetTextColor(LSQ_BLUE);
	if( pWnd->m_hWnd == m_jgc.m_hWnd || pWnd->m_hWnd == m_gwy.m_hWnd || pWnd->m_hWnd == m_dbjz.m_hWnd 
		|| pWnd->m_hWnd == m_tc.m_hWnd || pWnd->m_hWnd == m_ic.m_hWnd )
		pDC->SetTextColor(LSQ_BLUE2);
	if( pWnd->m_hWnd == m_ys.m_hWnd || pWnd->m_hWnd == m_name.m_hWnd || pWnd->m_hWnd == m_age.m_hWnd 
		|| pWnd->m_hWnd == m_sex.m_hWnd || pWnd->m_hWnd == m_type.m_hWnd )
		pDC->SetTextColor(LSQ_BLUE);
	return hbr;
}

void CSickGetMedView::unbundle()
{
	CString str1,str2,str3,str4;
	CString strSql;
	m_cost.GetWindowText(str1);
	m_cash.GetWindowText(str2);
	double cost=atof(str1);
	double cash=atof(str2);
	strSql.Format("%.2f",cost-cash);
/*	if( GHTYPE.Compare("����ͳ��") == 0 ){ //���ܷ��ü�ȥ�ֽ�,ʣ���Ϊͳ��
		
		m_tc.SetWindowText(strSql);

	}
	else */
	if( GHTYPE.Compare("��������") ==0  ){ //���ܷ��ü�ȥ�ֽ�,ʣ���ΪIC��֧��
	
		m_ic.SetWindowText(strSql);
	
	}
	else if( GHTYPE.Compare("�ض�����") == 0 ){//���ܷ��ü�ȥ�ֽ�,ic,����ǰ֧��,����Ա����,�󲡾���,ʣ��Ϊͳ��
		
		m_ic.GetWindowText(str1);
		m_dbjz.GetWindowText(str2);
		m_gwy.GetWindowText(str3);
		m_jgc.GetWindowText(str4);
		strSql.Format("%.2f",cost-cash-atof(str1)-atof(str2)-atof(str3)-atof(str4) );

		m_tc.SetWindowText(strSql);

	}
	else if( GHTYPE.Compare("���䱣��") == 0 || GHTYPE.Compare("��������") == 0 ){
		
		m_account.SetWindowText(strSql);

	}
	


}
