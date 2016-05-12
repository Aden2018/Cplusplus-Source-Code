// PayMed.cpp: implementation of the CPayMed class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "PayMed.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPayMed::CPayMed()
{

}

CPayMed::~CPayMed()
{

}
const char NOWORK[]="离休人员";
const char GAOQIAN[]="建国前老工人";
const char GANGSHANG[]="工伤人员";
const char R1[]="供养亲属";
const char RR[]="补充保险";
const char TUIYANG[]="退养人员";

BOOL CPayMed::OnInitDialog()
{
	CDialog::OnInitDialog();
//	CString HeadTitle[]={"序号","姓名","BM","挂号类型","日期","序列号"};
// 							0     1	     2       3        4       5
	GetDlgItem(IDOK)->EnableWindow(true);
	GetDlgItem(IDBUTTON_CHARGE_PRICE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDBUTTON_PRINT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_DOCTOR)->ShowWindow(SW_HIDE);
	c_doctor.SetReadOnly(true);

	c_sick.SetWindowText(str2[1]);
	c_type.SetWindowText(str2[3]);
	c_danjuhao.SetWindowText(str2[5]);
	

	GetDlgItem(IDC_EDIT_GH_HUAJIA)->SetWindowText("挂号: "+strGhHuajia[0]+" 划价收费: "+strGhHuajia[1] );

	CString strSql,s1,s2;
	x4.SetWindowText("0.00%");
	scale=1; //费用自付,默认
	balance=0;
	try{
		if(str2[3] == "补充保险"){
			

			strSql.Format("select 结存金额 from 职工基本情况表 where 卡号 = '%s' ",str2[2]);
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){
				s1=(char*)_bstr_t(recSet->GetCollect("结存金额").vt == VT_NULL? "0":recSet->GetCollect("结存金额"));
				balance=atof(s1);
				s2.Format(" %s : %s ","帐户余额为",s1);
				x1.SetWindowText(s1);
			}
			recSet->Close();
			x1.ShowWindow(SW_HIDE);
		}
		else if(str2[3] == "供养亲属"){
			strSql.Format("select NVL(xm,' ') as xm,NVL(xb,' ') as xb,NVL(xingzhi,' ') as xz,\
				NVL(姓名,' ') as name ,NVL(yuer,'0') as yuer from codeQingShu a,职工基本情况表 b  where 卡号=KAHAO and BM = '%s' ",str2[2]);
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){

				GetDlgItem(IDC_STATIC_PRICE)->ShowWindow(SW_SHOW);

				s1=(char*)_bstr_t(recSet->GetCollect("name"));
				s2.Format("供养人:%s",s1);

				s1=(char*)_bstr_t(recSet->GetCollect("yuer"));
				x1.SetWindowText(s1);
				balance=atof(s1);

				s1=(char*)_bstr_t(recSet->GetCollect("xz"));
				s2+="     "+s1;
				GetDlgItem(IDC_STATIC_PRICE)->SetWindowText(s2);
			
			}

			recSet->Close();

		}
		else if(  str2[3] == "住院人员" ){
			strSql.Format("select p1,p2,p1+p2,price+p1+p2,price from lsq_reside_hos_huajia t,lsq_reside_hos a where a.serial=t.s1 and t.s2='%s' ",str2[5]);
			recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
			if(!recSet->adoEOF){
				long i=0;
				s1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?"0":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				x2.SetWindowText(s1);
				i++;
				s1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?"0":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				x3.SetWindowText(s1);
				i++;
				s1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?"0":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				x7.SetWindowText(s1); //总费用
				x5.SetWindowText(s1);//实收
				i++;
				s1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?"0":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				x1.SetWindowText(s1); //帐户未收费前
				i++;
				s1=(char*)_bstr_t(recSet->GetFields()->GetItem(_variant_t(i))->Value.vt==VT_NULL?"0":recSet->GetFields()->GetItem(_variant_t(i))->Value);
				x6.SetWindowText(s1); //帐户收费后
			
				c_doctor.SetWindowText(strGhHuajia[1]);

			}
			recSet->Close();
			goto END;


		}
		else {
			GetDlgItem(IDC_STATIC_X1)->ShowWindow(SW_HIDE);//SetWindowText("用户付款");
		}

		
		strSql.Format("SELECT DOCTORNAME,MEDMONEY,TREATEMONEY from ItemRegisterTou where danjuhao='%s' ",str2[5]);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
			s1=(char*)_bstr_t(recSet->GetCollect("DOCTORNAME"));
			c_doctor.SetWindowText(s1);
		
			s1=(char*)_bstr_t(recSet->GetCollect("MedMoney"));
		
			x2.SetWindowText(s1);
		
			s2=(char*)_bstr_t(recSet->GetCollect("TreateMoney"));
			x3.SetWindowText(s2);
			
			s1.Format("%.2f",atof(s1)+atof(s2));
			x7.SetWindowText(s1);
			if( str2[3] == TUIYANG ) s2.Format("%.2f",atof(s1)*0.1); //退养人员90%折扣
			else if( str2[3] == NOWORK ) s2.Format("%.2f",0);
			else if( str2[3] == GAOQIAN ) s2.Format("%.2f",0);
			else if( str2[3] == GANGSHANG ) s2.Format("%.2f",0);
			else s2=s1 ;
			x5.SetWindowText(s2);
		}
		recSet->Close();
/*			{"ID","药品编码","药品名称","规格","单位","生产期","有效期",\
		"产地BM","产地","库存量","售价","进价","指导价","取药数"}; //共14列
*/
END:		SetGridHead();
		m_grid.SetColWidth(1,600);
		m_grid.SetTextMatrix(0,1,"序号");
		m_grid.SetColAlignment(1,short(4));//居中对齐
	//	m_grid.SetColWidth(10,0);
		long row=1;
//		strSql.Format("SELECT ID,BM,MC,GG,DW,RQ2,NVL(FACTORY,' ') as factory,a.dj as DJ,SL FROM ITEMTI a,MEDCODE b WHERE  a.YPBM=b.BM AND a.DANJUHAO='%s' ",str2[5]);
		strSql.Format("SELECT a.ID ID,BM,MC,GG,DW,a.RQ2 RQ2,NVL(FACTORY,' ') as factory,a.dj as DJ,a.SL SL,c.sl SL2 FROM ITEMTI a,\
			MEDCODE b,medlie c WHERE  a.YPBM=b.BM AND c.id=a.id AND a.DANJUHAO='%s' ",str2[5]);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF)
		{
			m_grid.SetTextMatrix(row,0,(char*)_bstr_t(recSet->GetCollect("ID")));
	//		m_grid.SetTextMatrix(row,1,(char*)_bstr_t(recSet->GetCollect("BM")));
			strSql.Format("%ld",row);
			m_grid.SetTextMatrix(row,1,strSql);
			m_grid.SetTextMatrix(row,2,(char*)_bstr_t(recSet->GetCollect("MC")));
			m_grid.SetTextMatrix(row,3,(char*)_bstr_t(recSet->GetCollect("GG")));
			m_grid.SetTextMatrix(row,4,(char*)_bstr_t(recSet->GetCollect("DW")));
			m_grid.SetTextMatrix(row,6,(char*)_bstr_t(recSet->GetCollect("RQ2")));
			m_grid.SetTextMatrix(row,8,(char*)_bstr_t(recSet->GetCollect("FACTORY")));
			m_grid.SetTextMatrix(row,9,(char*)_bstr_t(recSet->GetCollect("SL2")));
			m_grid.SetTextMatrix(row,10,(char*)_bstr_t(recSet->GetCollect("DJ")));
			m_grid.SetTextMatrix(row,13,(char*)_bstr_t(recSet->GetCollect("SL")));
			row++;
			m_grid.AddItem(" ",_variant_t(row));
			recSet->MoveNext();
		}
		recSet->Close();
		row=1;
		strSql.Format("SELECT ZLMC,费用名称,DJ FROM ItemRegisterTiZL a,费用项目表 b WHERE  a.ZLMC=b.费用编码 AND a.danjuhao='%s' ",str2[5]);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF)
		{
			m_grid2.SetTextMatrix(row,0,(char*)_bstr_t(recSet->GetCollect("ZLMC")));
			m_grid2.SetTextMatrix(row,1,(char*)_bstr_t(recSet->GetCollect("费用名称")));
			m_grid2.SetTextMatrix(row,2,(char*)_bstr_t(recSet->GetCollect("DJ")));
			row++;
			m_grid2.AddItem(" ",_variant_t(row));
			recSet->MoveNext();
		}
		recSet->Close();
			


	}
	catch(_com_error e)
	{
		recSet->Close();
		AfxMessageBox(strSql);
		return false;
	}


	m_grid.SetColWidth(14,0,0);//由于继承于HUAJIA 所以将最后一列费用额隐藏

	return true;
}

void CPayMed::OnOK()
{
	if(!theApp.AssertRole(ROLE_STARTDOCTOR_CY))return ;	
	long i=0,id;
	float meds(0);
	CString strSql;
	try{
		HospitalConnect->BeginTrans();

		for(i=1;i<m_grid.GetRows()-1;i++)
		{
			id=atol(m_grid.GetTextMatrix(i,0));
			meds=atof(m_grid.GetTextMatrix(i,13));//13列为药品数量
			strSql.Format("UPDATE MEDLIE SET SL=SL-(%.2f) WHERE ID=%ld ",meds,id);
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		}
	
		if( str2[3] =="住院人员" ){
			strSql.Format("UPDATE lsq_reside_hos_huajia SET H2='%s',N2='%s' WHERE s2='%s' ",\
				LoginInformation.user_code,LoginInformation.user,str2[5]);
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			strSql.Format("INSERT INTO lsq_reside_hos_huajia_complete SELECT * FROM lsq_reside_hos_huajia \
				WHERE s2='%s' ",str2[5]);
			HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
			strSql.Format("DELETE FROM lsq_reside_hos_huajia WHERE s2='%s' ",str2[5]);

		}
		else
			strSql.Format("UPDATE ITEMREGISTERTOU Set 发药员='%s',发药员名='%s' WHERE danjuhao='%s' ",\
				LoginInformation.user_code,LoginInformation.user,str2[5]);
		
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();



	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox("取药失败...,请联系程序设计人员");
		return;
	}

	MessageBox("成功取药,当前药品数量将从电脑中扣除...","提示",MB_OK|MB_ICONINFORMATION);
	CDialog::OnOK();


}

BOOL CPayMed::PreTranslateMessage(MSG *pMsg)
{
	return CDialog::PreTranslateMessage(pMsg);

}

void CPayMed::OnButtonDoctor()
{

}

void CPayMed::OnRollmed()
{

}
