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
	HBITMAP PopDownbit, PopUpbit, PopLeftbit, PopRightbit;
	HBITMAP PopDownold, PopUpold, PopLeftold, PopRightold;
	myJson parseJson;
	int PopFrameX = 0;
public:
	Wave();
	~Wave();
	void Initialize(HDC hdc);
	void Progress();
	void Render(HDC hdc, float fX, float fY); // 물풍선 설치
	int getWidth(const char* chFileName);
	int getHeight(const char* chFileName);
	void InitializeFrameX(); // 물줄기 프레임 초기화하기
};