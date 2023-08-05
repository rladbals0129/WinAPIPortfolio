#pragma once
#include "GameNode.h"
class Lipo : public GameNode
{
private:
	RECT _rc;
	RECT _Range;
	int _dmg;
	bool _isDie;

	bool _boomStart;
	bool _once;
	bool _isLeft;
	bool _boom;
	
	int _state;

	int iCnt;
	int iIdx;
	int iYIdx;
	int Bcnt;
	int BIdx;
	int BYIdx;


	int _breakSizeX;
	int _breakSizeY;
	int _breakStartX;
	int _breakStartY;

	bool _soundReady;
	bool _soundBoom;
	bool _recognition;

public:
	HRESULT init(void);
	void release(void);
	void UpdateLipo(void);
	void render();

	inline int getAtk() { return _dmg; }
	inline bool getDie() { return _isDie; }
	inline RECT getPos() { return _rc; }
	inline bool getIsLeft() { return _isLeft; }
	inline RECT getRange() { return _Range; }
	inline int getState() { return _state; }
	inline int getCenter() { return (_rc.left + _rc.right) / 2; }
	inline bool getRecognition() { return _recognition; }

	inline void setRecognition(bool recognition) { _recognition = recognition; }
	inline void setDie(bool die) { _boomStart = die; }
	inline void setPosLeft(int x) { _rc.left += x; _rc.right += x; }
	inline void setPosRight(int x) { _rc.left -= x; _rc.right -= x; }
	inline void setPosBottom(int y) { _rc.top -= y; _rc.bottom -= y; }
	inline void setPosTop(int y) { _rc.top += y; _rc.bottom += y; }
	inline void setPos(int x, int y) { _rc = { x,y,x + 90,y + 82 }; }
	inline void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	inline void setState(int state) { _state = state; }
	
	inline void setBreakStartXRight(int x) { _breakStartX -= x; }
	inline void setBreakStartXLeft(int x) {	_breakStartX += x;}


	void idle();
	void boom();
};

