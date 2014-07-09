
// generatorDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include <string>
#include <vector> 

#include "../../CommonData.h"
#include "afxcolorbutton.h"

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
	void create_Image(int shift = 0);
	void create_Image_To_Send(unsigned char *sequence, int shift = 0);
	BOOL send_DataUDP(struct send_Data data);

	std::vector <std::string> m_Storage_Screen_Point;
	int current_Size_Screen;

protected:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

	CEdit m_Speed;
	CEdit m_Shift;
	CEdit m_Not_Found_Symbols;
	CButton m_Stop;
	
	CMFCColorButton m_Background_Color;
	CMFCColorButton m_Symbols_Color;
	CEdit m_Incoming_Sequence;
};
