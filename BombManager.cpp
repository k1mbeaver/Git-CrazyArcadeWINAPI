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

}

void BombManager::Progress()
{
	// Ÿ�̸� �缭 DeleteBomb ���
}

void BombManager::CreateBomb(float PlayerX, float PlayerY, int nLength)
{
	Bomb* newBomb = new Bomb;

	newBomb->myCreateBomb.fX = PlayerX;
	newBomb->myCreateBomb.fY = PlayerY;
	newBomb->myCreateBomb.myExist = true;

	myBomb.push_back(newBomb);
}

void BombManager::DeleteBomb()
{
	delete myBomb[0];
	// ���⼭ �޸� ���� ��� �Ұ���?
	//myBomb.pop();
}