#pragma once
#include "GameNode.h"

#define PI 3.141592f
#define RADIAN(dig) (PI * (dig) / 180.f)
enum MAP
{
	map1,map2,
	map3,map4,
	map5,map6,
	map7,map8,
	map9,map10,
	map11
};

class Stage1 : public GameNode
{
private:
	RECT _pPosRc;
	RECT _pPosRcCol;

	MAP _currentMap;

	RECT _collider;

	float _offsetX;
	float _offsetY;
	bool _renderBreakGlass;

	//��Ʈ�� �� ���۱۶�
	
	int _glassIdx;

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
	int _mglassPushX;
	int _mglassPushY;
	float _mglassAngle;
	int _mglassCnt;
	int _mglassIdx;
	RECT _glass[50];


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

	
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void openDoorR();
	void openDoorL();


	void efKnife();
	

	void shakeScreen(int currntOffsetX, int currntOffsetY);
	void glassBoom();


};

