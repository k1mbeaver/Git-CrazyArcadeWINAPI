#include "myJson.h"

void myJson::Initialize()
{
	ifstream ist("Image\\ImageLink.json");
	for (char chP; ist >> chP;)
		str += chP;

	parsingRet = reader.parse(str, root);

}

string& myJson::getMyObjectLink(const char* chFileName)
{
	strObject = "\0";

	Json::Value myobject = root[chFileName];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		strObject = (*it)["ImageLink"].asString();
	}

	return strObject;
}

int myJson::getMyObjectWidth(const char* chFileName)
{
	nObject = 0;

	Json::Value myobject = root[chFileName];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		nObject = (*it)["Width"].asInt();
	}

	return nObject;
}

int myJson::getMyObjectHeight(const char* chFileName)
{
	nObject = 0;

	Json::Value myobject = root[chFileName];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		nObject = (*it)["Height"].asInt();
	}

	return nObject;
}

float myJson::getMyObjectX(const char* chFileName)
{
	fObject = 0;

	Json::Value myobject = root[chFileName];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		fObject = (*it)["LocateX"].asFloat();
	}

	return fObject;

}

float myJson::getMyObjectY(const char* chFileName)
{
	fObject = 0;

	Json::Value myobject = root[chFileName];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		fObject = (*it)["LocateY"].asFloat();
	}

	return fObject;
}

int myJson::getMyObjectBottomRect(const char* chFileName)
{
	nObject = 0;

	Json::Value myobject = root[chFileName];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		nObject = (*it)["BottomRect"].asInt();
	}

	return nObject;
}

int myJson::getMyObjectTopRect(const char* chFileName)
{
	nObject = 0;

	Json::Value myobject = root[chFileName];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		nObject = (*it)["TopRect"].asInt();
	}

	return nObject;
}

int myJson::getMyObjectBetweenX(const char* chFileName)
{
	nObject = 0;

	Json::Value myobject = root[chFileName];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		nObject = (*it)["BetweenX"].asInt();
	}

	return nObject;
}

int myJson::getMyObjectBetweenY(const char* chFileName)
{
	nObject = 0;

	Json::Value myobject = root[chFileName];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		nObject = (*it)["BetweenY"].asInt();
	}

	return nObject;
}

float myJson::getMyObjectX2(const char* chFileName)
{
	fObject = 0;

	Json::Value myobject = root[chFileName];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		fObject = (*it)["LocateX2"].asFloat();
	}

	return fObject;

}

float myJson::getMyObjectY2(const char* chFileName)
{
	fObject = 0;

	Json::Value myobject = root[chFileName];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		fObject = (*it)["LocateY2"].asFloat();
	}

	return fObject;
}

// 맵에 있는 블럭의 존재유무
bool myJson::getMapExist(int nCount)
{
	string strNumber;
	const char* chNumber;
	strNumber = to_string(nCount);
	chNumber = strNumber.c_str();
	boolObject = false;

	Json::Value myobject = root[chNumber];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		boolObject = (*it)["Blockexist"].asBool();
	}

	return boolObject;
}

// 맵 블럭의 X 좌표
float myJson::getMapX(int nCount)
{
	string strNumber;
	const char* chNumber;
	strNumber = to_string(nCount);
	chNumber = strNumber.c_str();
	fObject = 0;

	Json::Value myobject = root[chNumber];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		fObject = (*it)["LocateX"].asFloat();
	}

	return fObject;
}

// 맵 블럭의 Y좌표
float myJson::getMapY(int nCount)
{
	string strNumber;
	const char* chNumber;
	strNumber = to_string(nCount);
	chNumber = strNumber.c_str();
	fObject = 0;

	Json::Value myobject = root[chNumber];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		fObject = (*it)["LocateY"].asFloat();
	}

	return fObject;
}

// 맵 블럭의 파괴 여부
bool myJson::getMapBreak(int nCount)
{
	string strNumber;
	const char* chNumber;
	strNumber = to_string(nCount);
	chNumber = strNumber.c_str();
	boolObject = false;

	Json::Value myobject = root[chNumber];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		boolObject = (*it)["Break"].asBool();
	}

	return boolObject;
}

int myJson::getMapWidth(int nCount)
{
	string strNumber;
	const char* chNumber;
	strNumber = to_string(nCount);
	chNumber = strNumber.c_str();
	nObject = 0;

	Json::Value myobject = root[chNumber];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		nObject = (*it)["Width"].asInt();
	}

	return nObject;
}

int myJson::getMapHeight(int nCount)
{
	string strNumber;
	const char* chNumber;
	strNumber = to_string(nCount);
	chNumber = strNumber.c_str();
	nObject = 0;

	Json::Value myobject = root[chNumber];

	for (Json::ValueIterator it = myobject.begin(); it != myobject.end(); it++)
	{
		nObject = (*it)["Height"].asInt();
	}

	return nObject;
}

// 이제 BackGround 클래스에서 저것들을 이용하여 Json을 읽어서 Image* 2차원 배열에 넣든지 어떻게든 Initialize에서 설정을 하고 읽어와서 출력하는 것으로
/*
string myJson::getObjectLink()
{
}
*/