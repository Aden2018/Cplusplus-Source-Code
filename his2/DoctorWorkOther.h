// DoctorWorkOther.h: interface for the CDoctorWorkOther class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCTORWORKOTHER_H__56FC484F_0687_4C6C_8702_6B229683361E__INCLUDED_)
#define AFX_DOCTORWORKOTHER_H__56FC484F_0687_4C6C_8702_6B229683361E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DoctorWorkLoad.h"

class CDoctorWorkOther : public CDoctorWorkLoad  
{
public:
	static UINT QueryDoctorOther(LPVOID ps);
	CComboBox * pCombo1;
	void SetGridHead();
	void OnOK();
	BOOL OnInitDialog();
	CDoctorWorkOther();
	virtual ~CDoctorWorkOther();

};

#endif // !defined(AFX_DOCTORWORKOTHER_H__56FC484F_0687_4C6C_8702_6B229683361E__INCLUDED_)
