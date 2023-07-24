#pragma once
#include "SingletonBase.h"

class UIManager : public SingletonBase<UIManager>
{
private:
	
	int _upCnt;
	int _upIdx;

	int _enterCnt;
	int _enterIdx;

	int _ECnt;
	int _EIdx;

	int _lowHPCnt;
	int _lowHpX;
	int _lowHpY;
	int _lowHpWidth;
	int _lowHpHeight;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void btnUPRender(HDC hdc);
	void btnUPAnim();
	

	void txtRender(HDC hdc, string key);
	void btnEnterRender(HDC hdc, string key);
	void btnEndterAnim();

	void btnERender(HDC hdc);
	void btnEAnim();

	void panalHpRender(HDC hdc);
	void lowHpUpdate();
	void lowHpRender(HDC hdc);

	
};

