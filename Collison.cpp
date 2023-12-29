#include "Collison.h"

// 사각형끼리 충돌시 밀어내기!
Direction Collison::SetNotCharacter(RECT& pRect, RECT pHold) // 캐릭터 전용
{
	// 사각형이 충돌 했다면 if문이 실행되며, rcInter의 값(충돌 영역)이 구해진다.
	if (IntersectRect(&rcInter, &pRect, &pHold))
	{
		// 교차된 영역의 가로 세로 크기를 따진다.
		int nInterW = rcInter.right - rcInter.left;
		int nInterH = rcInter.bottom - rcInter.top;

		// 위아래 체크
		if (nInterW > nInterH)
		{
			// 위에서 충돌
			if (rcInter.top == pHold.top)
			{
				// 충돌 수직 높이만큼 위로 밀어준다.
				//pRect.top -= nInterH;
				//pRect.bottom -= nInterH;
				//myXY.myY -= nInterH;
				return Up;
			}

			// 아래에서 충돌
			if (rcInter.bottom == pHold.bottom)
			{
				// 충돌 수직 높이만큼 아래로 밀어준다.
				//pRect.top += nInterH;
				//pRect.bottom += nInterH;
				//myXY.myY += nInterH;
				return Down;
			}
		}

		// 좌우 체크
		else
		{
			// 왼쪽에서 충돌 시
			if (rcInter.left == pHold.left)
			{
				// 충돌 가로 폭만큼 좌로 밀어준다.
				//pRect.left -= nInterW;
				//pRect.right -= nInterW;
				//myXY.myX -= nInterW;
				return Left;
			}

			else if (rcInter.right == pHold.right)
			{
				// 충돌 가로 폭만큼 우로 밀어 준다.
				//pRect.left += nInterW;
				//pRect.right += nInterW;
				//myXY.myX += nInterW;
				return Right;
			}
		}
	}

	return None;
}

// 사각형끼리 충돌시 밀어내기!
Direction Collison::SetNotInterSect(RECT pRect, RECT pHold) // 나머지
{
	// 사각형이 충돌 했다면 if문이 실행되며, rcInter의 값(충돌 영역)이 구해진다.
	if (IntersectRect(&rcInter, &pRect, &pHold))
	{
		// 교차된 영역의 가로 세로 크기를 따진다.
		int nInterW = rcInter.right - rcInter.left;
		int nInterH = rcInter.bottom - rcInter.top;

		// 위아래 체크
		if (nInterW > nInterH)
		{
			// 위에서 충돌
			if (rcInter.top == pHold.top)
			{
				// 충돌 수직 높이만큼 위로 밀어준다.
				//pRect.top -= nInterH;
				//pRect.bottom -= nInterH;
				//myXY.myY -= nInterH;
				return Up;
			}

			// 아래에서 충돌
			if (rcInter.bottom == pHold.bottom)
			{
				// 충돌 수직 높이만큼 아래로 밀어준다.
				//pRect.top += nInterH;
				//pRect.bottom += nInterH;
				//myXY.myY += nInterH;
				return Down;
			}
		}

		// 좌우 체크
		else
		{
			// 왼쪽에서 충돌 시
			if (rcInter.left == pHold.left)
			{
				// 충돌 가로 폭만큼 좌로 밀어준다.
				//pRect.left -= nInterW;
				//pRect.right -= nInterW;
				//myXY.myX -= nInterW;
				return Left;
			}

			else if (rcInter.right == pHold.right)
			{
				// 충돌 가로 폭만큼 우로 밀어 준다.
				//pRect.left += nInterW;
				//pRect.right += nInterW;
				//myXY.myX += nInterW;
				return Right;
			}
		}
	}

	return None;
}

