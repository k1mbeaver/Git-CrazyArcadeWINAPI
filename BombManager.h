#pragma once
#include "stdafx.h"
#include "Define.h"
#include "myJson.h"
#include "Bomb.h"
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
	float fX, fY;
	BITMAP bit;
	int bx, by;
	myJson parseJson;
	int CollisonPlayer = 0; // �浹 ����

public:
	// ������ �迭, ���ͷ� �ϴ°� �´µ���
	vector<Bomb*> myBomb;
public:
	BombManager();
	~BombManager();
	void Initialize(HDC hdc);
	void Progress();
	void Render(HDC hdc); // ���� �÷��� ��;
	void CreateBomb(float PlayerX, float PlayerY, int nLength); // ��ǳ�� ��ġ, �Ű����� = ���� ĳ������ ��ǥ, ��ǳ�� ����
	void DeleteBomb(); // ��ǳ�� ��
};