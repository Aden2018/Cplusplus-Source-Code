// PeculiarInput.h: interface for the CPeculiarInput class.
//
//	������:
//		���ⲹ����Ա��ֵ
//
//		ʵ�ֽ����ⲹ����Ա���䲹����׼��Ӧ�������ʻ���
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PECULIARINPUT_H__BE382DCE_78E9_4386_80DB_1FBFC376B8DC__INCLUDED_)
#define AFX_PECULIARINPUT_H__BE382DCE_78E9_4386_80DB_1FBFC376B8DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WageInput.h"

class CPeculiarInput : public CWageInput  
{
public:
	static UINT QueryData2(LPVOID ps);
	void OnOK();
	static UINT QueryData(LPVOID ps);
	static void SetGridHead(CString ps[], long pl[], CMSHFlexGrid &pg, long len,long fixLen,long merge);
	void OnB1();
	void OnB3();
	BOOL OnInitDialog();
	CPeculiarInput();
	virtual ~CPeculiarInput();

};

#endif // !defined(AFX_PECULIARINPUT_H__BE382DCE_78E9_4386_80DB_1FBFC376B8DC__INCLUDED_)
