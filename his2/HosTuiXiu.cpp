// HosTuiXiu.cpp: implementation of the CHosTuiXiu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his2.h"
#include "HosTuiXiu.h"
#include "employeeNoWorkQuery.h"
#include "OtherSickQuery.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHosTuiXiu::CHosTuiXiu()
{


}

CHosTuiXiu::~CHosTuiXiu()
{

}

void CHosTuiXiu::OnButtonA()
{

	if( iType == 0 ){
			CEmployeeNoworkQuery rybm;
			rybm.p=NULL;
			if(rybm.DoModal()==IDOK){
				strBm=rybm.strKH;
				strName=rybm.strName;
				strSex=rybm.strSex;
			}
			else strBm="";
			c1.SetWindowText(strName+" / "+strSex);
	}
	else {	
		COtherSickQuery other;
		other.flagWhatDo=1; //为零时做为挂号时使用
	
		if(iType ==1)// == GAOQIAN )
		{
			other.strSql.Format("SELECT * FROM OtherSick Where LB='退养人员' ");
			other.strTitle="退养人员信息";
		}
		else if ( iType == 2) //GANGSHANG )
		{
			other.strSql.Format("SELECT * from OTHERSICK WHERE LB='建国前老工人' ");
			other.strTitle="建国前老工人信息";
		
		}
		else  //退养人
		{
			other.strSql.Format("SELECT * From OtherSick Where LB='工伤人员' ");
			other.strTitle="工伤人员信息";

		}
		
		if( other.DoModal() == IDOK)
		{
			strBm=other.strKH;
			strName=other.strName;
			strSex=other.strSex;
		

		}
		else strBm="";
	
		c1.SetWindowText(strName+" / "+strSex);
	}
	c2.SetFocus();
}

void CHosTuiXiu::OnOK()
{
	UpdateData();
	CString strTmp,strSel,strSql;
	c_type.GetWindowText(strSel);
	
	if( strSel.IsEmpty() ) {
		AfxMessageBox("请先选择一个项目或输入经济内容");
		return;
	}
	
	if( c_type.FindStringExact(-1,strSel) ==CB_ERR ){ //新增一个经济内容方式
	
		c_type.AddString(strSel);
		strSql.Format("INSERT INTO LSQ_ECONOMY_RANK(n1,ds3,d1) \
			values( (SELECT max(NVL(n1,0))+1 FROM LSQ_ECONOMY_RANK ),'%s',sysdate ) ",strSel );
		if( !WriteSQL(strSql) ) {
			AfxMessageBox("写入数据库失败");
			AfxMessageBox(strSql);
		}

	}
/* 日期, 系统日期,序列号,经济内容,描述,使用人,验收人,经手人,审批人,单据张数,附件张数,总金额,比例,操作人
	select substr(sys_context( 'userenv' , 'ip_address'),
	instr(sys_context( 'userenv' , 'ip_address'),'.',-1,2)+1)  from dual	--生成客户端IP的最后两位
	c1 使用人
	c2 验收人
	c3 经手人
	c4 审批人
	c5 凭证号
	c6 单据数
	c7 附件数
	c8 总金额
	c9 比例
	c10 报销额
	c11 备注
	
	*/
	CString strc[11];
	long i=0;
	c1.GetWindowText(strc[i++] );
	c2.GetWindowText(strc[i++] );
	c3.GetWindowText(strc[i++] );
	c4.GetWindowText(strc[i++] );
	c5.GetWindowText(strc[i++] );
	c6.GetWindowText(strc[i++] );
	c7.GetWindowText(strc[i++] );
	c8.GetWindowText(strc[i++] );
	c9.GetWindowText(strc[i++] );
	c10.GetWindowText(strc[i++] );
	c11.GetWindowText(strc[i++] );

	strSql.Format(" INSERT INTO LSQ_OTHER_DECHARGE ( d1,d2,ds1,ds2,ds3,ds4,ds5,ds6,ds7,n5,n1,n2,n3,n4,ds8,ds9,ds10) \
		values(to_date(%s,'yyyymmdd'),sysdate,to_char(sysdate,'yyyymmddhh24miss')||'_'||(select substr(sys_context( 'userenv' , 'ip_address'),\
		instr(sys_context( 'userenv' , 'ip_address'),'.',-1,2)+1)  from dual),'%s','%s',\
		'%s','%s','%s','%s',%ld,%ld,%ld,%.2f,%.4f,'%s','%s','%s' ) ",m_date1.Format("%Y%m%d"),strSel,strc[10],strName,strc[1],\
		strc[2],strc[3],atol(strc[4]),atol(strc[5]),atol(strc[6]),atof(strc[7]),atof(strc[8])/100,LoginInformation.user,strTag,strBm);
	//		               凭证编码		单据张数	 附件张数			总额	比例
	if(WriteSQL(strSql)){
		ClearDialogInformation();
		AfxMessageBox("填写成功");
	}
	else AfxMessageBox(strSql);
}

BOOL CHosTuiXiu::OnInitDialog()
{
	switch( iType ){
	case 0:strTag.Format("AAN"); break;
	case 1:strTag.Format("AAQ"); break;
	case 2:strTag.Format("AAO"); break;
	case 3:strTag.Format("AAP"); break;
	}
	CString strSql;
	strSql.Format("SELECT ds2 FROM LSQ_GH_TYPE WHERE ds1='%s' ",strTag );
	strTitle=GetStringTitle(strSql);
	
	if(COtherDecharge::OnInitDialog()) return true;
	else return false;

}
