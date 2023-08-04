#include "Stdafx.h"
#include "Player.h"



HRESULT Player::init(void)
{

	_hp = 155;
	_hit = false;

	
	_isLeft = true;
	_breath = 0;
	_breathIn = false;
	
	_rc = RectMake(630, 550, 74, 74);
	_cnt = 0;
	_alpha = 255;
	_mAlpha = 255;
	_down = false;
	_knockbackSpeedX = 0.0f;
	_knockbackSpeedY = 0.0f;
	_knockbackDistanceX = 0.0f;
	_knockbackDistanceY = 0.0f;
	//칼
	_knife = false;
	_txtKnife = false;
	_usingKnife = false;
	_panalKnife = false;
	//총
	_usingGun = false;
	//ui
	_txtCom = false;
	_colCom = false;
	//쿠나이
	_usingKunai = false;
	_kunai = new Kunai;
	_kunai->init();
	_lerpSpeed = 1.f;
	//보스
	_createBoss = false;
	
	//이동
	_speed = 8.0f;
	_colRight = false;
	_colLeft = false;
	_colTop = false;
	


	//점프
	_gravity = 8.0f;
	_jumpPower = 0.0f;
	_isJumping = false;
	_jumpEnd = false;
	_isGravity = true;
	_frame = 0;
	_jumpStartFrame = 0;


	//공격
	_isATK = false;
	_atkUpIdx = 0;
	_atkDownIdx = 0;
	_isUpATK = false;
	_isDownATK = false;

	_katanaCnt = 20;
	
	//하단점프
	_downJump = false;
	//벽점프
	_canLeftWallJump = false;
	_canRightWallJump = false;
	return S_OK;
}

void Player::release(void)
{
	IMAGEMANAGER->deleteImage("머리");
	IMAGEMANAGER->deleteImage("기본표정");
	IMAGEMANAGER->deleteImage("런표정");
	IMAGEMANAGER->deleteImage("Idle");
	IMAGEMANAGER->deleteImage("Move");
	IMAGEMANAGER->deleteImage("Jump");
}

void Player::update(void)
{
	_frame++;

	_rc.left += _knockbackSpeedX;
	_rc.right += _knockbackSpeedX;
	_rc.top += _knockbackSpeedY;
	_rc.bottom += _knockbackSpeedY;
	_knockbackDistanceX += abs(_knockbackSpeedX);
	_knockbackDistanceY += abs(_knockbackSpeedY);
	if (_usingKunai)
	{
		_kunai->update();
	}
	
	if (_knockbackDistanceX >= _maxKnockbackDistance || _knockbackDistanceY >= _maxKnockbackDistance)
	{
		_knockbackSpeedX = 0.0f;
		_knockbackSpeedY = 0.0f;
	}
	
	if (_isJumping && !_onRock)
	{
		_currentState = JUMP;
	}
	else if (!_isJumping && !_isATK)
	{
		
		_currentState = IDLE;
	}
	if (_currentState == JUMP)
	{
		jump();
		IMAGEMANAGER->findImage("머리")->setY(_rc.top);
		IMAGEMANAGER->findImage("기본표정")->setY(_rc.top);
		
		if (_jumpDust) {
			
	
			for (int i = 0; i < 5; i++)
			{
				float dustXLeft = RND->getFromIntTo(_rc.left, _rc.right);
				float dustY = RND->getFromIntTo(_rc.bottom - 40,_rc.bottom);
				_dustEffect.addDust(dustXLeft, dustY, 1);
			}
			
			_jumpDust = false;
		}// 점프 시 먼지 5개 생성
	}

	if (IMAGEMANAGER->findImage("머리")->getY() - _rc.top < - 6.f)
	{
	
	IMAGEMANAGER->findImage("머리")->setY(IMAGEMANAGER->findImage("머리")->getY() + 1);
	}
	
	
	
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT)&&!_down && !_colLeft &&!_isATK&&!shoot)
	{
		_isLeft = true;
		if (_currentState != JUMP)
		_currentState = MOVE;

		if (_currentState == MOVE)
		{
			move();
		}
		_rc.left -= _speed;
		_rc.right -= _speed;
	
	}
	else if(KEYMANAGER->isStayKeyDown(VK_LEFT) && KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_currentState = IDLE;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) )
	{
		IMAGEMANAGER->findImage("머리")->setY(_rc.top);
		IMAGEMANAGER->findImage("기본표정")->setY(_rc.top);
		if (_currentState != JUMP)
		_currentState = IDLE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_LEFT) && !_down && !_colRight && !_isATK &&!shoot)
	{
		_isLeft = false;
		if (_currentState != JUMP)
			_currentState = MOVE;

		if (_currentState == MOVE)
		{
			move();
		}
		_rc.left += _speed;
		_rc.right += _speed;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_currentState != JUMP)
		_currentState = IDLE;
	
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		IMAGEMANAGER->findImage("머리")->setY(_rc.top);
		IMAGEMANAGER->findImage("기본표정")->setY(_rc.top);
		_currentState = IDLE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		
		_down = true;
		_currentState = DOWN;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_down = false;
		_currentState = IDLE;
	}
	//===========점프===========
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && (!_isJumping || _canLeftWallJump || _canRightWallJump || _onRock) && !shoot)
	{
		_jumpDust = true;
		if (!_downJump)
		{
			_jumpPower = -18.f;
			_jumpStartFrame = _frame;
			_jumpEnd = false;
		}
		else if (_downJump && KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_rc.top += 40;
			_goDownJump = true;
			_rc.bottom += 40;
		}
	
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
	{
		_jumpEnd = true;
	}
	
	//벽잡기 활용
	if ((_frame > _jumpStartFrame + 25 && _jumpStartFrame != 0)) //&& _colTop)
	{
		_jumpEnd = true;
		_jumpStartFrame = 0;	
		_frame = 0;
	}
	if (_jumpEnd)
	{
		_jumpPower += 1.f;
	}
	if (_jumpPower > 0.f)
	{
		_jumpPower = 0.f;
		
	}	

	_rc.top +=  _jumpPower;
	_rc.bottom +=  _jumpPower;

	if (_isJumping)
	{
		_rc.top += _gravity;
		_rc.bottom += _gravity;
	}

	_gravityJumpPower = _gravity + _jumpPower;

	
	//========================================
	//===일본도 획득===
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && (_knife || _colCom || _colKunai || _colGun || _colBoss))
	{
		if (_colCom)
		{
			_txtCom = true;
		}
		else if (_knife)
		{
			_txtKnife = true;
		}
		else if (_colKunai)
		{
			_txtKunai = true;
		}
		else if (_colGun)
		{
			_txtGun = true;
		}
		else if (_colBoss)
		{
			_txtBoss = true;
		}
		
		
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP)) {}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && (_txtKnife || _txtCom || _txtKunai || _txtGun || _txtBoss))
	{
		
		if (_txtCom)
		{
			_txtCom = false;
		}
		else if (_txtKnife)
		{
			_txtKnife = false;
			_panalKnife = true;


			cout << "얻다" << endl;
			_usingKnife = true;
		}
		else if (_txtKunai)
		{
			_txtKunai = false;
			_panalKunai = true;

			_usingKunai = true;
		}
		else if(_txtGun)
		{
			_txtGun = false;
			_panalGun = true;
			_usingGun = true;
		}
		else if (_txtBoss)
		{
			_txtIdx++;
			if (_txtIdx == 4)
			{
				_txtBoss = false;
				_panalBoss = true;
			//	_createBoss = true;
			}
		}
	
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RETURN)) {}
	//=====================================txtui==========
	//if (KEYMANAGER->isOnceKeyDown(VK_UP) && _colCom)
	//{
	//	_txtCom = true;
	//	cout << "dd" << endl;
	//}

	//if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _txtCom)
	//{
	//	cout << "dd" << endl;
	//	_txtCom = false;
	//}
	
	
	//================================
	//========공격===========
	if (KEYMANAGER->isStayKeyDown('S') && _usingKnife && !_hit && !shoot)
	{
		_currentState = ATTACK;
		_isATK = true;
		//cout << "ss?" << endl;
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_currentState = UPATTACK;
			_isUpATK = true;
			_isATK = false;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			_isUpATK = false;
			_isATK = true;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_currentState = DOWNATTACK;
			_isDownATK = true;
			_isATK = false;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			_isDownATK = true;
			_isATK = false;
		}
	
		
	}

	if (KEYMANAGER->isOnceKeyUp('S') && _usingKnife)
	{
		_currentState = IDLE;
		_isATK = false;
		_isUpATK = false;
		_isDownATK = false;
	}
	if (_isATK)
	{
		if (_isLeft)
		{
			_rangeATK = RectMake(_rc.left - 100, _rc.top - 15, 100, 100);
		}
		else
		{
			_rangeATK = RectMake(_rc.right, _rc.top - 15, 100, 100);
		}
	}
	else if (_isUpATK)
	{
		_rangeATK = RectMake(_rc.left - 10 , _rc.top - 100, 100, 100);
	}
	else if (_isDownATK)
	{
		_rangeATK = RectMake(_rc.left - 10, _rc.bottom , 100, 100);
	}
	else
	{
		_rangeATK = RectMake(_rc.right, _rc.top - 15, 0, 0);
	}

	if (KEYMANAGER->isStayKeyDown('W') && _usingGun)
	{
		shoot = true;
		_currentState = GUN;
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		shoot = false;
	}
	if (_currentState == GUN)
	{
		IMAGEMANAGER->findImage("머리")->setX(_rc.left);
		IMAGEMANAGER->findImage("공격표정")->setX(_rc.left);
		IMAGEMANAGER->findImage("공격표정")->setY(_rc.top);
		idle();
		shot();
		fire();
		_bulletCnt++;
		if (_bulletCnt % 5 == 0)
		{
			float bulletX = _isLeft ?  _rc.left : _rc.right - 5 ;
			float bulletY = _rc.bottom - 40;
			_bullet.addBullet(bulletX, bulletY, 1);
		}
	}
	if (_currentState == ATTACK)
	{
		IMAGEMANAGER->findImage("머리")->setX(_rc.left);
		IMAGEMANAGER->findImage("공격표정")->setX(_rc.left);
		IMAGEMANAGER->findImage("공격표정")->setY(_rc.top);
		Attack();
	}
	if (_currentState == UPATTACK)
	{
		IMAGEMANAGER->findImage("머리")->setX(_rc.left);
		IMAGEMANAGER->findImage("공격표정")->setX(_rc.left);
		IMAGEMANAGER->findImage("공격표정")->setY(_rc.top);
		AttackUP();

	}
	if (_currentState == DOWNATTACK)
	{
		IMAGEMANAGER->findImage("머리")->setX(_rc.left);
		IMAGEMANAGER->findImage("공격표정")->setX(_rc.left);
		IMAGEMANAGER->findImage("공격표정")->setY(_rc.top);
		AttackDown();
	}

	if (_currentState == MOVE)
	{
		IMAGEMANAGER->findImage("머리")->setX(_rc.left);
		IMAGEMANAGER->findImage("런표정")->setX(_rc.left);
		IMAGEMANAGER->findImage("런표정")->setY(_rc.top);
		_dustCnt++;
		if (_dustCnt % 10 == 0) {
			
			float dustX = _isLeft ? _rc.right - 5 : _rc.left;
			float dustY = _rc.bottom - 40;
			_dustEffect.addDust(dustX, dustY, 1);
		} 
		
	}

	if (_currentState == IDLE)
	{
		idle();

	
		IMAGEMANAGER->findImage("머리")->setX(_rc.left);
		IMAGEMANAGER->findImage("기본표정")->setX(_rc.left);
	}

	if (_currentState == DOWN)
	{
		down();
	}
	
	if (_hp < 30)
	{
		_batteryCnt++;
		if (_batteryCnt % 20 == 0)
		{
			_battery = !_battery;
		}
	}
	_bullet.update();

	_katanaCnt = (_katanaCnt + 1) % 360;
	_handCnt = (_handCnt + 1) % 360;
	_gunReaction = (_gunReaction + 1) % 360;

}

void Player::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_F1)) 
	{
		DrawRectMake(hdc, _rc);
		DrawRectMake(hdc, _rangeATK);
	}
	//보스할때 응용
	//float xOffset = cos(_handCnt * 0.1) * 5;
	//float xOffset
	float yOffset = sin(_handCnt * 0.1) * 5;
	float yKatanaOffset = sin(_katanaCnt * 0.08) * 3;
	float X_gunReaction = cos(_gunReaction * 1) * 2; //강도/범위
	float Y_gunReaction = sin(_gunReaction * 0.1) * 2; //강도/범위
	_bullet.render(hdc);

	if (_currentState == IDLE)
	{
		

		if (_isLeft)
		{
			if (_usingKnife)
			{
				IMAGEMANAGER->findImage("칼")->setFrameY(1);
				IMAGEMANAGER->frameRender("칼", hdc, _rc.left - 45, _rc.top + 30 + yKatanaOffset);
			}


			IMAGEMANAGER->frameAlphaRender("Idle", hdc, _rc.left - 15, _rc.top, _alpha);
			IMAGEMANAGER->frameAlphaRender("머리", hdc, IMAGEMANAGER->findImage("머리")->getX() +5, IMAGEMANAGER->findImage("머리")->getY() - 12.5f, _alpha);
		
			if (!_hit)
			{
				IMAGEMANAGER->frameAlphaRender("기본표정", hdc,
					IMAGEMANAGER->findImage("머리")->getX() + 5,
					IMAGEMANAGER->findImage("머리")->getY() - 12.5f, _alpha);
			}
			else //x+6 y+5
			{
				IMAGEMANAGER->frameAlphaRender("피격표정", hdc, 
					IMAGEMANAGER->findImage("머리")->getX() + 11,
					IMAGEMANAGER->findImage("머리")->getY() - 6.5f, _alpha);
			}
			if (_hp < 30 && _battery)
			{
				IMAGEMANAGER->frameRender("개피", hdc, IMAGEMANAGER->findImage("머리")->getX() + 11, IMAGEMANAGER->findImage("머리")->getY() - 6.5f);
			}
			if (_usingKnife)
			{
				IMAGEMANAGER->findImage("손")->setFrameY(1);
				IMAGEMANAGER->frameRender("손", hdc, _rc.left + 30, _rc.top + yOffset + 35);
				
				//IMAGEMANAGER->frameRender("손", hdc, _rc.left+30, _rc.top+35);
			}
		}
		else
		{
			if (_usingKnife)
			{
				IMAGEMANAGER->findImage("칼")->setFrameY(0);
				IMAGEMANAGER->frameRender("칼", hdc, _rc.left - 25, _rc.top + 30 + yKatanaOffset);
			}


			IMAGEMANAGER->frameAlphaRender("Idle", hdc, _rc.left - 15, _rc.top, _alpha);
			IMAGEMANAGER->frameAlphaRender("머리", hdc, IMAGEMANAGER->findImage("머리")->getX() + 20, IMAGEMANAGER->findImage("머리")->getY() - 12.5f, _alpha);
		
			if (!_hit)
			{
				IMAGEMANAGER->frameAlphaRender("기본표정", hdc,
					IMAGEMANAGER->findImage("머리")->getX() + 20, 
					IMAGEMANAGER->findImage("머리")->getY() - 12.5f, _alpha);
			}
			else //x + 8 y + 6
			{
				IMAGEMANAGER->frameAlphaRender("피격표정", hdc,
					IMAGEMANAGER->findImage("머리")->getX() + 28,
					IMAGEMANAGER->findImage("머리")->getY() - 6.5f, _alpha);

			}
			if (_hp < 30 && _battery)
			{
				IMAGEMANAGER->frameRender("개피", hdc, IMAGEMANAGER->findImage("머리")->getX() + 28, IMAGEMANAGER->findImage("머리")->getY()-6);
			}
			if (_usingKnife)
			{
				IMAGEMANAGER->findImage("손")->setFrameY(0);
				IMAGEMANAGER->frameRender("손", hdc, _rc.left + 3, _rc.top + yOffset + 35);
				//IMAGEMANAGER->frameRender("손", hdc, _rc.left+3, _rc.top+35);
			}
		}
		
	
	}
	if (_currentState == GUN)
	{
		IMAGEMANAGER->frameAlphaRender("Idle", hdc, _rc.left - 15, _rc.top, _alpha);
		if (_isLeft)
		{
			IMAGEMANAGER->frameAlphaRender("머리", hdc, IMAGEMANAGER->findImage("머리")->getX() + 5, IMAGEMANAGER->findImage("머리")->getY() - 12.5f, _alpha);
			IMAGEMANAGER->alphaRender("공격표정", hdc, IMAGEMANAGER->findImage("머리")->getX() + 8, IMAGEMANAGER->findImage("머리")->getY() - 6.5f, _alpha);
			IMAGEMANAGER->frameRender("총1", hdc, _rc.left-90+ X_gunReaction, _rc.top+10 + Y_gunReaction);
			IMAGEMANAGER->frameRender("총2", hdc, _rc.left-30+ X_gunReaction, _rc.top+10 + Y_gunReaction);
			IMAGEMANAGER->frameRender("총기화염", hdc, _rc.left - 110 + X_gunReaction, _rc.top + 10 + Y_gunReaction);
			IMAGEMANAGER->frameRender("총기화염", hdc, _rc.left - 190 + X_gunReaction, _rc.top + 10 + Y_gunReaction);
			//_createBulletPosX = 
		}
		else
		{
			IMAGEMANAGER->frameAlphaRender("머리", hdc, IMAGEMANAGER->findImage("머리")->getX() + 20, IMAGEMANAGER->findImage("머리")->getY() - 12.5f, _alpha);
			IMAGEMANAGER->alphaRender("공격표정", hdc, IMAGEMANAGER->findImage("머리")->getX() + 24, IMAGEMANAGER->findImage("머리")->getY() - 7.5f, _alpha);
			IMAGEMANAGER->frameRender("총1", hdc, _rc.left+20+ X_gunReaction, _rc.top+10 + Y_gunReaction);
			IMAGEMANAGER->frameRender("총2", hdc, _rc.left+80+ X_gunReaction, _rc.top+10 + Y_gunReaction);
			IMAGEMANAGER->frameRender("총기화염", hdc, _rc.left +80 + X_gunReaction, _rc.top + 10 + Y_gunReaction);
			IMAGEMANAGER->frameRender("총기화염", hdc, _rc.left +160 + X_gunReaction, _rc.top + 10 + Y_gunReaction);

		}
		
	}
	if (_currentState == MOVE)
	{
		
	
		if (_isLeft)
		{
			if (_usingKnife)
			{
				IMAGEMANAGER->findImage("칼")->setFrameY(1);
				IMAGEMANAGER->frameRender("칼", hdc, _rc.left - 30, _rc.top + 30 + yKatanaOffset);
			}

			IMAGEMANAGER->frameAlphaRender("Move", hdc, _rc.left , _rc.top, _alpha);
			
			IMAGEMANAGER->frameAlphaRender("머리", hdc, _rc.left + 5, _rc.top - 12.5f, _alpha);
		
			if (!_hit)
			{
				IMAGEMANAGER->frameAlphaRender("런표정", hdc, _rc.left + 5, _rc.top - 12.5f, _alpha);
			}
			else
			{
				IMAGEMANAGER->frameAlphaRender("피격표정", hdc,
					_rc.left + 11, _rc.top - 6.5f, _alpha);
			}
			if (_hp < 30 && _battery)
			{
				IMAGEMANAGER->frameRender("개피", hdc, _rc.left + 11, _rc.top - 6.5f);
			}
			if (_usingKnife)
			{
				IMAGEMANAGER->findImage("손")->setFrameY(1);
				IMAGEMANAGER->frameRender("손", hdc, _rc.left + 30, _rc.top + yOffset + 35);
				//IMAGEMANAGER->frameRender("손", hdc, _rc.left + 30, _rc.top + 35);
			}

		}
		else
		{
			if (_usingKnife)
			{
				IMAGEMANAGER->findImage("칼")->setFrameY(0);
				IMAGEMANAGER->frameRender("칼", hdc, _rc.left - 40, _rc.top + 30 + yKatanaOffset);
			}
			IMAGEMANAGER->frameAlphaRender("Move", hdc, _rc.left - 30, _rc.top, _alpha);
			IMAGEMANAGER->frameAlphaRender("머리", hdc, _rc.left + 20, _rc.top - 12.5f, _alpha);
			//IMAGEMANAGER->frameAlphaRender("달리기먼지", hdc, _rc.left, _rc.bottom - 40, _mAlpha);
			
			if (!_hit)
			{
				IMAGEMANAGER->frameAlphaRender("런표정", hdc, _rc.left + 20, _rc.top - 12.5f, _alpha);
			}
			else
			{
				IMAGEMANAGER->frameAlphaRender("피격표정", hdc,
					_rc.left + 28, _rc.top - 6.5f, _alpha);
			}
			if (_hp < 30 && _battery)
			{
				IMAGEMANAGER->frameRender("개피", hdc, _rc.left + 28, _rc.top - 6.5f);
			}
			if (_usingKnife)
			{
				IMAGEMANAGER->findImage("손")->setFrameY(0);
				IMAGEMANAGER->frameRender("손", hdc, _rc.left + 3, _rc.top + yOffset + 35);
				//IMAGEMANAGER->frameRender("손", hdc, _rc.left + 3, _rc.top + 35);
			}

		}
	}

	if (_currentState == JUMP)
	{
		
		if (_isLeft)
		{
			if (_usingKnife)
			{
				IMAGEMANAGER->findImage("칼")->setFrameY(1);
				IMAGEMANAGER->frameRender("칼", hdc, _rc.left - 30, _rc.top + 30 + yKatanaOffset);
			}
			IMAGEMANAGER->frameAlphaRender("Jump", hdc, _rc.left - 15, _rc.top, _alpha);
			IMAGEMANAGER->frameAlphaRender("머리", hdc, _rc.left+5, _rc.top - 12.5f, _alpha);
			if (!_hit)
			{
				IMAGEMANAGER->frameAlphaRender("기본표정", hdc, _rc.left + 5, _rc.top - 12.5f, _alpha);

			}
			else
			{
				IMAGEMANAGER->frameAlphaRender("피격표정", hdc,
					_rc.left + 11, _rc.top - 6.5f, _alpha);
			}
			if (_hp < 30 && _battery)
			{
				IMAGEMANAGER->frameRender("개피", hdc, _rc.left + 11, _rc.top - 6.5f);
			}
			if (_usingKnife)
			{
				IMAGEMANAGER->findImage("손")->setFrameY(1);
				IMAGEMANAGER->frameRender("손", hdc, _rc.left + 30, _rc.top + yOffset + 35);
				//IMAGEMANAGER->frameRender("손", hdc, _rc.left + 30, _rc.top + 35);
			}

		}
		else
		{
			if (_usingKnife)
			{
				IMAGEMANAGER->findImage("칼")->setFrameY(0);
				IMAGEMANAGER->frameRender("칼", hdc, _rc.left - 25, _rc.top + 30 + yKatanaOffset);
			}

			IMAGEMANAGER->frameAlphaRender("Jump", hdc, _rc.left - 15, _rc.top, _alpha);
			IMAGEMANAGER->frameAlphaRender("머리", hdc, _rc.left + 20, _rc.top -12.5f, _alpha);
			if (!_hit)
			{
				IMAGEMANAGER->frameAlphaRender("기본표정", hdc, _rc.left + 20, _rc.top - 12.5f, _alpha);

			}
			else
			{
				IMAGEMANAGER->frameAlphaRender("피격표정", hdc,
					_rc.left + 28, _rc.top - 6.5f, _alpha);
			}
			if (_hp < 30 && _battery)
			{
				IMAGEMANAGER->frameRender("개피", hdc, _rc.left + 28, _rc.top - 6.5f);
			}
			if (_usingKnife)
			{
				IMAGEMANAGER->findImage("손")->setFrameY(0);
				IMAGEMANAGER->frameRender("손", hdc, _rc.left + 3, _rc.top + yOffset + 35);
			//	IMAGEMANAGER->frameRender("손", hdc, _rc.left + 3, _rc.top + 35);
			}
		}
	}

	if (_currentState == DOWN)
	{
		//IMAGEMANAGER->frameRender("Crouch", hdc, _rc.left - 15, _rc.top);
		if (_isLeft)
		{
			IMAGEMANAGER->frameAlphaRender("Crouch", hdc, _rc.left, _rc.top + 30, _alpha);
			IMAGEMANAGER->frameAlphaRender("머리", hdc, _rc.left +6, _rc.top + 6.f, _alpha);
			if (!_hit)
			{
				IMAGEMANAGER->frameAlphaRender("숙인표정", hdc,
					_rc.left +9,
					_rc.top + 11.f, _alpha);

			}
			else
			{
				IMAGEMANAGER->frameAlphaRender("피격표정", hdc,
					_rc.left + 13,
					_rc.top + 12.f, _alpha);
			}
		
		}
		else
		{
			IMAGEMANAGER->frameAlphaRender("Crouch", hdc, _rc.left, _rc.top + 30, _alpha);
			IMAGEMANAGER->frameAlphaRender("머리", hdc, _rc.left + 22, _rc.top + 6.f, _alpha);
			if (!_hit)
			{
				IMAGEMANAGER->frameAlphaRender("숙인표정", hdc,
					_rc.left + 25, _rc.top + 11.f, _alpha);

			}
			else
			{
				IMAGEMANAGER->frameAlphaRender("피격표정", hdc,
					_rc.left + 30, _rc.top + 12.f, _alpha);
			}
		}

	}
	if (_currentState == ATTACK)
	{
		
		if (_isLeft)
		{
			IMAGEMANAGER->frameAlphaRender("AttackFX", hdc, _rc.left- 90, (_rc.top + _rc.bottom )/ 2 - 70, _alpha);
			IMAGEMANAGER->frameAlphaRender("Attack", hdc, _rc.left - 60, _rc.top - 45, _alpha);
			IMAGEMANAGER->frameAlphaRender("머리", hdc, IMAGEMANAGER->findImage("머리")->getX() + 14, IMAGEMANAGER->findImage("머리")->getY() - 16.5f, _alpha);
			IMAGEMANAGER->alphaRender("공격표정", hdc, IMAGEMANAGER->findImage("머리")->getX() + 17, IMAGEMANAGER->findImage("머리")->getY() - 11.5f, _alpha);
			
		}
		else
		{
			IMAGEMANAGER->frameAlphaRender("AttackFX", hdc, _rc.right-90 , (_rc.top + _rc.bottom) / 2 - 70, _alpha);
			IMAGEMANAGER->frameAlphaRender("Attack", hdc, _rc.left - 25, _rc.top - 45, _alpha);
			IMAGEMANAGER->frameAlphaRender("머리", hdc, IMAGEMANAGER->findImage("머리")->getX() + 20, IMAGEMANAGER->findImage("머리")->getY() - 16.5f, _alpha);
			IMAGEMANAGER->alphaRender("공격표정", hdc, IMAGEMANAGER->findImage("머리")->getX() + 24, IMAGEMANAGER->findImage("머리")->getY() - 11.5f, _alpha);
		
		}
		
	}
	

	if (_currentState == UPATTACK)
	{
		if (_isLeft)
		{
			IMAGEMANAGER->frameRender("AttackFXUP", hdc, _rc.left - 75, (_rc.top + _rc.bottom) / 2 - 200);
			IMAGEMANAGER->frameRender("AttackUP", hdc, _rc.left - 35, _rc.top - 45);
			IMAGEMANAGER->frameRender("머리", hdc, IMAGEMANAGER->findImage("머리")->getX() + 10, IMAGEMANAGER->findImage("머리")->getY() - 35.5f);
			IMAGEMANAGER->render("공격표정", hdc, IMAGEMANAGER->findImage("머리")->getX() + 15, IMAGEMANAGER->findImage("머리")->getY() - 30.5f);
		}
		else
		{
			IMAGEMANAGER->frameRender("AttackFXUP", hdc, _rc.left - 100, (_rc.top + _rc.bottom) / 2 - 200);
			IMAGEMANAGER->frameRender("AttackUP", hdc, _rc.left - 60, _rc.top - 45);
			IMAGEMANAGER->frameRender("머리", hdc, IMAGEMANAGER->findImage("머리")->getX() + 10, IMAGEMANAGER->findImage("머리")->getY() - 35.5f);
			IMAGEMANAGER->render("공격표정", hdc, IMAGEMANAGER->findImage("머리")->getX() + 15, IMAGEMANAGER->findImage("머리")->getY() - 30.5f);
		}
	
	}

	if (_currentState == DOWNATTACK)
	{
		if (_isLeft)
		{
			IMAGEMANAGER->frameRender("AttackFXDown", hdc, _rc.left - 120, (_rc.top + _rc.bottom) / 2 - 30);
			IMAGEMANAGER->frameRender("AttackDown", hdc, _rc.left - 80, _rc.top - 5);
			IMAGEMANAGER->frameRender("머리", hdc, IMAGEMANAGER->findImage("머리")->getX() + 10, IMAGEMANAGER->findImage("머리")->getY() - 30.5f);
			IMAGEMANAGER->render("공격표정", hdc, IMAGEMANAGER->findImage("머리")->getX() + 15, IMAGEMANAGER->findImage("머리")->getY() - 25.5f);
		}
		else
		{
			IMAGEMANAGER->frameRender("AttackFXDown", hdc, _rc.left-60, (_rc.top + _rc.bottom) / 2 - 30);
			IMAGEMANAGER->frameRender("AttackDown", hdc, _rc.left-20, _rc.top - 5);
			IMAGEMANAGER->frameRender("머리", hdc, IMAGEMANAGER->findImage("머리")->getX() + 10, IMAGEMANAGER->findImage("머리")->getY() - 30.5f);
			IMAGEMANAGER->render("공격표정", hdc, IMAGEMANAGER->findImage("머리")->getX() + 15, IMAGEMANAGER->findImage("머리")->getY() - 25.5f);
		}
		
	}
	
	if (_usingKunai)
	{
		_kunai->render(hdc);
	}
	
	_dustEffect.render(hdc);
	

}

void Player::idle(void)
{
	if (_isLeft)
	{
		_cnt++;
		

		IMAGEMANAGER->findImage("Idle")->setFrameY(1);	
		IMAGEMANAGER->findImage("머리")->setFrameY(1);
		IMAGEMANAGER->findImage("기본표정")->setFrameY(1);

		if (_cnt % 12 == 0)
		{
			_eyes--;
			if (_eyes < 0)
			{
				_cnt = 0;
				_eyes = 28;
			}
			IMAGEMANAGER->findImage("기본표정")->setFrameX(_eyes);
		}


		if (_cnt % 3 == 0)
		{
			_idx--;
			
			
			if (_idx < 0)
			{
				
				
				_idx = 14;
				
			}
			!_breathIn ? _breath++ : _breath--;

			if (_breath > 8 && !_breathIn)
			{
				_breathIn = true;
			}
			if (_breath < 0 && _breathIn)
			{
				_breathIn = false;
			}
			_breathIn ? IMAGEMANAGER->findImage("머리")->setY(IMAGEMANAGER->findImage("머리")->getY() + 0.5f) : IMAGEMANAGER->findImage("머리")->setY(IMAGEMANAGER->findImage("머리")->getY() - 0.5f);
			_breathIn ? IMAGEMANAGER->findImage("기본표정")->setY(IMAGEMANAGER->findImage("기본표정")->getY() + 0.5f) : IMAGEMANAGER->findImage("기본표정")->setY(IMAGEMANAGER->findImage("기본표정")->getY() - 0.5f);
			IMAGEMANAGER->findImage("Idle")->setFrameX(_idx);
		

		}

	}
	else
	{
		_cnt++;

		IMAGEMANAGER->findImage("Idle")->setFrameY(0);
		IMAGEMANAGER->findImage("머리")->setFrameY(0);
		IMAGEMANAGER->findImage("기본표정")->setFrameY(0);
		if (_cnt % 12 == 0)
		{
			_eyes++;
			if (_eyes > 28)
			{
				_cnt = 0;
				_eyes = 0;
			}
			IMAGEMANAGER->findImage("기본표정")->setFrameX(_eyes);
		}
	
		if (_cnt % 4 == 0)
		{
			
			_idx++;
			if (_idx > 14)
			{
				_cnt = 0;
				_idx = 0;
				
			}
			
			!_breathIn ? _breath++ : _breath--;

			if (_breath > 8 && !_breathIn)
			{
				_breathIn = true;			
			}
			if (_breath < 0 && _breathIn)
			{
				_breathIn = false; 
			}
			_breathIn ? IMAGEMANAGER->findImage("머리")->setY(IMAGEMANAGER->findImage("머리")->getY() + 0.5f) : IMAGEMANAGER->findImage("머리")->setY(IMAGEMANAGER->findImage("머리")->getY() - 0.5f);
			_breathIn ? IMAGEMANAGER->findImage("기본표정")->setY(IMAGEMANAGER->findImage("기본표정")->getY() + 0.5f) : IMAGEMANAGER->findImage("기본표정")->setY(IMAGEMANAGER->findImage("기본표정")->getY() - 0.5f);
			IMAGEMANAGER->findImage("Idle")->setFrameX(_idx);
			
		}
		
	}
}

void Player::move(void)
{
	if (_isLeft)
	{
		_cnt++;

		IMAGEMANAGER->findImage("Move")->setFrameY(1);
		IMAGEMANAGER->findImage("머리")->setFrameY(1);
		IMAGEMANAGER->findImage("런표정")->setFrameY(1);

		if (_cnt % 3 == 0)
		{
			_idx--;
			if (_idx < 0)
			{
				_cnt = 0;
				_idx = 24;
			}

			IMAGEMANAGER->findImage("Move")->setFrameX(_idx);
		}

	}
	else
	{
		_cnt++;

		IMAGEMANAGER->findImage("Move")->setFrameY(0);
		IMAGEMANAGER->findImage("머리")->setFrameY(0);
		IMAGEMANAGER->findImage("런표정")->setFrameY(0);
	
		if (_cnt % 3 == 0)
		{

			_idx++;
			if (_idx > 24)
			{
				_cnt = 0;
				_idx = 0;
			}

			IMAGEMANAGER->findImage("Move")->setFrameX(_idx);

		}

	}
}

void Player::moveEF(void)
{
	if (_isLeft)
	{
		_mCnt++;
		IMAGEMANAGER->findImage("달리기먼지")->setFrameY(1);
		if (_mCnt % 5 == 0)
		{
			_mIdx++;
			if (_mIdx > 3)
			{
				_mIdx = 0;
				_mCnt = 0;
			}
			IMAGEMANAGER->findImage("달리기먼지")->setFrameX(_mIdx);
		}
	}
	else
	{
		_mCnt++;
		IMAGEMANAGER->findImage("달리기먼지")->setFrameY(0);
		if (_mCnt % 5 == 0)
		{
			_mIdx--;
			if (_mIdx < 0)
			{
				_mIdx = 3;
				_mCnt = 0;
			}
			IMAGEMANAGER->findImage("달리기먼지")->setFrameX(_mIdx);
		}
	}
}

void Player::jump(void)
{

	IMAGEMANAGER->findImage("기본표정")->setFrameX(0);
	if (_isLeft)
	{
		_cnt++;

		IMAGEMANAGER->findImage("Jump")->setFrameY(1);
		IMAGEMANAGER->findImage("머리")->setFrameY(1);
		IMAGEMANAGER->findImage("기본표정")->setFrameY(1);

		if (_cnt % 2 == 0)
		{
			_idx--;
			if (_idx < 0)
			{
				_cnt = 0;
				_idx = 23;
			}

			IMAGEMANAGER->findImage("Jump")->setFrameX(_idx);
		}

	}
	else
	{
		_cnt++;

		IMAGEMANAGER->findImage("Jump")->setFrameY(0);
		IMAGEMANAGER->findImage("머리")->setFrameY(0);
		IMAGEMANAGER->findImage("기본표정")->setFrameY(0);

		if (_cnt % 2 == 0)
		{

			_idx++;
			if (_idx > 23)
			{
				_cnt = 0;
				_idx = 0;
			}

			IMAGEMANAGER->findImage("Jump")->setFrameX(_idx);
		}

	}
}

void Player::down(void)
{
	if (_isLeft)
	{
		IMAGEMANAGER->findImage("Crouch")->setFrameY(1);
		IMAGEMANAGER->findImage("머리")->setFrameY(1);
		IMAGEMANAGER->findImage("숙인표정")->setFrameY(1);
	}
	else
	{
		IMAGEMANAGER->findImage("Crouch")->setFrameY(0);
		IMAGEMANAGER->findImage("머리")->setFrameY(0);
		IMAGEMANAGER->findImage("숙인표정")->setFrameY(0);
	}
}

void Player::clap(void)
{

}

void Player::Attack(void)
{
	if (_isLeft)
	{

		_cnt++;
		IMAGEMANAGER->findImage("AttackFX")->setFrameY(1);
		IMAGEMANAGER->findImage("Attack")->setFrameY(1);
		if (_cnt % 3 == 0)
		{
			_idx--;
			if (_idx < 0)
			{
				_idx = 4;
				
				
			}
			IMAGEMANAGER->findImage("AttackFX")->setFrameX(_idx);
		}

		if (_cnt % 3 == 0)
		{
			_atkIdx--;
			if (_atkIdx < 0)
			{
				_atkIdx = 9;
				_cnt = 0;
				_rc.left -= 30;
				_rc.right -= 30;
			//	_currentState = IDLE;
			//	_isATK = false;
			}
			IMAGEMANAGER->findImage("Attack")->setFrameX(_atkIdx);

		}


	}
	else
	{
		_cnt++;
		IMAGEMANAGER->findImage("AttackFX")->setFrameY(0);
		IMAGEMANAGER->findImage("Attack")->setFrameY(0);
		if (_cnt % 3 == 0)
		{
			_idx++;
			if (_idx > 4)
			{
				_idx = 0;
				
			}
			IMAGEMANAGER->findImage("AttackFX")->setFrameX(_idx);
		}

		
		if (_cnt % 3 == 0)
		{
			_atkIdx++;
			if (_atkIdx > 9)
			{
				_atkIdx = 0;
				_cnt = 0;
				_rc.left += 30;
				_rc.right += 30;
			//	_currentState = IDLE;
			//	_isATK = false;
			}
			IMAGEMANAGER->findImage("Attack")->setFrameX(_atkIdx);

		}
	}
	IMAGEMANAGER->findImage("머리")->setY(_rc.top);
	IMAGEMANAGER->findImage("기본표정")->setY(_rc.top);

}

void Player::AttackUP(void)
{
	if (_isLeft)
	{

		_cnt++;
		IMAGEMANAGER->findImage("AttackFXUP")->setFrameY(1);
		IMAGEMANAGER->findImage("AttackUP")->setFrameY(1);
		if (_cnt % 3 == 0)
		{
			_idx--;
			if (_idx < 0)
			{
				_idx = 4;


			}
			IMAGEMANAGER->findImage("AttackFXUP")->setFrameX(_idx);
		}

		if (_cnt % 3 == 0)
		{
			_atkUpIdx--;
			if (_atkUpIdx < 0)
			{
				_atkUpIdx = 5;
				_cnt = 0;
				_rc.top -= 30;
				_rc.bottom -= 30;
				//	_currentState = IDLE;
				//	_isATK = false;
			}
			IMAGEMANAGER->findImage("AttackUP")->setFrameX(_atkUpIdx);

		}


	}
	else
	{
		_cnt++;
		IMAGEMANAGER->findImage("AttackFXUP")->setFrameY(0);
		IMAGEMANAGER->findImage("AttackUP")->setFrameY(0);
		if (_cnt % 3 == 0)
		{
			_idx++;
			if (_idx > 4)
			{
				_idx = 0;

			}
			IMAGEMANAGER->findImage("AttackFXUP")->setFrameX(_idx);
		}


		if (_cnt % 3 == 0)
		{
			_atkUpIdx++;
			if (_atkUpIdx > 5)
			{
				_atkUpIdx = 0;
				_cnt = 0;
				_rc.top -= 30;
				_rc.bottom -= 30;
				//	_currentState = IDLE;
				//	_isATK = false;
			}
			IMAGEMANAGER->findImage("AttackUP")->setFrameX(_atkUpIdx);

		}
	}
	IMAGEMANAGER->findImage("머리")->setY(_rc.top);
	IMAGEMANAGER->findImage("기본표정")->setY(_rc.top);
}

void Player::AttackDown(void)
{
	if (_isLeft)
	{

		_cnt++;
		IMAGEMANAGER->findImage("AttackFXDown")->setFrameY(1);
		IMAGEMANAGER->findImage("AttackDown")->setFrameY(1);
		if (_cnt % 3 == 0)
		{
			_idx--;
			if (_idx < 0)
			{
				_idx = 4;


			}
			IMAGEMANAGER->findImage("AttackFXDown")->setFrameX(_idx);
		}

		if (_cnt % 3 == 0)
		{
			_atkDownIdx--;
			if (_atkDownIdx < 0)
			{
				_atkDownIdx = 5;
				_cnt = 0;
				_rc.top -= 30;
				_rc.bottom -= 30;
				//_rc.left -= 30;
				//_rc.right -= 30;
				//	_currentState = IDLE;
				//	_isATK = false;
			}
			IMAGEMANAGER->findImage("AttackDown")->setFrameX(_atkDownIdx);

		}


	}
	else
	{
		_cnt++;
		IMAGEMANAGER->findImage("AttackFXDown")->setFrameY(0);
		IMAGEMANAGER->findImage("AttackDown")->setFrameY(0);
		if (_cnt % 3 == 0)
		{
			_idx++;
			if (_idx > 4)
			{
				_idx = 0;

			}
			IMAGEMANAGER->findImage("AttackFXDown")->setFrameX(_idx);
		}


		if (_cnt % 3 == 0)
		{
			_atkDownIdx++;
			if (_atkDownIdx > 5)
			{
				_atkDownIdx = 0;
				_cnt = 0;
				_rc.top -= 30;
				_rc.bottom -= 30;
				//_rc.left += 30;
				//_rc.right += 30;
				//	_currentState = IDLE;
				//	_isATK = false;
			}
			IMAGEMANAGER->findImage("AttackDown")->setFrameX(_atkDownIdx);

		}
	}
	IMAGEMANAGER->findImage("머리")->setY(_rc.top);
	IMAGEMANAGER->findImage("기본표정")->setY(_rc.top);
}

void Player::shot(void)
{
	if (_isLeft)
	{
		
		_gunAnimCnt++;
		IMAGEMANAGER->findImage("총1")->setFrameY(1);
		IMAGEMANAGER->findImage("총2")->setFrameY(1);
		//IMAGEMANAGER->findImage("총기화염")->setFrameY(1);
		if (_gunAnimCnt % 4 == 0)
		{
			_gunAnimIdx--;
			if (_gunAnimIdx < 0 )
			{
				_gunAnimIdx = 7;
				_gunAnimCnt = 0;
			}
			IMAGEMANAGER->findImage("총1")->setFrameX(_gunAnimIdx);
			IMAGEMANAGER->findImage("총2")->setFrameX(_gunAnimIdx);
			//IMAGEMANAGER->findImage("총기화염")->setFrameX(_gunAnimIdx);
		}
	}
	else
	{
		_gunAnimCnt++;
		IMAGEMANAGER->findImage("총1")->setFrameY(0);
		IMAGEMANAGER->findImage("총2")->setFrameY(0);
		//IMAGEMANAGER->findImage("총기화염")->setFrameY(0);
		if (_gunAnimCnt % 4 == 0)
		{
			_gunAnimIdx++;
			if (_gunAnimIdx > 7)
			{
				_gunAnimIdx = 0;
				_gunAnimCnt = 0;
			}
			IMAGEMANAGER->findImage("총1")->setFrameX(_gunAnimIdx);
			IMAGEMANAGER->findImage("총2")->setFrameX(_gunAnimIdx);
		//	IMAGEMANAGER->findImage("총기화염")->setFrameX(_gunAnimIdx);
		}

	}

}

void Player::fire(void)
{
	if (_isLeft)
	{

		_fireCnt++;
		IMAGEMANAGER->findImage("총기화염")->setFrameY(1);
		if (_fireCnt % 3 == 0)
		{
			_fireIdx--;
			if (_fireIdx < 0)
			{
				_fireIdx = 5;
				_fireCnt = 0;
			}
			
			IMAGEMANAGER->findImage("총기화염")->setFrameX(_fireIdx);
		}
	}
	else
	{
		_fireCnt++;
		
		IMAGEMANAGER->findImage("총기화염")->setFrameY(0);
		if (_fireCnt % 3 == 0)
		{
			_fireIdx++;
			if (_fireIdx > 5)
			{
				_fireIdx = 0;
				_fireCnt = 0;
			}
			
			IMAGEMANAGER->findImage("총기화염")->setFrameX(_fireIdx);
		}

	}
}

void Player::Hit(void)
{
	
	if (_isLeft)
	{
		IMAGEMANAGER->findImage("피격표정")->setFrameY(1);
	}
	else
	{
		IMAGEMANAGER->findImage("피격표정")->setFrameY(0);
	}

}

void Player::titlePlayer(HDC hdc)
{
	_isLeft = true;


		IMAGEMANAGER->frameRender("Idle", hdc, _rc.left - 15, _rc.top);

		if (_isLeft)
		{
			IMAGEMANAGER->frameRender("머리", hdc, IMAGEMANAGER->findImage("머리")->getX() + 5, IMAGEMANAGER->findImage("머리")->getY() - 12.5f);
			IMAGEMANAGER->frameRender("기본표정", hdc, IMAGEMANAGER->findImage("머리")->getX() + 5, IMAGEMANAGER->findImage("머리")->getY() - 12.5f);
		}
		else
		{
			IMAGEMANAGER->frameRender("머리", hdc, IMAGEMANAGER->findImage("머리")->getX() + 20, IMAGEMANAGER->findImage("머리")->getY() - 12.5f);
			IMAGEMANAGER->frameRender("기본표정", hdc, IMAGEMANAGER->findImage("머리")->getX() + 20, IMAGEMANAGER->findImage("머리")->getY() - 12.5f);
		}


	
	IMAGEMANAGER->findImage("머리")->setX(_rc.left);
	IMAGEMANAGER->findImage("기본표정")->setX(_rc.left);


	
	//idle();


}




//
//void Player::savePosition()
//{
//	_previousPosition = { _rc.left, _rc.top };
//}

Player::Player()
{
}


Player::~Player()
{
}



void DustEffect::update()
{
	for (auto& dust : _dustList) 
	{
		if (dust.alive) 
		{
			dust.frameCount++;
		
			if (PLAYER->getIsLeft())
			{
				dust.x += dust.vx;
			}
			else
			{
				dust.x -= dust.vx;
			}
			dust.y += dust.vy;
			if (dust.frameCount % 5 == 0)
			{
				dust.frameX++;
			}
			
			if (dust.frameX > 4)
			{
				dust.alive = false;
				
			}
			
		}
	}
}

void DustEffect::render(HDC hdc)
{
	for (const auto& dust : _dustList) {
		if (dust.alive) {
			IMAGEMANAGER->findImage("달리기먼지")->frameRender(hdc, dust.x, dust.y, dust.frameX, dust.frameY);
		}
	}
}

void DustEffect::addDust(float x, float y, int count)
{
	for (int i = 0; i < count; i++) 
	{
		Dust newDust;
		newDust.x = x + (i*10);
		newDust.y = y;
		newDust.vx = 0.3f; 
		newDust.vy = -0.5f; 
		newDust.frameX = 0;
		newDust.frameY = 0;
		newDust.frameCount = 0;
		newDust.alive = true;
	
		_dustList.push_back(newDust);
	}
}

void FireBullet::update()
{
	for (auto& bullet : _bulletList)
	{
		if (bullet.alive)
		{
			bullet.frameCount++;
			
			if (PLAYER->getIsLeft())
			{
				bullet.frameY = 1;
				bullet.x += bullet.vx;
			}
			else
			{
				bullet.frameY = 0;
				bullet.x -= bullet.vx;
			}
			bullet.col = RectMake(bullet.x, bullet.y, 10, 100);
			if (bullet.frameCount % 20 == 0)
			{
				//bullet.col = RectMake(bullet.x, bullet.y, 0, 0);
				bullet.alive = false;
			}

		}
	}
}

void FireBullet::render(HDC hdc)
{
	for (const auto& _bullet: _bulletList) 
	{
		if (_bullet.alive)
		{
			IMAGEMANAGER->findImage("총알")->frameRender(hdc, _bullet.x, _bullet.y, _bullet.frameX, _bullet.frameY);
		}
	}
}

void FireBullet::addBullet(float x, float y, int count)
{
	for (int i = 0; i < count; i++)
	{
		Bullet newBullet;
		newBullet.x = x + (i * 10);
		newBullet.y = y;
		newBullet.vx = -30;
		newBullet.vy = 0;
		newBullet.frameX = 0;
		newBullet.frameY = 0;
		newBullet.frameCount = 0;
		newBullet.alive = true;

		_bulletList.push_back(newBullet);
	}
}
