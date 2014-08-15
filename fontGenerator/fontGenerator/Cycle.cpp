#include "StdAfx.h"
#include "Cycle.h"


Cycle::Cycle(int current_X, int current_Y, int lenght, CWnd *parent)
	: CStatic(), lenghtBalloon(lenght)
{
	CRect rect(current_X, current_Y, current_X + lenghtBalloon, current_Y + lenghtBalloon);
	
	CStatic::Create("", WS_CHILD|WS_VISIBLE|SS_NOTIFY, *rect, parent, 1235);

	lRGBMas[0] = RGB(255, 255, 255);
	lRGBMas[1] = RGB(0, 255, 0);

	//lRGB = lRGBMas[0];
	numRGB = 0;
}


Cycle::~Cycle(void)
{
}

long Cycle::GetCurrentRGB()
{
	return lRGBMas[numRGB];
}

bool Cycle::isClickedItem()
{
	if (numRGB > 0)
		return true;
	return false;
}

BEGIN_MESSAGE_MAP(Cycle, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()

void Cycle::OnLButtonDown(UINT nFlags, CPoint point)
{
	numRGB = (++numRGB)%2;
	//lRGB = lRGBMas[(++numRGB)%2];

	CWnd::OnLButtonDown(nFlags, point);
	Invalidate();
}

void Cycle::OnPaint()
{
	CPaintDC dc(this); 
		
	CDC memDC;
	
	RECT dialog_Rect;
	this->GetClientRect(&dialog_Rect);

	CBitmap b;

	b.CreateCompatibleBitmap( &dc, dialog_Rect.right, dialog_Rect.bottom);
	memDC.CreateCompatibleDC( &dc ) ;
	
	memDC.SelectObject( &b );

	CRect rect(0, 0, 0 + lenghtBalloon, 0 + lenghtBalloon);	

	HBRUSH hBrush = CreateSolidBrush(lRGBMas[numRGB]);
	memDC.SelectObject(hBrush);
	memDC.Ellipse(&rect);

	DeleteObject(hBrush);
	
	dc.BitBlt(0, 0, dialog_Rect.right, dialog_Rect.bottom,
           &memDC,
           0, 0,
           SRCCOPY);
}
