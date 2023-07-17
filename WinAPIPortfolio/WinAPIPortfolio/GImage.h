#pragma once
class GImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0, LOAD_FILE,	//리소스,파일
		LOAD_EMPTY, LOAD_END				// 빈 비트맵, 로드Done
	};

	typedef struct tagImage
	{
		DWORD	 resID;
		HDC		 hMemDC;
		HBITMAP  hBit;
		HBITMAP  hObit;
		float	 x;						//이미지 x좌표
		float	 y;
		int		 width;
		int		 height;
		int		 currentFrameX;			//현재 프레임 x		//
		int		 currentFrameY;			//
		int		 maxFrameX;				//최대 프레임 x 갯수
		int		 maxFrameY;				//
		int		 frameWidth;			//1프레임 가로크기
		int		 frameHeight;
		BYTE	 loadType;


		tagImage()
		{
			resID = 0;
			hMemDC = NULL;		
			hBit = NULL;		
			hObit = NULL;		
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO; 

private:
	LPIMAGE_INFO _imageInfo; 
	char*		 _fileName; 
	bool		 _isTrans;  

	COLORREF	 _transColor; 

	

	BLENDFUNCTION _blendFunc;	//알파블랜드에 대한 기능 (투명)
	LPIMAGE_INFO _blendImage;   // 알파블랜드 이미지  (투명)


public:
	//이미지 너비높이로 초기화
	HRESULT init(int width, int height);

	//이미지 리소스로 초기화									
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));		

	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));



	HRESULT initForAlphaBlend(void);
	//투명 컬러키 세팅
	void setTransColor(bool isTrans, COLORREF transColor);
	//해제
	void release(void);

	//랜더
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY); 
	void render(HDC hdc, int destX, int destY, int destWidth, int destHight);
	//이미지클리핑 (잘라그리기)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, int destWidth, int destHight);

	
	//알파랜더 BYTE 0~255
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int destWidth, int destHight, int sourX, int sourY, int sourWidth, int sourHight, BYTE alpha);


	//===================프레임 랜더=================== 
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//=================루프랜더=====================
	void camRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY); 
	

	// ==인라인함수==
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	//이미지 센터좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}
	//이미지 가로세로크기
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	inline RECT boundimgBox(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height
		};

		return rc;
	}


	//바운딩박스(충돌용렉트)
	inline RECT boundimgBoxWithFrame(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight
		};

		return rc;
	}


	//===프레임에 대한 인라인
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}

	}
	//프레임 x y가 max를 넘어가면 max로 정해준다
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}

	}

	//이미지 1프레임에 대한 가로세로크기
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }

	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//최대 프레임 xy 갯수
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }

	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }





	GImage(); 
	~GImage() {}
};


