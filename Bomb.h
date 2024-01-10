#pragma once
#include "stdafx.h"
#include "Define.h"
#include "myJson.h"

extern HINSTANCE hInst;
extern HWND g_hWnd;
extern RECT crt;

typedef struct BombPosition
{
	float fX = 0; // x��ǥ
	float fY = 0; // y��ǥ
	int WaveLength = 1;
	bool myExist = false;
}BombInfo;

class Bomb
{
private:
	HWND myHWND;
	HDC myDC;
	int nBombSecond = 0;
	HBITMAP Bombbit, BombPopbit, PopDownbit, PopUpbit, PopLeftbit, PopRightbit;
	HBITMAP Bombold, BombPopold, PopDownold, PopUpold, PopLeftold, PopRightold;
	BITMAP Bombbitmap, BombPopbitmap;
	myJson parseJson;
	int FrameX, BombFrameX = 0;
	int PopFrameX = 0;
	float BombFrameDelay = 0.0f;
	int WaveFrameX = 0;
	float WaveFrameDelay = 0.0f;
	RECT WidthWaveRECT;
	RECT HeightWaveRECT;

public:
	// ��ġ�� ���� ����ü
	BombInfo myCreateBomb;

	// ����
	int nBombLength = 1;

	// ���ѽð�
	int nBombCount = 0;
public:
	Bomb();
	~Bomb();
	void Initialize(HDC hdc, float fX, float fY, int nLength);
	bool Progress();
	void Render(HDC hdc); // ��ǳ�� ��ġ
	bool BombRender(HDC hdc); // ��ǳ�� ���Ľ�
	int getWidth(const char* chFileName);
	int getHeight(const char* chFileName);
	float getX();
	float getY();
	void CreateBomb(float m_fX, float m_fY);
	void DeleteBomb();
	bool ExistBomb();
	RECT getWidthPop();
	RECT getHeightPop();
	RECT getWidthWave();
	RECT getHeightWave();
};