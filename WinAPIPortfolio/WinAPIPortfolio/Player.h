#pragma once

#include "SingletonBase.h"


class DustEffect {
public:
	void update();
	void render(HDC hdc);
	void addDust(float x, float y, int count);

private:
	struct Dust {
		float x;
		float y;
		float vx; 
		float vy;
		int frameX;
		int frameY;
		int frameCount;
		bool alive;
	};
	std::vector<Dust> _dustList;
};

class Player :public SingletonBase<Player>
{
private:
	enum STATE {
		IDLE, MOVE,
		JUMP, SLAP,
		DOWN, ATTACK,
		UPATTACK,DOWNATTACK
	};
	STATE _currentState;
	DustEffect _dustEffect;
	RECT _rc;
	//플레이어 스펙
	int _speed;
	int _attack;
	int _hp;
	
	//애니메이션 컨트롤
	int _cnt;
	int _idx;
	bool _isLeft;

	int _alpha;
	//달리기 이펙트
	int _mCnt;
	int _mIdx;
	int _mAlpha;

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

	bool _isUpATK;
	int _atkUpIdx;

	bool _isDownATK;
	int _atkDownIdx;

	//하단점프
	bool _downJump;
	bool _goDownJump;

	//피격
	bool _hit;
	int _hcnt;
	int _hidx;
	//넉백
	float _knockbackSpeedX;
	float _knockbackSpeedY;
	float _knockbackDistanceX;
	float _knockbackDistanceY;
	const float _maxKnockbackDistance = 100.0f;
public:	
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void idle(void);
	void move(void);
	void moveEF(void);
	void jump(void);
	void down(void);
	void clap(void);
	void Attack(void);
	void AttackUP(void);
	void AttackDown(void);

	void Hit(void);


	void titlePlayer(HDC hdc);

	inline STATE getState() { return _currentState; }
	inline RECT getPlayerPos() { return _rc; }
	inline int getPlayerCenter() { return (_rc.left + _rc.right) / 2; }

	inline RECT getATKRange() { return _rangeATK; }

	inline bool getIsJumping() { return _isJumping; }
	inline bool getColRight() { return _colRight; }

	inline float getColTop() { return _gravityJumpPower; }

	inline bool getKnife() { return _knife; }
	inline bool getTxtKnife() { return _txtKnife; }
	inline bool getUsingKnife() { return _usingKnife; }
	inline bool getPanalKnife() { return _panalKnife; }
	inline bool getTxtCom() { return _txtCom; }
	inline bool getDownJump() { return _downJump; }
	inline bool getGoDownjump() { return _goDownJump; }

	inline int getHp() { return _hp; }
	inline int getAlpha() { return _alpha; }
	inline bool getHit() { return _hit; }

	bool getIsLeft() { return _isLeft; }
	inline float getKnocback() { return _knockbackSpeedX, _knockbackSpeedY; }
	
	inline void setIdle() { _currentState = IDLE; }
	//inline void setStateHit() { _currentState = HIT; }

	//inline void setATKRange(RECT rangeATK) { _rangeATK = rangeATK; }

	inline void setPlayerPosLeft(int x) { _rc.left += x; _rc.right += x; }
	inline void setPlayerPosRight(int x) { _rc.left -= x; _rc.right -= x; }
	inline void setPlayerPosBottom(int y){ _rc.top -= y; _rc.bottom -= y; }
	inline void setPlayerPosTop(int y) { _rc.top += y; _rc.bottom += y; }
	inline void setPlayerPos(RECT rc) { _rc = rc; }
	inline void setIsJumping(bool isJumping) { _isJumping = isJumping; }
	inline void setPlayerPos(int x, int y) { _rc.left = x; _rc.right = x + 74; _rc.top = y; _rc.bottom = y + 74; }
	inline void setPlayerPos(int left, int top, int right, int bottom) { _rc.left = left; _rc.top = top; _rc.right = right; _rc.bottom = bottom; }
	inline void setIsGravity(bool isGravity) { _isGravity = isGravity; }
	inline void setColRight(bool colRight) { _colRight = colRight; }
	inline void setColLeft(bool colLeft) { _colLeft = colLeft; }
	inline void setColTop(bool colTop) { _colTop = colTop; }
	inline void setKnife(bool knife) { _knife = knife; }
	inline void setTxtKnife(bool txtKnife) { _txtKnife = txtKnife; }
	inline void setPanalKnife(bool panalKnife) { _panalKnife = panalKnife; }
	inline void setTxtCom(bool txtCom) { _txtCom = txtCom; }
	inline void setcolCom(bool colCom) { _colCom = colCom; }
	inline void setDownJump(bool downJump) { _downJump = downJump; }
	inline void setGoDownJump(bool goDoinJump) { _goDownJump = goDoinJump; }

	inline void setDmg(int dmg) { _hp -= dmg; }
	inline void setHit(bool hit) { _hit = hit; }
	inline void setAlpha(int alpha) { _alpha = alpha; }
	void setKnockback(float knockbackSpeedX, float knockbackSpeedY)
	{
		_knockbackSpeedX = knockbackSpeedX;
		_knockbackSpeedY = knockbackSpeedY;
		_knockbackDistanceX = 0.0f;
		_knockbackDistanceY = 0.0f;
	}

	//void setPanalCom(bool panalCom) { _panalCom = panalCom; }
	
	


//	void savePosition();

	Player();
	~Player();
};

