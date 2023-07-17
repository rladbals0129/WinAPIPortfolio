#include "Stdafx.h"
#include "Stage1.h"


HRESULT Stage1::init(void)
{
	_player = new Player;
	_player->init();
	_currentMap = map1;
	_offsetX = 3840;
	_offsetY = 0;

	_cutDoorL = 0;
	_cutDoorR = 0;
	_renderDoor = true;

	_knifeGet = false;
	_UIknifeRender = false;
	_knifeCol = RectMake(900, 537, 140, 100);
	_knifeCnt = 0;
	_knifeIdx = 0;

	_keyUPCnt = 0;
	_keyUPIdx = 0;

	_enterCnt = 0;
	_enterIdx = 0;

	_panalCnt = 0;
	_panalOffsetY = 800;

	return S_OK;
}

void Stage1::release(void)
{
}

void Stage1::update(void)
{
	_player->update();
	_pPosRc.left = _player->getPlayerPos().left;
	_pPosRc.right = _player->getPlayerPos().right;
	_pPosRc.top = _player->getPlayerPos().top;
	_pPosRc.bottom = _player->getPlayerPos().bottom;
	//==픽셀 충돌==
	int Rlb = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.bottom + _offsetY+3));
	int Rlbup = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.bottom + _offsetY - 5));

	int Rrb = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.bottom + _offsetY));
	int Rrbup = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.bottom + _offsetY - 5));

	int Rlt = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.top + _offsetY)); //r131
	int Rrt = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.top + _offsetY));

	int Glb = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.bottom + _offsetY));
	int Grb = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.bottom + _offsetY));
	int Glt = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.top + _offsetY));
	int Grt = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.top + _offsetY)); //g134

	int GCR = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _pPosRc.right + _offsetX, (_pPosRc.top + _pPosRc.bottom) / 2 + _offsetY)); //g134
	int GCL = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _pPosRc.left + _offsetX, (_pPosRc.top + _pPosRc.bottom) / 2 + _offsetY));

	//cout << "lb : " << Rlb << "    rb : " << Rrb << endl;
	//cout << "GCL : " << GCL << "    GCR : " << GCR << endl;

	//cout << _pPosRc.left << " " << _pPosRc.bottom << endl;
	//바닥
	if (Rlb == 131 || Rrb == 131)
	{
		if (Rlbup == 131 || Rrbup == 131)
		{
			_player->setPlayerPosBottom(7);
		}
		
		_player->setIsJumping(false);
	
		

	}
	else {
		
		_player->setIsJumping(true);

	}
	//센터값 장애물
	if (GCR == 134)
	{
		_player->setColRight(true);
	}
	else {
		_player->setColRight(false);
	}
	if (GCL == 134)
	{
		_player->setColLeft(true);
	}
	else {
		_player->setColLeft(false);
	}

	

	//오른쪽 막힌곳
	if (Grt == 134 && Grb == 134)
	{
		_player->setPlayerPosRight(8);
		
	}
	/*else 
	{
		_player->setColRight(false);
	}*/
	
	//왼쪽막힌곳
	if (Glt == 134 && Glb == 134)
	{
		_player->setPlayerPosLeft(8);
	}
	//else
	//{
	//	//_player->setColLeft(false);
	//}

	//위쪽막힌곳
	if (Glt == 134 && Grt == 134)
	{
		_player->setPlayerPosBottom(_player->getColTop());
	
	}
	else
	{
		
	}

	

	
	
	
	if (_currentMap == map1)
	{
		if ((_pPosRc.right + _pPosRc.left )/ 2 > 1280) //맵 넘기기
		{
		
			_pPosRc = RectMake(0, _player->getPlayerPos().top-40, 74, 74);
			_offsetX += 80;
			if (_offsetX == 5120)
			{
				_renderDoor = true;
				_currentMap = map2;
				_player->setPlayerPos(_pPosRc);
			}	
		}
	}

	if (_currentMap == map2)
	{
		if ((_pPosRc.left + _pPosRc.right)  / 2 < 0)
		{
			_renderDoor = false;
			_pPosRc = RectMake(1180, _player->getPlayerPos().top-40, 74, 74);
			_offsetX -= 80;
			if (_offsetX == 3840)
			{
				_currentMap = map1;
				
				_player->setPlayerPos(_pPosRc);
			}							
		}
		openDoorR();
		
		if ((_pPosRc.right + _pPosRc.left) / 2 > 1280) //맵 넘기기
		{
			_cutDoorL = 170;
			_renderDoor = false;
			_pPosRc = RectMake(0, _player->getPlayerPos().top-40, 74, 74);
			_offsetX += 80;
			if (_offsetX == 6400)
			{
				_cutDoorR = 0;
				_renderDoor = true;
				_currentMap = map3;
				_player->setPlayerPos(_pPosRc);
			}
		}

	

	}

	if (_currentMap == map3)
	{
		if ((_pPosRc.left + _pPosRc.right) / 2 < 0)
		{
			_renderDoor = false;
			_pPosRc = RectMake(1180, _player->getPlayerPos().top - 40, 74, 74);
			_offsetX -= 80;
			if (_offsetX == 5120)
			{
				_cutDoorR = 170;
				_renderDoor = true;
				_currentMap = map2;

				_player->setPlayerPos(_pPosRc);
			}
		}
		openDoorL();
		openDoorR();
		if ((_pPosRc.right + _pPosRc.left) / 2 > 1280) //맵 넘기기
		{
			_renderDoor = false;
			_renderKnife = false;
			_pPosRc = RectMake(0, _player->getPlayerPos().top - 40, 74, 74);
			_offsetX += 80;
			if (_offsetX == 7680)
			{
				_cutDoorL = 170;
				_renderDoor = true;
				_renderKnife = true;
				_currentMap = map4;
				_player->setPlayerPos(_pPosRc);
			}
		}
	}

	if (_currentMap == map4)
	{
		if ((_pPosRc.left + _pPosRc.right) / 2 < 0)
		{			
			_pPosRc = RectMake(1180, _player->getPlayerPos().top - 40, 74, 74);
			_offsetX -= 80;
			_renderKnife = false;
			if (_offsetX == 6400)
			{
				_cutDoorR = 170;
				_cutDoorL = 0;
				_currentMap = map3;
				_player->setPlayerPos(_pPosRc);
			
			}
		}	
		openDoorL();
		efKnife();
		if (IntersectRect(&_collider, &_player->getPlayerPos(), &_knifeCol) && !_knifeGet)
		{
			_UIknifeRender = true;
			efUIKeybordUp();
			_player->setKnife(true);
			if (_player->getUsingKnife())
			{
				_player->setKnife(false);
				cout << "dd" << endl;
			}
			if (_player->getTxtKnife())
			{
				_knifeGet = true;
				_renderKnife = false;
			}

			
		}
		else 
		{
			_UIknifeRender = false;
			_player->setKnife(false);
		}
		if (_player->getTxtKnife())
		{
			efUIReturn();
		}
		if (_player->getPanalKnife())
		{
			_panalCnt++;
			if (_panalOffsetY > 0)
			{
				_panalOffsetY -= 50;
			}
			
			if (_panalCnt > 200)
			{
				_panalCnt = 0;
				_player->setPanalKnife(false);
			}
			_player->setKnife(false);
			//cout << _panalCnt << endl;
			
		}
	}
	


} 

void Stage1::render(void)
{
	IMAGEMANAGER->render("스테이지1", getMemDC(), 0, 0, _offsetX, _offsetY, 8960, 1600);
	

	if (_currentMap == map2 && _renderDoor)
	{
		IMAGEMANAGER->render("문", getMemDC(), 1255, 437, 0 , _cutDoorR, 55, 225);

	}
	if (_currentMap == map3 && _renderDoor)
	{
		IMAGEMANAGER->render("문", getMemDC(), -30, 437, 0, _cutDoorL, 55, 225);
		IMAGEMANAGER->render("문", getMemDC(), 1255, 437, 0, _cutDoorR, 55, 225);
	}

	if (_currentMap == map4)
	{
		IMAGEMANAGER->render("문", getMemDC(), -30, 437, 0, _cutDoorL, 55, 225);
		if (_renderKnife && !_knifeGet)
		{
			IMAGEMANAGER->frameRender("일본도이펙트", getMemDC(), _knifeCol.left, _knifeCol.top);
			IMAGEMANAGER->render("일본도", getMemDC(), _knifeCol.left, _knifeCol.top);

		}
		if (_UIknifeRender && !_knifeGet)
		{
			IMAGEMANAGER->frameRender("방향키위", getMemDC(), (_pPosRc.left + _pPosRc.right) / 2, _pPosRc.top - 60);

		}
		if (_player->getTxtKnife())
		{
			
			IMAGEMANAGER->render("일본도텍스트", getMemDC(), _pPosRc.left-200, _pPosRc.top-200);
			
			IMAGEMANAGER->frameRender("엔터키", getMemDC(), _pPosRc.left+240, _pPosRc.top + 3);

		}
		if (_player->getPanalKnife())
		{
			IMAGEMANAGER->render("일본도획득", getMemDC(),0, _panalOffsetY);
		}

	}

	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		IMAGEMANAGER->render("스테이지1픽셀", getMemDC(), 0, 0, _offsetX, _offsetY, 8960, 1600);
		if(_currentMap == map4)	DrawRectMake(getMemDC(), _knifeCol);
	}	
	_player->render();

	
}

void Stage1::openDoorR()
{
	if (_player->getPlayerPos().right >= 1100)
	{
		if (_cutDoorR <= 170)
		{
			_cutDoorR += 10;
		}
	}
	else {
		if (_cutDoorR > 0 )
		{
			_cutDoorR -= 10;
		}
	}	
}

void Stage1::openDoorL()
{
	if (_player->getPlayerPos().left <= 180)
	{
		if (_cutDoorL <= 170)
		{
			_cutDoorL += 10;
		}
	}
	else {
		if (_cutDoorL > 0)
		{
			_cutDoorL -= 10;
		}
	}
}

void Stage1::efKnife()
{
	_knifeCnt++;
	if (_knifeCnt % 3 == 0)
	{
		_knifeIdx++;

		if (_knifeIdx > 7)
		{
			_knifeIdx = 0;
			_knifeCnt = 0;
		}
		IMAGEMANAGER->findImage("일본도이펙트")->setFrameX(_knifeIdx);
	}
	
}

void Stage1::efUIKeybordUp()
{
	_keyUPCnt++;
	if (_keyUPCnt % 24 == 0)
	{
		_keyUPIdx++;
		
		if (_keyUPIdx > 2)
		{
			_keyUPIdx = 0;
			_keyUPCnt = 0;
		}
		IMAGEMANAGER->findImage("방향키위")->setFrameX(_keyUPIdx);
	}

}

void Stage1::efUIReturn()
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
}


