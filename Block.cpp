#include "Block.h"
Block::Block() {}
Block::~Block()
{
	for (int nIndex = 0; nIndex < 12; nIndex++)
	{
		for (int nJndex = 0; nJndex < 18; nJndex++)
		{
			delete myMap[nIndex][nJndex];
		}
	}
}

void Block::Initialize(HDC hdc)
{
	// 이미지 링크 읽어오기
	parseJson.Initialize();

	// 맵에 있는 블록 정보 가져 오기
	getMapPosition();

	// 빈 DC
	myDC = CreateCompatibleDC(hdc);

	// 블럭이미지들 불러오기
	Block2bit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("block2").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	Block3bit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("block3").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	BlockBreak2bit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("Breakblock2").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BlockBreak2old = (HBITMAP)SelectObject(myDC, BlockBreak2bit);
	BlockBreak3bit = (HBITMAP)LoadImage(NULL, parseJson.getMyObjectLink("Breakblock3").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BlockBreak3old = (HBITMAP)SelectObject(myDC, BlockBreak3bit);
}

void Block::Progress()
{
}

void Block::Render(HDC hdc)
{
	// 블럭 [12][27]까지 다 만들어 보기
	for (int nIndex = 0; nIndex < 12; nIndex++)
	{
		for (int nJndex = 0; nJndex < 18; nJndex++)
		{
			// 블럭이 존재 & 부서지는 블럭
			if (myMap[nIndex][nJndex]->BlockExist == true && myMap[nIndex][nJndex]->BlockBreak == true)
			{
				Block2old = (HBITMAP)SelectObject(myDC, Block2bit);
				TransparentBlt(hdc, myMap[nIndex][nJndex]->fX, myMap[nIndex][nJndex]->fY, myMap[nIndex][nJndex]->nWidth, myMap[nIndex][nJndex]->nHeight
					, myDC, 0, 0, myMap[nIndex][nJndex]->nWidth, myMap[nIndex][nJndex]->nHeight, RGB(255, 0, 255));
			}

			// 블럭이 존재 & 부서지지 않는 블럭
			else if (myMap[nIndex][nJndex]->BlockExist == true && myMap[nIndex][nJndex]->BlockBreak == false)
			{
				Block3old = (HBITMAP)SelectObject(myDC, Block3bit);
				TransparentBlt(hdc, myMap[nIndex][nJndex]->fX, myMap[nIndex][nJndex]->fY, myMap[nIndex][nJndex]->nWidth, myMap[nIndex][nJndex]->nHeight
					, myDC, 0, 0, myMap[nIndex][nJndex]->nWidth, myMap[nIndex][nJndex]->nHeight, RGB(255, 0, 255));
			}

			// 부서지는 애니메이션
			else if (myMap[nIndex][nJndex]->BlockBreak == true && myMap[nIndex][nJndex]->BreakCount == 1)
			{
				BlockBreak2old = (HBITMAP)SelectObject(myDC, BlockBreak2bit);
				TransparentBlt(hdc, myMap[nIndex][nJndex]->fX, myMap[nIndex][nJndex]->fY, myMap[nIndex][nJndex]->nWidth, myMap[nIndex][nJndex]->nHeight
					, myDC, nBreakFrameX, 0, myMap[nIndex][nJndex]->nWidth, myMap[nIndex][nJndex]->nHeight, RGB(255, 0, 255));

				// 애니메이션 출력을 위한 프레임
				PopFrame += dDT;
				if (PopFrame > 0.01f)
				{
					PopFrame = 0;
					nBreakFrameX += 68;

					if (nBreakFrameX >= 340)
					{
						nBreakFrameX = 0;
						myMap[nIndex][nJndex]->BreakCount = 0;
					}
				}
			}
		}
	}
}

int Block::getWidth(const char* chFileName)
{
	int nWidth;
	nWidth = parseJson.getMyObjectWidth(chFileName);

	return nWidth;
}

int Block::getHeight(const char* chFileName)
{
	int nHeight;
	nHeight = parseJson.getMyObjectHeight(chFileName);

	return nHeight;
}

float Block::getX(const char* chFileName)
{
	float fX;
	fX = parseJson.getMyObjectX(chFileName);

	return fX;
}

float Block::getY(const char* chFileName)
{
	float fY;
	fY = parseJson.getMyObjectY(chFileName);

	return fY;
}

float Block::getX2(const char* chFileName)
{
	float fX;
	fX = parseJson.getMyObjectX2(chFileName);

	return fX;
}

float Block::getY2(const char* chFileName)
{
	float fY;
	fY = parseJson.getMyObjectY2(chFileName);

	return fY;
}

int Block::getBetweenX(const char* chFileName)
{
	int nBX;
	nBX = parseJson.getMyObjectBetweenX(chFileName);

	return nBX;
}

int Block::getBetweenY(const char* chFileName)
{
	int nBY;
	nBY = parseJson.getMyObjectBetweenY(chFileName);

	return nBY;
}

void Block::getMapPosition()
{
	// Json 파일에 있는 0~323 까지 들어있는 블럭의 정보들을 myMap[12][27]에 차곡차곡 넣는다.
	int nCount = 0;
	for (int nCount1 = 0; nCount1 < 12; nCount1++)
	{
		for (int nCount2 = 0; nCount2 < 18; nCount2++)
		{
			myMap[nCount1][nCount2] = MapInitialize(parseJson.getMapX(nCount), parseJson.getMapY(nCount),
				parseJson.getMapExist(nCount), parseJson.getMapBreak(nCount), parseJson.getMapWidth(nCount), parseJson.getMapHeight(nCount));
			nCount++;
		}
	}
}

MapInfo* Block::MapInitialize(float m_fX, float m_fY, bool m_BlockExist, bool m_BlockBreak, int m_nWidth, int m_nHeight)
{
	MapPosition* myBlock = new MapPosition;
	myBlock->fX = m_fX;
	myBlock->fY = m_fY;
	myBlock->BlockExist = m_BlockExist;
	myBlock->BlockBreak = m_BlockBreak;
	myBlock->nWidth = m_nWidth;
	myBlock->nHeight = m_nHeight;
	myBlock->BlockRECT.left = myBlock->fX;
	myBlock->BlockRECT.top = myBlock->fY;
	myBlock->BlockRECT.right = myBlock->BlockRECT.left + myBlock->nWidth;
	myBlock->BlockRECT.bottom = myBlock->BlockRECT.top + myBlock->nHeight;

	return myBlock;
}

RECT Block::getBlockRect(int nCount1, int nCount2)
{
	RECT returnRECT;

	returnRECT = myMap[nCount1][nCount2]->BlockRECT;
	return returnRECT;
}

bool Block::getBlockExist(int nCount1, int nCount2)
{
	if (myMap[nCount1][nCount2]->BlockExist == true) return true;
	else { return false; }
}

void Block::PopBlock(Direction myDirection, int nCount1, int nCount2)
{
	// 충돌 반응이 없는 경우
	if (myDirection == None)
	{
		return;
	}

	// 충돌 반응이 있는 경우
	else if (myDirection != None && myMap[nCount1][nCount2]->BlockBreak == true)
	{
		myMap[nCount1][nCount2]->BlockExist = false;
	}
}