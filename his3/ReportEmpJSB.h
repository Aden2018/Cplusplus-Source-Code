// ReportEmpJSB.h: interface for the CReportEmpJSB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTEMPJSB_H__645B7FCB_51DD_42D7_8F03_258A63277D2E__INCLUDED_)
#define AFX_REPORTEMPJSB_H__645B7FCB_51DD_42D7_8F03_258A63277D2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ReportEmpCount.h"
//********************************************************************
//*DATE:2012/06/18
//*DESC��
//*		����ҽ������������ԭ���ɳ���Ľ���������³����У��漰����
//*ͳ�������㷽ʽ����,���������oracle�洢����prc_balance��ԭ���ļ��㷽ʽ���£�
//*  �����ܶ�*4% - ������ȳ�ֵ - �����ֵ = ͳ�����
//* ���ڵļ��㷽ʽ��
//*	 �����ܶ�*4% - ������ȳ�ֵ = ͳ�����
//*���������ֵ��ͳ������а���
/////////////////////////////////////////////////////////////////////////
class CReportEmpJSB : public CReportEmpCount  
{
public:
	static UINT GenerateJSB(LPVOID ps);
	void OnOK();
	BOOL OnInitDialog();
	CReportEmpJSB();
	virtual ~CReportEmpJSB();
	enum{ GRID_ID=27 };
};

#endif // !defined(AFX_REPORTEMPJSB_H__645B7FCB_51DD_42D7_8F03_258A63277D2E__INCLUDED_)
