#pragma once
#include "Image.h"
#include "myJson.h"

class ImageManager
{
private:
	map<string, Image*> ImageList;
	myJson parseJson;
public:
	ImageManager();
	~ImageManager();

	//Initialize
	HRESULT Initialize();
	Image* findImage(string strKey);
	Image* addImage(string strKey, int nHeight, int nWidth, float fX, float fY, bool isTrans);
	void Render(string strKey, HDC hdc);
	void Render(string strKey, HDC hdc, float fX, float fY);

	void release();
};