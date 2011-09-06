// TabDlgDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once

#include "HBTab.h"


// CTabDlgDlg �_�C�A���O
class CTabDlgDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CTabDlgDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^
	~CTabDlgDlg();	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_TABDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g
public:
	void DrawTab(int iItem);
	void DrawCircle(int iRadius);
public:
	int m_iSelect;
	CHBTab m_ctlTab;
	CBitmapButton lButton;
	CBitmapButton rButton;

// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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
