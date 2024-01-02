#include "ItemManager.h"

ItemManager::ItemManager() {}

ItemManager::~ItemManager()
{
	// �Ҹ��ڿ����� �����ߴ� Item Ŭ�������� free �����ش�.
	for (int nIndex = 0; nIndex < myItem.size(); nIndex++)
	{
		delete myItem[nIndex];
	}
}

void ItemManager::Initialize(HDC hdc)
{
	parseJson.Initialize();

	// �������� ���� �־��ش� (��ǥ, ����)
	for (int nIndex = 0; nIndex < parseJson.getMapItemCount("mapitem"); nIndex++)
	{
		// ���⼭ Item Ŭ������ ���� �����ؼ�
		Item* newItem = new Item;
		int myRandom = GetRandomPosition();

		// ���࿡ �� ������ �ҷ��ͼ� ���� ������
		CheckRandomPosition(myRandom);

		newItem->ItemX = parseJson.getMapX(myRandom);
		newItem->ItemY = parseJson.getMapY(myRandom);
		newItem->Initialize(hdc, GetRandomType());

		// �迭�� �־��ش�
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