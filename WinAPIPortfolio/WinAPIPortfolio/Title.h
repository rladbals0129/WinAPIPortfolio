#pragma once
#include "GameNode.h"
#include "Player.h"
class Title : public GameNode
{
private:
	Player* _player;

	RECT _col;
	RECT _selectArrowL;
	RECT _selectArrowR;
	RECT _select[3];

	int _idx;

	int _arrowCntL;
	int _arrowIdxL;
	int _arrowCntR;
	int _arrowIdxR;

	bool _StartGame;

	

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	bool getStartGame() { return _StartGame; }

	void animSelectL(void);
	void animSelectR(void);
};

