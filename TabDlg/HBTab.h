#pragma once

class CExt_TCITEM
{
public:
	CExt_TCITEM(){
		iBaselineLen = 0;
	}
public:
	UINT iIndex;//インデックス
	UINT ID;//識別子
	POINT pt[9];
	int pt_num;
	CRgn pl;
	CSize xySize;
	int iBaselineLen;
	CString title;

	CExt_TCITEM& operator=(const CExt_TCITEM& nSrc){
		if (this != &nSrc){
			this->iIndex = nSrc.iIndex;
			this->ID = nSrc.ID;
			this->pt_num = nSrc.pt_num;
			for(int i=0;i<this->pt_num;i++){
				this->pt[i].x = nSrc.pt[i].x;
				this->pt[i].y = nSrc.pt[i].y;
			}

			if(nSrc.pl.m_hObject){
				this->pl.CreatePolygonRgn(pt,pt_num,ALTERNATE);
			}

			this->xySize.SetSize(nSrc.xySize.cx,nSrc.xySize.cy);
			this->iBaselineLen = nSrc.iBaselineLen;
			this->title = nSrc.title;
		}
		return *this;
	}
	void CreatePolyon(int iStartCX, int nType){
		int iSideLen = this->xySize.cy/2 ;
		int iBuf = 5;
		int iRightBuf = 30;

		pt[0].x = iSideLen + iStartCX;
		pt[0].y = 1;

		pt[1].x = 0 + iStartCX;
		pt[1].y = this->xySize.cy;

		pt[2].x = iSideLen + iBuf + this->xySize.cx + iRightBuf + iSideLen + iStartCX;
		pt[2].y = this->xySize.cy;

		pt[3].x = iSideLen + iBuf + this->xySize.cx + iRightBuf + iStartCX;
		pt[3].y = 1;

		pt[4].x = iSideLen + iStartCX;
		pt[4].y = 1;

		pt_num = 5;

		if(pl.m_hObject){pl.DeleteObject();}
		pl.CreatePolygonRgn(pt,pt_num,ALTERNATE);
	}

} ;


// CHBTab

class CHBTab : public CWnd
{
	DECLARE_DYNAMIC(CHBTab)

public:
	CHBTab();
	virtual ~CHBTab();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	// 選択したタブのインデックス
	int m_ShapeType;// 0：/￣￣￣￣＼ 1:○ 2:□ 3:/￣￣￣|
	int m_iSel;
	int m_iFlatSel;
	BOOL m_bGradient;
	int m_iTabMaxNum;

private:
	CRect m_Rect;
	CSize m_Size;
	COLORREF m_Color;
	COLORREF m_BgColor;
	CPtrList m_ItemList;
	BOOL m_bDrawedBtn;
	BOOL m_bFlag;
	BOOL m_bColor;
	CBitmapButton m_leftBtn;
	CBitmapButton m_rightBtn;
	int m_iLeftmostTab;//最左のインデックス、とタブのずれたインデックス
	int m_iRightmostTab;


public:
	LONG InsertItem(CString sTitle);
	void ClearItemList();
	void AdjustSize(CSize nSize);
	int GetInsertStartCX(int nIndex=-1);
	void SetColor(COLORREF nRGB);
	void SetGradientDraw(BOOL bGradient);
	int DrawFlatBtn();
	void EraseTab(CExt_TCITEM & tci);
	void EraseTail();
	COLORREF NoSelTabColor(COLORREF crBase, float fFactor);
	COLORREF SelTabColor(COLORREF crBase, float fFactor);
	void CreateArrowBtn();
	void MoveItems(BOOL bLeft=1);
	void SetBaselineLen(int nItem, int iLen);
	BOOL Create(CWnd * pParent, DWORD dwStyle, const RECT& rect);
	virtual BOOL DestroyWindow();

public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonArrow(UINT nID);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
};


