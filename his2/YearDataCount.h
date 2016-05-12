// YearDataCount.h: interface for the CYearDataCount class.
//--------------------------------------------------------------------
// ����
//		��Ⱦ�����Ϣͳ�Ʊ�,�ֽ⵽ÿ����,ÿ�����
// ���� 2004/12/12				���� ������
//--------------------------------------------------------------------
// �޸ļ�¼
// ���� 2005/03/07				���� ������
//		�������Ϳؼ��ı�Ϊ������ѡ������,��Ϊ����ֻ�õ����
//	�����������ָ���Ϊ�����ݿ���ѡ��
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
