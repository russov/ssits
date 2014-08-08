
// fontGeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fontGenerator.h"
#include "fontGeneratorDlg.h"
#include "Cycle.h"
#include "afxdialogex.h"

#include <stdio.h>
#include <cstring>

#define count_column 27
#define count_row 17

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const unsigned char sequenceIn[] = "���������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������";	


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
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
//	DDX_Control(pDX, ;
}

BEGIN_MESSAGE_MAP(CfontGeneratorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CfontGeneratorDlg::OnBnClickedOk)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
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

void CfontGeneratorDlg::SetColorBallons(const unsigned char *sequenceIn)
{
	CString result;
	result.Format("%d", clock());
	OutputDebugString(result + CString("\n"));
 
	int row = 0;
	int column = 0;

	RECT dialog_Rect;
	this->GetClientRect(&dialog_Rect);

	CClientDC dc(this);

	if ( !bMemDCEnabled )
	{
		b.CreateCompatibleBitmap( &dc, dialog_Rect.right, dialog_Rect.bottom);
		memDC.CreateCompatibleDC( &dc ) ;
		bMemDCEnabled = TRUE;
	}

	memDC.SelectObject( &b );

	CBrush brush ( RGB(255,255,255) );
	memDC.FillRect( &dialog_Rect, &brush);

	int lenght_Balloon = dialog_Rect.right / count_column;
	int current_Y = dialog_Rect.bottom  - lenght_Balloon - lenght_Balloon;
	int current_X = dialog_Rect.left;

	for (int i = 0; i < 1338; i += 3)
	{
		long lRGB = RGB(sequenceIn[i], sequenceIn[i+1], sequenceIn[i+2]);
		
		CRect rect(current_X, current_Y, current_X + lenght_Balloon, current_Y + lenght_Balloon);
		
		if (column%2 == 0)
			current_Y -= lenght_Balloon;
		else
			current_Y += lenght_Balloon;
			
		HBRUSH hBrush = CreateSolidBrush(lRGB);
		memDC.SelectObject(hBrush);
		memDC.Ellipse(&rect);

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
		DeleteObject(hBrush);
	}
	dc.BitBlt(0, 0, dialog_Rect.right, dialog_Rect.bottom,
           &memDC,
           0, 0,
           SRCCOPY);

	CString result1;
	result1.Format("%d", clock());

	OutputDebugString(result1 + CString("-END") + CString("\n"));
}

void CfontGeneratorDlg::OnBnClickedOk()
{
	//SetColorBallons(sequenceIn);

	RECT dialog_Rect;
	this->GetClientRect(&dialog_Rect);

	CClientDC dc(this);

	b.CreateCompatibleBitmap( &dc, dialog_Rect.right, dialog_Rect.bottom);
	memDC.CreateCompatibleDC( &dc ) ;
	
	//bMemDCEnabled = TRUE;
	

	memDC.SelectObject( &b );

	//CBrush brush ( RGB(255,255,255) );
	//memDC.FillRect( &dialog_Rect, &brush);

	Cycle *cycle = new Cycle(0,25,50,memDC,dc,dialog_Rect, this);



	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}





void CfontGeneratorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnLButtonDown(nFlags, point);
}