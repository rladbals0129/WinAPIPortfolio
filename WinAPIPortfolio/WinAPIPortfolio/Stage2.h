#pragma once
#include "GameNode.h"
#include "RotationRender.h"
#include "RigidBody.h"
#include "Fragment.h"
#include "Zombiebot.h"
#include "BoxBreakEffect.h"
#include "ZombieManager.h"
#include "KunaiCollision.h"


class Stage2 : public GameNode
{
private:
	enum MAP
	{
		map1, map2,
		map3, map4
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
	//============Àû==

	Zombiebot* _zm;
	vector<Zombiebot*> _Fzm;
	int _zombieDiePosX;
	int _zombieDiePosY;

	std::vector<Fragment> _Zfragments;
	bool _zomIdle;
	int _zomIdleCnt;
	//========³Ë¹é====

	float _knockBackMagnitude;
	bool _hitDelay;
	int _hitCnt;


	RECT _pPosRc;
	//===Äí³ªÀÌ
	float _lerpSpeed;

	//==È­¸éÈçµé±â
	float _shakeDuration;
	float _shakeOffsetX;
	float _shakeOffsetY;

	float _initialShakeDuration = 0.5f;  // Èçµé±â Áö¼Ó½Ã°£
	float _initialShakeMagnitude = 15.0f; // Èçµé±â °­µµ
	bool _switchScreen;

	//ÃÑ È¹µæ//
	int _panalGunOffsetY;
	RECT _gungetCOl;
	bool _UIGunRender;
	bool _gunGet;
	bool _renderGun;
	int _panalGunCnt;
	int _gunCnt;
	int _gunIdx;

	bool _sound;
	//=========½ºÅ×ÀÌÁö3 
	bool _goStage3;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void efGun();


	void playerPixel();

	void moveCamera(int LcameraOffsetX, int RcameraOffsetX, int cameraOffsetY, int LmaxOffsetX, int RmaxOffsetX, int maxOffsetY);

	void updateShakeEffect(float& shakeDuration, float& shakeOffsetX, float& shakeOffsetY);
	void applyShake(float shakeDuration);
	void createFragments(std::vector<Fragment>& fragments, const POINT& position, wchar_t* imagePath, int numFragments);

	void updateZombieBot();
	void renderZombieBot();

	bool getGoStage3() { return _goStage3; }
	void setGoStage3(bool goStage3) { _goStage3 = goStage3; }

};

