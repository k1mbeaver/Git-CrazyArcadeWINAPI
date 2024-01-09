#include "Wave.h"
Wave::Wave() {}
Wave::~Wave() {}

void Wave::Initialize(HDC hdc)
{
	// Initialize에서 각 이미지들의 정보를 저장해 놓으면?
	parseJson.Initialize();
	myDC = CreateCompatibleDC(hdc);
	PopDownbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("DownWave").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	PopUpbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("UpWave").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	PopLeftbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("LeftWave").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	PopRightbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("RightWave").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BombPopbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("BombPop").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void Wave::Progress()
{
}

bool Wave::Render(HDC hdc, float fX, float fY) // 물풍선 폭파
{
	BombPopold = (HBITMAP)SelectObject(myDC, BombPopbit);
	TransparentBlt(hdc, fX, fY, getWidth("BombPop"), getHeight("BombPop"), myDC, BombFrameX, 0, getWidth("BombPop"), getHeight("BombPop"), RGB(255, 0, 255)); // 가운데
	PopDownold = (HBITMAP)SelectObject(myDC, PopDownbit);
	TransparentBlt(hdc, fX, fY + getHeight("DownWave"), getWidth("DownWave"), getHeight("DownWave"), myDC, PopFrameX, 0, getWidth("DownWave"), getHeight("DownWave"), RGB(255, 0, 255)); // 아래
	PopUpold = (HBITMAP)SelectObject(myDC, PopUpbit);
	TransparentBlt(hdc, fX, fY - getHeight("UpWave"), getWidth("UpWave"), getHeight("UpWave"), myDC, PopFrameX, 0, getWidth("UpWave"), getHeight("UpWave"), RGB(255, 0, 255)); // 위
	PopLeftold = (HBITMAP)SelectObject(myDC, PopLeftbit);
	TransparentBlt(hdc, fX - getWidth("LeftWave"), fY, getWidth("LeftWave"), getHeight("LeftWave"), myDC, PopFrameX, 0, getWidth("LeftWave"), getHeight("LeftWave"), RGB(255, 0, 255)); // 왼쪽
	PopRightold = (HBITMAP)SelectObject(myDC, PopRightbit);
	TransparentBlt(hdc, fX + getWidth("RightWave"), fY, getWidth("RightWave"), getHeight("RightWave"), myDC, PopFrameX, 0, getWidth("RightWave"), getHeight("RightWave"), RGB(255, 0, 255)); // 오른쪽

	// 애니메이션 출력을 위한 프레임
	WaveFrameDelay += dDT;

	if (WaveFrameDelay > 0.1f)
	{
		WaveFrameDelay = 0;
		PopFrameX += 52; // 4방향
		BombFrameX += 52; // 가운데

		if (BombFrameX >= 312)
		{
			BombFrameX = 0;
		}

		if (PopFrameX >= 572)
		{
			PopFrameX = 0;

			return true;
		}
	}

	return false;
}

int Wave::getWidth(const char* chFileName)
{
	int nWidth;
	nWidth = parseJson.getMyObjectWidth(chFileName);

	return nWidth;
}

int Wave::getHeight(const char* chFileName)
{
	int nHeight;
	nHeight = parseJson.getMyObjectHeight(chFileName);

	return nHeight;
}

void Wave::InitializeFrameX()
{
	PopFrameX = 0;
	BombFrameX = 0;
	WaveFrameDelay = 0.0f;
}