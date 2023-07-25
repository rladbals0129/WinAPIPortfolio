#pragma once
#include "GameNode.h"
class Title : public GameNode
{
private:
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
	bool _StartTutorial;
	

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	bool getStartGame() { return _StartGame; }
	bool getStartTutorial() { return _StartTutorial; }

	void setStartGame(bool x) { _StartGame = x; }
	void setStartTutorial(bool x) { _StartTutorial = x; }

	void animSelectL(void);
	void animSelectR(void);
};

