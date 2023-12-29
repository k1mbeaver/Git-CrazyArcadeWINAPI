#pragma once
#include "stdafx.h"
#include "Define.h"
#include "KeyManager.h"
#include "myJson.h"


extern HINSTANCE hInst;                             
extern HWND g_hWnd;
extern RECT crt;
class Lobby
{
private:
	//map<string, BitmapImage*> BazziList;
	HWND myHWND;
	HDC myDC;
	HBITMAP hbitmap;
	HBITMAP holdbitmap;
	BITMAP bit;
	KeyManager myKey;
	RECT clickStart;
	myJson parseJson;
	bool checkStart;
	int FrameX = 0, FrameY = 0;
	int bx, by;
public:
	Lobby();
	~Lobby();
	void Initialize(HDC hdc);
	int Progress(int& m_nCurrent);
	void Render(HDC hdc);
};