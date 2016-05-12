// YearDataCount.h: interface for the CYearDataCount class.
//--------------------------------------------------------------------
// 描述
//		年度就诊信息统计表,分解到每个月,每个类别
// 日期 2004/12/12				作者 凌绍清
//--------------------------------------------------------------------
// 修改记录
// 日期 2005/03/07				作者 凌绍清
//		将日期型控件改变为下拉框选择日期,因为日期只用到年份
//	并将标题名字更换为从数据库中选择
//--------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YEARDATACOUNT_H__AEFFD360_43B9_4C2D_B132_D94093F10F77__INCLUDED_)
#define AFX_YEARDATACOUNT_H__AEFFD360_43B9_4C2D_B132_D94093F10F77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DoctorWorkLoad.h"

class CYearDataCount : public CDoctorWorkLoad  
{
public:
	void OnSelchangeCombo2();
	CComboBox *pbox2;
	CString strConstName;
	void OnDblClickMshflexgrid1();
	static UINT QueryYearData(LPVOID ps);
	void OnOK();
	void SetGridHead();
	BOOL OnInitDialog();
	CYearDataCount();
	virtual ~CYearDataCount();

};

#endif // !defined(AFX_YEARDATACOUNT_H__AEFFD360_43B9_4C2D_B132_D94093F10F77__INCLUDED_)
