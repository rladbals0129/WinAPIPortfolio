#pragma once
#include "GameNode.h"

class IntroScene : public GameNode
{
private:
	HWND _hWndVideo;
	bool _nextScene;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void playVideo();


	bool getNextScene() { return _nextScene; }
	
	IntroScene() {}
	~IntroScene() {}
};

