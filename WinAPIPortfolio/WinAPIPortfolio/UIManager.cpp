#include "Stdafx.h"
#include "UIManager.h"

HRESULT UIManager::init()
{
	_upCnt = 0;
	_upIdx = 0;
	_enterCnt = 0;
	_enterIdx = 0;
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

void UIManager::txtRender(HDC hdc, string key)
{
	IMAGEMANAGER->render(key ,hdc ,PLAYER->getPlayerPos().left - 200, PLAYER->getPlayerPos().top - 200);
	IMAGEMANAGER->findImage(key)->setX(PLAYER->getPlayerPos().left - 220);
	IMAGEMANAGER->findImage(key)->setY(PLAYER->getPlayerPos().top - 220);
}



