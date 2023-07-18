#include "Stdafx.h"
#include "IntroScene.h"

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

HRESULT IntroScene::init(void)
{
    _hWndVideo = MCIWndCreate(_hWnd, _hInstance, MCIWNDF_NOPLAYBAR, "Resources/Video/Intro.wmv");

    MoveWindow(_hWndVideo, 0, 0, WINSIZE_X, WINSIZE_Y, FALSE);

    MCIWndPlay(_hWndVideo);

    _nextScene = false;
    

    return S_OK;
}

void IntroScene::release(void)
{
    MCIWndClose(_hWndVideo);
    MCIWndDestroy(_hWndVideo);
}

void IntroScene::update(void)
{                                               //영상 전체 길이                      현제 재생 시간
    if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE) || MCIWndGetLength(_hWndVideo) <= MCIWndGetPosition(_hWndVideo))
    {

        _nextScene = true;
        release();
    }
}

void IntroScene::render(void)
{
}

void IntroScene::playVideo()
{

}
