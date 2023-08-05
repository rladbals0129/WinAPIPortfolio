#pragma once
#include "GameNode.h"
class Ending : public GameNode
{
private:
	HWND _hWndVideo;
	bool _nextScene;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	


	bool getNextScene() { return _nextScene; }
};

