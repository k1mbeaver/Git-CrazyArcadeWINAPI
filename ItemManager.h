#pragma once
#include "stdafx.h"
#include "Define.h"
#include "myJson.h"
#include "Item.h"
#include <vector>
#include <random>

// 여기서 아이템의 정보 구조체?
extern HINSTANCE hInst;
extern HWND g_hWnd;
extern RECT crt;
extern RECT rcInter;

class ItemManager
{
private:
	HWND myHWND;
	HDC myDC;
	string filename;
	int nWidth, nHeight;
	float fX, fY;
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
	float fItemX, fItemY = 0;
	int ItemX;
	int CollisonPlayer = 0; // 충돌 여부

public:
	// 아이템 배열
	vector<Item*> myItem;

	// 아이템의 효과

	int nBombMax = 0; // 물풍선 갯수
	float fSpeedMax = 0.0f; // 속도
	int nBombLength = 0; // 물풍선 길이
public:
	ItemManager();
	~ItemManager();
	void Initialize(HDC hdc);
	void Progress();
	void Render(HDC hdc); // 게임 플레이 용;
	void DeleteItem(int nIndex);
	int RandomTransform(int min, int max);
	int GetRandomPosition();
	void CheckRandomPosition(int& nPosition);
	int GetRandomType();
};