
// emulatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "emulator.h"
#include "emulatorDlg.h"
#include "afxdialogex.h"

#include <regex>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define count_column 27
#define count_row 17


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


// CemulatorDlg dialog




CemulatorDlg::CemulatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CemulatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CemulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_Button1);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_EDIT2, m_PathDirectory);
}

BEGIN_MESSAGE_MAP(CemulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CemulatorDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


void CemulatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	TCHAR	szBuffer[10000] = {0}; 
	UINT    nActual = 0; 
	CFile	myFile;

	CString path;
	m_PathDirectory.GetWindowTextA(path);

	if ( myFile.Open( path, CFile::modeRead ))
	{
	    myFile.Seek( 0, CFile::begin );
	    nActual = myFile.Read(szBuffer, sizeof(szBuffer)); 
				
		SetColorBallons(CString(szBuffer));
		myFile.Close();
	}
	
	CDialogEx::OnTimer(nIDEvent);
}

void CemulatorDlg::ClearScreen()
{
	CClientDC * pDC = new CClientDC(this);
	
	long lRGB = RGB(255, 255, 255);

	HBRUSH hBrush = CreateSolidBrush(lRGB);
	

	pDC->SelectObject(hBrush); 
	
	RECT rect;

	this->GetClientRect(&rect);

	pDC->Rectangle(&rect);

			
	pDC->SetBkColor(lRGB);
	UpdateData(false);


	DeleteObject(hBrush);

	delete pDC;
}

void CemulatorDlg::SetColorBallons(const CString &sequenceIn)
{
	
	
	ClearScreen();
	
	
	
	const std::tr1::regex pattern("RGB\\((\\d+),(\\d+),(\\d+)\\)");

	std::string sequence = (LPCTSTR)sequenceIn;  //"RGB(100,100,100)RGB(10,10,130)";
 




	int row = 0;
	int column = 0;

	RECT dialog_Rect;

	this->GetClientRect(&dialog_Rect);

	int current_Y = 0;
	int current_X = 0;

	int lenght_Balloon = dialog_Rect.right / count_column;

	const std::tr1::sregex_token_iterator end;
	for (std::tr1::sregex_token_iterator i(sequence.begin(), sequence.end(), pattern); i != end; ++i)
	{
		//std::cout << (*i).str() << std::endl;
		std::tr1::match_results<std::string::const_iterator> result;
		std::string f = (*i).str();

		std::tr1::regex_match(f, result, pattern);

		//RECT pRect;

		int iRed = atoi(result[1].str().c_str());
		int iGrn = atoi(result[2].str().c_str());
		int iBlu = atoi(result[3].str().c_str());

		long lRGB = RGB(iRed, iGrn, iBlu);
		
	//	CDC * pDC = m_Edit1.GetDC();
				
		CClientDC * pDC = new CClientDC(this);
		
		HBRUSH hBrush = CreateSolidBrush(lRGB);
		
		CRect rect(current_Y,current_X,current_Y + lenght_Balloon, current_X + lenght_Balloon);

		current_Y += lenght_Balloon; 

		
		//ScreenToClient(&pRect);

		pDC->SelectObject(hBrush); 
		pDC->Ellipse(&rect);
		
		pDC->SetBkColor(lRGB);
		UpdateData(false);

		++column;
		
		if ((column >= count_column) || (row%2 && ((column + 1) == count_column)))
		{
			++row;
			column = 0;
			
			current_X += lenght_Balloon;
			current_Y = 0;

			if (row%2)
				current_Y += lenght_Balloon / 2;
		}
		
		
	//	pDC->res DeleteDC();

		DeleteObject(hBrush);
		delete pDC;

		/*
		for(int i = 0; i < count_row; ++i)
		{
			if (i%2)
				current_Y += lenght_Balloon / 2;

			for (int j = 0; j < count_column; ++j)
			{
				if (i%2 && ((j + 1) == count_column))
					break;
			*/	


		//if (number >= edit_Vector.size())
			//break;


		//CClientDC * pDC = new CClientDC(this) ;//(edit_Vector[number])->GetDC();
	
		//(edit_Vector[number])->GetWindowRect(&pRect);


		//pDC->Rectangle(1,50,100,150);


		/*++number;

		HBRUSH hBrush = CreateSolidBrush(lRGB);
		
		//WINDOWPLACEMENT pl;

		//(edit_Vector[number++])->GetWindowPlacement(&pl);

		//pRect = pl.rcNormalPosition;
		
		ScreenToClient(&pRect);

		pDC->SelectObject(hBrush); 
		pDC->Ellipse(&pRect);
		
		pDC->SetBkColor(lRGB);
		UpdateData(false);
		
		int y = 0;
		
		*/


		/*
		std::cout << result[1] << std::endl;
		std::cout << result[2] << std::endl;
		std::cout << result[3] << std::endl;
		*/
	}

}

void CemulatorDlg::SetBalloon(int red, int grn, int blu)
{
	RECT pRect;
	int iRed = rand()%255;
		int iGrn = rand()%255;
		int iBlu = rand()%255;
		long lRGB = RGB(iRed, iGrn, iBlu);
		CDC * pDC = m_Edit1.GetDC();

		m_Edit1.GetClientRect(&pRect);
		HBRUSH hBrush = CreateSolidBrush(lRGB);
		pDC->SelectObject(hBrush); 
		pDC->Rectangle(&pRect);
		pDC->SetBkColor(lRGB);
		UpdateData(false);			
}

BOOL CemulatorDlg::OnInitDialog()
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

	{
		TCHAR pathBuffer[10000] = {0};
		GetCurrentDirectoryA(10000, pathBuffer);
		
		CString path(pathBuffer);
		path += CString("\\..\\inbox\\1.txt");
		m_PathDirectory.SetWindowTextA(path);

		// TODO: Add extra validation here
		
		/*CRect dialog_Rect;

		this->GetClientRect(&dialog_Rect);

		int current_Y = 0;
		int current_X = 0;

		int lenght_Balloon = dialog_Rect.right / count_column;
		
		for(int i = 0; i < count_row; ++i)
		{
			if (i%2)
				current_Y += lenght_Balloon / 2;

			for (int j = 0; j < count_column; ++j)
			{
				if (i%2 && ((j + 1) == count_column))
					break;
				
				CEdit* edit = new CEdit();
				
				CRect rect(current_Y,current_X,current_Y + lenght_Balloon, current_X + lenght_Balloon);

				current_Y += lenght_Balloon; 
				
				RECT pRect1;

				edit->Create(ES_CENTER | WS_OVERLAPPED | WS_VISIBLE | ES_AUTOHSCROLL, rect, this, 1000);
				
				//CPaintDC* pDC=new CPaintDC(this);    
				
				//pDC->Rectangle(1,50,100,150);
				
				
				edit->GetRect(&pRect1);

								
				ClientToScreen(&pRect1);

				edit_Vector.push_back(edit);
			}
			current_X += lenght_Balloon;
			current_Y = 0;
		}
		*/
		SetTimer(2, 1000, 0);
			
		/*RECT pRect;
		int iRed = rand()%255;
		int iGrn = rand()%255;
		int iBlu = rand()%255;
		long lRGB = RGB(iRed, iGrn, iBlu);
		CDC * pDC = m_Edit1.GetDC();

		m_Edit1.GetClientRect(&pRect);
		HBRUSH hBrush = CreateSolidBrush(lRGB);
		pDC->SelectObject(hBrush); 
		pDC->Rectangle(&pRect);
		pDC->SetBkColor(lRGB);
		UpdateData(false);*/

	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}



void CemulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CemulatorDlg::OnPaint()
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

		CPaintDC* pDC=new CPaintDC(this);    
		pDC->Rectangle(1,1,10,10);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CemulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CemulatorDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	RECT pRect;
	int iRed = rand()%255;
	int iGrn = rand()%255;
	int iBlu = rand()%255;
	long lRGB = RGB(iRed, iGrn, iBlu);
	CDC * pDC = m_Edit1.GetDC();

	m_Edit1.GetClientRect(&pRect);
	HBRUSH hBrush = CreateSolidBrush(lRGB);
	pDC->SelectObject(hBrush); 
	pDC->Rectangle(&pRect);
	pDC->SetBkColor(lRGB);
	UpdateData(false);
	
	for (unsigned int i = 0; i < edit_Vector.size(); ++i)
	{
		CEdit *edit = edit_Vector[i];

		RECT rect;

		edit->GetClientRect(&rect);

		int h = 0;
	}

}


