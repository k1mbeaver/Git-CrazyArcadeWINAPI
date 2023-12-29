//충돌 처리
#pragma once
#include "stdafx.h"
#include "Define.h"

extern RECT rcInter;

class Collison
{
private:
public:
	void Initialize() {};
	void Progress();
	void Render() {};
	Direction SetNotCharacter(RECT& pRect, RECT pHold); // 사각형 끼리 교차되지 않게 셋팅, 캐릭터용
	Direction SetNotInterSect(RECT pRect, RECT pHold); // 나머지
};