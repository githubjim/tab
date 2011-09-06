// TabDlg.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CTabDlgApp:
// このクラスの実装については、TabDlg.cpp を参照してください。
//

class CTabDlgApp : public CWinApp
{
public:
	CTabDlgApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CTabDlgApp theApp;