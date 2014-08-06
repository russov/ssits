
// fontGeneratorDlg.h : header file
//

#pragma once


// CfontGeneratorDlg dialog
class CfontGeneratorDlg : public CDialogEx
{
// Construction
public:
	CfontGeneratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FONTGENERATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	bool bMemDCEnabled;
	CDC memDC;
	CBitmap b;

	void SetColorBallons(const unsigned char *sequenceIn);
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
