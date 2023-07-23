#include "Stdafx.h"
#include "Zombiebot.h"

HRESULT Zombiebot::init(void)
{
	
	_dmg = 10;
	_isDie = false;
	//

	_Scnt = 0;
	_Sidx = 0;
	_Wcnt = 0;
	_Widx = 0;
	_Mcnt = 0;
	_Midx = 0;
	_MYidx = 0;
	_state = 0;
	_go = false;
	_isWake = false;
	_isLeft = false;
	//_rc = RectMake(200, 670, 100, 100);
	

	return S_OK;
}

void Zombiebot::release(void)
{

}

void Zombiebot::UpdateZombie(void)
{
	if (!_isDie)
	{
		switch (_state)
		{
		case 0:
			sleep();
			break;
		case 1:
			wake();
			break;
		case 2:
			move();
			break;
		}
	}
	_Range = RectMakeCenter(_rc.left+30 , _rc.top, 800, 100);

}

void Zombiebot::render()
{

	if (!_isDie)
	{
		switch (_state)
		{
		case 0:
			IMAGEMANAGER->frameRender("좀비정지", getMemDC(), _rc.left, _rc.top);
			break;
		case 1:
			IMAGEMANAGER->frameRender("좀비기상", getMemDC(), _rc.left, _rc.top);
			break;
		case 2:
			if (!_isLeft)
			{			
				IMAGEMANAGER->frameRender("좀비이동", getMemDC(), _rc.left, _rc.top - 30,_Midx, _MYidx);
			}
			else 
			{			
				IMAGEMANAGER->frameRender("좀비이동", getMemDC(), _rc.left, _rc.top - 30, _Midx, _MYidx);
			}
			break;
		}
	}
	

}



void Zombiebot::sleep()
{	
	_Scnt++;
	if (_Scnt % 20 == 0)
	{
		_Sidx++;
		if (_Sidx > 2)
		{
			_Scnt = 0;
			_Sidx = 0;
		}
		IMAGEMANAGER->findImage("좀비정지")->setFrameX(_Sidx);
	}
}

void Zombiebot::wake()
{
	_Wcnt++;
	
	if (_Wcnt % 19 == 0)
	{
		_Widx++;
		
		if (_Widx > 2)
		{
			_Wcnt = 0;
			_Widx = 0;
		//	_isWake = true;

			_state = 2;
			
		}
		IMAGEMANAGER->findImage("좀비기상")->setFrameX(_Widx);
	}

	
}

void Zombiebot::move()
{
	if (_isLeft)
	{
		_Mcnt++;
		_MYidx = 1;
		if (_Mcnt % 20 == 0)
		{
			
			_Midx--;
			if (_Midx < 0)
			{
				_Mcnt = 0;
				_Midx = 4;
			}
		}

	}

	else
	{
		_Mcnt++;
		_MYidx = 0;
		if (_Mcnt % 20 == 0)
		{
			_Midx++;
			if (_Midx > 4)
			{
				_Mcnt = 0;
				_Midx = 0;
			}
		}
	}
}
