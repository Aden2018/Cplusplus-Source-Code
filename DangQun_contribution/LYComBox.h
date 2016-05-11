#pragma once


// CLYComBox

class CLYComBox : public CComboBox
{
	DECLARE_DYNAMIC(CLYComBox)

public:
	CLYComBox();
	virtual ~CLYComBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

public:
	BOOL m_bReadOnly;
	CFont* m_pEdtFont;
	CFont* m_pListFont;
	int m_nEdtFontPtSize;
	int m_nListFontPtSize;
	CString m_csEdtFontName;
	CString m_csListFontName;
	COLORREF m_clrEditText;
	COLORREF m_clrListText;

public:
	void SetReadOnly(BOOL bReadOnly=TRUE);
	void SetEdtFontHelper();
	void SetListFontHelper();
	void SetEditNewFont(int nPtSize, CString csFontName=_T("Î¢ÈíÑÅºÚ"));
	void SetListNewFont(int nPtSize, CString csFontName=_T("Î¢ÈíÑÅºÚ"));
	void SetEdtTextColor(COLORREF clrEdtText);
	void SetListTextColor(COLORREF clrListText);

public:
	BOOL m_bBtnHover;
	BOOL m_bBtnDown;
	CBitmap m_bmButton;

public:
	void	DrawShowText(CDC* pDC);
	void	DrawBtnImg(CDC* pDC, CRect rcButton);

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


