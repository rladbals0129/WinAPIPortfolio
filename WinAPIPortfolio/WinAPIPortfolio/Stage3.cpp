#include "Stdafx.h"
#include "Stage3.h"

HRESULT Stage3::init(void)
{
	PLAYER->setPlayerPos(600, 0);
	_offsetX = 0;
	_offsetY = 0;
	_rot = new RotationRender;
	_rot->init();
	_switchScreen = false;
	_currentMap = map1;
	_kunaiCOl.init();

	_boss = new Boss;
	_boss->init();
	_bossgetCOl = RectMake(400, 630, 240, 80);
	_zm = new Zombiebot;
	_zm->init();
	_zm->setPos(440, 510);
	_Fzm.push_back(_zm);
	_zm = new Zombiebot;
	_zm->init();
	_zm->setPos(760, 510);
	_Fzm.push_back(_zm);
	_zm = new Zombiebot;
	_zm->init();
	_zm->setPos(1120, 510);
	_Fzm.push_back(_zm);
	_renderBoss = true;

	return S_OK;
}

void Stage3::release(void)
{
}

void Stage3::update(void)
{
	PLAYER->update();
	PLAYER->_dustEffect.update();
	playerPixel();
	updateShakeEffect(_shakeDuration, _shakeOffsetX, _shakeOffsetY);
	updateZombieBot();
	_knockBackMagnitude = 10.0f;
	if (_currentMap == map1)
	{
		if ((_pPosRc.right + _pPosRc.left) / 2 > 1280) //맵 넘기기
		{

			_pPosRc = RectMake(0, PLAYER->getPlayerPos().top - 40, 74, 74);
			_offsetX += 80;
			_switchScreen = true;
			if (_offsetX == 1280)
			{
				_switchScreen = false;
				_currentMap = map2;
				PLAYER->setPlayerPos(_pPosRc);
			}
		}
	}
	if (_currentMap == map2)
	{

		moveCamera(400, 600, 1280,3840);

		if ((_pPosRc.right + _pPosRc.left) / 2 > 1280) //맵 넘기기
		{

			_pPosRc = RectMake(0, PLAYER->getPlayerPos().top - 40, 74, 74);
			_offsetX += 80;
			_switchScreen = true;
			if (_offsetX == 5120)
			{
				_switchScreen = false;
				_currentMap = map3;
				PLAYER->setPlayerPos(_pPosRc);
			}
		}
		if ((_pPosRc.left + _pPosRc.right) / 2 < 0)
		{

			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top - 40, 74, 74);
			_offsetX -= 80;
			_switchScreen = true;
			if (_offsetX == 0)
			{
				_switchScreen = false;
				_currentMap = map1;
				PLAYER->setPlayerPos(_pPosRc);

			}
		}

	//	updateZombieBot();
	}
	if (_currentMap == map3)
	{
		if ((_pPosRc.left + _pPosRc.right) / 2 < 0)
		{

			_pPosRc = RectMake(1180, PLAYER->getPlayerPos().top - 40, 74, 74);
			_offsetX -= 80;
			_switchScreen = true;
			if (_offsetX == 3840)
			{
				_switchScreen = false;
				_currentMap = map2;
				PLAYER->setPlayerPos(_pPosRc);

			}
		}

		if (IntersectRect(&_collider, &PLAYER->getPlayerPos(), &_bossgetCOl) && !_bossGet)
		{
			_UIBossRender = true;
			UI->btnUPAnim();

			PLAYER->setColBoss(true);
			if (PLAYER->getCreateBoss())
			{
				PLAYER->setColBoss(false);
			}
			if (PLAYER->getTxtBoss())
			{
				
				_bossIdx = 1;
				
			}

		}
		else
		{
			_UIBossRender = false;
			PLAYER->setColBoss(false);
		}
		if (PLAYER->getTxtBoss())
		{
			UI->btnEndterAnim();
		}

		if (PLAYER->getPanalBoss())
		{
			_panalBossCnt++;
			if (_panalBossCnt > 200)
			{
				_bossGet = true;
				_renderBoss = false;
				PLAYER->setPanalBoss(false);
				PLAYER->setCreateBoss(true);
			}
			PLAYER->setColBoss(false);
		}



		if (PLAYER->getCreateBoss())
		{
			_boss->update();
		//	updateZombieBot();
			if (IntersectRect(&_collider, &PLAYER->getATKRange(), &_boss->getPos()) && _boss->getCurrentState() != 0)
			{

				if (!_bossHitDelay)
				{

					_boss->setHp(_boss->getHp() - 1);
					_boss->setStateIdle();
					_zombieOnce = false;
					_boss->setHit(true);
					_bossHitDelay = true;

					applyShake(_initialShakeDuration); 

					createBoxEF = true;
					if (createBoxEF)
					{
						for (int k = 0; k < 8; k++)
						{
							float EFX = RND->getFromIntTo(_boss->getPos().left, _boss->getPos().right);
							float EFY = RND->getFromIntTo(_boss->getPos().top, _boss->getPos().top + 50);
							_slashEffect.addEffect(EFX, EFY, 1, "상자깨지기이펙트검은색");
						}
						for (int j = 0; j < 3; j++)
						{
							float EFX = RND->getFromIntTo(_boss->getPos().left, _boss->getPos().right);
							float EFY = RND->getFromIntTo(_boss->getPos().top, _boss->getPos().top + 50);
							_slashEffect.addEffect(EFX, EFY, 1, "상자깨지기이펙트");
						}
						for (int j = 0; j < 3; j++)
						{
							float EFX = RND->getFromIntTo(_boss->getPos().left, _boss->getPos().right);
							float EFY = RND->getFromIntTo(_boss->getPos().top, _boss->getPos().top + 50);
							_slashEffect.addEffect(EFX, EFY, 1, "베기먼지");
						}

						float slashX = _boss->getPos().left;
						float slashY = _boss->getPos().top;
						_slashEffect.addSlashEffect(slashX, slashY, 1, "베기");
					}
					createBoxEF = false;


					//_boss->setPattern(_boss->getPattern() + 1);
				}


			}

			if (_bossHitDelay)
			{
				_bossHitCnt++;
				if (_bossHitCnt % 40 == 0)
				{
					_boss->setHit(false);
					_bossHitDelay = false;
					_bossHitCnt = 0;
					_boss->setPattern(_boss->getPattern() + 1);


					//	cout << _boss->getPattern() << endl;
				}
			}

			if (_boss->getCurrentState() == 2)
			{
				//cout << "좀비소환" << endl;

				if (!_zombieOnce)
				{
					for (int i = 0; i < 3; i++)
					{
						createZombie(300 * (i + 1), 600);
					}

				}
				_zombieOnce = true;

			}


			if (IntersectRect(&_collider, &PLAYER->getPlayerPos(), &_boss->getPos()))
			{
				if (!_hitDelay)
				{
					PLAYER->setDmg(_boss->getAtk());
					PLAYER->setHit(true);
					_hitDelay = true;
					//넉백
					float knockBackX = PLAYER->getPlayerCenter() > _boss->getCenter() ? _knockBackMagnitude : -_knockBackMagnitude;
					float knockBackY = 0; //-_knockBackMagnitude;  
					PLAYER->setKnockback(knockBackX, knockBackY);
					//======
					applyShake(_initialShakeDuration);
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

void Stage3::render(void)
{
	IMAGEMANAGER->render("스테이지3", getMemDC(), 0 - _shakeOffsetX, 0 - _shakeOffsetY, _offsetX, _offsetY, 6400, 800);
	_slashEffect.render(getMemDC());
	if (PLAYER->getHp() < 30)
	{
		UI->lowHpRender(getMemDC());
	}

	UI->panalHpRender(getMemDC());

	if (_currentMap == map2)
	{
		renderZombieBot();
	}
	if (_currentMap == map3)
	{
		cout << _renderBoss <<"    " << _bossGet << endl;
		if (_renderBoss && !_bossGet)
		{
			//IMAGEMANAGER->frameRender("총이펙트", getMemDC(), _bossgetCOl.left, _bossgetCOl.top);
			IMAGEMANAGER->frameRender("보스정지", getMemDC(), _bossgetCOl.left, _bossgetCOl.top, _bossIdx,0);

		}
		if (_UIBossRender && !_bossGet)
		{
			UI->btnUPRender(getMemDC());
		}
		if (PLAYER->getTxtBoss())
		{
			if (PLAYER->getTxtIdx() == 0)
			{
				UI->txtRender(getMemDC(), "보스텍스트1");
				UI->btnEnterRender(getMemDC(), "보스텍스트1");
			}
			else if (PLAYER->getTxtIdx() == 1)
			{
				UI->txtRender(getMemDC(), "보스텍스트2");
				UI->btnEnterRender(getMemDC(), "보스텍스트2");

			}
			else if (PLAYER->getTxtIdx() == 2)
			{
				UI->txtRender(getMemDC(), "보스텍스트3");
				UI->btnEnterRender(getMemDC(), "보스텍스트3");
			}
			else if (PLAYER->getTxtIdx() == 3)
			{
				UI->txtRender(getMemDC(), "보스텍스트4");
				UI->btnEnterRender(getMemDC(), "보스텍스트4");
			}
			
		}
		if (PLAYER->getPanalBoss())
		{
			IMAGEMANAGER->render("보스패널", getMemDC(),207,40);
		}
		if (!_bossGet)
		{
			_bossgetCOl = RectMake(400, 630, 240, 80);
		}




		if (PLAYER->getCreateBoss())
		{
			_boss->render();
			renderZombieBot();
		}
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

void Stage3::playerPixel()
{
	_pPosRc.left = PLAYER->getPlayerPos().left;
	_pPosRc.right = PLAYER->getPlayerPos().right;
	_pPosRc.top = PLAYER->getPlayerPos().top;
	_pPosRc.bottom = PLAYER->getPlayerPos().bottom;
	//==픽셀 충돌==
	int Rlb = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.bottom + _offsetY + 3));
	int Rlbup = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.bottom + _offsetY - 5));

	int Rrb = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.bottom + _offsetY));
	int Rrbup = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.bottom + _offsetY - 5));

	int Rlt = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.top + _offsetY)); //r131
	int Rrt = GetRValue(GetPixel(IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.top + _offsetY));

	int Glb = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.bottom + _offsetY));
	int Grb = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.bottom + _offsetY));
	int Glt = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.top + _offsetY));
	int Grt = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.top + _offsetY)); //g134

	int GCR = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _pPosRc.right + _offsetX, (_pPosRc.top + _pPosRc.bottom) / 2 + _offsetY)); //g134
	int GCL = GetGValue(GetPixel(IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _pPosRc.left + _offsetX, (_pPosRc.top + _pPosRc.bottom) / 2 + _offsetY));


	if (PLAYER->getUsingKunai())
	{
		_kunaiCOl.kunaiCollision(IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _offsetX, _offsetY);
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

void Stage3::updateZombieBot()
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
		fragment.Update(0.16f, IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _offsetX, _offsetY);
	}
}

void Stage3::renderZombieBot()
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

void Stage3::moveCamera(int LcameraOffsetX, int RcameraOffsetX, int LmaxOffsetX, int RmaxOffsetX)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (PLAYER->getPlayerPos().left < LcameraOffsetX && _offsetX > LmaxOffsetX)
		{
			_offsetX -= 8;
			PLAYER->_dustEffect.setRight(8.f);
			_slashEffect.setRight(8.f);
			PLAYER->_bullet.setRight(8.f);
			for (int i = 0; i < _Fzm.size(); i++)
			{
				_Fzm[i]->setPosLeft(8);
			}
			for (auto& fragment : _Zfragments)
			{
				fragment.SetPosition(fragment.GetPosition().x + 8, fragment.GetPosition().y);

			}
			for (int i = 0; i < _Flp.size(); i++)
			{
				_Flp[i]->setPosLeft(8);
			}
			for (auto& fragment : _Lfragments)
			{
				fragment.SetPosition(fragment.GetPosition().x + 8, fragment.GetPosition().y);

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
			for (int i = 0; i < _Fzm.size(); i++)
			{
				_Fzm[i]->setPosRight(8);
			}
			for (auto& fragment : _Zfragments)
			{
				fragment.SetPosition(fragment.GetPosition().x - 8, fragment.GetPosition().y);
			}
			for (int i = 0; i < _Flp.size(); i++)
			{
				_Flp[i]->setPosRight(8);
			}
			for (auto& fragment : _Lfragments)
			{
				fragment.SetPosition(fragment.GetPosition().x - 8, fragment.GetPosition().y);
			}
			_slashEffect.setLeft(8.f);
			PLAYER->setPlayerPosRight(8);
		}

	}

	
}

void Stage3::updateShakeEffect(float& shakeDuration, float& shakeOffsetX, float& shakeOffsetY)
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

void Stage3::applyShake(float shakeDuration)
{
	_shakeDuration = shakeDuration;

}

void Stage3::createFragments(std::vector<Fragment>& fragments, const POINT& position, wchar_t* imagePath, int numFragments)
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

void Stage3::createZombie(int x, int y)
{
	Zombiebot* newZombie = new Zombiebot;
	newZombie->init();
	newZombie->setPos(x, y);
	newZombie->setIsLeft(true);
	//newZombie->setState(2);
	_Fzm.push_back(newZombie);
}

void Stage3::createLipo(int x, int y)
{
	Lipo* newLipo = new Lipo;
	newLipo->init();
	newLipo->setPos(x, y);
	newLipo->setIsLeft(false);
	_Flp.push_back(newLipo);
}

void Stage3::updateLipo()
{
	for (int i = 0; i < _Flp.size(); i++)
	{
		_Flp[i]->UpdateLipo();
	}
	vector<size_t> lipoFM;

	for (int i = 0; i < _Flp.size(); i++)
	{
		if (IntersectRect(&_collider, &PLAYER->getATKRange(), &_Flp[i]->getPos()))
		{
			_zombieDiePosX = _Flp[i]->getPos().left;
			_zombieDiePosY = _Flp[i]->getPos().top;
			float knockBackX = PLAYER->getPlayerCenter() > _Flp[i]->getCenter() ? _knockBackMagnitude : -_knockBackMagnitude;
			float knockBackY = 0;
			PLAYER->setKnockback(knockBackX, knockBackY);
			_Flp[i]->setDie(true);

			applyShake(_initialShakeDuration);
			createBoxEF = true;
			if (createBoxEF)
			{
				for (int k = 0; k < 8; k++)
				{
					float EFX = RND->getFromIntTo(_Flp[i]->getPos().left, _Flp[i]->getPos().right);
					float EFY = RND->getFromIntTo(_Flp[i]->getPos().top, _Flp[i]->getPos().top + 50);
					_slashEffect.addEffect(EFX, EFY, 1, "상자깨지기이펙트검은색");
				}
				for (int j = 0; j < 3; j++)
				{
					float EFX = RND->getFromIntTo(_Flp[i]->getPos().left, _Flp[i]->getPos().right);
					float EFY = RND->getFromIntTo(_Flp[i]->getPos().top, _Flp[i]->getPos().top + 50);
					_slashEffect.addEffect(EFX, EFY, 1, "상자깨지기이펙트");
				}
				for (int j = 0; j < 3; j++)
				{
					float EFX = RND->getFromIntTo(_Flp[i]->getPos().left, _Flp[i]->getPos().right);
					float EFY = RND->getFromIntTo(_Flp[i]->getPos().top, _Flp[i]->getPos().top + 50);
					_slashEffect.addEffect(EFX, EFY, 1, "베기먼지");
				}

				float slashX = _Flp[i]->getPos().left;
				float slashY = _Flp[i]->getPos().top;
				_slashEffect.addSlashEffect(slashX, slashY, 1, "베기");
			}
			createBoxEF = false;

		}
		if (_Flp[i]->getDie())
		{
			applyShake(_initialShakeDuration);
			lipoFM.push_back(i);

		}

	}


	for (size_t i : lipoFM)
	{

		POINT position = { _zombieDiePosX, _zombieDiePosY };
		createFragments(_Lfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_4.png", 1);
		createFragments(_Lfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_bustedHead.png", 1);
		createFragments(_Lfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_Core.png", 1);
		createFragments(_Lfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_4.png", 1);
		createFragments(_Lfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_bustedHead.png", 1);
		createFragments(_Lfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_Core.png", 1);


	}
	for (auto it = lipoFM.rbegin(); it != lipoFM.rend(); ++it)
	{

		_Flp.erase(_Flp.begin() + *it);
	}

	// 파편 업데이트
	for (auto& fragment : _Lfragments)
	{
		fragment.Update(0.16f, IMAGEMANAGER->findImage("스테이지3픽셀")->getMemDC(), _offsetX, _offsetY);
	}
}

void Stage3::renderLipo()
{
	for (int i = 0; i < _Flp.size(); i++)
	{
		_Flp[i]->render();
	}

	for (int i = 0; i < _Lfragments.size(); i++)
	{
		auto& fragment = _Lfragments[i];
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
