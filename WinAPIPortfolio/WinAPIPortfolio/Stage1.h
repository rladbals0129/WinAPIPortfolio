#pragma once
#include "GameNode.h"
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
	//인트로 후 시작글라스
	bool _breakGlass;
	int _glassIdx;


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

	
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void openDoorR();
	void openDoorL();


	void efKnife();
	void efUIKeybordUp();
	void efUIReturn();

};

