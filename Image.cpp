#include "Image.h"

Image::Image()
{
	parseJson.Initialize();
}

HRESULT Image::Initialize(string m_strFileName, int m_nWidth, int m_nHeight, float m_fX, float m_fY, bool m_isTrans)
{
	HDC hdc = GetDC(g_hWnd);
	const char* chFileName = m_strFileName.c_str();

	imageInformation = new IMAGE_INFO;
	imageInformation -> hMemDC = CreateCompatibleDC(hdc); 
	imageInformation -> hBit = (HBITMAP)LoadImage(hInst, parseJson.getMyObjectLink(chFileName).c_str(), IMAGE_BITMAP, m_nWidth, m_nHeight, LR_LOADFROMFILE); // 이부분부터 문제가 있음
	imageInformation -> hObit = (HBITMAP)SelectObject(imageInformation -> hMemDC, imageInformation -> hBit);
	imageInformation -> nWidth = m_nWidth;
	imageInformation -> nHeight = m_nHeight;
	imageInformation -> fX = m_fX;
	imageInformation -> fY = m_fY;

	// 파일 이름
	strFileName = m_strFileName;

	// transparent 설정
	isTrans = m_isTrans;

	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

void Image::Render(HDC hdc, float fX, float fY)
{
	// isTrans = true
	if (isTrans)
	{
		TransparentBlt(
			hdc, 
			fX, 
			fY, 
			imageInformation -> nWidth, 
			imageInformation -> nHeight, 
			imageInformation -> hMemDC, 
			0, 
			0, 
			imageInformation -> nWidth,
			imageInformation -> nHeight,
			RGB(255, 0, 255));
	}

	// isTrans = false
	else
	{
		BitBlt(hdc, fX, fY, imageInformation -> nWidth, imageInformation -> nHeight, imageInformation -> hMemDC, 0, 0, SRCCOPY);
	}
}