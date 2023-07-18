#include "Stdafx.h"
#include "Stage1.h"


HRESULT Stage1::init(void)
{
	PLAYER->init();
	_currentMap = map1;
	_offsetX = 3840;
	_offsetY = 0;

	_breakGlass = false;
	_glassIdx = 0;


	_cutDoorL = 0;
	_cutDoorR = 0;
	_renderDoor = true;

	_knifeGet = false;
	_UIknifeRender = false;
	_obCol = RectMake(900, 537, 140, 100);
	_knifeCnt = 0;
	_knifeIdx = 0;

	_keyUPCnt = 0;
	_keyUPIdx = 0;

	_enterCnt = 0;
	_enterIdx = 0;

	_panalCnt = 0;
	_panalOffsetY = 800;

	_upBtnRender = false;
	_txtComputer1 = false;

	return S_OK;
}

void Stage1::release(void)
{
}

void Stage1::update(void)
{
	PLAYER->update();
	_pPosRc.left = PLAYER->getPlayerPos().left;
	_pPosRc.right = PLAYER->getPlayerPos().right;
	_pPosRc.top = PLAYER->getPlayerPos().top;
	_pPosRc.bottom = PLAYER->getPlayerPos().bottom;
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
			PLAYER->setPlayerPosBottom(7);
		}
		
		PLAYER->setIsJumping(false);
	
		

	}
	else {
		
		PLAYER->setIsJumping(true);

	}
	//센터값 장애물
	if (GCR == 134)
	{
		PLAYER->setColRight(true);
	}
	else {
		PLAYER->setColRight(false);
	}
	if (GCL == 134)
	{
		PLAYER->setColLeft(true);
	}
	else {
		PLAYER->setColLeft(false);
	}

	

	//오른쪽 막힌곳
	if (Grt == 134 && Grb == 134)
	{
		PLAYER->setPlayerPosRight(8);
		
	}
	/*else 
	{
		PLAYER->setColRight(false);
	}*/
	
	//왼쪽막힌곳
	if (Glt == 134 && Glb == 134)
	{
		PLAYER->setPlayerPosLeft(8);
	}
	//else
	//{
	//	//PLAYER->setColLeft(false);
	//}

	//위쪽막힌곳
	if (Glt == 134 && Grt == 134)
	{
		PLAYER->setPlayerPosBottom(PLAYER->getColTop());
	
	}
	else
	{
		
	}

	

	
	
	
	if (_currentMap == map1)
	{
		if ((_pPosRc.right + _pPosRc.left )/ 2 > 1280) //맵 넘기기
		{
		
			_pPosRc = RectMake(0, PLAYER->getPlayerPos().top-40, 74, 74);
			_offsetX += 80;
			if (_offsetX == 5120)
			{
				_renderDoor = true;
				_currentMap = map2;
				PLAYER->setPlayerPos(_pPosRc);
			}	
		}
		/*if (KEYMANAGER->isOnceKeyDown(VK_UP) && !_breakGlass)
		{
			_glassIdx++;
			cout << "되냐?" << endl;
		}*/

		if (IntersectRect(&_collider, &PLAYER->getPlayerPos(), &_obCol))
		{
			_upBtnRender = true;
			//cout << "들어옴" << endl;
			//efUIKeybordUp();
			UI->btnUPAnim();
			PLAYER->setcolCom(true);

			if (PLAYER->getTxtCom())
			{
				UI->btnEndterAnim();
			}
			
		}
		else
		{
			PLAYER->setcolCom(false);
			_upBtnRender = false;
		}
		
	}

	if (_currentMap == map2)
	{
		if ((_pPosRc.left + _pPosRc.right)  / 2 < 0)
		{
			_renderDoor = false;
			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top-40, 74, 74);
			_offsetX -= 80;
			if (_offsetX == 3840)
			{
				_currentMap = map1;
				
				PLAYER->setPlayerPos(_pPosRc);
			}							
		}
		openDoorR();
		
		if ((_pPosRc.right + _pPosRc.left) / 2 > 1280) //맵 넘기기
		{
			_cutDoorL = 170;
			_renderDoor = false;
			_pPosRc = RectMake(0, PLAYER->getPlayerPos().top-40, 74, 74);
			_offsetX += 80;
			if (_offsetX == 6400)
			{
				_cutDoorR = 0;
				_renderDoor = true;
				_currentMap = map3;
				PLAYER->setPlayerPos(_pPosRc);
			}
		}

	

	}

	if (_currentMap == map3)
	{
		if ((_pPosRc.left + _pPosRc.right) / 2 < 0)
		{
			_renderDoor = false;
			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top - 40, 74, 74);
			_offsetX -= 80;
			if (_offsetX == 5120)
			{
				_cutDoorR = 170;
				_renderDoor = true;
				_currentMap = map2;

				PLAYER->setPlayerPos(_pPosRc);
			}
		}
		openDoorL();
		openDoorR();
		if ((_pPosRc.right + _pPosRc.left) / 2 > 1280) //맵 넘기기
		{
			_renderDoor = false;
			_renderKnife = false;
			_pPosRc = RectMake(0, PLAYER->getPlayerPos().top - 40, 74, 74);
			_offsetX += 80;
			if (_offsetX == 7680)
			{
				_cutDoorL = 170;
				_renderDoor = true;
				_renderKnife = true;
				_currentMap = map4;
				PLAYER->setPlayerPos(_pPosRc);
			}
		}
	}

	if (_currentMap == map4)
	{
		if ((_pPosRc.left + _pPosRc.right) / 2 < 0)
		{			
			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top - 40, 74, 74);
			_offsetX -= 80;
			_renderKnife = false;
			if (_offsetX == 6400)
			{
				_cutDoorR = 170;
				_cutDoorL = 0;
				_currentMap = map3;
				PLAYER->setPlayerPos(_pPosRc);
			
			}
		}	
		openDoorL();
		efKnife();
		if (IntersectRect(&_collider, &PLAYER->getPlayerPos(), &_obCol) && !_knifeGet)
		{
			_UIknifeRender = true;
			efUIKeybordUp();
			PLAYER->setKnife(true);
			if (PLAYER->getUsingKnife())
			{
				PLAYER->setKnife(false);
				cout << "dd" << endl;
			}
			if (PLAYER->getTxtKnife())
			{
				_knifeGet = true;
				_renderKnife = false;
			}

			
		}
		else 
		{
			_UIknifeRender = false;
			PLAYER->setKnife(false);
		}
		if (PLAYER->getTxtKnife())
		{
			efUIReturn();
		}
		if (PLAYER->getPanalKnife())
		{
			_panalCnt++;
			if (_panalOffsetY > 0)
			{
				_panalOffsetY -= 50;
			}
			
			if (_panalCnt > 200)
			{
				_panalCnt = 0;
				PLAYER->setPanalKnife(false);
			}
			PLAYER->setKnife(false);
			//cout << _panalCnt << endl;
			
		}
	}
	


} 

void Stage1::render(void)
{
	IMAGEMANAGER->render("스테이지1", getMemDC(), 0, 0, _offsetX, _offsetY, 8960, 1600);
	
	if (_currentMap == map1)
	{
		_obCol = RectMake(130, 580, 100, 100);
		IMAGEMANAGER->render("깨진유리위", getMemDC(), 593, 412);
		IMAGEMANAGER->render("깨진유리아래", getMemDC(), 593, 567);
		if (_upBtnRender)
		{
			UI->btnUPRender(getMemDC());
		}
		if (PLAYER->getTxtCom())
		{
			UI->txtRender(getMemDC(), "컴퓨터텍스트");
			
			UI->btnEnterRender(getMemDC(), "컴퓨터텍스트");

		}

		
	}

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
			IMAGEMANAGER->frameRender("일본도이펙트", getMemDC(), _obCol.left, _obCol.top);
			IMAGEMANAGER->render("일본도", getMemDC(), _obCol.left, _obCol.top);

		}
		if (_UIknifeRender && !_knifeGet)
		{
			UI->btnUPRender(getMemDC());
			//IMAGEMANAGER->frameRender("방향키위", getMemDC(), (_pPosRc.left + _pPosRc.right) / 2, _pPosRc.top - 60);

		}
		if (PLAYER->getTxtKnife())
		{
			UI->txtRender(getMemDC(), "일본도텍스트");

			UI->btnEnterRender(getMemDC(), "일본도텍스트");

		//	IMAGEMANAGER->render("일본도텍스트", getMemDC(), _pPosRc.left-200, _pPosRc.top-200);
			
		//	IMAGEMANAGER->frameRender("엔터키", getMemDC(), _pPosRc.left+240, _pPosRc.top + 3);

		}
		if (PLAYER->getPanalKnife())
		{
			IMAGEMANAGER->render("일본도획득", getMemDC(),0, _panalOffsetY);
		}
		if (!_knifeGet)
		{
			_obCol = RectMake(900, 537, 140, 100);
		}

	}

	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		IMAGEMANAGER->render("스테이지1픽셀", getMemDC(), 0, 0, _offsetX, _offsetY, 8960, 1600);
		if(_currentMap == map1)	
		DrawRectMake(getMemDC(), _obCol);

		if (_currentMap == map4)
			DrawRectMake(getMemDC(), _obCol);
	}	
	PLAYER->render(getMemDC());

	
}

void Stage1::openDoorR()
{
	if (PLAYER->getPlayerPos().right >= 1100)
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
	if (PLAYER->getPlayerPos().left <= 180)
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


