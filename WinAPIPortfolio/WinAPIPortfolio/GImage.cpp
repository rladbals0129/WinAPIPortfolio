#include "Stdafx.h"
#include "GImage.h"


GImage::GImage() :_imageInfo(nullptr),
_fileName(nullptr),
_isTrans(false),
_transColor(RGB(0, 0, 0)),
_blendImage(NULL)
{


}

HRESULT GImage::init(int width, int height) 
{
	if (_imageInfo != nullptr) this->release(); 

	HDC hdc = GetDC(_hWnd); 

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); 
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = nullptr; 

	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	
	if (_imageInfo->hBit == 0) 
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = nullptr;

	_isTrans = isTrans;
	_transColor = transColor;


	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT GImage::init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new char[len + 1];
	strcpy_s(_fileName, len += 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어 오는데 실패했다.
	if (_imageInfo->hBit == 0)
	{
		release(); cout << "false" << endl;
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}



HRESULT GImage::init(const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); 
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); 
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	
	if (_imageInfo->hBit == 0) 
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT GImage::init(const char * fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	int len = strlen(fileName);
	_fileName = new char[len + 1];

	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;


	if (_imageInfo->hBit == 0) 
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;

	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); 
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); 
	_imageInfo->hObit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit); 
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	int len = strlen(fileName);
	_fileName = new char[len + 1];
	
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0) 
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT GImage::initForAlphaBlend(void)	
{
	HDC hdc = GetDC(_hWnd);



	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	
	_blendFunc.BlendOp = AC_SRC_OVER;	

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc); 
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hObit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit); 
	_blendImage->width = WINSIZE_X;
	_blendImage->height = WINSIZE_Y;

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

void GImage::setTransColor(bool isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}


void GImage::release(void)
{
	
	if (_imageInfo)
	{
		
		SelectObject(_imageInfo->hMemDC, _imageInfo->hObit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

	
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		
		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hObit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_blendImage);
	}
}

void GImage::render(HDC hdc)
{
	if (_isTrans)
	{
		
		GdiTransparentBlt
		(
			hdc,							
			0,								
			0,								
			_imageInfo->width,				
			_imageInfo->height,				
			_imageInfo->hMemDC,				
			0, 0,							
			_imageInfo->width,				
			_imageInfo->height,				
			_transColor						
		);
	}

	else
	{
		
		
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void GImage::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		
		GdiTransparentBlt
		(
			hdc,							
			destX,							
			destY,							
			_imageInfo->width,				
			_imageInfo->height,				
			_imageInfo->hMemDC,				
			0, 0,							
			_imageInfo->width,				
			_imageInfo->height,				
			_transColor						
		);
	}

	else
	{
		
		
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void GImage::render(HDC hdc, int destX, int destY, int destWidth, int destHight)
{
	if (_isTrans)
	{
		
		GdiTransparentBlt
		(
			hdc,					
			destX,					
			destY,					
			destWidth,				
			destHight,				
			_imageInfo->hMemDC,		
			0, 0,
			_imageInfo->width,		
			_imageInfo->height,		
			_transColor				
		);
	}

	else
	{
		
		BitBlt(hdc, destX, destY, destWidth, destHight, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}

}

void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight)
{												
	if (_isTrans)
	{
	
		GdiTransparentBlt
		(
			hdc,					
			destX,					
			destY,					
			sourWidth,				
			sourHight,				
			_imageInfo->hMemDC,		
			sourX, sourY,			
			sourWidth,				
			sourHight,				
			_transColor				
		);
	}
	else
	{
		BitBlt(hdc, destX, destY, sourWidth, sourHight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, int destWidth, int destHight)
{
	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,					
			destX,					
			destY,					
			destWidth,				
			destHight,				
			_imageInfo->hMemDC,		
			sourX, sourY,			
			sourWidth,				
			sourHight,				
			_transColor				
		);
	}
	else
	{
	
		BitBlt(hdc, destX, destY, destWidth, destHight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void GImage::alphaRender(HDC hdc, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			0, 0,
			SRCCOPY
		); 


		GdiTransparentBlt
		(

			_blendImage->hMemDC,			
			0, 0,							
			_imageInfo->width,				
			_imageInfo->height,				
			_imageInfo->hMemDC,				
			0, 0,							
			_imageInfo->width,				
			_imageInfo->height,				
			_transColor
		);

	
		AlphaBlend
		(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);

	}
	else
	{
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}

}
void GImage::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			destX, destY,
			SRCCOPY
		); 


		GdiTransparentBlt
		(

			_blendImage->hMemDC,			
			0, 0,							
			_imageInfo->width,				
			_imageInfo->height,				
			_imageInfo->hMemDC,				
			0, 0,							
			_imageInfo->width,				
			_imageInfo->height,				
			_transColor
		);

		
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);

	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}


}

void GImage::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			sourWidth,
			sourHight,
			hdc,
			destX, destY,
			SRCCOPY
		); 

	

		GdiTransparentBlt
		(

			_blendImage->hMemDC,	
			0, 0,					
			sourWidth,				
			sourHight,				
			_imageInfo->hMemDC,		
			sourX, sourY,			
			sourWidth,				
			sourHight,				
			_transColor
		);

		
		AlphaBlend
		(
			hdc,
			destX, destY,
			sourWidth,
			sourHight,
			_blendImage->hMemDC,
			0, 0,
			sourWidth,
			sourHight,
			_blendFunc
		);

	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHight, _blendFunc);
	}
}
void GImage::alphaRender(HDC hdc, int destX, int destY, int destWidth, int destHight, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha)
{

	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			destWidth,
			destHight,
			hdc,
			destX, destY,
			SRCCOPY
		); 

	

		GdiTransparentBlt
		(

			_blendImage->hMemDC,	
			0, 0,					
			destWidth,				
			destHight,				
			_imageInfo->hMemDC,		
			sourX, sourY,			
			sourWidth,				
			sourHight,				
			_transColor
		);

	
		AlphaBlend
		(
			hdc,
			destX, destY,
			destWidth,
			destHight,
			_blendImage->hMemDC,
			0, 0,
			destWidth,
			destHight,
			_blendFunc
		);

	}
	else
	{
		AlphaBlend(hdc, destX, destY, destWidth, destHight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHight, _blendFunc);
	}


}
void GImage::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{

		GdiTransparentBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,			
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX* _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}
void GImage::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{//이미지 예외처리
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans)
	{

		GdiTransparentBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX* _imageInfo->frameWidth,			
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			 
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX* _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void GImage::frameAlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		// 1. 출력해야 할 DC에 그려져 있는 내용을 블렌드 이미지에 그린다. (복사)
		BitBlt
		(
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			hdc,
			destX,
			destY,
			SRCCOPY
		);

		// 2. 원본 이미지의 배경을 없앤 후 블렌드 이미지에 그린다.
		GdiTransparentBlt
		(
			_blendImage->hMemDC,                                        // 복사할 장소의 DC (화면 DC)
			0, 0,                                                       // 복사될 좌표 시작
			_imageInfo->frameWidth,                                     // 복사될 이미지 가로 크기
			_imageInfo->frameHeight,                                    // 복사될 이미지 세로 크기
			_imageInfo->hMemDC,                                         // 복사될 대상 메모리 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,         // 복사 시작지점 X
			_imageInfo->currentFrameY * _imageInfo->frameHeight,        // 복사 시작지점 Y
			_imageInfo->frameWidth,                                     // 복사 영역 가로 크기
			_imageInfo->frameHeight,                                    // 복사 영역 세로 크기
			_transColor                                                 // 복사할 때 제외할 색상 (마젠타)
		);


		// 3. 블렌드 이미지를 화면에 그린다.
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc
		);
	}

	else
	{
		AlphaBlend(hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc);
	}
}

void GImage::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	// 알파블렌드를 처음 사용하면 초기화
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	// 이미지 예외처리
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans)
	{
		// 1. 출력해야 할 DC에 그려져 있는 내용을 블렌드 이미지에 그린다. (복사)
		BitBlt
		(
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			hdc,
			destX,
			destY,
			SRCCOPY
		);

		// 2. 원본 이미지의 배경을 없앤 후 블렌드 이미지에 그린다.
		GdiTransparentBlt
		(
			_blendImage->hMemDC,                                        // 복사할 장소의 DC (화면 DC)
			0, 0,                                                       // 복사될 좌표 시작
			_imageInfo->frameWidth,                                     // 복사될 이미지 가로 크기
			_imageInfo->frameHeight,                                    // 복사될 이미지 세로 크기
			_imageInfo->hMemDC,                                         // 복사될 대상 메모리 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,         // 복사 시작지점 X
			_imageInfo->currentFrameY * _imageInfo->frameHeight,        // 복사 시작지점 Y
			_imageInfo->frameWidth,                                     // 복사 영역 가로 크기
			_imageInfo->frameHeight,                                    // 복사 영역 세로 크기
			_transColor                                                 // 복사할 때 제외할 색상 (마젠타)
		);


		// 3. 블렌드 이미지를 화면에 그린다.
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc
		);
	}

	else
	{
		AlphaBlend(hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc);
	}
}



void GImage::camRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{	
	RECT rcSour; // 소스 이미지 영역
	int sourWidth; // 소스 이미지의 너비
	int sourHeight; // 소스 이미지의 높이

	RECT rcDest; // 출력될 화면 영역

	int drawAreaX = drawArea->left; // 그려져야 할 전체 영역의 왼쪽 좌표
	int drawAreaY = drawArea->top; // 그려져야 할 전체 영역의 상단 좌표
	int drawAreaW = drawArea->right - drawArea->left; // 전체 영역의 너비
	int drawAreaH = drawArea->bottom - drawArea->top; // 전체 영역의 높이

	for (int y = 0; y < drawAreaH; y += sourHeight) // 세로 루프: 화면 영역 높이까지 반복
	{
		rcSour.top = (y + offsetY) % _imageInfo->height; // 소스 이미지 영역의 위쪽 좌표 계산
		rcSour.bottom = _imageInfo->height; // 소스 이미지 영역의 아래쪽 좌표
		sourHeight = rcSour.bottom - rcSour.top; // 소스 이미지 영역의 높이 계산

		if (y + sourHeight > drawAreaH) // 소스 영역이 화면 영역을 넘어갔을 경우
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH; // 소스 영역 보정
			sourHeight = rcSour.bottom - rcSour.top; // 보정된 소스 이미지 영역의 높이
		}

		rcDest.top = y + drawAreaY; // 출력 화면 영역의 위쪽 좌표
		rcDest.bottom = rcDest.top + sourHeight; // 출력 화면 영역의 아래쪽 좌표 설정

		for (int x = 0; x < drawAreaW; x += sourWidth) // 가로 루프: 화면 영역 너비까지 반복
		{
			rcSour.left = (x + offsetX) % _imageInfo->width; // 소스 이미지 영역의 왼쪽 좌표 계산
			rcSour.right = _imageInfo->width; // 소스 이미지 영역의 오른쪽 좌표 설정
			sourWidth = rcSour.right - rcSour.left; // 소스 이미지 영역의 너비 계산

			if (x + sourWidth > drawAreaW) // 소스 영역이 화면 영역을 넘어갔을 경우
			{
				rcSour.right -= (x + sourWidth) - drawAreaW; // 소스 영역 보정
				sourWidth = rcSour.right - rcSour.left; // 보정된 소스 이미지 영역의 너비
			}

			rcDest.left = x + drawAreaX; // 출력 화면 영역의 왼쪽 좌표
			rcDest.right = rcDest.left + sourWidth; // 출력 화면 영역의 오른쪽 좌표 설정

			render(hdc, rcDest.left, rcDest.top, // 이미지를 출력하는 render 함수 호출
				rcSour.left, rcSour.top,
				sourWidth, sourHeight);
		}
	}


}
