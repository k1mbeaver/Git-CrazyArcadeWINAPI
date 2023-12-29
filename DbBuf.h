#pragma once
#include "stdafx.h"
#include "Define.h"

extern HINSTANCE hInst;                                // 현재 인스턴스입니다.
extern HWND g_hWnd;
extern RECT crt;

class DbBuf
{
private:
	HWND myhWnd;
	HDC hDCMain;
	HDC hdcBuffer; // 메모리에 그려줄 dc
	HBITMAP hdcBmp; // hDCMain이 사용하는 빈 종이
public:
	DbBuf();
	~DbBuf();

	bool Initialize(); // 초기화
	void Progress(); // 처리
	void Render(); // 그리기
	void Destroy(); // 메모리 삭제
	HDC ReturnBackDC(); // 백버퍼 제공
	void DeleteScreen(); // 현재 그림 삭제
};