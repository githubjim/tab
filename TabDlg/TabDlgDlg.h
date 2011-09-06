// TabDlgDlg.h : ヘッダー ファイル
//

#pragma once

#include "HBTab.h"


// CTabDlgDlg ダイアログ
class CTabDlgDlg : public CDialog
{
// コンストラクション
public:
	CTabDlgDlg(CWnd* pParent = NULL);	// 標準コンストラクタ
	~CTabDlgDlg();	// 標準コンストラクタ

// ダイアログ データ
	enum { IDD = IDD_TABDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート
public:
	void DrawTab(int iItem);
	void DrawCircle(int iRadius);
public:
	int m_iSelect;
	CHBTab m_ctlTab;
	CBitmapButton lButton;
	CBitmapButton rButton;

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButtonArrow(UINT nID);
};
