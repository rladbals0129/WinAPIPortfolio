#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init()
{
	GameNode::init(true);
	_resource.init();
	_title = new Title;
	_intro = new IntroScene;
	_stage1 = new Stage1;
	_stage2 = new Stage2;
	_stage3 = new Stage3;
	_tutorial = new Tutorial;

	_title->init();
	
	_currentScene = _title;

	_playVideo = false;
	_startStage1 = false;
	_startTutorial = false;
	_startStage2 = false;
	
	assert(_currentScene != nullptr); 	// <->

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	_title->release();
	_intro->release();
	_stage1->release();
	_stage2->release();
	_stage3->release();
	_tutorial->relese();
	SAFE_DELETE(_title);
	SAFE_DELETE(_intro);
	SAFE_DELETE(_stage1);
	SAFE_DELETE(_stage2);
	SAFE_DELETE(_stage3);
	SAFE_DELETE(_tutorial);
}

void MainGame::update(void)
{
	GameNode::update();

	if (_title->getStartGame())
	{	
		if (!_playVideo)
		{
			_intro->init();
			_playVideo = true;
		}
		_currentScene = _intro;
		_title->setStartGame(false);
	}
	if (_title->getStartTutorial())
	{
		_tutorial->init();
		_currentScene = _tutorial;
		_title->setStartTutorial(false);
	}
	if (_tutorial->getGoTitle())
	{
	
		_currentScene = _title;

		_tutorial->setGoTitle(false);
		
		
	}
	if (_intro->getNextScene())
	{
		if (!_startStage1)
		{
			_stage1->init();
			_startStage1 = true;
		}
		_currentScene = _stage1;
	}
	if (_stage1->getGoStage2())
	{
		if (!_startStage2)
		{
			_stage2->init();
			_startStage2 = true;
		}
		_currentScene = _stage2;

	}
	if (_stage2->getGoStage3())
	{
		if (!_startStage3)
		{
			_stage3->init();
			_startStage3 = true;
		}
		_currentScene = _stage3;
	}

	_currentScene->update();

}

void MainGame::render(void)
{
	if (_currentScene != _intro)
	{
		PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
		_currentScene->render();
		this->getBackBuffer()->render(getHDC());
	}
	
}
