#pragma once
#include "GameNode.h"
#include "Kunai.h"
class Boss : public GameNode
{
private:
	enum STATE
	{
		IDLE,ATTACK1,
		ATTACK2,ATTACK3,
		DIE
	};
	Kunai* _kunaiCol;
	int _hp;
	int _dmg;
	bool _die;
	bool _hit;

	RECT _rc;
	STATE _currentState;
	RECT _rockRc;
	RECT _collider;

	bool _isLeft;

	int _currentPattern;

	// ¼û,È¸Àü
	int _breath;
	int _obj1;
	int _obj2;
	int _obj3;
	int _obj4;
	int _obj5;
	int _obj6;
	int _obj7;
	int _obj8;
	int _obj9;
	int _idleHandCnt;
	int _idleWeaponCnt;

	int _delayTime;

	int _movementTime;  
	int _maxMovementTime;

	int _delayTime2;

	int _aCnt;
	int _alpha;

	bool _once;

	int _FXDieCnt;
	int _goFX;
	bool _FXDie;
	int _breakSizeX;
	int _breakSizeY;
	int _breakStartX;
	int _breakStartY;

	int _dieAlpha;

	bool _realDie;

	bool _clear;

	bool _patternSound1;
	bool _patternSound2;
	bool _patternSound3;
	bool _shieldSound;
	bool _hitSound;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void pattern1(void);
	void pattern2(void);
	void pattern3(void);
	void dieAnim(void);

	void IdleBossRender(void);

	inline int getHp() { return _hp; }
	inline int getAtk() { return _dmg; }
	inline bool getDie() { return _die; }
	inline RECT getPos() { return _rc; }
	inline bool getIsLeft() { return _isLeft; }
	inline int getCenter() { return (_rc.left + _rc.right) / 2; }
	int getPattern() { return _currentPattern; }
	bool getHit() { return _hit; }
	STATE getStateAttack2() { return ATTACK2; }

	STATE getCurrentState() { return _currentState; }
	bool getClera() { return _clear; }
	void setHit(bool hit) { _hit = hit; }

	bool getRealDie() { return _realDie; }


	

	void setPattern(int x) { _currentPattern = x; }
	void setHp(int hp) { _hp = hp; }
	void setDie(bool die) { _die = die; }
	void setStateIdle() { _currentState = IDLE; }
	//void setCurrentPattern(int currentPattern) { _currentPattern = currentPattern; }

	
};

