
// generatorDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include <string>
#include <vector> 

// CgeneratorDlg dialog
class CgeneratorDlg : public CDialogEx
{
// Construction
public:
	CgeneratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GENERATOR_DIALOG };

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

	bool write_file(const CString &text);
	void add_Blank_Screen_Begin();
	void add_Blank_Screen_End();
	void fill_Useful_Data_Screen();
	void create_Image();

	std::vector <std::string> m_Storage_Screen_Point;
	int current_Size_Screen;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	CEdit m_Speed;
};
