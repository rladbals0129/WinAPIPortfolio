#include "Stdafx.h"
#include "Kunai.h"

HRESULT Kunai::init()
{

    speed = 30;
    angle = 0.0;
    isLeftFlying = false;
    isRightFlying = false;
    _render = false;
    isLeftStuck = false;
    isRightStuck = false;
	return S_OK;
}

void Kunai::release(void)
{

}

void Kunai::update(void)
{

    if (KEYMANAGER->isStayKeyDown('Q'))
    {
        isLeftFlying = false;
        angle = -135.0f;
    }
    else
    {
        isLeftFlying = true;
        isLeftStuck = false;
    }
    if (KEYMANAGER->isStayKeyDown('E'))
    {
        isRightFlying = false;
        angle = -55.0f;
    }
    else
    {
        isRightFlying = true;
        isRightStuck = false;
    }

    if (!isLeftFlying && !isLeftStuck)
    {
        float radian = angle * (3.14159265f / 180.0f);
        _rc1.left += speed * cos(radian);
        _rc1.top += speed * sin(radian);
    }
    else
    {
        _rc1 = RectMake(PLAYER->getPlayerPos().left - 60, PLAYER->getPlayerPos().top - 20, 60, 160);
    }
    if (!isRightFlying && !isRightStuck)
    {
        float radian = angle * (3.14159265f / 180.0f);
        _rc2.left += speed * cos(radian);
        _rc2.top += speed * sin(radian);
    }
    else
    {
        _rc2 = RectMake(PLAYER->getPlayerPos().left + 70, PLAYER->getPlayerPos().top - 20, 60, 160);
    }
}

void Kunai::render(HDC hdc)
{
    IMAGEMANAGER->frameRender("Äí³ªÀÌ1", hdc, _rc1.left, _rc1.top,0,1);

    IMAGEMANAGER->frameRender("Äí³ªÀÌ2", hdc, _rc2.left, _rc2.top,0,0);
}
