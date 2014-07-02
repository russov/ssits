
// generatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "generator.h"
#include "generatorDlg.h"
#include "afxdialogex.h"

#include <fstream>
#include <istream>
#include <iostream>

#include <ctime>

#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#define PORT 666
#define SERVERADDR "127.0.0.1"

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
	DDX_Control(pDX, IDC_EDIT2, m_Shift);
}

BEGIN_MESSAGE_MAP(CgeneratorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CgeneratorDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CgeneratorDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CgeneratorDlg::OnBnClickedButton2)
	ON_WM_TIMER()
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
	m_Shift.SetWindowTextW(CString("0"));

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

void CgeneratorDlg::OnTimer(UINT_PTR nIDEvent)
{
	std::string NameFile("../../emulator/inbox/1.txt");
	std::remove(NameFile.c_str());

	//static int last_Time_ms = CTime::GetCurrentTime().ge;

	static clock_t time1 = clock();
	// do something heavy
	clock_t time2 = clock();
	clock_t timediff = time2 - time1;

	float timediff_sec = ((float)timediff) / CLOCKS_PER_SEC;

	//time1 = time2;


		//create_Image((timediff/800) *2 );

	CString g = create_Image_To_Send((timediff/800) *2);
	send_Data data;
	//LPTSTR l = g.GetBuffer();
	//const char *c = l;
	//CString z(_T("I love CString!\r\n"));
//char sz[100];
sprintf(data.sequence_frame, "%S", g);
	
//memcpy(data.sequence_frame, g.GetBuffer(), 7582);
	send_DataUDP(data);



	CDialogEx::OnTimer(nIDEvent);
}

void CgeneratorDlg::add_Blank_Screen_Begin()
{
	for (int i = 0; i != m_Storage_Screen_Point.size(); ++i)
		for (int ii = 0; ii < count_column; ++ii)
		{
			if(i == 0 && (m_Storage_Screen_Point[i].size()-1)%2 == 0 && *(m_Storage_Screen_Point[0].begin()) != ' ')
				m_Storage_Screen_Point[i].insert(m_Storage_Screen_Point[i].begin(), ' ');
			else
			    m_Storage_Screen_Point[i].insert(m_Storage_Screen_Point[i].begin(), '0');
		}
}

void CgeneratorDlg::add_Blank_Screen_End()
{
	for (int i = 0; i != m_Storage_Screen_Point.size(); ++i)
	{
		for (int ii = 0; ii < count_column-1; ++ii)
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
	std::string incoming_Sequence = "11A";

	for (int i = 0; i < incoming_Sequence.size(); ++i)
	{
		std::ifstream in;
		in.open(CString(CString("..\\symbols\\") + CString(incoming_Sequence[i]) + CString(".txt")));
		
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
}

void CgeneratorDlg::create_Image(int shift)
{
	CString backGroundColor = CString("RGB(0,0,0)");
	CString symbolColor = CString("RGB(255,255,255)");

	for (int j = 0; j < count_column; j+=2)
	{
		for (int i = m_Storage_Screen_Point.size() - 1; i >= 0; --i)
		{
			char symbol = (m_Storage_Screen_Point[i])[j + shift%(m_Storage_Screen_Point[i].size() - count_column)];
			if (symbol == '0' || symbol == '1')
				write_file(symbol == '1' ? symbolColor : backGroundColor);
		}
		if (j < (count_column-2))
		{
			for (int i = 0; i != m_Storage_Screen_Point.size(); ++i)
			{
				char symbol = (m_Storage_Screen_Point[i])[j + 1 + shift%(m_Storage_Screen_Point[i].size() - count_column)];
				if (symbol == '0' || symbol == '1')
					write_file(symbol == '1' ? symbolColor : backGroundColor);
			}
		}
	}
}

CString CgeneratorDlg::create_Image_To_Send(int shift)
{
	CString backGroundColor = CString("RGB(0,0,0)");
	CString symbolColor = CString("RGB(255,255,255)");

	CString result;

	for (int j = 0; j < count_column; j+=2)
	{
		for (int i = m_Storage_Screen_Point.size() - 1; i >= 0; --i)
		{
			char symbol = (m_Storage_Screen_Point[i])[j + shift%(m_Storage_Screen_Point[i].size() - count_column)];
			if (symbol == '0' || symbol == '1')
				result += symbol == '1' ? symbolColor : backGroundColor;
		}
		if (j < (count_column-2))
		{
			for (int i = 0; i != m_Storage_Screen_Point.size(); ++i)
			{
				char symbol = (m_Storage_Screen_Point[i])[j + 1 + shift%(m_Storage_Screen_Point[i].size() - count_column)];
				if (symbol == '0' || symbol == '1')
					result += symbol == '1' ? symbolColor : backGroundColor;
			}
		}
	}

	return result;
}

void CgeneratorDlg::OnBnClickedButton1()
{
	current_Size_Screen = 0;
	m_Storage_Screen_Point.clear();
	std::string NameFile("../../emulator/inbox/1.txt");
	std::remove(NameFile.c_str());
	
	fill_Useful_Data_Screen();
	add_Blank_Screen_Begin();
	add_Blank_Screen_End();

	CString shift;
	m_Shift.GetWindowTextW(shift);

	//const char* cstr = (LPCTSTR)shift;
	atoi((char*)(LPCTSTR)shift);

	create_Image(atoi((char*)(LPCTSTR)shift));

	//send_Data data;

	//send_DataUDP(data);
}

bool CgeneratorDlg::write_file(const CString &text)
{
    std::string NameFile("../../emulator/inbox/1.txt");
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


void CgeneratorDlg::OnBnClickedButton2()
{
	current_Size_Screen = 0;
	m_Storage_Screen_Point.clear();

	fill_Useful_Data_Screen();
	add_Blank_Screen_Begin();
	add_Blank_Screen_End();

	create_Image();

	SetTimer(2, 400, 0);
}

BOOL CgeneratorDlg::send_DataUDP(struct send_Data data)
{
	char buff[10*1014];
    printf("UDP DEMO Client\nType quit to quit\n");

    // Шаг 1 - иницилизация библиотеки Winsocks
    if (WSAStartup(0x202,(WSADATA *)&buff[0]))
    {
      printf("WSAStartup error: %d\n",
             WSAGetLastError());
      return -1;
    }

    // Шаг 2 - открытие сокета
    SOCKET my_sock=socket(AF_INET, SOCK_DGRAM, 0);
    if (my_sock==INVALID_SOCKET)
    {
      printf("socket() error: %d\n",WSAGetLastError());
      WSACleanup();
      return -1;
    }

    // Шаг 3 - обмен сообщений с сервером
    HOSTENT *hst;
    sockaddr_in dest_addr;

    dest_addr.sin_family=AF_INET;
    dest_addr.sin_port=htons(PORT);

    // определение IP-адреса узла
    if (inet_addr(SERVERADDR))
      dest_addr.sin_addr.s_addr=inet_addr(SERVERADDR);
    else
      if (hst=gethostbyname(SERVERADDR))
        dest_addr.sin_addr.s_addr=((unsigned long **)
              hst->h_addr_list)[0][0];
    else
      {
        printf("Unknown host: %d\n",WSAGetLastError());
        closesocket(my_sock);
        WSACleanup();
        return -1;
      }

   /* while(1)
    {
      // чтение сообщения с клавиатуры
      printf("S<=C:");fgets(&buff[0],sizeof(buff)-1,
             stdin);
      if (!strcmp(&buff[0],"quit\n")) break;
	  */
      // Передача сообщений на сервер
	  
	 // data.sequence_frame = ;

      sendto(my_sock, (char *)&data,sizeof(data),0,
        (sockaddr *) &dest_addr,sizeof(dest_addr));
	  /*
      // Прием сообщения с сервера
      sockaddr_in server_addr;
      int server_addr_size=sizeof(server_addr);

      int n=recvfrom(my_sock,&buff[0],sizeof(buff)-1,0,
        (sockaddr *) &server_addr, &server_addr_size);

      if (n==SOCKET_ERROR)
      {
        printf("recvfrom() error:"\
          "%d\n",WSAGetLastError());
        closesocket(my_sock);
        WSACleanup();
        return -1;
      }
	  */
     // buff[n]=0;

      // Вывод принятого с сервера сообщения на экран
    //  printf("S=>C:%s",&buff[0]);
  //  }

    // шаг последний - выход
    closesocket(my_sock);
    WSACleanup();
}