#pragma once
//#include "Enemy.h"
#include "GameNode.h"



class Zombiebot : public GameNode
{
private:
	RECT _rc;
	RECT _Range;
	int _dmg;
	bool _isDie;

	bool _isWake;
	bool _isLeft;
	bool _go;

	//bool _isLeft;

	
	
	int _state;

	int _Scnt;
	int _Sidx;
	int _Wcnt;
	int _Widx;
	int _Mcnt;
	int _Midx;
	int _MYidx;

	//sound
	bool _aggroSound;
	bool _deathSound;
public:
	HRESULT init(void);
	void release(void);
	void UpdateZombie(void);
	void render();


	

	//inline int getHp() { return _hp; }
	inline int getAtk() { return _dmg; }
	inline bool getDie() { return _isDie; }
	inline RECT getPos() { return _rc; }
	inline bool getIsLeft() { return _isLeft; }
	inline RECT getRange() { return _Range; }
	inline int getState() { return _state; }
	inline bool getGo() { return _go; }
	inline bool getWake() { return _isWake; }
	inline int getCenter() { return (_rc.left + _rc.right) / 2; }

//	inline void setHp(int hp) { _hp = hp; }
	inline void setDie(bool die) { _isDie = die; }
	inline void setPosLeft(int x) { _rc.left += x; _rc.right += x; }
	inline void setPosRight(int x) { _rc.left -= x; _rc.right -= x; }
	inline void setPosBottom(int y) { _rc.top -= y; _rc.bottom -= y; }
	inline void setPosTop(int y) { _rc.top += y; _rc.bottom += y; }
	inline void setPos(int x, int y) { _rc = { x,y,x + 100,y + 100 }; }
	//RECT rc = { x,y,x + width,y + height };
	inline void setIsLeft(bool isLeft) { _isLeft = isLeft;}
	inline void setState(int state) { _state = state; }
	inline void setGo(bool go) { _go = go; }
	inline void setWake(bool wake) { _isWake = wake; }

	inline bool getDeathSound() { return _deathSound; }
	inline void setDeathSound(bool deathSound) { _deathSound = deathSound; }

	void sleep();
	void wake();
	void move();
	
};

