#include "Bomb.h"
Bomb::Bomb() {}
Bomb::~Bomb() {}

void Bomb::Initialize(HDC hdc)
{
	// Initialize에서 각 이미지들의 정보를 저장해 놓으면?

	parseJson.Initialize();
	myDC = CreateCompatibleDC(hdc);
	Bombbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("Bomb").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	PopDownbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("DownWave").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	PopUpbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("UpWave").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	PopLeftbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("LeftWave").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	PopRightbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("RightWave").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BombPopbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("BombPop").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	nBombCount = 200; // 물풍선 타이머 설정
}

bool Bomb::Progress()
{
	if (nBombCount == 0)
	{
		return false;
	}

	else
	{
		nBombCount--;
		return true;
	}
}

void Bomb::Render(HDC hdc) // 물풍선 설치
{
	Bombold = (HBITMAP)SelectObject(myDC, Bombbit);
	TransparentBlt(hdc, myCreateBomb.fX, myCreateBomb.fY, getWidth("Bomb"), getHeight("Bomb"), myDC, FrameX, 0, getWidth("Bomb"), getHeight("Bomb"), RGB(255, 0, 255));

	// 애니메이션 출력을 위한 프레임
	BombFrameDelay += dDT;
	if (BombFrameDelay > 0.1f)
	{
		BombFrameDelay = 0;
		FrameX += 56;

		if (FrameX >= 224)
		{
			FrameX = 0;
		}
	}
}

bool Bomb::BombRender(HDC hdc) // 물풍선 폭파
{
	BombPopold = (HBITMAP)SelectObject(myDC, BombPopbit);
	TransparentBlt(hdc, myCreateBomb.fX, myCreateBomb.fY, getWidth("BombPop"), getHeight("BombPop"), myDC, PopFrameX, 0, getWidth("BombPop"), getHeight("BombPop"), RGB(255, 0, 255)); // 가운데

	for (int nIndex = 1; nIndex <= myCreateBomb.WaveLength; nIndex++)
	{
		PopDownold = (HBITMAP)SelectObject(myDC, PopDownbit);
		TransparentBlt(hdc, myCreateBomb.fX, myCreateBomb.fY + nIndex * getHeight("DownWave"), getWidth("DownWave"), getHeight("DownWave"), myDC, WaveFrameX, 0, getWidth("DownWave"), getHeight("DownWave"), RGB(255, 0, 255)); // 아래
		PopUpold = (HBITMAP)SelectObject(myDC, PopUpbit);
		TransparentBlt(hdc, myCreateBomb.fX, myCreateBomb.fY - nIndex * getHeight("UpWave"), getWidth("UpWave"), getHeight("UpWave"), myDC, WaveFrameX, 0, getWidth("UpWave"), getHeight("UpWave"), RGB(255, 0, 255)); // 위
		PopLeftold = (HBITMAP)SelectObject(myDC, PopLeftbit);
		TransparentBlt(hdc, myCreateBomb.fX - nIndex * getWidth("LeftWave"), myCreateBomb.fY, getWidth("LeftWave"), getHeight("LeftWave"), myDC, WaveFrameX, 0, getWidth("LeftWave"), getHeight("LeftWave"), RGB(255, 0, 255)); // 왼쪽
		PopRightold = (HBITMAP)SelectObject(myDC, PopRightbit);
		TransparentBlt(hdc, myCreateBomb.fX + nIndex * getWidth("RightWave"), myCreateBomb.fY, getWidth("RightWave"), getHeight("RightWave"), myDC, WaveFrameX, 0, getWidth("RightWave"), getHeight("RightWave"), RGB(255, 0, 255)); // 오른쪽
	}

	// 애니메이션 출력을 위한 프레임
	WaveFrameDelay += dDT;

	if (WaveFrameDelay > 0.1f)
	{
		WaveFrameDelay = 0;
		WaveFrameX += 52; // 4방향
		PopFrameX += 52; // 가운데

		if (PopFrameX >= 312)
		{
			PopFrameX = 0;
		}

		if (WaveFrameX >= 572)
		{
			WaveFrameX = 0;

			return true;
		}
	}

	return false;
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