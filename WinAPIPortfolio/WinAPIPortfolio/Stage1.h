#pragma once
#include "GameNode.h"
#include "RotationRender.h"
#include "RigidBody.h"
#include "Fragment.h"
#include "Zombiebot.h"
#include "BoxBreakEffect.h"
#include "ZombieManager.h"


#define PI 3.141592f
#define RADIAN(dig)  (PI * dig) / 180.f
#define GRAVITY  0.5f;
enum MAP
{
	map1,map2,
	map3,map4,
	map5,map6,
	map7,map8,
	map9,map10,
	map11
};




struct GlassFragment
{
	int glassCnt;
	int glassXIdx;
	int glassYIdx;



	float angle;
	float distance;
	int centerX;
	int centerY;

	int createX, createY;

	int bounceX;
	int bounceY;
	int bounce;

	//int setPosY;
	RECT glass;


	bool isGlass;
	int alpha;
	int alphaCnt;

	int speedX;
	int speedY;
	int speed;
};

struct BREAKOBJECT
{
	RECT rc;
	bool isBreak;

};
class Stage1 : public GameNode
{
private:
	RotationRender* _rot;
	
	
	RigidBody m_rigidBody;
	bool m_isDestroyed;
	std::vector<Fragment> m_fragments;
	float m_gravity; 
	vector<BREAKOBJECT> _obj;
	vector<BREAKOBJECT> _box2;
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


	bool _once;

	RECT _pPosRc;
	RECT _pPosRcCol;

	RECT _bgImage;

	MAP _currentMap;
	bool _boom;
	GlassFragment _gl[50];
	
	BREAKOBJECT _box[10];

	

	RECT _collider;

	int _offsetX;
	int _offsetY;
	bool _renderBreakGlass;

	//인트로 후 시작글라스
	
	int _glassIdx;

	bool _readyPlayer;
	int _readyIdx;
	int _readyCnt;
	bool _createPlayer;

	//깨지기 이펙트 사이즈
	int _breakSizeX;
	int _breakSizeY;
	int _breakStartX;
	int _breakStartY;
	bool _breakFX;
	//유리조각
	bool _explosion;


	//문 애니메이션
	int _cutDoorL;
	int _cutDoorR;
	bool _renderDoor;

	//일본도 획득
	bool _knifeGet;
	bool _UIknifeRender;
	bool _renderKnife;

	RECT _obCol;
	

	int _keyUPCnt;
	int _keyUPIdx;

	int _knifeCnt;
	int _knifeIdx;

	int _enterCnt;
	int _enterIdx;

	int _panalCnt;
	int _panalOffsetY;
//=========================================

	bool _upBtnRender;
	bool _txtComputer1;

	//==========쿠나이
	Kunai* _kunai;

	float _shakeDuration;
	float _shakeOffsetX;
	float _shakeOffsetY;

	 float _initialShakeDuration = 0.5f;  // 흔들기 지속시간
	 float _initialShakeMagnitude = 15.0f; // 흔들기 강도

	ZombieManager _zombieManager;

	float _lerpSpeed;

	
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void openDoorR();
	void openDoorL();
	//====파편=====
//	void addFragment(const Fragment& fragment);
	//=======

	void efKnife();
	

	void moveCamera(int LcameraOffsetX,int RcameraOffsetX,  int cameraOffsetY, int LmaxOffsetX, int RmaxOffsetX, int maxOffsetY);
	void glassBoom();

	void updateShakeEffect(float& shakeDuration, float& shakeOffsetX, float& shakeOffsetY);
	void applyShake(float shakeDuration);
	void createFragments(std::vector<Fragment>& fragments, const POINT& position, wchar_t* imagePath, int numFragments);


};

