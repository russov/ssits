
// fontGeneratorDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "vector"

#include "Cycle.h"

class CfontGeneratorDlg : public CDialogEx
{
public:
	CfontGeneratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FONTGENERATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	void clearFromVector();
	void clearScreen();
	bool saveSequenceToFile();

	DECLARE_MESSAGE_MAP()

	bool bMemDCEnabled;
	CDC memDC;
	CBitmap b;

	std::vector <Cycle *> cycleVec;
		
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonClear();
	CEdit m_SymbolName;
};
