#pragma once
#include "stdafx.h"
#include "Define.h"
#include "DbBuf.h"
#include "background.h"
#include "Player.h"
#include "Login.h"
#include "Lobby.h"
#include "Block.h"
#include "Shadow.h"
#include "Collison.h"
#include "Bomb.h"
#include "myJson.h"
#include "Wave.h"
#include "Item.h"

//나머지 게임에 관련된 클래스가 있는 헤더를 추가한다.
extern HINSTANCE hInst;                                // 현재 인스턴스입니다.
extern HWND g_hWnd;
extern RECT crt;

class GameCore
{
private:
	//관련된 클래스들 추가
	HDC myHDC = GetDC(g_hWnd);
	DbBuf myDbBuf;
	Shadow myShadow;
	BackGround myBackGround;
	Player myPlayer;
	Login myLogin;
	Lobby myLobby;
	Block myBlock;
	Bomb myBomb;
	Wave myWave;
	Item myItem;
	Collison myCollison;
	myJson parseJson;
	int nCurrent = 0;
	int nFrame = 0;
	int nInitNum = 0;
	int nBombCount = 0; // 물풍선 타이머
	int nBombState = 1;
	int nPopFrameX = 0; // 물줄기 프레임
	int nGameOverCount = 0; // 게임 오버 카운트
	int nPlayerState = 0; // 0 : 생존, 1 : 갇힘, 2: 사망
	int nPlayerTrap = 0; // 갇혀있는 시간 카운트 
	Block* myMap[12][27];
public:
	GameCore();
	~GameCore();

	void Initialize(); // 초기화
	void Progress(); // 처리
	void Render(); // 그리기
	void Release();
};