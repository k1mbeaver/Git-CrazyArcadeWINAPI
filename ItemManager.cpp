#include "ItemManager.h"

ItemManager::ItemManager() {}

ItemManager::~ItemManager()
{
	// 소멸자에서는 생성했던 Item 클래스들을 free 시켜준다.
	for (int nIndex = 0; nIndex < myItem.size(); nIndex++)
	{
		delete myItem[nIndex];
	}
}

void ItemManager::Initialize(HDC hdc)
{
	parseJson.Initialize();

	// 랜덤으로 값을 넣어준다 (좌표, 종류)
	for (int nIndex = 0; nIndex < parseJson.getMapItemCount("mapitem"); nIndex++)
	{
		// 여기서 Item 클래스를 동적 생성해서
		Item* newItem = new Item;
		int myRandom = GetRandomPosition();

		// 만약에 블럭 정보를 불러와서 블럭이 있으면
		CheckRandomPosition(myRandom);

		newItem->ItemX = parseJson.getMapX(myRandom);
		newItem->ItemY = parseJson.getMapY(myRandom);
		newItem->Initialize(hdc, GetRandomType());

		// 배열에 넣어준다
		myItem.push_back(newItem);
	}
}

void ItemManager::Progress()
{

}

void ItemManager::Render(HDC hdc)
{
	for (int nIndex = 0; nIndex < myItem.size(); nIndex++)
	{
		myItem[nIndex]->Render(hdc);
	}
}

int ItemManager::RandomTransform(int max, int min)
{
	std::random_device rd;
	std::mt19937_64 rEngine(rd());
	std::uniform_int_distribution<>dist(min, max);
	return static_cast<int>(dist(rEngine));
}

int ItemManager::GetRandomPosition()
{
	int nDestination;
	nDestination = RandomTransform(215, 0);

	return nDestination;
}

int ItemManager::GetRandomType()
{
	int nDestinationType;
	nDestinationType = RandomTransform(3, 0);

	return nDestinationType;
}

void ItemManager::CheckRandomPosition(int& nRandom)
{
	if (parseJson.getMapExist(nRandom))
	{
		nRandom = GetRandomPosition();
		CheckRandomPosition(nRandom);
	}

	else
	{
		return;
	}
}