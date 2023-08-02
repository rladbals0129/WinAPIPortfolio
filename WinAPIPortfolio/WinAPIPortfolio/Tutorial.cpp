#include "Stdafx.h"
#include "Tutorial.h"

HRESULT Tutorial::init()
{
   
    _goTitle = false;
	_hitCnt = 0;
	_hitDelay = false;
	
	
	_rot = new RotationRender;

	_rot->init();
	//적

	_zombieManager.init();
	_zombieManager.setShakeOffset(_shakeOffsetX, _shakeOffsetY);
	_kunaiCol = new KunaiCollision;
	_kunaiCol->init();

	_knockBackMagnitude = 10.0f;


	

	//버튼//
	const vector<string> buttonTexts = {
	"좀비 생성", "일본도 사용" ,"P90 사용" , "쿠나이 사용"};
	for (int i = 0; i < buttonTexts.size(); i++)
	{
		int x = (i < 4) ? 0 : 1280 - _buttonWidth;
		int y = 100 + i % 4 * (_buttonHeight + 20);
		_buttons.emplace_back(x, y, _buttonWidth, _buttonHeight, buttonTexts[i]);
	}
	//=====================//
	
	return S_OK;
	
}

void Tutorial::relese()
{
}

void Tutorial::update()
{
    if (KEYMANAGER->isOnceKeyDown(VK_BACK))
    {
		_title.init();
        _goTitle = true;
		
    }
	PLAYER->update();
	playerPixel();
	//버튼===========================================
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _buttons.size(); i++)
		{
			if (PtInRect(&_buttons[i].rect, _ptMouse))
			{
				// 버튼 이벤트 처리
				onButtonClick(i);
			}
		}
	}
	//====================================================
	//updateShakeEffect(_shakeDuration, _shakeOffsetX, _shakeOffsetY);
	_zombieManager.update(0,0);

	//updateZombie();

	if (PLAYER->getShoot())
	{
		_initialShakeDuration = 0.1;
		_zombieManager.applyShake(_initialShakeDuration);
	}
}

void Tutorial::render()
{
    IMAGEMANAGER->render("튜토리얼", getMemDC(), 0 - _shakeOffsetX, 0 - _shakeOffsetY);

    if (KEYMANAGER->isToggleKey(VK_F1))
    {
        IMAGEMANAGER->render("튜토리얼픽셀", getMemDC(), 0, 0);
    }

	UI->panalHpRender(getMemDC());



	for (const auto& button : _buttons)
	{
		IMAGEMANAGER->render("버튼", getMemDC(), button.rect.left, button.rect.top, _buttonWidth, _buttonHeight);

		// 텍스트 그리기
		FONTMANAGER->drawText(getMemDC(), button.rect.left + 25, button.rect.top + 30, "Orange Kid", 30, FW_BOLD, (char*)button.text.c_str(), static_cast<int>(button.text.length()), RGB(255, 255, 255));
	}

	_slashEffect.render(getMemDC());
	//플레이어
	PLAYER->render(getMemDC());
	PLAYER->_dustEffect.update();
	//====
	_zombieManager.render();
	//renderZombie();
}


void Tutorial::playerPixel()
{
	_pPosRc.left = PLAYER->getPlayerPos().left;
	_pPosRc.right = PLAYER->getPlayerPos().right;
	_pPosRc.top = PLAYER->getPlayerPos().top;
	_pPosRc.bottom = PLAYER->getPlayerPos().bottom;
	//==픽셀 충돌==
	int Rlb = GetRValue(GetPixel(IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), _pPosRc.left , _pPosRc.bottom + 3));
	int Rlbup = GetRValue(GetPixel(IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), _pPosRc.left, _pPosRc.bottom - 5));

	int Rrb = GetRValue(GetPixel(IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), _pPosRc.right , _pPosRc.bottom ));
	int Rrbup = GetRValue(GetPixel(IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), _pPosRc.right , _pPosRc.bottom - 5));

	int Rlt = GetRValue(GetPixel(IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), _pPosRc.left , _pPosRc.top )); //r131
	int Rrt = GetRValue(GetPixel(IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), _pPosRc.right , _pPosRc.top ));

	int Glb = GetGValue(GetPixel(IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), _pPosRc.left , _pPosRc.bottom ));
	int Grb = GetGValue(GetPixel(IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), _pPosRc.right, _pPosRc.bottom ));
	int Glt = GetGValue(GetPixel(IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), _pPosRc.left , _pPosRc.top ));
	int Grt = GetGValue(GetPixel(IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), _pPosRc.right, _pPosRc.top )); //g134

	int GCR = GetGValue(GetPixel(IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), _pPosRc.right, (_pPosRc.top + _pPosRc.bottom) / 2 )); //g134
	int GCL = GetGValue(GetPixel(IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), _pPosRc.left , (_pPosRc.top + _pPosRc.bottom) / 2 ));

	if (PLAYER->getUsingKunai())
	{
		_kunaiCol->kunaiCollision(IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), 0, 0);
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

void Tutorial::onButtonClick(int buttonIndex)
{
	switch (buttonIndex)
	{
	case 0: // 좀비 생성 버튼
		_zombieManager.createZombie(800, 600);
		//createZombie(800,600);
		break;
	case 1: // 칼 사용 버튼
		PLAYER->setUsingKnife(!PLAYER->getUsingKnife());
		break;
	case 2:
		PLAYER->setUsingGun(!PLAYER->getUsingGun());
		break;
	case 3:
		PLAYER->setUsingKunai(!PLAYER->getUsingKunai());
		
	}
}

void Tutorial::createFragments(std::vector<Fragment>& fragments, const POINT& position, wchar_t* imagePath, int numFragments)
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


void Tutorial::updateShakeEffect(float& shakeDuration, float& shakeOffsetX, float& shakeOffsetY)
{
	if (shakeDuration > 0)
	{
		shakeDuration -= 0.016f; // 상황에 따라 실제 deltaTime으로 변경됩니다.

		shakeOffsetX = (rand() % (int)(_initialShakeMagnitude * 2 + 1) - _initialShakeMagnitude) * sin(2 * PI * shakeDuration / _initialShakeDuration);
		shakeOffsetY = (rand() % (int)(_initialShakeMagnitude * 2 + 1) - _initialShakeMagnitude) * sin(2 * PI * shakeDuration / _initialShakeDuration);
	}
	else
	{
		shakeOffsetX = 0.0f;
		shakeOffsetY = 0.0f;
	}
}

void Tutorial::applyShake(float shakeDuration)
{
	_shakeDuration = shakeDuration;
}






/*
void Tutorial::createZombie(int x, int y)
{
	_zm = new Zombiebot;
	_zm->init();
	_zm->setPos(x, y);   //670
	_zm->setIsLeft(true);
	//_zm->setState(2);
	_Fzm.push_back(_zm);
}

void Tutorial::updateZombie()
{
	//좀비 상태처리
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

	//cout << PLAYER->getHit() << endl;
	//좀비 파티클
	vector<size_t> zombieFM;
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
		_st.createFragments(_Zfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_4.png", 1);
		_st.createFragments(_Zfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_bustedHead.png", 1);
		_st.createFragments(_Zfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_Core.png", 1);
		_st.createFragments(_Zfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_4.png", 1);
		_st.createFragments(_Zfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_bustedHead.png", 1);
		_st.createFragments(_Zfragments, position, L"Resources/Images/Enemy/Zombie/Zombiebot_Core.png", 1);
	}
	for (auto it = zombieFM.rbegin(); it != zombieFM.rend(); ++it)
	{
		_Fzm.erase(_Fzm.begin() + *it);
	}
	// 파편 업데이트
	for (auto& fragment : _Zfragments)
	{
		fragment.Update(0.16f, IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), 0, 0);
	}

}

void Tutorial::renderZombie()
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



*/