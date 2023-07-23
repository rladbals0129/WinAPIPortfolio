#include "Stdafx.h"
#include "Player.h"



HRESULT Player::init(void)
{

	_hp = 155;

	
	_isLeft = true;
	_breath = 0;
	_breathIn = false;
	_rc = RectMake(630, 550, 74, 74);
	_cnt = 0;
	_alpha = 255;

	_down = false;
	
	//칼
	_knife = false;
	_txtKnife = false;
	_usingKnife = false;
	_panalKnife = false;

	//ui
	_txtCom = false;
	_colCom = false;
	
	
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

	
	//하단점프
	_downJump = false;

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

	/*savePosition();
	if (_colRight)
	{
		_rc.left = _previousPosition.x;
		_rc.right = _previousPosition.y;
	}*/



	if (_isJumping)
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
	}

	if (IMAGEMANAGER->findImage("머리")->getY() - _rc.top < - 6.f)
	{
	
	IMAGEMANAGER->findImage("머리")->setY(IMAGEMANAGER->findImage("머리")->getY() + 1);
	}
	
	
	
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT)&&!_down && !_colLeft &&!_isATK)
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
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_LEFT) && !_down && !_colRight && !_isATK)
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
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && !_isJumping)
	{
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
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && (_knife || _colCom))
	{
		if (_colCom)
		{
			_txtCom = true;
		}
		else
		{
			_txtKnife = true;
		}
		
		
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP)) {}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && (_txtKnife || _txtCom))
	{
		if (_txtCom)
		{
			_txtCom = false;
		}
		else
		{
			_txtKnife = false;
			_panalKnife = true;


			cout << "얻다" << endl;
			_usingKnife = true;
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
	if (KEYMANAGER->isStayKeyDown('S') && _usingKnife)
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
	

}

void Player::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_F1)) 
	{
		DrawRectMake(hdc, _rc);
		DrawRectMake(hdc, _rangeATK);
	}

	if (_currentState == IDLE)
	{
		_alpha = 130;
		IMAGEMANAGER->frameAlphaRender("Idle", hdc, _rc.left - 15, _rc.top,_alpha);

		if (_isLeft)
		{
			IMAGEMANAGER->frameAlphaRender("머리", hdc, IMAGEMANAGER->findImage("머리")->getX() +5, IMAGEMANAGER->findImage("머리")->getY() - 12.5f, _alpha);
			IMAGEMANAGER->frameAlphaRender("기본표정", hdc, IMAGEMANAGER->findImage("머리")->getX() + 5, IMAGEMANAGER->findImage("머리")->getY() - 12.5f, _alpha);
		}
		else
		{
			IMAGEMANAGER->frameAlphaRender("머리", hdc, IMAGEMANAGER->findImage("머리")->getX() + 20, IMAGEMANAGER->findImage("머리")->getY() - 12.5f, _alpha);
			IMAGEMANAGER->frameAlphaRender("기본표정", hdc,IMAGEMANAGER->findImage("머리")->getX() + 20, IMAGEMANAGER->findImage("머리")->getY() - 12.5f, _alpha);
		}
		
	
	}

	if (_currentState == MOVE)
	{
		
	
		if (_isLeft)
		{
			IMAGEMANAGER->frameAlphaRender("Move", hdc, _rc.left , _rc.top, _alpha);
			IMAGEMANAGER->frameAlphaRender("머리", hdc, _rc.left + 5, _rc.top - 12.5f, _alpha);
			IMAGEMANAGER->frameAlphaRender("런표정", hdc, _rc.left + 5, _rc.top - 12.5f, _alpha);

		}
		else
		{
			IMAGEMANAGER->frameAlphaRender("Move", hdc, _rc.left - 30, _rc.top, _alpha);
			IMAGEMANAGER->frameAlphaRender("머리", hdc, _rc.left + 20, _rc.top - 12.5f, _alpha);
			IMAGEMANAGER->frameAlphaRender("런표정", hdc, _rc.left + 20, _rc.top - 12.5f, _alpha);

		}
	}

	if (_currentState == JUMP)
	{
		IMAGEMANAGER->frameAlphaRender("Jump", hdc, _rc.left - 15, _rc.top, _alpha);
		if (_isLeft)
		{
		
			IMAGEMANAGER->frameAlphaRender("머리", hdc, _rc.left+5, _rc.top - 12.5f, _alpha);
			IMAGEMANAGER->frameAlphaRender("기본표정", hdc, _rc.left + 5, _rc.top - 12.5f, _alpha);

		}
		else
		{
			IMAGEMANAGER->frameAlphaRender("머리", hdc, _rc.left + 20, _rc.top -12.5f, _alpha);
			IMAGEMANAGER->frameAlphaRender("기본표정", hdc, _rc.left + 20, _rc.top - 12.5f, _alpha);
		}
	}

	if (_currentState == DOWN)
	{
		//IMAGEMANAGER->frameRender("Crouch", hdc, _rc.left - 15, _rc.top);
		if (_isLeft)
		{
			IMAGEMANAGER->frameAlphaRender("Crouch", hdc, _rc.left, _rc.top + 30, _alpha);
			IMAGEMANAGER->frameAlphaRender("머리", hdc, _rc.left +6, _rc.top + 6.f, _alpha);
			IMAGEMANAGER->frameAlphaRender("숙인표정", hdc, _rc.left +9, _rc.top + 11.f, _alpha);
		
		}
		else
		{
			IMAGEMANAGER->frameAlphaRender("Crouch", hdc, _rc.left, _rc.top + 30, _alpha);
			IMAGEMANAGER->frameAlphaRender("머리", hdc, _rc.left + 22, _rc.top + 6.f, _alpha);
			IMAGEMANAGER->frameAlphaRender("숙인표정", hdc, _rc.left + 25, _rc.top + 11.f, _alpha);
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
