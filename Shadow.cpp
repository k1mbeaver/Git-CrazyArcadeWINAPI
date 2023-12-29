#include "Shadow.h"
Shadow::Shadow() {}
Shadow::~Shadow() {}

void Shadow::Initialize(HDC hdc)
{
	// Initialize에서 각 이미지들의 정보를 저장해 놓으면?

	parseJson.Initialize();
	myDC = CreateCompatibleDC(hdc);
	Shadowbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("Shadow").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	Shadowold = (HBITMAP)SelectObject(myDC, Shadowbit);
}

void Shadow::Progress()
{
}

void Shadow::Render(HDC hdc, int nPlayerState, int nState) // 게임 플레이 화면 용
{
	if (nPlayerState == 0) // 생존
	{
		TransparentBlt(hdc, myXY.myX + 10, myXY.myY + 60, getWidth("Shadow"), getHeight("Shadow"), myDC, 0, 0, getWidth("Shadow"), getHeight("Shadow"), RGB(255, 0, 255));
	}

	else if (nPlayerState == 1) // 갇힘 & 사망
	{
		if (nDieCount == 0)
		{
			nDieX = myXY.myX;
			nDieY = myXY.myY;
		}
		TransparentBlt(hdc, nDieX + 23, nDieY + 110, getWidth("Shadow"), getHeight("Shadow"), myDC, 0, 0, getWidth("Shadow"), getHeight("Shadow"), RGB(255, 0, 255));

		nDieCount++;
	}
}

void Shadow::Render(HDC hdc, int nState) // 로비용
{
	TransparentBlt(hdc, getX("BazziJump") + 10, getY("BazziJump") + 65, getWidth("Shadow"), getHeight("Shadow"), myDC, 0, 0, getWidth("Shadow"), getHeight("Shadow"), RGB(255, 0, 255));
}

int Shadow::getWidth(const char* chFileName)
{
	int nWidth;
	nWidth = parseJson.getMyObjectWidth(chFileName);

	return nWidth;
}

int Shadow::getHeight(const char* chFileName)
{
	int nHeight;
	nHeight = parseJson.getMyObjectHeight(chFileName);

	return nHeight;
}

float Shadow::getX(const char* chFileName)
{
	float fX;
	fX = parseJson.getMyObjectX(chFileName);

	return fX;
}

float Shadow::getY(const char* chFileName)
{
	float fY;
	fY = parseJson.getMyObjectY(chFileName);

	return fY;
}