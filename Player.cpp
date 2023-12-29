#include "Player.h"
Player::Player() {}
Player::~Player() {}

void Player::Initialize(HDC hdc)
{
	myXY.myX = 500;
	myXY.myY = 500;

	// Initialize���� �� �̹������� ������ ������ ������?

	parseJson.Initialize();
	myDC = CreateCompatibleDC(hdc);
	Downbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("BazziDown").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	Upbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("BazziUp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	Leftbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("BazziLeft").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	Rightbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("BazziRight").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	Jumpbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("BazziJump").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	Trapbit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("BazziTrap").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	Diebit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("BazziDie").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void Player::Progress()
{
	if (bMove)
	{
		switch (nPlayerWay)
		{
		case VK_LEFT:
			myXY.myX -= 5.0f;
			break;
		case VK_UP:
			myXY.myY -= 5.0f;
			break;
		case VK_RIGHT:
			myXY.myX += 5.0f;
			break;
		case VK_DOWN:
			myXY.myY += 5.0f;
			break;
		default:
			break;
		}
	}
}

void Player::Render(HDC hdc, int nPlayerState, int nState) // ���� �÷��� ȭ�� ��
{
	if (nPlayerState == 0) // ����
	{
		if (!bMove)
		{
			switch (nPlayerWay)
			{
			case VK_LEFT:
				Leftold = (HBITMAP)SelectObject(myDC, Leftbit);
				TransparentBlt(hdc, myXY.myX, myXY.myY, getWidth("BazziLeft"), getHeight("BazziLeft"), myDC, 0, 0, getWidth("BazziLeft"), getHeight("BazziLeft"), RGB(255, 0, 255));
				break;
			case VK_UP:
				Upold = (HBITMAP)SelectObject(myDC, Upbit);
				TransparentBlt(hdc, myXY.myX, myXY.myY, getWidth("BazziUp"), getHeight("BazziUp"), myDC, 0, 0, getWidth("BazziUp"), getHeight("BazziUp"), RGB(255, 0, 255));
				break;
			case VK_RIGHT:
				Rightold = (HBITMAP)SelectObject(myDC, Rightbit);
				TransparentBlt(hdc, myXY.myX, myXY.myY, getWidth("BazziRight"), getHeight("BazziRight"), myDC, 0, 0, getWidth("BazziRight"), getHeight("BazziRight"), RGB(255, 0, 255));
				break;
			case VK_DOWN:
				Downold = (HBITMAP)SelectObject(myDC, Downbit);
				TransparentBlt(hdc, myXY.myX, myXY.myY, getWidth("BazziDown"), getHeight("BazziDown"), myDC, 0, 0, getWidth("BazziDown"), getHeight("BazziDown"), RGB(255, 0, 255));
				break;
			case 0:
				Downold = (HBITMAP)SelectObject(myDC, Downbit);
				TransparentBlt(hdc, myXY.myX, myXY.myY, getWidth("BazziDown"), getHeight("BazziDown"), myDC, 0, 0, getWidth("BazziDown"), getHeight("BazziDown"), RGB(255, 0, 255));
				break;
			}
		}

		else
		{
			switch (nPlayerWay)
			{
			case VK_LEFT:
				Leftold = (HBITMAP)SelectObject(myDC, Leftbit);
				TransparentBlt(hdc, myXY.myX, myXY.myY, getWidth("BazziLeft"), getHeight("BazziLeft"), myDC, LRFrameX, 0, getWidth("BazziLeft"), getHeight("BazziLeft"), RGB(255, 0, 255));
				break;
			case VK_UP:
				Upold = (HBITMAP)SelectObject(myDC, Upbit);
				TransparentBlt(hdc, myXY.myX, myXY.myY, getWidth("BazziUp"), getHeight("BazziUp"), myDC, UDFrameX, 0, getWidth("BazziUp"), getHeight("BazziUp"), RGB(255, 0, 255));
				break;
			case VK_RIGHT:
				Rightold = (HBITMAP)SelectObject(myDC, Rightbit);
				TransparentBlt(hdc, myXY.myX, myXY.myY, getWidth("BazziRight"), getHeight("BazziRight"), myDC, LRFrameX, 0, getWidth("BazziRight"), getHeight("BazziRight"), RGB(255, 0, 255));
				break;
			case VK_DOWN:
				Downold = (HBITMAP)SelectObject(myDC, Downbit);
				TransparentBlt(hdc, myXY.myX, myXY.myY, getWidth("BazziDown"), getHeight("BazziDown"), myDC, UDFrameX, 0, getWidth("BazziDown"), getHeight("BazziDown"), RGB(255, 0, 255));
				break;
			}
		}

		// �ִϸ��̼� ����� ���� ������
		fFrameDelay += dDT;
		if (fFrameDelay > 0.1f)
		{
			fFrameDelay = 0;
			UDFrameX += 64;
			LRFrameX += 64;
			if (UDFrameX >= 512)
			{
				UDFrameX = 0;
			}

			if (LRFrameX >= 384)
			{
				LRFrameX = 0;
			}
		}
	}

	else if (nPlayerState == 1) // ����
	{
		if (nDieCount == 0)
		{
			nDieX = myXY.myX;
			nDieY = myXY.myY;
		}


		if (TrapFrameX < 1144)
		{
			Trapold = (HBITMAP)SelectObject(myDC, Trapbit);
			TransparentBlt(hdc, nDieX, nDieY, getWidth("BazziTrap"), getHeight("BazziTrap"), myDC, TrapFrameX, 0, getWidth("BazziTrap"), getHeight("BazziTrap"), RGB(255, 0, 255));
		}

		// �ִϸ��̼� ����� ���� ������
		fFrameDelay += dDT;

		if (fFrameDelay > 0.1f)
		{

			fFrameDelay = 0;
			TrapFrameX += 88;
		}

		if (TrapFrameX >= 1144)
		{
			Dieold = (HBITMAP)SelectObject(myDC, Diebit);
			TransparentBlt(hdc, nDieX, nDieY, getWidth("BazziDie"), getHeight("BazziDie"), myDC, DieFrameX, 0, getWidth("BazziDie"), getHeight("BazziDie"), RGB(255, 0, 255));

			// �ִϸ��̼� ����� ���� ������
			fFrameDelay2 += dDT;
			if (fFrameDelay2 > 0.2f)
			{
				fFrameDelay2 = 0;
				DieFrameX += 88;
			}
		}

		nDieCount++;
	}
}

void Player::Render(HDC hdc, int nState) // �κ��
{
	Jumpold = (HBITMAP)SelectObject(myDC, Jumpbit);
	TransparentBlt(hdc, getX("BazziJump"), getY("BazziJump"), getWidth("BazziJump"), getHeight("BazziJump"), myDC, JumpFrameX, 0, getWidth("BazziJump"), getHeight("BazziJump"), RGB(255, 0, 255));

	fFrameDelay += dDT;
	if (fFrameDelay > 0.5f)
	{
		fFrameDelay = 0;
		JumpFrameX += 64;
		if (JumpFrameX >= 512)
		{
			JumpFrameX = 0;
		}

	}
}

int Player::getWidth(const char* chFileName)
{
	int nWidth;
	nWidth = parseJson.getMyObjectWidth(chFileName);

	return nWidth;
}

int Player::getHeight(const char* chFileName)
{
	int nHeight;
	nHeight = parseJson.getMyObjectHeight(chFileName);

	return nHeight;
}

float Player::getX(const char* chFileName)
{
	float fX;
	fX = parseJson.getMyObjectX(chFileName);

	return fX;
}

float Player::getY(const char* chFileName)
{
	float fY;
	fY = parseJson.getMyObjectY(chFileName);

	return fY;
}

RECT& Player::getPlayerRECT(float fX, float fY)
{
	PlayerRECT.left = fX + 20;
	PlayerRECT.top = fY + 20;
	PlayerRECT.right = PlayerRECT.left + getWidth("BazziDown") - 20;
	PlayerRECT.bottom = PlayerRECT.top + getHeight("BazziDown") - 20;

	return PlayerRECT;
}


// �÷��̾�� ���𰡰� �浹�Ͽ��� �� �����Ű�� �ʰ� �о��
void Player::pushbackPlayer(Direction myDirection)
{
	if (nBanCount == 0)
	{
		fPlayerX = myXY.myX;
		fPlayerY = myXY.myY;
	}
	// ��ȯ ���� ������ ������ ���� ĳ���͸� �о��.
	switch (myDirection)
	{
	case Up:
		myXY.myY -= 2.f;
		break;
	case Down:
		myXY.myY += 2.f;
		break;
	case Right:
		myXY.myX += 2.f;
		break;
	case Left:
		myXY.myX -= 2.f;
	case None:
		break;
	}
}
