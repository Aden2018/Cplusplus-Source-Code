// OtherDechargeQuery.h: interface for the COtherDechargeQuery class.
//------------------------------------------------------------------
//������:
// ���� ҽԺ�ɱ��ȷ��ñ�����ѯ
// ����:2004/12/12
//------------------------------------------------------------------
// �޸ļ�¼:	
// 2005/3/5									������
//	  ����һ�Ի����ѯ,���Խ����������ϲ���һ���ѯ,��ҽԺ�ɱ�(��������
//	����),���н����ַ��������һ���ѯ
//------------------------------------------------------------------
// �޸ļ�¼:
// 2005/3/8 08:25							������
//	  ����һ��ť��ѯ,����ֱ�ӽ�ҽԺ�ɱ����(ҽԺ�ɱ�����:�д���,ά�޷�,��������)
//	�����������趨��ѯ�ĳɱ�����,�Ա����պ���ķ���
//------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTHERDECHARGEQUERY_H__72B0FC86_57BE_4892_9F95_02D9F22929AC__INCLUDED_)
#define AFX_OTHERDECHARGEQUERY_H__72B0FC86_57BE_4892_9F95_02D9F22929AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RelateCharge.h"

class COtherDechargeQuery : public CRelateCharge  
{

public:	
	void OnButtonCostQuery();
	CString strQuery2;
	CString strQuery;
	void SetGridHead();
	void OnOK();
	void OnButtonAdd();
	void OnButtonDeleteRow();
	BOOL OnInitDialog();
	COtherDechargeQuery();
	virtual ~COtherDechargeQuery();

protected:
	CString flagQueryStr;
	CStringArray typeArray;
	UINT flagQuery;

};

#endif // !defined(AFX_OTHERDECHARGEQUERY_H__72B0FC86_57BE_4892_9F95_02D9F22929AC__INCLUDED_)
