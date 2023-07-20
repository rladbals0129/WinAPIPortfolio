#pragma once
#include "GameNode.h"
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

class RotationRender : public GameNode
{
private:
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Image* image;
    REAL _angle;

public:
    HRESULT init(void);
    void release(void);
   // void Render(HDC hdc, int x, int y, float angle);
   
    void LoadImage(wchar_t* filePath);
    void RotateRender(int x, int y, int width, int height);
    void rotateImage(REAL delta_angle);
};