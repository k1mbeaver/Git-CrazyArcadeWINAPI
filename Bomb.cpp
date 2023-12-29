#include "Bomb.h"
Bomb::Bomb() {}
Bomb::~Bomb() {}

void Bomb::Initialize(HDC hdc)
{
	// Initialize에서 각 이미지들의 정보를 저장해 놓으면?

	parseJson.Initialize();
	myDC = CreateCompatibleDC(hdc);
	Bombbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("Bomb").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BombPopbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("BombPop").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	nBombCount = 1; // 물풍선 갯수 1개로 초기화
}

void Bomb::Progress()
{
}

void Bomb::Render(HDC hdc) // 물풍선 설치
{
	Bombold = (HBITMAP)SelectObject(myDC, Bombbit);
	TransparentBlt(hdc, myCreateBomb.fX, myCreateBomb.fY, getWidth("Bomb"), getHeight("Bomb"), myDC, FrameX, 0, getWidth("Bomb"), getHeight("Bomb"), RGB(255, 0, 255));

	// 애니메이션 출력을 위한 프레임
	fFrameDelay += dDT;
	if (fFrameDelay > 0.1f)
	{
		fFrameDelay = 0;
		FrameX += 56;

		if (FrameX >= 224)
		{
			FrameX = 0;
		}
	}
}

void Bomb::BombRender(HDC hdc) // 물풍선 폭파
{
	BombPopold = (HBITMAP)SelectObject(myDC, BombPopbit);
	TransparentBlt(hdc, myCreateBomb.fX, myCreateBomb.fY, getWidth("BombPop"), getHeight("BombPop"), myDC, BombFrameX, 0, getWidth("BombPop"), getHeight("BombPop"), RGB(255, 0, 255)); // 가운데

	// 애니메이션 출력을 위한 프레임
	fFrameDelay += dDT;
	if (fFrameDelay > 0.1f)
	{
		fFrameDelay = 0;
		BombFrameX += 52; // 가운데

		if (BombFrameX >= 312)
		{
			BombFrameX = 0;
		}
	}
}

int Bomb::getWidth(const char* chFileName)
{
	int nWidth;
	nWidth = parseJson.getMyObjectWidth(chFileName);

	return nWidth;
}

int Bomb::getHeight(const char* chFileName)
{
	int nHeight;
	nHeight = parseJson.getMyObjectHeight(chFileName);

	return nHeight;
}

void Bomb::CreateBomb(float m_fX, float m_fY)
{
	myCreateBomb.fX = m_fX;
	myCreateBomb.fY = m_fY;
	myCreateBomb.myExist = true;

	// 물풍선 애니메이션 프레임 초기화
	FrameX = 0;
	BombFrameX = 0;
}

void Bomb::DeleteBomb()
{
	myCreateBomb.fX = 0;
	myCreateBomb.fY = 0;
	myCreateBomb.myExist = false;
}

bool Bomb::ExistBomb()
{
	if (myCreateBomb.myExist == false)
	{
		return false;
	}

	else
	{
		return true;
	}
}

float Bomb::getX()
{
	return myCreateBomb.fX;
}

float Bomb::getY()
{
	return myCreateBomb.fY;
}

// 물줄기의 가로를 구한다.
RECT Bomb::getWidthPop()
{
	RECT PopWidth;
	PopWidth.left = myCreateBomb.fX - 52;
	PopWidth.top = myCreateBomb.fY;
	PopWidth.right = myCreateBomb.fX + 104;
	PopWidth.bottom = myCreateBomb.fY + 52;

	return PopWidth;
}

// 물줄기의 세로를 구한다.
RECT Bomb::getHeightPop()
{
	RECT PopHeight;
	PopHeight.left = myCreateBomb.fX;
	PopHeight.top = myCreateBomb.fY - 52;
	PopHeight.right = myCreateBomb.fX + 52;
	PopHeight.bottom = myCreateBomb.fY + 104;

	return PopHeight;
}