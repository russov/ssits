
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
	void changeState();

	int numRGB;
	int lastNumRGB;
	long lRGBMas[2];
	int lenghtBalloon;

public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};

