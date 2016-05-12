// Hos30Hospital.h: interface for the CHos30Hospital class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOS30HOSPITAL_H__A0695645_191C_4A15_AF7F_59621F6081B4__INCLUDED_)
#define AFX_HOS30HOSPITAL_H__A0695645_191C_4A15_AF7F_59621F6081B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OtherDecharge.h"
//医院30%自留资金
class CHos30Hospital : public COtherDecharge  
{
public:
	CHos30Hospital();
	virtual ~CHos30Hospital();

};

#endif // !defined(AFX_HOS30HOSPITAL_H__A0695645_191C_4A15_AF7F_59621F6081B4__INCLUDED_)
