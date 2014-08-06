#include "StdAfx.h"
#include "Cycle.h"




Cycle::Cycle(int current_X, int current_Y, int lenght_Balloon, CDC& memDC, CClientDC& dc, const RECT& dialog_Rect)
{
	long lRGB = RGB(0, 0, 0);
		
		CRect rect(current_X, current_Y, current_X + lenght_Balloon, current_Y + lenght_Balloon);
		
		/*if (column%2 == 0)
			current_Y -= lenght_Balloon;
		else
			current_Y += lenght_Balloon;
			*/
		HBRUSH hBrush = CreateSolidBrush(lRGB);
		memDC.SelectObject(hBrush);
		memDC.Ellipse(&rect);

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
		DeleteObject(hBrush);
	
	dc.BitBlt(0, 0, dialog_Rect.right, dialog_Rect.bottom,
           &memDC,
           0, 0,
           SRCCOPY);


	MSG msg;
	BOOL bRet;

	while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
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
	}

}


Cycle::~Cycle(void)
{
}
