#include "Stdafx.h"
#include "Stage1.h"


HRESULT Stage1::init(void)
{
	PLAYER->init();
	_rot = new RotationRender;
	_rot->init();
	_rot->LoadImageA(L"Resources/Images/Stage1/Object/BoxBreak.png");
	_currentMap = map1;
	_offsetX = 3840;
	_offsetY = 0;


	_glassIdx = 0;

	_createPlayer = true;
	_readyPlayer = false;
	_readyCnt = 0;
	_readyIdx = 0;
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
	
	_boom = false;
	for (int i = 0; i < 50; i++)
	{
		_gl[i].isGlass = false;
		_gl[i].alpha = 255;
		_gl[i].bounceX = 1;
		_gl[i].bounceY = 1;
		_gl[i].bounce = 1;

		_gl[i].glassYIdx = RND->getInt(5);
	
		_gl[i].angle = RND->getFromFloatTo(-92.5f, -87.5f);

		_gl[i].speed = 20;
		_gl[i].speedX = _gl[i].speed * cosf(_gl[i].angle);
		_gl[i].speedY = _gl[i].speed * sinf(_gl[i].angle);

		_gl[i].centerX = 625;
		_gl[i].centerY = 480;
		_gl[i].distance = 10;
		_gl[i].createX =  _gl[i].centerX + cosf(RADIAN(_gl[i].angle))  * _gl[i].distance;
		_gl[i].createY =  _gl[i].centerY + sinf(RADIAN(_gl[i].angle))  * _gl[i].distance;
		_gl[i].glass = RectMakeCenter(_gl[i].createX, _gl[i].createY, 72, 76);

	}
	_bgImage = RectMake(150, 600, 440, 300);


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
	_explosion = false;

	//박스 792 440
	for (int i = 0; i < 3; i++)
	{	
		_box[i].rc = RectMake(792, 440 + (i * 70), 120, 80);
		_box[i].isBreak = false;
		_obj.push_back(_box[i]);
	}

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
	_rot->rotateImage(0.1f);
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
		PLAYER->setGoDownJump(false);
		PLAYER->setIsJumping(false);
	}
	else {
		
		PLAYER->setIsJumping(true);

	}
	if (Rlb == 176 || Rrb == 176)
	{
		PLAYER->setDownJump(true);
		PLAYER->setIsJumping(false);
	}
	else
	{
		PLAYER->setDownJump(false);
		//PLAYER->setIsJumping(true);
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
			/*	if (_glassIdx == 4 && !_explosion)
				{
					_explosion = true;
				}*/
			
			}
			IMAGEMANAGER->findImage("유리관")->setFrameX(_glassIdx);
			if (_glassIdx < 4)
			{
				shakeScreen(3840, 0,50);

			}
			
			/*if (_explosion)
			{
				_shakeDuration = 10;
				_shakeScreen = true;
				shakeScreen(3840, 0, 50);
		
			}*/
			UI->btnEAnim();
			

			if (_glassIdx > 3)
			{
				
			
				_readyPlayer = true;
				_renderBreakGlass = true;
				_breakFX = true;
				_boom = true;
				for (int i = 0; i < 50; i++)
				{
					_gl[i].isGlass = true;
				}
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
			
		}
		if (_boom)
		{
			glassBoom();
			for (int i = 0; i < 50; i++)
			{

				if (!_gl[i].isGlass) continue;

				_gl[i].speedY -= GRAVITY;
				//_gl[i].speedX += GRAVITY;

				_gl[i].glass.left += _gl[i].speedX * _gl[i].bounce;
				_gl[i].glass.right += _gl[i].speedX * _gl[i].bounce;
				_gl[i].glass.top -= _gl[i].speedY * _gl[i].bounce - GRAVITY;
				_gl[i].glass.bottom -= _gl[i].speedY * _gl[i].bounce - GRAVITY;

				int RLB = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(),
					_gl[i].glass.left + _offsetX, _gl[i].glass.bottom + _offsetY + 3));
				int RRB = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(),
					_gl[i].glass.right + _offsetX, _gl[i].glass.bottom + _offsetY + 3));

				int GLB = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(),
					_gl[i].glass.left + _offsetX, _gl[i].glass.bottom + _offsetY + 3));
				int GLT = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(),
					_gl[i].glass.left + _offsetX, _gl[i].glass.top + _offsetY + 3));
				int GRB = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(),
					_gl[i].glass.right + _offsetX, _gl[i].glass.bottom + _offsetY + 3));
				int GRT = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(),
					_gl[i].glass.right + _offsetX, _gl[i].glass.top + _offsetY + 3));

				if (RLB == 131 || RRB == 131)
				{

					_gl[i].speedY = -_gl[i].speedY * 0.8;
					_gl[i].speedX = _gl[i].speedX * 0.5;
					_gl[i].bounce = -_gl[i].bounce;
					// 
					// 
						//_gl[i].speedX = _gl[i].speedX / 1.5f;



				}

				if (GLB == 134 || GLT == 134 || GRB == 134 || GRT == 134)
				{

					//_gl[i].bounceY = -_gl[i].bounceY;
					//_gl[i].speedY = -_gl[i].speedY * -1.5;
					//_gl[i].glass.top += 10;
					//_gl[i].glass.bottom += 10;
					
					_gl[i].speedX *= 0.5;
					_gl[i].speedY *= 0.5f;
				}

				if (fabs(_gl[i].speedX) < 0.1 && fabs(_gl[i].speedY) < 0.1)
				{
					_gl[i].speedX = 0;
					_gl[i].speedY = 0;
				}


			}
		}
		
		if (_readyPlayer)
		{
			_readyCnt++;
			IMAGEMANAGER->findImage("플레이어생성")->setFrameX(0);
			if (_readyCnt > 40)
			{
				IMAGEMANAGER->findImage("플레이어생성")->setFrameX(1);
			}

			if (_readyCnt > 250)
			{
				_readyPlayer = false;
				_createPlayer = true;
			}
			
		}


		if ((_pPosRc.right + _pPosRc.left )/ 2 > 1280) //맵 넘기기
		{
			_renderBreakGlass = false;
			_pPosRc = RectMake(0, PLAYER->getPlayerPos().top-40, 74, 74);
			_offsetX += 80;
			if (_offsetX == 5120 && _offsetY == 0)
			{
				
				_renderDoor = true;
				_currentMap = map2;
				PLAYER->setPlayerPos(_pPosRc);
			}	
		}


		if (IntersectRect(&_collider, &PLAYER->getPlayerPos(), &_obCol))
		{
			_upBtnRender = true;
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
			if (_offsetX == 3840 && _offsetY == 0)
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
			if (_offsetX == 6400 && _offsetY == 0)
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
			if (_offsetX == 5120 && _offsetY == 0)
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
			if (_offsetX == 7680 && _offsetY == 0)
			{
				_cutDoorL = 170;
				_renderDoor = true;
				_renderKnife = true;
				_currentMap = map4;
				PLAYER->setPlayerPos(_pPosRc);
			}
		}

		//여기서부터
		//if ((_pPosRc.bottom + _pPosRc.top) / 2 > 800)
		//{
		//	_offsetY += 20;
		//		//PLAYER->getColTop();
		//	_pPosRc = RectMake(PLAYER->getPlayerPos().left, PLAYER->getPlayerPos().top - 400, 74, 74);
		//	if (_offsetY == 800)
		//	{
		//		cout << Rlb << endl;
		//		cout << "offsetY = " << _offsetY << endl;
		//		_currentMap = map5;
		//		
		//		PLAYER->setPlayerPos(_pPosRc);
		//	}
		//	
		//}
	//	cout << _offsetY << endl;



		/*if (PLAYER->getPlayerPos().top < 400)
		{

			_offsetY -= 400 - PLAYER->getPlayerPos().top;
			PLAYER->setPlayerPosTop(400 - PLAYER->getPlayerPos().top);
		}*/
		if (PLAYER->getGoDownjump())
		{
			if (PLAYER->getPlayerPos().top > 600 && _offsetY < 800)
			{
				//cout << _offsetY << endl;

				//cout << PLAYER->getPlayerPos().top << endl;
				_offsetY += PLAYER->getPlayerPos().top - 600;
				PLAYER->setPlayerPosBottom(PLAYER->getPlayerPos().top - 600);
				if (_offsetY > 600)
				{
				
					_currentMap = map5;
				}
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
			if (_offsetX == 6400 && _offsetY == 0)
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
				//cout << "dd" << endl;
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

	if (_currentMap == map5)
	{
		cout << _offsetY << endl;
		if (PLAYER->getPlayerPos().top < 400)
		{

			_offsetY -= 400 - PLAYER->getPlayerPos().top;
			/*for (auto _iter = _obj.begin(); _iter != _obj.end(); ++_iter)
			{
				_iter->rc.top += 400 - PLAYER->getPlayerPos().top;
				_iter->rc.bottom += 400 - PLAYER->getPlayerPos().bottom;
			}*/
			PLAYER->setPlayerPosTop(400 - PLAYER->getPlayerPos().top);
		}
		if (PLAYER->getPlayerPos().top > 400 && _offsetY < 800)
		{
			_offsetY += PLAYER->getPlayerPos().top - 400;
			/*for (auto _iter = _obj.begin(); _iter != _obj.end(); ++_iter)
			{
				_iter->rc.top -= PLAYER->getPlayerPos().top - 600;
				_iter->rc.bottom -= PLAYER->getPlayerPos().bottom - 600;
			}*/
			PLAYER->setPlayerPosBottom(PLAYER->getPlayerPos().top - 400);
		}

		if ((_pPosRc.left + _pPosRc.right) / 2 < 0)
		{
			//_renderBreakGlass = true;
			//_renderDoor = false;
			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top -80, 74, 74);
			_offsetX -= 80;
			if (_offsetX == 5120)
			{
				_currentMap = map6;

				PLAYER->setPlayerPos(_pPosRc);
			}
		}
		//박스
		for (auto it = _obj.begin(); it != _obj.end();)
		{
			
			if (IntersectRect(&_collider, &PLAYER->getPlayerPos(), &it->rc))
			{
				PLAYER->setColRight(true);
			}

			if (IntersectRect(&_collider, &PLAYER->getATKRange(), &it->rc))
			{
				cout << "상자 맞았다";
				it->isBreak = false;
				it = _obj.erase(it);
			}
			else
			{
				it++;
			}

		}

		





		//moveCamera(400,600, 600, 6420, 800);

	}

	if (_currentMap == map6)
	{
		if ((_pPosRc.left + _pPosRc.right) / 2 > 1280)
		{
			//_renderBreakGlass = true;
			//_renderDoor = false;
			_pPosRc = RectMake(0, PLAYER->getPlayerPos().top - 80, 74, 74);
			_offsetX += 80;
			if (_offsetX == 6400)
			{
				_currentMap = map5;

				PLAYER->setPlayerPos(_pPosRc);
			}
		}
		moveCamera(400, 600, 400,3880, 5120, 800);

		if ((_pPosRc.left + _pPosRc.right) / 2 < 0)
		{
			//_renderBreakGlass = true;
			//_renderDoor = false;
			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top - 80, 74, 74);
			_offsetX -= 80;
			if (_offsetX == 2600)
			{
				_currentMap = map7;

				PLAYER->setPlayerPos(_pPosRc);
			}
		}
	}
	if (_currentMap == map7)
	{
		if ((_pPosRc.left + _pPosRc.right) / 2 > 1280)
		{
			//_renderBreakGlass = true;
			//_renderDoor = false;
			_pPosRc = RectMake(0, PLAYER->getPlayerPos().top - 80, 74, 74);
			_offsetX += 80;
			if (_offsetX == 3880)
			{
				_currentMap = map6;

				PLAYER->setPlayerPos(_pPosRc);
			}
		}
		moveCamera(400,600,400,1280,2600,800);


	}
	


} 

void Stage1::render(void)
{
	IMAGEMANAGER->render("스테이지1", getMemDC(), 0, 0, _offsetX, _offsetY, 8960, 1600);
	
	_rot->RotateRender(400, 400, 72, 40);
	if (_currentMap == map1)
	{
		_obCol = RectMake(130, 580, 100, 100);
		

		if (_renderBreakGlass)
		{
			IMAGEMANAGER->render("깨진유리위", getMemDC(), 593, 412);
			IMAGEMANAGER->render("깨진유리아래", getMemDC(), 593, 567);
		}
		else if (!_createPlayer)
		{
			IMAGEMANAGER->frameRender("유리관", getMemDC(),602,420);
			IMAGEMANAGER->findImage("유리관플레이어")->setX(640);
			IMAGEMANAGER->findImage("유리관플레이어")->setY(480);
			IMAGEMANAGER->render("유리관플레이어", getMemDC(), 640, 480);
			UI->btnERender(getMemDC());
			//RECT test = RectMake(625, 480, 76, 72);
			//DrawRectMake(getMemDC(), test);
		}
	
		if (_breakFX)
		{
			IMAGEMANAGER->render("깨지는파티클", getMemDC(), _breakStartX, _breakStartY, _breakSizeX, _breakSizeY);
		}
	
		for (int i = 0; i < 50; i++)
		{
			if (!_gl[i].isGlass) continue;

			if (_gl[i].isGlass)
			{
				//	cout << "dd" << endl;
				IMAGEMANAGER->findImage("유리폭발")->setFrameY(_gl[i].glassYIdx);
				IMAGEMANAGER->frameAlphaRender("유리폭발", getMemDC(), _gl[i].glass.left, _gl[i].glass.top,
					IMAGEMANAGER->findImage("유리폭발")->getFrameX(),
					IMAGEMANAGER->findImage("유리폭발")->getFrameY(), _gl[i].alpha);
				//cout << _gl[i].alpha << endl;
			}

		}
		if (_readyPlayer)
		{
			IMAGEMANAGER->frameRender("플레이어생성", getMemDC(), 600, 570);
		}




		
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
		if (_currentMap == map1)
			DrawRectMake(getMemDC(), _obCol);

		if (_currentMap == map4)
			DrawRectMake(getMemDC(), _obCol);
	}
	if (_createPlayer)
	{
		PLAYER->render(getMemDC());

	}	

	if (_currentMap == map5)
	{
		for (auto it = _obj.begin(); it != _obj.end(); ++it)
		{
			//BREAKOBJECT& breakObject = *it;
			//RECT& rc = breakObject.rc;
			//bool isBreak = breakObject.isBreak;

			IMAGEMANAGER->render("상자", getMemDC(), it->rc.left, it->rc.top);
			// 이곳에서 필요한 작업을 수행하세요.
		}
		//for (int i = 0; i < 3; i++)
		//{
		//	
		//	//IMAGEMANAGER->render("상자", getMemDC(), _box[i].rc.left,_box[i].rc.top);
		//	
		////	DrawRectMake(getMemDC(), _box[i].rc);

		//}
	}


	if (_currentMap == map6)
	{
		IMAGEMANAGER->render("배경시체", getMemDC(), _bgImage.left, _bgImage.top);
		//DrawRectMake(getMemDC(), _bgImage);
	}

	if (_currentMap == map7)
	{

	}



	char ptMouse[128];

	wsprintf(ptMouse, "x : %d y : %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), 100, 100, ptMouse, strlen(ptMouse));


	
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

void Stage1::shakeScreen(int currntOffsetX, int currntOffsetY, int shakeAmount)
{
	_shakeAmount = shakeAmount;
	if (_shakeScreen && _shakeDuration > 0)
	{
		_offsetX += RND->getInt(_shakeAmount * 2) - _shakeAmount;
		_offsetY += RND->getInt(_shakeAmount) - _shakeAmount * 2;
		_shakeDuration--;
		if (_shakeDuration % 2== 0)
		{
			_offsetX = currntOffsetX;
			_offsetY = currntOffsetY;
			
		}

		if (_shakeDuration == 0)
		{
			_offsetX = currntOffsetX;
			_offsetY = currntOffsetY;
			_shakeScreen = false;
		}
	}

	

	
}

void Stage1::moveCamera(int LcameraOffsetX,int RcameraOffsetX, int cameraOffsetY, int LmaxOffsetX, int RmaxOffsetX, int maxOffsetY)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (PLAYER->getPlayerPos().left < LcameraOffsetX && _offsetX > LmaxOffsetX)
		{
			_offsetX -= 8;
			_bgImage.left += 8;
			_bgImage.right += 8;
			PLAYER->setPlayerPosLeft(8);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (PLAYER->getPlayerPos().left > RcameraOffsetX && _offsetX < RmaxOffsetX)
		{
			_offsetX += 8;
			_bgImage.left -= 8;
			_bgImage.right -= 8;
			PLAYER->setPlayerPosRight(8);
		}

	}

	//상하
	if (PLAYER->getPlayerPos().top < cameraOffsetY && _offsetY > 0)
	{

		_offsetY -= cameraOffsetY - PLAYER->getPlayerPos().top;
		_bgImage.top += cameraOffsetY - PLAYER->getPlayerPos().top;
		_bgImage.bottom += cameraOffsetY - PLAYER->getPlayerPos().top;
		PLAYER->setPlayerPosTop(cameraOffsetY - PLAYER->getPlayerPos().top);
	}
	if (PLAYER->getPlayerPos().top > cameraOffsetY && _offsetY < maxOffsetY)
	{
	
		_offsetY += PLAYER->getPlayerPos().top - cameraOffsetY;
		_bgImage.top -= PLAYER->getPlayerPos().top - cameraOffsetY;
		_bgImage.bottom -= PLAYER->getPlayerPos().top - cameraOffsetY;
		PLAYER->setPlayerPosBottom(PLAYER->getPlayerPos().top - cameraOffsetY);
	}



}

void Stage1::glassBoom()
{
	for (int i = 0; i < 50; i++)
	{
		_gl[i].glassCnt++;
		//cout << _gl[i].alpha << endl;
		
		if (_gl[i].glassCnt % 20 == 0 && _gl[i].glassXIdx <4)
		{
			if(_gl[i].glassXIdx < 4)
			{
				_gl[i].glassXIdx++;
				
			}
			else 
			{
				_gl[i].glassXIdx = 4;
			}
			
			IMAGEMANAGER->findImage("유리폭발")->setFrameX(_gl[i].glassXIdx);
		}
		else if (_gl[i].glassXIdx == 4)
		{
		
			
			_gl[i].alphaCnt++;
			if (_gl[i].alphaCnt % 4 == 0)
			{
				_gl[i].alpha = 255 - _gl[i].alpha;
			}



			if (_gl[i].alphaCnt > 200)
			{
				_gl[i].isGlass = false;
			}
		
		}
	}
}



