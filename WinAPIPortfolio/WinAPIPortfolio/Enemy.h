#pragma once
#include "GameNode.h"
#include "Fragment.h"

class Enemy : public GameNode
{
private:
	int _hp;
	int _dmg;
	bool _isDie;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	inline int GetHp() { return _hp; }
	inline int GetAtk() { return _dmg; }
	inline bool GetDie() { return _isDie; }

	inline void SetHp(int hp) { _hp = hp; }
	inline void SetDie(bool die) { _isDie = die; }
	
};

