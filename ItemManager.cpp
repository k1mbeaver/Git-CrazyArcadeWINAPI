#include "ItemManager.h"

ItemManager::ItemManager() {}
ItemManager::~ItemManager() {}

void ItemManager::Initialize(HDC hdc)
{

}

int ItemManager::RandomTransform(int max, int min)
{
	std::random_device rd;
	std::mt19937_64 rEngine(rd());
	std::uniform_int_distribution<>dist(min, max);
	return static_cast<int>(dist(rEngine));
}

int ItemManager::GetRandomX()
{
	int nDestinationX;
	nDestinationX = RandomTransform(0, 1000);

	return nDestinationX;
}

int ItemManager::GetRandomY()
{
	int nDestinationY;
	nDestinationY = RandomTransform(0, 1000);

	return nDestinationY;
}

