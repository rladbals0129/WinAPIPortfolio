#pragma once
#include "GameNode.h"
#include "RotationRender.h"
#include "RigidBody.h"
#include "Fragment.h"
#include "Zombiebot.h"
#include "BoxBreakEffect.h"
#include "ZombieManager.h"
#include "KunaiCollision.h"
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
	//========적====

	float _knockBackMagnitude;
	bool _hitDelay;
	int _hitCnt;


	RECT _pPosRc;
	//===쿠나이
	float _lerpSpeed;

	//==화면흔들기
	float _shakeDuration;
	float _shakeOffsetX;
	float _shakeOffsetY;

	float _initialShakeDuration = 0.5f;  // 흔들기 지속시간
	float _initialShakeMagnitude = 15.0f; // 흔들기 강도
	bool _switchScreen;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	void playerPixel();

	void moveCamera(int LcameraOffsetX, int RcameraOffsetX, int LmaxOffsetX, int RmaxOffsetX);

	void updateShakeEffect(float& shakeDuration, float& shakeOffsetX, float& shakeOffsetY);
	void applyShake(float shakeDuration);
	void createFragments(std::vector<Fragment>& fragments, const POINT& position, wchar_t* imagePath, int numFragments);
};

