#include "StdAfx.h"
#include "Cycle.h"


Cycle::Cycle(int current_X, int current_Y, int lenght_Balloon, CDC& memDC, CClientDC& dc, const RECT& dialog_Rect, CWnd *parent)
	: CStatic()
{
	long lRGB = RGB(0, 255, 0);
		
		CRect rect(current_X, current_Y, current_X + lenght_Balloon, current_Y + lenght_Balloon);
		
		CStatic::Create("", WS_CHILD|WS_VISIBLE|SS_NOTIFY, *rect, parent, 1235);

		//this->ShowWindow(SW_HIDE);

		/*if (column%2 == 0)
			current_Y -= lenght_Balloon;
		else
			current_Y += lenght_Balloon;
			*/

		//++row;
		
		/*if (row >= count_row || (column%2 && (row+1) == count_row))
		{			
			row = 0;
			current_X += lenght_Balloon;

			if (column%2 == 0)
				current_Y += lenght_Balloon + lenght_Balloon / 2;	
			else
				current_Y -= lenght_Balloon / 2;
			++column;
		}*/
		

		/*CDC memDC;
		
			
			CClientDC dc(parent);
			CBitmap b;
			b.CreateCompatibleBitmap( &dc, dialog_Rect.right, dialog_Rect.bottom);
			memDC.CreateCompatibleDC( &dc ) ;
	
			//bMemDCEnabled = TRUE;
	

			memDC.SelectObject( &b );

			*/
			HBRUSH hBrush = CreateSolidBrush(lRGB);
			memDC.SelectObject(hBrush);
			memDC.Ellipse(&rect);

			DeleteObject(hBrush);

			//CBrush brush ( RGB(255,255,255) );
			//memDC.FillRect( &dialog_Rect, &brush);

		

	
	dc.BitBlt(0, 0, dialog_Rect.right, dialog_Rect.bottom,
           &memDC,
           0, 0,
           SRCCOPY);


	

	//ModifyStyle(0,SS_NOTIFY,0);


	//MSG msg;
//	BOOL bRet;

	/*while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
	{ 
		if (bRet == -1)
		{
			// обработка ошибки и возможный выход из программы
		}
		else
		{
			if (msg.message == 5)
			{
				int y = 0;
			}
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
	}*/

}


Cycle::~Cycle(void)
{
}

BEGIN_MESSAGE_MAP(Cycle, CStatic)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()






void Cycle::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDown(nFlags, point);
}
