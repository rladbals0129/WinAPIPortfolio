#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init()
{
	GameNode::init(true);
	_resource.init();
	_title = new Title;
	_intro = new Intro;
	_stage1 = new Stage1;

	_title->init();
	_intro->init();
	_stage1->init();

	_currentScene = _title;


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
		_intro->playVideo();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		_currentScene = _stage1;
		//_intro->release();
	}
	_currentScene->update();

}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	_currentScene->render();
	this->getBackBuffer()->render(getHDC());
}

//void MainGame::playVideo()
//{
//	HWND LogoVideo;
//
//	LogoVideo = MCIWndCreate(_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD, "Resources/video/Intro.avi");
//
//	MoveWindow(LogoVideo, 0, 0, 1280, 800, NULL);
//	MCIWndPlay(LogoVideo);
//}
//
//void MainGame::stopVideo()
//{
//	MCIWndClose(LogoVideo);sadasdqqweqweqwe
//}
