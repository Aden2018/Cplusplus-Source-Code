// EmpGetAccount.h: interface for the CEmpGetAccount class.
//
// 类描述:
//		补充保险基金征集表
//
//		
//	
//
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMPGETACCOUNT_H__621F87FB_BC41_4321_926B_D8A759D8DD50__INCLUDED_)
#define AFX_EMPGETACCOUNT_H__621F87FB_BC41_4321_926B_D8A759D8DD50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DoctorWorkLoad.h"

class CEmpGetAccount : public CDoctorWorkLoad  
{
public:
	static UINT QueryData(LPVOID ps);
	void OnOK();
	CComboBox *pc;
	BOOL OnInitDialog();
	CEmpGetAccount();
	virtual ~CEmpGetAccount();

};

#endif // !defined(AFX_EMPGETACCOUNT_H__621F87FB_BC41_4321_926B_D8A759D8DD50__INCLUDED_)
