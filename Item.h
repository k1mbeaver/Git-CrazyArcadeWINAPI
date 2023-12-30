#pragma once
#include "stdafx.h"
#include "Define.h"
#include "myJson.h"

// 여기서 아이템의 정보 구조체?
extern HINSTANCE hInst;
extern HWND g_hWnd;
extern RECT crt;
extern RECT rcInter;
class Item
{
private:
	HWND myHWND;
	HDC myDC;
	string filename;
	int nWidth, nHeight;
	float fX, fY;
	BITMAP bit;
	int bx, by;
	HBITMAP ItemBit, ShadowBit;
	HBITMAP ItemOld, ShadowOld;
	BITMAP ItemBitmap, Shadowbitmap;
	RECT ItemRECT;
	myJson parseJson;
	int ItemFrameX;
	float fItemX, fItemY = 0;
	int ItemX;
	int CollisonPlayer = 0; // 충돌 여부
public:
	Item();
	~Item();
	void Initialize(HDC hdc);
	void Progress();
	void PlayerMove();
	void Render(HDC hdc, int nState); // 게임 플레이 용;
	int getWidth(const char* chFileName);
	int getHeight(const char* chFileName);
	float getX(const char* chFileName);
	float getY(const char* chFileName);
	RECT& getItemRECT(float fX, float fY);
};