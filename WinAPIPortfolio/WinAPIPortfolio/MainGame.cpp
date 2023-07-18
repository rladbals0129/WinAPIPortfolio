#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init()
{
	GameNode::init(true);
	_resource.init();
	_title = new Title;
	_intro = new IntroScene;
	_stage1 = new Stage1;

	_title->init();
	
	_currentScene = _title;

	_playVideo = false;
	_startStage1 = false;
	
	assert(_currentScene != nullptr); 	// <->

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	_title->release();
	_intro->release();
	_stage1->release();
	SAFE_DELETE(_title);
	SAFE_DELETE(_intro);
	SAFE_DELETE(_stage1);
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
