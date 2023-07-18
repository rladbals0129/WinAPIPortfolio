#include "Stdafx.h"
#include "Title.h"

HRESULT Title::init(void)
{
	PLAYER->init();

	PLAYER->setPlayerPos(610, 325, 685, 400);

	IMAGEMANAGER->findImage("머리")->setY(PLAYER->getPlayerPos().top);
	IMAGEMANAGER->findImage("기본표정")->setY(PLAYER->getPlayerPos().top);
	_arrowCntL = 0;
	_arrowIdxL = 0;
	_arrowCntR = 0;
	_arrowIdxR = 6;
	_StartGame = false;
	for (int i = 0; i < 3; i++)
	{
		_select[i] = RectMake(580, 645+(i*45), 120, 40);
	}
	
	

	return S_OK;
}

void Title::release(void)
{
}

void Title::update(void)
{
	_selectArrowL = RectMake(480, 645 + (_idx * 45), 100, 40);
	_selectArrowR = RectMake(700, 645 + (_idx * 45), 100, 40);
	if (_idx < 2)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_idx++;
		}
	}
	
	if (_idx > 0)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_idx--;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		switch (_idx)
		{
		case 0:
			_StartGame = true;
			
			break;
		case 1:

			break;
		case 2:
			PostQuitMessage(0);
			break;
	
		}
	}

	

	

	PLAYER->idle();
}

void Title::render(void)
{
	IMAGEMANAGER->render("타이틀", getMemDC());
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		for (int i = 0; i < 3; i++)
		{
			DrawRectMake(getMemDC(), _select[i]);
		}
		DrawRectMake(getMemDC(), _selectArrowL);
		DrawRectMake(getMemDC(), _selectArrowR);
	}
	animSelectL();
	IMAGEMANAGER->frameRender("선택", getMemDC(), _selectArrowL.left, _selectArrowL.top);
	animSelectR();
	IMAGEMANAGER->frameRender("선택", getMemDC(), _selectArrowR.left, _selectArrowR.top);
	//PLAYER->setIdle();
	//PLAYER->getState();
	//PLAYER->render(getMemDC());
	PLAYER->titlePlayer(getMemDC());
}

void Title::animSelectR(void)
{

	_arrowCntR++;
	IMAGEMANAGER->findImage("선택")->setFrameY(1);
	if (_arrowCntR % 5 == 0)
	{
		_arrowIdxR--;
		if (_arrowIdxR < 0)
		{
			_arrowIdxR = 6;
			_arrowCntR = 0;
		}
		IMAGEMANAGER->findImage("선택")->setFrameX(_arrowIdxR);
	}

}

void Title::animSelectL(void)
{

		_arrowCntL++;
		IMAGEMANAGER->findImage("선택")->setFrameY(0);
		if (_arrowCntL % 5 == 0)
		{
			_arrowIdxL++;
			if (_arrowIdxL > 6)
			{
				_arrowIdxL = 0;
				_arrowCntL = 0;
			}
			IMAGEMANAGER->findImage("선택")->setFrameX(_arrowIdxL);
		}
	
	
	

}
