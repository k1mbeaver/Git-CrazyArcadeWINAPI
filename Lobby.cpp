#include "Lobby.h"
Lobby::Lobby()
{
	SetRect(&clickStart, 848, 594, 1078, 660);
	//왼쪽 위 848, 594 왼쪽 아래 848, 660 오른쪽 아래 1078, 660 오른쪽 위 1078, 594
}
Lobby::~Lobby() {}
void Lobby::Initialize(HDC hdc)
{
	parseJson.Initialize();
	myDC = CreateCompatibleDC(hdc);
	hbitmap = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("lobbyBackGround").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	holdbitmap = (HBITMAP)SelectObject(myDC, hbitmap);
}
int Lobby::Progress(int& m_nCurrent)
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
void Lobby::Render(HDC hdc)
{
	GetObject(hbitmap, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;
	TransparentBlt(hdc, 0, 0, bx, by, myDC, 0, 0, bx, by, RGB(255, 0, 255));
}

