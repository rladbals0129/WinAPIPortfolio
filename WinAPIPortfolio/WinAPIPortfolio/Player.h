#pragma once
#include "SingletonBase.h"
#include "Kunai.h"


class DustEffect {

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

public:
	void update();
	void render(HDC hdc);
	void addDust(float x, float y, int count);
	void setLeft(float x) 
	{
		for (auto& dust : _dustList)
		{
			dust.x -= x;
		}
	}
	void setTop(float y)
	{
		for (auto& dust : _dustList)
		{
			dust.y -= y;
		}
	}
	void setRight(float x) 
	{
		for (auto& dust : _dustList)
		{
			dust.x += x;
		}
	}
	void setBottom(float y) 
	{
		for (auto& dust : _dustList) 
		{
			dust.y += y;
		}
	}

};

class FireBullet {

private:
	struct Bullet {
		RECT col;
		float x;
		float y;
		float vx;
		float vy;
		int frameX;
		int frameY;
		int frameCount;
		bool alive;
	};
	std::vector<Bullet> _bulletList;

public:
	void update();
	void render(HDC hdc);
	void addBullet(float x, float y, int count);

	RECT getPos()
	{
		for (auto& bullet : _bulletList)
		{
			if (bullet.alive)
			{
				return 	bullet.col;

			}
		}
	}

	

	void setAlive(bool alive) { for (auto& bullet : _bulletList) { bullet.alive = alive; } }
	void setLeft(float x)
	{
		for (auto& bullet : _bulletList)
		{
			bullet.x -= x;
		}
	}
	void setTop(float y)
	{
		for (auto& bullet : _bulletList)
		{
			bullet.y -= y;
		}
	}
	void setRight(float x)
	{
		for (auto& bullet : _bulletList)
		{
			bullet.x += x;
		}
	}
	void setBottom(float y)
	{
		for (auto& bullet : _bulletList)
		{
			bullet.y += y;
		}
	}

};

class Player :public SingletonBase<Player>
{
private:
	enum STATE {
		IDLE, MOVE,
		JUMP, SLAP,
		DOWN, ATTACK,
		UPATTACK,DOWNATTACK,
		GUN
	};
	STATE _currentState;

	Kunai* _kunai;
	int _dustCnt;
	bool _jumpDust;

	RECT _rc;
	//ÇÃ·¹ÀÌ¾î ½ºÆå
	int _speed;
	int _attack;
	int _hp;
	
	//¾Ö´Ï¸ÞÀÌ¼Ç ÄÁÆ®·Ñ
	int _cnt;
	int _idx;
	bool _isLeft;

	int _alpha;
	//´Þ¸®±â ÀÌÆåÆ®
	int _mCnt;
	int _mIdx;
	int _mAlpha;

	int _eyes; //´«¾Ö´Ï¸ÞÀÌ¼Ç

	//¸Ó¸® ¾Ö´Ï¸ÞÀÌ¼Ç
	int _breathCnt;
	int _breath;
	bool _breathIn;
	// Á¡ÇÁ
	float _gravity;
	float _jumpPower;
	bool _isJumping;
	bool _isGravity;

	float _gravityJumpPower;

	//Á¡ÇÁ ÇÁ·¹ÀÓ°è»ê
	int _frame;
	int _jumpStartFrame;
	bool _jumpEnd;

	int _head;
	//Ãæµ¹ÆÇÁ¤
	bool _colRight;
	bool _colLeft;
	bool _colTop;
	bool _down;

	//Ä® È¹µæ
	bool _knife;
	bool _txtKnife;
	bool _usingKnife;
	bool _panalKnife;
	
	//Äí³ªÀÌÈ¹µæ
	bool _kunai1;
	bool  _colKunai;
	bool _txtKunai;
	bool _panalKunai;

	//ÃÑ È¹µæ
	bool _gun1;
	bool  _colGun;
	bool _txtGun;
	bool _panalGun;

	//1ÄÄÅÍ
	bool _txtCom;
	bool _colCom;
	//bool _panalCom;

	//°ø°Ý°ü·Ã
	RECT _rangeATK;
	bool _isATK;
	int _atkIdx;

	bool _isUpATK;
	int _atkUpIdx;

	bool _isDownATK;
	int _atkDownIdx;

	//ÇÏ´ÜÁ¡ÇÁ
	bool _downJump;
	bool _goDownJump;

	//ÇÇ°Ý
	bool _hit;
	int _hcnt;
	int _hidx;
	//µþÇÇ
	bool _battery;
	int _batteryCnt;
	//³Ë¹é
	float _knockbackSpeedX;
	float _knockbackSpeedY;
	float _knockbackDistanceX;
	float _knockbackDistanceY;
	const float _maxKnockbackDistance = 100.0f;

	//¼Õ/Ä® µé°íÀÖ´Â ¾Ö´Ï¸ÞÀÌ¼Ç
	int _katanaCnt;
	int _handCnt;

	//ÃÑ
	bool shoot;
	int _gunCnt;
	int _gunAnimCnt;
	int _gunAnimIdx;
	bool _usingGun;
	int _gunReaction; // ¹Ýµ¿

	//ÃÑ¾Ë
	int _bulletCnt;

	//ÃÑ±âÈ­¿°
	int _fireCnt;
	int _fireIdx;

	int _createBulletPosX;
	int _createBulletPosY;
	//Äí³ªÀÌ
	float _lerpSpeed;
	bool _canLeftWallJump;
	bool _canRightWallJump;
	bool _usingKunai;


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

	void shot(void);
	void fire(void);
	


	void Hit(void);
	
	DustEffect _dustEffect;
	FireBullet _bullet;
	void titlePlayer(HDC hdc);

	Kunai* getKunai() { return _kunai; }

	inline STATE getState() { return _currentState; }
	inline RECT getPlayerPos() { return _rc; }
	inline int getPlayerCenter() { return (_rc.left + _rc.right) / 2; }

	inline RECT getATKRange() { return _rangeATK; }

	inline bool getIsJumping() { return _isJumping; }
	inline bool getColRight() { return _colRight; }

	inline float getColTop() { return _gravityJumpPower; }

	inline bool getKnife() { return _knife; }
	inline bool getTxtKnife() { return _txtKnife; }
	inline bool getPanalKnife() { return _panalKnife; }
	inline bool getTxtCom() { return _txtCom; }
	inline bool getDownJump() { return _downJump; }
	inline bool getGoDownjump() { return _goDownJump; }

	inline bool getColKunai() { return _colKunai; }
	inline bool getTxtKunai() { return _txtKunai; }
	inline bool getPanalKunai() { return _panalKunai; }

	inline bool getUsingGun() { return _usingGun; }
	inline bool getShoot() { return shoot; }

	inline bool getColGun() { return _colGun; }
	inline bool getTxtGun() { return _txtGun; }
	inline bool getPanalGun() { return _panalGun; }

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

	float getPosX() { return _rc.left; }
	float getPosY() { return _rc.top; }
	bool getUsingKunai() { return _usingKunai; }
	void setPosX(float x) { _rc.left = x; _rc.right = x + 74; }
	void setPosY(float y) { _rc.top = y; _rc.bottom = y + 74; }
	void setGravity(float gravity) { _gravity = gravity; }

	inline void setIsGravity(bool isGravity) { _isGravity = isGravity; }
	inline void setColRight(bool colRight) { _colRight = colRight; }
	inline void setColLeft(bool colLeft) { _colLeft = colLeft; }
	inline void setColTop(bool colTop) { _colTop = colTop; }
	inline void setKnife(bool knife) { _knife = knife; }
	inline void setTxtKnife(bool txtKnife) { _txtKnife = txtKnife; }
	inline void setPanalKnife(bool panalKnife) { _panalKnife = panalKnife; }
	inline void setTxtCom(bool txtCom) { _txtCom = txtCom; }
	inline void setcolCom(bool colCom) { _colCom = colCom; }

	inline void setcolKunai(bool colKunai) { _colKunai = colKunai; }
	inline void setTxtKunai(bool txtKunai) { _txtKunai = txtKunai; }
	inline void setPanalKunai(bool panalKunai) { _panalKunai = panalKunai; }

	inline void setcolGun(bool colGun) { _colGun = colGun; }
	inline void setTxtGun(bool txtGun) { _txtGun = txtGun; }
	inline void setPanalGun(bool panalGun) { _panalGun = panalGun; }


	inline void setDownJump(bool downJump) { _downJump = downJump; }
	inline void setGoDownJump(bool goDoinJump) { _goDownJump = goDoinJump; }
	inline void setUsingGun(bool usingGun) { _usingGun = usingGun; }

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
	void setUsingKunai(bool kunai) { _usingKunai = kunai; }

	

	void setIsCanLeftWallJump(bool canLeftWallJump) { _canLeftWallJump = canLeftWallJump; }
	void setIsCanRightWallJump(bool canRightWallJump) { _canRightWallJump = canRightWallJump; }

	//Æ©Åä¸®¾ó°ü·Ã
	bool getUsingKnife() { return _usingKnife; }
	void setUsingKnife(bool x) { _usingKnife = x; }
	//==============================


	//void setPanalCom(bool panalCom) { _panalCom = panalCom; }
	
	


//	void savePosition();

	Player();
	~Player();
};

