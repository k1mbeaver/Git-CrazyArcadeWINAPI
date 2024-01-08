#include "BombManager.h"

BombManager::BombManager() {}
BombManager::~BombManager() 
{
	for (int nIndex = 0; nIndex < myBomb.size(); nIndex++)
	{
		delete myBomb[nIndex];
	}
}

void BombManager::Initialize(HDC hdc)
{
	parseJson.Initialize();
}

void BombManager::Render(HDC hdc)
{
	if (!myBomb.empty())
	{
		for (int nIndex = 0; nIndex < myBomb.size(); nIndex++)
		{
			myBomb[nIndex]->Render(hdc);
		}
	}
}

void BombManager::Progress()
{
	// Ÿ�̸� �缭 DeleteBomb ���
	if (!myBomb.empty())
	{
		for (int nIndex = 0; nIndex < myBomb.size(); nIndex++)
		{
			if (myBomb[nIndex]->Progress() == false)
			{
				DeleteBomb();
			}
		}
	}
}

void BombManager::CreateBomb(float PlayerX, float PlayerY, int nLength, HDC hdc)
{
	Bomb* newBomb = new Bomb;

	newBomb->Initialize(hdc);
	newBomb->myCreateBomb.fX = PlayerX;
	newBomb->myCreateBomb.fY = PlayerY;
	newBomb->myCreateBomb.myExist = true;

	myBomb.push_back(newBomb);
}

void BombManager::DeleteBomb()
{
	delete myBomb[0];
	// ���⼭ �޸� ���� ��� �Ұ���?
	myBomb.erase(myBomb.begin());
	myBomb.shrink_to_fit();
}