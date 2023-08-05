#include "Stdafx.h"
#include "Lipo.h"

HRESULT Lipo::init(void)
{
	_isLeft = true;
	_dmg = 50;
	return S_OK;
}

void Lipo::release(void)
{

}

void Lipo::UpdateLipo(void)
{
	if (_boomStart )
	{
		if (!_once)
		{
			_breakStartX = (_rc.left + _rc.right) / 2;
			_breakStartY = (_rc.top + _rc.bottom) / 2;
			_once = true;
		}
		
		//cout << "dd" << endl;
		boom();
	}
	else
	{
		idle();
	}

}

void Lipo::render()
{
	if (!_isDie)
	{
		if (!_boomStart)
		{
			IMAGEMANAGER->frameRender("ÀÚÆøÁ»ºñ±âº»", getMemDC(), _rc.left, _rc.top, iIdx, iYIdx);
		}
		else
		{
			IMAGEMANAGER->frameRender("ÀÚÆøÁ»ºñÆøÆÄ", getMemDC(), _rc.left, _rc.top, BIdx, BYIdx);
			if (_boom)
			{
				IMAGEMANAGER->render("±úÁö´ÂÆÄÆ¼Å¬", getMemDC(), _breakStartX, _breakStartY, _breakSizeX, _breakSizeY);
			}

		}
	}
	
}

void Lipo::idle()
{
	if (_isLeft)
	{
		iYIdx = 1;
		iCnt++;
		if (iCnt % 10 == 0)
		{
			
			if (iIdx < 1)
			{
				iIdx = 4;
				iCnt = 0;
			}
			iIdx--;
		}
	}
	else
	{
		iYIdx = 0;
		iCnt++;
		if (iCnt % 10 == 0)
		{
			if (iIdx > 3)
			{
				iIdx = 0;
				iCnt = 0;
			}
			iIdx++;
		}
	}

}

void Lipo::boom()
{
	if (_isLeft)
	{
		BYIdx = 1;
	}
	else
	{
		BYIdx = 0;
	}


	Bcnt++;
	if (!_soundReady)
	{
		SOUNDMANAGER->play("ÀÚÆøÁØºñ");
		SOUNDMANAGER->setVolume("ÀÚÆøÁØºñ", 0.2f);
		_soundReady = true;
	}
	if (Bcnt % 10 == 0)
	{
		BIdx = 1 - BIdx;
	}
	if (Bcnt > 120)
	{
		_boom = true;
	}

	if (_boom)
	{
		if (!_soundBoom)
		{
			SOUNDMANAGER->play("ÀÚÆø");
			SOUNDMANAGER->setVolume("ÀÚÆø", 0.2f);
			_soundBoom = true;
		}
		_breakSizeX += 30;
		_breakSizeY += 30;
		_breakStartX -= 15;
		_breakStartY -= 15;
		_Range = RectMake(_breakStartX, _breakSizeY, _breakSizeX, _breakSizeY);
		if (_breakSizeX > 1000 && _breakSizeY > 800)
		{
			_isDie = true;

			_breakSizeX = 0;
			_breakSizeY = 0;
			_breakStartX = (_rc.left + _rc.right) / 2;
			_breakStartY = (_rc.top + _rc.bottom) / 2;
			_Range = RectMake(_breakStartX, _breakSizeY, _breakSizeX, _breakSizeY);
		}
	}
}
