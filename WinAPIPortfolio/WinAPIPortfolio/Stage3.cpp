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

	if (_currentMap == map1)
	{
		if ((_pPosRc.right + _pPosRc.left) / 2 > 1280) //�� �ѱ��
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

		if ((_pPosRc.right + _pPosRc.left) / 2 > 1280) //�� �ѱ��
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

	}

	updateShakeEffect(_shakeDuration, _shakeOffsetX, _shakeOffsetY);
}

void Stage3::render(void)
{
	IMAGEMANAGER->render("��������3", getMemDC(), 0 - _shakeOffsetX, 0 - _shakeOffsetY, _offsetX, _offsetY, 6400, 800);
	_slashEffect.render(getMemDC());
	if (PLAYER->getHp() < 30)
	{
		UI->lowHpRender(getMemDC());
	}

	UI->panalHpRender(getMemDC());



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
	//==�ȼ� �浹==
	int Rlb = GetRValue(GetPixel(IMAGEMANAGER->findImage("��������3�ȼ�")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.bottom + _offsetY + 3));
	int Rlbup = GetRValue(GetPixel(IMAGEMANAGER->findImage("��������3�ȼ�")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.bottom + _offsetY - 5));

	int Rrb = GetRValue(GetPixel(IMAGEMANAGER->findImage("��������3�ȼ�")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.bottom + _offsetY));
	int Rrbup = GetRValue(GetPixel(IMAGEMANAGER->findImage("��������3�ȼ�")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.bottom + _offsetY - 5));

	int Rlt = GetRValue(GetPixel(IMAGEMANAGER->findImage("��������3�ȼ�")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.top + _offsetY)); //r131
	int Rrt = GetRValue(GetPixel(IMAGEMANAGER->findImage("��������3�ȼ�")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.top + _offsetY));

	int Glb = GetGValue(GetPixel(IMAGEMANAGER->findImage("��������3�ȼ�")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.bottom + _offsetY));
	int Grb = GetGValue(GetPixel(IMAGEMANAGER->findImage("��������3�ȼ�")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.bottom + _offsetY));
	int Glt = GetGValue(GetPixel(IMAGEMANAGER->findImage("��������3�ȼ�")->getMemDC(), _pPosRc.left + _offsetX, _pPosRc.top + _offsetY));
	int Grt = GetGValue(GetPixel(IMAGEMANAGER->findImage("��������3�ȼ�")->getMemDC(), _pPosRc.right + _offsetX, _pPosRc.top + _offsetY)); //g134

	int GCR = GetGValue(GetPixel(IMAGEMANAGER->findImage("��������3�ȼ�")->getMemDC(), _pPosRc.right + _offsetX, (_pPosRc.top + _pPosRc.bottom) / 2 + _offsetY)); //g134
	int GCL = GetGValue(GetPixel(IMAGEMANAGER->findImage("��������3�ȼ�")->getMemDC(), _pPosRc.left + _offsetX, (_pPosRc.top + _pPosRc.bottom) / 2 + _offsetY));


	if (PLAYER->getUsingKunai())
	{
		_kunaiCOl.kunaiCollision(IMAGEMANAGER->findImage("��������3�ȼ�")->getMemDC(), _offsetX, _offsetY);
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
	//���Ͱ� ��ֹ�
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



	//������ ������
	if (Grt == 134 && Grb == 134)
	{
		PLAYER->setPlayerPosRight(8);

	}


	//���ʸ�����
	if (Glt == 134 && Glb == 134)
	{
		PLAYER->setPlayerPosLeft(8);
	}


	//���ʸ�����
	if (Glt == 134 && Grt == 134)
	{
		PLAYER->setPlayerPosBottom(PLAYER->getColTop());

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
