#pragma once
#include "stdafx.h"
#include "Define.h"
#include "myJson.h"

extern HWND g_hWnd;
extern HINSTANCE hInst;

class Image
{
	typedef struct tagImage
	{
		HDC hMemDC = NULL; // 메모리 DC
		HBITMAP hBit = NULL; // 비트맵 (새로운 비트맵 핸들)
		HBITMAP hObit = NULL; // 올드 비트맵 (기존 비트맵 핸들)
		float fX = 0; // x좌표
		float fY = 0; // y좌표
		int nWidth = 0; // 가로
		int nHeight = 0; // 세로
		int nCurrentFrameX = 0; // 현재 프레임 X
		int nCurrentFrameY = 0; // 현재 프레임 Y
		int nMaxFrameX = 0; // 최대 프레임 X
		int nMaxFrameY = 0; // 최대 프레임 Y
		int nFrameWidth = 0;
		int nFrameHeight = 0;
	} IMAGE_INFO, *LPIMAGE_INFO;
	LPIMAGE_INFO imageInformation; // 이미지 정보
	string strFileName; // 이미지 경로 이름
	bool isTrans; // TransParent 사용할건지
	myJson parseJson;
public:
	Image();
	~Image();

	//Initialize()
	HRESULT Initialize(string m_strFileName, int nWidth, int nHeight, float fX, float fY, bool m_isTrans);

	//Render()
	void Render(HDC hdc, float fX, float fY);

	// DC를 얻어온다
	HDC getMemDC() { return imageInformation -> hMemDC; }

	// 이미지의 좌표 얻기 및 세팅, 이미지의 센터 좌표 세팅, 이미지의 가로세로 얻기
	
	// 이미지의 좌표 
	float getX() { return imageInformation -> fX; }
	void getX(float fX) { imageInformation -> fX = fX; }
	float getY() { return imageInformation -> fY; }
	void getY(float fY) { imageInformation -> fY = fY; }

	// 이미지의 센터
	void setCenter(float fX, float fY)
	{
		imageInformation -> fX = fX - (imageInformation->nWidth / 2);
		imageInformation -> fY = fY - (imageInformation->nHeight / 2);
	}

	// 중점 X
	float getCenterX()
	{
		return imageInformation -> nMaxFrameX <= 0 ? imageInformation -> fX + (imageInformation -> nWidth / 2) : imageInformation -> fX + (imageInformation -> nFrameWidth / 2);
		/*
		if (imageInformation->nMaxFrameX <= 0) return imageInformation->fX + (imageInformation->nWidth / 2);
		else return imageInformation->fX + (imageInformation->nFrameWidth / 2);
		*/
	}

	// 중점 Y
	float getCenterY()
	{
		return imageInformation -> nMaxFrameY <= 0 ? imageInformation -> fY + (imageInformation -> nHeight / 2) : imageInformation -> fY + (imageInformation -> nFrameHeight / 2);
		/*
		if (imageInformation->nMaxFrameY <= 0) return imageInformation->fY + (imageInformation->nHeight / 2);
		else return imageInformation->fY + (imageInformation->nFrameHeight / 2);
		*/
	}

	// 가로, 세로 크기 얻기
	int getWidth() { return imageInformation -> nWidth; }
	int getHeight() { return imageInformation -> nHeight; }

	// 충돌 처리 (바운딩 박스)
	RECT getBoundingBOX()
	{
		RECT rc;
		if (imageInformation -> nFrameWidth != 0 && imageInformation -> nFrameHeight != 0)
		{
			rc = makeRect(imageInformation -> fX, imageInformation -> fY, imageInformation -> nFrameWidth, imageInformation -> nFrameHeight);
		}

		else
		{
			rc = makeRect(imageInformation -> fX, imageInformation -> fY, imageInformation -> nWidth, imageInformation -> nHeight);
		}
	}

	RECT makeRect(float fX, float fY, int nWidth, int nHeight)
	{
		RECT rc = { fX, fY, fX + nWidth, fY + nHeight };
		return rc;
	}
};