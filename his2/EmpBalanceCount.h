// EmpBalanceCount.h: interface for the CEmpBalanceCount class.
//
// ������:
//		���䱣�ջ�������
//
//		����ϵͳ�д洢���� prc_balance( iyear in number,retfet out number),
//	�˴洢���̲���һ��д�� lsq_temp_a��,Ȼ�����lsq_temp_a�еı���������ʾ����
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
