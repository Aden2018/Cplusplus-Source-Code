// ComFunc.cpp: implementation of the CComFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "his3.h"
#include "ComFunc.h"
#include "progressEx.h"
#include "dialogWait.h"
#include "gridctrl\gridctrl.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComFunc::CComFunc()
{

}

CComFunc::~CComFunc()
{

}

CString CComFunc::GetString(CString strSql)
{
	CString strout(BLANKSTR);
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
		
			strout=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(0L)->Value );
		}
		recSet->Close();

		return strout;

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return strout;
	}	

}

BOOL CComFunc::WriteSql(CString strSql)
{
	try{

		HospitalConnect->BeginTrans();
		HospitalConnect->Execute(_bstr_t(strSql),NULL,adCmdText);
		HospitalConnect->CommitTrans();

	}
	catch(_com_error e)
	{
		HospitalConnect->RollbackTrans();
		AfxMessageBox(e.Description());
		return false;
	}
	return true;

}

void CComFunc::writeDebug(CString strout)
{
	CFile fDebug;

	if( ! fDebug.Open("F:\\log.txt",CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite  ) )
		AfxMessageBox("���������ļ�ʧ��...");
	else fDebug.SeekToEnd();

	COleDateTime curDate=COleDateTime::GetCurrentTime();
	CString strFmt;
	CString strRet("\r\n");
	CString strSpan('-',40);
	strFmt.Format("%s\r\n",curDate.Format("%Y-%m-%d %H:%M:%S") );
	fDebug.Write(strFmt,strFmt.GetLength());
	strSpan+=strRet;
	fDebug.Write(strSpan,strSpan.GetLength());

	fDebug.Write(strout,strout.GetLength());
	fDebug.Write(strRet+strRet,strRet.GetLength()*2 );


	fDebug.Close();

}
#define IDC_PROGRESS_EXCEL WM_USER+1001
void CComFunc::ToExcel(CMSHFlexGrid *pg)
{
/*
	CProgressEx *pp=new CProgressEx();

	CRect r1(0,0,400,25);
	pp->Create(WS_CHILD |PBS_SMOOTH|WS_BORDER ,r1,AfxGetMainWnd()->GetForegroundWindow(),IDC_PROGRESS_EXCEL);
	pp->UpdateWindow();
	pp->ShowWindow(SW_SHOW);
	pp->CenterWindow();
	pp->Invalidate();
	pp->SetRange32(0,pg->GetRows() );
	pp->strView="����׼������...���Ե�!!";
	
	theApp.pParentGrid.pGrid=pg;
	AfxBeginThread(THREAD_TO_EXCEL,pp);
*/
	_Application app2;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;
	 COleVariant vOpt2(DISP_E_PARAMNOTFOUND,VT_ERROR);

	CProgressEx pp;
	CRect r1(0,0,400,25);
	pp.Create(WS_CHILD |PBS_SMOOTH|WS_BORDER ,r1,AfxGetMainWnd()->GetForegroundWindow(),IDC_PROGRESS_EXCEL);
	pp.UpdateWindow();
	pp.ShowWindow(SW_SHOW);
	pp.CenterWindow();
	pp.Invalidate();
	pp.SetRange32(0,pg->GetRows() );
	pp.strView="����׼������...���Ե�!!";

//	if( ! app2 ){
	app2.CreateDispatch("excel.application");
	if(!app2){
		AfxMessageBox("��ע��ϵͳ�б���װ��EXCEL97 ���� EXCEL2000 ,����˹��ܲ���ʹ��...");
		return;
	}
	books2=app2.GetWorkbooks();
	//		book2=books2.Open(strFileName,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
	book2=books2.Add(vOpt2);
	sheets2=book2.GetWorksheets();
	sheet2=sheets2.GetItem(COleVariant((short)1));
//	}

//


	Range vRange;
	Font font;
	long x,y;
	CString str1,str2;
	
	app2.SetVisible(false);
	pp.strView="";


	for (x=0; x<pg->GetRows(); x++)
	{
		for( y=0 ; y< pg->GetCols(0) ; y++ )
		{
			if( y<26)str1.Format("%c%ld",'A'+y , x+1 );
			else str1.Format("%c%c%ld",'A'+ ( y/26 -1) ,'A'+y % 26,x+1 );
			vRange=sheet2.GetRange(_variant_t(str1),_variant_t(str1)); // ҽ�ƻ���
		//	font=vRange.GetFont();
		//	font.SetName(_O(FONTNAME));
		//	font.SetSize(_O((short)STANDARDFONT));
			vRange.SetValue(COleVariant(pg->GetTextMatrix(x,y)));
		}
		
		pp.strView.Format("%2.0f%%",double(x)/pg->GetRows()*100);
		pp.SetPos(x);
	}
	app2.SetVisible(true);
		
	pp.DestroyWindow();
	sheet2.ReleaseDispatch();

	sheets2.ReleaseDispatch();
//	book.Close(_O((short)0),vOpt,vOpt); //�ر�EXCEL,�������ļ�

	book2.ReleaseDispatch();
//	books2.Close();
	books2.ReleaseDispatch();
	app2.ReleaseDispatch();	

}
/*  �����ṩ��ID�Ŵ����ݿ��ж�ȡ��Ӧ����ͷ,�����б��� 
*
*/
BOOL CComFunc::comSetGridHeader(CMSHFlexGrid &m_grid, ULONG id)
{

	m_grid.Clear();
	m_grid.SetRows(2);
	m_grid.SetAllowUserResizing(1);//flexResizeColumns 1 �С��û���������������µ����еĴ�С�� 
	long GRID_COLS=0, i=0;
	CString strSql;
	try{
		strSql.Format("select mc,width,align from lsq_grid_col  where id=%ld order by rank ",id);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect, adOpenDynamic ,adLockOptimistic,adCmdText); 

		m_grid.SetCols(0,GRID_COLS);
		while(!recSet->adoEOF){
			GRID_COLS++;
			m_grid.SetCols(0,GRID_COLS);
	
			strSql=(char*)_bstr_t(recSet->GetCollect("MC").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("MC"));
			m_grid.SetTextMatrix(HEADER_ROW,i,strSql);
			strSql=(char*)_bstr_t(recSet->GetCollect("width").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("width"));
			m_grid.SetColWidth(i,0,atol(strSql) );
			strSql=(char*)_bstr_t(recSet->GetCollect("align").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("align"));
			m_grid.SetColAlignment(i,atoi(strSql));
			
			i++;
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return false;
	}		

	m_grid.SetFixedCols(0);
	long  col(0),row(0);
	m_grid.SetSelectionMode(1L);
	m_grid.SetRow(0);

	for(i =0 ; i< GRID_COLS; i++){
		m_grid.SetCol( i );
		m_grid.SetCellAlignment((short)4); //���ж���
	
	}	
	CComFunc::GridSelRow(m_grid,1);
	return true;

}

UINT CComFunc::THREAD_TO_EXCEL(LPVOID lp)
{
	_Application app2;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;
	 COleVariant vOpt2(DISP_E_PARAMNOTFOUND,VT_ERROR);

	 app2.CreateDispatch("excel.application");
	if(!app2){
		AfxMessageBox("��ע��ϵͳ�б���װ��EXCEL97���ϰ汾 ,����˹��ܲ���ʹ��...");
		return false;
	}
	books2=app2.GetWorkbooks();
	book2=books2.Add(vOpt2);
	sheets2=book2.GetWorksheets();
	sheet2=sheets2.GetItem(COleVariant((short)1));


	Range vRange;
	Font font;
	long x,y;
	CString str1,str2;
	
	app2.SetVisible(false);
	((CProgressEx *)lp)->strView="";
	CMSHFlexGrid *pg=(CMSHFlexGrid *)theApp.pParentGrid.pGrid;
	

	for (x=0; x<pg->GetRows(); x++)
	{
		for( y=0 ; y< pg->GetCols(0) ; y++ )
		{
			if( y<26)str1.Format("%c%ld",'A'+y , x+1 );
			else str1.Format("%c%c%ld",'A'+ ( y/26 -1) ,'A'+y % 26,x+1 );
			vRange=sheet2.GetRange(_variant_t(str1),_variant_t(str1)); // ҽ�ƻ���
			vRange.SetValue(COleVariant(pg->GetTextMatrix(x,y)));
		}
		
		((CProgressEx *)lp)->strView.Format("%2.0f%%",double(x)/pg->GetRows()*100);
		((CProgressEx *)lp)->SetPos(x);
	}
	app2.SetVisible(true);
		
	((CProgressEx *)lp)->DestroyWindow();

	sheet2.ReleaseDispatch();

	sheets2.ReleaseDispatch();
//	book.Close(_O((short)0),vOpt,vOpt); //�ر�EXCEL,�������ļ�

	book2.ReleaseDispatch();
	books2.ReleaseDispatch();
	app2.ReleaseDispatch();	


	return true;
}

bool CComFunc::AssertPriv(UINT id)
{
	CString str,str2;
/*	str.Format(" SELECT ID FROM his3_priv_quota WHERE BM=%ld and ID= %ld AND effect=1" ,atol(LoginInformation.user_code),id);
*/	
	GetSql(str,20);
	str2.Format("%ld",atol(LoginInformation.user_code ));
	str.Replace("XT001", str2 );
	str2.Format("%ld",id);
	str.Replace("XT002",str2);
	str2=GetString(str);

	if( CComFunc::GetString(str).IsEmpty() ){
		str.LoadString(IDS_PRIV_PROMPT);
		AfxMessageBox(str);
		return false;
	}
	return true;
}

void CComFunc::SetExcelCell(_Worksheet &sheetx, int iRow, int iCol, CString &strData)
{

	/* ����EXCEL��Ԫ���ַ��� 
		sheetx  Ҫ�����Ĺ�����
		iRow	Ҫ�������������ڵ���
		iCol	Ҫ�����Ĺ�����������
		strData Ҫд����ַ���
	*/
#define _O(x) COleVariant(x)
	
	CString strCell;
	Range vRange;
	strCell.Format("%c%d",iCol+'A',iRow+1);
	vRange=sheetx.GetRange(_O(strCell),_O(strCell));
	vRange.SetValue(_O(strData));

}

void CComFunc::GridSelRow(CMSHFlexGrid &m_grid, ULONG row)
{
	long cols=m_grid.GetCols(0);
	m_grid.SetCol(0);
	m_grid.SetRow(row);
	m_grid.SetRowSel(row);
	m_grid.SetColSel(cols-1);
}
/*
// �����ṩ���ڲ��Һ�����,���س�����ʹ�õ���Ӧ
// �����ֱ�ʶ
*/
int CComFunc::GetGhType(CString &strType)
{
	int iRet =0 ;

	if( strType.Compare("QPYB") == 0 || strType.Compare("QPTD") == 0  || strType.Compare("QHMT") == 0 ){ //��Ϊ����ǰ׺��ͬ
		
		iRet=TYPE_QPYB; // ����ҽ��
			
	}
	else if( strType.Compare("��������") == 0 || strType.Compare("�ض�����") == 0 ||
		strType.Compare("��ͥ����")==0  || 
		strType.Compare("GMMT_201001")==0 )
		//20090916,�򻴵�Ҫ���������������ء�����ڲ�����Ϊ��GMMT_090916,�������л���ҽ�����
		//20100105,�򻴵�Ҫ������"�������"����ڲ�����Ϊ��GMMT_201001,��������ҽ�����
	{
		iRet=TYPE_HAYB; //��ҽ������
	}
	else if( strType.Compare("����ͳ��") == 0  || strType.Compare("GMMT_090916") == 0 ){

		iRet=TYPE_JMTC; //��ҽ������ͳ��
	}
	else if ( strType.Compare("���䱣��") == 0  )
	{
		iRet=TYPE_BCBX;
	}
	else if ( strType.Compare("��������") == 0  )
	{
		iRet=TYPE_GYQS;
	}
	else if ( strType.Compare("������Ա") == 0  )
	{
		iRet=TYPE_GS;
	}
	else if ( strType.Compare("������Ա") == 0  )
	{
		iRet=TYPE_LX;
	}
	else if ( strType.Compare("������Ա") == 0  )
	{
		iRet=TYPE_TY;
	}
	else if ( strType.Compare("����ǰ�Ϲ���") == 0  )
	{
		iRet=TYPE_GC;
	}
	else 
		iRet=0;

	return iRet;

}

bool CComFunc::GetString(CString & strSql, CString *pS, int num)
{

	for(int i=0; i<num; i++ ) pS[i]=BLANKSTR;

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		if(!recSet->adoEOF){
			for( i=0; i< num ;i++ )
				pS[i]=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
		}
			
		recSet->Close();

		return true;

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}	

}

bool CComFunc::GetSql(CString &strOut, UINT id)
{

	CString strSql;
	strOut=BLANKSTR;
	strSql.Format( " SELECT sql FROM lsq_sql_statemnet WHERE id= %ld ",id);

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		if(!recSet->adoEOF){
		
			strOut=(char*)_bstr_t(recSet->GetFields()->GetItem(0L)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(0L)->Value );
		}
		recSet->Close();

		return true;

	}
	catch(_com_error e)
	{
		strOut=BLANKSTR;
		AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}	
}

bool CComFunc::BeginCritical(CString strID, bool flag)
{
	int ib;
	CString strSql;
	if( flag ){
		try{
			_CommandPtr cmd;
			_ParameterPtr par;
			cmd.CreateInstance(__uuidof( Command ));
			par.CreateInstance(__uuidof( Parameter));
			
			_variant_t vNULL;
			vNULL.vt = VT_ERROR;
			vNULL.scode = DISP_E_PARAMNOTFOUND;
			
			cmd->put_CommandType(adCmdStoredProc) ;
			par=cmd->CreateParameter(_bstr_t("success"),adUnsignedInt,adParamOutput,20,vNULL);
			cmd->Parameters->Append( par );
			
			par=cmd->CreateParameter(_bstr_t("paraID"),adVarChar,adParamInput,50,_bstr_t( strID ) );
			cmd->Parameters->Append( par );
			
			cmd->put_CommandText(_bstr_t("PRC_gh_check"));
			cmd->ActiveConnection=HospitalConnect;
			cmd->Execute(NULL,NULL,adCmdStoredProc);
			
			ib=cmd->Parameters->GetItem("success")->Value.uintVal;
			cmd.Detach();
			par.Detach();
			if ( ib ) return true;
			else return false;
			
		}
		catch(_com_error e)
		{
			AfxMessageBox(e.ErrorMessage());
			return false;
		}
		



	}
	else{ //�����ͻ
	
		strSql.Format(" Delete From lsq_share Where serial='%s' ",strID);
		if( !CComFunc::WriteSql(strSql) )AfxMessageBox("��������ͻʱ���ִ���!!");
		return true;
		

	}
}

CString CComFunc::GetSqlItem(long i)
{
	CString str(BLANKSTR);
	str=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
	return str;
}
/*
// ͨ�������SQL���,�Զ���ȡ���������
*/
/*
void CComFunc::ReadDataForGrid(CString &strSql, CMSHFlexGrid &m_grid)
{
	long row(0),i;
	long cols=m_grid.GetCols(0);
	try{

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		m_grid.SetRedraw(false);
		while(! recSet->adoEOF){

			strSql.Format("%ld",row); //��ʾ���к�,���¼���,���ݿ�ѡ��ʱ���к��ѱ�����
			m_grid.SetTextMatrix(row,0,strSql);
			for( i=1; i< cols ; i++ )
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
				m_grid.SetTextMatrix(row,i,strSql);
			}
			row++;
			m_grid.AddItem(BLANKSTR,_variant_t(row));
			recSet->MoveNext();

		}
		recSet->Close();
		GridSelRow(m_grid,1);
		m_grid.SetRedraw(true);
	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return ;
	}
}
*/
//**********************************************************
//# ���ݱ��IDֵ,�������Ӧ����������ɫ
//
//***********************************************************

UINT CComFunc::SetGridColColor( UINT id,CMSHFlexGrid &pGrid)
{
	//�����һ�д�� �к�,�ڶ��д�� ��ɫֵ

	CUIntArray arrCol,arrBack,arrFore;
	CString strSql;
	int iRgb[3];
	long i(0),x,iLine(0);
	strSql.Format(" Select rank,cR,cG,cB,cR2,cG2,cB2 from lsq_grid_col WHERE id=%ld and color =1  order by rank ",id );
	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			i=0;
			strSql= (char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value ) ;
			arrCol.Add( atol(strSql) );
			for(x=0; x< 3; x++ ) //����ɫ
			{
				++i;
				strSql= (char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value ) ;
				iRgb[x]=atol(strSql);
			}
			arrBack.Add( RGB(iRgb[0],iRgb[1],iRgb[2] ) );

			for(x=0; x< 3; x++ ) //ǰ��ɫ
			{
				++i;
				strSql= (char*)_bstr_t(recSet->GetFields()->GetItem(i)->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(i)->Value ) ;
				iRgb[x]=atol(strSql);
			}
			arrFore.Add( RGB(iRgb[0],iRgb[1],iRgb[2] ) );

			recSet->MoveNext();
		}
	
		recSet->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}	
	long colorCols=arrCol.GetSize() ; //��Ҫ����ɫ�ʵ�����

	if( colorCols > 0 ){
		long row=pGrid.GetRows()-1 ;
		while( row > 0 ){
			
			pGrid.SetRow(row);
			for( i=0 ; i<  colorCols ; i++ )
			{
				pGrid.SetCol( arrCol[i] -1 ); //���ݿ��м�¼�ĵ�һ�д��㿪ʼ
				pGrid.SetCellBackColor(arrBack[i] );
				pGrid.SetCellForeColor(arrFore[i] );
			}
			row -- ;
		}
	}

	return true;
}

UINT CComFunc::ForWait(LPVOID pw)
{
	CDialogWait dw;
	dw.DoModal();

	return true;
}

CDialog * CComFunc::SysWait(CDialog* pt)
{
	CDialogWait *pw=new CDialogWait;
	pw->Create(IDD_DIALOG_WAIT,pt);
	pw->ShowWindow(SW_SHOW);
//	pw->UpdateData();
	return (CDialog*)pw;
}

void CComFunc::ReadDataForGrid(CString &strSql, CMSHFlexGrid &m_grid, int *iCol, int iSum)
{
	long row(0),i;
	long cols=m_grid.GetCols(0);
	double *dbSum=NULL;
	CString strTmp;


	if( iSum > 0 )	{
		dbSum=new double[iSum];
		for(i=0 ; i < iSum; i++ )dbSum[i]=0.0;
	}

	try{

		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		row=1;
		m_grid.SetRedraw(false);
		while(! recSet->adoEOF){

			strSql.Format("%ld",row); //��ʾ���к�,���¼���,���ݿ�ѡ��ʱ���к��ѱ�����
			m_grid.SetTextMatrix(row,0,strSql);
			for( i=1; i< cols ; i++ )
			{
				strSql=(char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ? _variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value );
				m_grid.SetTextMatrix(row,i,strSql);
				for(int x=0; x<iSum ; x++ )
				{
					if( iCol[x] == i )dbSum[x]+=atof(strSql);

				}
			}
			row++;
			m_grid.AddItem(BLANKSTR,_variant_t(row));
			recSet->MoveNext();

		}
		recSet->Close();
		for(i=0 ; i< iSum ; i++ )//��д������
		{	
			strTmp.Format("%.2f",dbSum[i]);
			m_grid.SetTextMatrix(row,iCol[i],strTmp);
			

		}
		if(iSum > 0 ) delete[] dbSum;
		GridSelRow(m_grid,1);
		m_grid.SetRedraw(true);
	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		recSet->Close();
		return ;
	}
}

void CComFunc::GetBigMoney(const double &dMoney, CString &strReturnValue)
{
     CString strMoney;

     strMoney.Format ("%.2f" , dMoney);

	 if( strMoney.GetLength() >15 ){
		 strReturnValue="��"+strMoney;
		 return ; //��ֵ̫��
	 }

     CString strUnit = "Ԫʰ��Ǫ��ʰ��Ǫ��ʰ��Ǫ";

     CString strNumber = "��Ҽ��������½��ƾ�";

     CString strOtherUnit = "���Ƿ�";

 

     //�����ַ�����������С�����ݴ���

     int nPos = strMoney.Find (".");
     int nLength = strMoney.GetLength ();
     if(nPos < 0)
         nPos = nLength;
 //    CString strReturnValue;
     int nCount = 0;
     bool bZero = false;
     bool bNeedLevel = false;    //�Զε�ʶ�������Ƿ���Ҫ���ֶ��������ڣ����
     //���������ݽ��з���ʶ����

     for(int i = nPos - 1;i >= 0;i --)
     {
         TCHAR ch = strMoney.GetAt (i);
         if(nCount % 4 == 0 && nCount > 0)
         {
               //������������Ϊ����λ���򣩣���ڰ�λ���ڣ��ȣ���Ҫ���ö�
              bNeedLevel = true;
         }
         if(ch == '0')
         {
               //ֻ��ʰ��Ǫλ�ģ�����ʶ����Ҫ���ǵ�ʰ�������ԣ����磱����Ҽʰ�������Ҽʰ��
              if(nCount % 4 != 0)

                   bZero = true;
         }
         else
         {

              CString strTemp(strReturnValue);

              strReturnValue = strNumber.Mid ((ch - 0x30) * 2 , 2);

              if(nCount > 0)

              {

                  strReturnValue += strUnit.Mid (nCount * 2 , 2);

                   if(nCount % 4 != 0 && bNeedLevel)

                   {

                         //�����ж��Ƿ���Ҫ�������������ڵ�

                       strReturnValue += strUnit.Mid (int(nCount / 4) * 8 , 2);

                   }

                   bNeedLevel = false;

              }

              if(bZero)

              {

                   //ֻ�бȵ�ǰ�����λҪ���������ֲŲ���

                   if(!strTemp.IsEmpty ())

                       strReturnValue += strNumber.Left (2);

                   bZero = false;

              }

              strReturnValue += strTemp;

         }

         nCount ++;

     }

     strReturnValue += strUnit.Left (2);
	 if(strReturnValue.GetLength()<=2) strReturnValue="";
	 //��ֹ��������Ϊ��

     bool bAllZero = true;

     //����ʵ�ֶ�С�������Ĵ���

     //���ж��Ƿ�Ϊȫ�㣬����Ҫ������

     if(nPos < nLength)

     {

         if(nLength > 2)

              nLength = 2;

         for(int i = 0;i < nLength;i ++)

              if(strMoney.GetAt (nPos + i + 1) != '0')

                   bAllZero = false;

     }

     if(bAllZero)

     {

         strReturnValue += strOtherUnit.Left (2);

     }

     else

     {

          //�ԷֽǵĴ���

         for(int i = 0;i < nLength;i ++)

         {

              TCHAR ch = strMoney.GetAt (nPos + 1 + i);

              if(ch == '0' && i > 0)

              {

              }

              else

              {

                   strReturnValue += strNumber.Mid ((ch - 0x30) * 2 , 2);

                   if(ch != '0')

                       strReturnValue += strOtherUnit.Mid ((i + 1) * 2 , 2);

              }

         }

     }

  //   return strReturnValue;
}

bool CComFunc::GetStringCollect(CString &strSql, CStringArray &ary)
{

	ary.RemoveAll();
	const int i=0;

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 

		while(!recSet->adoEOF){
				ary.Add( (char*)_bstr_t(recSet->GetFields()->GetItem(long(i))->Value.vt == VT_NULL ?_variant_t(BLANKSTR):recSet->GetFields()->GetItem(long(i))->Value ) );
				recSet->MoveNext();
		}
			
		recSet->Close();

		return true;

	}
	catch(_com_error e)
	{
		AfxMessageBox(strSql);
		recSet->Close();
		return false;
	}	

}

//��� CGridCtrl ���б�����,�������غ���,��ԭ�е�CMSHGRID������
BOOL CComFunc::comSetGridHeader(CGridCtrl &m_grid, ULONG id)
{

	m_grid.SetRowCount(2);
	m_grid.SetFixedColumnSelection(false);
	m_grid.SetFixedRowSelection(false);
	m_grid.SetSingleRowSelection(true); //����ѡ��ģʽ
	m_grid.SetSingleColSelection(false);//����ѡ��ģʽ�ر�
	m_grid.SetFixedRowCount(1);


	
	long GRID_COLS=0, i=0;
	CString strSql;
	try{
		strSql.Format("select mc,width,align from lsq_grid_col  where id=%ld order by rank ",id);
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect, adOpenDynamic ,adLockOptimistic,adCmdText); 

		//m_grid.SetCols(0,GRID_COLS); 
		m_grid.SetColumnCount(GRID_COLS);
		while(!recSet->adoEOF){
			GRID_COLS++;
			m_grid.SetColumnCount(GRID_COLS);
	
			strSql=(char*)_bstr_t(recSet->GetCollect("MC").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("MC"));
			m_grid.SetItemText(0,i,strSql);
			strSql=(char*)_bstr_t(recSet->GetCollect("width").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("width"));
			if( atol(strSql) ==0 ) //���Ϊ0������
				m_grid.SetColumnWidth(i,0 );
			strSql=(char*)_bstr_t(recSet->GetCollect("align").vt==VT_NULL? _variant_t( BLANKSTR):recSet->GetCollect("align"));
			m_grid.SetItemFormat(0,i,atoi(strSql));
			
			i++;
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return false;
	}	
	
	m_grid.AutoSize();


	return true;
}
// ���������ؼ����ã�SQL��䣬���������Ҫ���ܵ��У��������ݴ���λ�ã���������У���Ԫ���������
// 2015/12/28
BOOL CComFunc::ReadDataForGrid(CGridCtrl& m_grid, CString & strSql,int gridCols,vector<int> &vtCols,vector<double> &vtCount,int sn,
	vector<int> &vtAlign )
{

	m_grid.SetRedraw(false);
	m_grid.SetListMode();
	m_grid.SetSingleRowSelection(true);

	m_grid.SetFrameFocusCell(false);
	m_grid.SetTrackFocusCell(false);
	m_grid.SetRowCount(1);

	vector<double>::size_type iCols=vtCols.size();
	vector<int>::iterator  iteTmp;
	int iAry;
	vector<int>::size_type iNum=vtAlign.size(); //�����Ƿ��ж�������
	long i(1);

	try{
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		long col(0);
		//���±������ںϲ���Ԫ��
		//vector<	int>  iBegin(gridCols,1),iCounting(gridCols,1);
		//CStringArray aryBegin;
		//aryBegin.SetSize(gridCols);

		while(!recSet->adoEOF){
			m_grid.InsertRow("xx");

			while( col < gridCols ){

				strSql=CComFunc::GetSqlItem(col) ;

				m_grid.SetItemFormat(i,col,iNum==0?0 : vtAlign[col] );	
				//������Ҫ������趨˳���
				if( col == sn ){
					strSql.Format("%d",i);
					m_grid.SetItemFormat(i,col,37U);

				}
				
				m_grid.SetItemText(i,col,strSql);
				
				//����Ҫ�����Ӧ���н�������ۼ�
				if( ( iteTmp= std::find(vtCols.begin(),vtCols.end(),col) )  !=vtCols.end()  && iCols > 0 )
				{

					iAry=iteTmp-vtCols.begin();
					vtCount[iAry]+=atof(strSql);
					m_grid.SetItemFormat(i,col,DT_RIGHT);
				}

				col++;
		}

		col=0;
		i++;

		recSet->MoveNext();

	}
		recSet->Close();

	}

	catch(_com_error e)

	{

		AfxMessageBox(TEXT("���ݿ����ӳ���"));

		AfxMessageBox(e.Description());
		return false;
	}

	//������һ�л�����
	m_grid.InsertRow("xx");
	m_grid.SetItemText(i,0,"�ϼ�");
	int idx;
	for(idx=0;idx<vtCols.size();idx++)
	{
		strSql.Format("%.2f",vtCount[idx]);
		m_grid.SetItemText(i,vtCols[idx],strSql);
		m_grid.SetItemFormat(i,vtCols[idx],DT_RIGHT);
	}
	m_grid.SetRedraw(true);
	return true;
}

void CComFunc::toExcel(CGridCtrl &  m_grid)
{
	_Application app2;
	Workbooks books2;
	_Workbook book2;
	Worksheets sheets2;
	_Worksheet sheet2;


	 COleVariant vOpt2(DISP_E_PARAMNOTFOUND,VT_ERROR);

	 if (! app2.CreateDispatch(_T("Excel.Application"),NULL))   
	 {   
		 AfxMessageBox(_T("����Excel����ʧ��,�����û�а�װEXCEL������!"));   
		 return ;  
	 } 

	 books2=app2.GetWorkbooks();
	book2=books2.Add(vOpt2);
	sheets2=book2.GetWorksheets();
	sheet2=sheets2.GetItem(COleVariant((short)1));


	Range vRange;
	long x,y;
	CString str1,str2;
	


	for (x=0; x< m_grid.GetRowCount() ; x++)
	{
		for( y=0 ; y< m_grid.GetColumnCount() ; y++ )
		{
			if( y<26)str1.Format("%c%ld",'A'+y , x+1 );
			else str1.Format("%c%c%ld",'A'+ ( y/26 -1) ,'A'+y % 26,x+1 );
			vRange=sheet2.GetRange(_variant_t(str1),_variant_t(str1)); 
			vRange.SetValue(COleVariant(m_grid.GetItemText(x,y) ));
		}
	}
		
	app2.SetVisible(true);
	sheet2.ReleaseDispatch();

	sheets2.ReleaseDispatch();

	book2.ReleaseDispatch();

	books2.ReleaseDispatch();
	app2.ReleaseDispatch();	
	app2=NULL;
}
//����SQL���������д��Ͽ�ID
BOOL CComFunc::SetComboxType(CStringArray &aryID, CComboBox &cbType, const CString &strSql)
{

	try{
		aryID.RemoveAll();
		cbType.ResetContent();
		aryID.Add("");
		cbType.AddString("");
		recSet->Open(_bstr_t(strSql),(IDispatch*)HospitalConnect,adOpenDynamic,adLockOptimistic,adCmdText); 
		while(!recSet->adoEOF){
			
			aryID.Add(GetSqlItem(0));
			cbType.AddString(GetSqlItem(1));
			recSet->MoveNext();
	
		}
		recSet->Close();
		
	}
	catch(_com_error e)
	{
		AfxMessageBox("���ִ���,����SQL���...");
		return false;
	}		
	return true;
}
