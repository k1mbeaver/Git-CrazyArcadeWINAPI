#pragma once
#include "stdafx.h"
#pragma warning(disable : 4996)

class myJson
{
private:
public:
	string str;
	string strObject;
	int nObject;
	float fObject;
	bool boolObject;
	bool parsingRet;
	Json::Reader reader;
	Json::Value root;

	void Initialize();
	string& getMyObjectLink(const char* chFileName);
	int getMyObjectWidth(const char* chFileName);
	int getMyObjectHeight(const char* chFileName);
	float getMyObjectX(const char* chFileName);
	float getMyObjectY(const char* chFileName);
	float getMyObjectX2(const char* chFileName);
	float getMyObjectY2(const char* chFileName);
	int getMyObjectBottomRect(const char* chFileName);
	int getMyObjectTopRect(const char* chFileName);
	int getMyObjectBetweenX(const char* chFileName);
	int getMyObjectBetweenY(const char* chFileName);
	bool getMapExist(int nCount); // 블럭의 존재 유무 불러오기
	float getMapX(int nCount); // 블럭의 X좌표 불러오기
	float getMapY(int nCount); // 블럭의 Y좌표 불러오기
	bool getMapBreak(int nCount); // 블럭의 파괴여부 불러오기
	int getMapWidth(int nCount); // 블럭의 너비 불러오기
	int getMapHeight(int nCount); // 블럭의 높이 불러오기

	//string getObjectLink();
};