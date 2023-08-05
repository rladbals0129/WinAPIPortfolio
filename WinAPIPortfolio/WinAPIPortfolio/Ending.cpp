#include "Stdafx.h"
#include "Ending.h"

HRESULT Ending::init(void)
{
    _hWndVideo = MCIWndCreate(_hWnd, _hInstance, MCIWNDF_NOPLAYBAR, "Resources/Video/Lemonkus.wmv");

    MoveWindow(_hWndVideo, 0, 0, WINSIZE_X, WINSIZE_Y, FALSE);

    MCIWndPlay(_hWndVideo);

    _nextScene = false;


    return S_OK;
}

void Ending::release(void)
{
    MCIWndClose(_hWndVideo);
    MCIWndDestroy(_hWndVideo);
}

void Ending::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE) || MCIWndGetLength(_hWndVideo) <= MCIWndGetPosition(_hWndVideo))
    {

        _nextScene = true;
        release();
    }
}

void Ending::render(void)
{
}

