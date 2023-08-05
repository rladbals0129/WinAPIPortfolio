#pragma once
#include "GameNode.h"
#include "RotationRender.h"
#include "RigidBody.h"
#include "Fragment.h"
#include "Zombiebot.h"
#include "BoxBreakEffect.h"
#include "ZombieManager.h"
#include "KunaiCollision.h"
#include "Boss.h"
#include "Lipo.h"
class Stage3 :public GameNode
{
private:
	enum MAP
	{
		map1, map2,
		map3
	};
	RECT _collider;

	int _offsetX;
	int _offsetY;

	MAP _currentMap;
	RotationRender* _rot;
	KunaiCollision _kunaiCOl;

	RigidBody m_rigidBody;
	bool m_isDestroyed;
	std::vector<Fragment> m_fragments;
	float m_gravity;

	BoxBreakEffect _slashEffect;
	bool createBoxEF;
	//==============

	Zombiebot* _zm;
	vector<Zombiebot*> _Fzm;
	int _zombieDiePosX;
	int _zombieDiePosY;

	std::vector<Fragment> _Zfragments;
	bool _zomIdle;
	int _zomIdleCnt;
	//========��====

	float _knockBackMagnitude;
	bool _hitDelay;
	int _hitCnt;

	//===����
	Boss* _boss;
	RECT _bossgetCOl;
	bool _UIBossRender;
	bool _bossGet;
	bool _renderBoss;
	int _panalBossCnt;
	int _bossCnt;
	int _bossIdx;

	
	RECT _pPosRc;
	//===����
	float _lerpSpeed;

	//==ȭ������
	float _shakeDuration;
	float _shakeOffsetX;
	float _shakeOffsetY;

	float _initialShakeDuration = 0.5f;  // ���� ���ӽð�
	float _initialShakeMagnitude = 15.0f; // ���� ����
	bool _switchScreen;


	//==����
	bool _zombieOnce;
	int _bossHitCnt;
	int _bossHitDelay;
	bool _bossSound;
	bool _bossCreateSound;
	//== �ڽT
	vector<Lipo*> _Flp;
	vector<Fragment> _Lfragments;
	bool lipoInit;

	//==����
	bool _clear;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	void playerPixel();

	void updateZombieBot();
	void renderZombieBot();


	void moveCamera(int LcameraOffsetX, int RcameraOffsetX, int LmaxOffsetX, int RmaxOffsetX);

	void updateShakeEffect(float& shakeDuration, float& shakeOffsetX, float& shakeOffsetY);
	void applyShake(float shakeDuration);
	void createFragments(std::vector<Fragment>& fragments, const POINT& position, wchar_t* imagePath, int numFragments);

	void createZombie(int x, int y);

	void createLipo(int x, int y);
	void updateLipo();
	void renderLipo();

	bool getClear() { return _clear; }
};

