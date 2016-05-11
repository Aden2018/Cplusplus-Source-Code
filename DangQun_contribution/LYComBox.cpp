// LYComBox.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "LYComBox.h"


// CLYComBox

IMPLEMENT_DYNAMIC(CLYComBox, CComboBox)

CLYComBox::CLYComBox()
{
	m_bReadOnly = FALSE;
	m_pEdtFont = NULL;
	m_pListFont = NULL;
	m_nEdtFontPtSize = 90;
	m_nListFontPtSize = 90;
	m_csEdtFontName = _T("微软雅黑");
	m_csListFontName = _T("微软雅黑");
	m_clrEditText = RGB(0, 0, 0);
	m_clrListText = RGB(0, 0, 0);

	m_bBtnHover = FALSE;
	m_bBtnDown = FALSE;
	m_bmButton.LoadBitmap(IDB_BUTTON);
}

CLYComBox::~CLYComBox()
{
}


BEGIN_MESSAGE_MAP(CLYComBox, CComboBox)
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CLYComBox 消息处理程序




HBRUSH CLYComBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	// 编辑框设置
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		CFont* font = new CFont;
		font->CreatePointFont(m_nEdtFontPtSize, m_csEdtFontName);
		pDC->SelectObject(font);
		pDC->SetTextColor(m_clrEditText);
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH B = CreateSolidBrush(RGB(255,255,255));
		return (HBRUSH) B; //返回画刷句柄
	}
	if(nCtlColor==CTLCOLOR_EDIT)
	{
		CEdit* pEdit = reinterpret_cast<CEdit*>(pWnd);
		pEdit->SetLimitText(256); // 无效
		pDC->SetTextColor(m_clrEditText);
	}
	// 列表框设置
	if(nCtlColor==CTLCOLOR_LISTBOX)
	{
		CFont* font = new CFont;
		font->CreatePointFont(m_nListFontPtSize, m_csListFontName);
		pDC->SelectObject(font);
		pDC->SetTextColor(m_clrListText);
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH B = CreateSolidBrush(RGB(255, 255, 255));
		return (HBRUSH) B; //返回画刷句柄
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CLYComBox::SetEditNewFont( int nPtSize, CString csFontName/*=_T("微软雅黑")*/ )
{
	if(nPtSize>0)
		m_nEdtFontPtSize = nPtSize;
	m_csEdtFontName = csFontName;
	SetEdtFontHelper();
}

void CLYComBox::SetListNewFont( int nPtSize, CString csFontName/*=_T("微软雅黑")*/ )
{
	if(nPtSize>0)
		m_nListFontPtSize = nPtSize;
	m_csListFontName = csFontName;
	SetListFontHelper();
}

void CLYComBox::SetEdtFontHelper()
{
	if(m_pEdtFont)
		delete m_pEdtFont;
	m_pEdtFont = new CFont;

	LOGFONT lgFont;
	lgFont.lfCharSet = DEFAULT_CHARSET;
	lgFont.lfClipPrecision = 0;
	lgFont.lfEscapement = 0;
	_tcscpy_s(lgFont.lfFaceName, m_csEdtFontName);
	lgFont.lfHeight = m_nEdtFontPtSize;
	lgFont.lfItalic = 0;
	lgFont.lfOrientation = 0;
	lgFont.lfOutPrecision = 0;
	lgFont.lfPitchAndFamily = 2;
	lgFont.lfQuality = 0;
	lgFont.lfStrikeOut = 0;
	lgFont.lfUnderline = 0;
	lgFont.lfWidth = 0;
	lgFont.lfWeight = FW_NORMAL;

	m_pEdtFont->CreatePointFontIndirect(&lgFont);
	SetFont(m_pEdtFont);
}

void CLYComBox::SetListFontHelper()
{
	if(m_pListFont)
		delete m_pListFont;
	m_pListFont = new CFont;

	LOGFONT lgFont;
	lgFont.lfCharSet = DEFAULT_CHARSET;
	lgFont.lfClipPrecision = 0;
	lgFont.lfEscapement = 0;
	_tcscpy_s(lgFont.lfFaceName, m_csListFontName);
	lgFont.lfHeight = m_nListFontPtSize;
	lgFont.lfItalic = 0;
	lgFont.lfOrientation = 0;
	lgFont.lfOutPrecision = 0;
	lgFont.lfPitchAndFamily = 2;
	lgFont.lfQuality = 0;
	lgFont.lfStrikeOut = 0;
	lgFont.lfUnderline = 0;
	lgFont.lfWidth = 0;
	lgFont.lfWeight = FW_NORMAL;

	m_pListFont->CreatePointFontIndirect(&lgFont);
}

BOOL CLYComBox::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	SetEdtFontHelper();
	SetListFontHelper();
	//this->LimitText(256); // 无效
	return CComboBox::PreCreateWindow(cs);
}


void CLYComBox::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TRACKMOUSEEVENT tme;
	tme.cbSize		= sizeof(tme);
	tme.hwndTrack	= m_hWnd;
	tme.dwHoverTime	= 1;
	tme.dwFlags		= TME_LEAVE | TME_HOVER;
	_TrackMouseEvent(&tme);

	CComboBox::OnMouseMove(nFlags, point);
}


void CLYComBox::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bBtnHover)
		m_bBtnHover = FALSE;
	if(m_bBtnDown)
		m_bBtnDown = FALSE;

	Invalidate();
	return ;

	//CComboBox::OnMouseLeave();
}


void CLYComBox::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	COMBOBOXINFO combInfo;
	CRect rcButton;
	// 获取控件信息
	combInfo.cbSize = sizeof(COMBOBOXINFO);
	GetComboBoxInfo(&combInfo);
	// 获取按钮区域
	rcButton = combInfo.rcButton;
	if(rcButton.PtInRect(point))
		m_bBtnHover = TRUE;

	Invalidate(FALSE);
	return ;
	//CComboBox::OnMouseHover(nFlags, point);
}

void CLYComBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	COMBOBOXINFO combInfo;
	CRect rcButton;
	// 获取控件信息
	combInfo.cbSize = sizeof(COMBOBOXINFO);
	GetComboBoxInfo(&combInfo);
	// 获取按钮区域
	rcButton = combInfo.rcButton;
	if(rcButton.PtInRect(point))
		m_bBtnDown = TRUE;

	CComboBox::OnLButtonDown(nFlags, point);
}

void CLYComBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	COMBOBOXINFO combInfo;
	CRect rcButton;
	// 获取控件信息
	combInfo.cbSize = sizeof(COMBOBOXINFO);
	GetComboBoxInfo(&combInfo);
	// 获取按钮区域
	rcButton = combInfo.rcButton;
	if(rcButton.PtInRect(point))
		m_bBtnDown = FALSE;

	CComboBox::OnLButtonUp(nFlags, point);
}


void CLYComBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CComboBox::OnPaint()

	CRect rcComb;
	CBrush brushInner, brushOuter;
	COMBOBOXINFO combInfo;

	combInfo.cbSize = sizeof(COMBOBOXINFO);
	GetComboBoxInfo(&combInfo);

	if(combInfo.stateButton==8)
		m_bBtnDown = TRUE;
	
	GetClientRect(rcComb);
	//brushInner.CreateSolidBrush(RGB(240, 248, 255));
	brushOuter.CreateSolidBrush(RGB(109, 161, 16));
	
	CPen rp,*op;
	rp.CreatePen(PS_SOLID,1,RGB(255,0,0));
		op=dc.SelectObject(&rp);
		dc.MoveTo(rcComb.left,rcComb.bottom);
	dc.LineTo(rcComb.right,rcComb.bottom); //划上横线
//	dc.FillRect(rcComb, &brushInner);
//	dc.FrameRect(rcComb, &brushOuter);
	DrawBtnImg(&dc, combInfo.rcButton);
	//DrawShowText(&dc);
}

void CLYComBox::DrawShowText( CDC* pDC )
{
	TCHAR tszText[MAX_PATH+1];
	GetWindowText(tszText, MAX_PATH);

	if(tszText==NULL)
		return ;

	CFont* hOldFont = pDC->SelectObject(GetFont());
	CSize szExtent = pDC->GetTextExtent(tszText, _tcslen(tszText));
	int nMode = pDC->SetBkMode(TRANSPARENT);
	CPoint point(2, 2);

	pDC->DrawState(point, szExtent, tszText, DSS_NORMAL, TRUE, 0, (HBRUSH)NULL);
	pDC->SelectObject(hOldFont);
	pDC->SetBkMode(nMode);
}

void CLYComBox::DrawBtnImg( CDC* pDC, CRect rcButton )
{
	CBitmap* pOldBitmap;
	CDC* pMemDC = new CDC;
	BITMAP bitmapBtn;
	m_bmButton.GetBitmap(&bitmapBtn);

	int nLeft = (rcButton.Width()-bitmapBtn.bmWidth/2)/2;
	int nTop = (rcButton.Height()-bitmapBtn.bmHeight/2)/2;

	// 读位图到内存
	pMemDC->CreateCompatibleDC(pDC);
	pOldBitmap = pMemDC->SelectObject(&m_bmButton);
	if(m_bBtnDown || m_bBtnHover)
		pDC->BitBlt(rcButton.left, rcButton.top+nTop, rcButton.Width()/2, rcButton.Height(), pMemDC, rcButton.Width()/2+1, 0, SRCCOPY);
	else
		pDC->BitBlt(rcButton.left, rcButton.top+nTop, rcButton.Width()/2, rcButton.Height(), pMemDC, 0, 0, SRCCOPY);

	pMemDC->SelectObject(pOldBitmap);
	// 释放内存
	ReleaseDC(pMemDC);
	delete pMemDC;
	pMemDC = NULL;
}

void CLYComBox::SetEdtTextColor( COLORREF clrEdtText )
{
	m_clrEditText = clrEdtText;
}

void CLYComBox::SetListTextColor( COLORREF clrListText )
{
	m_clrListText = clrListText;
}

void CLYComBox::SetReadOnly( BOOL bReadOnly/*=TRUE*/ )
{
	m_bReadOnly = bReadOnly;
	// 该属性应该在此处进行一次性的设置，而不要在OnCtlColor中设置，因为它的调用太频繁
	// 获取组合框中的编辑框窗口指针，设置只读属性
	::CWnd *pWnd = this->GetWindow(GW_CHILD);
	while(pWnd)
	{
		TCHAR classname[256];
		::GetClassName(pWnd->m_hWnd, classname, 256);
		if(lstrcmpi(classname, _T("Edit")) == 0)
			break;
		if(pWnd)
			pWnd = pWnd->GetNextWindow();
	}
	CEdit *pEdit = (CEdit*)pWnd;
	pEdit->SetReadOnly(m_bReadOnly);
}

