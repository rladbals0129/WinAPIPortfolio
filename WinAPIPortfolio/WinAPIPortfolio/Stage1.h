#pragma once
#include "GameNode.h"
#include "Player.h"
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
	Player* _player;
	RECT _pPosRc;
	RECT _pPosRcCol;

	MAP _currentMap;

	RECT _collider;

	float _offsetX;
	float _offsetY;

	//문 애니메이션
	int _cutDoorL;
	int _cutDoorR;
	bool _renderDoor;

	//일본도 획득
	bool _knifeGet;
	bool _UIknifeRender;
	bool _renderKnife;
	RECT _knifeCol;
	

	int _keyUPCnt;
	int _keyUPIdx;

	int _knifeCnt;
	int _knifeIdx;

	int _enterCnt;
	int _enterIdx;

	int _panalCnt;
	int _panalOffsetY;
//=========================================

	
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

