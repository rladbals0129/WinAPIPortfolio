#pragma once
#include "GameNode.h"
#include "RotationRender.h"
#include "RigidBody.h"
#include "Fragment.h"
#include "Zombiebot.h"
#include "BoxBreakEffect.h"
#include "ZombieManager.h"
#include "KunaiCollision.h"

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
	enum MAP
	{
		map1, map2,
		map3, map4,
		map5, map6,
		map7, map8,
		map9, map10,
		map11
	};
	RotationRender* _rot;
	KunaiCollision _kunaiCOl;
	
	RigidBody m_rigidBody;
	std::vector<Fragment> m_fragments;
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
	//========��====

	float _knockBackMagnitude;
	bool _hitDelay;
	int _hitCnt;


	RECT _pPosRc;


	MAP _currentMap;
	bool _boom;
	GlassFragment _gl[50];
	
	BREAKOBJECT _box[10];

	

	RECT _collider;

	int _offsetX;
	int _offsetY;
	bool _renderBreakGlass;

	//��Ʈ�� �� ���۱۶�
	
	int _glassIdx;

	bool _readyPlayer;
	int _readyIdx;
	int _readyCnt;
	bool _createPlayer;

	//������ ����Ʈ ������
	int _breakSizeX;
	int _breakSizeY;
	int _breakStartX;
	int _breakStartY;
	bool _breakFX;
	//��������
	bool _explosion;


	//�� �ִϸ��̼�
	int _cutDoorL;
	int _cutDoorR;
	bool _renderDoor;

	//�Ϻ��� ȹ��
	bool _knifeGet;
	bool _UIknifeRender;
	bool _renderKnife;

	RECT _obCol;
	



	int _knifeCnt;
	int _knifeIdx;



	int _panalCnt;
	int _panalOffsetY;
//=========================================

	bool _upBtnRender;
	bool _txtComputer1;

	//==========����
	float _lerpSpeed;
	//����ȹ��
	int _panalKunaiOffsetY;
	RECT _kunaigetCOl;
	bool _UIkunaiRender;
	bool _kunaiGet;
	bool _renderKunai;
	int _panalKunaiCnt;
	int _kunaiCnt;
	int _kunaiIdx;
	//=======
	bool _goStage2;


	//==ȭ��==
	float _shakeDuration;
	float _shakeOffsetX;
	float _shakeOffsetY;

	 float _initialShakeDuration = 0.5f;  // ���� ���ӽð�
	 float _initialShakeMagnitude = 15.0f; // ���� ����
	 bool _switchScreen;
	
	

	
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void openDoorR();
	void openDoorL();
	//====����=====
//	void addFragment(const Fragment& fragment);
	//=======

	void efKnife();
	void efKunai();

	void glassBoom();
	void moveCamera(int LcameraOffsetX,int RcameraOffsetX,  int cameraOffsetY, int LmaxOffsetX, int RmaxOffsetX, int maxOffsetY);

	void updateShakeEffect(float& shakeDuration, float& shakeOffsetX, float& shakeOffsetY);
	void applyShake(float shakeDuration);
	void createFragments(std::vector<Fragment>& fragments, const POINT& position, wchar_t* imagePath, int numFragments);

	bool getGoStage2() { return _goStage2; }
	void setGoStage2(bool goStage2) { _goStage2 = goStage2; }
	

};

