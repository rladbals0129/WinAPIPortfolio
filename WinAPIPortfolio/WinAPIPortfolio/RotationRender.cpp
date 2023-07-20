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
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);


    int centerX = image->GetWidth() / 2;
    int centerY = image->GetHeight() / 2;
    graphics.TranslateTransform(x, y);
    graphics.RotateTransform(_angle);
    graphics.TranslateTransform(-x, -y);

    graphics.DrawImage(image, x - centerX, y - centerY,width,height);
}

void RotationRender::rotateImage(REAL delta_angle)
{
    _angle += delta_angle;
    if (_angle >= 360)
        _angle -= 360;
}