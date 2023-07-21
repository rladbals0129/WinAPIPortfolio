#include "Stdafx.h"
#include "Zombiebot.h"

HRESULT Zombiebot::init(void)
{
	_hp = 3;
	_dmg = 10;
	_isDie = false;
	//

	_Scnt = 0;
	_Sidx = 0;
	_Wcnt = 0;
	_Widx = 0;
	_Mcnt = 0;
	_Midx = 0;
	_state = 0;
	_go = false;
	//_rc = RectMake(200, 670, 100, 100);
	initZombieState();

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
		//sleep();
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
			IMAGEMANAGER->frameRender("좀비이동", getMemDC(), _rc.left, _rc.top);
			break;
		}
	}
	

}

void Zombiebot::initZombieState()
{
	_zombieState.Mcnt = 0;
	_zombieState.Midx = 0;
	_zombieState.isLeft = false;
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
			_state = 2;
			
		}
		IMAGEMANAGER->findImage("좀비기상")->setFrameX(_Widx);
	}

	
}

void Zombiebot::move()
{
	if (_zombieState.isLeft)
	{
		_zombieState.Mcnt++;
		IMAGEMANAGER->findImage("좀비이동")->setFrameY(1);
		if (_zombieState.Mcnt % 20 == 0)
		{
			_zombieState.Midx--;
			if (_zombieState.Midx < 0)
			{
				_zombieState.Mcnt = 0;
				_zombieState.Midx = 4;
			}
			IMAGEMANAGER->findImage("좀비이동")->setFrameX(_zombieState.Midx);
		}
	}

	else
	{
		_zombieState.Mcnt++;
		IMAGEMANAGER->findImage("좀비이동")->setFrameY(0);
		if (_zombieState.Mcnt % 20 == 0)
		{
			_zombieState.Midx++;
			if (_zombieState.Midx > 4)
			{
				_zombieState.Mcnt = 0;
				_zombieState.Midx = 0;
			}
			IMAGEMANAGER->findImage("좀비이동")->setFrameX(_zombieState.Midx);
		}
	}
}
