// 01. GameCore
#include "GameCore.h"


GameCore::GameCore()
{
}

GameCore::~GameCore()
{
	Release();
}

void GameCore::Initialize()
{
	nCurrent = 0; // 0 = main, 1 = GameStart, 2 = GameMenu, 3 = GameOver
	nPlayerState = 0;
	nBombState = 1;
	myHDC = GetDC(g_hWnd);
	myLogin.Initialize(myHDC);
	myLobby.Initialize(myHDC);
	myBackGround.Initialize(myHDC);
	myPlayer.Initialize(myHDC);
	myShadow.Initialize(myHDC);
	myBlock.Initialize(myHDC);
	myBomb.Initialize(myHDC);
	myWave.Initialize(myHDC);
	myItemManager.Initialize(myHDC);
	myDbBuf.Initialize();
}

void GameCore::Progress()
{
	myPlayer.PlayerMove();

	if (nCurrent == 0)
	{
		nInitNum = myLogin.Progress(nCurrent);
		if (nInitNum == 1)
		{
			myDbBuf.DeleteScreen();
		}
	}
	if (nCurrent == 1)
	{
		nInitNum = myLobby.Progress(nCurrent);
		if (nInitNum == 1)
		{
			myDbBuf.DeleteScreen();
		}
	}

	else if (nCurrent == 2)
	{
		// 블록과 충돌처리
		if (nFrame == 1)
		{
			for (int nIndex = 0; nIndex < 12; nIndex++)
			{
				for (int nJndex = 0; nJndex < 18; nJndex++)
				{
					if (myBlock.getBlockExist(nIndex, nJndex) == true)
					{
						// 블록들과 캐릭터의 충돌
						myPlayer.pushbackPlayer(myCollison.SetNotInterSect(myPlayer.getPlayerRECT(myXY.myX, myXY.myY), myBlock.getBlockRect(nIndex, nJndex)));

						// 블록들과 물줄기의 충돌
						if (nBombCount < 20)
						{
							myBlock.PopBlock(myCollison.SetNotInterSect(myBlock.getBlockRect(nIndex, nJndex), myBomb.getHeightPop()), nIndex, nJndex); // 세로
							myBlock.PopBlock(myCollison.SetNotInterSect(myBlock.getBlockRect(nIndex, nJndex), myBomb.getWidthPop()), nIndex, nJndex); // 가로
						}
					}
				}
			}

			for (int nIndex = 0; nIndex < myItemManager.myItem.size(); nIndex++)
			{
				if (myCollison.SetNotInterSect(myPlayer.getPlayerRECT(myXY.myX, myXY.myY), myItemManager.myItem[nIndex]->getItemRECT()) != None)
				{
					myPlayer.GetItem(myItemManager.myItem[nIndex]->nItemType);
					//int nMyItemType = myItemManager.myItem[nIndex]->nItemType;
					myItemManager.DeleteItem(nIndex);

					break;
				}
			}
			nFrame = 0;
		}

		// 플레이중 스페이스 바를 누르고, 플레이어의 물풍선 갯수가 남아있을 떄
		if (nBomb == VK_SPACE && myPlayer.PlayerBomb != 0)
		{
			myBomb.CreateBomb(myXY.myX, myXY.myY);
			// 버튼 초기화
			nBomb = 0;
			// 물풍선 남은 갯수
			myPlayer.PlayerBomb = 0;
			// 타이머 시작
			nBombCount = 150;
			// 물줄기 프레임 초기화
			myWave.InitializeFrameX();
		}

		// 물줄기와 캐릭터의 충돌처리
		if (nBombCount < 20 && (myCollison.SetNotInterSect(myPlayer.getPlayerRECT(myXY.myX, myXY.myY), myBomb.getHeightPop()) != None 
			|| myCollison.SetNotInterSect(myPlayer.getPlayerRECT(myXY.myX, myXY.myY), myBomb.getWidthPop()) != None)) // 물풍선이 터져서 물줄기가 나올때, 캐릭터가 물줄기의 가로 또는 세로에 충돌시
		{
			nPlayerState = 1; // 플레이어의 속성을 갇힘으로 설정
			nPlayerTrap = 300; // 갇혀있는 시간 카운트 시작
		}

		if (nPlayerState == 1 && nPlayerTrap == 0) // 갇혀있는 상태에서 시간 다되면
		{
			nPlayerState = 2; // 플레이어의 속성을 사망으로 설정
			nCurrent = 3; // 게임 오버 
			nGameOverCount = 300; // 게임 오버 화면 카운트 시작
			myDbBuf.DeleteScreen(); // 화면 초기화
		}

		// 블록 다뿌수고 게임 끝내기
		if (myCollison.SetNotInterSect(myPlayer.getPlayerRECT(myXY.myX, myXY.myY), myBackGround.GameOverRECT()) != None)
		{
			nCurrent = 3;
			nGameOverCount = 300; // 게임 오버 화면 카운트 시작
			myDbBuf.DeleteScreen(); // 화면 초기화
		}
		
		// 타이머 줄이기
		nBombCount--;
		nPlayerTrap--;

		// 충돌 프레임
		nFrame++;
	}

	else if (nCurrent == 3) // 게임 오버
	{
		if (nGameOverCount == 0) // 게임 오버 카운트가 다되면
		{
			myDbBuf.DeleteScreen(); // 화면 초기화
			DestroyWindow(g_hWnd); // 종료
		}
		// 게임 오버 카운트 줄이기
		nGameOverCount--;
	}
}

void GameCore::Render()
{
	if (nCurrent == 0)
	{
		myLogin.Render(myDbBuf.ReturnBackDC());
		//myImageManager.Render("BazziDown1", myDbBuf.ReturnBackDC());
	}

	else if (nCurrent == 1)
	{
		myLobby.Render(myDbBuf.ReturnBackDC());
		myShadow.Render(myDbBuf.ReturnBackDC(), 1);
		myPlayer.Render(myDbBuf.ReturnBackDC(), 1);
	}

	else if (nCurrent == 2)
	{
		myBackGround.Render(myDbBuf.ReturnBackDC());
		myShadow.Render(myDbBuf.ReturnBackDC(), nPlayerState, 1);
		// 물풍선 객체가 존재 할때
		if (nBombState == 0)
		{
			// 물풍선이 터지는 시점
			if (nBombCount < 20)
			{
				myWave.Render(myDbBuf.ReturnBackDC(), myBomb.getX(), myBomb.getY()); // 물줄기 4방향
			}
		}

		myBlock.Render(myDbBuf.ReturnBackDC());

		// 물풍선 객체가 존재 할때
		if (nBombState == 0)
		{
			// 물풍선이 터지기 전
			if (nBombCount > 20)
			{
				myBomb.Render(myDbBuf.ReturnBackDC()); // 물풍선 애니메이션 출력
			}

			// 물풍선이 터지는 시점
			if (nBombCount < 20)
			{
				myBomb.BombRender(myDbBuf.ReturnBackDC()); // 물줄기 가운데
				if (nBombCount == 0)
				{
					myBomb.DeleteBomb(); // 물풍선 초기화
					nBombState = 1; // 물풍선 갯수 1개로 초기화
				}
			}
		}

		myItemManager.Render(myDbBuf.ReturnBackDC());

		myPlayer.Render(myDbBuf.ReturnBackDC(), nPlayerState, 1);
	}

	else if (nCurrent == 3)
	{
		myBackGround.GameOver(myDbBuf.ReturnBackDC());
	}
	myDbBuf.Render();
}

void GameCore::Release()
{
	ReleaseDC(g_hWnd, myHDC);
}