#pragma once
#include "stdafx.h"
#include "Define.h"
#include "myJson.h"

// ���⼭ �������� ���� ����ü?
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
	int CollisonPlayer = 0; // �浹 ����
public:
	Item();
	~Item();
	void Initialize(HDC hdc);
	void Progress();
	void PlayerMove();
	void Render(HDC hdc, int nState); // ���� �÷��� ��;
	int getWidth(const char* chFileName);
	int getHeight(const char* chFileName);
	float getX(const char* chFileName);
	float getY(const char* chFileName);
	RECT& getItemRECT(float fX, float fY);
};