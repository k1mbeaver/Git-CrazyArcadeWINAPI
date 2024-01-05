#pragma once
#include "stdafx.h"
#include "Define.h"
#include "myJson.h"

extern HINSTANCE hInst;
extern HWND g_hWnd;
extern RECT crt;
extern RECT rcInter;
class Player
{
private:
	HWND myHWND;
	HDC myDC;
	string filename;
	int nWidth, nHeight;
	float fX, fY;
	BITMAP bit;
	int bx, by;
	HBITMAP Downbit, Upbit, Leftbit, Rightbit, Jumpbit, Shadowbit, Trapbit, Diebit;
	HBITMAP Downold, Upold, Leftold, Rightold, Jumpold, Shadowold, Trapold, Dieold;
	BITMAP UpDownbit, LeftRightbit, Jumpbitmap, Shadowbitmap;
	RECT PlayerRECT;
	myJson parseJson;
	int UDFrameX, LRFrameX, JumpFrameX, TrapFrameX, DieFrameX;
	float fPlayerX, fPlayerY = 0;
	int UpDownX, LeftRightX, PlayerY, JumpX, JumpY;
	int nDieCount = 0; // 죽었을때 좌표 멈추기위해
	int nDieX, nDieY = 0;
	int CollisonPlayer = 0; // 충돌 여부
	int nBanCount = 0;
	int nBanWay = 0;

public:
	float PlayerSpeed = 1.0f; // Default = 1.0f, 속도 아이템을 먹을 수록 점점 증가한다 1.0f 씩
	int PlayerBomb = 1;
	int PlayerPotion = 1;
public:
	Player();
	~Player();
	void Initialize(HDC hdc);
	void Progress();
	void PlayerMove();
	void Render(HDC hdc, int nPlayerState, int nState); // 게임 플레이 용;
	void Render(HDC hdc, int nState); // 로비용;
	void GetItem(int nItemType);
	int getWidth(const char* chFileName);
	int getHeight(const char* chFileName);
	float getX(const char* chFileName);
	float getY(const char* chFileName);
	RECT& getPlayerRECT(float fX, float fY);
	void pushbackPlayer(Direction myDirection);
	void PlayerStop();
};