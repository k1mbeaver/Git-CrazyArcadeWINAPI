#pragma once
#include "stdafx.h"
#include "Define.h"
#include "myJson.h"

extern HINSTANCE hInst;
extern HWND g_hWnd;
extern RECT crt;

class Wave
{
private:
	HWND myHWND;
	HDC myDC;
	HBITMAP PopDownbit, PopUpbit, PopLeftbit, PopRightbit, BombPopbit;
	HBITMAP PopDownold, PopUpold, PopLeftold, PopRightold, BombPopold;
	myJson parseJson;
	int PopFrameX = 0;
	int BombFrameX = 0;
	float WaveFrameDelay = 0.0f;
public:
	Wave();
	~Wave();
	void Initialize(HDC hdc);
	void Progress();
	bool Render(HDC hdc, float fX, float fY); // ��ǳ�� ��ġ
	int getWidth(const char* chFileName);
	int getHeight(const char* chFileName);
	void InitializeFrameX(); // ���ٱ� ������ �ʱ�ȭ�ϱ�
};