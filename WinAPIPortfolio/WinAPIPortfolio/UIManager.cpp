#include "Stdafx.h"
#include "UIManager.h"

HRESULT UIManager::init()
{
	_upCnt = 0;
	_upIdx = 0;
	_enterCnt = 0;
	_enterIdx = 0;
	_ECnt = 0;
	_EIdx = 0;

	_lowHPCnt = 0;
	_lowHpX = 0;
	_lowHpY = 0;
	_lowHpWidth = 1280;
	_lowHpHeight = 800;


	return S_OK;

}

void UIManager::release()
{
	
}

void UIManager::update()
{
}

void UIManager::render()
{
}

void UIManager::btnUPRender(HDC hdc)
{
	IMAGEMANAGER->frameRender("방향키위", hdc, (PLAYER->getPlayerPos().left + PLAYER->getPlayerPos().right) / 2, PLAYER->getPlayerPos().top - 60);
}

void UIManager::btnUPAnim()
{
	_upCnt++;
	if (_upCnt % 24 == 0)
	{
		_upIdx++;

		if (_upIdx > 2)
		{
			_upIdx = 0;
			_upCnt = 0;
		}
		IMAGEMANAGER->findImage("방향키위")->setFrameX(_upIdx);
	}
}

void UIManager::btnEnterRender(HDC hdc, string key)
{
	IMAGEMANAGER->frameRender("엔터키", hdc, IMAGEMANAGER->findImage(key)->getX() + IMAGEMANAGER->findImage(key)->getWidth(),
		IMAGEMANAGER->findImage(key)->getY() + IMAGEMANAGER->findImage(key)->getHeight());
	
}

void UIManager::btnEndterAnim()
{
	_enterCnt++;
	if (_enterCnt % 24 == 0)
	{
		_enterIdx++;

		if (_enterIdx > 2)
		{
			_enterIdx = 0;
			_enterCnt = 0;
		}
		IMAGEMANAGER->findImage("엔터키")->setFrameX(_enterIdx);
	}

	//cout << "cnt : " << _cnt << "idx : " << _idx << endl;
}

void UIManager::btnERender(HDC hdc)
{
	IMAGEMANAGER->frameRender("E키", hdc, (PLAYER->getPlayerPos().left + PLAYER->getPlayerPos().right) / 2 - 10, PLAYER->getPlayerPos().top - 60);
}

void UIManager::btnEAnim()
{
	_ECnt++;
	if (_ECnt % 24 == 0)
	{
		_EIdx++;

		if (_EIdx > 2)
		{
			_EIdx = 0;
			_ECnt = 0;
		}
		IMAGEMANAGER->findImage("E키")->setFrameX(_EIdx);
	}

}

void UIManager::panalHpRender(HDC hdc)
{
	IMAGEMANAGER->render("체력패널", hdc, 0, 5);
	IMAGEMANAGER->render("체력바", hdc, 38, 15,PLAYER->getHp(),29);
	IMAGEMANAGER->render("코인패널", hdc, 0, 53);
	
}

void UIManager::lowHpUpdate()
{
	_lowHPCnt++;
	if (_lowHPCnt % 10 == 0)
	{
		_lowHpX = 20 - _lowHpX;
		_lowHpY = 20 - _lowHpY;
		_lowHpWidth = 1260 - _lowHpWidth;
		_lowHpHeight = 780 - _lowHpHeight;
	}
}

void UIManager::lowHpRender(HDC hdc)
{
	IMAGEMANAGER->render("개피화면", hdc, _lowHpX, _lowHpY, _lowHpWidth, _lowHpHeight);
}

void UIManager::txtRender(HDC hdc, string key)
{
	IMAGEMANAGER->render(key ,hdc ,PLAYER->getPlayerPos().left - 200, PLAYER->getPlayerPos().top - 200);
	IMAGEMANAGER->findImage(key)->setX(PLAYER->getPlayerPos().left - 220);
	IMAGEMANAGER->findImage(key)->setY(PLAYER->getPlayerPos().top - 220);
}



