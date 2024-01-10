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
			if (myBomb[nIndex]->nBombCount == 0)
			{
				if (myBomb[nIndex]->BombRender(hdc) == true)
				{
					DeleteBomb();
				}

				else
				{
					bBoom = true;
				}
			}

			else
			{
				myBomb[nIndex]->Render(hdc);
			}
		}
	}
}

void BombManager::Progress(int& nPlayerBomb)
{
	// 타이머 재서 DeleteBomb 사용
	if (!myBomb.empty())
	{
		for (int nIndex = 0; nIndex < myBomb.size(); nIndex++)
		{
			if (myBomb[nIndex]->Progress() == false)
			{
				nPlayerBomb += 1;
			}
		}
	}
}

void BombManager::CreateBomb(float PlayerX, float PlayerY, int nLength, HDC hdc)
{
	Bomb* newBomb = new Bomb;

	newBomb->Initialize(hdc, PlayerX, PlayerY, nLength);

	myBomb.push_back(newBomb);
}

void BombManager::DeleteBomb()
{
	delete myBomb[0];

	myBomb.erase(myBomb.begin());
	myBomb.shrink_to_fit();

	bBoom = false;
}