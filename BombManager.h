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
	int CollisonPlayer = 0; // �浹 ����
	bool bBoom = false;

public:
	// ������ �迭, ���ͷ� �ϴ°� �´µ���
	vector<Bomb*> myBomb;
public:
	BombManager();
	~BombManager();
	void Initialize(HDC hdc);
	void Progress(int& nPlayerBomb);
	void Render(HDC hdc); // ���� �÷��� ��;
	void CreateBomb(float PlayerX, float PlayerY, int nLength, HDC hdc); // ��ǳ�� ��ġ, �Ű����� = ���� ĳ������ ��ǥ, ��ǳ�� ����
	void DeleteBomb(); // ��ǳ�� ��
};