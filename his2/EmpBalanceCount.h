// EmpBalanceCount.h: interface for the CEmpBalanceCount class.
//
// 类描述:
//		补充保险基金结算表
//
//		调用系统中存储过程 prc_balance( iyear in number,retfet out number),
//	此存储过程产生一表写入 lsq_temp_a中,然后根据lsq_temp_a中的表内容来显示数据
//		
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMPBALANCECOUNT_H__5D45460C_AE3D_44EE_B58D_05422FF5EA27__INCLUDED_)
#define AFX_EMPBALANCECOUNT_H__5D45460C_AE3D_44EE_B58D_05422FF5EA27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DoctorWorkLoad.h"

class CEmpBalanceCount : public CDoctorWorkLoad  
{
public:
	void OnOK();
	BOOL OnInitDialog();
	CEmpBalanceCount();
	virtual ~CEmpBalanceCount();
	CComboBox *pc;
};

#endif // !defined(AFX_EMPBALANCECOUNT_H__5D45460C_AE3D_44EE_B58D_05422FF5EA27__INCLUDED_)
