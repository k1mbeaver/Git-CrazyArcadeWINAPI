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
	// 타이머 재서 DeleteBomb 사용
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
	// 여기서 메모리 관리 어떻게 할건지?
	myBomb.erase(myBomb.begin());
	myBomb.shrink_to_fit();
}