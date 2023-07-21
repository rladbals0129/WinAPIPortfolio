#pragma once
#include "Enemy.h"

struct ZombieState {
	int Mcnt = 0;
	int Midx = 0;
	bool isLeft = false;
};


class Zombiebot : public Enemy
{
private:
	RECT _rc;
	RECT _Range;
	int _hp;
	int _dmg;
	bool _isDie;
	ZombieState _zombieState;

	bool _go;

	//bool _isLeft;

	
	
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
	void UpdateZombie(void);
	void render();
	void initZombieState();

	

	inline int getHp() { return _hp; }
	inline int getAtk() { return _dmg; }
	inline bool getDie() { return _isDie; }
	inline RECT getPos() { return _rc; }
	inline bool getIsLeft() { return _zombieState.isLeft; }
	inline RECT getRange() { return _Range; }
	inline int getState() { return _state; }
	inline bool getGo() { return _go; }
	inline int getCenter() { return (_rc.left + _rc.right) / 2; }

	inline void setHp(int hp) { _hp = hp; }
	inline void setDie(bool die) { _isDie = die; }
	inline void setPosLeft(int x) { _rc.left += x; _rc.right += x; }
	inline void setPosRight(int x) { _rc.left -= x; _rc.right -= x; }
	inline void setPosBottom(int y) { _rc.top -= y; _rc.bottom -= y; }
	inline void setPosTop(int y) { _rc.top += y; _rc.bottom += y; }
	inline void setPos(int x, int y) { _rc = { x,y,x + 100,y + 100 }; }
	//RECT rc = { x,y,x + width,y + height };
	inline void setIsLeft(bool isLeft) { _zombieState.isLeft = isLeft; }

	inline void setState(int state) { _state = state; }
	inline void setGo(bool go) { _go = go; }

	void sleep();
	void wake();
	void move();
	
};

