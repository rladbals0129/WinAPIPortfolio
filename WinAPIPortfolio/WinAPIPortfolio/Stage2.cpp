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

		if ((_pPosRc.right + _pPosRc.left) / 2 > 1280) //¸Ê ³Ñ±â±â
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

		//ÃÑ==
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
		if (PLAYER->getPlayerPos().bottom > 800)
		{
			_goStage3 = true;
			cout << "½ºÅ×ÀÌÁö3" << endl;
		}

	}


	updateShakeEffect(_shakeDuration, _shakeOffsetX, _shakeOffsetY);
}

void Stage2::render(void)
{
	IMAGEMANAGER->render("½ºÅ×ÀÌÁö2", getMemDC(), 0 - _shakeOffsetX, 0 - _shakeOffsetY, _offsetX, _offsetY, 5120, 2400);
	_slashEffect.render(getMemDC());
	if (PLAYER->getHp() < 30)
	{
		UI->lowHpRender(getMemDC());
	}

	UI->panalHpRender(getMemDC());

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		IMAGEMANAGER->render("½ºÅ×ÀÌÁö2ÇÈ¼¿", getMemDC(), 0, 0, _offsetX, _offsetY, 5120, 2400);

	}


	if (_currentMap == map3)
	{
		if (_renderGun && !_gunGet)
		{
			IMAGEMANAGER->frameRender("ÃÑÀÌÆåÆ®", getMemDC(), _gungetCOl.left, _gungetCOl.top);
			IMAGEMANAGER->render("ÃÑ", getMemDC(), _gungetCOl.left + 30, _gungetCOl.top + 30);

		}
		if (_UIGunRender && !_gunGet)
		{
			UI->btnUPRender(getMemDC());
		}
		if (PLAYER->getTxtGun())
		{
			UI->txtRender(getMemDC(), "ÃÑÅØ½ºÆ®");
			UI->btnEnterRender(getMemDC(), "ÃÑÅØ½ºÆ®");
		}
		if (PLAYER->getPanalGun())
		{
			IMAGEMANAGER->render("ÃÑÈ¹µæ", getMemDC(), 0, _panalGunOffsetY);
		}
		if (!_gunGet)
		{
			_gungetCOl = RectMake(300, 600, 140, 100);
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
		IMAGEMANAGER->findImage("ÃÑÀÌÆåÆ®")->setFrameX(_gunIdx);
	}
}

void Stage2::playerPixel()
{

	//==ÇÈ¼¿ Ãæµ¹==
	int Rlb = GetRValue(GetPixel(IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö2ÇÈ¼¿")->getMemDC(), _pPosRc.left + _offsetX,   _pPosRc.bottom + _offsetY + 3));
	int Rlbup = GetRValue(GetPixel(IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö2ÇÈ¼¿")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.bottom + _offsetY - 5));

	int Rrb = GetRValue(GetPixel(IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö2ÇÈ¼¿")->getMemDC(), _pPosRc.right + _offsetX,   _pPosRc.bottom + _offsetY));
	int Rrbup = GetRValue(GetPixel(IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö2ÇÈ¼¿")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.bottom + _offsetY - 5));

	int Rlt = GetRValue(GetPixel(IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö2ÇÈ¼¿")->getMemDC(), _pPosRc.left + _offsetX,  _pPosRc.top + _offsetY)); //r131
	int Rrt = GetRValue(GetPixel(IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö2ÇÈ¼¿")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.top + _offsetY));

	int Glb = GetGValue(GetPixel(IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö2ÇÈ¼¿")->getMemDC(), _pPosRc.left + _offsetX,  _pPosRc.bottom + _offsetY));
	int Grb = GetGValue(GetPixel(IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö2ÇÈ¼¿")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.bottom + _offsetY));
	int Glt = GetGValue(GetPixel(IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö2ÇÈ¼¿")->getMemDC(), _pPosRc.left + _offsetX,  _pPosRc.top + _offsetY));
	int Grt = GetGValue(GetPixel(IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö2ÇÈ¼¿")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.top + _offsetY)); //g134

	int GCR = GetGValue(GetPixel(IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö2ÇÈ¼¿")->getMemDC(), _pPosRc.right + _offsetX, (_pPosRc.top + _pPosRc.bottom) / 2 + _offsetY)); //g134
	int GCL = GetGValue(GetPixel(IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö2ÇÈ¼¿")->getMemDC(), _pPosRc.left + _offsetX, (_pPosRc.top + _pPosRc.bottom) / 2 + _offsetY));

	if (PLAYER->getUsingKunai())
	{
		_kunaiCOl.kunaiCollision(IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö2ÇÈ¼¿")->getMemDC(), _offsetX, _offsetY);
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
	//¼¾ÅÍ°ª Àå¾Ö¹°
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

	//¿À¸¥ÂÊ ¸·Èù°÷
	if (Grt == 134 && Grb == 134)
	{
		PLAYER->setPlayerPosRight(8);

	}

	//¿ÞÂÊ¸·Èù°÷
	if (Glt == 134 && Glb == 134)
	{
		PLAYER->setPlayerPosLeft(8);
	}

	//À§ÂÊ¸·Èù°÷
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
			PLAYER->setPlayerPosRight(8);
		}

	}

	//»óÇÏ
	if (PLAYER->getPlayerPos().top < cameraOffsetY && _offsetY > 0)
	{

		_offsetY -= cameraOffsetY - PLAYER->getPlayerPos().top;
		_slashEffect.setBottom(cameraOffsetY - PLAYER->getPlayerPos().top);

		
		PLAYER->setPlayerPosTop(cameraOffsetY - PLAYER->getPlayerPos().top);
	}
	if (PLAYER->getPlayerPos().top > cameraOffsetY && _offsetY < maxOffsetY)
	{

		_offsetY += PLAYER->getPlayerPos().top - cameraOffsetY;
		_slashEffect.setTop(PLAYER->getPlayerPos().top - cameraOffsetY);
		


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
