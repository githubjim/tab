// TabDlgDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "TabDlg.h"
#include "TabDlgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTabDlgDlg ダイアログ




CTabDlgDlg::CTabDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabDlgDlg::IDD, pParent)
{
	m_iSelect = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CTabDlgDlg::~CTabDlgDlg()
{
	m_ctlTab.DestroyWindow();
}

void CTabDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTabDlgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTabDlgDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTabDlgDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTabDlgDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTabDlgDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTabDlgDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTabDlgDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTabDlgDlg::OnBnClickedButton6)
	ON_COMMAND_RANGE(0x334, 0x335, &CTabDlgDlg::OnBnClickedButtonArrow)
END_MESSAGE_MAP()


// CTabDlgDlg メッセージ ハンドラ

BOOL CTabDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	//((CTabCtrl*)GetDlgItem(IDC_TAB1))->InsertItem(0, "Tab 1", 0);
	//((CTabCtrl*)GetDlgItem(IDC_TAB1))->InsertItem(1, "Tab 2", 0);
	//((CTabCtrl*)GetDlgItem(IDC_TAB1))->InsertItem(2, "Tab 3", 0);

	//m_ctlTab.Create(NULL,"Tab",WS_VISIBLE|WS_BORDER|WS_CHILD  ,CRect(0,0,300,50),this,0x333);
	
	m_ctlTab.Create(this,WS_VISIBLE|WS_BORDER|WS_CHILD|BS_PUSHBUTTON  ,CRect(10,10,500,50));


	// Create the bitmap button (must include the BS_OWNERDRAW style).
	lButton.Create(NULL, WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
	   CRect(10,80,25,99), this, 0x334);

	lButton.LoadBitmaps(IDB_LNORMAL, IDB_LDOWN,IDB_LNORMAL,IDB_LGRAY);
	lButton.SizeToContent();

	rButton.Create(NULL, WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
	CRect(25,80,40,99), this, 0x335);

	rButton.LoadBitmaps(IDB_RNORMAL, IDB_RDOWN,IDB_RNORMAL,IDB_RGRAY);
	rButton.SizeToContent();

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CTabDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CTabDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	for(int uTabIndex = 0; uTabIndex < ((CTabCtrl*)GetDlgItem(IDC_TAB1))->GetItemCount(); uTabIndex++ )//(UINT)this->GetItemCount()
   {
		DrawTab(uTabIndex);
   }
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CTabDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTabDlgDlg::DrawTab(int iItem)
{
	TC_ITEM     tci;
	CDC* pDC = this->GetDC();//CDC::FromHandle(lpdis->hDC);
	HIMAGELIST hilTabs = (HIMAGELIST)TabCtrl_GetImageList(GetSafeHwnd());

	CString sTemp;
	tci.mask        = TCIF_TEXT | TCIF_IMAGE;
	tci.pszText     = sTemp.GetBuffer(100);
	tci.cchTextMax  = 99;
//	this->SetItemSize(CSize(22,84));
	((CTabCtrl*)GetDlgItem(IDC_TAB1))->GetItem(iItem, &tci);
	sTemp.ReleaseBuffer();
	int iTag = iItem;

   POINT ppoint[20];          // points that will be used to draw tab                                                                   

   UINT  uTabHeight = 15;         // the tab height 
   UINT  uDistanceToNextTab = 7; // distance between tabs
   int   iOffsetToLeft = 20 + iTag * 84 ;      // distance from left side of client edge   

   CFont *pFont = (CFont*)this->GetFont();
	LOGFONT LogFont;
	pFont->GetLogFont(&LogFont);
	//strcpy(LogFont.lfFaceName , "ＭＳ ゴシック");
	LogFont.lfWidth = 9;
	LogFont.lfWeight = FW_NORMAL;

	HFONT hfont = ::CreateFontIndirect(&LogFont); 
	CFont* pfont = CFont::FromHandle(hfont);
	CFont* oldFont = pDC->SelectObject(pfont);

   
   //CPen     penBlack( PS_SOLID, 1, RGB(0,0,0) );
  
   //CPen*    ppenOld;


   //ppenOld = pDC->SelectObject( &penBlack );               // select a black pen

   pDC->SetBkMode( TRANSPARENT );                          // just text

   // ***
      // set all points for tab, then we will be able to draw it
      // ***
	  int num_of_points = 6;
      
	  ppoint[0].x = iOffsetToLeft;                         // ""
      ppoint[0].y = 0;
	  int init_x = iOffsetToLeft;
	  int init_y = 0;
	  //ppoint[5].x = iOffsetToLeft;   // ""
	  //ppoint[5].y = 0;

	  
      //iOffsetToLeft -= uDistanceToNextTab;                 // "/" 
      ppoint[1].x   =  iOffsetToLeft - uDistanceToNextTab;
      ppoint[1].y   =  uTabHeight / 2;	  
	  
	  ppoint[2].x   =  iOffsetToLeft - uDistanceToNextTab;
      ppoint[2].y   =  uTabHeight;
	  /*if(uTabIndex == m_uSelectedViewIndex)
	  {
		  ppoint[2].x   =  iOffsetToLeft - 2 * uDistanceToNextTab;
	  }	*/  
      //draw tab-text 
      pDC->TextOut( ppoint[0].x + 3,         
                    1,
                    tci.pszText );

      iOffsetToLeft += 84;       // "____"
      
	  ppoint[3].x   =  iOffsetToLeft + uDistanceToNextTab;
      ppoint[3].y   =  uTabHeight;

      if( iTag == (UINT)( ((CTabCtrl*)GetDlgItem(IDC_TAB1))->GetItemCount() - 1) ) // "\____/"
      {
         iOffsetToLeft += uDistanceToNextTab;
         ppoint[4].x   =  iOffsetToLeft;
         ppoint[4].y   =  0;	
		 
		 ppoint[5].x   =  init_x;
         ppoint[5].y   =  init_y;	
		 num_of_points = 6;

		 //iOffsetToLeft += (uDistanceToNextTab);
   //      
		 //ppoint[6].x   =  iOffsetToLeft;
   //      ppoint[6].y   =  0;
		 //
		 //ppoint[7].x = init_x;
		 //ppoint[7].y = init_y;		 
		 //num_of_points = 8;
	  }
      else
	  {
         
		 ppoint[4].x   =  iOffsetToLeft;
         ppoint[4].y   =  uTabHeight;
		 ppoint[5].x   =  iOffsetToLeft;
         ppoint[5].y   =  uTabHeight / 2;
		 
		 iOffsetToLeft += (uDistanceToNextTab);
         
		 ppoint[6].x   =  iOffsetToLeft;
         ppoint[6].y   =  0;
		 
		 ppoint[7].x = init_x;
		 ppoint[7].y = init_y;		 
		 num_of_points = 8;
         //iOffsetToLeft -= (uDistanceToNextTab / 2);		 
		 //iOffsetToLeft += uDistanceToNextTab;		 
      }
	  
		CRgn   rgn;
		CBrush brush;
		brush.CreateSolidBrush( ::GetSysColor( iTag != m_iSelect ? COLOR_BTNFACE : COLOR_WINDOW ) );
		rgn.CreatePolygonRgn( ppoint, num_of_points, ALTERNATE );	  	  
        CBrush * oldBrush = pDC->SelectObject(&brush);

		//DWORD   dwSize = rgn.GetRegionData(0, NULL);
		//BYTE* pData=new BYTE[dwSize];

		//rgn.GetRegionData((LPRGNDATA)pData,dwSize);//(LPRGNDATA)pData
		//LPRGNDATA d;
		//d =  (LPRGNDATA)pData ;
		//CRect * rect = (CRect*)(d->Buffer);
		//for(UINT i = 0; i< d->rdh.nCount;i++){
		//	CRect r = *(rect);

		//	TRACE1("%d,",r.left);
		//	TRACE1("%d,",r.top);
		//	TRACE1("%d,",r.right);
		//	TRACE1("%d;\r\n",r.bottom);

		//	rect++;
		//}
		//delete pData;

      CPen pen;
	  pen.CreatePen(PS_SOLID,5,RGB(128,128,0));
	  CPen * oldPen = pDC->SelectObject(&pen);
	  pDC->FillRgn( &rgn, &brush );
	  pDC->TextOut( ppoint[0].x + 3,1,tci.pszText);
	
      pDC->Polyline( ppoint, num_of_points );

	TRACE1("sel:%d; \r\n",m_iSelect);

	pDC->SelectObject(oldPen);

	pDC->SelectObject(oldFont);
	::DeleteObject(hfont);

   pDC->SelectObject( oldBrush );
}


void CTabDlgDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	*pResult = 0;

	m_iSelect = ((CTabCtrl*)GetDlgItem(IDC_TAB1))->GetCurSel( );

	for(int uTabIndex = 0; uTabIndex < ((CTabCtrl*)GetDlgItem(IDC_TAB1))->GetItemCount(); uTabIndex++ )
   {
		DrawTab(uTabIndex);
   }
}

void CTabDlgDlg::OnBnClickedButton1()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。

	CString strTabTitle;
	strTabTitle.Format("タブ %d",m_ctlTab.m_iTabMaxNum);
	int nIndex = m_ctlTab.InsertItem(strTabTitle);
	m_ctlTab.SetBaselineLen(nIndex, 30*nIndex);
	m_ctlTab.Invalidate();
}

void CTabDlgDlg::OnBnClickedButton2()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	m_ctlTab.AdjustSize(CSize(500,27));
}

void CTabDlgDlg::OnBnClickedButton3()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	CColorDialog dlg;
	dlg.DoModal();
	
	m_ctlTab.SetColor(dlg.GetColor());
}

void CTabDlgDlg::OnBnClickedButton4()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	//for(;i<15;){
		DrawCircle(0);
	//}
}

void CTabDlgDlg::DrawCircle(int iRadius){
	CDC* pDC = GetDC();
	CPoint p(80,50);

	// create and select a solid blue brush
	CBrush brushBlue(RGB(175, 25, 48));
	CBrush* pOldBrush = pDC->SelectObject(&brushBlue);

	// create and select a thick, black pen
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 1,RGB(175, 25, 48)/*RGB(0, 0, 0)*/);
	CPen* pOldPen = pDC->SelectObject(&penBlack);
	CRect r(50,140,63,153);
	pDC->Ellipse(r);

	CPen linePen;
	linePen.CreatePen(PS_SOLID, 2,::GetSysColor(COLOR_3DHIGHLIGHT));
	pDC->SelectObject(&linePen);
	pDC->MoveTo(CPoint(r.left+3,r.top+3));
	pDC->LineTo(CPoint(r.right-4,r.bottom-4));
	pDC->MoveTo(CPoint(r.left+9,r.top+3));
	pDC->LineTo(CPoint(r.right-9,r.bottom-3));
	// put back the old objects
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}
void CTabDlgDlg::OnBnClickedButton5()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
		CDC * pDC = GetDC();
		
		POINT pt[9] = {{17,36},{0,70},{149,70},{132,36},{17,36}};
		//CRect rect(pt[1].x,pt[0].y,pt[2].x,pt[2].y);
		CRgn   rgn;
		//CBrush brush;
		//brush.CreateSolidBrush( ::GetSysColor( i == m_iSel ? COLOR_3DHIGHLIGHT : COLOR_3DFACE ) );
		rgn.CreatePolygonRgn( pt, 5, ALTERNATE );
		//pDC->FillRgn( &rgn, &brush );

		//pDC->Polyline(tci.pt, tci.pt_num );

		
		CDC dcMem;
		CBitmap Bitmap;
		dcMem.CreateCompatibleDC(pDC);
		Bitmap.CreateCompatibleBitmap(pDC,59,23);
		CBitmap * pOldBmp=dcMem.SelectObject(&Bitmap); 
		//CBrush defaultBrush;
		//defaultBrush.CreateSolidBrush( ::GetSysColor(CTLCOLOR_DLG ) );
		//CBrush * oldBrush = dcMem.SelectObject(&defaultBrush);
		//int r1=128,g1=200,b1=200;
		//int r2=100,  g2=55, b2=165;
		COLORREF crFrom = RGB(255,0,100);
		COLORREF crTo = RGB(240,23,80);
 		int r1 = GetRValue(crFrom);
		int g1 = GetGValue(crFrom);
		int b1 = GetBValue(crFrom);
		int r2 = GetRValue(crTo) - r1;
		int g2 = GetGValue(crTo) - g1;
		int b2 = GetBValue(crTo) - b1;

		DWORD   dwSize = rgn.GetRegionData(0, NULL);
		BYTE* pData=new BYTE[dwSize];
 		rgn.GetRegionData((LPRGNDATA)pData,dwSize);
		LPRGNDATA d = (LPRGNDATA)pData;
		CRect * rect = (CRect*)(d->Buffer);
		int nHeight = d->rdh.nCount;
		//CPen penBlack;
		//penBlack.CreatePen(PS_SOLID, 1,crFrom/*RGB(0, 0, 0)*/);
		//CPen* pOldPen = pDC->SelectObject(&penBlack);
		for(int i=0;i<d->rdh.nCount;i++){
			int r,g,b;
			r = r1 + (i * (r2-r1) / nHeight);
			g = g1 + (i * (g2-g1) / nHeight);
			b = b1 + (i * (b2-b1) / nHeight);

			CRect aRect = rect+i;
			CRect sr(0,i,148,i+1);//②：0,i,rect.Width(),1
			TRACE3("left:%d,top:%d,right:%d,",sr.left,sr.top,sr.right);
			TRACE1("bottom:%d\r\n",sr.bottom);
			dcMem.FillSolidRect(sr,RGB(r,g,b));
	
			pDC->FillSolidRect(aRect, RGB(r,g,b));
			//if(i<12)
			//{
			//pDC->BitBlt(aRect.left,aRect.top,aRect.Width(),aRect.Height(),&dcMem,0,i,SRCCOPY);
			//}
			//pDC->StretchBlt(aRect.left,aRect.top,aRect.Width(),aRect.Height(),&dcMem,0,i,sr.Width(),sr.Height(),WHITENESS                                             );
		}
		//pDC->BitBlt(10,80,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);

		Bitmap.DeleteObject();
		//dcMem.SelectObject(pOldPen);
		dcMem.SelectObject(pOldBmp);
		dcMem.DeleteDC();


	//CRect rect(10,10,180,60);
	//
	//CDC dcBAK;
 //   CBitmap map;
 //   dcBAK.CreateCompatibleDC(pDC);
 //   map.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
 //   CBitmap * poldbmp=dcBAK.SelectObject(&map); 
 //   int r1=128,g1=200,b1=200;
 //   int r2=100,  g2=55, b2=165;
	//for(int i=0;i <rect.Height();i++){
 //       int r,g,b;
 //       r = r1 + (i * (r2-r1) / rect.Height());
 //       g = g1 + (i * (g2-g1) / rect.Height());
 //       b = b1 + (i * (b2-b1) / rect.Height());
	//	CRect sr(0,i,rect.Width(),i+1);//②：0,i,rect.Width(),1
	//	dcBAK.FillSolidRect(&sr,RGB(r,g,b));//
	//	
	//	pDC->BitBlt(10,80+i,sr.Width(),1,&dcBAK,0,i,SRCCOPY);
 //   }
	////pDC->BitBlt(10,80,rect.Width(),rect.Height(),&dcBAK,0,0,SRCCOPY);

	//map.DeleteObject();
 //   dcBAK.SelectObject(poldbmp);
	//dcBAK.DeleteDC();

}

void CTabDlgDlg::OnBnClickedButton6()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	//DWORD dStyle = rButton.GetStyle();
	//if(dStyle &= WS_DISABLED){
	//	rButton.ModifyStyle(WS_DISABLED,0 ); 
	//}
	//else{
	//	rButton.ModifyStyle(0,WS_DISABLED ); 
	//}
	//rButton.Invalidate();

	CRect rTail(460,8 ,460,19  );
	CPoint point(466 ,17);
	if(rTail.PtInRect(point)) {
		MessageBox("あたる");
	}
}


void CTabDlgDlg::OnBnClickedButtonArrow(UINT nID){
	CString s;
	s.Format("Button Num: %d",(nID));
	this->GetDlgItem(IDC_STATIC)->SetWindowTextA(s);
	//MessageBox(s);


	switch(nID){
		case 0x334:
			rButton.ModifyStyle(WS_DISABLED,0 ); 
			lButton.ModifyStyle(0,WS_DISABLED ); 
			lButton.EnableWindow(0);
			//rButton.EnableWindow(1);
			rButton.Invalidate();
			lButton.Invalidate();
			break;
		case 0x335:
			lButton.ModifyStyle(WS_DISABLED,0 ); 
			rButton.ModifyStyle(0,WS_DISABLED ); 
			//lButton.EnableWindow(1);
			rButton.EnableWindow(0);
			rButton.Invalidate();
			lButton.Invalidate();
			break;
	}
	//DWORD dStyle = rButton.GetStyle();
	//if(dStyle &= WS_DISABLED){
	//	rButton.ModifyStyle(WS_DISABLED,0 ); 
	//}
	//else{
	//	rButton.ModifyStyle(0,WS_DISABLED ); 
	//}
	//rButton.Invalidate();
}
