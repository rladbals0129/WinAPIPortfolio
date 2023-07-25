#include "Stdafx.h"
#include "ZombieManager.h"

void ZombieManager::createZombie(int x, int y)
{
    Zombiebot* newZombie = new Zombiebot;
    newZombie->init();
    newZombie->setPos(x, y);
    newZombie->setIsLeft(true);
    //newZombie->setState(2);
    _Fzm.push_back(newZombie);
}

void ZombieManager::update()
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
		fragment.Update(0.16f, IMAGEMANAGER->findImage("튜토리얼픽셀")->getMemDC(), 0, 0);
	}
}

void ZombieManager::render()
{
    // renderZombie() 코드를 여기에 복사합니다.
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

std::vector<Zombiebot*>& ZombieManager::getZombies()
{
    return _Fzm;
}

void ZombieManager::updateShakeEffect(float& shakeDuration, float& shakeOffsetX, float& shakeOffsetY)
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

void ZombieManager::applyShake(float shakeDuration)
{
	_shakeDuration = shakeDuration;
}

void ZombieManager::createFragments(std::vector<Fragment>& fragments, const POINT& position, wchar_t* imagePath, int numFragments)
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
