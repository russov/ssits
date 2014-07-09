
// emulatorDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "resource.h"

#include <vector>


// CemulatorDlg dialog
class CemulatorDlg : public CDialogEx
{
// Construction
public:
	CemulatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EMULATOR_DIALOG };

	void SetColorBallons(const unsigned char *sequence);

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
	//void OnTimer(UINT nIDEvent);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


	std::vector<CEdit *> edit_Vector;

	void ClearScreen();

	static UINT receive_Data(LPVOID param);
	bool write_file(const CString &text);

	bool bMemDCEnabled;
	CDC memDC;
	CBitmap b;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	CButton m_Button1;
	CEdit m_Edit1;
	CEdit m_PathDirectory;
};
