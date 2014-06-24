
// generatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "generator.h"
#include "generatorDlg.h"
#include "afxdialogex.h"

#include <fstream>
#include <istream>
#include <iostream>
#include <string>


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


// CgeneratorDlg dialog




CgeneratorDlg::CgeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CgeneratorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgeneratorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CgeneratorDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CgeneratorDlg message handlers

BOOL CgeneratorDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CgeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CgeneratorDlg::OnPaint()
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
HCURSOR CgeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CgeneratorDlg::OnBnClickedButton1()
{
	int my = 0;

	TCHAR	szBuffer[10000] = {0}; 
	UINT    nActual = 0; 
	//CFile	myFile;

	std::ifstream in;

	in.open(CString( _T("..\\symbols\\1.txt")));

	CString temp;

	char f = '0';

	CString backGroundColor = CString("RGB(0,0,0)");
	CString symbolColor = CString("RGB(255,255,255)");

	int column_number = 0;
	int row_count = 0;
	while (f != EOF)
	{
		f = in.get();

		if (f == '\n')
		{
			for (int i = column_number; i < count_column; ++i)
				write_file(backGroundColor);
			if (row_count%2)
				column_number = 1;
			else
				column_number = 0;
			++row_count;
		}
		else if (f == '0')
		{
			write_file(backGroundColor);
			++column_number;
		}
		else if (f == '1')
		{
			write_file(symbolColor);
			++column_number;
			
		}

		


	//while( std::getline(in, temp))
    {                         
       /* char symbol;
        char *s;
        in.get(symbol);
        in.get(symbol1);

        if(symbol != ' ' && (!(symbol1 >= '�' && symbol1 <= '�') ) && symbol!='\n' && symbol1!='\n')
        {
            temp1 = temp1+temp;
            temp1.push_back('.');
            temp1.push_back(symbol);
            temp1.push_back(symbol1);

            continue;
        }
        else
        {
            temp1 = temp1+temp;
            temp1.push_back('.');
            return temp1;
        }*/
    }
	}


	in.close();


	/*
	if ( myFile.Open( _T("..\\symbols\\1.txt"), CFile::modeRead ))
	{
	    myFile.Seek( 0, CFile::begin );
	    
		get

		nActual = myFile.Read(szBuffer, sizeof(szBuffer)); 
	}*/
	// TODO: Add your control notification handler code here
}

bool CgeneratorDlg::write_file(const CString &text)
{
    CString NameFile = CString("../../emulator/inbox/log_out.txt");
    std::ofstream os;
	os.open(NameFile, std::ios::app);
    if(!os )
    {
        printf("File not found");
        return(0);
    }

	CString h = CString("123");

    CT2CA pszConvertedAnsiString (text);
 
    std::string strStd (pszConvertedAnsiString);

    os << strStd.substr(0,strStd.size()) << std::endl;
    os.close();
}