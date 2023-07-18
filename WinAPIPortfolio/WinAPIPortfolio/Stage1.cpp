#include "Stdafx.h"
#include "Stage1.h"


HRESULT Stage1::init(void)
{
	PLAYER->init();
	_currentMap = map1;
	_offsetX = 3840;
	_offsetY = 0;


	_glassIdx = 0;

	_createPlayer = false;
	//화면흔들기
	_shakeScreen = false;
	_shakeDuration = 0;
	_shakeAmount = 50;
	//유리깨지기
	_breakFX = false;
	_breakSizeX = 0;
	_breakSizeY = 0;
	_breakStartX = 640;
	_breakStartY = 520;
	


	_mglassPushX = 0;
	_mglassPushY = 0;
	_mglassCnt = 0;
	_mglassIdx = 0;
	_mglassAngle = 0.f;
	for (int i = 0; i < 50; i++)
	{
		_glass[i] = RectMake(600, 400, 72, 76);
	}
	

	//
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
	if (_createPlayer)
	{
		PLAYER->update();
		
	}
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
		if (!_createPlayer)
		{
		
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_glassIdx++;
				_shakeScreen = true;
				_shakeDuration = 10;
			
			}
			IMAGEMANAGER->findImage("유리관")->setFrameX(_glassIdx);
			if (_glassIdx < 4)
			{
				shakeScreen(3840, 0);

			}
			UI->btnEAnim();
			

			if (_glassIdx > 3)
			{
				_createPlayer = true;
				_breakFX = true;
			}

		
		
			
		}

		if (_breakFX)
		{
			_breakSizeX += 30;
			_breakSizeY += 30;
			_breakStartX -= 15;
			_breakStartY -= 15;
			if (_breakSizeX > 1000 && _breakSizeY > 800)
			{
				_breakFX = false;
			}

			//여기
			for (int i = 0; i < 25; i++)
			{
				_mglassPushX = RND->getFromIntTo(-100, -90);
				_mglassPushY = RND->getFromIntTo(-100, -90);
				_mglassAngle = RND->getFromFloatTo(-180.f, 180.f);
				_glass[i].left += cosf(RADIAN(-_mglassAngle)) * _mglassPushX;
				_glass[i].right += cosf(RADIAN(-_mglassAngle)) * _mglassPushX;
				_glass[i].top += sinf(RADIAN(-_mglassAngle)) * _mglassPushY;
				_glass[i].bottom += sinf(RADIAN(-_mglassAngle)) * _mglassPushY;
				

			}
			for (int i = 25;  i < 50; i++)
			{

			}



		}


		if ((_pPosRc.right + _pPosRc.left )/ 2 > 1280) //맵 넘기기
		{
			_renderBreakGlass = false;
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
			_renderBreakGlass = true;
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
			_renderDoor = false;
			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top - 40, 74, 74);
			_offsetX -= 80;
			_renderKnife = false;
			if (_offsetX == 6400)
			{
				_renderDoor = true;
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
			UI->btnUPAnim();
			
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
			UI->btnEndterAnim();
			
		}
		if (PLAYER->getPanalKnife())
		{
			_panalCnt++;
			if (_panalOffsetY > 0 && _panalCnt < 200)
			{
				_panalOffsetY -= 50;
			}
			
			if (_panalCnt > 200)
			{
				if (_panalOffsetY <= 800)
				{
					_panalOffsetY += 50;
				}
				else 
				{
					_panalCnt = 0;
					PLAYER->setPanalKnife(false);
				}
				
				
				
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
		
		if (_createPlayer)
		{
			IMAGEMANAGER->render("깨진유리위", getMemDC(), 593, 412);
			IMAGEMANAGER->render("깨진유리아래", getMemDC(), 593, 567);
		}
		else if (!_createPlayer)
		{
			IMAGEMANAGER->frameRender("유리관", getMemDC(),602,420);
			UI->btnERender(getMemDC());
		}
		if (_breakFX)
		{
			IMAGEMANAGER->render("깨지는파티클", getMemDC(), _breakStartX, _breakStartY, _breakSizeX, _breakSizeY);
			for (int i = 0; i < 50; i++)
			{
				IMAGEMANAGER->frameRender("유리폭발", getMemDC(), _glass[i].left, _glass[i].top);
			}

		}
		/*
		inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}
		*/



		
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

	if (_currentMap == map4 && _renderDoor)
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
	if (_createPlayer)
	{
		PLAYER->render(getMemDC());

	}
	

	
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

void Stage1::shakeScreen(int currntOffsetX, int currntOffsetY)
{
	if (_shakeScreen && _shakeDuration > 0)
	{
		_offsetX += RND->getInt(_shakeAmount * 2) - _shakeAmount;
		_offsetY += RND->getInt(_shakeAmount) - _shakeAmount;
		_shakeDuration--;

		if (_shakeDuration == 0)
		{
			_offsetX = currntOffsetX;
			_offsetY = currntOffsetY;
			_shakeScreen = false;
		//	cout << _offsetX << " " << _offsetY << endl;

		}
	}
}

void Stage1::glassBoom()
{

}



