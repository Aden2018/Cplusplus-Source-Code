// DoctorWorkLoad.h: interface for the CDoctorWorkLoad class.
//
//	类描述:
//
//	医生工作量统计
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCTORWORKLOAD_H__4C5F65A4_7FCA_4FDB_AED3_BF3811D45BF9__INCLUDED_)
#define AFX_DOCTORWORKLOAD_H__4C5F65A4_7FCA_4FDB_AED3_BF3811D45BF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GenericStockMed.h"

class CDoctorWorkLoad : public CGenericStockMed  
{
public:
	CString strTitle;
	static UINT QueryDoctor(LPVOID ps);
	void SetGridHead();
	void OnOK();
	void OnDblClickMshflexgrid1();
	BOOL OnInitDialog();
	CDoctorWorkLoad();
	virtual ~CDoctorWorkLoad();

};

#endif // !defined(AFX_DOCTORWORKLOAD_H__4C5F65A4_7FCA_4FDB_AED3_BF3811D45BF9__INCLUDED_)
