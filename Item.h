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
	float fItemDelay = 0.0f;
	BITMAP bit;
	int bx, by;
	HBITMAP ItemBit;
	HBITMAP ItemOld;
	int BitmapWidth = 0;
	int BitmapHeight = 0;
	BITMAP ItemBitmap;
	RECT ItemRECT;
	myJson parseJson;
	int ItemFrameX = 0;
	int CollisonPlayer = 0; // 충돌 여부

public:
	// 아이템의 효과
	int nBombMax = 0; // 물풍선 갯수
	float fSpeedMax = 0.0f; // 속도
	int nBombLength = 0; // 물풍선 길이

	// 아이템의 좌표
	int ItemX, ItemY = 0;
	int nItemType = 0;
public:
	Item();
	~Item();
	void Initialize(HDC hdc, int myType);
	void Progress();
	void Render(HDC hdc); // 게임 플레이 용;
	int getWidth(const char* chFileName);
	int getHeight(const char* chFileName);
	float getX(const char* chFileName);
	float getY(const char* chFileName);
	RECT& getItemRECT();
};