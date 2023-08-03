#pragma once
#include "GameNode.h"
class Boss : public GameNode
{
private:
	enum STATE
	{
		IDLE,ATTACK1,
		ATTACK2,ATTACK3,
		DIE
	};
	int _hp;
	int _dmg;
	bool _die;

	RECT _rc;
	STATE _currentState;

	bool _isLeft;

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







public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void pattern1(void);
	void pattern2(void);
	void pattern3(void);
	
	void IdleBossRender(void);
	
	
};

