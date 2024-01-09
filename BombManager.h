#pragma once
#include "stdafx.h"
#include "Define.h"
#include "myJson.h"
#include "Bomb.h"
#include "Wave.h"
#include <vector>

extern HINSTANCE hInst;
extern HWND g_hWnd;
extern RECT crt;
extern RECT rcInter;

class BombManager
{
private:
	HWND myHWND;
	HDC myDC;
	string filename;
	int nWidth, nHeight;
	BITMAP bit;
	int bx, by;
	myJson parseJson;
	int CollisonPlayer = 0; // 충돌 여부
	bool bBoom = false;

public:
	// 아이템 배열, 벡터로 하는게 맞는듯함
	vector<Bomb*> myBomb;
public:
	BombManager();
	~BombManager();
	void Initialize(HDC hdc);
	void Progress(int& nPlayerBomb);
	void Render(HDC hdc); // 게임 플레이 용;
	void CreateBomb(float PlayerX, float PlayerY, int nLength, HDC hdc); // 물풍선 설치, 매개변수 = 현재 캐릭터의 좌표, 물풍선 길이
	void DeleteBomb(); // 물풍선 펑
};