#pragma once
#include "GameNode.h"
#include "Title.h"
#include "IntroScene.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Tutorial.h"
#include "Ending.h"
#include "ResourceClass.h"
#include "SoundClass.h"

class MainGame : public GameNode
{
private:
	ResourceClass _resource;
	SoundClass _sound;

	Title* _title;
	Stage1* _stage1;
	Stage2* _stage2;
	Stage3* _stage3;
	Ending* _ending;
	IntroScene* _intro;
	Tutorial* _tutorial;

	GameNode* _currentScene;

	bool _playVideo;
	bool _startStage1;
	bool _startTutorial;
	bool _startStage2;
	bool _startStage3;
	bool _gameEnd;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() : _currentScene(nullptr) {}
};

