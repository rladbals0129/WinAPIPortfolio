#include "Stdafx.h"
#include "Stage1.h"


HRESULT Stage1::init(void)
{
	PLAYER->init();
	//_rot->LoadImageA();

	
	


	_currentMap = map1;
	_offsetX = 3840;
	_offsetY = 0;
	_switchScreen = false;


	_glassIdx = 0;

	_createPlayer = false;
	_readyPlayer = false;
	_readyCnt = 0;
	_readyIdx = 0;
	//화면흔들기

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
	


	_cutDoorL = 0;
	_cutDoorR = 0;
	_renderDoor = true;
	_renderKunai = true;
	_knifeGet = false;
	_UIknifeRender = false;
	_obCol = RectMake(900, 537, 140, 100);


	_kunaigetCOl = RectMake(300, 600, 100, 100);

	_knifeCnt = 0;
	_knifeIdx = 0;

	_panalCnt = 0;
	_panalOffsetY = 800;

	_upBtnRender = false;
	_txtComputer1 = false;
	_explosion = false;


	_rot = new RotationRender;
	_rot->init();

	
	
	for (int i = 0; i < 3; i++)
	{	
		_box[i].rc = RectMake(792, 440 + (i * 70), 120, 80);
		_box[i].isBreak = false;	
		_obj.push_back(_box[i]);

	}
	for (int i = 0; i < 6; i++)
	{
		if (i < 3)
		{
			_box[i].rc = RectMake(310, 360 + (i * 70), 120, 80);
			_box2.push_back(_box[i]);
		}
		
		else if (i >= 3)
		{
			_box[i].rc = RectMake(-460, 360 + ((i-3) * 70), 120, 80);
			_box2.push_back(_box[i]);
		}
	}

	_hitCnt = 0;
	_hitDelay = false;
	//적

	_knockBackMagnitude = 10.0f;

	//===========
	for (int i = 0; i < 3; i++)
	{
		_zm = new Zombiebot;
		_zm->init();
		_zm->setPos(200 - (i * 300), 670);   //670
		_Fzm.push_back(_zm);
	
	}
	_kunaiCOl.init();
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
		PLAYER->_dustEffect.update();
		//_kunai->update();
	
	}
	updateShakeEffect(_shakeDuration, _shakeOffsetX, _shakeOffsetY);
	
	
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
	if (PLAYER->getUsingKunai() && _createPlayer)
	{
		_kunaiCOl.kunaiCollision(IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _offsetX,_offsetY);
	}
	




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

	
	//왼쪽막힌곳
	if (Glt == 134 && Glb == 134)
	{
		PLAYER->setPlayerPosLeft(8);
	}


	//위쪽막힌곳
	if (Glt == 134 && Grt == 134)
	{
		PLAYER->setPlayerPosBottom(PLAYER->getColTop());
	
	}



	
	
	
	if (_currentMap == map1)
	{
		if (!_createPlayer)
		{
		
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_glassIdx++;
				applyShake(_initialShakeDuration);
				//_shakeScreen = true;
				//_shakeDuration1 = 10;
			/*	if (_glassIdx == 4 && !_explosion)
				{
					_explosion = true;
				}*/
			
			}
			IMAGEMANAGER->findImage("유리관")->setFrameX(_glassIdx);
			/*if (_glassIdx < 4)
			{
				shakeScreen(3840, 0,50);

			}*/
			
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
				}

				if (GLB == 134 || GLT == 134 || GRB == 134 || GRT == 134)
				{	
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
			_switchScreen = true;
			if (_offsetX == 5120 && _offsetY == 0)
			{
				_switchScreen = false;
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
			_switchScreen = true;
			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top-40, 74, 74);
			_offsetX -= 80;
			if (_offsetX == 3840 && _offsetY == 0)
			{
				_switchScreen = false;
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
			_switchScreen = true;
			if (_offsetX == 6400 && _offsetY == 0)
			{
				_cutDoorR = 0;
				_switchScreen = false;
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
			_switchScreen = true;
			if (_offsetX == 5120 && _offsetY == 0)
			{
				_switchScreen = false;
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
			_switchScreen = true;
			if (_offsetX == 7680 && _offsetY == 0)
			{
				_switchScreen = false;
				_cutDoorL = 170;
				_renderDoor = true;
				_renderKnife = true;
				_currentMap = map4;
				PLAYER->setPlayerPos(_pPosRc);
			}
		}

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
			_switchScreen = true;
			_renderKnife = false;
			if (_offsetX == 6400 && _offsetY == 0)
			{
				_renderDoor = true;
				_switchScreen = false;
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
		
		if (PLAYER->getPlayerPos().top < 400)
		{

			_offsetY -= 400 - PLAYER->getPlayerPos().top;
			PLAYER->setPlayerPosTop(400 - PLAYER->getPlayerPos().top);
		}
		if (PLAYER->getPlayerPos().top > 400 && _offsetY < 800)
		{
			_offsetY += PLAYER->getPlayerPos().top - 400;
	
			PLAYER->setPlayerPosBottom(PLAYER->getPlayerPos().top - 400);
		}

		if ((_pPosRc.left + _pPosRc.right) / 2 < 0)
		{
			//_renderBreakGlass = true;
			//_renderDoor = false;
			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top -80, 74, 74);
			_offsetX -= 80;
			_switchScreen = true;
			if (_offsetX == 5120)
			{
				_switchScreen = false;
				_currentMap = map6;

				PLAYER->setPlayerPos(_pPosRc);
			}
		}
		//박스
		std::vector<size_t> breakIndices;

		// 박스
		for (size_t i = 0; i < _obj.size(); i++)
		{
			if (IntersectRect(&_collider, &PLAYER->getPlayerPos(), &_obj[i].rc))
			{
				PLAYER->setColRight(true);
			}

			if (IntersectRect(&_collider, &PLAYER->getATKRange(), &_obj[i].rc))
			{
				cout << "상자 맞았다" << endl;
				applyShake(_initialShakeDuration);
				createBoxEF = true;
				if (createBoxEF)
				{
					for (int k = 0; k < 8; k++)
					{
						float EFX = RND->getFromIntTo(_obj[i].rc.left, _obj[i].rc.right);
						float EFY = RND->getFromIntTo(_obj[i].rc.bottom - 40, _obj[i].rc.bottom);
						_slashEffect.addEffect(EFX, EFY, 1, "상자깨지기이펙트검은색");
					}
					for (int j = 0; j < 3; j++)
					{
						float EFX = RND->getFromIntTo(_obj[i].rc.left, _obj[i].rc.right);
						float EFY = RND->getFromIntTo(_obj[i].rc.bottom - 40, _obj[i].rc.bottom);
						_slashEffect.addEffect(EFX, EFY, 1, "상자깨지기이펙트");
					}
					for (int j = 0; j < 3; j++)
					{
						float EFX = RND->getFromIntTo(_obj[i].rc.left, _obj[i].rc.right);
						float EFY = RND->getFromIntTo(_obj[i].rc.bottom - 40, _obj[i].rc.bottom);
						_slashEffect.addEffect(EFX, EFY, 1, "베기먼지");
					}

					float slashX = _obj[i].rc.left;
					float slashY = (_obj[i].rc.top + _obj[i].rc.bottom) / 2;
					_slashEffect.addSlashEffect(slashX, slashY, 1,"베기");
				}
				createBoxEF = false;

				breakIndices.push_back(i);			
			}
		}
		// 파괴된 상자의 인덱스를 사용해 파편 생성
		for (size_t i : breakIndices)
		{
			POINT position = { _obj[i].rc.left, _obj[i].rc.top };
			createFragments(m_fragments, position, L"Resources/Images/Stage1/Object/BoxBreak.png", 5);
		}
		// 상자 목록에서 파괴된 상자를 제거합니다.
		for (auto it = breakIndices.rbegin(); it != breakIndices.rend(); ++it)
		{
			_obj.erase(_obj.begin() + *it);
		}
		// 파편 업데이트
		for (auto& fragment : m_fragments)
		{
			fragment.Update(0.16f, IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(),_offsetX,_offsetY);
		}
	//	moveCamera(0,1280,400,0,1280,800);

	}

	if (_currentMap == map6)
	{		
		//좀비 상태처리
		for (int i = 0; i < _Fzm.size(); i++)
		{
			_Fzm[i]->UpdateZombie();
		}
		//좀비 추적범위
		for (int i = 0; i < _Fzm.size();i++)
		{
			if (IntersectRect(&_collider, &PLAYER->getPlayerPos(), &_Fzm[i]->getRange()))
			{
				if (!_Fzm[i]->getGo())
				{
					_Fzm[i]->setState(1);
					_Fzm[i]->setGo(true);
				}
				else if (_Fzm[i]->getState() == 2)
				{
					if (PLAYER->getPlayerCenter() > _Fzm[i]->getCenter())
					{
						_Fzm[i]->setPosLeft(1);
						_Fzm[i]->setIsLeft(false);
					}
					else if (PLAYER->getPlayerCenter() <= _Fzm[i]->getCenter())
					{
						_Fzm[i]->setPosRight(1);
						_Fzm[i]->setIsLeft(true);
					}
				}
				
			}
			else
			{
				if (_Fzm[i]->getState() == 2)
				{
					_zomIdleCnt++;
					if (_zomIdleCnt % RND->getFromIntTo(200,500) == 0)
					{
						_zomIdle = !_zomIdle;
					}

					if (_zomIdle)
					{
						_Fzm[i]->setIsLeft(false);
						_Fzm[i]->setPosLeft(1);
					}
					else
					{
						_Fzm[i]->setIsLeft(true);
						_Fzm[i]->setPosRight(1);
					}
					
				}
			}

		}
		
		for (int i = 0; i < _Fzm.size(); i++)
		{
			
			if (IntersectRect(&_collider, &PLAYER->getPlayerPos(), &_Fzm[i]->getPos()))
			{
				if (!_hitDelay)
				{
					PLAYER->setDmg(_Fzm[i]->getAtk());
					PLAYER->setHit(true);
					_hitDelay = true;
					//넉백
					float knockBackX = PLAYER->getPlayerCenter() > _Fzm[i]->getCenter() ? _knockBackMagnitude : -_knockBackMagnitude;
					float knockBackY = 0; //-_knockBackMagnitude;  
					PLAYER->setKnockback(knockBackX, knockBackY);
					//======
					applyShake(_initialShakeDuration);
				}
			}
			
		
		}
		
		
		
		if (_hitDelay)
		{
			PLAYER->Hit();
			_hitCnt++;
			if (_hitCnt % 5 == 0)
			{
				PLAYER->setAlpha(255 - (PLAYER->getAlpha() - 115));
			}
		}
		if (_hitCnt > 100)
		{
			PLAYER->setAlpha(255);
			PLAYER->setHit(false);
			_hitDelay = false;
			_hitCnt = 0;
		}
		
		//cout << PLAYER->getHit() << endl;
		//좀비 파티클
		vector<size_t> zombieFM;
		for (int i = 0; i < _Fzm.size(); i++)
		{

			if (IntersectRect(&_collider, &PLAYER->_bullet.getPos(), &_Fzm[i]->getPos()))
			{
				_zombieDiePosX = _Fzm[i]->getPos().left;
				_zombieDiePosY = _Fzm[i]->getPos().top;
				float knockBackX = PLAYER->getPlayerCenter() > _Fzm[i]->getCenter() ? _knockBackMagnitude : -_knockBackMagnitude;
				float knockBackY = 0;
				PLAYER->setKnockback(knockBackX, knockBackY);
				_Fzm[i]->setDie(true);
				applyShake(_initialShakeDuration);
				createBoxEF = true;
				if (createBoxEF)
				{
					for (int k = 0; k < 8; k++)
					{
						float EFX = RND->getFromIntTo(_Fzm[i]->getPos().left, _Fzm[i]->getPos().right);
						float EFY = RND->getFromIntTo(_Fzm[i]->getPos().top, _Fzm[i]->getPos().top + 50);
						_slashEffect.addEffect(EFX, EFY, 1, "상자깨지기이펙트검은색");
					}
					for (int j = 0; j < 3; j++)
					{
						float EFX = RND->getFromIntTo(_Fzm[i]->getPos().left, _Fzm[i]->getPos().right);
						float EFY = RND->getFromIntTo(_Fzm[i]->getPos().top, _Fzm[i]->getPos().top + 50);
						_slashEffect.addEffect(EFX, EFY, 1, "상자깨지기이펙트");
					}
					for (int j = 0; j < 3; j++)
					{
						float EFX = RND->getFromIntTo(_Fzm[i]->getPos().left, _Fzm[i]->getPos().right);
						float EFY = RND->getFromIntTo(_Fzm[i]->getPos().top, _Fzm[i]->getPos().top + 50);
						_slashEffect.addEffect(EFX, EFY, 1, "베기먼지");
					}

					float slashX = _Fzm[i]->getPos().left;
					float slashY = _Fzm[i]->getPos().top;
					_slashEffect.addSlashEffect(slashX, slashY, 1, "베기");
				}
				createBoxEF = false;
				zombieFM.push_back(i);
			}
		}
		for (int i = 0; i < _Fzm.size(); i++)
		{
			if (IntersectRect(&_collider, &PLAYER->getATKRange(), &_Fzm[i]->getPos()))
			{
				_zombieDiePosX = _Fzm[i]->getPos().left;
				_zombieDiePosY = _Fzm[i]->getPos().top;
				float knockBackX = PLAYER->getPlayerCenter() > _Fzm[i]->getCenter() ? _knockBackMagnitude : -_knockBackMagnitude;
				float knockBackY = 0;  
				PLAYER->setKnockback(knockBackX, knockBackY);
				_Fzm[i]->setDie(true);
				applyShake(_initialShakeDuration);
				createBoxEF = true;
				if (createBoxEF)
				{
					for (int k = 0; k < 8; k++)
					{
						float EFX = RND->getFromIntTo(_Fzm[i]->getPos().left, _Fzm[i]->getPos().right);
						float EFY = RND->getFromIntTo(_Fzm[i]->getPos().top , _Fzm[i]->getPos().top+50);
						_slashEffect.addEffect(EFX, EFY, 1, "상자깨지기이펙트검은색");
					}
					for (int j = 0; j < 3; j++)
					{
						float EFX = RND->getFromIntTo(_Fzm[i]->getPos().left, _Fzm[i]->getPos().right);
						float EFY = RND->getFromIntTo(_Fzm[i]->getPos().top, _Fzm[i]->getPos().top +50);
						_slashEffect.addEffect(EFX, EFY, 1, "상자깨지기이펙트");
					}
					for (int j = 0; j < 3; j++)
					{
						float EFX = RND->getFromIntTo(_Fzm[i]->getPos().left, _Fzm[i]->getPos().right);
						float EFY = RND->getFromIntTo(_Fzm[i]->getPos().top, _Fzm[i]->getPos().top+50);
						_slashEffect.addEffect(EFX, EFY, 1, "베기먼지");
					}

					float slashX = _Fzm[i]->getPos().left;
					float slashY = _Fzm[i]->getPos().top;
					_slashEffect.addSlashEffect(slashX, slashY, 1, "베기");
				}
				createBoxEF = false;
				zombieFM.push_back(i);
			}

			
		}
		
		for (size_t i : zombieFM)
		{
			POINT position = { _zombieDiePosX, _zombieDiePosY };
			createFragments(_Zfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_4.png", 1);
			createFragments(_Zfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_bustedHead.png", 1);
			createFragments(_Zfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_Core.png", 1);
			createFragments(_Zfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_4.png", 1);
			createFragments(_Zfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_bustedHead.png", 1);
			createFragments(_Zfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_Core.png", 1);
		}
		for (auto it = zombieFM.rbegin(); it != zombieFM.rend(); ++it)
		{
			_Fzm.erase(_Fzm.begin() + *it);
		}
		// 파편 업데이트
		for (auto& fragment : _Zfragments)
		{
			fragment.Update(0.16f , IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _offsetX, _offsetY);
		}

		if ((_pPosRc.left + _pPosRc.right) / 2 > 1280)
		{	//_renderBreakGlass = true;
			//_renderDoor = false;
			_pPosRc = RectMake(0, PLAYER->getPlayerPos().top - 80, 74, 74);
			_offsetX += 80;
			_switchScreen = true;
			if (_offsetX == 6400)
			{
				_currentMap = map5;
				_switchScreen = false;

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
			_switchScreen = true;
			if (_offsetX == 2600)
			{
				_switchScreen = false;
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
			_switchScreen = true;
			_offsetX += 80;
			if (_offsetX == 3880)
			{
				_switchScreen = false;
				_currentMap = map6;

				PLAYER->setPlayerPos(_pPosRc);
			}
		}
		if ((_pPosRc.left + _pPosRc.right) / 2 < 0 && _offsetY > 600)
		{

			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top - 80, 74, 74);
			_offsetX -= 80;
			_switchScreen = true;
			if (_offsetX == 0)
			{
				_switchScreen = false;
				_currentMap = map8;

				PLAYER->setPlayerPos(_pPosRc);
			}
		}
		if ((_pPosRc.left + _pPosRc.right) / 2 < 0 && _offsetY < 600)
		{

			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top - 80, 74, 74);
			_offsetX -= 80;
			_switchScreen = true;
			if (_offsetX == 0)
			{
				_switchScreen = false;
				_currentMap = map9;

				PLAYER->setPlayerPos(_pPosRc);
			}
		}

		std::vector<size_t> breakIndices;

		// 박스
		for (size_t i = 0; i < _box2.size(); i++)
		{
			
			if (IntersectRect(&_collider, &PLAYER->getPlayerPos(), &_box2[i].rc))
			{
				if (_box2[i].rc.right-10 < PLAYER->getPlayerPos().left)
				{
					PLAYER->setColLeft(true);
					cout << " ㅇ오른쪽에서박아" << endl;
				}
				else if (_box2[i].rc.left+10 > PLAYER->getPlayerPos().right)
				{
					PLAYER->setColRight(true);
					cout << "왼쪽에서박아" << endl;
				}
				
			}

			if (IntersectRect(&_collider, &PLAYER->getATKRange(), &_box2[i].rc))
			{
				cout << "상자 맞았다" << endl;
				applyShake(_initialShakeDuration);
				createBoxEF = true;
				if (createBoxEF)
				{
					for (int k = 0; k < 8; k++)
					{
						float EFX = RND->getFromIntTo(_box2[i].rc.left, _box2[i].rc.right);
						float EFY = RND->getFromIntTo(_box2[i].rc.bottom - 40, _box2[i].rc.bottom);
						_slashEffect.addEffect(EFX, EFY, 1, "상자깨지기이펙트검은색");
					}
					for (int j = 0; j < 3; j++)
					{
						float EFX = RND->getFromIntTo(_box2[i].rc.left, _box2[i].rc.right);
						float EFY = RND->getFromIntTo(_box2[i].rc.bottom - 40, _box2[i].rc.bottom);
						_slashEffect.addEffect(EFX, EFY, 1, "상자깨지기이펙트");
					}
					for (int j = 0; j < 3; j++)
					{
						float EFX = RND->getFromIntTo(_box2[i].rc.left, _box2[i].rc.right);
						float EFY = RND->getFromIntTo(_box2[i].rc.bottom - 40, _box2[i].rc.bottom);
						_slashEffect.addEffect(EFX, EFY, 1, "베기먼지");
					}

					float slashX = _box2[i].rc.left;
					float slashY = (_box2[i].rc.top + _box2[i].rc.bottom) / 2;
					_slashEffect.addSlashEffect(slashX, slashY, 1, "베기");
				}
				createBoxEF = false;
				breakIndices.push_back(i);
			}
		}
		// 파괴된 상자의 인덱스를 사용해 파편 생성
		for (size_t i : breakIndices)
		{
			POINT position = { _box2[i].rc.left, _box2[i].rc.top };
			createFragments(m_fragments, position, L"Resources/Images/Stage1/Object/BoxBreak.png", 5);
		}
		// 상자 목록에서 파괴된 상자를 제거
		for (auto it = breakIndices.rbegin(); it != breakIndices.rend(); ++it)
		{
			_box2.erase(_box2.begin() + *it);
		}
		// 파편 업데이트
		for (auto& fragment : m_fragments)
		{
			fragment.Update(0.16f, IMAGEMANAGER->findImage("스테이지1픽셀")->getMemDC(), _offsetX, _offsetY);
		}
		moveCamera(400,600,400,1280,2600,800);

		
	}


	if (_currentMap == map8)
	{
		if ((_pPosRc.left + _pPosRc.right) / 2 > 1280)
		{
	
			_pPosRc = RectMake(0, PLAYER->getPlayerPos().top - 80, 74, 74);
			_switchScreen = true;
			_offsetX += 80;
			if (_offsetX == 1280)
			{
				_switchScreen = false;
				_currentMap = map7;

				PLAYER->setPlayerPos(_pPosRc);
			}
		}
		efKunai();
		if (IntersectRect(&_collider, &PLAYER->getPlayerPos(), &_kunaigetCOl) && !_kunaiGet)
		{
			_UIkunaiRender = true;
			UI->btnUPAnim();

			PLAYER->setcolKunai(true);
			if (PLAYER->getUsingKunai())
			{
				PLAYER->setcolKunai(false);
			}
			if (PLAYER->getTxtKunai())
			{
				_kunaiGet = true;
				_renderKunai = false;
			}

		}
		else
		{
			_UIkunaiRender = false;
			PLAYER->setcolKunai(false);
		}
		if (PLAYER->getTxtKunai())
		{
			UI->btnEndterAnim();
		}

		if (PLAYER->getPanalKunai())
		{
			_panalKunaiCnt++;
			if (_panalKunaiOffsetY > 0 && _panalKunaiCnt < 200)
			{
				_panalKunaiOffsetY -= 50;
			}

			if (_panalKunaiCnt > 200)
			{
				if (_panalKunaiOffsetY <= 800)
				{
					_panalKunaiOffsetY += 50;
				}
				else
				{
					_panalKunaiCnt = 0;
					PLAYER->setPanalKunai(false);
				}



			}
			PLAYER->setcolKunai(false);
			//cout << _panalCnt << endl;

		}

	}

	if (_currentMap == map9)
	{
		if ((_pPosRc.left + _pPosRc.right) / 2 < 150)
		{
			_goStage2 = true;
			cout << "stage2" << endl;
		}
	
	}
	
	if (PLAYER->getShoot())
	{
		_initialShakeDuration = 0.1f;
		applyShake(_initialShakeDuration);
	}
	if (PLAYER->getHp() < 30)
	{
		UI->lowHpUpdate();
	}
	//_zombieManager.update(_offsetX, _offsetY);
	_slashEffect.update();

} 

void Stage1::render(void)
{
	
	
	IMAGEMANAGER->render("스테이지1", getMemDC(), 0 - _shakeOffsetX, 0 - _shakeOffsetY, _offsetX, _offsetY, 8960, 1600);
	_slashEffect.render(getMemDC());
	if (PLAYER->getHp() < 30)
	{
		UI->lowHpRender(getMemDC());
	}

	UI->panalHpRender(getMemDC());

	if (!_switchScreen)
	{
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
				IMAGEMANAGER->frameRender("유리관", getMemDC(), 602, 420);
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
			IMAGEMANAGER->render("문", getMemDC(), 1255, 437, 0, _cutDoorR, 55, 225);

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
			}
			if (PLAYER->getTxtKnife())
			{
				UI->txtRender(getMemDC(), "일본도텍스트");
				UI->btnEnterRender(getMemDC(), "일본도텍스트");
			}
			if (PLAYER->getPanalKnife())
			{
				IMAGEMANAGER->render("일본도획득", getMemDC(), 0, _panalOffsetY);
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

			if (_currentMap == map6)
			{
				for (int i = 0; i < _Fzm.size(); i++)
				{
					if (_Fzm[i]->getDie() == false)
					{
						DrawRectMake(getMemDC(), _Fzm[i]->getRange());
						DrawRectMake(getMemDC(), _Fzm[i]->getPos());
					}
				}
			}



		}


		if (_currentMap == map5)
		{

			for (auto it = _obj.begin(); it != _obj.end(); ++it)
			{
				IMAGEMANAGER->render("상자", getMemDC(), it->rc.left, it->rc.top);
			}

			// 파편 렌더링
			for (auto& fragment : m_fragments)
			{
				fragment.RotateRender(static_cast<int>(fragment.GetPosition().x),
					static_cast<int>(fragment.GetPosition().y),
					72,     // 파편의 너비 설정
					40);    // 파편의 높이 설정
			}

		}


		if (_currentMap == map6)
		{
			//_zm->render();
		//	_zombieManager.render();
			for (int i = 0; i < _Fzm.size(); i++)
			{
				_Fzm[i]->render();
			}

			for (int i = 0; i < _Zfragments.size(); i++)
			{
				auto& fragment = _Zfragments[i];
				switch (i % 3)
				{
				case 0:
					fragment.RotateRender(static_cast<int>(fragment.GetPosition().x),
						static_cast<int>(fragment.GetPosition().y),
						26,
						34);
					break;
				case 1:
					fragment.RotateRender(static_cast<int>(fragment.GetPosition().x),
						static_cast<int>(fragment.GetPosition().y),
						58,
						44);
					break;
				case 2:
					fragment.RotateRender(static_cast<int>(fragment.GetPosition().x),
						static_cast<int>(fragment.GetPosition().y),
						46,
						30);
					break;

				}


			}
			/*	for (auto& fragment : _Zfragments)
				{
					fragment.RotateRender(static_cast<int>(fragment.GetPosition().x),
						static_cast<int>(fragment.GetPosition().y),
						46,
						30);

				}*/
				//IMAGEMANAGER->render("배경시체", getMemDC(), _bgImage.left, _bgImage.top);

				//DrawRectMake(getMemDC(), _bgImage);
		}

		if (_currentMap == map7)
		{

			for (auto it = _box2.begin(); it != _box2.end(); ++it)
			{
				IMAGEMANAGER->render("상자", getMemDC(), it->rc.left, it->rc.top);
			}

			// 파편 렌더링
			for (auto& fragment : m_fragments)
			{
				fragment.RotateRender(static_cast<int>(fragment.GetPosition().x),
					static_cast<int>(fragment.GetPosition().y),
					72,     // 파편의 너비 설정
					40);    // 파편의 높이 설정
			}
		}

		if (_currentMap == map8)
		{
		//	_kunaigetCOl = RectMake(350, 550, 100, 100);
		//	DrawRectMake(getMemDC(), _kunaigetCOl);
		//	IMAGEMANAGER->render("쿠나이", getMemDC(), _kunaigetCOl.left, _kunaigetCOl.top);
		//	IMAGEMANAGER->render("쿠나이획득", getMemDC(),0, _kunaipanalOffsetY);
			if (_renderKunai && !_kunaiGet)
			{
				IMAGEMANAGER->frameRender("쿠나이이펙트", getMemDC(), _kunaigetCOl.left, _kunaigetCOl.top);
				IMAGEMANAGER->render("쿠나이", getMemDC(), _kunaigetCOl.left+30, _kunaigetCOl.top+30);

			}
			if (_UIkunaiRender && !_kunaiGet)
			{
				UI->btnUPRender(getMemDC());
			}
			if (PLAYER->getTxtKunai())
			{
				UI->txtRender(getMemDC(), "쿠나이텍스트");
				UI->btnEnterRender(getMemDC(), "쿠나이텍스트");
			}
			if (PLAYER->getPanalKunai())
			{
				IMAGEMANAGER->render("쿠나이획득", getMemDC(), 0, _panalKunaiOffsetY);
			}
			if (!_kunaiGet)
			{
				_kunaigetCOl = RectMake(300, 600, 140, 100);
			}
		}

		


	}
	


	if (_createPlayer)
	{
		PLAYER->render(getMemDC());

	}
	char ptMouse[128];
	char ptOffset[128];
	char ptPlayerPos[128];
	
	wsprintf(ptMouse, "x : %d y : %d", _ptMouse.x, _ptMouse.y);
	wsprintf(ptOffset, "offsetX : %d  offsetY : %d", _offsetX, _offsetY);
	wsprintf(ptPlayerPos, "x : %d y : %d", PLAYER->getPlayerPos().left, PLAYER->getPlayerPos().top);
	
	
	TextOut(getMemDC(), 100, 100, ptMouse, strlen(ptMouse));
	TextOut(getMemDC(), 100, 120, ptOffset, strlen(ptOffset));
	TextOut(getMemDC(), 100, 140, ptPlayerPos, strlen(ptPlayerPos));


	
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

//void Stage1::addFragment(const Fragment& fragment)
//{
//	_fragments.push_back(fragment);
//}

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

void Stage1::efKunai()
{
	_kunaiCnt++;
	if (_kunaiCnt % 3 == 0)
	{
		_kunaiIdx++;

		if (_kunaiIdx > 7)
		{
			_kunaiIdx = 0;
			_kunaiCnt = 0;
		}
		IMAGEMANAGER->findImage("쿠나이이펙트")->setFrameX(_kunaiIdx);
	}
}




void Stage1::moveCamera(int LcameraOffsetX,int RcameraOffsetX, int cameraOffsetY, int LmaxOffsetX, int RmaxOffsetX, int maxOffsetY)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (PLAYER->getPlayerPos().left < LcameraOffsetX && _offsetX > LmaxOffsetX)
		{
			_offsetX -= 8;
			PLAYER->_dustEffect.setRight(8.f);
			_slashEffect.setRight(8.f);
			PLAYER->_bullet.setRight(8.f);
			if (_currentMap == map5)
			{
				
			}
			if (_currentMap == map6)
			{
				
				for (int i = 0; i < _Fzm.size(); i++)
				{
					_Fzm[i]->setPosLeft(8);
				}
				for (auto& fragment : _Zfragments)
				{
					fragment.SetPosition(fragment.GetPosition().x + 8, fragment.GetPosition().y);

				}
			}

			if (_currentMap == map7)
			{
				for (int i = 0; i < _box2.size(); i++)
				{
					_box2[i].rc.left += 8;
					_box2[i].rc.right += 8;
				}
				for (auto& fragment : m_fragments)
				{
					fragment.SetPosition(fragment.GetPosition().x + 8, fragment.GetPosition().y);
				}
			}
			PLAYER->setPlayerPosLeft(8);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (PLAYER->getPlayerPos().left > RcameraOffsetX && _offsetX < RmaxOffsetX)
		{
			_offsetX += 8;
			PLAYER->_dustEffect.setLeft(8.f);
			PLAYER->_bullet.setLeft(8.f);
			_slashEffect.setLeft(8.f);
			if (_currentMap == map5)
			{

			}
			if (_currentMap == map6)
			{
			
				//_zombieDiePosX -= 8;
				for (int i = 0; i < _Fzm.size(); i++)
				{
					_Fzm[i]->setPosRight(8);
				}
				for (auto& fragment : _Zfragments)
				{
					fragment.SetPosition(fragment.GetPosition().x - 8, fragment.GetPosition().y);
				}
			}
			
			if (_currentMap == map7)
			{
				for (int i = 0; i < _box2.size(); i++)
				{
					_box2[i].rc.left -= 8;
					_box2[i].rc.right -= 8;
				}
				for (auto& fragment : m_fragments)
				{
					fragment.SetPosition(fragment.GetPosition().x - 8, fragment.GetPosition().y);
				}
			}
			PLAYER->setPlayerPosRight(8);
		}

	}

	//상하
	if (PLAYER->getPlayerPos().top < cameraOffsetY && _offsetY > 0)
	{

		_offsetY -= cameraOffsetY - PLAYER->getPlayerPos().top;
		_slashEffect.setBottom(cameraOffsetY - PLAYER->getPlayerPos().top);
	
		if (_currentMap == map5)
		{
			for (int i = 0; i < _obj.size(); i++)
			{
				_obj[i].rc.top += cameraOffsetY - PLAYER->getPlayerPos().top;
				_obj[i].rc.bottom += cameraOffsetY - PLAYER->getPlayerPos().top;
			}
			for (auto& fragment : m_fragments)
			{
				fragment.SetPosTop(cameraOffsetY - PLAYER->getPlayerPos().top);
			}
		}
		if (_currentMap == map6)
		{
			
			for (int i = 0; i < _Fzm.size(); i++)
			{
				_Fzm[i]->setPosTop(cameraOffsetY - PLAYER->getPlayerPos().top);
			}
			for (auto& fragment : _Zfragments)
			{
				fragment.SetPosTop(cameraOffsetY - PLAYER->getPlayerPos().top);
			}
		}
		
		if (_currentMap == map7)
		{
			for (int i = 0; i < _box2.size(); i++)
			{
				_box2[i].rc.top += cameraOffsetY - PLAYER->getPlayerPos().top;
				_box2[i].rc.bottom += cameraOffsetY - PLAYER->getPlayerPos().top;
			}
			for (auto& fragment : m_fragments)
			{
				fragment.SetPosTop(cameraOffsetY - PLAYER->getPlayerPos().top);
			}

		}
		PLAYER->setPlayerPosTop(cameraOffsetY - PLAYER->getPlayerPos().top);
	}
	if (PLAYER->getPlayerPos().top > cameraOffsetY && _offsetY < maxOffsetY)
	{
	
		_offsetY += PLAYER->getPlayerPos().top - cameraOffsetY;
		_slashEffect.setTop(PLAYER->getPlayerPos().top - cameraOffsetY);
		if (_currentMap == map5)
		{
			for (int i = 0; i < _box2.size(); i++)
			{
				_obj[i].rc.top -= PLAYER->getPlayerPos().top - cameraOffsetY;
				_obj[i].rc.bottom -= PLAYER->getPlayerPos().top - cameraOffsetY;
			}
			for (auto& fragment : m_fragments)
			{
				fragment.SetPosBottom(PLAYER->getPlayerPos().top - cameraOffsetY);
			}
		}
		if (_currentMap == map6)
		{

			for (int i = 0; i < _Fzm.size(); i++)
			{
				_Fzm[i]->setPosBottom(PLAYER->getPlayerPos().top - cameraOffsetY);
			}
			for (auto& fragment : _Zfragments)
			{
				fragment.SetPosBottom(PLAYER->getPlayerPos().top - cameraOffsetY);
			}
		}

		if (_currentMap == map7)
		{
			for (int i = 0; i < _box2.size(); i++)
			{
				_box2[i].rc.top -= PLAYER->getPlayerPos().top - cameraOffsetY;
				_box2[i].rc.bottom -= PLAYER->getPlayerPos().top - cameraOffsetY;
			}
			for (auto& fragment : m_fragments)
			{
				fragment.SetPosBottom(PLAYER->getPlayerPos().top - cameraOffsetY);
			}

		}

		
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

void Stage1::updateShakeEffect(float& shakeDuration, float& shakeOffsetX, float& shakeOffsetY)
{
	if (shakeDuration > 0)
	{
		shakeDuration -= 0.016f; 

		shakeOffsetX = (rand() % (int)(_initialShakeMagnitude * 2 + 1) - _initialShakeMagnitude) * sin(2 * PI * shakeDuration / _initialShakeDuration);
		shakeOffsetY = (rand() % (int)(_initialShakeMagnitude * 2 + 1) - _initialShakeMagnitude) * sin(2 * PI * shakeDuration / _initialShakeDuration);
	}
	else
	{
		shakeOffsetX = 0.0f;
		shakeOffsetY = 0.0f;
	}
}

void Stage1::applyShake(float shakeDuration)
{
	_shakeDuration = shakeDuration;
}

void Stage1::createFragments(std::vector<Fragment>& fragments, const POINT& position, wchar_t* imagePath, int numFragments)
{
	const float gravity = 9.81f;
	for (int i = 0; i < numFragments; i++)
	{
		Fragment fragment;
		fragment.SetPosition(static_cast<float>(position.x), static_cast<float>(position.y));
		float velocityX = static_cast<float>(rand() % 21 - 10) * 2.0f;
		float velocityY = static_cast<float>(rand() % 16 - 15) * 2.0f;
		fragment.SetVelocity(velocityX, velocityY);
		fragment.SetAcceleration(0, gravity);
		fragment.SetRotation(RND->getFloat(10.f));
		fragment.LoadImage(imagePath);
		fragments.push_back(fragment);
	}
}

