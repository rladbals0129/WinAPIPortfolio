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

	_boss = new Boss;
	_boss->init();

	

	//버튼//
	const vector<string> buttonTexts = {
	"좀비 생성", "일본도 사용" ,"P90 사용" , "쿠나이 사용","보스 소환"};
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
	_slashEffect.update();
	//updateZombie();
	if (PLAYER->getCreateBoss())
	{

		_boss->update();

	

		if (IntersectRect(&_collider, &PLAYER->getATKRange(), &_boss->getPos()))
		{
			
			if (!_bossHitDelay)
			{
			//	cout << "맞음?" << endl;
				_boss->setHp(_boss->getHp() - 1);
				_boss->setStateIdle();
				_zombieOnce = false;
				_boss->setHit(true);
				_bossHitDelay = true;
				
				_zombieManager.applyShake(_initialShakeDuration); //스테이지에선 그냥 applyShake
		
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
					_zombieManager.createZombie(300 * (i + 1), 600);
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
				_zombieManager.applyShake(_initialShakeDuration);
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
	if (PLAYER->getCreateBoss())
	{
		_boss->render();

	}
	_slashEffect.render(getMemDC());
	//플레이어
	PLAYER->render(getMemDC());
	PLAYER->_dustEffect.update();
	//====
	_zombieManager.render();
	//renderZombie();

	char ptMouse[128];
	char ptOffset[128];
	char ptPlayerPos[128];

	wsprintf(ptMouse, "x : %d y : %d", _ptMouse.x, _ptMouse.y);
	//wsprintf(ptOffset, "offsetX : %d  offsetY : %d", _offsetX, _offsetY);
	wsprintf(ptPlayerPos, "x : %d y : %d", PLAYER->getPlayerPos().left, PLAYER->getPlayerPos().top);


	TextOut(getMemDC(), 100, 100, ptMouse, strlen(ptMouse));
//	TextOut(getMemDC(), 100, 120, ptOffset, strlen(ptOffset));
	TextOut(getMemDC(), 100, 140, ptPlayerPos, strlen(ptPlayerPos));
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
		break;
	case 4:
		PLAYER->setCreateBoss(!PLAYER->getCreateBoss());
		break;
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






