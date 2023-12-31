#include "Stdafx.h"
#include "Tutorial.h"

HRESULT Tutorial::init()
{
   
    _goTitle = false;
	_hitCnt = 0;
	_hitDelay = false;

	
	_rot = new RotationRender;

	_rot->init();
	//��

	_zombieManager.init();
	_zombieManager.setShakeOffset(_shakeOffsetX, _shakeOffsetY);
	_kunaiCol = new KunaiCollision;
	_kunaiCol->init();

	_knockBackMagnitude = 10.0f;

	_boss = new Boss;
	_boss->init();




	//��ư//
	const vector<string> buttonTexts = {
	"���� ����", "�Ϻ��� ���" ,"P90 ���" , "������ ���","���� ��ȯ", "���� ����"};
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
		//_title.init();
        _goTitle = true;
	//	SOUNDMANAGER->play("Ÿ��Ʋ�����");
	//	SOUNDMANAGER->setVolume("Ÿ��Ʋ�����", 0.2f);
    }
	PLAYER->update();
	playerPixel();
	//��ư===========================================
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _buttons.size(); i++)
		{
			if (PtInRect(&_buttons[i].rect, _ptMouse))
			{
				// ��ư �̺�Ʈ ó��
				onButtonClick(i);
			}
		}
	}
	

	_zombieManager.update(0,0);
	_slashEffect.update();

	updateLipo();
	


	
	if (PLAYER->getCreateBoss())
	{

		_boss->update();
		bossBattle();
	

		
	}

	if (PLAYER->getShoot())
	{
		_initialShakeDuration = 0.1;
		_zombieManager.applyShake(_initialShakeDuration);
	}
}

void Tutorial::render()
{
    IMAGEMANAGER->render("Ʃ�丮��", getMemDC(), 0 - _shakeOffsetX, 0 - _shakeOffsetY);

    if (KEYMANAGER->isToggleKey(VK_F1))
    {
        IMAGEMANAGER->render("Ʃ�丮���ȼ�", getMemDC(), 0, 0);
    }

	UI->panalHpRender(getMemDC());



	for (const auto& button : _buttons)
	{
		IMAGEMANAGER->render("��ư", getMemDC(), button.rect.left, button.rect.top, _buttonWidth, _buttonHeight);

	
		FONTMANAGER->drawText(getMemDC(), button.rect.left + 25, button.rect.top + 30, "Orange Kid", 30, FW_BOLD, (char*)button.text.c_str(), static_cast<int>(button.text.length()), RGB(255, 255, 255));
	}
	if (PLAYER->getCreateBoss())
	{
		_boss->render();

	}
	_slashEffect.render(getMemDC());
	
	PLAYER->render(getMemDC());
	PLAYER->_dustEffect.update();
	
	_zombieManager.render();
	renderLipo();



	char ptMouse[128];
	char ptOffset[128];
	char ptPlayerPos[128];

	wsprintf(ptMouse, "x : %d y : %d", _ptMouse.x, _ptMouse.y);

	wsprintf(ptPlayerPos, "x : %d y : %d", PLAYER->getPlayerPos().left, PLAYER->getPlayerPos().top);


	TextOut(getMemDC(), 100, 100, ptMouse, strlen(ptMouse));

	TextOut(getMemDC(), 100, 140, ptPlayerPos, strlen(ptPlayerPos));
}


void Tutorial::playerPixel()
{
	_pPosRc.left = PLAYER->getPlayerPos().left;
	_pPosRc.right = PLAYER->getPlayerPos().right;
	_pPosRc.top = PLAYER->getPlayerPos().top;
	_pPosRc.bottom = PLAYER->getPlayerPos().bottom;

	int Rlb = GetRValue(GetPixel(IMAGEMANAGER->findImage("Ʃ�丮���ȼ�")->getMemDC(), _pPosRc.left , _pPosRc.bottom + 3));
	int Rlbup = GetRValue(GetPixel(IMAGEMANAGER->findImage("Ʃ�丮���ȼ�")->getMemDC(), _pPosRc.left, _pPosRc.bottom - 5));

	int Rrbup = GetRValue(GetPixel(IMAGEMANAGER->findImage("Ʃ�丮���ȼ�")->getMemDC(), _pPosRc.right , _pPosRc.bottom - 5));
	int Rrb = GetRValue(GetPixel(IMAGEMANAGER->findImage("Ʃ�丮���ȼ�")->getMemDC(), _pPosRc.right , _pPosRc.bottom ));

	int Rlt = GetRValue(GetPixel(IMAGEMANAGER->findImage("Ʃ�丮���ȼ�")->getMemDC(), _pPosRc.left , _pPosRc.top )); //r131
	int Rrt = GetRValue(GetPixel(IMAGEMANAGER->findImage("Ʃ�丮���ȼ�")->getMemDC(), _pPosRc.right , _pPosRc.top ));

	int Glb = GetGValue(GetPixel(IMAGEMANAGER->findImage("Ʃ�丮���ȼ�")->getMemDC(), _pPosRc.left , _pPosRc.bottom ));
	int Grb = GetGValue(GetPixel(IMAGEMANAGER->findImage("Ʃ�丮���ȼ�")->getMemDC(), _pPosRc.right, _pPosRc.bottom ));
	int Glt = GetGValue(GetPixel(IMAGEMANAGER->findImage("Ʃ�丮���ȼ�")->getMemDC(), _pPosRc.left , _pPosRc.top ));
	int Grt = GetGValue(GetPixel(IMAGEMANAGER->findImage("Ʃ�丮���ȼ�")->getMemDC(), _pPosRc.right, _pPosRc.top )); //g134

	int GCR = GetGValue(GetPixel(IMAGEMANAGER->findImage("Ʃ�丮���ȼ�")->getMemDC(), _pPosRc.right, (_pPosRc.top + _pPosRc.bottom) / 2 )); //g134
	int GCL = GetGValue(GetPixel(IMAGEMANAGER->findImage("Ʃ�丮���ȼ�")->getMemDC(), _pPosRc.left , (_pPosRc.top + _pPosRc.bottom) / 2 ));



	if (PLAYER->getUsingKunai())
	{
		_kunaiCol->kunaiCollision(IMAGEMANAGER->findImage("Ʃ�丮���ȼ�")->getMemDC(), 0, 0);
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



	
	if (Grt == 134 && Grb == 134)
	{
		PLAYER->setPlayerPosRight(8);

	}



	if (Glt == 134 && Glb == 134)
	{
		PLAYER->setPlayerPosLeft(8);
	}


	if (Glt == 134 && Grt == 134)
	{
		PLAYER->setPlayerPosBottom(PLAYER->getColTop());

	}





}

void Tutorial::onButtonClick(int buttonIndex)
{
	switch (buttonIndex)
	{
	case 0: 
		_zombieManager.createZombie(800, 600);
		
		break;
	case 1: 
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
	case 5:
		createLipo(300, 580);
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

void Tutorial::applyShake(float shakeDuration)
{
	_shakeDuration = shakeDuration;
}

void Tutorial::bossBattle()
{
	if (IntersectRect(&_collider, &PLAYER->getATKRange(), &_boss->getPos()) && _boss->getCurrentState() != 0 )
	{

		if (!_bossHitDelay)
		{
			
			_boss->setHp(_boss->getHp() - 1);
			_boss->setStateIdle();
			_zombieOnce = false;
			_boss->setHit(true);
			_bossHitDelay = true;

			_zombieManager.applyShake(_initialShakeDuration); 

			createBoxEF = true;
			if (createBoxEF)
			{
				for (int k = 0; k < 8; k++)
				{
					float EFX = RND->getFromIntTo(_boss->getPos().left, _boss->getPos().right);
					float EFY = RND->getFromIntTo(_boss->getPos().top, _boss->getPos().top + 50);
					_slashEffect.addEffect(EFX, EFY, 1, "���ڱ���������Ʈ������");
				}
				for (int j = 0; j < 3; j++)
				{
					float EFX = RND->getFromIntTo(_boss->getPos().left, _boss->getPos().right);
					float EFY = RND->getFromIntTo(_boss->getPos().top, _boss->getPos().top + 50);
					_slashEffect.addEffect(EFX, EFY, 1, "���ڱ���������Ʈ");
				}
				for (int j = 0; j < 3; j++)
				{
					float EFX = RND->getFromIntTo(_boss->getPos().left, _boss->getPos().right);
					float EFY = RND->getFromIntTo(_boss->getPos().top, _boss->getPos().top + 50);
					_slashEffect.addEffect(EFX, EFY, 1, "�������");
				}

				float slashX = _boss->getPos().left;
				float slashY = _boss->getPos().top;
				_slashEffect.addSlashEffect(slashX, slashY, 1, "����");
			}
			createBoxEF = false;


			
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


		
		}
	}

	if (_boss->getCurrentState() == 2)
	{
	

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
			
			float knockBackX = PLAYER->getPlayerCenter() > _boss->getCenter() ? _knockBackMagnitude : -_knockBackMagnitude;
			float knockBackY = 0;  
			PLAYER->setKnockback(knockBackX, knockBackY);
			
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

void Tutorial::createLipo(int x, int y)
{
	Lipo* newLipo = new Lipo;
	newLipo->init();
	newLipo->setPos(x, y);
	newLipo->setIsLeft(false);
	_Flp.push_back(newLipo);

}

void Tutorial::updateLipo()
{
	for (int i = 0; i < _Flp.size(); i++)
	{
		_Flp[i]->UpdateLipo();
	}

	for (int i = 0; i < _Flp.size(); i++)
	{
		if (IntersectRect(&_collider, &PLAYER->getPlayerPos(), &_Flp[i]->getRange()))
		{

			
			if (!_hitDelay)
			{
				PLAYER->setDmg(_Flp[i]->getAtk());
				PLAYER->setHit(true);
				_hitDelay = true;
				
				float knockBackX = PLAYER->getPlayerCenter() > _Flp[i]->getCenter() ? _knockBackMagnitude : -_knockBackMagnitude;
				float knockBackY = 0; 
				PLAYER->setKnockback(knockBackX, knockBackY);
			
				_zombieManager.applyShake(_initialShakeDuration);
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


	vector<size_t> lipoFM;

	for (int i = 0; i < _Flp.size(); i++)
	{
		if (IntersectRect(&_collider, &PLAYER->getATKRange(), &_Flp[i]->getPos()))
		{
			if (!_Flp[i]->getRecognition())
			{
				SOUNDMANAGER->play("�����ν�");
				SOUNDMANAGER->setVolume("�����ν�", 0.2f);
				SOUNDMANAGER->play("Į�ǰ�");
				SOUNDMANAGER->setVolume("Į�ǰ�", 0.2f);
				_Flp[i]->setRecognition(true);
			}

			_zombieDiePosX = _Flp[i]->getPos().left;
			_zombieDiePosY = _Flp[i]->getPos().top;
			float knockBackX = PLAYER->getPlayerCenter() > _Flp[i]->getCenter() ? _knockBackMagnitude : -_knockBackMagnitude;
			float knockBackY = 0;
			PLAYER->setKnockback(knockBackX, knockBackY);
			_Flp[i]->setDie(true);
			
			_zombieManager.applyShake(_initialShakeDuration);
			createBoxEF = true;
			if (createBoxEF)
			{
				for (int k = 0; k < 8; k++)
				{
					float EFX = RND->getFromIntTo(_Flp[i]->getPos().left, _Flp[i]->getPos().right);
					float EFY = RND->getFromIntTo(_Flp[i]->getPos().top, _Flp[i]->getPos().top + 50);
					_slashEffect.addEffect(EFX, EFY, 1, "���ڱ���������Ʈ������");
				}
				for (int j = 0; j < 3; j++)
				{
					float EFX = RND->getFromIntTo(_Flp[i]->getPos().left, _Flp[i]->getPos().right);
					float EFY = RND->getFromIntTo(_Flp[i]->getPos().top, _Flp[i]->getPos().top + 50);
					_slashEffect.addEffect(EFX, EFY, 1, "���ڱ���������Ʈ");
				}
				for (int j = 0; j < 3; j++)
				{
					float EFX = RND->getFromIntTo(_Flp[i]->getPos().left, _Flp[i]->getPos().right);
					float EFY = RND->getFromIntTo(_Flp[i]->getPos().top, _Flp[i]->getPos().top + 50);
					_slashEffect.addEffect(EFX, EFY, 1, "�������");
				}

				float slashX = _Flp[i]->getPos().left;
				float slashY = _Flp[i]->getPos().top;
				_slashEffect.addSlashEffect(slashX, slashY, 1, "����");
			}
			createBoxEF = false;

		}
		if (_Flp[i]->getDie())
		{
			_zombieManager.applyShake(_initialShakeDuration);
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


	for (auto& fragment : _Lfragments)
	{
		fragment.Update(0.16f, IMAGEMANAGER->findImage("Ʃ�丮���ȼ�")->getMemDC(), 0, 0);
	}


}

void Tutorial::renderLipo()
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






