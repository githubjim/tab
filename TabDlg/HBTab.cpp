// HBTab.cpp : 実装ファイル
//

#include "stdafx.h"
#include "TabDlg.h"
#include "HBTab.h"


// CHBTab

IMPLEMENT_DYNAMIC(CHBTab, CWnd)

CHBTab::CHBTab()
: m_iSel(0)
{
	m_ShapeType = 0;

	m_iFlatSel = 0;
	m_bDrawedBtn = FALSE;
	m_bFlag = FALSE;

	m_Color = ::GetSysColor(COLOR_3DFACE);
	m_BgColor = NoSelTabColor(m_bColor ? m_Color : ::GetSysColor(COLOR_3DFACE) , 0.5f);
	m_bColor = FALSE;
	m_iTabMaxNum = 0;

	m_iLeftmostTab = m_iRightmostTab = 0;

}

CHBTab::~CHBTab()
{
}


BEGIN_MESSAGE_MAP(CHBTab, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
//	ON_WM_DRAWITEM()
//	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave) 
 	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover) 
	ON_WM_LBUTTONUP()
	ON_COMMAND_RANGE(0x334, 0x335, OnBnClickedButtonArrow)
END_MESSAGE_MAP()



// CHBTab メッセージ ハンドラ



BOOL CHBTab::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	//背景を描く前にすべて消す
	CRect   r(0,0,m_Size.cx,m_Size.cy);
	CBrush defaultBrush;
	defaultBrush.CreateSolidBrush( ::GetSysColor(CTLCOLOR_DLG ) );
	CBrush * oldBrush = pDC->SelectObject(&defaultBrush);
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 1,::GetSysColor(CTLCOLOR_DLG ));
	CPen* pOldPen = pDC->SelectObject(&penBlack);
	pDC->FillRect(&r, &defaultBrush);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(oldBrush);

	int iMostRight = 0;
	for(int i=m_iLeftmostTab;i<m_iRightmostTab;i++){
		CExt_TCITEM     tci;
		CExt_TCITEM * p = (CExt_TCITEM*)(m_ItemList.GetAt(m_ItemList.FindIndex(i)));
		tci = *p;

		CRgn   rgn;
		//CBrush brush;
		//brush.CreateSolidBrush( ::GetSysColor( i == m_iSel ? COLOR_3DHIGHLIGHT : COLOR_3DFACE ) );
		rgn.CreatePolygonRgn( tci.pt, tci.pt_num, ALTERNATE );
		//pDC->FillRgn( &rgn, &brush );

		pDC->Polyline(tci.pt, tci.pt_num );

		COLORREF crFrom = i==m_iSel ? SelTabColor(m_Color,1.4f) : NoSelTabColor(m_bColor ? m_Color : ::GetSysColor(COLOR_3DFACE),0.9f);
		COLORREF crTo = i==m_iSel ? ::GetSysColor(COLOR_3DFACE) : NoSelTabColor(m_bColor ? m_Color : ::GetSysColor(COLOR_3DFACE) , 0.7f);

		int nROrg = GetRValue(crFrom);
		int nGOrg = GetGValue(crFrom);
		int nBOrg = GetBValue(crFrom);
		int nRDiff = GetRValue(crTo) - nROrg;
		int nGDiff = GetGValue(crTo) - nGOrg;
		int nBDiff = GetBValue(crTo) - nBOrg;
			
		DWORD   dwSize = rgn.GetRegionData(0, NULL);
		BYTE* pData=new BYTE[dwSize];

		rgn.GetRegionData((LPRGNDATA)pData,dwSize);//(LPRGNDATA)pData
		LPRGNDATA d = (LPRGNDATA)pData;
		CRect * rect = (CRect*)(d->Buffer);
		int nHeight = d->rdh.nCount;
		for(UINT i = 1; i< d->rdh.nCount;i++){
			
			//int nRed = nROrg + (i * ( nRDiff - nROrg) / nHeight);
			//int nGreen = nGOrg + (i * (nGDiff - nGOrg) / nHeight);
			//int nBlue = nBOrg + (i * (nBDiff - nBOrg) / nHeight);
			int nRed = nROrg + (i * nRDiff) / nHeight;
			int nGreen = nGOrg + (i * nGDiff) / nHeight;
			int nBlue = nBOrg + (i * nBDiff) / nHeight;
			
			pDC->FillSolidRect((rect+i), RGB(nRed, nGreen, nBlue));
		}
		delete pData;

		rgn.DeleteObject();

		iMostRight = tci.pt[2].x;
	}
	//残った区域を消す 
	if(iMostRight < m_Size.cx){
		CDC * pDC = GetDC();
		CRect   rTail(iMostRight+1,0,m_Size.cx,m_Size.cy);
		CBrush defaultBrush;
		defaultBrush.CreateSolidBrush( ::GetSysColor(CTLCOLOR_DLG ) );
		CBrush * oldBrush = pDC->SelectObject(&defaultBrush);
		CPen penBlack;
		penBlack.CreatePen(PS_SOLID, 1,::GetSysColor(CTLCOLOR_DLG ));
		CPen* pOldPen = pDC->SelectObject(&penBlack);
		pDC->FillRect(&rTail, &defaultBrush);

		pDC->SelectObject(pOldPen);
		pDC->SelectObject(oldBrush);
	}

	return CWnd::OnEraseBkgnd(pDC);
}

void CHBTab::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ここにメッセージ ハンドラ コードを追加します。
	// 描画メッセージで CWnd::OnPaint() を呼び出さないでください。
	//CDC * pDC = this->GetDC();

	for(int i=m_iLeftmostTab;i<m_iRightmostTab;i++){		
		CExt_TCITEM     tci;
		CExt_TCITEM* p = (CExt_TCITEM*)(m_ItemList.GetAt(m_ItemList.FindIndex(i)));
		tci = *p;
		
	    dc.SetBkMode( TRANSPARENT );                          // just text

		LOGFONT logfont;
		memset( &logfont, 0, sizeof( LOGFONT ) );
		GetParent()->GetFont()->GetLogFont(&logfont);
		logfont.lfHeight = 16;
		//_tcscpy(logfont.lfFaceName,logfont.lfFaceName ); //_T("ＭＳ ゴシック")
		CFont Font;
		Font.CreateFontIndirect(&logfont); 

		CFont* pOldfont = dc.SelectObject( &Font );                  // select tab font
		//1: 反対色を取得
		COLORREF rgb = i == m_iSel ? m_Color : m_BgColor;
		int nR = 255 - GetRValue(rgb);
		int nG = 255 - GetGValue(rgb);
		int nB = 255 - GetBValue(rgb);
		rgb = RGB(nR,nG,nB);
		//2: 色着いた場合白色を設置
		//rgb = m_bColor ? RGB(255,255,255) : ::GetSysColor(COLOR_BTNTEXT);
		dc.SetTextColor(rgb);

		dc.TextOut( tci.pt[0].x + 5,tci.xySize.cy/3-2,tci.title);
		dc.SelectObject(pOldfont);

		//バツのボタンを作る
		//CRgn   rgn;
		//CBrush brush;
		//brush.CreateSolidBrush( ::GetSysColor( i == m_iSel ? COLOR_3DHIGHLIGHT : COLOR_3DFACE ) );
		//rgn.CreatePolygonRgn( tci.pt, tci.pt_num, ALTERNATE );
		//dc.create
		//pDC->FillRgn( &rgn, &brush );

		//pDC->Polyline(tci.pt, tci.pt_num );

		//×を描画
		CPen linePen;
		linePen.CreatePen(PS_SOLID, 2,m_Color-22);
		CPen* pOldPen = dc.SelectObject(&linePen);
		dc.SelectObject(&linePen);

		CRect r(tci.pt[3].x-5-15,4,tci.pt[3].x-5-2,17);
		dc.MoveTo(CPoint(r.left+3,r.top+3));
		dc.LineTo(CPoint(r.right-4,r.bottom-4));
		dc.MoveTo(CPoint(r.left+9,r.top+3));
		dc.LineTo(CPoint(r.right-9,r.bottom-3));
		//put back the old objects
		dc.SelectObject(pOldPen);
	}
}

void CHBTab::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	CRect rTail(m_Size.cx-2*15,(m_Size.cy-19)/2 - 2,m_Size.cx,(m_Size.cy-19)/2 - 2 + 19);
	if(rTail.PtInRect(point)) 
		return;//重なるコントロールの動作で互い与えないように以上のコードを作成

	int iStep = m_iLeftmostTab;
	for(int i=m_iLeftmostTab;i<m_iRightmostTab;i++){
		CExt_TCITEM * pItem = (CExt_TCITEM*)m_ItemList.GetAt(m_ItemList.FindIndex(i));

		if(pItem->pl.PtInRegion(point)){
			CRect r(pItem->pt[3].x-5-15,3,pItem->pt[3].x-5-2,16);
			if(r.PtInRect(point)){
			}
			else{
				m_iSel = iStep;
			}
			break;
		}
		iStep++;
	}

	//POSITION pos = m_ItemList.GetHeadPosition();
	//POSITION oldPos = pos;
	//int iStep = 0;
	//while(pos != 0){
	//	oldPos = pos;
	//	CExt_TCITEM  * pItem = (CExt_TCITEM  *)m_ItemList.GetNext(pos);
	//	
	//	if(pItem->pl.PtInRegion(point)){
	//		CRect r(pItem->pt[3].x-5-15,3,pItem->pt[3].x-5-2,16);
	//		if(r.PtInRect(point)){
	//		}
	//		else{
	//			m_iSel = iStep;
	//		}
	//		break;
	//	}
	//	iStep++;
	//}
	Invalidate();


	CWnd::OnLButtonDown(nFlags, point);
}


LONG CHBTab::InsertItem(CString sTitle)
{
	++m_iTabMaxNum;

	CExt_TCITEM *pItem = new CExt_TCITEM(); 
	pItem->iIndex = m_ItemList.GetCount();
	pItem->ID = m_iTabMaxNum-1;
	pItem->title = sTitle.GetBuffer();
	sTitle.ReleaseBuffer();

	CRect r;
	this->GetClientRect(&r);
	pItem->xySize = CSize(sTitle.GetLength() * 10,r.bottom-3);

	//switch(m_ShapeType){
	//	case 0:pItem->ID
			pItem->CreatePolyon(GetInsertStartCX(),m_ShapeType);
	//		break;
	//}

	m_ItemList.AddTail(pItem);

	if(m_Size.cx > pItem->pt[1].x){
		m_iRightmostTab = pItem->iIndex + 1;
	}
	if(m_Size.cx < pItem->pt[2].x ){
		if(!m_leftBtn){
			CreateArrowBtn();
		}
		else{
			m_rightBtn.EnableWindow(1);
		}
	}
	return pItem->ID;
}

void CHBTab::CreateArrowBtn(){
	int iTop = (m_Size.cy-19)/2 - 2;

	m_leftBtn.Create(NULL, WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
		CRect(m_Size.cx-2*15,iTop,15,19), this, 0x334);

	m_leftBtn.LoadBitmaps(IDB_LNORMAL, IDB_LDOWN,IDB_LNORMAL,IDB_LGRAY);
	m_leftBtn.SizeToContent();
	m_leftBtn.ModifyStyle(0,WS_DISABLED);
	m_leftBtn.BringWindowToTop();

	m_rightBtn.Create(NULL, WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
	CRect(m_Size.cx-15,iTop,15,19), this, 0x335);

	m_rightBtn.LoadBitmaps(IDB_RNORMAL, IDB_RDOWN,IDB_RNORMAL,IDB_RGRAY);
	m_rightBtn.SizeToContent();
	m_rightBtn.BringWindowToTop();

}

BOOL CHBTab::Create(CWnd * pParent, DWORD dwStyle, const RECT& rect){
	ClearItemList();

	m_Rect = rect;
	m_Size = CSize(rect.right-rect.left,rect.bottom-rect.top);

	return Create(NULL,"Tab",dwStyle  ,rect,pParent,0x333);
}

BOOL CHBTab::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CHBTab::ClearItemList()
{
	POSITION pos = m_ItemList.GetHeadPosition();
	POSITION firstPos = pos;
	while(pos != 0){
		CExt_TCITEM  * pItem = (CExt_TCITEM  *)m_ItemList.GetNext(pos);
		delete pItem;
	}
	if(firstPos) m_ItemList.RemoveAll();

}
BOOL CHBTab::DestroyWindow()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	ClearItemList();

	return CWnd::DestroyWindow();
}

void CHBTab::AdjustSize(CSize nSize){
	m_Rect.right = m_Rect.left + nSize.cx;
	m_Rect.bottom = m_Rect.top + nSize.cy;
	m_Size = nSize;

	MoveWindow(m_Rect);

}

int CHBTab::GetInsertStartCX(int nIndex){
	int iResult = 0;

	POSITION pos = m_ItemList.GetHeadPosition();
	POSITION firstPos = pos;

	if(!firstPos) return iResult;

	CExt_TCITEM  * pItem;
	int iStep = 0;
	while(pos != 0){
		pItem = (CExt_TCITEM  *)m_ItemList.GetNext(pos);
		if(iStep == nIndex){ break;	}

		iStep++;
	}

	iResult += pItem->pt[2].x;
	iResult += pItem->iBaselineLen;
	//iResult++;
	return iResult;
}

void CHBTab::SetColor(COLORREF nRGB){
	m_Color = nRGB;
	m_bColor = TRUE;

	m_BgColor = NoSelTabColor(m_bColor ? m_Color : ::GetSysColor(COLOR_3DFACE) , 0.5f);

	Invalidate();
}

void CHBTab::SetGradientDraw(BOOL bGradient){
	m_bGradient = bGradient;
}

COLORREF CHBTab::NoSelTabColor(COLORREF crBase, float fFactor)
{
	ASSERT (fFactor < 1.0f && fFactor > 0.0f);

	fFactor = min(fFactor, 1.0f);
	fFactor = max(fFactor, 0.0f);

	BYTE bRed, bBlue, bGreen;
	BYTE bRedShadow, bBlueShadow, bGreenShadow;

	bRed = GetRValue(crBase);
	bBlue = GetBValue(crBase);
	bGreen = GetGValue(crBase);

	bRedShadow = (BYTE)(bRed * fFactor);
	bBlueShadow = (BYTE)(bBlue * fFactor);
	bGreenShadow = (BYTE)(bGreen * fFactor);

	return RGB(bRedShadow, bGreenShadow, bBlueShadow);
}


COLORREF CHBTab::SelTabColor(COLORREF crBase, float fFactor) 
{
	//ASSERT (fFactor > 1.0f);

	fFactor = max(fFactor, 1.0f);

	BYTE bRed, bBlue, bGreen;
	BYTE bRedHilite, bBlueHilite, bGreenHilite;

	bRed = GetRValue(crBase);
	bBlue = GetBValue(crBase);
	bGreen = GetGValue(crBase);

	bRedHilite = (BYTE)min((int)(bRed * fFactor), 255);
	bBlueHilite = (BYTE)min((int)(bBlue * fFactor), 255);
	bGreenHilite = (BYTE)min((int)(bGreen * fFactor), 255);

	return RGB(bRedHilite, bGreenHilite, bBlueHilite);
}

void CHBTab::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	POSITION pos = m_ItemList.GetHeadPosition();
	POSITION firstPos = pos;
	
	CExt_TCITEM  * pItem;
	for(int i=m_iLeftmostTab;i<m_iRightmostTab;i++){
		CExt_TCITEM * pItem = (CExt_TCITEM*)m_ItemList.GetAt(m_ItemList.FindIndex(i));
			CRect r(pItem->pt[3].x-5-15,4,pItem->pt[3].x-5-2,17);
			if (r.PtInRect(point )   )  {
				if(!m_bDrawedBtn){//default=false
					TRACKMOUSEEVENT csTME;
					csTME.cbSize = sizeof(csTME);
					csTME.dwFlags = TME_HOVER | TME_LEAVE;
					csTME.hwndTrack = m_hWnd ;
					csTME.dwHoverTime = 10;
					::_TrackMouseEvent (&csTME);

					m_bDrawedBtn = TRUE;
				}
				m_iFlatSel = i;
				break;
			}
	}
	if(firstPos){
		if(m_ItemList.GetCount() <= m_iFlatSel){
			m_iFlatSel--;
		}
		CExt_TCITEM* pTci = (CExt_TCITEM*)(m_ItemList.GetAt(m_ItemList.FindIndex(m_iFlatSel)));
		if(pTci->pl.PtInRegion(point)){
			CRect r(pTci->pt[3].x-5-15,4,pTci->pt[3].x-5-2,17);
			if (r.PtInRect(point)   )  {
			}
			else{
				TRACE("earse\r\n");
				if(m_bFlag){
					DrawFlatBtn();
					m_bFlag = m_bDrawedBtn = FALSE;//状態値を消す
				}
			}
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}


LRESULT CHBTab::OnMouseLeave(WPARAM wParam, LPARAM lParam){
	DrawFlatBtn();
	m_bFlag = m_bDrawedBtn = FALSE;//状態値を消す
	return 1;
}

LRESULT CHBTab::OnMouseHover(WPARAM wParam, LPARAM lParam){
	if(!m_ItemList.GetCount()) return 0;
	if( m_ItemList.GetCount() <= m_iFlatSel) return 0;
	//if(!m_bDrawedBtn) return 0;

	m_bFlag = TRUE;//トゥルーを設置

	CDC* pDC = GetDC();
	
	CExt_TCITEM* pTci = (CExt_TCITEM*)(m_ItemList.GetAt(m_ItemList.FindIndex(m_iFlatSel)));


	COLORREF bgColor = RGB(175, 25, 48);//button bg color
	CBrush brushBlue(bgColor);
	CBrush* pOldBrush = pDC->SelectObject(&brushBlue);

	//button layout side color 
	//CPen penBlack;
	//penBlack.CreatePen(PS_SOLID, 1,RGB(bgColor));
	//CPen* pOldPen = pDC->SelectObject(&penBlack);
	//丸を描く
	CRect r(pTci->pt[3].x-5-15,4,pTci->pt[3].x-5-2,17);
	pDC->Ellipse(r);
	//×を絵する
	CPen linePen;
	linePen.CreatePen(PS_SOLID, 2,::GetSysColor(COLOR_3DHIGHLIGHT));
	CPen* pOldPen = pDC->SelectObject(&linePen);
	pDC->MoveTo(CPoint(r.left+3,r.top+3));
	pDC->LineTo(CPoint(r.right-4,r.bottom-4));
	pDC->MoveTo(CPoint(r.left+9,r.top+3));
	pDC->LineTo(CPoint(r.right-9,r.bottom-3));
	// put back the old objects
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	return 1;
}


//激しい点滅を避ける為に、この余分見たいメッソッドを作成
int CHBTab::DrawFlatBtn(){
	if(!m_ItemList.GetCount()) return 1;
	if( m_ItemList.GetCount() <= m_iFlatSel) return 2;
	TRACE1("m_iFlatSel: %d;\r\n",m_iFlatSel);
	//if(m_iLeftmostTab>m_iFlatSel || (m_iRightmostTab-1)<m_iFlatSel) return 3;

	CDC * pDC = GetDC();

	CExt_TCITEM* pItem = (CExt_TCITEM*)(m_ItemList.GetAt(m_ItemList.FindIndex(m_iFlatSel)));
	CRect r(pItem->pt[3].x-5-15,4,pItem->pt[3].x-5-2,17);

	CRgn   rgn;
	rgn.CreatePolygonRgn( pItem->pt, pItem->pt_num, ALTERNATE );

	pDC->Polyline(pItem->pt, pItem->pt_num );

	COLORREF crFrom = m_iFlatSel == m_iSel ? SelTabColor(m_Color,1.4f) : NoSelTabColor(m_bColor ? m_Color : ::GetSysColor(COLOR_3DFACE),0.9f);

	COLORREF crTo = m_iFlatSel == m_iSel ? ::GetSysColor(COLOR_3DFACE) : NoSelTabColor(m_bColor ? m_Color : ::GetSysColor(COLOR_3DFACE) , 0.7f);

	int nROrg = GetRValue(crFrom);
	int nGOrg = GetGValue(crFrom);
	int nBOrg = GetBValue(crFrom);
	int nRDiff = GetRValue(crTo) - nROrg;
	int nGDiff = GetGValue(crTo) - nGOrg;
	int nBDiff = GetBValue(crTo) - nBOrg;
	

	DWORD   dwSize = rgn.GetRegionData(0, NULL);
	BYTE* pData=new BYTE[dwSize];

	rgn.GetRegionData((LPRGNDATA)pData,dwSize);
	LPRGNDATA d = (LPRGNDATA)pData;
	CRect * rect = (CRect*)(d->Buffer);
	int nHeight = d->rdh.nCount;
	for(UINT i = 1; i< d->rdh.nCount;i++){
		
		int nRed = nROrg + (i * nRDiff) / nHeight;
		int nGreen = nGOrg + (i * nGDiff) / nHeight;
		int nBlue = nBOrg + (i * nBDiff) / nHeight;
		
		pDC->FillSolidRect((rect+i), RGB(nRed, nGreen, nBlue));
	}
	delete pData;

	//foreground 設置
    pDC->SetBkMode( TRANSPARENT );                          // just text

	LOGFONT logfont;
	memset( &logfont, 0, sizeof( LOGFONT ) );
	GetParent()->GetFont()->GetLogFont(&logfont);
	logfont.lfHeight = 16;
	//_tcscpy(logfont.lfFaceName, _T("ＭＳ ゴシック")); 
	CFont Font;
	Font.CreateFontIndirect(&logfont); 

	CFont* pOldfont = pDC->SelectObject( &Font );                  // select tab font
	//1: 反対色を取得
	COLORREF rgb = m_iFlatSel == m_iSel ? m_Color : m_BgColor;
	int nR = 255 - GetRValue(rgb);
	int nG = 255 - GetGValue(rgb);
	int nB = 255 - GetBValue(rgb);
	rgb = RGB(nR,nG,nB);
	//2: 色着いた場合白色を設置
	//rgb = m_bColor ? RGB(255,255,255) : ::GetSysColor(COLOR_BTNTEXT);
	pDC->SetTextColor(rgb);

	pDC->TextOut( pItem->pt[0].x + 5,pItem->xySize.cy/3-2,pItem->title);
	pDC->SelectObject(pOldfont);

	CPen linePen;
	linePen.CreatePen(PS_SOLID, 2,m_Color-22);
	CPen* pOldPen = pDC->SelectObject(&linePen);
	pDC->SelectObject(&linePen);

	pDC->MoveTo(CPoint(r.left+3,r.top+3));
	pDC->LineTo(CPoint(r.right-4,r.bottom-4));
	pDC->MoveTo(CPoint(r.left+9,r.top+3));
	pDC->LineTo(CPoint(r.right-9,r.bottom-3));
	pDC->SelectObject(pOldPen);

	//一番上に表れるために
	if(pItem->pt[2].x > m_Size.cx-2*15) {
		if(m_leftBtn && m_rightBtn){
				m_leftBtn.Invalidate();
				m_rightBtn.Invalidate();
		}
	}

	//release mem
	linePen.DeleteObject();
	Font.DeleteObject();
	rgn.DeleteObject();

	return 0;
}

void CHBTab::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	POSITION pos = m_ItemList.GetHeadPosition();
	POSITION oldPos = pos;
	CExt_TCITEM  * pExchangeItem = NULL;
	BOOL bFound = FALSE;
	BOOL bSelected = FALSE;
	int iCnt = m_ItemList.GetCount();
	int iStep = 0;
	while(pos != 0){
		oldPos = pos;
		CExt_TCITEM  * pItem = (CExt_TCITEM  *)m_ItemList.GetNext(pos);
		if(pItem->pl.PtInRegion(point)){
			CRect r(pItem->pt[3].x-5-15,3,pItem->pt[3].x-5-2,16);
			if(r.PtInRect(point)){
				
				pExchangeItem = pItem;
				bFound = TRUE;
				bSelected = iStep == m_iSel;
			}
		}
		if(bFound){
			//important data Exchange
			pExchangeItem->title = pItem->title ;
			pExchangeItem = pItem;
			//below is really remove a tab on the tab end
			if(!pos){
				if(iStep && m_Size.cx - 2*15 >= ((CExt_TCITEM*)(m_ItemList.GetAt(m_ItemList.FindIndex(iStep-1))))->pt[2].x && m_leftBtn){
					m_leftBtn.DestroyWindow();
					m_rightBtn.DestroyWindow();
					
					EraseTail();
				}
				EraseTab(*pItem);
				Invalidate();

				m_iRightmostTab--;
				if(m_iSel == (iCnt-1)) m_iSel--;

				m_ItemList.RemoveAt(oldPos);
				delete pItem;
				break;
			}
		}
		iStep++;
	}
	if(iCnt == 1) m_iSel = 0;

	CWnd::OnLButtonUp(nFlags, point);
}

void  CHBTab::EraseTab(CExt_TCITEM & tci){
	CDC * pDC = GetDC();
	CRgn   rgn;
	CBrush defaultBrush;
	defaultBrush.CreateSolidBrush( ::GetSysColor(CTLCOLOR_DLG ) );
	CBrush * oldBrush = pDC->SelectObject(&defaultBrush);
	rgn.CreatePolygonRgn( tci.pt,tci.pt_num, ALTERNATE );
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 1,::GetSysColor(CTLCOLOR_DLG ));
	CPen* pOldPen = pDC->SelectObject(&penBlack);
	pDC->FillRgn(&rgn, &defaultBrush);
	pDC->Polyline(tci.pt, tci.pt_num );

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(oldBrush);
}

//矢印ボタン削除の時に残った跡を消すために
void  CHBTab::EraseTail(){
	CDC * pDC = GetDC();
	CRect   rTail(m_Size.cx-30,0,m_Size.cx,m_Size.cy);
	CBrush defaultBrush;
	defaultBrush.CreateSolidBrush( ::GetSysColor(CTLCOLOR_DLG ) );
	CBrush * oldBrush = pDC->SelectObject(&defaultBrush);
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 1,::GetSysColor(CTLCOLOR_DLG ));
	CPen* pOldPen = pDC->SelectObject(&penBlack);
	pDC->FillRect(&rTail, &defaultBrush);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(oldBrush);
}


void CHBTab::OnBnClickedButtonArrow(UINT nID){
	CString s;
	s.Format("Button Num: %d",(nID));

	switch(nID){
		case 0x334://lelt
			m_iLeftmostTab--;
			m_iRightmostTab--;

			if(m_iLeftmostTab == 0){
				m_leftBtn.EnableWindow(0);
				m_rightBtn.EnableWindow(1);
				m_iRightmostTab++;
			}
			else{
				//m_leftBtn.ModifyStyle(WS_DISABLED,0 ); 
			}
			MoveItems(0);

			break;
		case 0x335://right
			m_iLeftmostTab++;
			m_iRightmostTab++;

			if(m_iRightmostTab > m_ItemList.GetCount()){
				m_rightBtn.EnableWindow(0);
				m_leftBtn.EnableWindow(1);

				m_iRightmostTab--;
				//EraseTail();

			}
			else{
				//m_rightBtn.ModifyStyle(WS_DISABLED,0 ); 
			}
			MoveItems();

			break;
	}
	Invalidate();
}

void CHBTab::MoveItems(BOOL bLeft){
	int iStep = 0;
	for(int i=m_iLeftmostTab;i<m_iRightmostTab;i++){
		CExt_TCITEM * pItem = (CExt_TCITEM*)m_ItemList.GetAt(m_ItemList.FindIndex(i));
		
		//if(pItem->pt[3].x  >= m_Size.cx ){
		//	break;
		//}

		pItem->CreatePolyon(!iStep ? 0 : GetInsertStartCX(i-1), 0);

		iStep++;
	}
}


void CHBTab::SetBaselineLen(int nItem, int iLen){
	POSITION pos = m_ItemList.GetHeadPosition();
	POSITION oldPos = pos;
	int iStep = 0;
	while(pos != 0){
		oldPos = pos;
		CExt_TCITEM  * pItem = (CExt_TCITEM  *)m_ItemList.GetNext(pos);
		
		if(pItem->ID == nItem){
			pItem->iBaselineLen = iLen;
		}
	}
}