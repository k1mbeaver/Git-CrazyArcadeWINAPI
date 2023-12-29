
#pragma once
#include "stdafx.h"
#include "Define.h"
#include "myJson.h"

extern HINSTANCE hInst;                             
extern HWND g_hWnd;
extern RECT crt;

class BackGround
{
private:
	HWND myHWND;
	HDC myDC;
	HBITMAP hbitmap, Gamebit, Overbit;
	HBITMAP holdbitmap, Gameold, Overold;
	myJson parseJson;
	BITMAP bit;
	int bx, by = 0;
public:
	BackGround();
	~BackGround();

	void Initialize(HDC hdc);
	void Progress();
	void Render(HDC hdc);
	void GameOver(HDC hdc);
	float getX(const char* chFileName);
	float getY(const char* chFileName);
	int getWidth(const char* chFileName);
	int getHeight(const char* chFileName);
	RECT GameOverRECT();
};