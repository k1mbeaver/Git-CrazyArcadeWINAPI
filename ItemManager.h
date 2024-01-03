#pragma once
#include "stdafx.h"
#include "Define.h"
#include "myJson.h"
#include "Item.h"
#include <vector>
#include <random>

// ���⼭ �������� ���� ����ü?
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
	int CollisonPlayer = 0; // �浹 ����

public:
	// ������ �迭
	vector<Item*> myItem;

	// �������� ȿ��

	int nBombMax = 0; // ��ǳ�� ����
	float fSpeedMax = 0.0f; // �ӵ�
	int nBombLength = 0; // ��ǳ�� ����
public:
	ItemManager();
	~ItemManager();
	void Initialize(HDC hdc);
	void Progress();
	void Render(HDC hdc); // ���� �÷��� ��;
	void DeleteItem(int nIndex);
	int RandomTransform(int min, int max);
	int GetRandomPosition();
	void CheckRandomPosition(int& nPosition);
	int GetRandomType();
};