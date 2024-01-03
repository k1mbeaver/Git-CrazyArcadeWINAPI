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
	int CollisonPlayer = 0; // �浹 ����

public:
	// �������� ȿ��
	int nBombMax = 0; // ��ǳ�� ����
	float fSpeedMax = 0.0f; // �ӵ�
	int nBombLength = 0; // ��ǳ�� ����

	// �������� ��ǥ
	int ItemX, ItemY = 0;
	int nItemType = 0;
public:
	Item();
	~Item();
	void Initialize(HDC hdc, int myType);
	void Progress();
	void Render(HDC hdc); // ���� �÷��� ��;
	int getWidth(const char* chFileName);
	int getHeight(const char* chFileName);
	float getX(const char* chFileName);
	float getY(const char* chFileName);
	RECT& getItemRECT();
};