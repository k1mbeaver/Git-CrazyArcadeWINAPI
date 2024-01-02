#include "Item.h"
Item::Item() {}
Item::~Item() {}

void Item::Initialize(HDC hdc, int myType)
{
	// Initialize에서 각 이미지들의 정보를 저장해 놓으면?

	parseJson.Initialize();
	myDC = CreateCompatibleDC(hdc);

	const char* myBitName = "";

	switch (myType)
	{
	case BALLON:
		myBitName = "ballon";
		nBombMax = 1;
		break;

	case POTION:
		myBitName = "potion";
		nBombLength = 1;
		break;

	case POTIONMAX:
		myBitName = "potionmax";
		nBombLength = 10;
		break;

	case SKATE:
		myBitName = "skate";
		fSpeedMax = 1.0f;
		break;
	}

	ItemBit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink(myBitName).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BitmapWidth = getWidth(myBitName);
	BitmapHeight = getHeight(myBitName);
}

void Item::Progress()
{

}

void Item::Render(HDC hdc) // 게임 플레이 화면 용
{
	
	ItemOld = (HBITMAP)SelectObject(myDC, ItemBit);
	TransparentBlt(hdc, ItemX, ItemY, BitmapWidth, BitmapHeight, myDC, ItemFrameX, 0, BitmapWidth, BitmapHeight, RGB(255, 0, 255));
	
	fItemDelay += dDT;
	if (fItemDelay > 0.11f)
	{
		fItemDelay = 0;
		ItemFrameX += 56;

		if (ItemFrameX >= 112)
		{
			ItemFrameX = 0;
		}
	}
}

int Item::getWidth(const char* chFileName)
{
	int nWidth;
	nWidth = parseJson.getMyObjectWidth(chFileName);

	return nWidth;
}

int Item::getHeight(const char* chFileName)
{
	int nHeight;
	nHeight = parseJson.getMyObjectHeight(chFileName);

	return nHeight;
}

float Item::getX(const char* chFileName)
{
	float fX;
	fX = parseJson.getMyObjectX(chFileName);

	return fX;
}

float Item::getY(const char* chFileName)
{
	float fY;
	fY = parseJson.getMyObjectY(chFileName);

	return fY;
}

RECT& Item::getItemRECT(float fX, float fY)
{
	/*
	ItemRECT.left = fX + 20;
	ItemRECT.top = fY + 20;
	ItemRECT.right = ItemRECT.left + BitmapWidth - 20;
	ItemRECT.bottom = ItemRECT.top + BitmapHeight - 20;

	*/
	return ItemRECT;
	
}
