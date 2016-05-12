// OtherDechargeQuery.h: interface for the COtherDechargeQuery class.
//------------------------------------------------------------------
//类描述:
// 其它 医院成本等费用报销查询
// 日期:2004/12/12
//------------------------------------------------------------------
// 修改记录:	
// 2005/3/5									凌绍清
//	  新增一对话框查询,可以将各种条件合并在一起查询,如医院成本(包括三项
//	内容),还有将各种费用组合在一起查询
//------------------------------------------------------------------
// 修改记录:
// 2005/3/8 08:25							凌绍清
//	  新增一按钮查询,可以直接将医院成本查出(医院成本包括:招待费,维修费,其它费用)
//	拟在数据中设定查询的成本内容,以便于日后更改方便
//------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTHERDECHARGEQUERY_H__72B0FC86_57BE_4892_9F95_02D9F22929AC__INCLUDED_)
#define AFX_OTHERDECHARGEQUERY_H__72B0FC86_57BE_4892_9F95_02D9F22929AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RelateCharge.h"

class COtherDechargeQuery : public CRelateCharge  
{

public:	
	void OnButtonCostQuery();
	CString strQuery2;
	CString strQuery;
	void SetGridHead();
	void OnOK();
	void OnButtonAdd();
	void OnButtonDeleteRow();
	BOOL OnInitDialog();
	COtherDechargeQuery();
	virtual ~COtherDechargeQuery();

protected:
	CString flagQueryStr;
	CStringArray typeArray;
	UINT flagQuery;

};

#endif // !defined(AFX_OTHERDECHARGEQUERY_H__72B0FC86_57BE_4892_9F95_02D9F22929AC__INCLUDED_)
