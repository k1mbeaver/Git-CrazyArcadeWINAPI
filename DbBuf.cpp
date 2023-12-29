#include "DbBuf.h"
DbBuf::DbBuf()
{
}
DbBuf::~DbBuf()
{
}
bool DbBuf::Initialize()
{
	myhWnd = g_hWnd;
	GetClientRect(myhWnd, &crt); // 너비를 구하기 위함, crt.right, crt.bottom 사용
	if (myhWnd == NULL)
		return false;
	hDCMain = GetDC(myhWnd); // DC를 가져옴
	hdcBuffer = CreateCompatibleDC(hDCMain); // BackBuffer에 현재 DC를 저장 
	hdcBmp = CreateCompatibleBitmap(hDCMain, crt.right, crt.bottom); // 현재의 화면에 있는 모든 색들을 검출
	SelectObject(hdcBuffer, (HBITMAP)hdcBmp);
	ReleaseDC(myhWnd, hDCMain); // 현재의 DC를 해제

	SetTimer(myhWnd, 0, 10, NULL);

	return true;
}

void DbBuf::Progress()
{

}

void DbBuf::Render()
{
	myhWnd = g_hWnd;
	GetClientRect(myhWnd, &crt); // 너비를 구하기 위함, crt.right, crt.bottom 사용
	hDCMain = GetDC(myhWnd);
	BitBlt(hDCMain, 0, 0, crt.right, crt.bottom, hdcBuffer, 0, 0, SRCCOPY);
	// 고속 복사 함수 : 메모리 DC의 비트맵을 현재 DC에 고속복사하는 함수
	// 백버퍼에 저장함
	ReleaseDC(myhWnd, hDCMain);
}
void DbBuf::Destroy()
{
}
HDC DbBuf::ReturnBackDC()
{
	return hdcBuffer;
}
void DbBuf::DeleteScreen()
{
	PatBlt(hdcBuffer, 0, 0, crt.right, crt.bottom, BLACKNESS);
	// 패턴 방식 초기화 함수 : 해당 DC의 비트맵 영역을 패턴 형태로 초기화 하는 데 사용 ( 패턴 : 브러쉬 ), 지정한 사각영역을 현재 DC에 선택된 브러쉬로 채움
	// 초기화를 하고 이미지를 뿌림
}