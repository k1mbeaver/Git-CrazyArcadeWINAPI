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
	bool getMapExist(int nCount); // ������ ���� ���� �ҷ�����
	float getMapX(int nCount); // ������ X��ǥ �ҷ�����
	float getMapY(int nCount); // ������ Y��ǥ �ҷ�����
	bool getMapBreak(int nCount); // ������ �ı����� �ҷ�����
	int getMapWidth(int nCount); // ������ �ʺ� �ҷ�����
	int getMapHeight(int nCount); // ������ ���� �ҷ�����

	//string getObjectLink();
};