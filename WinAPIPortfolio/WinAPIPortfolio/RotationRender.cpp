#include "Stdafx.h"
#include "RotationRender.h"

HRESULT RotationRender::init(void)
{
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
    _angle = 0;

    return S_OK;
}

void RotationRender::release(void)
{
    delete image;
    GdiplusShutdown(gdiplusToken);
}


void RotationRender::LoadImage(wchar_t* filePath)
{
    if (image != nullptr)
    {
        delete image;
    }
    image = new Image(filePath);
}

void RotationRender::RotateRender(int x, int y, int width, int height)
{
    Gdiplus::Graphics graphics(getMemDC());    
    graphics.TranslateTransform(-(width / 2), -(height / 2));
    graphics.RotateTransform(_angle);
    graphics.TranslateTransform(width/2, height/2);


    graphics.DrawImage(image, x, y,width,height);
}

void RotationRender::rotateImage(REAL delta_angle)
{
    _angle += delta_angle;
    if (_angle >= 360)
        _angle -= 360;
}