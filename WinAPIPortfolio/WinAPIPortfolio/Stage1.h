#pragma once
#include "GameNode.h"

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

struct BREAKOBJECT
{
	RECT rc;
	bool isBreak;
	bool push;
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


class Stage1 : public GameNode
{
private:
	RECT _pPosRc;
	RECT _pPosRcCol;

	RECT _bgImage;

	MAP _currentMap;
	bool _boom;
	GlassFragment _gl[50];
	
	BREAKOBJECT _breakObject;

	vector<BREAKOBJECT> _obj;

	RECT _collider;

	float _offsetX;
	float _offsetY;
	bool _renderBreakGlass;

	//��Ʈ�� �� ���۱۶�
	
	int _glassIdx;

	bool _readyPlayer;
	int _readyIdx;
	int _readyCnt;
	bool _createPlayer;

	//ȭ�� ��鸲
	bool _shakeScreen;
	int _shakeDuration;
	int _shakeAmount;
	//������ ����Ʈ ������
	int _breakSizeX;
	int _breakSizeY;
	int _breakStartX;
	int _breakStartY;
	bool _breakFX;
	//��������
	


	//�� �ִϸ��̼�
	int _cutDoorL;
	int _cutDoorR;
	bool _renderDoor;

	//�Ϻ��� ȹ��
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

	//==========


	
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void openDoorR();
	void openDoorL();


	void efKnife();
	

	void shakeScreen(int currntOffsetX, int currntOffsetY, int shakeAmount);
	void moveCamera(int LcameraOffsetX,int RcameraOffsetX,  int cameraOffsetY, int LmaxOffsetX, int RmaxOffsetX, int maxOffsetY);
	void glassBoom();


	void updateObject();
	void createBreakObject(int x, int y, int width, int height, bool isBreak);

};
