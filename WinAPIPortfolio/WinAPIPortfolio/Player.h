#pragma once
#include "SingletonBase.h"
#define GRAVITY 0.3f



class Player :public SingletonBase<Player>
{
private:
	enum STATE {
		IDLE, MOVE,
		JUMP, SLAP,
		DOWN, ATTACK
	};
	STATE _currentState;

	RECT _rc;
	
	int _speed;
	int _attack;

	//애니메이션 컨트롤
	int _cnt;
	int _idx;
	bool _isLeft;

	int _eyes; //눈애니메이션

	//머리 애니메이션
	int _breathCnt;
	int _breath;
	bool _breathIn;
	// 점프
	float _gravity;
	float _jumpPower;
	bool _isJumping;
	bool _isGravity;

	float _gravityJumpPower;

	//점프 프레임계산
	int _frame;
	int _jumpStartFrame;
	bool _jumpEnd;

	int _head;
	//충돌판정
	bool _colRight;
	bool _colLeft;
	bool _colTop;
	bool _down;

	//칼 획득
	bool _knife;
	bool _txtKnife;
	bool _usingKnife;
	bool _panalKnife;

	//1컴터
	bool _txtCom;
	bool _colCom;
	//bool _panalCom;

	//공격관련
	RECT _rangeATK;
	bool _isATK;
	int _atkIdx;

public:	
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void idle(void);
	void move(void);
	void jump(void);
	void down(void);
	void clap(void);
	void Attack(void);

	void titlePlayer(HDC hdc);

	STATE getState() { return _currentState; }
	RECT getPlayerPos() { return _rc; }
	bool getIsJumping() { return _isJumping; }
	bool getColRight() { return _colRight; }
	float getColTop() { return _gravityJumpPower; }
	bool getKnife() { return _knife; }
	bool getTxtKnife() { return _txtKnife; }
	bool getUsingKnife() { return _usingKnife; }
	bool getPanalKnife() { return _panalKnife; }
	bool getTxtCom() { return _txtCom; }
//	bool getPanalCom() { return _panalCom; }

	
	void setIdle() { _currentState = IDLE; }
	void setPlayerPosLeft(int x) { _rc.left += x; _rc.right += x; }
	void setPlayerPosRight(int x) { _rc.left -= x; _rc.right -= x; }
	void setPlayerPosBottom(int y){ _rc.top -= y; _rc.bottom -= y; }
	void setPlayerPosTop(int y) { _rc.top += y; _rc.bottom += y; }
	void setPlayerPos(RECT rc) { _rc = rc; }
	void setIsJumping(bool isJumping) { _isJumping = isJumping; }
	void setPlayerPos(int left, int top, int right, int bottom) { _rc.left = left; _rc.top = top; _rc.right = right; _rc.bottom = bottom; }
	void setIsGravity(bool isGravity) { _isGravity = isGravity; }
	void setColRight(bool colRight) { _colRight = colRight; }
	void setColLeft(bool colLeft) { _colLeft = colLeft; }
	void setColTop(bool colTop) { _colTop = colTop; }
	void setKnife(bool knife) { _knife = knife; }
	void setTxtKnife(bool txtKnife) { _txtKnife = txtKnife; }
	void setPanalKnife(bool panalKnife) { _panalKnife = panalKnife; }
	void setTxtCom(bool txtCom) { _txtCom = txtCom; }
	void setcolCom(bool colCom) { _colCom = colCom; }
	//void setPanalCom(bool panalCom) { _panalCom = panalCom; }
	


//	void savePosition();

	Player();
	~Player();
};

