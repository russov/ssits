
#pragma once


class Cycle : public CStatic
{

public:
	Cycle(int current_X, int current_Y, int lenght_Balloon, CWnd *parent);
	~Cycle(void);

	long GetCurrentRGB();
	bool isClickedItem();
		
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();

	int numRGB;
	//long lRGB;
	long lRGBMas[2];
	int lenghtBalloon;
};

