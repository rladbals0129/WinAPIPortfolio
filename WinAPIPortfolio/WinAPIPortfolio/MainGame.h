#pragma once
#include "GameNode.h"
#include "Title.h"
#include "IntroScene.h"
#include "Stage1.h"
#include "ResourceClass.h"

class MainGame : public GameNode
{
private:
	ResourceClass _resource;
	Title* _title;
	Stage1* _stage1;
	IntroScene* _intro;

	GameNode* _currentScene;

	bool _playVideo;
	bool _startStage1;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() : _currentScene(nullptr) {}
};

