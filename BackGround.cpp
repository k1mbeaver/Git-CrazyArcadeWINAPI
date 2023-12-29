#include "Background.h"

BackGround::BackGround() {}
BackGround::~BackGround() {}

void BackGround::Initialize(HDC hdc)
{
	parseJson.Initialize();
	myDC = CreateCompatibleDC(hdc);
	hbitmap = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("BackGround").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	Gamebit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("Game").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	Overbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("Over").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	holdbitmap = (HBITMAP)SelectObject(myDC, hbitmap);
}

void BackGround::Progress()
{
}

void BackGround::Render(HDC hdc)
{
	GetObject(hbitmap, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, 0, 0, bx, by, myDC, 0, 0, SRCCOPY);

	//SelectObject(myDC, holdbitmap);
	//DeleteObject(hbitmap);
	//DeleteDC(myDC);
}

void BackGround::GameOver(HDC hdc)
{
	Gameold = (HBITMAP)SelectObject(myDC, Gamebit);
	TransparentBlt(hdc, getX("Game"), getY("Game"), getWidth("Game"), getHeight("Game"), myDC, 0, 0, getWidth("Game"), getHeight("Game"), RGB(255, 0, 255));
	Overold = (HBITMAP)SelectObject(myDC, Overbit);
	TransparentBlt(hdc, getX("Over"), getY("Over"), getWidth("Over"), getHeight("Over"), myDC, 0, 0, getWidth("Over"), getHeight("Over"), RGB(255, 0, 255));
}

float BackGround::getX(const char* chFileName)
{
	float fX;
	fX = parseJson.getMyObjectX(chFileName);

	return fX;
}

float BackGround::getY(const char* chFileName)
{
	float fY;
	fY = parseJson.getMyObjectY(chFileName);

	return fY;
}

int BackGround::getWidth(const char* chFileName)
{
	int nWidth;
	nWidth = parseJson.getMyObjectWidth(chFileName);

	return nWidth;
}

int BackGround::getHeight(const char* chFileName)
{
	int nHeight;
	nHeight = parseJson.getMyObjectHeight(chFileName);

	return nHeight;
}

RECT BackGround::GameOverRECT()
{
	RECT GameOver;
	GameOver.left = getX("BackGround");
	GameOver.top = getY("BackGround");
	GameOver.right = GameOver.left + getWidth("BackGround");
	GameOver.bottom = GameOver.top + getHeight("BackGround");

	return GameOver;
}