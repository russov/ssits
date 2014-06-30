
// generatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "generator.h"
#include "generatorDlg.h"
#include "afxdialogex.h"

#include <fstream>
#include <istream>
#include <iostream>

//#include <list>


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
	DDX_Control(pDX, IDC_EDIT1, m_Speed);
}

BEGIN_MESSAGE_MAP(CgeneratorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CgeneratorDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CgeneratorDlg::OnEnChangeEdit1)
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

	m_Speed.SetWindowTextW(CString("10"));

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

void CgeneratorDlg::add_Blank_Screen_Begin()
{
	for (int i = 0; i != m_Storage_Screen_Point.size(); ++i)
		for (int ii = 0; ii < count_column; ++ii)
			m_Storage_Screen_Point[i].insert(m_Storage_Screen_Point[i].begin(), '0');
}

void CgeneratorDlg::add_Blank_Screen_End()
{
	for (int i = 0; i != m_Storage_Screen_Point.size(); ++i)
	{
		for (int ii = 0; ii < count_column; ++ii)
		{
			if(i == 0 && (m_Storage_Screen_Point[i].size()-1)%2 == 0 && *(m_Storage_Screen_Point[0].end()-1) != ' ')
				m_Storage_Screen_Point[i].push_back(' ');
			else
				m_Storage_Screen_Point[i].push_back('0');
		}
	}
}

void CgeneratorDlg::fill_Useful_Data_Screen()
{
//int my = 0;

	//TCHAR	szBuffer[10000] = {0}; 
	//UINT    nActual = 0; 
	//CFile	myFile;

	/*std::vector<bool> keep_Point_Screen;
	std::list<bool> keep_Point_Screen_Not_Even_Columns;
	std::list<bool> keep_Point_Screen_Even_Columns;

	std::vector <std::string> storage_Screen_Point;
	*/
	

	std::string incoming_Sequence = "111";

	for (int i = 0; i < incoming_Sequence.size(); ++i)
	{
		std::ifstream in;
		in.open(CString(CString("..\\symbols\\") + CString(incoming_Sequence[i]) + CString(".txt")));

		//CString temp;

		//char symbol = '0';

		//CString backGroundColor = CString("RGB(0,0,0)");
		//CString symbolColor = CString("RGB(255,255,255)");
		
		//int column_number = 0;
		//int row_count = 0;
	
		
		char row[256] = {0};
	
		int size_Letter = 0;
		int current_row = 0;
		while (!in.eof())
		{
			in.getline(row, 256);
			std::string row_Letter(row);
			if (!current_row)
				size_Letter = row_Letter.size();

			if (size_Letter != row_Letter.size())
				return;

			if (m_Storage_Screen_Point.size() > current_row)
			{
				std::vector <std::string>::iterator iter;

				m_Storage_Screen_Point[current_row].append(row_Letter);
			} else
			{
				m_Storage_Screen_Point.push_back(row_Letter);
			}
			++current_row;
		}

		in.close();
	}
	/*
	while (f != EOF)
	{
		std::list<bool>::iterator it;

		f = in.get();

		if (column_number%2) // not even column
		{
			it = keep_Point_Screen_Not_Even_Columns.begin() +  m kbm9,hkl 

			if (f == '0' || f == '1')
				keep_Point_Screen_Even_Columns.insert(0, f);
		} else
		{
		
		}

		if (f == '\n' || f == EOF)
		{
		}
	}
	*/
	/*
	int column_number = 0;
	int row_count = 0;
	while (f != EOF)
	{
		f = in.get();

		if (f == '\n' || f == EOF)
		{
			for (int i = column_number; i < ((row_count%2 == 1)?(count_column-1):count_column); ++i)
				write_file(backGroundColor);
			++row_count;
			column_number = 0;
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
		*/
	//while( std::getline(in, temp))
   // {                         
       /* char symbol;
        char *s;
        in.get(symbol);
        in.get(symbol1);

        if(symbol != ' ' && (!(symbol1 >= 'À' && symbol1 <= 'ß') ) && symbol!='\n' && symbol1!='\n')
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
        }
    }*/
//	}
	/*
	if ( myFile.Open( _T("..\\symbols\\1.txt"), CFile::modeRead ))
	{
	    myFile.Seek( 0, CFile::begin );
		get
		nActual = myFile.Read(szBuffer, sizeof(szBuffer)); 
	}*/
	// TODO: Add your control notification handler code here
}

void CgeneratorDlg::create_Image()
{
	CString backGroundColor = CString("RGB(0,0,0)");
	CString symbolColor = CString("RGB(255,255,255)");

	for (int j = 0; j < count_column; j+=2)
	{
		for (int i = 0; i != m_Storage_Screen_Point.size(); ++i)
		{
			char symbol = (m_Storage_Screen_Point[i])[j];
			if (symbol == '0' || symbol == '1')
				write_file(symbol == '1' ? symbolColor : backGroundColor);
		}
		if (j < (count_column-2))
		{
			for (int i = 0; i != m_Storage_Screen_Point.size(); ++i)
			{
				char symbol = (m_Storage_Screen_Point[i])[j + 1];
				if (symbol == '0' || symbol == '1')
					write_file(symbol == '1' ? symbolColor : backGroundColor);
			}
		}
	}
		
	/*for (int i = 0; i != m_Storage_Screen_Point.size(); ++i)
	{
		char symbol = ((m_Storage_Screen_Point[i])[count_column]);
		if (symbol == '0' || symbol == '1')
			write_file(symbol == '1' ? symbolColor : backGroundColor);
	}*/
}

void CgeneratorDlg::OnBnClickedButton1()
{
	current_Size_Screen = 0;
	m_Storage_Screen_Point.clear();

	fill_Useful_Data_Screen();
	//add_Blank_Screen_Begin();
	add_Blank_Screen_End();

	create_Image();

}

bool CgeneratorDlg::write_file(const CString &text)
{
    CString NameFile = CString("../../emulator/inbox/1.txt");
    std::ofstream os;
	os.open(NameFile, std::ios::app);
    if(!os )
    {
        printf("File not found");
        return(0);
    }

	CT2CA pszConvertedAnsiString (text);
 
    std::string strStd (pszConvertedAnsiString);

    os << strStd.substr(0, strStd.size()) << std::endl;
    os.close();

	return true;
}

void CgeneratorDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
