// WageInput.h: interface for the CWageInput class.
// ������:
//		ְ����ȹ��ʵ���
//		��Ҫ����ְ����ȹ��ʵ���ϵͳ��
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAGEINPUT_H__5AC690D8_0ED5_4794_AA0D_50BD94562601__INCLUDED_)
#define AFX_WAGEINPUT_H__5AC690D8_0ED5_4794_AA0D_50BD94562601__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseAddCash.h"

class CWageInput : public CBaseAddCash  
{
public:
	static UINT QueryDataReal(LPVOID ps);
	void OnOK();
	void OnB3();
	void OnExcel();
	static UINT QueryData(LPVOID ps);
	void SetGridHead();
	void OnB1();
	void OnB2();
	BOOL OnInitDialog();
	CWageInput();
	virtual ~CWageInput();

};

#endif // !defined(AFX_WAGEINPUT_H__5AC690D8_0ED5_4794_AA0D_50BD94562601__INCLUDED_)
