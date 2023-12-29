#include "Login.h"


Login::Login()
{
	SetRect(&clickStart, 608, 61, 784, 268);
	//왼쪽 위 608, 61 왼쪽 아래 608, 268 오른쪽 아래 784, 268 오른쪽 위 784, 61
}
Login::~Login() {}

void Login::Initialize(HDC hdc)
{
	parseJson.Initialize();
	myDC = CreateCompatibleDC(hdc);
	hbitmap = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("loginBackGround").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	holdbitmap = (HBITMAP)SelectObject(myDC, hbitmap);
	myKey.Initialize();
}

int Login::Progress(int& m_nCurrent)
{
	if (PtInRect(&clickStart, ptMouse))
	{
		if (myKey.isOnceKeyDown(VK_LBUTTON))
		{
			m_nCurrent++;
			return 1;
		}
	}

	return 0;
}

void Login::Render(HDC hdc)
{
	GetObject(hbitmap, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	TransparentBlt(hdc, 0, 0, bx, by, myDC, 0, 0, bx, by, RGB(255, 0, 255));
}