#include "Stdafx.h"
#include "Stage2.h"

HRESULT Stage2::init(void)
{
	
	_offsetX = 0;
	_offsetY = 0;
	_rot = new RotationRender;
	_rot->init();
	_switchScreen = false;
	_kunaiCOl.init();
	_renderGun = true;
	_currentMap = map1;
	_gungetCOl = RectMake(300, 600, 140, 100);

	_zm = new Zombiebot;
	_zm->init();
	_zm->setPos(2200, 1330);
	_Fzm.push_back(_zm);
	for (int i = 0; i < 3; i++)
	{
		_zm = new Zombiebot;
		_zm->init();
		_zm->setPos(3000 + (i * 300), 1330);   //670
		_Fzm.push_back(_zm);

	}

	return S_OK;
}

void Stage2::release(void)
{
}

void Stage2::update(void)
{
	PLAYER->update();
	PLAYER->_dustEffect.update();
	_pPosRc.left = PLAYER->getPlayerPos().left;
	_pPosRc.right = PLAYER->getPlayerPos().right;
	_pPosRc.top = PLAYER->getPlayerPos().top;
	_pPosRc.bottom = PLAYER->getPlayerPos().bottom;
	playerPixel();
	updateShakeEffect(_shakeDuration, _shakeOffsetX, _shakeOffsetY);

	if (_currentMap == map1)
	{
		moveCamera(400, 600, 400, 0, 3840, 800);
		//800 1600;
		if (PLAYER->getPlayerPos().bottom > 600 && _offsetY < 1600)
		{
			_offsetY += PLAYER->getPlayerPos().bottom - 600;
			PLAYER->setPlayerPosBottom(PLAYER->getPlayerPos().bottom - 600);
			if (_offsetY > 1600)
			{
				_currentMap = map2;
				_offsetX = 3840;
			}
		}
		updateZombieBot();


	}
	if (_currentMap == map2)
	{
		if ((_pPosRc.left + _pPosRc.right) / 2 < 0)
		{

			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top - 40, 74, 74);
			_offsetX -= 80;
			_switchScreen = true;
			if (_offsetX == 2560)
			{
				_switchScreen = false;
				_currentMap = map3;
				PLAYER->setPlayerPos(_pPosRc);

			}
		}
	}

	if (_currentMap == map3)
	{
		if ((_pPosRc.left + _pPosRc.right) / 2 < 0)
		{

			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top - 40, 74, 74);
			_offsetX -= 80;
			_switchScreen = true;
			if (_offsetX == 1280)
			{
				_switchScreen = false;
				_currentMap = map4;
				PLAYER->setPlayerPos(_pPosRc);

			}
		}

		if ((_pPosRc.right + _pPosRc.left) / 2 > 1280) //맵 넘기기
		{
		
			_pPosRc = RectMake(0, PLAYER->getPlayerPos().top - 40, 74, 74);
			_offsetX += 80;
			_switchScreen = true;
			if (_offsetX == 3840)
			{
				_switchScreen = false;
				_currentMap = map2;
				PLAYER->setPlayerPos(_pPosRc);
			}
		}

		//총==
		efGun();
		if (IntersectRect(&_collider, &PLAYER->getPlayerPos(), &_gungetCOl) && !_gunGet)
		{
			_UIGunRender = true;
			UI->btnUPAnim();

			PLAYER->setcolGun(true);
			if (PLAYER->getUsingGun())
			{
				PLAYER->setcolGun(false);
			}
			if (PLAYER->getTxtGun())
			{
				_gunGet = true;
				_renderGun = false;
			}

		}
		else
		{
			_UIGunRender = false;
			PLAYER->setcolGun(false);
		}
		if (PLAYER->getTxtGun())
		{
			UI->btnEndterAnim();
		}

		if (PLAYER->getPanalGun())
		{
			_panalGunCnt++;
			if (_panalGunOffsetY > 0 && _panalGunCnt < 200)
			{
				_panalGunOffsetY -= 50;
			}

			if (_panalGunCnt > 200)
			{
				if (_panalGunOffsetY <= 800)
				{
					_panalGunOffsetY += 50;
				}
				else
				{
					_panalGunCnt = 0;
					PLAYER->setPanalGun(false);
				}



			}
			PLAYER->setcolGun(false);
			//cout << _panalCnt << endl;

		}





	}
	if (_currentMap == map4)
	{
		if ((_pPosRc.left + _pPosRc.right) / 2 < 0)
		{

			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top - 40, 74, 74);
			_offsetX -= 80;
			_switchScreen = true;
			if (_offsetX == 2560)
			{
				_switchScreen = false;
				_currentMap = map3;
				PLAYER->setPlayerPos(_pPosRc);

			}
		}
		if (PLAYER->getPlayerPos().bottom > 800)
		{
			_goStage3 = true;
			cout << "스테이지3" << endl;
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

	_slashEffect.update();

	
}

void Stage2::render(void)
{
	IMAGEMANAGER->render("스테이지2", getMemDC(), 0 - _shakeOffsetX, 0 - _shakeOffsetY, _offsetX, _offsetY, 5120, 2400);
	_slashEffect.render(getMemDC());
	if (PLAYER->getHp() < 30)
	{
		UI->lowHpRender(getMemDC());
	}

	UI->panalHpRender(getMemDC());



	if (_currentMap == map1)
	{
		renderZombieBot();
	}

	if (_currentMap == map3)
	{
		if (_renderGun && !_gunGet)
		{
			IMAGEMANAGER->frameRender("총이펙트", getMemDC(), _gungetCOl.left, _gungetCOl.top);
			IMAGEMANAGER->render("총", getMemDC(), _gungetCOl.left + 30, _gungetCOl.top + 30);

		}
		if (_UIGunRender && !_gunGet)
		{
			UI->btnUPRender(getMemDC());
		}
		if (PLAYER->getTxtGun())
		{
			UI->txtRender(getMemDC(), "총텍스트");
			UI->btnEnterRender(getMemDC(), "총텍스트");
		}
		if (PLAYER->getPanalGun())
		{
			IMAGEMANAGER->render("총획득", getMemDC(), 0, _panalGunOffsetY);
		}
		if (!_gunGet)
		{
			_gungetCOl = RectMake(300, 600, 140, 100);
		}
	}

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		IMAGEMANAGER->render("스테이지2픽셀", getMemDC(), 0, 0, _offsetX, _offsetY, 5120, 2400);

	}

	PLAYER->render(getMemDC());

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

void Stage2::efGun()
{
	_gunCnt++;
	if (_gunCnt % 3 == 0)
	{
		_gunIdx++;

		if (_gunIdx > 7)
		{
			_gunIdx = 0;
			_gunCnt = 0;
		}
		IMAGEMANAGER->findImage("총이펙트")->setFrameX(_gunIdx);
	}
}

void Stage2::playerPixel()
{

	//==픽셀 충돌==
	int Rlb = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지2픽셀")->getMemDC(), _pPosRc.left + _offsetX,   _pPosRc.bottom + _offsetY + 3));
	int Rlbup = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지2픽셀")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.bottom + _offsetY - 5));

	int Rrb = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지2픽셀")->getMemDC(), _pPosRc.right + _offsetX,   _pPosRc.bottom + _offsetY));
	int Rrbup = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지2픽셀")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.bottom + _offsetY - 5));

	int Rlt = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지2픽셀")->getMemDC(), _pPosRc.left + _offsetX,  _pPosRc.top + _offsetY)); //r131
	int Rrt = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지2픽셀")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.top + _offsetY));

	int Glb = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지2픽셀")->getMemDC(), _pPosRc.left + _offsetX,  _pPosRc.bottom + _offsetY));
	int Grb = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지2픽셀")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.bottom + _offsetY));
	int Glt = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지2픽셀")->getMemDC(), _pPosRc.left + _offsetX,  _pPosRc.top + _offsetY));
	int Grt = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지2픽셀")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.top + _offsetY)); //g134

	int GCR = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지2픽셀")->getMemDC(), _pPosRc.right + _offsetX, (_pPosRc.top + _pPosRc.bottom) / 2 + _offsetY)); //g134
	int GCL = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지2픽셀")->getMemDC(), _pPosRc.left + _offsetX, (_pPosRc.top + _pPosRc.bottom) / 2 + _offsetY));

	if (PLAYER->getUsingKunai())
	{
		_kunaiCOl.kunaiCollision(IMAGEMANAGER->findImage("스테이지2픽셀")->getMemDC(), _offsetX, _offsetY);
	}
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
}

void Stage2::moveCamera(int LcameraOffsetX, int RcameraOffsetX, int cameraOffsetY, int LmaxOffsetX, int RmaxOffsetX, int maxOffsetY)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (PLAYER->getPlayerPos().left < LcameraOffsetX && _offsetX > LmaxOffsetX)
		{
			_offsetX -= 8;
			PLAYER->_dustEffect.setRight(8.f);
			_slashEffect.setRight(8.f);
			if (_currentMap == map1)
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

			PLAYER->_bullet.setRight(8.f);
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
			if (_currentMap == map1)
			{
				for (int i = 0; i < _Fzm.size(); i++)
				{
					_Fzm[i]->setPosRight(8);
				}
				for (auto& fragment : _Zfragments)
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
		if (_currentMap == map1)
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
		
		PLAYER->setPlayerPosTop(cameraOffsetY - PLAYER->getPlayerPos().top);
	}
	if (PLAYER->getPlayerPos().top > cameraOffsetY && _offsetY < maxOffsetY)
	{

		_offsetY += PLAYER->getPlayerPos().top - cameraOffsetY;
		_slashEffect.setTop(PLAYER->getPlayerPos().top - cameraOffsetY);
		if (_currentMap == map1)
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


		PLAYER->setPlayerPosBottom(PLAYER->getPlayerPos().top - cameraOffsetY);
	}

}

void Stage2::updateShakeEffect(float& shakeDuration, float& shakeOffsetX, float& shakeOffsetY)
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

void Stage2::applyShake(float shakeDuration)
{
	_shakeDuration = shakeDuration;
}


void Stage2::updateZombieBot()
{
	for (int i = 0; i < _Fzm.size(); i++)
	{
		_Fzm[i]->UpdateZombie();
	}
	//좀비 추적범위
	for (int i = 0; i < _Fzm.size(); i++)
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
				if (_zomIdleCnt % RND->getFromIntTo(200, 500) == 0)
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
		fragment.Update(0.16f, IMAGEMANAGER->findImage("스테이지2픽셀")->getMemDC(), _offsetX, _offsetY);
	}
}

void Stage2::renderZombieBot()
{
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
}


void Stage2::createFragments(std::vector<Fragment>& fragments, const POINT& position, wchar_t* imagePath, int numFragments)
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