
// fontGeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fontGenerator.h"
#include "fontGeneratorDlg.h"
#include "afxdialogex.h"

#include <stdio.h>
#include <cstring>

#include <string>
#include <fstream>
#include <istream>
#include <iostream>
#include <algorithm>

#define count_column 27
#define count_row 17

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CfontGeneratorDlg dialog

CfontGeneratorDlg::CfontGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CfontGeneratorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfontGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//	DDX_Control(pDX, ;
	DDX_Control(pDX, IDC_EDIT_Symbol_Name, m_SymbolName);
}

BEGIN_MESSAGE_MAP(CfontGeneratorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CfontGeneratorDlg::OnBnClickedOk)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CfontGeneratorDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CfontGeneratorDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CfontGeneratorDlg message handlers

BOOL CfontGeneratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	bMemDCEnabled = FALSE;

	m_SymbolName.SetWindowTextA("");
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CfontGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CfontGeneratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CfontGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CfontGeneratorDlg::clearFromVector()
{
	std::vector < Cycle * >::iterator it;
	for( it = cycleVec.begin(); it != cycleVec.end(); )
	{
		delete *it;
		it = cycleVec.erase(it);
	} 
}

void CfontGeneratorDlg::clearScreen()
{
	RECT dialog_Rect;
	this->GetClientRect(&dialog_Rect);

	CClientDC dc(this);

	if (!bMemDCEnabled)
	{
		b.CreateCompatibleBitmap(&dc, dialog_Rect.right, dialog_Rect.bottom);
		memDC.CreateCompatibleDC(&dc) ;
		bMemDCEnabled = TRUE;
	}

	memDC.SelectObject( &b );

	CBrush brush ( RGB(255,0,255) );
	memDC.SelectObject(&brush);
	memDC.FillRect( &dialog_Rect, &brush);
	Invalidate();
}

bool isEqual(Cycle *c)
{
	return c->isClickedItem() ? true : false;
}

bool CfontGeneratorDlg::saveSequenceToFile()
{
	CString symbol;
	m_SymbolName.GetWindowTextA(symbol);

	CString rezultText;
	
	std::string NameFile("symbols/" + symbol);
    std::ofstream os;

	os.open(NameFile, std::ios::app);
    if(!os )
    {
        printf("File not found");
        return(0);
    }

	int row = count_row;
	int column = 0;
	int item = 0;

	std::vector < Cycle * >::iterator lastSymbolIt = cycleVec.end();
	std::vector < Cycle * >::iterator it = std::find_if(cycleVec.begin(), cycleVec.end(), isEqual);

	while (it != cycleVec.end())
	{
		lastSymbolIt = it;
		it = std::find_if(++it, cycleVec.end(), isEqual);
	}

	int position = 0;
	if (lastSymbolIt != cycleVec.end())
		position = (lastSymbolIt - cycleVec.begin()) / (count_row * 2 - 1) + 1;
	
	for (int row = 0; row < count_row; ++row)
	{
		for (int column = 0; column < position * 2; ++column)
		{
			if(column%2) // не четная
			{
				if (row == 0)
				{
					rezultText.AppendChar(' ');
					continue;
				}
				else
					item = row - 1 + ((count_row * column) - column / 2);
			}
			else //четная
			{
				item = (count_row - row - 1) + ((count_row * column) - column / 2);
			}
			rezultText.AppendChar(cycleVec[item]->isClickedItem() ? '1' : '0');
		}
		rezultText.AppendChar('\n');
	}

	CT2CA pszConvertedAnsiString (rezultText);
 
    std::string strStd (pszConvertedAnsiString);

    os << strStd.substr(0, strStd.size()) << std::endl;
    os.close();
	
	return true;
}

void CfontGeneratorDlg::OnBnClickedOk()
{
	clearScreen();

	RECT dialog_Rect;
	this->GetClientRect(&dialog_Rect);

	int row = 0;
	int column = 0;
	int lenght_Balloon = dialog_Rect.right / count_column;
	int current_Y = dialog_Rect.bottom  - lenght_Balloon - lenght_Balloon;
	int current_X = dialog_Rect.left;

	for (int i = 0; i < 1338; i += 3)
	{		
		cycleVec.push_back(new Cycle(current_X,current_Y,lenght_Balloon, this));

		if (column%2 == 0)
			current_Y -= lenght_Balloon;
		else
			current_Y += lenght_Balloon;
		
		++row;
		
		if (row >= count_row || (column%2 && (row+1) == count_row))
		{			
			row = 0;
			current_X += lenght_Balloon;

			if (column%2 == 0)
				current_Y += lenght_Balloon + lenght_Balloon / 2;	
			else
				current_Y -= lenght_Balloon / 2;
			++column;
		}
	}
}

void CfontGeneratorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CfontGeneratorDlg::OnBnClickedButtonSave()
{
	saveSequenceToFile();
}

void CfontGeneratorDlg::OnBnClickedButtonClear()
{
	clearFromVector();
	clearScreen();
}
