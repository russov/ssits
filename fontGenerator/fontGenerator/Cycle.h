
#pragma once


class Cycle : public CWnd
{
//	Cycle m_Cycle_Control;
public:
	Cycle(int current_X, int current_Y, int lenght_Balloon, CDC& memDC, CClientDC& dc, const RECT& dialog_Rect);
	~Cycle(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

