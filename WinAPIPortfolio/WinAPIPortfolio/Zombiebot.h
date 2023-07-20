#pragma once
#include "Enemy.h"
class Zombiebot : public Enemy
{
private:
	RECT _rc;
	RECT _Range;
	int _hp;
	int _dmg;
	bool _isDie;

	bool _idle;
	bool _go;
	bool _sleepFinish;
	bool _wakeFinish;

	bool _isLeft;
	
	int _state;

	int _Scnt;
	int _Sidx;
	int _Wcnt;
	int _Widx;
	int _Mcnt;
	int _Midx;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	

	inline int getHp() { return _hp; }
	inline int getAtk() { return _dmg; }
	inline bool getDie() { return _isDie; }
	inline RECT getPos() { return _rc; }
	inline bool getIsLeft() { return _isLeft; }
	inline RECT getRange() { return _Range; }
	inline int getState() { return _state; }

	inline void setHp(int hp) { _hp = hp; }
	inline void setDie(bool die) { _isDie = die; }
	inline void setPosLeft(int x) { _rc.left += x; _rc.right += x; }
	inline void setPosRight(int x) { _rc.left -= x; _rc.right -= x; }
	inline void setPosBottom(int y) { _rc.top -= y; _rc.bottom -= y; }
	inline void setPosTop(int y) { _rc.top += y; _rc.bottom += y; }
	inline void setPos(RECT rc) { _rc = rc; }
	inline void setIsLeft(bool isLeft) { _isLeft = isLeft; }

	inline void setState(int state) { _state = state; }
	inline void setGo(bool go) { _go = go; }

	void sleep();
	void wake();
	void move();
	
};

